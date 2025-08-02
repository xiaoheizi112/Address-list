#include"addresslist.h"
int main(int argc, char const *argv[])
{
    headlist list;  // 定义头节点结构体变量
    list.head=NULL;  // 初始化头节点指针为NULL
    char name[50];  // 用于存储用户输入的姓名
    char deletename[50];  // 用于存储用户输入的要删除的姓名
    char changename[50];  // 用于存储用户输入的新姓名
    char phonenumber[12];  // 用于存储用户输入的电话号码
    char foundname[50];  // 用于存储用户输入的要查找的姓名
    char changephonenumber[12];  // 用于存储用户输入的新电话号码
    char judge='Y';  // 用于判断用户是否继续执行操作
    Welcome();  // 显示欢迎界面
    sleep(1);  // 暂停1秒
    int choice;
    while(1)
    {
        //system("clear");
Menu:
        menu();  // 显示通讯录目录
        printf("请输入选项\n");
        scanf("%d",&choice);  // 读取用户输入的选项
        switch(choice)
        {
        case ADD:  // 添加联系人
again:        
            printf("请输入用户昵称：\n");
            scanf("%s",name);
            printf("请输入用户电话号码：\n");
            scanf("%s",phonenumber);
            ADD_list(&list,name,phonenumber);  // 调用添加联系人函数
            printf("是否继续执行？Y/N\n");
            getchar();
            judge=getchar();
            if(judge=='Y'|| judge=='y')
            {
                goto again;  // 如果用户选择继续，跳转到again标签处
            }
            break;
        case DEL:  // 删除联系人
again1:
            printf("请输入想要删除的用户昵称：\n");
            scanf("%s",deletename);
            Delete_list(&list,deletename);  // 调用删除联系人函数
            printf("是否继续执行？Y/N\n");
            getchar();
            judge=getchar();
            if(judge=='Y'|| judge=='y')
            {
                goto again1;  // 如果用户选择继续，跳转到again1标签处
            }
            break;
        case PRI:  // 显示所有联系人
            Print_list(&list);  // 调用显示所有联系人函数
            break;
        case XIU:  // 修改联系人信息
            printf("请输入想要修改的用户昵称：\n");
            scanf("%s",name);
            printf("请输入新的用户昵称：\n");
            scanf("%s",changename);
            printf("请输入新的用户电话号码：\n");
            scanf("%s",changephonenumber);
            Change_list(&list,name,changename,changephonenumber);  // 调用修改联系人信息函数
            break;
        case CHA:  // 查找联系人
again2:
            printf("请输入想要查询的用户昵称：\n");
            scanf("%s",foundname);
            Found_list(&list,foundname);  // 调用查找联系人函数
            printf("是否继续执行？Y/N\n");
            getchar();
            judge=getchar();
            if(judge=='Y'|| judge=='y')
            {
                goto again2;  // 如果用户选择继续，跳转到again2标签处
            }
            break;
        case QUIT:  // 退出系统
            exit(0);  // 退出程序
            break;
        }
    }
    return 0;
}