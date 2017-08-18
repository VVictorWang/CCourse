//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "head.h"


enum {
    GRADE_IN_TIME,
    GRADE_NO,
    GRADE_CLASS_COUNT,
    GRADE_IN_NUMBER,
    GRADE_GRADUATE_NO,
    GRADE_NOT_GRADUATE_NUMBER,
    GRADE_COLUMNS
};
enum {
    CLASS_IN_TIME,
    CLASS_NO,
    CLASS_UNGRADUATE_NO,
    CLASS_COLUMNS
};
enum {
    STUDENT_GRADUATO,
    STUDENT_COUNT,
    STUDENT_COLUMNS
};
enum {
    STUDENT_BIRTH_YEAR,
    STUDENT_COUNT_BY_YEAR,
    STUDENT_COLUMNS_BY_YEAR
};

/*************************************************
 @name: on_gradeInfo_stastical_clicked
 @function: called back when gradeInfo-stastical-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_gradeInfo_stastical_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按指定期限统计年级信息", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
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
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));

    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {

        GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
        GtkWidget *resuledialog = gtk_dialog_new_with_buttons("统计结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                              GTK_STOCK_CLOSE,
                                                              GTK_RESPONSE_CLOSE, NULL);
        gtk_window_set_icon(GTK_WINDOW(resuledialog), pixbuf);
        gtk_widget_set_usize(GTK_WIDGET(resuledialog), 480, 360);
        g_object_unref(pixbuf), pixbuf = NULL;

        GtkListStore *store = gtk_list_store_new(GRADE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT, G_TYPE_INT,
                                                 G_TYPE_INT, G_TYPE_INT);
        GtkWidget *charge_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        GtkTreeIter iter;

        GradeInfoByTime result = countGradeInfoByTime(startdate, enddate);
        GradeInfoByTime temp = result->next;
        free(result);
        result = temp;
        while (result != NULL) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, GRADE_IN_TIME, result->Year, GRADE_NO, result->CSNo, GRADE_CLASS_COUNT,
                               result->ClassCount, GRADE_IN_NUMBER, result->InNo, GRADE_GRADUATE_NO,
                               result->GraduatedCount,
                               GRADE_NOT_GRADUATE_NUMBER, result->UnGraduatedCount, -1);
            GradeInfoByTime temp1 = result->next;
            free(result);
            result = temp1;
        }

        free(result);

        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *inTimeColumn = gtk_tree_view_column_new_with_attributes("入学时间", renderer, "text",
                                                                                   GRADE_IN_TIME,
                                                                                   NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(inTimeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), inTimeColumn);

        GtkTreeViewColumn *gradeNoColumn = gtk_tree_view_column_new_with_attributes("年级编号", renderer, "text", GRADE_NO,
                                                                                    NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeNoColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeNoColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), gradeNoColumn);
        GtkTreeViewColumn *classCountColumn = gtk_tree_view_column_new_with_attributes("班级数目", renderer, "text",
                                                                                       GRADE_CLASS_COUNT, NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classCountColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classCountColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classCountColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), classCountColumn);

        GtkTreeViewColumn *inNoColumn = gtk_tree_view_column_new_with_attributes("入学人数", renderer, "text", GRADE_NO,
                                                                                 NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(inNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(inNoColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(inNoColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), inNoColumn);

        GtkTreeViewColumn *graduaCountColumn = gtk_tree_view_column_new_with_attributes("毕业人数", renderer, "text",
                                                                                        GRADE_GRADUATE_NO,
                                                                                        NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(graduaCountColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(graduaCountColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(graduaCountColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), graduaCountColumn);

        GtkTreeViewColumn *unGraduaCountColumn = gtk_tree_view_column_new_with_attributes("未毕业人数", renderer, "text",
                                                                                          GRADE_NOT_GRADUATE_NUMBER,
                                                                                          NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), unGraduaCountColumn);


        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), charge_list);

        GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resuledialog)->vbox), vbox);

        gtk_window_set_position(GTK_WINDOW(resuledialog), GTK_WIN_POS_CENTER_ON_PARENT);

        gtk_widget_show_all(resuledialog);
        gtk_dialog_run(GTK_DIALOG(resuledialog));

        gtk_widget_destroy(resuledialog);
    }
}

/*************************************************
 @name: on_classInfo_stastical_clicked
 @function: called back when classInfo-stastical-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_stastical_clicked(GtkWidget *widget) {

    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按指定期限统计班级信息", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
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
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));

    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {

        GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
        GtkWidget *resultdialog = gtk_dialog_new_with_buttons("统计结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                              GTK_STOCK_CLOSE,
                                                              GTK_RESPONSE_CLOSE, NULL);
        gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
        gtk_widget_set_usize(GTK_WIDGET(resultdialog), 480, 360);
        g_object_unref(pixbuf), pixbuf = NULL;

        GtkListStore *store = gtk_list_store_new(CLASS_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT);
        GtkWidget *charge_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        GtkTreeIter iter;
        ClassInfoByTime result = countClassInfoByTime(startdate, enddate);
        ClassInfoByTime temp = result->next;
        free(result);
        result = temp;
        while (result != NULL) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, CLASS_IN_TIME, result->Year, CLASS_NO, result->CNo, CLASS_UNGRADUATE_NO,
                               result->UnGraduateCount, -1);
            ClassInfoByTime temp1 = result->next;
            free(result);
            result = temp1;
        }

        free(result);

        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *inTimeColumn = gtk_tree_view_column_new_with_attributes("入学时间", renderer, "text",
                                                                                   CLASS_IN_TIME,
                                                                                   NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(inTimeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), inTimeColumn);

        GtkTreeViewColumn *classNoColumn = gtk_tree_view_column_new_with_attributes("班级编号", renderer, "text", CLASS_NO,
                                                                                    NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), classNoColumn);

        GtkTreeViewColumn *unGraduaCountColumn = gtk_tree_view_column_new_with_attributes("未毕业人数", renderer, "text",
                                                                                          CLASS_UNGRADUATE_NO, NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(unGraduaCountColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), unGraduaCountColumn);

        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), charge_list);

        GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

        gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);

        gtk_widget_show_all(resultdialog);
        gtk_dialog_run(GTK_DIALOG(resultdialog));

        gtk_widget_destroy(resultdialog);
    }
}


/*************************************************
 @name: on_studentInfo_stastical_clicked
 @function: called back when studentInfo-stastical-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_stastical_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按指定期限统计学生信息", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
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
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));

    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {

        GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
        GtkWidget *resultdialog = gtk_dialog_new_with_buttons("统计结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                              GTK_STOCK_CLOSE,
                                                              GTK_RESPONSE_CLOSE, NULL);
        gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
        gtk_widget_set_usize(GTK_WIDGET(resultdialog), 480, 360);
        g_object_unref(pixbuf), pixbuf = NULL;

        GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS, G_TYPE_STRING, G_TYPE_INT);
        GtkWidget *charge_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        GtkTreeIter iter;
        StudentInfoByTime result = countStudentInfoByTime(startdate, enddate);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, STUDENT_GRADUATO, result->GraduateTo, STUDENT_COUNT, result->Count, -1);
        free(result);
        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *inTimeColumn = gtk_tree_view_column_new_with_attributes("毕业去向", renderer, "text",
                                                                                   STUDENT_GRADUATO,
                                                                                   NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(inTimeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), inTimeColumn);

        GtkTreeViewColumn *classNoColumn = gtk_tree_view_column_new_with_attributes("学生数量", renderer, "text",
                                                                                    STUDENT_COUNT, NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), classNoColumn);

        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), charge_list);

        GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

        gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);

        gtk_widget_show_all(resultdialog);
        gtk_dialog_run(GTK_DIALOG(resultdialog));

        gtk_widget_destroy(resultdialog);
    }
}

/*************************************************
 @name: on_student_stastical_by_year_clicked
 @function: called back when studentInfo-by-year-stastical-button clicked.
            Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_student_stastical_by_year_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按年度统计学生信息", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *startlabel = gtk_label_new("开始年份：");
    GtkWidget *endlabel = gtk_label_new("截止年份：");
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
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));

    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {

        GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
        GtkWidget *resultdialog = gtk_dialog_new_with_buttons("统计结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                              GTK_STOCK_CLOSE,
                                                              GTK_RESPONSE_CLOSE, NULL);
        gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
        gtk_widget_set_usize(GTK_WIDGET(resultdialog), 480, 360);
        g_object_unref(pixbuf), pixbuf = NULL;

        GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS_BY_YEAR, G_TYPE_STRING, G_TYPE_INT);
        GtkWidget *charge_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        GtkTreeIter iter;
        StudentInfoByYear result = countStudentInfoByYear(startdate, enddate);

        StudentInfoByYear temp = result->next;
        free(result);
        result = temp;
        while (result != NULL) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, STUDENT_BIRTH_YEAR, result->Year, STUDENT_COLUMNS_BY_YEAR, result->Count,
                               -1);
            StudentInfoByYear temp1 = result->next;
            free(result);
            result = temp1;
        }

        free(result);
        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        GtkTreeViewColumn *inTimeColumn = gtk_tree_view_column_new_with_attributes("年份", renderer, "text",
                                                                                   STUDENT_BIRTH_YEAR,
                                                                                   NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(inTimeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(inTimeColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), inTimeColumn);

        GtkTreeViewColumn *classNoColumn = gtk_tree_view_column_new_with_attributes("出生学生数量", renderer, "text",
                                                                                    STUDENT_COUNT_BY_YEAR, NULL);
        gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
        gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classNoColumn), TRUE);
        gtk_tree_view_append_column(GTK_TREE_VIEW(charge_list), classNoColumn);

        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), charge_list);

        GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

        gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);

        gtk_widget_show_all(resultdialog);
        gtk_dialog_run(GTK_DIALOG(resultdialog));

        gtk_widget_destroy(resultdialog);
    }
}

