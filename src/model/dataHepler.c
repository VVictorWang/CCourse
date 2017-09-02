//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//


#include "../head.h"

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
    free(year);
    struct tm *p;
    time_t timep = time(NULL);
    p = localtime(&timep);
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
    result[i - start] = '\0';
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
    while (1) {
        int n = memcmp(res, des, strlen(des)); //比较
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

/**
 * @name getGtkWidgetListLen
 * @function get the length of a list of Gtkwidget * widgets
 * @param str: the list of the src
 * @return the length
 */
int getGtkWidgetListLen(GtkWidget **str) {
    int i = 0;
    while (str[i++] != NULL);
    return --i;
}

/**
 * @name getDateOfTheCalendar
 * @function get the selected date string of the calendar
 * @param calendar: the given calendar
 * @return the date string
 */
char *getDateOfTheCalendar(GtkWidget *calendar){
    char *result = (char *) malloc(sizeof(char) * 10);
    unsigned int year = 0, month = 0, day = 0;
    gtk_calendar_get_date(GTK_CALENDAR(calendar), &year, &month, &day);
    snprintf(result, 9, "%ud", year * 10000 + (month + 1) * 100 + day);
    return result;
}


/**
 * @name intToStr
 * @function change the given int to a string
 * @param m: the given integer
 * @return the string
 */
char *intToStr(int m) {
    char temp[20], *result;
    //由于int型表示的范围负数比正数多1，故在这里处理
    if (m == INT_MIN) {
        char *s = intToStr(INT_MIN + 1);
        s[strlen(s) - 1] += 1;
        return s;
    }
    int i = 0, flag = 0;
    if (m < 0 && m > INT_MIN) {
        flag = 1;
        m = -m;
    }
    while (m > 0) {
        temp[i++] = (char) (m % 10 + '0');
        m /= 10;
    }
    if (flag) {
        temp[i++] = '-';
    }
    temp[i] = '\0';
    i--;
    int j = 0;
    result = (char *) malloc(sizeof(char) * (strlen(temp) + 1));
    for (j = 0; i >= 0; j++, i--) {
        result[j] = temp[i];
    }
    result[j] = '\0';
    return result;
}

/**
 * @name myAtoi
 * @function convert a string to integer
 * @param str: the given string
 * @return the integer
 */
int myAtoi(const char *str) {
    int result = 0, i = 0, flag = 0;
    while (str[i] == ' ') //处理前面空格
        i++;
    if (str[i] == '-') { //判断是否为负数
        i++;
        flag = 1;
    } else if (str[i] == '+')
        i++;
    while (str[i] != '\0') {
        if ((str[i] >= '0' && str[i] <= '9')) {
            if (result >= (INT_MAX / 10 - (str[i] - '0') + 7)) { //判断是否超出int型最大
                if (flag && result > (INT_MAX / 10 - (str[i] - '0') + 7)) {
                    return INT_MIN;
                }
                return flag ? -INT_MAX : INT_MAX;
            }
            result *= 10;
            result += str[i++] - '0';
        } else {
            return flag ? -result : result;
        }
    }
    return flag ? -result : result;
}