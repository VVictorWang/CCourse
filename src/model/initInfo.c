//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include"../head.h"

/**
 * @name initInfo
 * @function init the infomation from existing files
 * @param none
 * @return the status of the process
 */
int initInfo(GradeInfo *phead) {
    char space;  //读取文件信息时用于匹配空格
    FILE *sp = fopen(MYDATAPATH.gradeFile, "r");
    if (sp == NULL) {
        *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
        (*phead)->next = NULL;
        return -1;
    }
    *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
    GradeInfo tail = *phead;
    char temp[20];
    while (fscanf(sp, "%s", temp) != EOF) {
        tail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
        tail = tail->next;
        strcpy(tail->CSNo, temp);
        fscanf(sp, "%s%d%d%s%s%s%s", tail->Year, &(tail->InNo), &(tail->GraduateNo),
               tail->MentorName, tail->MentorNo,
               tail->ChairmanName, tail->ChairmanNo);
        tail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
        tail->Classes->next = NULL;
    }
    tail->next = NULL;
    fclose(sp);
    sp = fopen(MYDATAPATH.classFile, "r");
    if (sp == NULL)
        return -2;

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
                fscanf(sp, "%s%s%d%f%d%s%s%s%s", mytail->CNo, mytail->Major, &(mytail->InNo),
                       &(mytail->AverageAge),
                       &(mytail->GraduateNo), mytail->MonitorName, mytail->MonitorNo,
                       mytail->MentorName,
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
    sp = fopen(MYDATAPATH.studentFile, "r");
    if (sp == NULL)
        return -4; //学生信息文件打开失败

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
                    StudentInfo studenttail = classtail->Students;
                    while (studenttail->next != NULL) {
                        studenttail = studenttail->next;
                    }
                    studenttail->next = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    studenttail = studenttail->next;
                    strcpy(studenttail->ClassNo, temp);
                    fscanf(sp, "%s%s%c%c%s%s%s%f%c%c%s", studenttail->CNo, studenttail->Name,
                           &space,
                           &(studenttail->sex),
                           studenttail->Birthplace, studenttail->Birthday, studenttail->Number,
                           &(studenttail->InScore),
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

/*************************************************
 @name: restore_data
 @function: restore data from certain file
 @param phead: the head of the province(first class) list
 @param filename: the file location and name
 @return: none
 @details: The data file is picked up by file chooser using absolute location
*************************************************/
int restoreInfo(GradeInfo *phead, char *filename) {
    int flag = 0;
    FILE *pf = fopen(filename, "r");
    if (!pf) {
        *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
        return -1; //文件打开失败
    }
    GradeInfo head = (GradeInfo) malloc(sizeof(GRADEInfo));
    GradeInfo tail = head;
    tail->next = NULL;
    int num;
    char temp[50];
    while (fscanf(pf, "%d", &num) != EOF) {
        if (num == 1) {
            tail = head;
            while (tail->next != NULL)
                tail = tail->next;
            tail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
            tail = tail->next;
            fscanf(pf, "%s%s%d%d%s%s%s%s", tail->CSNo, tail->Year, &(tail->InNo),
                   &(tail->GraduateNo),
                   tail->MentorName, tail->MentorNo, tail->ChairmanName, tail->ChairmanNo);
            tail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
            tail->Classes->next = NULL;
            tail->next = NULL;
        } else if (num == 2) {
            flag = 0;
            tail = head;
            fscanf(pf, "%s", temp);
            while (tail->next != NULL) {
                tail = tail->next;
                if (!strcmp(temp, tail->CSNo)) {
                    flag = 1;
                    ClassInfo tail1 = tail->Classes;
                    while (tail1->next != NULL)
                        tail1 = tail1->next;
                    tail1->next = (ClassInfo) malloc(sizeof(CLASSInfo));
                    tail1 = tail1->next;
                    strcpy(tail1->GradeNo, temp);
                    fscanf(pf, "%s%s%s%d%f%d%s%s%s%s", tail1->GradeNo, tail1->CNo, tail1->Major,
                           &(tail1->InNo), &(tail1->AverageAge), &(tail1->GraduateNo),
                           tail1->MonitorName,
                           tail1->MonitorNo,
                           tail1->MentorName, tail1->MentorNo);
                    tail1->Students = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    tail1->Students->next = NULL;
                    tail1->next = NULL;
                    break;
                }
            }
            if (!flag) {
                *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
                return -2; //备份文件有误！
            }
        } else if (num == 3) {
            flag = 0;
            tail = head;
            ClassInfo tail1 = NULL;
            fscanf(pf, "%s", temp);
            while (tail->next != NULL) {
                tail = tail->next;
                tail1 = tail->Classes;
                while (tail1->next != NULL) {
                    tail1 = tail1->next;
                    if (!strcmp(tail1->CNo, temp)) {
                        flag = 1;
                        StudentInfo tail2 = tail1->Students;
                        while (tail2->next != NULL)
                            tail2 = tail2->next;
                        tail2->next = (StudentInfo) malloc(sizeof(STUDENTInfo));
                        tail2 = tail2->next;
                        strcpy(tail2->ClassNo, temp);
                        fscanf(pf, "%s%s%s%c%s%s%s%f%c%s", tail2->ClassNo, tail2->CNo, tail2->Name,
                               &(tail2->sex), tail2->Birthplace, tail2->Birthday, tail2->Number,
                               &(tail2->InScore),
                               &(tail2->HasGraduated), tail2->GraduateTo);
                        tail2->next = NULL;
                        tail = head;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (!flag) {
                *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
                free(head);
                free(tail);
                return -2; //备份文件有误
            }
        }
    }
    fclose(pf);
    *phead = head;
    saveInfo(head);
    return 1; //恢复成功
}