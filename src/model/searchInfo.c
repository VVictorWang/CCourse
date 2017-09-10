//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "../head.h"

/**
 * @name: searchGradeInfoByNo
 * @function: search the gradeInfo by gradeNo
 * @param phead: the head of the list
 * @param gradeNo: the gradeNo to be searched
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByNo(GradeInfo phead, char *gradeNo) {
    if (gradeNo[0] == '\0') {
        return phead;
    }
    GradeInfo tail = phead;
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while (tail->next != NULL) {
        tail = tail->next;
        if (vagueSearch(tail->CSNo, gradeNo)) {
            p->next = copyGradeInfo(tail);
            p = p->next;
        }
    }
    p->next = NULL;
    return result;
}

/**
 * @name: searchGradeInfoByTime
 * @function: search the gradeInfo by the time
 * @param phead: the head of the list
 * @param start: the start time(none for no limits)
 * @param end: the end time(none for no limits)
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByTime(GradeInfo phead, char *start, char *end) {
    long starttime = atol(start);
    long endtime = atol(end);
    if (start[0] == '\0') {
        starttime = 0;
    }
    if (end[0] == '\0') {
        endtime = 99999999;
    }
    GradeInfo node = phead;
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while ((node = node->next) != NULL) {
        long time = atol(node->Year);
        if (time >= starttime && time <= endtime) {
            p->next = copyGradeInfo(node);
            p = p->next;
        }
    }
    p->next = NULL;
    return result;
}

/**
 * @name: searchGradeInfoByPeople
 * @function: search the gradeInfo by the StudentPeople
 * @param phead: the head of the list
 * @param min: the min number(none for no limits)
 * @param max: the max number(none for no limits)
 * @return the gradeInfo node of the searching result
 */
GradeInfo searchGradeInfoByPeople(GradeInfo phead, char *min, char *max) {
    long minNo, maxNo;
    if (min[0] == '\0') {
        minNo = 0;
    } else
        minNo = atol(min);
    if (max[0] == '\0') {
        maxNo = 999999;
    } else
        maxNo = atol(max);
    GradeInfo node = phead;
    GradeInfo p = (GradeInfo) malloc(sizeof(GRADEInfo));
    p->next = NULL;
    GradeInfo result = p;
    while ((node = node->next) != NULL) {
        int number = node->InNo;
        if (number >= minNo && number <= maxNo) {
            p->next = copyGradeInfo(node);
            p = p->next;
        }
    }
    p->next = NULL;
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
            if (vagueSearch(classHead->CNo, number)) {
                p->next = copyClassInfo(classHead);
                p = p->next;
            }
        }
    }
    p->next = NULL;
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
            if (vagueSearch(classHead->Major, major)) {
                p->next = copyClassInfo(classHead);
                p = p->next;
            }
        }
    }
    p->next = NULL;
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
    if (min[0] == '\0') {
        minNo = 0;
    }
    if (max[0] == '\0') {
        maxNo = 999999;
    }
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
                p->next = copyClassInfo(classHead);
                p = p->next;
            }
        }
    }
    p->next = NULL;
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
            if (vagueSearch(classHead->MentorName, mentorName)) {
                p->next = copyClassInfo(classHead);
                p = p->next;
            }
        }
    }
    p->next = NULL;
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
                if (vagueSearch(studentHead->Name, name)) {
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
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
                if (vagueSearch(classHead->Major, major)) {
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
    return result;
}

/**
 * @name: searchStudentInfoByInTime
 * @function: search the studentInfo by student join school's time
 * @param start: the start time to be searched
 * @param end: the end time to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByInTime(char *start, char *end) {
    long starttime = atol(start);
    long endtime = atol(end);
    if (start[0] == '\0') {
        starttime = 0;
    }
    if (end[0] == '\0') {
        endtime = 99999999;
    }
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
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
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
    int minAge = myAtoi(min);
    int maxAge = myAtoi(max);
    if (min[0] == '\0') {
        minAge = 0;
    }
    if (max[0] == '\0') {
        maxAge = 100;
    }
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
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
    return result;
}

/**
 * @name: searchStudentInfoGraduate
 * @function: search the graduated students
 * @param head: the head of the list
 * @param  isGraduarted: '1' presents the student has graduateds, while '0' presents not
 * @return the head of the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoGraduate(char isGraduarted) {
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
                if (studentHead->HasGraduated == isGraduarted) {
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
    return result;
}

/**
 * @name: searchStudentInfoByGradTo
 * @function: search the studentInfo by student's graduate willing
 * @param gradTo: the  information to be searched
 * @return the studentInfo node of the searching result
 */
StudentInfo searchStudentInfoByGradTo(char *gradTo) {
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
                if (vagueSearch(studentHead->GraduateTo, gradTo)) {
                    p->next = copyStudentInfo(studentHead);
                    p = p->next;
                }
            }
        }
    }
    p->next = NULL;
    return result;
}