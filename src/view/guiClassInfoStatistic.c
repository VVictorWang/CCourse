//
// Created by victor on 8/25/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "../head.h"

enum {
    CLASS_IN_TIME,
    CLASS_NO,
    CLASS_UNGRADUATE_NO,
    CLASS_COLUMNS
};

ClassInfoByTime headClass;
GtkWidget *class_list;

/*************************************************
 @name: on_classInfo_stastical_clicked
 @function: called back when classInfo-stastical-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_stastical_clicked(GtkWidget *widget) {

    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按指定期限统计班级信息", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *startlabel = gtk_label_new("开始日期：");
    GtkWidget *endlabel = gtk_label_new("截止日期：");
    GtkWidget *startTimeCalendar = gtk_calendar_new();
    GtkWidget *endTimeCalendar = gtk_calendar_new();

    GtkWidget *labels[] = {startlabel, endlabel, NULL};
    GtkWidget *entries[] = {startTimeCalendar, endTimeCalendar, NULL};
    setTableView(labels, entries, dialog);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);

    gint resultcode = gtk_dialog_run(GTK_DIALOG(dialog));

    char startdate[10], enddate[10];
    unsigned int year = 0, month = 0, day = 0;
    gtk_calendar_get_date(GTK_CALENDAR(startTimeCalendar), &year, &month, &day);
    snprintf(startdate, 9, "%d", year * 10000 + (month + 1) * 100 + day);
    gtk_calendar_get_date(GTK_CALENDAR(endTimeCalendar), &year, &month, &day);
    snprintf(enddate, 9, "%d", year * 10000 + (month + 1) * 100 + day);
    gtk_widget_destroy(dialog);
    if (resultcode == GTK_RESPONSE_OK) {

        headClass = countClassInfoByTime(startdate, enddate);
        headClass = sortClassInfoByTime(headClass, 0);
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

        GtkListStore *store = gtk_list_store_new(CLASS_COLUMNS, G_TYPE_STRING, G_TYPE_STRING,
                                                 G_TYPE_INT);
        class_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));


        g_object_unref(store);

        GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

        addTreeColumnView(class_list, renderer, "入学时间", CLASS_IN_TIME);
        addTreeColumnView(class_list, renderer, "班级编号", CLASS_NO);
        addTreeColumnView(class_list, renderer, "未毕业人数", CLASS_UNGRADUATE_NO);


        GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
        gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC,
                                       GTK_POLICY_AUTOMATIC);
        gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), class_list);

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

        g_signal_connect(sortCombo, "changed", G_CALLBACK(on_classInfo_stastical_sortCombo_changed),
                         NULL);
        g_signal_connect(G_OBJECT(closebtn), "clicked", G_CALLBACK(on_cancel_clicked), window);
        reload_classInfo_byTime_list();

    }
}

/*************************************************
 @name: on_classInfo_stastical_sortCombo_changed
 @function: called back when classInfo-stastical-sortCombox changed. refresh the list.
 @param widget: the widget that activates the signal
 @param data: the window that passes in
 @return none
*************************************************/
void on_classInfo_stastical_sortCombo_changed(GtkWidget *widget, gpointer data) {
    int slect = gtk_combo_box_get_active(GTK_COMBO_BOX(widget));
    headClass = sortClassInfoByTime(headClass, slect);
    reload_gradeInfo_byTime_list();
}

/*************************************************
 @name: reload_classInfo_byTime_list
 @function: refresh the classInfoByTime list.
 @param none
 @return none
*************************************************/
void reload_classInfo_byTime_list() {
    GtkListStore *store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(class_list)));
    gtk_list_store_clear(store);
    ClassInfoByTime temp = headClass->next;
    while (temp != NULL) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, CLASS_IN_TIME, temp->Year, CLASS_NO, temp->CNo,
                           CLASS_UNGRADUATE_NO,
                           temp->UnGraduateCount, -1);
        temp = temp->next;
    }
}