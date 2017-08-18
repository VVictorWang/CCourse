//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"

/**
* @name getClassNumber
* @function get the classCount of the grade
* @param head: the gradeInfo node
* @return the class Count
*/
int getClassNumber(GradeInfo head) {
    int count = 0;
    ClassInfo classNode = head->Classes;
    while ((classNode = classNode->next) != NULL) {
        count++;
    }
    return count;
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
