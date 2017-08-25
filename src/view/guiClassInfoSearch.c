//
// Created by victor on 8/18/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"


enum {
    CLASS_GRADENO_COLUMN,
    CLASSNO_COLUMN,
    CLASS_MAJOR_COLUMN,
    CLASS_INNO_COLUMN,
    CLASS_AGE_COLUMN,
    CLASS_GRAD_COLUMN,
    CLASS_MONITORNA_COLUMN,
    CLASS_MONITORNO_COLUMN,
    CLASS_MENTORNA_COLUMN,
    CLASS_MENTORNO_COLUMN,
    CLASS_ADDRESS_COLUMN,
    CASE_COLUMNS
};

/*************************************************
 @name: on_classInfo_no_search_clicked
 @function: called back when query-classInfo-by-No-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_no_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按班级编号查询", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classNoLabel = gtk_label_new("班级编号：");
    GtkWidget *classNoEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classNoLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classNoEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char classNo[8];
    strcpy(classNo, gtk_entry_get_text(GTK_ENTRY(classNoEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_classInfo_dialog(searchClassInfoByNo(classNo));
    }
}

/*************************************************
 @name: on_classInfo_major_search_clicked
 @function: called back when query-classInfo-by-major-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_major_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按班级所修专业查询", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
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

    char major[12];
    strcpy(major, gtk_entry_get_text(GTK_ENTRY(classMajorEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_classInfo_dialog(searchClassInfoByMajor(major));
    }
}

/*************************************************
 @name: on_classInfo_peopleNo_search_clicked
 @function: called back when query-classInfo-by-People-Number-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_peopleNo_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按人数查询", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
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
        run_classInfo_dialog(searchClassInfoByPeople(minNo, maxNo));
    }
}

/*************************************************
 @name: on_classInfo_mentorName_search_clicked
 @function: called back when query-classInfo-by-mentorName-button clicked. Run a dialog containing a list view to display the information.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_classInfo_mentorName_search_clicked(GtkWidget *widget) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("按班级班主任姓名查询", GTK_WINDOW(main_window),
                                                    GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classMajorLabel = gtk_label_new("班主任姓名：");
    GtkWidget *classMajorEntry = gtk_entry_new();

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorLabel, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(hbox), classMajorEntry, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), hbox);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);

    gtk_widget_show_all(dialog);
    gint result = gtk_dialog_run(GTK_DIALOG(dialog));

    char mentorName[12];
    strcpy(mentorName, gtk_entry_get_text(GTK_ENTRY(classMajorEntry)));

    gtk_widget_destroy(dialog);

    if (result == GTK_RESPONSE_OK) {
        run_classInfo_dialog(searchClassInfoByMentorName(mentorName));
    }
}

/*************************************************
 @name: run_classInfo_dialog
 @function:  Run a dialog containing a list view to display the information.
 @param node: the head of the information list
 @return none
*************************************************/
void run_classInfo_dialog(ClassInfo node) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *resultdialog = gtk_dialog_new_with_buttons("查询结果", GTK_WINDOW(main_window),
                                                          GTK_DIALOG_MODAL,
                                                          GTK_STOCK_CLOSE, GTK_RESPONSE_CLOSE,
                                                          NULL);
    gtk_window_set_icon(GTK_WINDOW(resultdialog), pixbuf);
    gtk_widget_set_usize(GTK_WIDGET(resultdialog), 580, 360);
    g_object_unref(pixbuf), pixbuf = NULL;


    GtkListStore *store = gtk_list_store_new(CASE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_INT,
                                             G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER);
    GtkWidget *classInfo_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    GtkTreeIter iter;
    while ((node = node->next) != NULL) {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, CLASS_GRADENO_COLUMN, node->GradeNo, CLASSNO_COLUMN,
                           node->CNo, CLASS_MAJOR_COLUMN, node->Major, CLASS_INNO_COLUMN,
                           node->InNo, CLASS_AGE_COLUMN, node->AverageAge, CLASS_GRAD_COLUMN,
                           node->GraduateNo, CLASS_MONITORNA_COLUMN, node->MonitorName,
                           CLASS_MONITORNO_COLUMN, node->MonitorNo, CLASS_MENTORNA_COLUMN,
                           node->MentorName, CLASS_MENTORNO_COLUMN, node->MentorNo,
                           CLASS_ADDRESS_COLUMN, node, -1);
    }

    g_object_unref(store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    addTreeColumnView(classInfo_list, renderer, "所属年级编号", CLASS_GRADENO_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "班级编号", CLASSNO_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "专业名称", CLASS_MAJOR_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "入学人数", CLASS_INNO_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "入学平均年龄", CLASS_AGE_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "毕业人数", CLASS_GRAD_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "班长姓名", CLASS_MONITORNA_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "班长联系电话", CLASS_MONITORNO_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "班主任姓名", CLASS_MENTORNA_COLUMN);
    addTreeColumnView(classInfo_list, renderer, "班主任联系电话", CLASS_MENTORNO_COLUMN);

    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), classInfo_list);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(resultdialog)->vbox), vbox);

    gtk_window_set_position(GTK_WINDOW(resultdialog), GTK_WIN_POS_CENTER_ON_PARENT);


    gtk_widget_show_all(resultdialog);
    gtk_dialog_run(GTK_DIALOG(resultdialog));

    gtk_widget_destroy(resultdialog);
}