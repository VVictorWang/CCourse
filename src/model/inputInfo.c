//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

/**
 * @name gradeInfoIn
 * @function save the gradeInfo into a node
 * @param head the node to be inserted
 * @param str the information that user inputs
 * @return none
 */
void gradeInfoIn(GradeInfo *head, const char **str) {
    strcpy((*head)->CSNo, str[0]);
    strcpy((*head)->Year, str[1]);
    (*head)->InNo = myAtoi(str[2]);
    (*head)->GraduateNo = myAtoi(str[3]);
    strcpy((*head)->MentorName, str[4]);
    strcpy((*head)->MentorNo, str[5]);
    strcpy((*head)->ChairmanName, str[6]);
    strcpy((*head)->ChairmanNo, str[7]);
}

/**
 * @name classInfoIn
 * @function save the classInfo into a node
 * @param head the node to be inserted
 * @param str the information that user inputs
 * @return none
 */
void classInfoIn(ClassInfo *head, const char **str) {
    strcpy((*head)->GradeNo, str[0]);
    strcpy((*head)->CNo, str[1]);
    strcpy((*head)->Major, str[2]);
    (*head)->InNo = myAtoi(str[3]);
    (*head)->AverageAge = (float) atof(str[4]);
    (*head)->GraduateNo = myAtoi(str[5]);
    strcpy((*head)->MonitorName, str[6]);
    strcpy((*head)->MonitorNo, str[7]);
    strcpy((*head)->MentorName, str[8]);
    strcpy((*head)->MentorNo, str[9]);

}

/**
 * @name: studentInfoIn
 * @function: save the studentInfo into a node
 * @param head the node to be inserted
 * @param str the information that user inputs
 * @return none
 */
void studentInfoIn(StudentInfo *head, const char **str) {
    strcpy((*head)->ClassNo, str[0]);
    strcpy((*head)->CNo, str[1]);
    strcpy((*head)->Name, str[2]);
    (*head)->sex = *str[3];
    strcpy((*head)->Birthplace, str[4]);
    strcpy((*head)->Birthday, str[5]);
    strcpy((*head)->Number, str[6]);
    (*head)->InScore = (float) atof(str[7]);
    (*head)->HasGraduated = *str[8];
    strcpy((*head)->GraduateTo, str[9]);
}


/**
 * @name inputGradeInfo
 * @function save the gradeInfo
 * @param head the head of the list
 * @param str the information that user inputs
 * @return none
 */
void inputGradeInfo(GradeInfo head, const char **str) {
    GradeInfo tail = head;
    while (tail->next != NULL)
        tail = tail->next;
    tail->next = (GradeInfo) malloc(sizeof(GRADEInfo));
    tail = tail->next;
    gradeInfoIn(&tail, str);
    tail->Classes = (ClassInfo) malloc(sizeof(CLASSInfo));
    tail->Classes->next = NULL;
    tail->next = NULL;
}

/**
 * @name inputClassInfo
 * @function save the classInfo
 * @param head the head of the list
 * @param str the information that user inputs
 * @return none
 */
void inputClassInfo(GradeInfo head, const char **str) {
    GradeInfo tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(str[0], tail->CSNo)) {
            ClassInfo tail1 = tail->Classes;
            while (tail1->next != NULL)
                tail1 = tail1->next;
            tail1->next = (ClassInfo) malloc(sizeof(CLASSInfo));
            tail1 = tail1->next;
            classInfoIn(&tail1, str);
            tail1->Students = (StudentInfo) malloc(sizeof(STUDENTInfo));
            tail1->Students->next = NULL;
            tail1->next = NULL;
            break;
        }
    }
}

/**
 * @name inputStudentInfo
 * @function save the studentInfo
 * @param head the head of the list
 * @param str the information that user inputs
 * @return: none
 *
 */
void inputStudentInfo(GradeInfo head, const char **str) {
    GradeInfo tail = head;
    int flag = 0;
    while (tail->next != NULL) {
        tail = tail->next;
        ClassInfo tail1 = tail->Classes;
        while (tail1->next != NULL) {
            tail1 = tail1->next;
            if (!strcmp(tail1->CNo, str[0])) {
                flag = 1;
                StudentInfo tail2 = tail1->Students;
                while (tail2->next != NULL)
                    tail2 = tail2->next;
                tail2->next = (StudentInfo) malloc(sizeof(STUDENTInfo));
                tail2 = tail2->next;
                studentInfoIn(&tail2, str);
                tail2->next = NULL;
                tail = head;
                break;
            }
        }
        if (flag)
            break;
    }
}


