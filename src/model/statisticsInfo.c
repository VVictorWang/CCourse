//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "../head.h"

/*************************************************
 @name: countGradeInfoByTime
 @function: get the statistical data of the gradeInfo by time.
 @param start: the start time
 @param end: the end time
 @return none
*************************************************/
GradeInfoByTime countGradeInfoByTime(char *start, char *end) {
    GradeInfoByTime p = (GradeInfoByTime) malloc(sizeof(GRADEInfobyTime));
    p->next = NULL;
    GradeInfoByTime result = p;
    long startTime = atol(start);
    long endTime = atol(end);
    GradeInfo gradeNode = head;
    while ((gradeNode = gradeNode->next) != NULL) {
        long year = atol(gradeNode->Year);
        if (year >= startTime && year <= endTime) {
            p->next = (GradeInfoByTime) malloc(sizeof(GRADEInfobyTime));
            p = p->next;
            strcpy(p->Year, gradeNode->Year);
            strcpy(p->CSNo, gradeNode->CSNo);
            p->ClassCount = getClassNumber(gradeNode);
            p->InNo = gradeNode->InNo;
            p->GraduatedCount = gradeNode->GraduateNo;
            p->UnGraduatedCount = gradeNode->InNo - gradeNode->GraduateNo;
            p->next = NULL;
        }
    }
    return result;

}

/*************************************************
 @name: countClassInfoByTime
 @function: get the statistical data of the classInfo by time.
 @param start: the start time
 @param end: the end time
 @return none
*************************************************/
ClassInfoByTime countClassInfoByTime(char *start, char *end) {
    ClassInfoByTime p = (ClassInfoByTime) malloc(sizeof(CLASSInfobyTime));
    p->next = NULL;
    ClassInfoByTime result = p;
    long startTime = atol(start);
    long endTime = atol(end);
    GradeInfo gradeNode = head;
    while ((gradeNode = gradeNode->next) != NULL) {
        ClassInfo classNode = gradeNode->Classes;
        while ((classNode = classNode->next) != NULL) {
            long year = atol(gradeNode->Year);
            if (year >= startTime && year <= endTime) {
                p->next = (ClassInfoByTime) malloc(sizeof(CLASSInfobyTime));
                p = p->next;
                strcpy(p->Year, gradeNode->Year);
                strcpy(p->CNo, classNode->CNo);
                p->UnGraduateCount = classNode->InNo - classNode->GraduateNo;
                p->next = NULL;
            }
        }

    }
    return result;

}

/*************************************************
 @name: countStudentInfoByTime
 @function: get the statistical data of the studentInfo by time.
 @param start: the start time
 @param end: the end time
 @return none
*************************************************/
StudentInfoByTime countStudentInfoByTime(char *start, char *end) {
    StudentInfoByTime p = (StudentInfoByTime) malloc(sizeof(STUDENTinfobyTime));
    p->next = NULL;
    StudentInfoByTime result = p;
    int startTime = atoi(start);
    int endTime = atoi(end);
    int flag = 0;
    GradeInfo gradeNode = head;
    while ((gradeNode = gradeNode->next) != NULL) {
        ClassInfo classNode = gradeNode->Classes;
        while ((classNode = classNode->next) != NULL) {
            StudentInfo studentNode = classNode->Students;
            while ((studentNode = studentNode->next) != NULL) {
                int year = atoi(gradeNode->CSNo) + 4;
                if (year >= startTime && year <= endTime) {
                    StudentInfoByTime temp = result;
                    while ((temp = temp->next) != NULL) {
                        if (year == atoi(p->Year)) {
                            flag = 1;
                            p->Count++;
                            break;
                        }
                    }
                    if (!flag) {
                        p->next = (StudentInfoByTime) malloc(sizeof(STUDENTinfobyTime));
                        p = p->next;
                        strcpy(p->GraduateTo, studentNode->GraduateTo);
                        strcpy(p->Year, intToStr(year));
                        p->Count = 1;
                        p->next = NULL;
                    }
                    flag = 0;
                }
            }
        }
    }
    return result;
}

/*************************************************
 @name: countStudentInfoByYear
 @function: get the statistical data of the studentInfo by year.
 @param start: the start time
 @param end: the end time
 @return none
*************************************************/
StudentInfoByYear countStudentInfoByYear(char *start, char *end) {
    StudentInfoByYear p = (StudentInfoByYear) malloc(sizeof(STUDENTinfobyYear));
    p->next = NULL;
    StudentInfoByYear result = p;
    GradeInfo gradeNode = head;
    int startTime = atoi(start);
    int endTime = atoi(end);
    int flag = 0;
    while ((gradeNode = gradeNode->next) != NULL) {
        ClassInfo classNode = gradeNode->Classes;
        while ((classNode = classNode->next) != NULL) {
            StudentInfo studentNode = classNode->Students;
            while ((studentNode = studentNode->next) != NULL) {
                int year = atoi(strsub(studentNode->Birthday, 0, 4));
                if (year >= startTime && year <= endTime) {
                    StudentInfoByYear temp = result;
                    while ((temp = temp->next) != NULL) {
                        if (year == atoi(temp->Year)) {
                            temp->Count++;
                            flag = 1;
                            break;
                        }
                    }
                    if (!flag) {
                        p->next = (StudentInfoByYear) malloc(sizeof(STUDENTinfobyYear));
                        p = p->next;
                        strcpy(p->Year, strsub(studentNode->Birthday, 0, 4));
                        p->Count = 1;
                        p->next = NULL;
                    }
                    flag = 0;
                }
            }

        }

    }
    return result;
}