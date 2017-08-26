//
// Created by victor on 8/25/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "../head.h"

/**
 * @name sortGradeInfoByTime
 * @function sort the GradeInfoByTime structure
 * @param head： the first node of the list to be sorted
 * @param way: the sorted way 0: sort by No,
 *              1: sort by addmitted population
 *              2: sort by the ungraduate students count
 *              3: sort by the class count
 *              4: sort by the graduate students count
 * @return the first node of the sorted list
 */
GradeInfoByTime sortGradeInfoByTime(GradeInfoByTime head, int way) {
    if (head->next == NULL) {
        return head;
    }
    GradeInfoByTime pStart = head;
    GradeInfoByTime result = pStart;
    while (result->next != NULL) {
        GradeInfoByTime minNode = result->next, p = result->next;
        GradeInfoByTime pre = result;
        while (NULL != p->next) {
            if ((way == 0 && atoi(p->next->CSNo) < atoi(minNode->CSNo)) ||
                (way == 1 && (p->next->InNo) < (minNode->InNo)) ||
                (way == 2 && (p->next->UnGraduatedCount < minNode->UnGraduatedCount)) ||
                (way == 3 && (p->next->ClassCount) < (minNode->ClassCount)) ||
                (way == 4 && p->next->GraduatedCount < minNode->GraduatedCount)) {
                pre = p;
                minNode = p->next;
            }
            p = p->next;
        }
        pre->next = result->next;
        GradeInfoByTime temp = minNode->next;
        minNode->next = result->next->next;
        result->next->next = temp;
        result->next = minNode;

        result = result->next;
    }
    return pStart;
}

/**
 * @name sortClassInfoByTime
 * @function sort the classInfoByTime structure
 * @param head： the first node of the list to be sorted
 * @param way: the sorted way 0: sort by the ungraduate students count
 * @return the first node of the sorted list
 */
ClassInfoByTime sortClassInfoByTime(ClassInfoByTime head, int way) {
    if (head->next == NULL) {
        return head;
    }
    ClassInfoByTime pStart = head;
    ClassInfoByTime result = pStart;
    while (result->next != NULL) {
        ClassInfoByTime minNode = result->next, p = result->next;
        ClassInfoByTime pre = result;
        while (NULL != p->next) {
            if ((way == 0 && p->next->UnGraduateCount < minNode->UnGraduateCount)) {
                pre = p;
                minNode = p->next;
            }
            p = p->next;
        }
        pre->next = result->next;
        ClassInfoByTime temp = minNode->next;
        minNode->next = result->next->next;
        result->next->next = temp;
        result->next = minNode;

        result = result->next;
    }
    return pStart;
}

/**
 * @name sortStudentInfoByTime
 * @function sort the studentInfoByTime structure
 * @param head： the first node of the list to be sorted
 * @param way: the sorted way 0: sort by the  students count
 * @return the first node of the sorted list
 */
StudentInfoByTime sortStudentInfoByTime(StudentInfoByTime head, int way) {
    if (head->next == NULL) {
        return head;
    }
    StudentInfoByTime pStart = head;
    StudentInfoByTime result = pStart;
    while (result->next != NULL) {
        StudentInfoByTime minNode = result->next, p = result->next;
        StudentInfoByTime pre = result;
        while (NULL != p->next) {
            if ((way == 0 && p->next->Count < minNode->Count)) {
                pre = p;
                minNode = p->next;
            }
            p = p->next;
        }
        pre->next = result->next;
        StudentInfoByTime temp = minNode->next;
        minNode->next = result->next->next;
        result->next->next = temp;
        result->next = minNode;

        result = result->next;
    }
    return pStart;
}

/**
 * @name sortStudentInfoByYear
 * @function sort the studentInfoByYear structure
 * @param head： the first node of the list to be sorted
 * @return the first node of the sorted list
 */
StudentInfoByYear sortStudentInfoByYear(StudentInfoByYear head) {
    if (head->next == NULL) {
        return head;
    }
    StudentInfoByYear pStart = head;
    StudentInfoByYear result = pStart;
    while (result->next != NULL) {
        StudentInfoByYear minNode = result->next, p = result->next;
        StudentInfoByYear pre = result;
        while (NULL != p->next) {
            if ((atoi(p->next->Year) < atoi(minNode->Year))) {
                pre = p;
                minNode = p->next;
            }
            p = p->next;
        }
        pre->next = result->next;
        StudentInfoByYear temp = minNode->next;
        minNode->next = result->next->next;
        result->next->next = temp;
        result->next = minNode;

        result = result->next;
    }
    return pStart;
}