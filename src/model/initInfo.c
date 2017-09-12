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
    char temp[16];
    while (fscanf(sp, "%15s", temp) != EOF) {
        tail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
        tail = tail->next;
        strcpy(tail->CSNo, temp);
        fscanf(sp, "%10s%d%d%16s%12s%16s%12s", tail->Year, &(tail->InNo), &(tail->GraduateNo),
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
    while (fscanf(sp, "%15s", temp) != EOF) {
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
                fscanf(sp, "%8s%30s%d%f%d%16s%12s%16s%12s", mytail->CNo, mytail->Major,
                       &(mytail->InNo),
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
    while (fscanf(sp, "%15s", temp) != EOF) {
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
                    fscanf(sp, "%12s%16s%c%c%16s%10s%12s%f%c%c%20s", studenttail->CNo,
                           studenttail->Name,
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
    GradeInfo gradeTail = head;
    gradeTail->next = NULL;
    int num;
    char temp[21];
    while (fscanf(pf, "%d", &num) != EOF) {
        if (num == 1) {
            gradeTail = head;
            while (gradeTail->next != NULL)
                gradeTail = gradeTail->next;
            gradeTail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
            gradeTail = gradeTail->next;
            fscanf(pf, "%6s%10s%d%d%16s%12s%16s%12s", gradeTail->CSNo, gradeTail->Year, &(gradeTail->InNo),
                   &(gradeTail->GraduateNo),
                   gradeTail->MentorName, gradeTail->MentorNo, gradeTail->ChairmanName, gradeTail->ChairmanNo);
            gradeTail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
            gradeTail->Classes->next = NULL;
            gradeTail->next = NULL;
        } else if (num == 2) {
            flag = 0;
            gradeTail = head;
            fscanf(pf, "%20s", temp);
            while (gradeTail->next != NULL) {
                gradeTail = gradeTail->next;
                if (!strcmp(temp, gradeTail->CSNo)) {
                    flag = 1;
                    ClassInfo classTail = gradeTail->Classes;
                    while (classTail->next != NULL)
                        classTail = classTail->next;
                    classTail->next = (ClassInfo) malloc(sizeof(CLASSInfo));
                    classTail = classTail->next;
                    strcpy(classTail->GradeNo, temp);
                    fscanf(pf, "%8s%30s%d%f%d%16s%12s%16s%12s", classTail->CNo,
                           classTail->Major,
                           &(classTail->InNo), &(classTail->AverageAge), &(classTail->GraduateNo),
                           classTail->MonitorName,
                           classTail->MonitorNo,
                           classTail->MentorName, classTail->MentorNo);
                    classTail->Students = (StudentInfo) malloc(sizeof(STUDENTInfo));
                    classTail->Students->next = NULL;
                    classTail->next = NULL;
                    break;
                }
            }
            if (!flag) {
                *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
                fclose(pf);
                return -2; //备份文件有误！
            }
        } else if (num == 3) {
            flag = 0;
            gradeTail = head;
            ClassInfo classTail = NULL;
            fscanf(pf, "%20s", temp);
            while (gradeTail->next != NULL) {
                gradeTail = gradeTail->next;
                classTail = gradeTail->Classes;
                while (classTail->next != NULL) {
                    classTail = classTail->next;
                    if (!strcmp(classTail->CNo, temp)) {
                        flag = 1;
                        StudentInfo studentTail = classTail->Students;
                        while (studentTail->next != NULL)
                            studentTail = studentTail->next;
                        studentTail->next = (StudentInfo) malloc(sizeof(STUDENTInfo));
                        studentTail = studentTail->next;
                        strcpy(studentTail->ClassNo, temp);
                        char space;
                        fscanf(pf, "%12s%16s%c%c%16s%10s%12s%f%c%c%20s", studentTail->CNo,
                               studentTail->Name,&space,
                               &(studentTail->sex), studentTail->Birthplace, studentTail->Birthday, studentTail->Number,
                               &(studentTail->InScore),&space,
                               &(studentTail->HasGraduated), studentTail->GraduateTo);
                        studentTail->next = NULL;
                        gradeTail = head;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            if (!flag) {
                *phead = (GradeInfo) malloc(sizeof(GRADEInfo));
                fclose(pf);
                return -2; //备份文件有误
            }
        }
    }
    fclose(pf);
    *phead = head;
    saveInfo(head);
    return 1; //恢复成功
}