//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#ifndef COURSE_HEAD_H
#define COURSE_HEAD_H
//头文件引入
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

//学生基本信息
typedef struct STUDENTINFO {
    char ClassNo[8];  //所属班级编号
    char CNo[12];  //学号
    char Name[6]; //姓名
    char sex;  //性别 1男2女
    char Birthplace[10];  //籍贯
    char Birthday[9]; //生日
    char Number[12]; //联系电话
    float InScore; //入学分数
    char HasGraduated;  //是否已经毕业 0没毕业  1已经毕业
    char GraduateTo[15];  //毕业去向
    struct STUDENTINFO *next;
} *StudentInfo, STUDENTInfo;

//班级基本信息
typedef struct CLASSINFO {
    char GradeNo[5];  //所属年级编号
    char CNo[8];  //班级编号
    char FullName[12];  //专业名称
    int InNo;  //入学人数
    float AverageAge;  //入学平均年龄
    int GraduateNo; //毕业人数
    char MonitorName[6];  //班长姓名
    char MonitorNo[12];  //班长联系电话
    char MentorName[6]; //班主任姓名
    char MentorNo[12]; //班主任联系电话
    StudentInfo Students; //班级中学生
    struct CLASSINFO *next;

} *ClassInfo, CLASSInfo;

//年级基本信息
typedef struct GRADEINFO {
    char CSNo[5];  //年级编号
    char Year[7];  //入学时间
    int InNo;   //入学人数
    int GraduateNo;  //毕业人数
    char MentorName[6]; //年级辅导员姓名
    char MentorNo[12];  //年级辅导员电话
    char ChairmanName[6]; //年级学生会主席姓名
    char ChairmanNo[12];  //年级学生会主席电话
    ClassInfo Classes; //年级中的班级
    struct GRADEINFO *next;
} *GradeInfo, GRADEInfo;

GradeInfo head;
GtkWidget *main_window;

//函数原型声明
int initInfo(GradeInfo *);//信息初始化函数
void saveInfo(GradeInfo);//信息保存函数
void backupInfo(GradeInfo);//信息备份函数
void restoreInfo(GradeInfo *, char *);//信息恢复函数

//信息录入函数
void inputGradeInfo(GradeInfo, const char **);//年级信息录入函数
void inputClassInfo(GradeInfo, const char **);//班级信息录入函数
void inputStudentInfo(GradeInfo, const char **);//学生信息录入函数
void gradeInfoIn(GradeInfo *, const char **);

void classInfoIn(ClassInfo *, const char **);

void studentInfoIn(StudentInfo *, const char **);

//信息修改函数
int changeGradeInfo(GradeInfo, char *, const char **);//年级信息修改函数
int changeClassInfo(GradeInfo, char *, const char **);//班级信息修改函数
void changeStudentInfo(GradeInfo, char *, const char **);//学生信息修改函数

//信息删除函数
void deleteGradeInfo(GradeInfo, char *);//年级信息删除函数
void deleteClassInfo(GradeInfo, char *);//班级信息删除函数
void deleteStudentInfo(GradeInfo, char *);//学生信息删除函数

//信息查询函数
int searchGradeInfo(GradeInfo, int, char *, char **);//年级信息查询函数
void searchClassInfo(GradeInfo, int, char *, char, char **);//班级信息查询函数
void searchStudentInfo(GradeInfo, int, char *, char *, char **);//学生信息查询函数

//信息统计函数
void CountGradeByTime(GradeInfo, char **);//统计指定时间期限内各年级的班数、入学人数、毕业人数、未毕业人数
void CountClassByTime(GradeInfo, char *,
                      char **);//统计指定时间期限内各班级未毕业学生人数，按未毕业学生人数从大到小排序
void CountStudentByTime(GradeInfo, char *, char *);//统计指定时间期限内毕业后到某企业工作的学生数量，按人数从大到小排序
void CountStudentNoByTime(GradeInfo, char **);//按年度统计从某年到某年每年出生的学生人数

//测试类函数
int testGradeInfo(char *);

//界面类函数
void show_window(GtkWidget **);

void show_notebook(void);

void show_menubar(GtkWidget *);

void show_sidebar(void);

void show_dataview(void);

void show_queryview(void);

void show_stasticalview(void);

//事件类函数
void on_data_clicked(GtkWidget *);

void on_query_clicked(GtkWidget *);

void on_stastical_clicked(GtkWidget *);

void on_grade_clicked(GtkWidget *);

void on_class_clicked(GtkWidget *);

void on_student_clicked(GtkWidget *);

void on_confirm_clicked(GtkWidget *);

void on_backup_clicked(GtkWidget *, gpointer);

void on_restore_clicked(GtkWidget *, gpointer);

void on_aboutsystem_clicked(GtkWidget *);

void on_aboutme_clicked(GtkWidget *);

//数据维护事件函数
void gradeInfo_method(void);

void on_gradeInfo_add_clicked(GtkWidget *, gpointer);

void on_gradeInfo_modify_clicked(GtkWidget *, gpointer);

void on_gradeInfo_delete_clicked(GtkWidget *);

void on_cancel_clicked(GtkWidget *, gpointer);

void reload_gradeInfo_list(void);

void classInfo_method(void);

void on_classInfo_add_clicked(GtkWidget *, gpointer);

void on_classInfo_modify_clicked(GtkWidget *, gpointer);

void on_classInfo_delete_clicked(GtkWidget *);

void reload_classInfo_list(void);

void studentInfo_method(void);

void on_studentInfo_add_clicked(GtkWidget *, gpointer);

void on_studentInfo_modify_clicked(GtkWidget *, gpointer);

void on_studentInfo_delete_clicked(GtkWidget *);

void reload_studentInfo_list(void);

void on_province_combo_changed(GtkWidget *, gpointer);


//界面辅助类函数
GdkPixbuf *create_pixbuf(const gchar *);

void warning_message_dialog(gchar *, gchar *);

void error_message_dialog(gchar *, gchar *);

void information_message_dialog(gchar *, gchar *);

#endif //COURSE_HEAD_H
