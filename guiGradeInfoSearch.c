//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "head.h"

enum {
    GRADENO_COLUMN,
    GRADE_TIME_COLUMN,
    GRADE_PEOPLE_COLUMN,
    GRADE_GRAD_COLUMN,
    GRADE_MENTORNA_COLUMN,
    GRADE_MENTORNO_COLUMN,
    GRADE_CHAIRNA_COLUMN,
    GRADE_CHAIRNO_COLUMN,
    GRADE_ADDRESS_COLUMN,
    GRADE_COLUMNS
};

/*************************************************
 @name: on_gradeInfo_no_search_clicked
 @function: called back when query-gradeInfo-by-No-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_gradeInfo_no_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按年级编号查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *gradeNoLabel = gtk_label_new("年级编号：");
    GtkWidget *gradeNoEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), gradeNoLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), gradeNoEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char gradeNo[8];
    strcpy(gradeNo, gtk_entry_get_text(GTK_ENTRY(gradeNoEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        GradeInfo node = searchGradeInfoByNo(head, gradeNo);
        run_gradeInfo_dialog(node);
    }
}


/*************************************************
 @name: on_gradeInfo_time_search_clicked
 @function: called back when query-gradeInfo-by-time-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_gradeInfo_time_search_clicked(GtkWidget *widget) {

    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按入学时间查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK,
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
        GradeInfo node;
        node = searchGradeInfoByTime(head, startdate, enddate);
        run_gradeInfo_dialog(node);
    }
}

/*************************************************
 @name: on_gradeInfo_inno_search_clicked
 @function: called back when query-gradeInfo-by-inNumber-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_gradeInfo_inno_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按入学人数查询", GTK_WINDOW(main_window), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    GtkWidget *minNoEntry = gtk_entry_new();
    GtkWidget *maxNoEntry = gtk_entry_new();
    GtkWidget *helperLabel = gtk_label_new("----");
    GtkWidget *minLabel = gtk_label_new("最小人数");
    GtkWidget *maxLabel = gtk_label_new("最大人数");

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
        GradeInfo node = searchGradeInfoByPeople(head, minNo, maxNo);
        run_gradeInfo_dialog(node);
    }
}

/*************************************************
 @name: run_gradeInfo_dialog
 @function:  Run a dialog containing a list view to display the information.
 @param node: the head of the information list
 @return none
*************************************************/
void run_gradeInfo_dialog(GradeInfo node) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *resultdialog = gtk_dialog_new_with_buttons("查询结果", GTK_WINDOW(main_window), GTK_DIALOG_MODAL,
                                                          GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE, NULL);
    gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
    gtk_widget_set_usize(GTK_WIDGET(resultdialog), 580, 360);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkListStore *store = gtk_list_store_new(GRADE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,
                                             G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_POINTER);
    GtkWidget *grade_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    GtkTreeIter iter;
    while ((node = node->next) != NULL) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, GRADENO_COLUMN, node->CSNo, GRADE_TIME_COLUMN, node->Year, GRADE_PEOPLE_COLUMN,
                           node->InNo, GRADE_GRAD_COLUMN, node->GraduateNo, GRADE_MENTORNA_COLUMN, node->MentorName,
                           GRADE_MENTORNO_COLUMN, node->MentorNo, GRADE_CHAIRNA_COLUMN, node->ChairmanName,
                           GRADE_CHAIRNO_COLUMN, node->ChairmanNo, GRADE_ADDRESS_COLUMN, node, -1);
    }
    g_object_unref(store);

    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    addTreeColumnView(grade_list, renderer, "年级编号", GRADENO_COLUMN);
    addTreeColumnView(grade_list, renderer, "入学时间", GRADE_TIME_COLUMN);
    addTreeColumnView(grade_list, renderer, "入学人数", GRADE_PEOPLE_COLUMN);
    addTreeColumnView(grade_list, renderer, "毕业人数", GRADE_GRAD_COLUMN);
    addTreeColumnView(grade_list, renderer, "年级辅导员姓名", GRADE_MENTORNA_COLUMN);
    addTreeColumnView(grade_list, renderer, "年级学生会主席姓名", GRADE_CHAIRNA_COLUMN);
    addTreeColumnView(grade_list, renderer, "年级辅导员电话", GRADE_MENTORNO_COLUMN);
    addTreeColumnView(grade_list, renderer, "年级学生会主席电话", GRADE_CHAIRNO_COLUMN);

    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), grade_list);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

    gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);


    gtk_widget_show_all(resultdialog);
    gtk_dialog_run(GTK_DIALOG(resultdialog));

    gtk_widget_destroy(resultdialog);
}