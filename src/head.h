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
    char Name[12]; //姓名
    char sex;  //性别 1男2女
    char Birthplace[10];  //籍贯
    char Birthday[10]; //生日
    char Number[12]; //联系电话
    float InScore; //入学分数
    char HasGraduated;  //是否已经毕业 0没毕业  1已经毕业
    char GraduateTo[15];  //毕业去向
    struct STUDENTINFO *next;
} *StudentInfo, STUDENTInfo;

//班级基本信息
typedef struct CLASSINFO {
    char GradeNo[6];  //所属年级编号
    char CNo[8];  //班级编号
    char Major[12];  //专业名称
    int InNo;  //入学人数
    float AverageAge;  //入学平均年龄
    int GraduateNo; //毕业人数
    char MonitorName[12];  //班长姓名
    char MonitorNo[14];  //班长联系电话
    char MentorName[12]; //班主任姓名
    char MentorNo[14]; //班主任联系电话
    StudentInfo Students; //班级中学生
    struct CLASSINFO *next;

} *ClassInfo, CLASSInfo;

//年级基本信息
typedef struct GRADEINFO {
    char CSNo[6];  //年级编号
    char Year[10];  //入学时间
    int InNo;   //入学人数
    int GraduateNo;  //毕业人数
    char MentorName[12]; //年级辅导员姓名
    char MentorNo[12];  //年级辅导员电话
    char ChairmanName[12]; //年级学生会主席姓名
    char ChairmanNo[12];  //年级学生会主席电话
    ClassInfo Classes; //年级中的班级
    struct GRADEINFO *next;
} *GradeInfo, GRADEInfo;

//按指定期限统计年级信息的数据
typedef struct GRADEINFOBYTIME {
    char Year[10]; //入学时间
    char CSNo[6]; //年级编号
    int ClassCount; //班级数目
    int InNo; //入学人数
    int GraduatedCount; //毕业人数
    int UnGraduatedCount; //未毕业人数
    struct GRADEINFOBYTIME *next;
} *GradeInfoByTime, GRADEInfobyTime;

//按指定期限统计班级信息的数据
typedef struct CLASSINFOBYTIME {
    char Year[10]; //入学时间
    char CNo[8]; //班级编号
    int UnGraduateCount; //未毕业人数
    struct CLASSINFOBYTIME *next;
} *ClassInfoByTime, CLASSInfobyTime;

//按指定期限统计学生信息的数据
typedef struct STUDENTINFOBYTIME {
    char GraduateTo[10]; //时间
    int Count; //数量
} *StudentInfoByTime, STUDENTinfobyTime;

//按年度统计学生信息的数据
typedef struct STUDENTINFOBYYEAR {
    char Year[6]; //年度
    int Count; //出生学生人数
    struct STUDENTINFOBYYEAR *next;
} *StudentInfoByYear, STUDENTinfobyYear;

//所有图片资源的路径
typedef struct IMAGEPATH {
    const char iconPath[50];
    const char sideBar[50];
    const char blueButton[50];
    const char yellowButton[50];
    const char greenButton[50];
    const char gradeInfoNormal[50];
    const char classInfoNormal[50];
    const char studentInfoNormal[50];
    const char gradeInfoSelec[50];
    const char classInfoSelec[50];
    const char studentInfoSelec[50];
    const char dataNormal[50];
    const char searchNormal[50];
    const char statisticNormal[50];
    const char dataSelec[50];
    const char searchSelec[50];
    const char statisticSelec[50];
} ImagePath;

//所有图片资源的路径，这里使用了相对路径(..代表当前目录的上一级目录),使用静态全局变量存储，节省内存开销与方便更改图片名称
const static ImagePath MYIMAGEPATH = {
        "../img/icon.png",
        "../img/sidebar.png",
        "../img/blue_button.png",
        "../img/yellow_button.png",
        "../img/green_button.png",
        "../img/gradeInfo.png",
        "../img/classInfo.png",
        "../img/studentInfo.png",
        "../img/gradeInfo_selected.png",
        "../img/classInfo_selected.png",
        "../img/studentInfo_selected.png",
        "../img/data.png",
        "../img/search.png",
        "../img/statistic.png",
        "../img/data_selected.png",
        "../img/search_selected.png",
        "../img/statistic_selected.png"
};
GradeInfo head;
GtkWidget *main_window;

//函数原型声明
int initInfo(GradeInfo *);//信息初始化函数
void saveInfo(GradeInfo);//信息保存函数
void backup_data(GradeInfo, char *); //信息备份函数
int restore_data(GradeInfo *, char *);//信息恢复函数

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
GradeInfo searchGradeInfoByNo(GradeInfo, char *);//年级信息查询函数
GradeInfo searchGradeInfoByTime(GradeInfo, char *, char *);//
GradeInfo searchGradeInfoByPeople(GradeInfo, char *, char *);//
ClassInfo searchClassInfoByNo(char *);//
ClassInfo searchClassInfoByMajor(char *);//
ClassInfo searchClassInfoByPeople(char *, char *);//
ClassInfo searchClassInfoByMentorName(char *);//
StudentInfo searchStudentInfoByName(char *);//
StudentInfo searchStudentInfoByMajor(char *);//
StudentInfo searchStudentInfoByInTime(char *, char *);//
StudentInfo searchStudentInfoByAge(char *, char *);//
StudentInfo searchStudentInfoGraduate(char);//
StudentInfo searchStudentInfoByGradTo(char *);//


//信息统计函数
GradeInfoByTime countGradeInfoByTime(char *, char *);//统计指定时间期限内各年级的班数、入学人数、毕业人数、未毕业人数
ClassInfoByTime countClassInfoByTime(char *, char *);//统计指定时间期限内各班级未毕业学生人数，按未毕业学生人数从大到小排序
StudentInfoByTime countStudentInfoByTime(char *, char *);//统计指定时间期限内毕业后到某企业工作的学生数量，按人数从大到小排序
StudentInfoByYear countStudentInfoByYear(char *, char *);//按年度统计从某年到某年每年出生的学生人数
int getClassNumber(GradeInfo); //统计该年级下的班级数量

//测试类函数
int testGradeInfo(char *);

//界面类函数
void show_window(GtkWidget **);//
void show_notebook(void);//
void show_menubar(GtkWidget *);//
void show_sidebar(void);//
void show_dataview(void);//
void show_queryview(void);//
void show_stasticalview(void);//
void run_gradeInfo_dialog(GradeInfo);//
void run_classInfo_dialog(ClassInfo);//
void run_studentInfo_dialog(StudentInfo);//

//事件类函数
void on_data_clicked(GtkWidget *);//
void on_query_clicked(GtkWidget *);//
void on_stastical_clicked(GtkWidget *);//
void on_grade_clicked(GtkWidget *);//
void on_class_clicked(GtkWidget *);//
void on_student_clicked(GtkWidget *);//
void on_confirm_clicked(GtkWidget *);//
void on_backup_clicked(GtkWidget *, gpointer);//
void on_save_clicked(GtkWidget *, gpointer);//
void on_restore_clicked(GtkWidget *, gpointer);//
void on_aboutsystem_clicked(GtkWidget *);//
void on_aboutme_clicked(GtkWidget *);//


//数据查询事件函数
void on_gradeInfo_no_search_clicked(GtkWidget *);//
void on_gradeInfo_time_search_clicked(GtkWidget *);//
void on_gradeInfo_inno_search_clicked(GtkWidget *);//
void on_classInfo_no_search_clicked(GtkWidget *);//
void on_classInfo_major_search_clicked(GtkWidget *);//
void on_classInfo_peopleNo_search_clicked(GtkWidget *);//
void on_classInfo_mentorName_search_clicked(GtkWidget *);//
void on_studentInfo_name_search_clicked(GtkWidget *);//
void on_studentInfo_major_search_clicked(GtkWidget *);//
void on_studentInfo_Intime_search_clicked(GtkWidget *);//
void on_studentInfo_age_search_clicked(GtkWidget *);//
void on_studentInfo_isGrad_search_clicked(GtkWidget *);//
void on_studentInfo_Graduate_clicked(GtkWidget *);//
void on_studentInfo_not_Graduate_clicked(GtkWidget *);//
void on_studentInfo_graduaTo_search_clicked(GtkWidget *);//


//数据统计事件函数
void on_gradeInfo_stastical_clicked(GtkWidget *);

void on_classInfo_stastical_clicked(GtkWidget *);

void on_studentInfo_stastical_clicked(GtkWidget *);

void on_student_stastical_by_year_clicked(GtkWidget *);


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


//界面辅助类函数
GdkPixbuf *create_pixbuf(const gchar *);

void warning_message_dialog(gchar *, gchar *);

void error_message_dialog(gchar *, gchar *);

void information_message_dialog(gchar *, gchar *);

void addTreeColumnView(GtkWidget *, GtkCellRenderer *, char *, int);

void setTableView(GtkWidget **, GtkWidget **, GtkWidget *);

//数据辅助类函数
int getAgeByBirthDay(char *);

char *strsub(char *, int, int);

int vagueSearch(char *, char *);

int getGtkWidgetListLen(GtkWidget **);

#endif //COURSE_HEAD_H
