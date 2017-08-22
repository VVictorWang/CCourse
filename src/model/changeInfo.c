//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

/**
 * @name changeGradeInfo
 * @function change the gradeInfo into the list.
 * @param head the head of the list
 * @param match the No of the grade to be modified
 * @param str the new information
 * @return flag 1 indicates that user has modified the No of the Grade,while 0 indicates the opposite
 * @details: if modified the grade No, the students' information and the classes' information of the grade will be lost
 */
int changeGradeInfo(GradeInfo head, char *match, const char **str) {
    GradeInfo tail = head;
    int flag = 0;//标志是否修改了年级编号
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(tail->CSNo, match)) {
            if (strcmp(str[0], tail->CSNo)) {
                strcpy(tail->CSNo, str[0]);
                tail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
                tail->Classes->next = NULL;
                flag = 1;
            }
            gradeInfoIn(&tail, str);
        }
    }
    return flag;
}

/**
 * @name changeClassInfo
 * @function change the classInfo into the list.
 * @param head: the head of the list
 * @param match: the No of the class to be modified
 * @param str: the new information
 * @return flag 1 indicates that user has modified the No of the Class,while 0 indicates the opposite
 * @details: if modified the class No, the students' information of the class will be lost
 */
int changeClassInfo(GradeInfo head, char *match, const char **str) {
    GradeInfo tail = head;
    int flag = 0;//标志是否修改了班级编号
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo tail1 = tail->Classes;
        while (tail1->next != NULL) {
            ClassInfo tail1old = tail1;
            tail1 = tail1->next;
            if (!strcmp(tail1->CNo, match)) {
                strcpy(tail1->GradeNo, str[0]);
                GradeInfo tailnew = head;//要把改变了年级的班级信息挂到改后的年级下面
                while (tailnew->next != NULL) {
                    tailnew = tailnew->next;
                    if (!strcmp(tailnew->CSNo, tail1->GradeNo)) {
                        ClassInfo tail1new = tailnew->Classes;
                        while (tail1new->next != NULL)
                            tail1new = tail1new->next;
                        tail1new->next = tail1;//原结点挂在新年级的班级链下面
                        tail1old->next = tail1->next;//原结点的前一个节点指向原结点下一个节点
                        tail1->next = NULL;//原结点为新年级下班级链的末端，next置为NULL
                        break;
                    }
                }
                //若传入信息不为空，加载到链表中
                if (strcmp(str[1], tail1->CNo)) {
                    flag = 1;
                    strcpy(tail1->CNo, str[1]);
                    tail1->Students = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    tail1->Students->next = NULL;
                }
                classInfoIn(&tail1, str);
                return flag;
            }
        }
    }
    return flag;
}

/**
 * @name changeStudentInfo
 * @function change the studentInfo into the list.
 * @param head the head of the list
 * @param match the No of the student to be modified
 * @param str the new information
 * @return flag 1 indicates that user has modified the No of the Student,while 0 indicates the opposite
 */
void changeStudentInfo(GradeInfo head, char *match, const char **str) {
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
                if (!strcmp(tail2->CNo, match)) {
                    if (strcmp(str[0], tail2->ClassNo)) {
                        strcpy(tail2->ClassNo, str[0]);
                        GradeInfo tailnew = head;
                        int flag = 0;
                        while (tailnew->next != NULL) {
                            tailnew = tailnew->next;
                            ClassInfo tail1new = tailnew->Classes;
                            while (tail1new->next != NULL) {
                                tail1new = tail1new->next;
                                if (!strcmp(tail1new->CNo, tail2->ClassNo)) {
                                    flag = 1;
                                    StudentInfo tail2new = tail1new->Students;
                                    while (tail2new->next != NULL)
                                        tail2new = tail2new->next;
                                    tail2new->next = tail2;
                                    tail2old->next = tail2->next;
                                    tail2->next = NULL;
                                    break;
                                }
                            }
                            if (flag)break;
                        }
                    }
                    studentInfoIn(&tail2, str);
                }
            }
        }
    }
}

