//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

/**
 * @name: testGradeInfo
 * @function: test whether the grade information to be inserted already existed
 * @param str:  the No of the grade to be tested
 * @return flag: 1 indicates the grade has already existed, 0 indicates the opposite
 */

int testGradeInfo(const char *str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(str, tail->CSNo)) {
            return 1;
        }
    }
    return 0;
}

/**
 * @name: testClassInfo
 * @function: test whether the class information to be inserted already existed
 * @param str:  the No of the class to be tested
 * @return flag: 1 indicates the class has already existed, 0 indicates the opposite
 */
int testClassInfo(const char *str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classNode = tail->Classes;
        while ((classNode = classNode->next) != NULL) {
            if (!strcmp(str, classNode->CNo)) {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * @name: testStudentInfo
 * @function: test whether the student information to be inserted already existed
 * @param str:  the No of the student to be tested
 * @return flag: 1 indicates the student has already existed, 0 indicates the opposite
 */
int testStudentInfo(const char *str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classNode = tail->Classes;
        while ((classNode = classNode->next) != NULL) {
            StudentInfo studentNode = classNode->Students;
            while ((studentNode = studentNode->next) != NULL) {
                if (!strcmp(str, studentNode->CNo)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}