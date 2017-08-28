//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

/**
**
* @name saveInfo
* @function save the information to file
* @param head the head of the list
* @return none
*/
void saveInfo(GradeInfo head) {
    FILE *fgrade = fopen(MYDATAPATH.gradeFile, "w+");
    FILE *fclass = fopen(MYDATAPATH.classFile, "w+");
    FILE *fstudent = fopen(MYDATAPATH.studentFile, "w+");
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        fprintf(fgrade, "%s %s %d %d %s %s %s %s\n", tail->CSNo, tail->Year, tail->InNo,
                tail->GraduateNo,
                tail->MentorName, tail->MentorNo, tail->ChairmanName, tail->ChairmanNo);
        ClassInfo tail1 = tail->Classes;
        while (tail1->next != NULL) {
            tail1 = tail1->next;
            fprintf(fclass, "%s %s %s %d %f %d %s %s %s %s\n", tail1->GradeNo, tail1->CNo,
                    tail1->Major,
                    tail1->InNo, tail1->AverageAge, tail1->GraduateNo, tail1->MonitorName,
                    tail1->MonitorNo,
                    tail1->MentorName, tail1->MentorNo);
            StudentInfo tail2 = tail1->Students;
            while (tail2->next != NULL) {
                tail2 = tail2->next;
                fprintf(fstudent, "%s %s %s %c %s %s %s %f %c %s\n", tail2->ClassNo, tail2->CNo,
                        tail2->Name,
                        tail2->sex, tail2->Birthplace, tail2->Birthday, tail2->Number,
                        tail2->InScore,
                        tail2->HasGraduated, tail2->GraduateTo);
            }
        }
    }
    fclose(fgrade);
    fclose(fclass);
    fclose(fstudent);
}

/*************************************************
 @name: backup_data
 @function: back up data into certain file
 @param head: the head of the province(first class) list
 @param filename: the file location and name
 @return none
 @details: The data file is picked up by file chooser
        using absolute location
*************************************************/
void backupInfo(GradeInfo head, char *filename) {
    FILE *p = fopen(filename, "w+");
    GradeInfo tail = head;
    while (tail->next != NULL)//第一级链表保存年级信息
    {
        tail = tail->next;
        fprintf(p, "%d %s %s %d %d %s %s %s %s\n", 1, tail->CSNo, tail->Year, tail->InNo,
                tail->GraduateNo,
                tail->MentorName, tail->MentorNo, tail->ChairmanName, tail->ChairmanNo);
        ClassInfo tail1 = tail->Classes;
        while (tail1->next != NULL)//第二级链表保存班级信息
        {
            tail1 = tail1->next;
            fprintf(p, "%d %s %s %s %d %f %d %s %s %s %s\n", 2, tail1->GradeNo, tail1->CNo,
                    tail1->Major,
                    tail1->InNo, tail1->AverageAge, tail1->GraduateNo, tail1->MonitorName,
                    tail1->MonitorNo,
                    tail1->MentorName, tail1->MentorNo);
            StudentInfo tail2 = tail1->Students;
            while (tail2->next != NULL)//第三级链表保存学生信息
            {
                tail2 = tail2->next;
                fprintf(p, "%d %s %s %s %c %s %s %s %f %c %s\n", 3, tail2->ClassNo, tail2->CNo,
                        tail2->Name,
                        tail2->sex, tail2->Birthplace, tail2->Birthday, tail2->Number,
                        tail2->InScore,
                        tail2->HasGraduated, tail2->GraduateTo);
            }
        }
    }
    fclose(p);
}