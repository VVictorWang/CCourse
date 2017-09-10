//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include"../head.h"

/**
 * @name deleteGradeInfo
 * @function delete the gradeInfo
 * @param head: the head of the list
 * @param str: the No of the grade
 * @return none
 * @details: the students' information and the classes' information of the grade will be lost
 */
void deleteGradeInfo(GradeInfo head, char *str) {
    GradeInfo gradeTail = head;
    while (gradeTail->next != NULL) {
        GradeInfo gradeTailOld = gradeTail;
        gradeTail = gradeTail->next;
        if (!strcmp(gradeTail->CSNo, str)) {
            gradeTailOld->next = gradeTail->next;
            gradeTail->next = NULL;
            freeAllClasses(gradeTail->Classes);
            free(gradeTail);
            break;
        }
    }
}


/**
 * @name deleteClassInfo
 * @function delete the classInfo
 * @param head: the head of the list
 * @param str: the No of the class
 * @return none
 * @details: the students' information of the class will be lost
 */
void deleteClassInfo(GradeInfo head, char *str) {
    GradeInfo gradeTail = head;
    while (gradeTail->next != NULL) {
        gradeTail = gradeTail->next;
        ClassInfo classTail = gradeTail->Classes;
        while (classTail->next != NULL) {
            ClassInfo classTailOld = classTail;
            classTail = classTail->next;
            if (!strcmp(classTail->CNo, str)) {
                classTailOld->next = classTail->next;
                classTail->next = NULL;
                freeAllStudents(classTail->Students);
                free(classTail);
                return;
            }
        }
    }
}

/**
 * @name deleteStudentInfo
 * @function delete the studentInfo
 * @param head: the head of the list
 * @param str: the No of the student
 * @return none
 */
void deleteStudentInfo(GradeInfo head, char *str) {
    GradeInfo gradeTail = head;
    while (gradeTail->next != NULL) {
        gradeTail = gradeTail->next;
        ClassInfo classTail = gradeTail->Classes;
        while (classTail->next != NULL) {
            classTail = classTail->next;
            StudentInfo studentTail = classTail->Students;
            while (studentTail->next != NULL) {
                StudentInfo studentTailOld = studentTail;
                studentTail = studentTail->next;
                if (!strcmp(studentTail->CNo, str)) {
                    studentTailOld->next = studentTail->next;
                    studentTail->next = NULL;
                    free(studentTail);
                    return;
                }
            }
        }
    }
}

/**
 * @name freeAllClasses
 * @function free all of the classInfo nodes
 * @param node: the head of the classInfo lists
 * @return none
 */
void freeAllClasses(ClassInfo node){
    ClassInfo classNode = node;
    while ((classNode = classNode->next) != NULL) {
        ClassInfo temp = classNode;
        freeAllStudents(classNode->Students);
        free(temp);
    }
}

/**
 * @name freeAllStudents
 * @function free all of the studentInfo nodes
 * @param node: the head of the studentInfo lists
 * @return none
 */
void freeAllStudents(StudentInfo node){
    StudentInfo studentNode = node;
    while ((studentNode = studentNode->next) != NULL) {
        StudentInfo temp = studentNode;
        free(temp);
    }
}