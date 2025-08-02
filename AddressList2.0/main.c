#include"addresslist.h"

// 清空输入缓冲区（新增：解决输入残留问题）
void clearBuffer() {
    int c;
    //读取并丢弃输入缓冲区中残留的所有字符，
    //直到遇到换行符（\n）或文件结束符（EOF）为止
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    AddressList list = {NULL, 0};  // 初始化通讯录（计数为0）
    char name[50], oldName[50], newName[50];
    char phone[20], newPhone[20];
    int choice;
    char continueOp;

    showWelcome();
    sleep(1);

    while (1) {
        showMenu();
        if (scanf("%d", &choice) != 1) {  // 处理非数字输入
            printf("输入无效，请输入数字(1-6)\n");
            clearBuffer();
            continue;
        }
        clearBuffer();  // 清空缓冲区

        switch (choice) {
            case ADD:
                do {
                    printf("请输入联系人姓名: ");
                    //stdin 是一个标准输入流（standard input stream）的文件指针，
                    //定义在 <stdio.h> 头文件中，用于表示程序的标准输入设备，通常是键盘。
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';  // 去除换行符

                    printf("请输入联系人电话(数字): ");
                    //fgets 会将用户输入的所有字符（包括按下回车键产生的 \n）一起存入缓冲区
                    fgets(phone, sizeof(phone), stdin);
                    //找到 \n 在字符串中的位置（通过 strcspn 返回的长度）
                    //用字符串结束符 \0 替换该位置的 \n
                    //替换后，phone 变为 123456789\0，成功去除了换行符
                    phone[strcspn(phone, "\n")] = '\0';

                    if (addContact(&list, name, phone)) {
                        printf("添加成功！\n");
                    }

                    printf("是否继续添加? (y/n): ");
                    scanf("%c", &continueOp);
                    clearBuffer();
                } while (tolower(continueOp) == 'y');  // 用循环替代goto
                break;

            case DELETE:
                do {
                    printf("请输入要删除的联系人姓名: ");
                    fgets(name, sizeof(name), stdin);
                    //strcspn(name, "\n")：这个函数会计算 name 字符串中从开头到第一个 \n 出现前的字符个数。
                    //name[...]：通过上一步得到的位置，定位到字符串中 \n 所在的索引位置。
                    //... = '\0'：用字符串结束符 '\0' 替换该位置的 \n，相当于字符串被截断。替换后成功去除了换行符。
                    name[strcspn(name, "\n")] = '\0';

                    deleteContact(&list, name);

                    printf("是否继续删除? (y/n): ");
                    scanf("%c", &continueOp);
                    clearBuffer();
                    //tolower() 是一个字符处理函数，用于将大写字母转换为小写字母，
                    //定义在 <ctype.h> 头文件中。
                } while (tolower(continueOp) == 'y');
                break;

            case DISPLAY_ALL:
                displayAll(&list);
                printf("按任意键继续...");
                getchar();  // 暂停查看结果
                clearBuffer();
                break;

            case MODIFY:
                printf("请输入要修改的联系人姓名: ");
                fgets(oldName, sizeof(oldName), stdin);
                oldName[strcspn(oldName, "\n")] = '\0';

                printf("请输入新姓名: ");
                fgets(newName, sizeof(newName), stdin);
                newName[strcspn(newName, "\n")] = '\0';

                printf("请输入新电话(数字): ");
                fgets(newPhone, sizeof(newPhone), stdin);
                newPhone[strcspn(newPhone, "\n")] = '\0';

                modifyContact(&list, oldName, newName, newPhone);
                printf("按任意键继续...");
                getchar();
                clearBuffer();
                break;

            case SEARCH:
                do {
                    printf("请输入要查找的联系人姓名: ");
                    fgets(name, sizeof(name), stdin);
                    name[strcspn(name, "\n")] = '\0';

                    searchContact(&list, name);

                    printf("是否继续查找? (y/n): ");
                    scanf("%c", &continueOp);
                    clearBuffer();
                } while (tolower(continueOp) == 'y');
                break;

            case EXIT:
                destroyList(&list);  // 退出前释放内存
                printf("感谢使用，再见！\n");
                return 0;

            default:
                printf("无效选项，请输入1-6之间的数字\n");
        }
    }
}