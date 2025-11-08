#include"addresslist.h"

// 显示欢迎界面
void showWelcome() {
    printf("\n=========================================\n");
    printf("\t\t通讯录管理系统\n");
    printf("=========================================\n\n");
}

// 显示操作菜单
void showMenu() {
    printf("请选择操作:\n");
    printf("1. 添加联系人\n");
    printf("2. 删除联系人\n");
    printf("3. 显示所有联系人\n");
    printf("4. 修改联系人信息\n");
    printf("5. 查找联系人\n");
    printf("6. 退出系统\n");
    printf("=========================================\n");
    printf("请输入选项(1-6): ");
}

// 创建联系人节点（优化：增加内存分配检查）
ContactNode* createNode(const char* name, const char* phone) {
    if (!name || !phone) return NULL;

    ContactNode* node = (ContactNode*)malloc(sizeof(ContactNode));
    if (!node) {
        perror("内存分配失败");
        return NULL;
    }

    strncpy(node->name, name, sizeof(node->name)-1);
    node->name[sizeof(node->name)-1] = '\0';  // 确保字符串结束符

    strncpy(node->phone, phone, sizeof(node->phone)-1);
    node->phone[sizeof(node->phone)-1] = '\0';

    node->next = NULL;
    return node;
}

// 添加联系人（优化：使用尾指针思想，减少遍历）
bool addContact(AddressList* list, const char* name, const char* phone) {
    if (!list || !name || !phone || !isPhoneValid(phone)) {
        printf("输入无效！姓名不能为空，电话号码必须为数字\n");
        return false;
    }

    ContactNode* node = createNode(name, phone);
    if (!node) return false;

    //static 关键字：让 tail 只初始化一次（第一次调用函数时），后续调用会保留上一次的指向（不会重置为 NULL）。
    //tail 作用：永久记住链表的「最后一个节点」，相当于给链表尾部做了个「书签」。
    //利用尾指针（tail） 来避免每次添加联系人时都从头遍历链表，从而提高性能。
    static ContactNode* tail = NULL;
    if (list->head == NULL) {
        list->head = node;
        tail = node;
    } else {
        // 让当前尾节点的next指向新节点
        tail->next = node; 
        // 尾指针前移，指向新的尾节点（刚添加的node） 
        tail = node;        
    }

    list->count++;
    return true;
}

// 显示所有联系人（优化：格式化输出，显示总数）
void displayAll(const AddressList* list) {
    if (!list) {
        printf("通讯录未初始化\n");
        return;
    }

    if (list->count == 0) {
        printf("通讯录为空，暂无联系人\n");
        return;
    }

    printf("\n===== 联系人列表（共%d人）=====\n", list->count);
    ContactNode* p = list->head;
    while (p) {
        printf("姓名: %-10s  电话: %s\n", p->name, p->phone);  // 左对齐，更整齐
        p = p->next;
    }
    printf("==============================\n\n");
}

// 删除联系人（优化：增加查找效率，完善提示）
bool deleteContact(AddressList* list, const char* name) {
    if (!list || !name || list->count == 0) {
        printf("操作失败：通讯录为空或输入无效\n");
        return false;
    }

    ContactNode* pre = NULL;
    ContactNode* curr = list->head;

    while (curr) {
        if (strcmp(curr->name, name) == 0) {
            // 调整指针
            if (pre == NULL) {
                list->head = curr->next;
            } else {
                // 前一个节点的next指向当前节点的下一个节点
                pre->next = curr->next;
            }

            free(curr);
            list->count--;
            printf("联系人 '%s' 删除成功\n", name);
            return true;
        }
        pre = curr;
        curr = curr->next;
    }

    printf("未找到联系人 '%s'\n", name);
    return false;
}

// 修改联系人（优化：修复嵌套循环bug，增加成功/失败提示）
//"嵌套循环 bug" 就是在不需要多重循环的场景中错误地使用了嵌套循环，
//导致代码效率降低或逻辑异常。
bool modifyContact(AddressList* list, const char* oldName, const char* newName, const char* newPhone) {
    if (!list || !oldName || !newName || !newPhone || list->count == 0) {
        printf("操作失败：输入无效或通讯录为空\n");
        return false;
    }

    if (!isPhoneValid(newPhone)) {
        printf("电话号码无效（必须为数字）\n");
        return false;
    }

    ContactNode* p = list->head;
    while (p) {
        if (strcmp(p->name, oldName) == 0) {
            // 复制姓名到结构体（name数组大小为50）
            strncpy(p->name, newName, sizeof(p->name)-1);
            p->name[sizeof(p->name)-1] = '\0';

            strncpy(p->phone, newPhone, sizeof(p->phone)-1);
            p->phone[sizeof(p->phone)-1] = '\0';

            printf("联系人 '%s' 修改成功\n", newName);
            return true;
        }
        p = p->next;
    }

    printf("未找到联系人 '%s'\n", oldName);
    return false;
}

// 查找联系人（优化：支持查找所有重名联系人）
void searchContact(const AddressList* list, const char* name) {
    if (!list || !name || list->count == 0) {
        printf("查找失败：输入无效或通讯录为空\n");
        return;
    }

    ContactNode* p = list->head;
    int found = 0;
    printf("\n===== 查找结果 ====\n");
    while (p) {
        if (strcmp(p->name, name) == 0) {
            printf("姓名: %s  电话: %s\n", p->name, p->phone);
            found++;
        }
        p = p->next;
    }

    if (found == 0) {
        printf("未找到联系人 '%s'\n", name);
    } else {
        printf("共找到 %d 个匹配结果\n", found);
    }
    printf("===================\n\n");
}

// 销毁链表（新增：释放所有动态内存）
void destroyList(AddressList* list) {
    if (!list) return;

    ContactNode* curr = list->head;
    while (curr) {
        ContactNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
    list->head = NULL;
    list->count = 0;
}

// 验证电话号码（新增：确保为数字）
bool isPhoneValid(const char* phone) {
    if (!phone || *phone == '\0') return false;
    for (int i = 0; phone[i]; i++) {
        if (!isdigit(phone[i])) return false;
    }
    return true;
}