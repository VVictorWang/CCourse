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
    char *year = strsub(birthday, 0, 4);
    int cuYear = atoi(year);
    int toYear = cuYear - 1900;
    struct tm *p;
    time_t timep;
    time(&timep);
    p = gmtime(&timep);
    return (p->tm_year - toYear);
}

/**
 * @name strsub
 * @function get the src string's substring by a start index and a end index
 * @param src: the src string
 * @param start: the start index(begins with 0)
 * @param end: the end index
 * @return the substring
 */
char *strsub(char *src, int start, int end) {
    int length = (int) strlen(src);
    char *result;
    int i = 0;
    if (start < 0) //如果起始index小于0，则从初始开始
        start = 0;
    if (end > length) { //如果终止index超过源字符串长度，则切到末尾
        result = (char *) malloc(sizeof(char) * (length - start + 1));
        for (i = start; i < length; i++) {
            result[i - start] = src[i];
        }
    } else {
        result = (char *) malloc(sizeof(char) * (end - start + 1));
        for (i = start; i < end; i++) {
            result[i - start] = src[i];
        }
    }
    return result;
}

/**
 * @name vagueSearch
 * @function test whether the des string is the src string's substring
 * @param src: the src string
 * @param des: the des string
 * @return the search result q indicates yes, 0 indicates no
 */
int vagueSearch(char *src, char *des) {
    char *res;
    res = memchr(src, des[0], strlen(src));   //根据要查找的字符串第一个字符，切割源字符串
    if (res == NULL)
        return 0;
    int n;
    while (1) {
        n = memcmp(res, des, strlen(des) - 1); //比较
        if (n != 0) {
            if (strlen(res) <= strlen(des))    //切割出的字符串小于要查找字符串的长度
                return 0;
            //根据要查找的第一个字符继续切割
            res = memchr(res + 1, des[0], strlen(res));
            if (res == NULL)
                return 0;
        } else  //如果n = 0，找到
            return 1;
    }
}

int getGtkWidgetListLen(GtkWidget **str) {
    int i = 0;
    while (str[i++] != NULL);
    return --i;
}