//
// Created by victor on 8/17/17.
//


#include "head.h"

GtkWidget *grade_list;
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
 @name: gradeInfo_method
 @function: configure a window to display information(listview) about province.
 @param none
 @return none
*************************************************/
void gradeInfo_method(void) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_window_set_title(GTK_WINDOW(window), "年级信息管理");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(main_window));
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);
    gtk_widget_set_usize(window, 640, 480);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);

    GtkWidget *addbtn = gtk_button_new_with_label("录入");
    GtkWidget *modifybtn = gtk_button_new_with_label("修改");
    GtkWidget *deletebtn = gtk_button_new_with_label("删除");
    GtkWidget *cancelbtn = gtk_button_new_with_label("取消");
    gtk_widget_set_usize(addbtn, 72, 24);
    gtk_widget_set_usize(modifybtn, 72, 24);
    gtk_widget_set_usize(deletebtn, 72, 24);
    gtk_widget_set_usize(cancelbtn, 72, 24);

    GtkListStore *store = gtk_list_store_new(GRADE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,
                                             G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_POINTER);
    grade_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *gradeNoColumn = gtk_tree_view_column_new_with_attributes("年级编号", renderer, "text",
                                                                                GRADENO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeNoColumn);

    GtkTreeViewColumn *gradeTimeColumn = gtk_tree_view_column_new_with_attributes("入学时间", renderer, "text",
                                                                                  GRADE_TIME_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeTimeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeTimeColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeTimeColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeTimeColumn);

    GtkTreeViewColumn *gradePeopleColumn = gtk_tree_view_column_new_with_attributes("入学人数", renderer, "text",
                                                                                    GRADE_PEOPLE_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradePeopleColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradePeopleColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradePeopleColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradePeopleColumn);

    GtkTreeViewColumn *gradeGradColumn = gtk_tree_view_column_new_with_attributes("毕业人数", renderer, "text",
                                                                                  GRADE_GRAD_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeGradColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeGradColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeGradColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeGradColumn);

    GtkTreeViewColumn *gradeMentorNameColumn = gtk_tree_view_column_new_with_attributes("年级辅导员姓名", renderer, "text",
                                                                                        GRADE_MENTORNA_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeMentorNameColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeMentorNameColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeMentorNameColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeMentorNameColumn);

    GtkTreeViewColumn *gradeMentorNoColumn = gtk_tree_view_column_new_with_attributes("年级辅导员电话", renderer, "text",
                                                                                      GRADE_MENTORNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeMentorNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeMentorNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeMentorNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeMentorNoColumn);

    GtkTreeViewColumn *gradeChairmanNameColumn = gtk_tree_view_column_new_with_attributes("年级学生会主席姓名", renderer, "text",
                                                                                          GRADE_CHAIRNA_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeChairmanNameColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeChairmanNameColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeChairmanNameColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeChairmanNameColumn);

    GtkTreeViewColumn *gradeChairmanNoColumn = gtk_tree_view_column_new_with_attributes("年级学生会主席电话", renderer, "text",
                                                                                          GRADE_CHAIRNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(gradeChairmanNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(gradeChairmanNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(gradeChairmanNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(grade_list), gradeChairmanNoColumn);

    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), grade_list);

    GtkWidget *vbox = gtk_vbox_new(FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), scrolledwindow, TRUE, TRUE, 5);

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), cancelbtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), deletebtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), modifybtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), addbtn, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(G_OBJECT(addbtn), "clicked", G_CALLBACK(on_gradeInfo_add_clicked), window);
    g_signal_connect(G_OBJECT(modifybtn), "clicked", G_CALLBACK(on_gradeInfo_modify_clicked), window);
    g_signal_connect(G_OBJECT(deletebtn), "clicked", G_CALLBACK(on_gradeInfo_delete_clicked), NULL);
    g_signal_connect(G_OBJECT(cancelbtn), "clicked", G_CALLBACK(on_cancel_clicked), window);

    reload_gradeInfo_list();

    gtk_widget_show_all(window);
}

/*************************************************
 @name: on_gradeInfo_add_clicked
 @function: called back when add button clicked.Run a dialog for information adding.
 @param widget: the widget that activates the signal
 @param data: the window that passes
 @return none
*************************************************/
void on_gradeInfo_add_clicked(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = create_pixbuf("/home/victor/CLionProjects/course/img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("年级信息录入", GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *gradeNoLabel = gtk_label_new("年级编号：");
    GtkWidget *gradeTimeLabel = gtk_label_new("入学时间：");
    GtkWidget *gradePeopleLabel = gtk_label_new("入学人数：");
    GtkWidget *gradeGradLabel = gtk_label_new("毕业人数:");
    GtkWidget *gradeMentorNameLabel = gtk_label_new("年级辅导员姓名:");
    GtkWidget *gradeMentorNoLabel = gtk_label_new("年级辅导员电话:");
    GtkWidget *gradeChairmanNameLabel = gtk_label_new("年级学生会主席姓名:");
    GtkWidget *gradeChairmanNoLabel = gtk_label_new("年级学生会主席电话:");
    GtkWidget *gradeNoEntry = gtk_entry_new();
    GtkWidget *gradeTimeEntry = gtk_entry_new();
    GtkWidget *gradePeopleEntry = gtk_entry_new();
    GtkWidget *gradeGradEntry = gtk_entry_new();
    GtkWidget *gradeMentorNameEntry = gtk_entry_new();
    GtkWidget *gradeMentorNoEntry = gtk_entry_new();
    GtkWidget *gradeChairmanNameEntry = gtk_entry_new();
    GtkWidget *gradeChairmanNoEntry = gtk_entry_new();


    GtkWidget *table = gtk_table_new(8, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(table), gradeNoLabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeTimeLabel, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), gradePeopleLabel, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeGradLabel, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNameLabel, 0, 1, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNoLabel, 0, 1, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNameLabel, 0, 1, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNoLabel, 0, 1, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeNoEntry, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeTimeEntry, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), gradePeopleEntry, 1, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeGradEntry, 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNameEntry, 1, 2, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNoEntry, 1, 2, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNameEntry, 1, 2, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNoEntry, 1, 2, 7, 8);
    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(table), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), table);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);

    int error;
    do {
        error = 1;
        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        switch (result) {
            case GTK_RESPONSE_OK:
                if (*gtk_entry_get_text(GTK_ENTRY(gradeNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级编号不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeTimeEntry)) == '\0') {
                    error_message_dialog("错误", "入学时间不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradePeopleEntry)) == '\0') {
                    error_message_dialog("错误", "入学人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeGradEntry)) == '\0') {
                    error_message_dialog("错误", "毕业人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeMentorNameEntry)) == '\0') {
                    error_message_dialog("错误", "年级辅导员姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeMentorNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级辅导员电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeChairmanNameEntry)) == '\0') {
                    error_message_dialog("错误", "年级学生会主席姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeChairmanNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级学生会主席电话不能为空！");
                }
                else if (testGradeInfo(gtk_entry_get_text(GTK_ENTRY(gradeNoEntry))) == 1)
                {
                    error_message_dialog("错误","年级编号重复！");
                }
                else {
                    const char *str[] = {gtk_entry_get_text(GTK_ENTRY(gradeNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeTimeEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradePeopleEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeGradEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeMentorNameEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeMentorNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeChairmanNameEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(gradeChairmanNoEntry))
                    };
                    inputGradeInfo(head, str);
                    reload_gradeInfo_list();
                    error = 0;
                }
                break;
            default:
                error = 0;
                break;
        }
    } while (error != 0);

    gtk_widget_destroy(dialog);
}

/*************************************************
 @name: on_gradeInfo_modify_clicked
 @function called back when modify button clicked. Run a dialog for information modifying.
 @param widget: the widget that activates the signal
 @param data: the window that passes
 @return none
*************************************************/
void on_gradeInfo_modify_clicked(GtkWidget *widget, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel * model;
    GradeInfo node = NULL;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(grade_list))), &model, &iter)){
        gtk_tree_model_get(model, &iter, GRADE_ADDRESS_COLUMN, &node, -1);
    }
    else{
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }

    GdkPixbuf * pixbuf = create_pixbuf("img/icon.png");
    GtkWidget * dialog = gtk_dialog_new_with_buttons("省份监管信息维护", GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_STOCK_OK, GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *gradeNoLabel = gtk_label_new("年级编号：");
    GtkWidget *gradeTimeLabel = gtk_label_new("入学时间：");
    GtkWidget *gradePeopleLabel = gtk_label_new("入学人数：");
    GtkWidget *gradeGradLabel = gtk_label_new("毕业人数:");
    GtkWidget *gradeMentorNameLabel = gtk_label_new("年级辅导员姓名:");
    GtkWidget *gradeMentorNoLabel = gtk_label_new("年级辅导员电话:");
    GtkWidget *gradeChairmanNameLabel = gtk_label_new("年级学生会主席姓名:");
    GtkWidget *gradeChairmanNoLabel = gtk_label_new("年级学生会主席电话:");

    GtkWidget *gradeNoEntry = gtk_entry_new();
    GtkWidget *gradeTimeEntry = gtk_entry_new();
    GtkWidget *gradePeopleEntry = gtk_entry_new();
    GtkWidget *gradeGradEntry = gtk_entry_new();
    GtkWidget *gradeMentorNameEntry = gtk_entry_new();
    GtkWidget *gradeMentorNoEntry = gtk_entry_new();
    GtkWidget *gradeChairmanNameEntry = gtk_entry_new();
    GtkWidget *gradeChairmanNoEntry = gtk_entry_new();

    char inno[8],graduateNo[8];
    snprintf(inno, 8, "%d", node->InNo);
    snprintf(graduateNo, 8, "%d", node->GraduateNo);

    gtk_entry_set_text(GTK_ENTRY(gradeNoEntry), node->CSNo);
    gtk_entry_set_text(GTK_ENTRY(gradeTimeEntry), node->Year);
    gtk_entry_set_text(GTK_ENTRY(gradePeopleEntry), inno);
    gtk_entry_set_text(GTK_ENTRY(gradeGradEntry), graduateNo);
    gtk_entry_set_text(GTK_ENTRY(gradeMentorNameEntry), node->MentorName);
    gtk_entry_set_text(GTK_ENTRY(gradeMentorNoEntry), node->MentorNo);
    gtk_entry_set_text(GTK_ENTRY(gradeChairmanNameEntry), node->ChairmanName);
    gtk_entry_set_text(GTK_ENTRY(gradeChairmanNoEntry), node->ChairmanNo);

    GtkWidget *table = gtk_table_new(8, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(table), gradeNoLabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeTimeLabel, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), gradePeopleLabel, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeGradLabel, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNameLabel, 0, 1, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNoLabel, 0, 1, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNameLabel, 0, 1, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNoLabel, 0, 1, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeNoEntry, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeTimeEntry, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), gradePeopleEntry, 1, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeGradEntry, 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNameEntry, 1, 2, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeMentorNoEntry, 1, 2, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNameEntry, 1, 2, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), gradeChairmanNoEntry, 1, 2, 7, 8);
    gtk_table_set_row_spacings(GTK_TABLE(table), 5);
    gtk_table_set_col_spacings(GTK_TABLE(table), 5);
    gtk_container_set_border_width(GTK_CONTAINER(table), 5);
    gtk_box_pack_start_defaults(GTK_BOX(GTK_DIALOG(dialog)->vbox), table);
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);

    int error;
    do
    {
        error = 1;
        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        switch (result) {
            case GTK_RESPONSE_OK:
                if (*gtk_entry_get_text(GTK_ENTRY(gradeNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级编号不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeTimeEntry)) == '\0') {
                    error_message_dialog("错误", "入学时间不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradePeopleEntry)) == '\0') {
                    error_message_dialog("错误", "入学人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeGradEntry)) == '\0') {
                    error_message_dialog("错误", "毕业人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeMentorNameEntry)) == '\0') {
                    error_message_dialog("错误", "年级辅导员姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeMentorNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级辅导员电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeChairmanNameEntry)) == '\0') {
                    error_message_dialog("错误", "年级学生会主席姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(gradeChairmanNoEntry)) == '\0') {
                    error_message_dialog("错误", "年级学生会主席电话不能为空！");
                } else {
                    const char *str[] = {gtk_entry_get_text(GTK_ENTRY(gradeNoEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeTimeEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradePeopleEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeGradEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeMentorNameEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeMentorNoEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeChairmanNameEntry)),
                                   gtk_entry_get_text(GTK_ENTRY(gradeChairmanNoEntry))
                    };
                    if (changeGradeInfo(head, node->CSNo, str)==1) {
                        warning_message_dialog("修改成功", "原年级下的班级和学生信息将丢失！");
                    }

                    reload_gradeInfo_list();
                    error = 0;
                }
                break;
            default:
                error = 0;
                break;
        }
    } while (error != 0);

    gtk_widget_destroy(dialog);

}

/*************************************************
 @name: on_gradeInfo_delete_clicked
 @function: called back when delete button clicked. Delete certain media node.
 @param widget: indicating the widget that activates the signal
 @return none
*************************************************/
void on_gradeInfo_delete_clicked(GtkWidget *widget) {
    GtkTreeIter iter;
    GtkTreeModel * model;
    GradeInfo node = NULL;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(grade_list))), &model, &iter))
    {
        gtk_tree_model_get(model, &iter, GRADE_ADDRESS_COLUMN, &node, -1);
    } else
    {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }
    deleteGradeInfo(head, node->CSNo);
    reload_gradeInfo_list();
}

/*************************************************
 @name: reload_province_list
 @function: reload all data, this usually because of the change of data such as adding, modifying and deleting data.
 @param none
 @return none
*************************************************/
void reload_gradeInfo_list(void) {
    GtkListStore * store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(grade_list)));
    gtk_list_store_clear(store);
    GradeInfo node = head->next;
    while (node != NULL)
    {
        gtk_list_store_append(store, &iter);
        gtk_list_store_set(store, &iter, GRADENO_COLUMN, node->CSNo, GRADE_TIME_COLUMN, node->Year, GRADE_PEOPLE_COLUMN,
                           node->InNo, GRADE_GRAD_COLUMN,node->GraduateNo,GRADE_MENTORNA_COLUMN,node->MentorName,
                           GRADE_MENTORNO_COLUMN,node->MentorNo,GRADE_CHAIRNA_COLUMN,node->ChairmanName,
                           GRADE_CHAIRNO_COLUMN,node->ChairmanNo,GRADE_ADDRESS_COLUMN, node, -1);
        node = node->next;
    }
}

