//
// Created by victor on 8/25/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

enum {
    STUDENT_GRADUATO,
    STUDENT_YEAR,
    STUDENT_COUNT,
    STUDENT_COLUMNS
};
enum {
    STUDENT_BIRTH_YEAR,
    STUDENT_COUNT_BY_YEAR,
    STUDENT_COLUMNS_BY_YEAR
};
StudentInfoByTime headStudent;
GtkWidget *student_list;

/*************************************************
 @name: on_studentInfo_stastical_clicked
 @function: called back when studentInfo-stastical-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_stastical_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按指定期限统计学生信息", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *startlabel = gtk_label_new("开始年份：");
    GtkWidget *endlabel = gtk_label_new("截止年份：");
    GtkWidget *startentry = gtk_entry_new();
    GtkWidget *endentry = gtk_entry_new();

    GtkWidget *labels[] = {startlabel, endlabel, NULL};
    GtkWidget *entries[] = {startentry, endentry, NULL};
    setTableView(labels, entries, dialog);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));
    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {
        headStudent = countStudentInfoByTime(startdate, enddate);
        headStudent = sortStudentInfoByTime(headStudent, 0);
        GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
        gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
        g_object_unref(pixbuf), pixbuf = NULL;
        gtk_window_set_title(GTK_WINDOW(window), "统计结果");
        gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
        gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(main_window));
        gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
        gtk_widget_set_usize(window, 640, 480);
        gtk_window_set_modal(GTK_WINDOW(window), TRUE);

        GtkWidget *sortLabel = gtk_label_new("排序方式");
        GtkWidget *closebtn = gtk_button_new_with_label("关闭");
        gtk_widget_set_usize(closebtn, 72, 24);

        GtkListStore *sortStore = gtk_list_store_new(1, G_TYPE_STRING);
        GtkTreeIter iter;
        gtk_list_store_append(sortStore, &iter);
        gtk_list_store_set(sortStore, &iter, 0, "按未毕业人数排序", -1);
        gtk_list_store_append(sortStore, &iter);
        GtkWidget *sortCombo = gtk_combo_box_new_with_model(
                GTK_TREE_MODEL(sortStore));
        g_object_unref(sortStore);
        GtkCellRenderer *classGradeNoRenderer = gtk_cell_renderer_text_new();
        gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(sortCombo), classGradeNoRenderer, TRUE);
        gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(sortCombo), classGradeNoRenderer,
                                       "text",
                                       0, NULL);
        gtk_combo_box_set_active(GTK_COMBO_BOX(sortCombo), 0);

        GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS, G_TYPE_STRING, G_TYPE_STRING,
                                                 G_TYPE_INT);
        student_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        StudentInfoByTime result = countStudentInfoByTime(startdate, enddate);
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, STUDENT_GRADUATO, result->GraduateTo, STUDENT_COUNT,
                           result->Count, -1);
        free(result);
        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        addTreeColumnView(student_list, renderer, "年份", STUDENT_YEAR);
        addTreeColumnView(student_list, renderer, "毕业去向", STUDENT_GRADUATO);
        addTreeColumnView(student_list, renderer, "学生数量", STUDENT_COUNT);

        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), student_list);

        GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
        GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
        gtk_box_pack_start(GTK_BOX(hbox), sortLabel, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(hbox), sortCombo, FALSE, FALSE, 5);
        gtk_box_pack_end(GTK_BOX(hbox), closebtn, FALSE, FALSE, 5);
        gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
        gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
        gtk_container_add(GTK_CONTAINER(window), vbox);
        gtk_widget_show_all(window);

        g_signal_connect(sortCombo, "changed",
                         G_CALLBACK(on_studentInfo_stastical_sortCombo_changed), NULL);
        g_signal_connect(G_OBJECT(closebtn), "clicked", G_CALLBACK(on_cancel_clicked), window);

        reload_studentInfo_byTime_list();
    }
}

/*************************************************
 @name: on_studentInfo_stastical_sortCombo_changed
 @function: called back when studentInfo-stastical-sortCombox changed. refresh the list.
 @param widget: the widget that activates the signal
 @param data: the window that passes in
 @return none
*************************************************/
void on_studentInfo_stastical_sortCombo_changed(GtkWidget *widget, gpointer data) {
    int slect = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
    headStudent = sortStudentInfoByTime(headStudent, slect);
    reload_studentInfo_byTime_list();
}

/*************************************************
 @name: reload_studentInfo_byTime_list
 @function: refresh the studentInfoByTime list.
 @param none
 @return none
*************************************************/
void reload_studentInfo_byTime_list() {
    GtkListStore *store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(student_list)));
    gtk_list_store_clear(store);
    StudentInfoByTime temp = headStudent->next;
    while (temp != NULL) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, STUDENT_YEAR, temp->Year, STUDENT_GRADUATO,
                           temp->GraduateTo,
                           STUDENT_COUNT,
                           temp->Count, -1);
        temp = temp->next;
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
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按年度统计学生信息", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *startlabel = gtk_label_new("开始年份：");
    GtkWidget *endlabel = gtk_label_new("截止年份：");
    GtkWidget *startentry = gtk_entry_new();
    GtkWidget *endentry = gtk_entry_new();

    GtkWidget *labels[] = {startlabel, endlabel, NULL};
    GtkWidget *entries[] = {startentry, endentry, NULL};
    setTableView(labels, entries, dialog);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    strcpy(startdate, gtk_entry_get_text(GTK_ENTRY(startentry)));
    strcpy(enddate, gtk_entry_get_text(GTK_ENTRY(endentry)));

    gtk_widget_destroy(dialog);

    if (resultcode == GTK_RESPONSE_OK) {

        GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
        GtkWidget *resultdialog = gtk_dialog_new_with_buttons("统计结果", GTK_WINDOW(main_window),
                                                              GTK_DIALOG_MODAL,
                                                              GTK_STOCK_CLOSE,
                                                              GTK_RESPONSE_CLOSE, NULL);
        gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
        gtk_widget_set_usize(GTK_WIDGET(resultdialog), 480, 360);
        g_object_unref(pixbuf), pixbuf = NULL;

        GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS_BY_YEAR, G_TYPE_STRING,
                                                 G_TYPE_INT);
        GtkWidget *charge_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
        GtkTreeIter iter;
        StudentInfoByYear result = countStudentInfoByYear(startdate, enddate);
        result = sortStudentInfoByYear(result);
        StudentInfoByYear temp = result->next;
        free(result);
        result = temp;
        while (result != NULL) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, STUDENT_BIRTH_YEAR, result->Year,
                               STUDENT_COUNT_BY_YEAR, result->Count,
                               -1);
            StudentInfoByYear temp1 = result->next;
            free(result);
            result = temp1;
        }

        free(result);
        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
        addTreeColumnView(charge_list, renderer, "年份", STUDENT_BIRTH_YEAR);
        addTreeColumnView(charge_list, renderer, "出生学生数量", STUDENT_COUNT_BY_YEAR);

        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
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
