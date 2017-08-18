//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"

/**
 * @name: searchGradeInfoByNo
 * @function: search the gradeInfo by gradeNo
 * @param head: the head of the list
 * @param temp: the gradeNo to be searched
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByNo(GradeInfo head, char *temp) {
    GradeInfo tail = head;
    GradeInfo p  = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(tail->CSNo, temp)) {
            p->next = tail;
            p = p->next;
            p->next = NULL;
        }
    }
    return result;
}

/**
 * @name: searchGradeInfoByTime
 * @function: search the gradeInfo by the time
 * @param head: the head of the list
 * @param start: the start time(none for no limits)
 * @param end: the end time(none for no limits)
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByTime(GradeInfo head, char *start, char *end) {
    long starttime = atol(start);
    long endtime = atol(end);
    GradeInfo node = head;
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while ((node = node->next) != NULL) {
        long time = atol(node->Year);
        if (time >= starttime && time <= endtime) {
            p->next = node;
            p = p->next;
        }
    }
    return result;
}

/**
 * @name: searchGradeInfoByPeople
 * @function: search the gradeInfo by the StudentPeople
 * @param head: the head of the list
 * @param min: the min number(none for no limits)
 * @param max: the max number(none for no limits)
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByPeople(GradeInfo head, char *min, char *max) {
    long minNo = atol(min);
    long maxNo = atol(max);
    GradeInfo node = head;
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while ((node = node->next) != NULL) {
        int number = node->InNo;
        if (number >= minNo && number <= maxNo) {
            p->next = node;
            p = p->next;
        }
    }
    return result;
}
