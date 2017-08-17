//
// Created by victor on 8/17/17.
//

#include"head.h"

/**
 * @name deleteGradeInfo
 * @function 删除年级信息.
 * @param head 链表头结点指针
 * @param str 用户输入的年级编号
 * @return none
 * 调用说明: 原年级下的班级及学生信息将丢失
 */
void deleteGradeInfo(GradeInfo head, char *str) {
    GradeInfo tail = head;
    GradeInfo tailold = head;
    while (tail->next != NULL) {
        tailold = tail;
        tail = tail->next;
        if (!strcmp(tail->CSNo, str)) {
            tailold->next = tail->next;
            tail->next = NULL;
            break;
        }
    }
}

/**
 * @name deleteClassInfo
 * @function 删除班级信息.
 * @param head 链表头结点指针
 * @param str 用户输入的班级编号
 * @return none
 * 调用说明: 原省份下的学生信息将丢失
 */
void deleteClassInfo(GradeInfo head, char *str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo tail1 = tail->Classes;
        ClassInfo tail1old = tail1;
        while (tail1->next != NULL) {
            tail1old = tail1;
            tail1 = tail1->next;
            if (!strcmp(tail1->CNo, str)) {
                tail1old->next = tail1->next;
                tail1->next = NULL;
                return;
            }
        }
    }
}

/**
 * @name deleteStudentInfo
 * @function 删除学生信息.
 * @param head 链表头结点指针
 * @param str 用户输入的报道编号
 * @return none
 */
void deleteStudentInfo(GradeInfo head, char *str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo tail1 = tail->Classes;
        while (tail1->next != NULL) {
            tail1 = tail1->next;
            StudentInfo tail2 = tail1->Students;
            StudentInfo tail2old = tail2;
            while (tail2->next != NULL) {
                tail2old = tail2;
                tail2 = tail2->next;
                if (!strcmp(tail2->CNo, str)) {
                    tail2old->next = tail2->next;
                    tail2->next = NULL;
                    return;
                }
            }
        }
    }
}