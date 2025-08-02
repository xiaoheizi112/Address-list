#ifndef _ADDRESSLIST_H_
#define _ADDRESSLIST_H_
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<unistd.h>

// 定义链表节点结构体，用于存储联系人信息
typedef struct linklist
{
    char name[50];  // 联系人姓名
    char phonenumber[20];  // 联系人电话号码
    struct linklist* next;  // 指向下一个节点的指针
}linklist;

// 定义头节点结构体，用于管理链表
typedef struct headlist
{
    linklist* head;  // 指向链表的头节点
}headlist;

// 定义枚举类型，用于表示用户的操作选择
enum CHOICE
{
    ADD = 1,  // 添加联系人
    DEL,  // 删除联系人
    PRI,  // 显示所有联系人
    XIU,  // 修改联系人信息
    CHA,  // 查找联系人
    QUIT  // 退出系统
};

// 以下是各个功能函数的声明
// 欢迎界面函数
void Welcome();
// 通讯录目录函数
void menu();
// 创建新联系人节点函数
linklist* LinklistCreate(char* name,char* phonenumber);
// 添加联系人到通讯录函数
void ADD_list(headlist* list,char* name,char* phonenumber);
// 显示所有用户（遍历）函数
void Print_list(headlist* list);
// 删除用户数据函数
void Delete_list(headlist*list,char* deletename);
// 修改用户信息函数
void Change_list(headlist* list,char* name,char* changename,char* changephonenumber);
// 查找用户信息函数
void Found_list(headlist*list,char* foundname);
#endif