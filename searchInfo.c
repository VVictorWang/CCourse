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
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
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
            p->next = NULL;
        }
    }
    return result;
}

/**
 * @name: searchClassInfoByNo
 * @function: search the classInfo by classNo
 * @param head: the head of the list
 * @param number: the classNo to be searched
 * @return the classInfo node of the searching result
 */
ClassInfo searchClassInfoByNo(char *number) {
    GradeInfo tail = head;
    ClassInfo p = (ClassInfo) malloc(sizeof(CLASSInfo));
    p->next = NULL;
    ClassInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            if (!strcmp(classHead->CNo, number)) {
                p->next = classHead;
                p = p->next;
                p->next = NULL;
            }
        }

    }
    return result;

}

/**
 * @name: ssearchClassInfoByMajor
 * @function: search the classInfo by Major
 * @param head: the head of the list
 * @param major: the major to be searched
 * @return the classInfo node of the searching result
 */
ClassInfo searchClassInfoByMajor(char *major) {
    GradeInfo tail = head;
    ClassInfo p = (ClassInfo) malloc(sizeof(CLASSInfo));
    p->next = NULL;
    ClassInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            if (!strcmp(classHead->Major, major)) {
                p->next = classHead;
                p = p->next;
                p->next = NULL;
            }
        }

    }
    return result;
}

/**
 * @name: searchClassInfoByPeople
 * @function: search the classInfo by the StudentPeople
 * @param head: the head of the list
 * @param min: the min number(none for no limits)
 * @param max: the max number(none for no limits)
 * @return the head of the classInfo node of the searching result
 */
ClassInfo searchClassInfoByPeople(char *min, char *max) {
    long minNo = atol(min);
    long maxNo = atol(max);
    GradeInfo tail = head;
    ClassInfo p = (ClassInfo) malloc(sizeof(CLASSInfo));
    p->next = NULL;
    ClassInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            int number = classHead->InNo;
            if (number >= minNo && number <= maxNo) {
                p->next = classHead;
                p = p->next;
                p->next = NULL;
            }
        }
    }
    return result;
}

/**
 * @name: searchClassInfoByMentorName
 * @function: search the classInfo by mentor name
 * @param head: the head of the list
 * @param mentorName: the mentorName to be searched
 * @return the classInfo node of the searching result
 */
ClassInfo searchClassInfoByMentorName(char *mentorName) {
    GradeInfo tail = head;
    ClassInfo p = (ClassInfo) malloc(sizeof(CLASSInfo));
    p->next = NULL;
    ClassInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            if (!strcmp(classHead->MentorName, mentorName)) {
                p->next = classHead;
                p = p->next;
                p->next = NULL;
            }
        }

    }
    return result;
}

/**
 * @name: searchStudentInfoByName
 * @function: search the studentInfo by student name
 * @param head: the head of the list
 * @param name: the name to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByName(char *name) {
    GradeInfo tail = head;
    StudentInfo p = (StudentInfo) malloc(sizeof(STUDENTInfo));
    p->next = NULL;
    StudentInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            StudentInfo studentHead = classHead->Students;
            while ((studentHead = studentHead->next) != NULL) {
                if (!strcmp(studentHead->Name, name)) {
                    p->next = studentHead;
                    p = p->next;
                    p->next = NULL;
                }
            }

        }
    }
    return result;
}


/**
 * @name: searchStudentInfoByMajor
 * @function: search the studentInfo by student major
 * @param head: the head of the list
 * @param major: the major name to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByMajor(char *major) {
    GradeInfo tail = head;
    StudentInfo p = (StudentInfo) malloc(sizeof(STUDENTInfo));
    p->next = NULL;
    StudentInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            StudentInfo studentHead = classHead->Students;
            while ((studentHead = studentHead->next) != NULL) {
                if (!strcmp(classHead->Major, major)) {
                    p->next = studentHead;
                    p = p->next;
                    p->next = NULL;
                }
            }

        }
    }
    return result;
}

/**
 * @name: searchStudentInfoByInTime
 * @function: search the studentInfo by student join school's time
 * @param head: the head of the list
 * @param start: the start time to be searched
 * @param end: the end time to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByInTime(char *start, char *end) {
    long starttime = atol(start);
    long endtime = atol(end);
    GradeInfo tail = head;
    StudentInfo p = (StudentInfo) malloc(sizeof(STUDENTInfo));
    p->next = NULL;
    StudentInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            StudentInfo studentHead = classHead->Students;
            while ((studentHead = studentHead->next) != NULL) {
                long time = atol(tail->Year);
                if (time >= starttime && time <= endtime) {
                    p->next = studentHead;
                    p = p->next;
                    p->next = NULL;
                }
            }

        }
    }
    return result;
}

/**
 * @name: searchStudentInfoByAge
 * @function: search the studentInfo by students' age
 * @param head: the head of the list
 * @param min: the min age to be searched
 * @param max: the max age to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByAge(char *min, char *max) {
    int minAge = atoi(min);
    int maxAge = atoi(max);
    GradeInfo tail = head;
    StudentInfo p = (StudentInfo) malloc(sizeof(STUDENTInfo));
    p->next = NULL;
    StudentInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo classHead = tail->Classes;
        while ((classHead = classHead->next) != NULL) {
            StudentInfo studentHead = classHead->Students;
            while ((studentHead = studentHead->next) != NULL) {
                int age = getAgeByBirthDay(studentHead->Birthday);
                if (age >= minAge && age <= maxAge) {
                    p->next = studentHead;
                    p = p->next;
                    p->next = NULL;
                }
            }

        }
    }
    return result;
}