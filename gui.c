//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"

static GtkWidget *fixed;
static GtkWidget *notebook;
static GtkWidget *data, *query, *stastical;
static int state = 1;
static GtkWidget *dataview, *queryview, *stasticalview;
static GtkWidget *gradeInfo, *classInfo, *studentInfo;
static int data_type = 1;


/*************************************************
 @name: show_window
 @function: configure the main window
 @param pwindow: pointer to the window widget
 @return None
*************************************************/
void show_window(GtkWidget **pwindow) {
    GdkPixbuf *icon;
    GtkWidget *window;

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    *pwindow = window;
    gtk_window_set_title(GTK_WINDOW(window), "学生信息管理系统");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_usize(GTK_WIDGET(window), 960, 688);

    fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), fixed);

    icon = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    gtk_window_set_icon(GTK_WINDOW(window), icon);

    g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

    g_object_unref(icon), icon = NULL;

    show_menubar(window);
    show_sidebar();
    show_notebook();
    show_dataview();
    show_queryview();
    show_stasticalview();

    gtk_widget_show_all(window);
}

/*************************************************
 @name: show_menubar
 @function: configure the menu bar
 @param window:  main window
 @return None
*************************************************/
void show_menubar(GtkWidget *window) {
    GtkWidget *menubar_vbox;

    GtkWidget *menubar;

    GtkWidget *filemenu;
    GtkWidget *aboutmenu;

    GtkWidget *fileMi;
    GtkWidget *saveMi;
    GtkWidget *backupMi;
    GtkWidget *restoreMi;
    GtkWidget *quitMi;
    GtkWidget *aboutMi;
    GtkWidget *meMi;
    GtkWidget *systemMi;

    menubar_vbox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(fixed), menubar_vbox);
    gtk_widget_set_usize(menubar_vbox, 960, 20);

    menubar = gtk_menu_bar_new();
    filemenu = gtk_menu_new();
    aboutmenu = gtk_menu_new();

    fileMi = gtk_menu_item_new_with_label("文件");
    backupMi = gtk_menu_item_new_with_label("数据另存为");
    saveMi = gtk_menu_item_new_with_label("数据保存");
    restoreMi = gtk_menu_item_new_with_label("数据还原");
    quitMi = gtk_menu_item_new_with_label("退出");
    aboutMi = gtk_menu_item_new_with_label("关于");
    meMi = gtk_menu_item_new_with_label("关于作者");
    systemMi = gtk_menu_item_new_with_label("关于本系统");

    gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi), filemenu);
    gtk_menu_item_set_submenu(GTK_MENU_ITEM(aboutMi), aboutmenu);

    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), backupMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), saveMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), restoreMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), gtk_separator_menu_item_new());
    gtk_menu_shell_append(GTK_MENU_SHELL(filemenu), quitMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(aboutmenu), meMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(aboutmenu), systemMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(aboutmenu), gtk_separator_menu_item_new());

    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), fileMi);
    gtk_menu_shell_append(GTK_MENU_SHELL(menubar), aboutMi);
    gtk_box_pack_start(GTK_BOX(menubar_vbox), menubar, FALSE, FALSE, 0);

    g_signal_connect(G_OBJECT(backupMi), "activate", G_CALLBACK(on_backup_clicked), main_window);
    g_signal_connect(G_OBJECT(saveMi), "activate", G_CALLBACK(on_save_clicked), main_window);
    g_signal_connect(G_OBJECT(restoreMi), "activate", G_CALLBACK(on_restore_clicked), main_window);
    g_signal_connect(G_OBJECT(quitMi), "activate", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(G_OBJECT(systemMi), "activate", G_CALLBACK(on_aboutsystem_clicked), NULL);
    g_signal_connect(G_OBJECT(meMi), "activate", G_CALLBACK(on_aboutme_clicked), NULL);
}

/*************************************************
 @name: show_sidebar
 @function: configure the side bar
 @param None
 @return None
*************************************************/
void show_sidebar(void) {
    GtkWidget *sidebar_fixed = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(fixed), sidebar_fixed);

    GtkWidget *background = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/sidebar.png");
    gtk_widget_set_usize(background, 212, 670);
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), background, 0, 18);

    data = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/highlighted_data.png");
    GtkWidget *datalabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(datalabel), "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>数据维护</span>");
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), datalabel, 65, 224);
    GtkWidget *databox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(databox), FALSE);
    gtk_container_add(GTK_CONTAINER(databox), data);
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), databox, 26, 68);

    query = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/query.png");
    GtkWidget *querylabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(querylabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>数据查询</span>");
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), querylabel, 65, 404);
    GtkWidget *querybox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(querybox), FALSE);
    gtk_container_add(GTK_CONTAINER(querybox), query);
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), querybox, 26, 248);

    stastical = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/stastical.png");
    GtkWidget *stasticallabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(stasticallabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>数据统计</span>");
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), stasticallabel, 65, 584);
    GtkWidget *stasticalbox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(stasticalbox), FALSE);
    gtk_container_add(GTK_CONTAINER(stasticalbox), stastical);
    gtk_fixed_put(GTK_FIXED(sidebar_fixed), stasticalbox, 26, 428);

    g_signal_connect(databox, "button_press_event", G_CALLBACK(on_data_clicked), NULL);
    g_signal_connect(querybox, "button_press_event", G_CALLBACK(on_query_clicked), NULL);
    g_signal_connect(stasticalbox, "button_press_event", G_CALLBACK(on_stastical_clicked), NULL);

}

/*************************************************
 @Function: show_notebook
 @Description: configure the note book
 @param None
 @return None
*************************************************/
void show_notebook(void) {
    notebook = gtk_notebook_new();
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(notebook), FALSE);
    gtk_notebook_set_show_border(GTK_NOTEBOOK(notebook), FALSE);
    gtk_container_add(GTK_CONTAINER(fixed), notebook);
}

/*************************************************
 @name: show_dataview
 @function: configure the data view
 @param None
 @return None
*************************************************/
void show_dataview(void) {
    dataview = gtk_fixed_new();
    GtkWidget *typelabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(typelabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 19.5'>选择数据类型</span>");
    gtk_fixed_put(GTK_FIXED(dataview), typelabel, 505, 170);

    gradeInfo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/highlighted_province.png");
    GtkWidget *provincelabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(provincelabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>年级信息</span>");
    gtk_fixed_put(GTK_FIXED(dataview), provincelabel, 328, 335);
    GtkWidget *provincebox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(provincebox), FALSE);
    gtk_container_add(GTK_CONTAINER(provincebox), gradeInfo);
    gtk_fixed_put(GTK_FIXED(dataview), provincebox, 309, 221);

    classInfo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/studentInfo.png");
    GtkWidget *caselabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(caselabel), "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>班级信息</span>");
    gtk_fixed_put(GTK_FIXED(dataview), caselabel, 544, 335);
    GtkWidget *casebox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(casebox), FALSE);
    gtk_container_add(GTK_CONTAINER(casebox), classInfo);
    gtk_fixed_put(GTK_FIXED(dataview), casebox, 525, 221);

    studentInfo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/studentInfo.png");
    GtkWidget *medialabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(medialabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>学生信息</span>");
    gtk_fixed_put(GTK_FIXED(dataview), medialabel, 760, 335);
    GtkWidget *mediabox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(mediabox), FALSE);
    gtk_container_add(GTK_CONTAINER(mediabox), studentInfo);
    gtk_fixed_put(GTK_FIXED(dataview), mediabox, 741, 221);

    GtkWidget *confirm = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button1.png");
    GtkWidget *confirmbox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(confirmbox), FALSE);
    gtk_container_add(GTK_CONTAINER(confirmbox), confirm);
    gtk_fixed_put(GTK_FIXED(dataview), confirmbox, 479, 391);
    GtkWidget *confirmlabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(confirmlabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 19.5'>确认</span>");
    gtk_fixed_put(GTK_FIXED(dataview), confirmlabel, 559, 397);

    g_signal_connect(provincebox, "button_press_event", G_CALLBACK(on_grade_clicked), NULL);
    g_signal_connect(casebox, "button_press_event", G_CALLBACK(on_class_clicked), NULL);
    g_signal_connect(mediabox, "button_press_event", G_CALLBACK(on_student_clicked), NULL);
    g_signal_connect(confirmbox, "button_press_event", G_CALLBACK(on_confirm_clicked), NULL);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), dataview, NULL);
}

/*************************************************
 @name: show_queryview
 @function: configure the query view
 @param None
 @return None
*************************************************/
void show_queryview(void) {
    queryview = gtk_fixed_new();

    GtkWidget *gradeLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 19.5'>年级信息查询</span>");
    gtk_fixed_put(GTK_FIXED(queryview), gradeLabel, 223, 45);

    GtkWidget *gradeNo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *gradeNoBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(gradeNoBox), FALSE);
    gtk_container_add(GTK_CONTAINER(gradeNoBox), gradeNo);
    gtk_fixed_put(GTK_FIXED(queryview), gradeNoBox, 251, 97);
    GtkWidget *gradeNoLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeNoLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按年级编号查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), gradeNoLabel, 340, 107);

    GtkWidget *gradeInTime = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *gradeInTimeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(gradeInTimeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(gradeInTimeBox), gradeInTime);
    gtk_fixed_put(GTK_FIXED(queryview), gradeInTimeBox, 601, 97);
    GtkWidget *gradeInTimelabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeInTimelabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按入学时间查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), gradeInTimelabel, 658, 107);

    GtkWidget *gradeInNo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *gradeInNoBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(gradeInNoBox), FALSE);
    gtk_container_add(GTK_CONTAINER(gradeInNoBox), gradeInNo);
    gtk_fixed_put(GTK_FIXED(queryview), gradeInNoBox, 251, 165);
    GtkWidget *gradeInNoLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeInNoLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按入学人数查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), gradeInNoLabel, 340, 175);

    GtkWidget *classLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 19.5'>班级信息查询</span>");
    gtk_fixed_put(GTK_FIXED(queryview), classLabel, 223, 240);

    GtkWidget *classNo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *classNoBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(classNoBox), FALSE);
    gtk_container_add(GTK_CONTAINER(classNoBox), classNo);
    gtk_fixed_put(GTK_FIXED(queryview), classNoBox, 251, 292);
    GtkWidget *classNoLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classNoLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按班级编号查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), classNoLabel, 340, 302);

    GtkWidget *classMajor = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *classsMajorBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(classsMajorBox), FALSE);
    gtk_container_add(GTK_CONTAINER(classsMajorBox), classMajor);
    gtk_fixed_put(GTK_FIXED(queryview), classsMajorBox, 601, 292);
    GtkWidget *classMajorLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classMajorLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按专业查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), classMajorLabel, 638, 302);

    GtkWidget *classPeople = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *classPeopleBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(classPeopleBox), FALSE);
    gtk_container_add(GTK_CONTAINER(classPeopleBox), classPeople);
    gtk_fixed_put(GTK_FIXED(queryview), classPeopleBox, 251, 360);
    GtkWidget *classPeopleLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classPeopleLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按人数查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), classPeopleLabel, 340, 372);

    GtkWidget *classMentorName = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *classMentorNameBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(classMentorNameBox), FALSE);
    gtk_container_add(GTK_CONTAINER(classMentorNameBox), classMentorName);
    gtk_fixed_put(GTK_FIXED(queryview), classMentorNameBox, 601, 360);
    GtkWidget *classMentorNameLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classMentorNameLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按班主任姓名查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), classMentorNameLabel, 638, 372);

    GtkWidget *studentLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 19.5'>学生信息查询</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentLabel, 223, 430);

    GtkWidget *studentName = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentNameBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentNameBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentNameBox), studentName);
    gtk_fixed_put(GTK_FIXED(queryview), studentNameBox, 251, 482);
    GtkWidget *studentNameLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentNameLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生姓名查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentNameLabel, 288, 492);

    GtkWidget *studentMajor = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentMajorBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentMajorBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentMajorBox), studentMajor);
    gtk_fixed_put(GTK_FIXED(queryview), studentMajorBox, 601, 482);
    GtkWidget *studentMajorLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentMajorLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生专业查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentMajorLabel, 638, 492);

    GtkWidget *studentInTime = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentInTimeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentInTimeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentInTimeBox), studentInTime);
    gtk_fixed_put(GTK_FIXED(queryview), studentInTimeBox, 251, 550);
    GtkWidget *studentInTineLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentInTineLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生入学时间查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentInTineLabel, 288, 560);

    GtkWidget *studentAge = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentAgeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentAgeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentAgeBox), studentAge);
    gtk_fixed_put(GTK_FIXED(queryview), studentAgeBox, 601, 550);
    GtkWidget *studentAgeLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentAgeLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生年龄查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentAgeLabel, 638, 560);

    GtkWidget *studentIsGrad = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentIsGradBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentIsGradBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentIsGradBox), studentIsGrad);
    gtk_fixed_put(GTK_FIXED(queryview), studentIsGradBox, 251, 618);
    GtkWidget *studentIsGradLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentIsGradLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生毕业与否查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentIsGradLabel, 288, 628);

    GtkWidget *studentGradTo = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button2.png");
    GtkWidget *studentGradToBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentGradToBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentGradToBox), studentGradTo);
    gtk_fixed_put(GTK_FIXED(queryview), studentGradToBox, 601, 618);
    GtkWidget *studentGradToLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentGradToLabel),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按学生毕业去向查找</span>");
    gtk_fixed_put(GTK_FIXED(queryview), studentGradToLabel, 638, 628);

    g_signal_connect(G_OBJECT(gradeNoBox), "button_press_event", G_CALLBACK(on_gradeInfo_no_search_clicked), NULL);
    g_signal_connect(G_OBJECT(gradeInTimeBox), "button_press_event", G_CALLBACK(on_gradeInfo_time_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(gradeInNoBox), "button_press_event", G_CALLBACK(on_gradeInfo_inno_search_clicked), NULL);
    g_signal_connect(G_OBJECT(classNoBox), "button_press_event", G_CALLBACK(on_classInfo_no_search_clicked), NULL);
    g_signal_connect(G_OBJECT(classsMajorBox), "button_press_event", G_CALLBACK(on_classInfo_major_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(classPeopleBox), "button_press_event", G_CALLBACK(on_classInfo_peopleNo_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(classMentorNameBox), "button_press_event",
                     G_CALLBACK(on_classInfo_mentorName_search_clicked), NULL);
    g_signal_connect(G_OBJECT(studentNameBox), "button_press_event", G_CALLBACK(on_studentInfo_name_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(studentMajorBox), "button_press_event", G_CALLBACK(on_studentInfo_major_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(studentInTimeBox), "button_press_event", G_CALLBACK(on_studentInfo_Intime_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(studentAgeBox), "button_press_event", G_CALLBACK(on_studentInfo_age_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(studentIsGradBox), "button_press_event", G_CALLBACK(on_studentInfo_isGrad_search_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(studentGradToBox), "button_press_event",
                     G_CALLBACK(on_studentInfo_graduaTo_search_clicked),
                     NULL);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), queryview, NULL);
}

/*************************************************
 @name: show_stasticalview
 @function: configure the stastical view
 @param None
 @return None
*************************************************/
void show_stasticalview(void) {
    stasticalview = gtk_fixed_new();

    GtkWidget *gradeTimeLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeTimeLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>统计指定时间期限内各年级的班数、入学人数、毕业人数、未毕业人数。</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), gradeTimeLabel, 245, 70);
    GtkWidget *gradeTimeBtn = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button3.png");
    GtkWidget *gradeTimeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(gradeTimeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(gradeTimeBox), gradeTimeBtn);
    gtk_fixed_put(GTK_FIXED(stasticalview), gradeTimeBox, 623, 127);
    GtkWidget *gradeTimeTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(gradeTimeTitle),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按指定期限统计年级信息</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), gradeTimeTitle, 670, 136);

    GtkWidget *classTimeLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classTimeLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>统计指定时间期限内各班级未毕业学生人数，按未毕业学生人数从大到小排序</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), classTimeLabel, 245, 180);
    GtkWidget *classTimeBtn = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button3.png");
    GtkWidget *classTimeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(classTimeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(classTimeBox), classTimeBtn);
    gtk_fixed_put(GTK_FIXED(stasticalview), classTimeBox, 623, 237);
    GtkWidget *classTimeTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(classTimeTitle),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按指定期限统计班级信息</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), classTimeTitle, 670, 246);

    GtkWidget *studentTimeLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentTimeLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>统计指定时间期限内毕业后到某企业工作的学生数量，按人数从大到小排序</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), studentTimeLabel, 245, 290);
    GtkWidget *studentTimeBtn = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button3.png");
    GtkWidget *studentTimeBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentTimeBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentTimeBox), studentTimeBtn);
    gtk_fixed_put(GTK_FIXED(stasticalview), studentTimeBox, 623, 347);
    GtkWidget *studentTimeTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentTimeTitle),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按指定期限统计学生信息</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), studentTimeTitle, 670, 356);

    GtkWidget *studentBirthLabel = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentBirthLabel),
                         "<span foreground='#60646d' font_desc='Microsoft YaHei 15'>按年度统计从某年到某年每年出生的学生人数,按年度排序。</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), studentBirthLabel, 245, 400);
    GtkWidget *studentBirthBtn = gtk_image_new_from_file("/home/victor/CLionProjects/course/img/button3.png");
    GtkWidget *studentBirthBox = gtk_event_box_new();
    gtk_event_box_set_visible_window(GTK_EVENT_BOX(studentBirthBox), FALSE);
    gtk_container_add(GTK_CONTAINER(studentBirthBox), studentBirthBtn);
    gtk_fixed_put(GTK_FIXED(stasticalview), studentBirthBox, 623, 457);
    GtkWidget *studentBirthTitle = gtk_label_new("");
    gtk_label_set_markup(GTK_LABEL(studentBirthTitle),
                         "<span foreground='#FFFFF7' font_desc='Microsoft YaHei 15'>按年度统计学生信息</span>");
    gtk_fixed_put(GTK_FIXED(stasticalview), studentBirthTitle, 670, 466);


    g_signal_connect(G_OBJECT(gradeTimeBox), "button_press_event", G_CALLBACK(on_gradeInfo_stastical_clicked), NULL);
    g_signal_connect(G_OBJECT(classTimeBox), "button_press_event", G_CALLBACK(on_classInfo_stastical_clicked), NULL);
    g_signal_connect(G_OBJECT(studentTimeBox), "button_press_event", G_CALLBACK(on_studentInfo_stastical_clicked), NULL);
    g_signal_connect(G_OBJECT(studentBirthBox), "button_press_event", G_CALLBACK(on_student_stastical_by_year_clicked), NULL);

    gtk_notebook_append_page(GTK_NOTEBOOK(notebook), stasticalview, NULL);
}

/*************************************************
 @name: on_data_clicked
 @function: called back when data button on the side bar clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_data_clicked(GtkWidget *widget) {
    if (state != 1) {
        gtk_image_set_from_file(GTK_IMAGE(data), "/home/victor/CLionProjects/course/img/highlighted_data.png");
        gtk_image_set_from_file(GTK_IMAGE(query), "/home/victor/CLionProjects/course/img/query.png");
        gtk_image_set_from_file(GTK_IMAGE(stastical), "/home/victor/CLionProjects/course/img/stastical.png");
        if (state == 2) {
            gtk_notebook_prev_page(GTK_NOTEBOOK(notebook));
        } else if (state == 3) {
            gtk_notebook_prev_page(GTK_NOTEBOOK(notebook));
            gtk_notebook_prev_page(GTK_NOTEBOOK(notebook));
        }
        state = 1;
    }
}

/*************************************************
 @name: on_query_clicked
 @function: called back when query button on the side bar clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_query_clicked(GtkWidget *widget) {
    if (state != 2) {
        gtk_image_set_from_file(GTK_IMAGE(data), "/home/victor/CLionProjects/course/img/data.png");
        gtk_image_set_from_file(GTK_IMAGE(query), "/home/victor/CLionProjects/course/img/highlighted_query.png");
        gtk_image_set_from_file(GTK_IMAGE(stastical), "/home/victor/CLionProjects/course/img/stastical.png");
        if (state == 1) {
            gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
        } else if (state == 3) {
            gtk_notebook_prev_page(GTK_NOTEBOOK(notebook));
        }
        state = 2;
    }
}

/*************************************************
 @name: on_stastical_clicked
 @function: called back when stastical button on the side bar clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_stastical_clicked(GtkWidget *widget) {
    if (state != 3) {
        gtk_image_set_from_file(GTK_IMAGE(data), "/home/victor/CLionProjects/course/img/data.png");
        gtk_image_set_from_file(GTK_IMAGE(query), "/home/victor/CLionProjects/course/img/query.png");
        gtk_image_set_from_file(GTK_IMAGE(stastical),
                                "/home/victor/CLionProjects/course/img/highlighted_stastical.png");
        if (state == 1) {
            gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
            gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
        } else if (state == 2) {
            gtk_notebook_next_page(GTK_NOTEBOOK(notebook));
        }
        state = 3;
    }
}

/*************************************************
 @name: on_grade_clicked
 @function: called back when province button on the data view clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_grade_clicked(GtkWidget *widget) {
    if (data_type != 1) {
        gtk_image_set_from_file(GTK_IMAGE(gradeInfo), "/home/victor/CLionProjects/course/img/highlighted_province.png");
        gtk_image_set_from_file(GTK_IMAGE(classInfo), "/home/victor/CLionProjects/course/img/studentInfo.png");
        gtk_image_set_from_file(GTK_IMAGE(studentInfo), "/home/victor/CLionProjects/course/img/studentInfo.png");
        data_type = 1;
    }
}

/*************************************************
 @name: on_class_clicked
 @function: called back when case button on the data view clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_class_clicked(GtkWidget *widget) {
    if (data_type != 2) {
        gtk_image_set_from_file(GTK_IMAGE(gradeInfo), "/home/victor/CLionProjects/course/img/gradeInfo.png");
        gtk_image_set_from_file(GTK_IMAGE(classInfo), "/home/victor/CLionProjects/course/img/highlighted_case.png");
        gtk_image_set_from_file(GTK_IMAGE(studentInfo), "/home/victor/CLionProjects/course/img/studentInfo.png");
        data_type = 2;
    }
}

/*************************************************
 @name: on_student_clicked
 @function: called back when media button on the data view clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_student_clicked(GtkWidget *widget) {
    if (data_type != 3) {
        gtk_image_set_from_file(GTK_IMAGE(gradeInfo), "/home/victor/CLionProjects/course/img/gradeInfo.png");
        gtk_image_set_from_file(GTK_IMAGE(classInfo), "/home/victor/CLionProjects/course/img/studentInfo.png");
        gtk_image_set_from_file(GTK_IMAGE(studentInfo), "/home/victor/CLionProjects/course/img/highlighted_media.png");
        data_type = 3;
    }
}

/*************************************************
 @name: on_confirm_clicked
 @function: called back when confirm button on the data view clicked.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_confirm_clicked(GtkWidget *widget) {
    switch (data_type) {
        case 1:
            gradeInfo_method();
            break;
        case 2:
            classInfo_method();
            break;
        case 3:
            studentInfo_method();
            break;
    }
}

/*************************************************
 @name: on_backup_clicked
 @function: called back when backup Mi on the menu bar activated.
 @param widget: the widget that activates the signal
 @param data: the window that passes in
 @return None
*************************************************/
void on_backup_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    dialog = gtk_file_chooser_dialog_new("Save File",
                                         GTK_WINDOW(data),
                                         GTK_FILE_CHOOSER_ACTION_SAVE,
                                         GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                         GTK_STOCK_SAVE, GTK_RESPONSE_ACCEPT,
                                         NULL);

    char timestr[29];
    time_t result = time(NULL);
    strcpy(timestr, asctime(localtime(&result)));
    timestr[10] = '\0';
    strncat(timestr, ".txt", 4);

    gtk_file_chooser_set_do_overwrite_confirmation(GTK_FILE_CHOOSER (dialog), TRUE);
    gtk_file_chooser_set_current_name(GTK_FILE_CHOOSER (dialog), timestr);
    if (gtk_dialog_run(GTK_DIALOG (dialog)) == GTK_RESPONSE_ACCEPT) {
        char *filename;
        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (dialog));
        backup_data(head, filename);
        information_message_dialog("备份完成", "备份已完成。");
        g_free(filename);
    }

    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: on_backup_clicked
 @function: called back when backup Mi on the menu bar activated.
 @param widget: the widget that activates the signal
 @param data: the window that passes in
 @return None
*************************************************/
void on_save_clicked(GtkWidget *widget, gpointer data) {
    saveInfo(head);
    information_message_dialog("备份完成", "备份已完成。");
}

/*************************************************
 @name: on_restore_clicked
 @function: called back when restore Mi on the menu bar activated.
 @param widget: the widget that activates the signal
 @param data: the window that passes in
 @return None
*************************************************/
void on_restore_clicked(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/about.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("警告", GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *label = gtk_label_new("您确认要恢复数据吗？\n如果这么做的话，您会丢失当前所有的数据。");
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), label);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    switch (result) {
        case GTK_RESPONSE_OK: {
            GtkWidget *choosedialog;
            choosedialog = gtk_file_chooser_dialog_new("打开备份文件",
                                                       GTK_WINDOW(data),
                                                       GTK_FILE_CHOOSER_ACTION_OPEN,
                                                       GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                                       GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                                       NULL);

            if (gtk_dialog_run(GTK_DIALOG (choosedialog)) == GTK_RESPONSE_ACCEPT) {
                char *filename;
                filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER (choosedialog));
                int n = restore_data(&head, filename);
                if (n == -1) {
                    error_message_dialog("恢复失败", "打开文件失败");
                } else if (n == -2) {
                    error_message_dialog("恢复失败", "备份文件有误");
                } else if (n == 1) {
                    information_message_dialog("恢复成功", "成功恢复数据");
                }
                g_free(filename);
            }

            gtk_widget_destroy(choosedialog);
        }
            break;
    }
    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: on_aboutsystem_clicked
 @function: called back when about-system Mi on the menu bar activated.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_aboutsystem_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/about.png");
    GtkWidget *dialog = gtk_about_dialog_new();
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), "学生信息管理系统");
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), "V1.0");
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), "Chengyi Wang");
    gtk_about_dialog_set_comments(GTK_ABOUT_DIALOG(dialog), "本系统用来管理学校中年级、班级、学生的信息");
    gtk_about_dialog_set_logo(GTK_ABOUT_DIALOG(dialog), pixbuf);

    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    g_object_unref(pixbuf), pixbuf = NULL;

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: on_aboutme_clicked
 @funciton: called back when about-me Mi on the menu bar activated.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_aboutme_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/about.png");
    GtkWidget *dialog = gtk_message_dialog_new(NULL, GTK_DIALOG_MODAL, GTK_MESSAGE_OTHER, GTK_BUTTONS_OK,
                                               "华中科技大学 CS1609\nChengyi Wang\nchengyiwang@hustunique.com");

    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    gtk_window_set_title(GTK_WINDOW(dialog), "关于作者");
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER);

    g_object_unref(pixbuf), pixbuf = NULL;

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}


/*************************************************
 @name: on_cancel_clicked
 @function: called back when cancel button clicked
 @param widget: the widget that activates the signal
 @param data: the widget that passes in
 @return None
*************************************************/
void on_cancel_clicked(GtkWidget *widget, gpointer data) {
    gtk_widget_destroy(GTK_WIDGET(data));
}
