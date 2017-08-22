//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

//防止头文件重复引入
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

GradeInfo head; //整个链表头结点
GtkWidget *main_window; //主窗体

//函数原型声明
int initInfo(GradeInfo *);//信息初始化函数
void saveInfo(GradeInfo);//信息保存函数
void backupInfo(GradeInfo, char *); //信息备份函数
int restoreInfo(GradeInfo *, char *);//信息恢复函数

//信息录入函数
void inputGradeInfo(GradeInfo, const char **);//年级信息录入函数，为新节点分配内存
void inputClassInfo(GradeInfo, const char **);//班级信息录入函数，为新节点分配内存
void inputStudentInfo(GradeInfo, const char **);//学生信息录入函数，为新节点分配内存
void gradeInfoIn(GradeInfo *, const char **);  //将年级信息保存到链表中
void classInfoIn(ClassInfo *, const char **); //将班级信息保存到链表中
void studentInfoIn(StudentInfo *, const char **); //将学生信息保存到链表中

//信息修改函数
int changeGradeInfo(GradeInfo, char *, const char **);//年级信息修改函数
int changeClassInfo(GradeInfo, char *, const char **);//班级信息修改函数
void changeStudentInfo(GradeInfo, char *, const char **);//学生信息修改函数

//信息删除函数
void deleteGradeInfo(GradeInfo, char *);//年级信息删除函数
void deleteClassInfo(GradeInfo, char *);//班级信息删除函数
void deleteStudentInfo(GradeInfo, char *);//学生信息删除函数

//信息查询函数
GradeInfo searchGradeInfoByNo(GradeInfo, char *);//年级信息查询函数,通过年级编号
GradeInfo searchGradeInfoByTime(GradeInfo, char *, char *); //年级信息查询函数,通过入学时间（区间)
GradeInfo searchGradeInfoByPeople(GradeInfo, char *, char *);//年级信息查询函数,通过入学人数
ClassInfo searchClassInfoByNo(char *); //班级信息查询函数,通过班级编号
ClassInfo searchClassInfoByMajor(char *); //班级信息查询函数,通过班级所修专业
ClassInfo searchClassInfoByPeople(char *, char *);//班级信息查询函数,通过班级入学人数
ClassInfo searchClassInfoByMentorName(char *); //班级信息查询函数,通过班级班主任姓名
StudentInfo searchStudentInfoByName(char *); //学生信息查询函数,通过学生姓名
StudentInfo searchStudentInfoByMajor(char *); //学生信息查询函数,通过学生所修专业
StudentInfo searchStudentInfoByInTime(char *, char *); //学生信息查询函数,通过学生入学时间
StudentInfo searchStudentInfoByAge(char *, char *); //学生信息查询函数,通过学生年龄(区间)
StudentInfo searchStudentInfoGraduate(char); //学生信息查询函数,通过学生是否已毕业
StudentInfo searchStudentInfoByGradTo(char *); //学生信息查询函数,通过学生毕业去向


//信息统计函数
GradeInfoByTime countGradeInfoByTime(char *, char *);//统计指定时间期限内各年级的班数、入学人数、毕业人数、未毕业人数
ClassInfoByTime countClassInfoByTime(char *, char *);//统计指定时间期限内各班级未毕业学生人数，按未毕业学生人数从大到小排序
StudentInfoByTime countStudentInfoByTime(char *, char *);//统计指定时间期限内毕业后到某企业工作的学生数量，按人数从大到小排序
StudentInfoByYear countStudentInfoByYear(char *, char *);//按年度统计从某年到某年每年出生的学生人数
int getClassNumber(GradeInfo); //统计该年级下的班级数量

//测试类函数
int testGradeInfo(const char *); //通过编号测试是否已经存在此年级
int testClassInfo(const char *); //通过编号测试是否已经存在此班级
int testStudentInfo(const char *); //通过学号测试是否已经存在此学生

//界面类函数
void show_window(GtkWidget **); //显示主界面
void show_notebook(void); //显示右边窗体的容器
void show_menubar(GtkWidget *);//显示上方菜单
void show_sidebar(void);//显示侧边菜单
void show_dataview(void);//显示数据维护界面
void show_queryview(void);//显示数据查询界面
void show_stasticalview(void);//显示数据统计界面
void run_gradeInfo_dialog(GradeInfo);//显示年级信息的表格
void run_classInfo_dialog(ClassInfo);//显示班级信息的表格
void run_studentInfo_dialog(StudentInfo);//显示学生信息的表格

//事件类函数
void on_data_clicked(GtkWidget *);//数据维护控件被点击事件
void on_query_clicked(GtkWidget *);//数据查询控件被点击事件
void on_stastical_clicked(GtkWidget *);//数据统计控件被点击事件
void on_grade_clicked(GtkWidget *);//年级信息控件被点击事件
void on_class_clicked(GtkWidget *);//班级信息控件被点击事件
void on_student_clicked(GtkWidget *);//学生信息控件被点击事件
void on_confirm_clicked(GtkWidget *);//确定被点击事件
void on_backup_clicked(GtkWidget *, gpointer);//数据另存为被点击事件
void on_save_clicked(GtkWidget *, gpointer);//数据保存被点击事件
void on_restore_clicked(GtkWidget *, gpointer);//数据恢复被点击事件
void on_aboutsystem_clicked(GtkWidget *);//关于本系统被点击事件
void on_aboutme_clicked(GtkWidget *);//关于作者被点击事件


//数据查询事件函数
void on_gradeInfo_no_search_clicked(GtkWidget *);//年级信息查询事件,通过年级编号
void on_gradeInfo_time_search_clicked(GtkWidget *);//年级信息查询事件,通过入学时间（区间)
void on_gradeInfo_inno_search_clicked(GtkWidget *);//年级信息查询事件,通过入学人数
void on_classInfo_no_search_clicked(GtkWidget *);//班级信息查询事件,通过班级编号
void on_classInfo_major_search_clicked(GtkWidget *);//班级信息查询事件,通过班级所修专业
void on_classInfo_peopleNo_search_clicked(GtkWidget *);//班级信息查询事件,通过班级入学人数
void on_classInfo_mentorName_search_clicked(GtkWidget *);//班级信息查询事件,通过班级班主任姓名
void on_studentInfo_name_search_clicked(GtkWidget *); //学生信息查询事件,通过学生姓名
void on_studentInfo_major_search_clicked(GtkWidget *); //学生信息查询事件,通过学生所修专业
void on_studentInfo_Intime_search_clicked(GtkWidget *); //学生信息查询事件,通过学生入学时间(区间)
void on_studentInfo_age_search_clicked(GtkWidget *); //学生信息查询事件,通过学生年龄(区间)
void on_studentInfo_isGrad_search_clicked(GtkWidget *); //学生信息查询事件,通过学生是否已经毕业(区间)
void on_studentInfo_Graduate_clicked(GtkWidget *); //学生信息查询事件,通过学生毕业去向
void on_studentInfo_not_Graduate_clicked(GtkWidget *);//查询未毕业学生信息事件
void on_studentInfo_graduaTo_search_clicked(GtkWidget *); //查询已毕业学生信息事件


//数据统计事件函数
void on_gradeInfo_stastical_clicked(GtkWidget *); //年级信息统计事件
void on_classInfo_stastical_clicked(GtkWidget *); //班级信息统计事件
void on_studentInfo_stastical_clicked(GtkWidget *); //学生信息统计事件
void on_student_stastical_by_year_clicked(GtkWidget *); //学生信息统计事件,按年度


//数据维护事件函数
void gradeInfo_method(void); //年级信息数据维护事件
void on_gradeInfo_add_clicked(GtkWidget *, gpointer); //录入年级信息事件
void on_gradeInfo_modify_clicked(GtkWidget *, gpointer); //修改年级信息事件
void on_gradeInfo_delete_clicked(GtkWidget *); //删除年级信息事件
void on_cancel_clicked(GtkWidget *, gpointer); //取消事件
void reload_gradeInfo_list(void); //重新加载年级信息列表
void classInfo_method(void); //班级信息数据维护事件
void on_classInfo_add_clicked(GtkWidget *, gpointer); //录入班级信息事件
void on_classInfo_modify_clicked(GtkWidget *, gpointer); //修改班级信息事件
void on_classInfo_delete_clicked(GtkWidget *); //删除班级信息事件
void reload_classInfo_list(void); //重新加载班级信息列表
void studentInfo_method(void); //学生信息数据维护事件
void on_studentInfo_add_clicked(GtkWidget *, gpointer); //录入学生信息事件
void on_studentInfo_modify_clicked(GtkWidget *, gpointer); //修改学生信息事件
void on_studentInfo_delete_clicked(GtkWidget *); //删除学生信息事件
void reload_studentInfo_list(void); //重新学生信息列表


//界面辅助类函数
GdkPixbuf *create_pixbuf(const gchar *); //创建一个pixbuf
void warning_message_dialog(gchar *, gchar *); //警告信息弹窗界面
void error_message_dialog(gchar *, gchar *); //错误信息弹窗界面
void information_message_dialog(gchar *, gchar *); //一般信息弹窗界面
void addTreeColumnView(GtkWidget *, GtkCellRenderer *, char *, int); //在表格中增加一列
void setTableView(GtkWidget **, GtkWidget **, GtkWidget *); //设置table中的控件


//数据辅助类函数
int getAgeByBirthDay(char *); //通过生日得到年龄
char *strsub(char *, int, int); //得到给定字符串的子串
int vagueSearch(char *, char *); //模糊搜素字符串
int getGtkWidgetListLen(GtkWidget **); //得到一个GtkWidget数组的长度

#endif //COURSE_HEAD_H
