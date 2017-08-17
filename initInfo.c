//
// Created by victor on 8/17/17.
//
#include"head.h"

/**
 * @name initInfo
 * @function 初始化链表信息.
 * @param none
 * @return phead 新建的链表头结点指针
 */
int initInfo(GradeInfo * phead) {
    char space;  //读取文件信息时用于匹配空格
    FILE *sp = fopen("GradeInfo.txt", "r");
    if (!sp) {
        *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
        (*phead)->next = NULL;
        return -1;
    }
    *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
    GradeInfo tail = *phead;
    char temp[10];
    while (fscanf(sp, "%s", temp) != EOF) {
        tail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
        tail = tail->next;
        strcpy(tail->CSNo, temp);
        fscanf(sp, "%s%d%d%s%s%s%s", tail->Year, &(tail->InNo), &(tail->GraduateNo), tail->MentorName, tail->MentorNo,
               tail->ChairmanName, tail->ChairmanNo);
        tail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
        tail->Classes->next = NULL;
    }
    tail->next = NULL;
    fclose(sp);

    sp = fopen("ClassInfo.txt", "r");
    if (!sp) {
        fclose(sp);
        return -2;
    }
    tail = *phead;
    ClassInfo classtail = NULL;
    int flag = 0;
    while (fscanf(sp, "%s", temp) != EOF) {
        flag = 0;
        while (tail->next != NULL) {
            tail = tail->next;
            if (!strcmp(temp, tail->CSNo)) {
                flag = 1;
                ClassInfo mytail = tail->Classes;
                while (mytail->next != NULL) {
                    mytail = mytail->next;
                }
                mytail->next = (ClassInfo) malloc(sizeof(CLASSInfo));
                mytail = mytail->next;
                strcpy(mytail->GradeNo, temp);
                fscanf(sp, "%s%s%d%f%d%s%s%s%s", mytail->CNo, mytail->FullName, &(mytail->InNo), &(mytail->AverageAge),
                       &(mytail->GraduateNo), mytail->MonitorName, mytail->MonitorNo, mytail->MentorName,
                       mytail->MentorNo);
                mytail->Students = (StudentInfo) malloc(sizeof(STUDENTInfo));
                mytail->Students->next = NULL;
                mytail->next = NULL;
                tail = *phead;
                break;
            }
        }
        if (!flag) {
            fclose(sp);
            return -3;
        }
    }
    fclose(sp);
    sp = fopen("StudentInfo.txt", "r");
    if (!sp) {
        fclose(sp);
        return -4; //学生信息文件打开失败
    }

    tail = *phead;
    while (fscanf(sp, "%s", temp) != EOF) {
        flag = 0;
        while (tail->next != NULL) {
            tail = tail->next;
            classtail = tail->Classes;
            while (classtail->next != NULL) {
                classtail = classtail->next;
                if (!strcmp(classtail->CNo, temp)) {
                    flag = 1;
                    StudentInfo studenttail = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    while (studenttail->next != NULL) {
                        studenttail = studenttail->next;
                    }
                    studenttail->next = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    studenttail = studenttail->next;
                    strcpy(studenttail->ClassNo, temp);
                    fscanf(sp, "%s%s%c%c%s%s%s%f%c%c%s", studenttail->CNo, studenttail->Name, &space,
                           &(studenttail->sex),
                           studenttail->Birthplace, studenttail->Birthday, studenttail->Number, &(studenttail->InScore),
                           &space,
                           &(studenttail->HasGraduated), studenttail->GraduateTo);
                    studenttail->next = NULL;
                    tail = *phead;
                    break;
                }
            }
            if (flag)
                break;
        }
        if (!flag) {
            fclose(sp);
            return -5; //学生信息有误
        }
    }
    fclose(sp);
    return 1;
}
