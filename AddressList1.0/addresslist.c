#include"addresslist.h"

// 显示欢迎界面
void Welcome()
{
    printf("\t\t\t\t     通讯录\n\n\n");
}

// 显示通讯录目录
void menu()
{
    printf("\t\t\t\t 1.创建用户信息   2.删除用户数据\n\n\n");
    printf("\t\t\t\t 3.显示用户信息   4.修改用户数据\n\n\n");
    printf("\t\t\t\t 5.查找用户信息   6.退出系统返回\n\n\n");
}

// 创建新联系人节点
linklist* LinklistCreate(char* name,char* phonenumber)
{
    linklist* temp =(linklist*)malloc(sizeof(linklist));  // 为新节点分配内存
    strcpy(temp->name,name);  // 复制姓名到新节点
    strcpy(temp->phonenumber,phonenumber);  // 复制电话号码到新节点
    temp->next=NULL;  // 新节点的下一个节点指针初始化为NULL
    return temp;  // 返回新创建的节点
}

// 添加联系人到通讯录(尾插法)
void ADD_list(headlist* list,char* name,char* phonenumber)
{
    linklist* temp =LinklistCreate(name,phonenumber);  // 创建新联系人节点
    if(list->head==NULL)  // 如果链表为空
    {
        list->head=temp;  // 新节点作为头节点
    }
    else  // 链表不为空
    {
        linklist* number=list->head;
        while(number->next!=NULL)  // 找到链表的最后一个节点
        {
            number=number->next;
        }
        number->next=temp;  // 将新节点添加到链表末尾
    }
}

// 显示所有用户（遍历）
void Print_list(headlist* list)
{
    linklist* p=list->head;  // 从链表头开始遍历
    if(p==NULL)  // 如果链表为空
    {
        printf("通讯录为空!\n");
    }
    else
    {
        while(p)  // 遍历链表
        {
            printf("通讯录中的联系人：");
            printf("用户姓名：%s  电话号码：%s\n",p->name,p->phonenumber);
            p=p->next;  // 移动到下一个节点
        }
    }
}

// 删除用户数据
void Delete_list(headlist* list, char* deletename)
{
    if (list == NULL || deletename == NULL)  // 增加参数合法性检查
    {
        printf("参数无效！\n");
        return;
    }
    
    if (list->head == NULL)  // 如果链表为空
    {
        printf("通讯录为空，无法删除！\n");
        return;
    }
    
    linklist* pre = NULL;    // 前驱节点指针
    linklist* p = list->head; // 当前节点指针
    int found = 0;           // 标记是否找到要删除的节点

    while (p != NULL)
    {
        if (strcmp(p->name, deletename) == 0)  // 找到要删除的节点
        {
            found = 1;
            // 调整链表指针
            if (pre == NULL)  // 要删除的是头节点
            {
                list->head = p->next;
            }
            else  // 要删除的是中间或尾节点
            {
                pre->next = p->next;
            }
            // 释放节点内存，避免内存泄漏
            free(p);
            printf("%s 删除成功！\n", deletename);
            break;  // 假设只删除第一个匹配的节点，如需删除所有匹配可去掉break
        }
        
        // 移动到下一个节点
        pre = p;
        p = p->next;
    }
    
    if (!found)  // 遍历完链表未找到目标节点
    {
        printf("未找到名为 %s 的用户，删除失败！\n", deletename);
    }
}

// 修改用户信息
void Change_list(headlist* list,char* name,char* changename,char* changephonenumber)
{
    if(list->head==NULL)  // 如果链表为空
    {
        printf("通讯录为空！\n");
    }
    linklist*p=list->head;
    int charge=1;
    while(p!=NULL&&charge==1)
    {
        if(p)
        {
            while(strcmp(p->name,name) == 0)  // 找到要修改的节点
            {
                strcpy(p->name,changename);  // 修改姓名
                strcpy(p->phonenumber,changephonenumber);  // 修改电话号码
                printf("用户名：%s 电话号码：%s 修改成功\n",p->name,p->phonenumber);
                charge=0;
                return;
            }
            p=p->next;  // 移动到下一个节点
        }
        else
        {
            printf("修改失败！\n");
        }
    }
}

// 查找用户信息
void Found_list(headlist*list,char* foundname)
{
    if(list->head==NULL)  // 如果链表为空
    {
        printf("通讯录为空！\n");
    }
    linklist*p=list->head;
    int charge=1;
    while(p!=NULL&&charge==1)
    {
        if(p)
        {
            while(strcmp(p->name,foundname) == 0)  // 找到要查找的节点
            {
                printf("用户名：%s 查找成功！电话号码：%s\n",p->name,p->phonenumber);
                charge=0;
                return;
            }
            p=p->next;  // 移动到下一个节点
        }
        else
        {
            printf("查找失败！\n");
        }
    }
}