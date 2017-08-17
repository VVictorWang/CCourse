//
// Created by victor on 8/17/17.
//
#include "head.h"

/**
 * @name: testGradeInfo
 * @function: test whether the grade information to be inserted already existed
 * @param str:  the No of the grade to be tested
 * @return flag: 1 indicates the grade has already existed, 0 indicates the opposite
 */

int testGradeInfo(char *str)
{
    GradeInfo tail = head;
    int flag = 0;
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(str, tail->CSNo)) {
            flag = 1;
            break;
        }
    }
    return flag;
}