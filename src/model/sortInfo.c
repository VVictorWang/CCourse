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
        GradeInfoByTime minNode = result->next, p = result->next->next;
        while (NULL != p) {
            if ((way == 0 && atoi(p->CSNo) < atoi(minNode->CSNo)) ||
                (way == 1 && (p->InNo) < (minNode->InNo)) ||
                (way == 2 && (p->UnGraduatedCount < minNode->UnGraduatedCount)) ||
                (way == 3 && (p->ClassCount) < (minNode->ClassCount)) ||
                (way == 4 && p->GraduatedCount < minNode->GraduatedCount)) {
                minNode = p;
            }
            p = p->next;
        }
        swapStr(minNode->Year, result->next->Year);
        swapStr(minNode->CSNo, result->next->CSNo);
        SWPAINT(minNode->InNo, result->next->InNo);
        SWPAINT(minNode->ClassCount, result->next->ClassCount);
        SWPAINT(minNode->GraduatedCount, result->next->GraduatedCount);
        SWPAINT(minNode->UnGraduatedCount, result->next->UnGraduatedCount);
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
        ClassInfoByTime minNode = result->next, p = result->next->next;
        while (NULL != p) {
            if ((way == 0 && p->UnGraduateCount < minNode->UnGraduateCount)) {
                minNode = p;
            }
            p = p->next;
        }
        swapStr(minNode->Year, result->next->Year);
        swapStr(minNode->CNo, result->next->CNo);
        SWPAINT(minNode->UnGraduateCount, result->next->UnGraduateCount);
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
        StudentInfoByTime minNode = result->next, p = result->next->next;
        while (NULL != p) {
            if ((way == 0 && p->Count < minNode->Count)) {
                minNode = p;
            }
            p = p->next;
        }
        swapStr(minNode->Year, result->next->Year);
        swapStr(minNode->GraduateTo, result->next->GraduateTo);
        SWPAINT(minNode->Count, result->next->Count);
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
        StudentInfoByYear minNode = result->next, p = result->next->next;
        while (NULL != p) {
            if ((atoi(p->Year) < atoi(minNode->Year))) {
                minNode = p;
            }
            p = p->next;
        }
        swapStr(minNode->Year, result->next->Year);
        SWPAINT(minNode->Count, result->next->Count);
        result = result->next;
    }
    return pStart;
}