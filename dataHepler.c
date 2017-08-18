//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"
#include <time.h>

int getGradeNumber(GradeInfo head) {
    GradeInfo node = head;
    int count = 0;
    while ((node = node->next) != NULL)
        count++;
    return count;
}

int getClassNumber(GradeInfo head) {
    GradeInfo gradeNode = head;
    int count = 0;
    while ((gradeNode = gradeNode->next) != NULL) {
        ClassInfo classNode = gradeNode->Classes;
        while ((classNode = classNode->next) != NULL) {
            count++;
        }
    }
    return count;
}

int getStudentNumber(GradeInfo head) {
    GradeInfo gradeNode = head;
    int count = 0;
    while ((gradeNode = gradeNode->next) != NULL) {
        ClassInfo classNode = gradeNode->Classes;
        while ((classNode = classNode->next) != NULL) {
            StudentInfo studentNode = classNode->Students;
            while ((studentNode = studentNode->next) != NULL) {
                count++;
            }
        }
    }
    return count;
}

void free_all(GradeInfo head) {
    GradeInfo gradeNode = head;
    ClassInfo classNode;
    while (gradeNode != NULL) {
        classNode = gradeNode->Classes;
        while (classNode != NULL) {
            StudentInfo studentNode = classNode->Students;
            while (studentNode != NULL) {
                StudentInfo temp = studentNode->next;
                free(studentNode);
                studentNode = temp;
            }
            ClassInfo temp = classNode->next;
            free(classNode);
            classNode = temp;
        }
        GradeInfo temp = gradeNode->next;
        free(gradeNode);
        gradeNode = temp;
    }
}


/**
 * @name getAgeByBirthDay
 * @function get the student's age by his or her birthday
 * @param birthday: the student's birthday
 * @return the student's age
 */
int getAgeByBirthDay(char *birthday) {
    char year[4];
    int i = 0;
    for (i = 0; i < 4; i++) {
        year[i] = birthday[i];
    }
    int cuYear = atoi(year);
    int toYear = cuYear - 1900;
    struct tm *p;
    time_t timep;
    time(&timep);
    p = gmtime(&timep);
    return (p->tm_year - toYear);
}
