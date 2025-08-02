#ifndef _ADDRESSLIST_H_
#define _ADDRESSLIST_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>
#include<ctype.h>  // 新增：用于字符验证

// 联系人节点结构体
typedef struct ContactNode {
    char name[50];         // 联系人姓名
    char phone[20];        // 联系人电话号码（扩大容量，适应长号）
    struct ContactNode* next;  // 下一个节点指针
} ContactNode;

// 通讯录管理结构体（优化：增加节点计数）
typedef struct AddressList {
    ContactNode* head;     // 头节点指针
    int count;             // 联系人数量
} AddressList;

// 操作选项枚举（优化：增加注释说明）
enum OPTION {
    ADD = 1,       // 添加联系人
    DELETE,        // 删除联系人
    DISPLAY_ALL,   // 显示所有联系人
    MODIFY,        // 修改联系人信息
    SEARCH,        // 查找联系人
    EXIT           // 退出系统
};

// 函数声明（优化：增加const修饰常量参数）
void showWelcome();                          // 显示欢迎界面
void showMenu();                             // 显示操作菜单
ContactNode* createNode(const char* name, const char* phone);  // 创建联系人节点
bool addContact(AddressList* list, const char* name, const char* phone);  // 添加联系人
void displayAll(const AddressList* list);    // 显示所有联系人
bool deleteContact(AddressList* list, const char* name);  // 删除联系人
bool modifyContact(AddressList* list, const char* oldName, const char* newName, const char* newPhone);  // 修改联系人
void searchContact(const AddressList* list, const char* name);  // 查找联系人
void destroyList(AddressList* list);         // 销毁链表（新增：内存释放）
bool isPhoneValid(const char* phone);        // 验证电话号码（新增：合法性检查）

#endif