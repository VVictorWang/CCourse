//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"

enum {
    STUDENT_CLASSNO_COLUMN,
    STUDENTNO_COLUMN,
    STUDENT_NAME_COLUMN,
    STUDENT_SEX_COLUMN,
    STUDENT_BIRTHPLACE_COLUMN,
    STUDENT_BIRTHDAY_COLUMN,
    STUDENT_NUMBER_COLUMN,
    STUDENT_INSCORE_COLUMN,
    STUDENT_ISGRAD_COLUMN,
    STUDENT_GRADUATETO_COLUMN,
    STUDENT_ADDRESS_COLUMN,
    STUDENT_COLUMNS
};


/*************************************************
 @name: on_studentInfo_name_search_clicked
 @function: called back when query-studentInfo-by-name-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_name_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按姓名查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classMajorLabel = gtk_label_new("学生姓名：");
    GtkWidget *classMajorEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char name[12];
    strcpy(name, gtk_entry_get_text(GTK_ENTRY(classMajorEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_studentInfo_dialog(searchStudentInfoByName(name));
    }
}


/*************************************************
 @name: on_studentInfo_major_search_clicked
 @function: called back when query-studentInfo-by-student-major-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_major_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按学生专业查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classMajorLabel = gtk_label_new("专业名称：");
    GtkWidget *classMajorEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char name[12];
    strcpy(name, gtk_entry_get_text(GTK_ENTRY(classMajorEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_studentInfo_dialog(searchStudentInfoByMajor(name));
    }
}

/*************************************************
 @name: on_studentInfo_Intime_search_clicked
 @function: called back when query-studentInfo-by-student-in-time-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_Intime_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按学生入学时间查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *startlabel = gtk_label_new("开始日期：");
    GtkWidget *endlabel = gtk_label_new("截止日期：");
    GtkWidget *startentry = gtk_entry_new();
    GtkWidget *endentry = gtk_entry_new();

    GtkWidget *table = gtk_table_new(2, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(table), startlabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), endlabel, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), startentry, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), endentry, 1, 2, 1, 2);

    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(table), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), table);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));
    gtk_widget_destroy(dialog);
    if (result == GTK_RESPONSE_OK) {
        run_studentInfo_dialog(searchStudentInfoByInTime(startdate, enddate));
    }
}

/*************************************************
 @name: on_gradeInfo_inno_search_clicked
 @function: called back when query-gradeInfo-by-inNumber-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_age_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按学生年龄查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    GtkWidget *minNoEntry = gtk_entry_new();
    GtkWidget *maxNoEntry = gtk_entry_new();
    GtkWidget *helperLabel = gtk_label_new("----");
    GtkWidget *minLabel = gtk_label_new("最小年龄");
    GtkWidget *maxLabel = gtk_label_new("最大年龄");

    GtkWidget *table = gtk_table_new(2, 3, FALSE);
    gtk_table_attach_defaults(GTK_TABLE(table), minLabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), maxLabel, 2, 3, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), minNoEntry, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), helperLabel, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), maxNoEntry, 2, 3, 1, 2);
    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(table), 3);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), table);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    char minNo[8], maxNo[8];
    strcpy(minNo, gtk_entry_get_text(GTK_ENTRY(minNoEntry)));
    strcpy(maxNo, gtk_entry_get_text(GTK_ENTRY(maxNoEntry)));
    gtk_widget_destroy(dialog);
    if (result == GTK_RESPONSE_OK) {
        run_studentInfo_dialog(searchStudentInfoByAge(minNo, maxNo));
    }
}


/*************************************************
 @name: on_studentInfo_isGrad_search_clicked
 @function: called back when query-gradeInfo-by-isGraduate-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_isGrad_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_window_set_title(GTK_WINDOW(window), "按毕业与否查询");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(main_window));
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_usize(window, 180, 120);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    GtkWidget *yesbtn = gtk_button_new_with_label("已经毕业");
    GtkWidget *nobtn = gtk_button_new_with_label("未毕业");
    gtk_widget_set_usize(yesbtn, 72, 24);
    gtk_widget_set_usize(nobtn, 72, 24);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), yesbtn, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), nobtn, FALSE, FALSE, 5);


    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);



    gtk_widget_show_all(window);
    g_signal_connect(G_OBJECT(yesbtn), "clicked", G_CALLBACK(on_studentInfo_Graduate_clicked),NULL);
    g_signal_connect(G_OBJECT(nobtn), "clicked", G_CALLBACK(on_studentInfo_not_Graduate_clicked),NULL);

}


/*************************************************
 @name: on_studentInfo_graduaTo_search_clicked
 @function: called back when query-studentInfo-by-student-graduaTo-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_graduaTo_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按学生毕业去向查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *studentGraduaToLabel = gtk_label_new("毕业去向：");
    GtkWidget *studentGraduaToEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), studentGraduaToLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), studentGraduaToEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char name[12];
    strcpy(name, gtk_entry_get_text(GTK_ENTRY(studentGraduaToEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_studentInfo_dialog(searchStudentInfoByGradTo(name));
    }
}


/*************************************************
 @name: on_studentInfo_Graduate_clicked
 @function: called back when is_graduate button clicked.Run a dialog for information adding.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_Graduate_clicked(GtkWidget *widget){
    run_studentInfo_dialog(searchStudentInfoGraduate('1'));
}


/*************************************************
 @name: on_studentInfo_not_Graduate_clicked
 @function: called back when not_graduate button clicked.Run a dialog for information adding.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_not_Graduate_clicked(GtkWidget *widget){
    run_studentInfo_dialog(searchStudentInfoGraduate('0'));
}

/*************************************************
 @name: run_studentInfo_dialog
 @function:  Run a dialog containing a list view to display the information.
 @param node: the head of the information list
 @return none
*************************************************/
void run_studentInfo_dialog(StudentInfo node) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *resultdialog = gtk_dialog_new_with_buttons("查询结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                          GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);
    gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
    gtk_widget_set_usize(GTK_WIDGET(resultdialog), 580, 360);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_FLOAT, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_POINTER);
    GtkWidget *student_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    GtkTreeIter iter;
    while ((node = node->next) != NULL) {
        char sex[4], isGraduated[4];
        if (node->sex == '1')
            strcpy(sex, "男");
        else
            strcpy(sex, "女");
        if (node->HasGraduated == '1')
            strcpy(isGraduated, "是");
        else
            strcpy(isGraduated, "否");

        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, STUDENT_CLASSNO_COLUMN, node->ClassNo, STUDENTNO_COLUMN,
                           node->CNo, STUDENT_NAME_COLUMN, node->Name, STUDENT_SEX_COLUMN,
                           sex, STUDENT_BIRTHPLACE_COLUMN, node->Birthplace, STUDENT_BIRTHDAY_COLUMN,
                           node->Birthday, STUDENT_NUMBER_COLUMN, node->Number,
                           STUDENT_INSCORE_COLUMN, node->InScore, STUDENT_ISGRAD_COLUMN, isGraduated,
                           STUDENT_GRADUATETO_COLUMN, node->GraduateTo,
                           STUDENT_ADDRESS_COLUMN, node, -1);
    }
    g_object_unref(store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    GtkTreeViewColumn *studentClassNoColumn = gtk_tree_view_column_new_with_attributes("所属班级编号", renderer, "text",
                                                                                       STUDENT_CLASSNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentClassNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentClassNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentClassNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentClassNoColumn);

    GtkTreeViewColumn *studentNoColumn = gtk_tree_view_column_new_with_attributes("学号", renderer, "text",
                                                                                  STUDENTNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentNoColumn);

    GtkTreeViewColumn *studentNameColumn = gtk_tree_view_column_new_with_attributes("姓名", renderer, "text",
                                                                                    STUDENT_NAME_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentNameColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentNameColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentNameColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentNameColumn);

    GtkTreeViewColumn *studentSexColumn = gtk_tree_view_column_new_with_attributes("性别", renderer, "text",
                                                                                   STUDENT_SEX_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentSexColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentSexColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentSexColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentSexColumn);

    GtkTreeViewColumn *studentBirthplaceColumn = gtk_tree_view_column_new_with_attributes("籍贯", renderer, "text",
                                                                                          STUDENT_BIRTHPLACE_COLUMN,
                                                                                          NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentBirthplaceColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentBirthplaceColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentBirthplaceColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentBirthplaceColumn);

    GtkTreeViewColumn *studentBirthdayColumn = gtk_tree_view_column_new_with_attributes("生日", renderer, "text",
                                                                                        STUDENT_BIRTHDAY_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentBirthdayColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentBirthdayColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentBirthdayColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentBirthdayColumn);

    GtkTreeViewColumn *studentNumberColumn = gtk_tree_view_column_new_with_attributes("联系电话", renderer, "text",
                                                                                      STUDENT_NUMBER_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentNumberColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentNumberColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentNumberColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentNumberColumn);

    GtkTreeViewColumn *studentInScoreColumn = gtk_tree_view_column_new_with_attributes("入学分数", renderer, "text",
                                                                                       STUDENT_INSCORE_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentInScoreColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentInScoreColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentInScoreColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentInScoreColumn);

    GtkTreeViewColumn *studentIsGradColumn = gtk_tree_view_column_new_with_attributes("已经毕业", renderer, "text",
                                                                                      STUDENT_ISGRAD_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentIsGradColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentIsGradColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentIsGradColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentIsGradColumn);

    GtkTreeViewColumn *studentGraduaToColumn = gtk_tree_view_column_new_with_attributes("毕业去向", renderer, "text",
                                                                                        STUDENT_GRADUATETO_COLUMN,
                                                                                        NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(studentGraduaToColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(studentGraduaToColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(studentGraduaToColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(student_list), studentGraduaToColumn);

    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), student_list);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

    gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);


    gtk_widget_show_all(resultdialog);
    gtk_dialog_run(GTK_DIALOG(resultdialog));

    gtk_widget_destroy(resultdialog);
}