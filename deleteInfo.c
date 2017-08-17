//
// Created by victor on 8/17/17.
//

#include"head.h"

/**
 * @name deleteGradeInfo
 * @function delete the gradeInfo
 * @param head: the head of the list
 * @param str: the No of the grade
 * @return none
 * @details: the students' information and the classes' information of the grade will be lost
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
 * @function delete the classInfo
 * @param head: the head of the list
 * @param str: the No of the class
 * @return none
 * @details: the students' information of the class will be lost
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
 * @function delete the studentInfo
 * @param head: the head of the list
 * @param str: the No of the student
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