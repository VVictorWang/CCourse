#include "head.h"

GtkWidget *classInfo_list;

enum {
    CLASS_GRADENO_COLUMN, CLASSNO_COLUMN, CLASS_MAJOR_COLUMN, CLASS_INNO_COLUMN, CLASS_AGE_COLUMN, CLASS_GRAD_COLUMN,
    CLASS_MONITORNA_COLUMN, CLASS_MONITORNO_COLUMN, CLASS_MENTORNA_COLUMN, CLASS_MENTORNO_COLUMN,
    CLASS_GRADE_ADDRESS_COLUMN, CLASS_ADDRESS_COLUMN, CASE_COLUMNS
};


/*************************************************
Function: case_method
Description: configure a window to display information(listview) about case.
Input: None
Output: None
Return: None
Others: None
*************************************************/
void classInfo_method() {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_window_set_title(GTK_WINDOW(window), "班级信息管理");
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

    GtkListStore *store = gtk_list_store_new(CASE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_INT,
                                             G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_POINTER);
    classInfo_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    GtkTreeViewColumn *classGradeNoColumn = gtk_tree_view_column_new_with_attributes("所属年级编号", renderer, "text",
                                                                                     CLASS_GRADENO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classGradeNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classGradeNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classGradeNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classGradeNoColumn);

    GtkTreeViewColumn *classNoCloumn = gtk_tree_view_column_new_with_attributes("班级编号", renderer, "text",
                                                                                CLASSNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classNoCloumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classNoCloumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classNoCloumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classNoCloumn);

    GtkTreeViewColumn *classMajorColumn = gtk_tree_view_column_new_with_attributes("专业名称", renderer, "text",
                                                                                   CLASS_MAJOR_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classMajorColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classMajorColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classMajorColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classMajorColumn);

    GtkTreeViewColumn *classInNoColumn = gtk_tree_view_column_new_with_attributes("入学人数", renderer, "text",
                                                                                  CLASS_INNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classInNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classInNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classInNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classInNoColumn);

    GtkTreeViewColumn *classInAgeColumn = gtk_tree_view_column_new_with_attributes("入学平均年龄", renderer, "text",
                                                                                   CLASS_AGE_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classInAgeColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classInAgeColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classInAgeColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classInAgeColumn);

    GtkTreeViewColumn *classGradNoColumn = gtk_tree_view_column_new_with_attributes("毕业人数", renderer, "text",
                                                                                    CLASS_GRAD_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(classGradNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(classGradNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(classGradNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), classGradNoColumn);

    GtkTreeViewColumn *monitorNameColumn = gtk_tree_view_column_new_with_attributes("班长姓名", renderer, "text",
                                                                                    CLASS_MONITORNA_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(monitorNameColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(monitorNameColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(monitorNameColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), monitorNameColumn);

    GtkTreeViewColumn *monitorNoColumn = gtk_tree_view_column_new_with_attributes("班长联系电话", renderer, "text",
                                                                                  CLASS_MONITORNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(monitorNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(monitorNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(monitorNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), monitorNoColumn);

    GtkTreeViewColumn *mentorNameColumn = gtk_tree_view_column_new_with_attributes("班主任姓名", renderer, "text",
                                                                                   CLASS_MONITORNA_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(mentorNameColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(mentorNameColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(mentorNameColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), mentorNameColumn);

    GtkTreeViewColumn *mentorNoColumn = gtk_tree_view_column_new_with_attributes("班主任联系电话", renderer, "text",
                                                                                 CLASS_MENTORNO_COLUMN, NULL);
    gtk_tree_view_column_set_sizing(GTK_TREE_VIEW_COLUMN(mentorNoColumn), GTK_TREE_VIEW_COLUMN_GROW_ONLY);
    gtk_tree_view_column_set_resizable(GTK_TREE_VIEW_COLUMN(mentorNoColumn), TRUE);
    gtk_tree_view_column_set_expand(GTK_TREE_VIEW_COLUMN(mentorNoColumn), TRUE);
    gtk_tree_view_append_column(GTK_TREE_VIEW(classInfo_list), mentorNoColumn);

    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), classInfo_list);

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

    g_signal_connect(G_OBJECT(addbtn), "clicked", G_CALLBACK(on_classInfo_add_clicked), window);
    g_signal_connect(G_OBJECT(modifybtn), "clicked", G_CALLBACK(on_classInfo_modify_clicked), window);
    g_signal_connect(G_OBJECT(deletebtn), "clicked", G_CALLBACK(on_classInfo_delete_clicked), NULL);
    g_signal_connect(G_OBJECT(cancelbtn), "clicked", G_CALLBACK(on_cancel_clicked), window);

    reload_classInfo_list();

    gtk_widget_show_all(window);
}

/*************************************************
Function: on_case_add_clicked
Description: called back when add button clicked.Run a dialog for information adding.
Input: GtkWidget * indicating the widget that activates the signal
       gpointer data indicating the window that passes
Output: None
Return: None
Others: None
*************************************************/
void on_classInfo_add_clicked(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("班级信息录入", GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classGradeNoLabel = gtk_label_new("所属年级编号：");
    GtkWidget *classNoLabel = gtk_label_new("班级编号：");
    GtkWidget *classMajorLabel = gtk_label_new("专业名称：");
    GtkWidget *classInNoLabel = gtk_label_new("入学人数:");
    GtkWidget *classInAgeLabel = gtk_label_new("入学平均年龄：");
    GtkWidget *classGradLabel = gtk_label_new("毕业人数：");
    GtkWidget *classMonitorNameLabel = gtk_label_new("班长姓名：");
    GtkWidget *classMonitorNoLabel = gtk_label_new("班长联系电话：");
    GtkWidget *classMentorNameLabel = gtk_label_new("班主任姓名：");
    GtkWidget *classMentorNoLabel = gtk_label_new("班主任联系电话：");


    GtkListStore *classGradeNoStore = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeIter iter;
    GradeInfo node = head->next;
    while (node != NULL) {
        gtk_list_store_append(classGradeNoStore, &iter);
        gtk_list_store_set(classGradeNoStore, &iter, 0, node->CSNo, -1);
        node = node->next;
    }
    GtkWidget *classGradeNoCombo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(classGradeNoStore));
    g_object_unref(classGradeNoStore);
    GtkCellRenderer *classGradeNoRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(classGradeNoCombo), 0);

    GtkWidget *classNoEntry = gtk_entry_new();
    GtkWidget *classMajorEntry = gtk_entry_new();
    GtkWidget *classInNoEntry = gtk_entry_new();
    GtkWidget *classInAgeEntry = gtk_entry_new();
    GtkWidget *classGradEntry = gtk_entry_new();
    GtkWidget *classMonitorNameEnrtry = gtk_entry_new();
    GtkWidget *classMonitorNoEntry = gtk_entry_new();
    GtkWidget *classMentorNameEntry = gtk_entry_new();
    GtkWidget *classMentorNoEntry = gtk_entry_new();


    GtkWidget *table = gtk_table_new(10, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(table), classGradeNoLabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), classNoLabel, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), classMajorLabel, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), classInNoLabel, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), classInAgeLabel, 0, 1, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), classGradLabel, 0, 1, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNameLabel, 0, 1, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNoLabel, 0, 1, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNameLabel, 0, 1, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNoLabel, 0, 1, 9, 10);

    gtk_table_attach_defaults(GTK_TABLE(table), classGradeNoCombo, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), classNoEntry, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), classMajorEntry, 1, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), classInNoEntry, 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), classInAgeEntry, 1, 2, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), classGradEntry, 1, 2, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNameEnrtry, 1, 2, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNoEntry, 1, 2, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNameEntry, 1, 2, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNoEntry, 1, 2, 9, 10);

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
                if (gtk_combo_box_get_active(GTK_COMBO_BOX(classGradeNoCombo)) == -1) {
                    error_message_dialog("错误", "请先录入对应的年级信息");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classNoEntry)) == '\0') {
                    error_message_dialog("错误", "班级编号不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMajorEntry)) == '\0') {
                    error_message_dialog("错误", "班级所修的专业不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classInNoEntry)) == '\0') {
                    error_message_dialog("错误", "班级入学人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classInAgeEntry)) == '\0') {
                    error_message_dialog("错误", "班级入学平均年龄不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classGradEntry)) == '\0') {
                    error_message_dialog("错误", "班级毕业人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMonitorNameEnrtry)) == '\0') {
                    error_message_dialog("错误", "班长姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMonitorNoEntry)) == '\0') {
                    error_message_dialog("错误", "班长联系电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMentorNameEntry)) == '\0') {
                    error_message_dialog("错误", "班主任姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMentorNoEntry)) == '\0') {
                    error_message_dialog("错误", "班主任联系电话不能为空！");
                } else {
                    const char *str[] = {gtk_combo_box_get_active_text(GTK_COMBO_BOX(classGradeNoCombo)),
                                         gtk_entry_get_text(GTK_ENTRY(classNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMajorEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classInNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classInAgeEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classGradEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMonitorNameEnrtry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMonitorNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMentorNameEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMentorNoEntry))
                    };
                    inputClassInfo(head, str);
                    reload_classInfo_list();
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
Function: on_case_modify_clicked
Description: called back when modify button clicked.Run a dialog for information modifying.
Input: GtkWidget * indicating the widget that activates the signal
       gpointer data indicating the window that passes
Output: None
Return: None
Others: None
*************************************************/
void on_classInfo_modify_clicked(GtkWidget *widget, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode;
    ClassInfo classNode;
    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(classInfo_list))), &model, &iter)) {
        gtk_tree_model_get(model, &iter, CLASS_GRADE_ADDRESS_COLUMN, &gradeNode, CLASS_ADDRESS_COLUMN, &classNode,
                           -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }

    GdkPixbuf *pixbuf = create_pixbuf("img/icon.png");
    GtkWidget *dialog = gtk_dialog_new_with_buttons("班级信息修改", GTK_WINDOW(data), GTK_DIALOG_MODAL, GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *classGradeNoLabel = gtk_label_new("所属年级编号：");
    GtkWidget *classNoLabel = gtk_label_new("班级编号：");
    GtkWidget *classMajorLabel = gtk_label_new("专业名称：");
    GtkWidget *classInNoLabel = gtk_label_new("入学人数:");
    GtkWidget *classInAgeLabel = gtk_label_new("入学平均年龄：");
    GtkWidget *classGradLabel = gtk_label_new("毕业人数：");
    GtkWidget *classMonitorNameLabel = gtk_label_new("班长姓名：");
    GtkWidget *classMonitorNoLabel = gtk_label_new("班长联系电话：");
    GtkWidget *classMentorNameLabel = gtk_label_new("班主任姓名：");
    GtkWidget *classMentorNoLabel = gtk_label_new("班主任联系电话：");


    GtkListStore *classGradeNoStore = gtk_list_store_new(1, G_TYPE_STRING);
    GradeInfo node = head->next;
    GtkTreeIter iter_temp;
    while (node != NULL) {
        gtk_list_store_append(classGradeNoStore, &iter_temp);
        gtk_list_store_set(classGradeNoStore, &iter_temp, 0, node->CSNo, -1);
        node = node->next;
    }
    GtkWidget *classGradeNoCombo = gtk_combo_box_new_with_model(GTK_TREE_MODEL(classGradeNoStore));
    g_object_unref(classGradeNoStore);
    GtkCellRenderer *classGradeNoRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(classGradeNoCombo), 0);

    GtkWidget *classNoEntry = gtk_entry_new();
    GtkWidget *classMajorEntry = gtk_entry_new();
    GtkWidget *classInNoEntry = gtk_entry_new();
    GtkWidget *classInAgeEntry = gtk_entry_new();
    GtkWidget *classGradEntry = gtk_entry_new();
    GtkWidget *classMonitorNameEnrtry = gtk_entry_new();
    GtkWidget *classMonitorNoEntry = gtk_entry_new();
    GtkWidget *classMentorNameEntry = gtk_entry_new();
    GtkWidget *classMentorNoEntry = gtk_entry_new();

    //得到此班级所属的年级编号的index
    GradeInfo temp = head->next;
    int index = 0;
    while (temp != NULL) {
        if (strcmp(classNode->GradeNo, temp->CSNo) == 0) {
            break;
        }
        temp = temp->next;
        index++;
    }

    char inNo[8], age[8], graduateNo[8];
    snprintf(inNo, 8, "%d", classNode->InNo);
    snprintf(age, 8, "%f", classNode->AverageAge);
    snprintf(graduateNo, 8, "%d", classNode->GraduateNo);

    gtk_combo_box_set_active(GTK_COMBO_BOX(classGradeNoCombo), index);
    gtk_entry_set_text(GTK_ENTRY(classNoEntry), classNode->CNo);
    gtk_entry_set_text(GTK_ENTRY(classMajorEntry), classNode->FullName);
    gtk_entry_set_text(GTK_ENTRY(classInNoEntry), inNo);
    gtk_entry_set_text(GTK_ENTRY(classInAgeEntry), age);
    gtk_entry_set_text(GTK_ENTRY(classGradEntry), graduateNo);
    gtk_entry_set_text(GTK_ENTRY(classMonitorNameEnrtry), classNode->MonitorName);
    gtk_entry_set_text(GTK_ENTRY(classMonitorNoEntry), classNode->MonitorNo);
    gtk_entry_set_text(GTK_ENTRY(classMentorNameEntry), classNode->MentorName);
    gtk_entry_set_text(GTK_ENTRY(classMentorNoEntry), classNode->MentorNo);

    GtkWidget *table = gtk_table_new(10, 2, FALSE);

    gtk_table_attach_defaults(GTK_TABLE(table), classGradeNoLabel, 0, 1, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), classNoLabel, 0, 1, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), classMajorLabel, 0, 1, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), classInNoLabel, 0, 1, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), classInAgeLabel, 0, 1, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), classGradLabel, 0, 1, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNameLabel, 0, 1, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNoLabel, 0, 1, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNameLabel, 0, 1, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNoLabel, 0, 1, 9, 10);

    gtk_table_attach_defaults(GTK_TABLE(table), classGradeNoCombo, 1, 2, 0, 1);
    gtk_table_attach_defaults(GTK_TABLE(table), classNoEntry, 1, 2, 1, 2);
    gtk_table_attach_defaults(GTK_TABLE(table), classMajorEntry, 1, 2, 2, 3);
    gtk_table_attach_defaults(GTK_TABLE(table), classInNoEntry, 1, 2, 3, 4);
    gtk_table_attach_defaults(GTK_TABLE(table), classInAgeEntry, 1, 2, 4, 5);
    gtk_table_attach_defaults(GTK_TABLE(table), classGradEntry, 1, 2, 5, 6);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNameEnrtry, 1, 2, 6, 7);
    gtk_table_attach_defaults(GTK_TABLE(table), classMonitorNoEntry, 1, 2, 7, 8);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNameEntry, 1, 2, 8, 9);
    gtk_table_attach_defaults(GTK_TABLE(table), classMentorNoEntry, 1, 2, 9, 10);

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
                if (gtk_combo_box_get_active(GTK_COMBO_BOX(classGradeNoCombo)) == -1) {
                    error_message_dialog("错误", "请先录入对应的年级信息");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classNoEntry)) == '\0') {
                    error_message_dialog("错误", "班级编号不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMajorEntry)) == '\0') {
                    error_message_dialog("错误", "班级所修的专业不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classInNoEntry)) == '\0') {
                    error_message_dialog("错误", "班级入学人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classInAgeEntry)) == '\0') {
                    error_message_dialog("错误", "班级入学平均年龄不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classGradEntry)) == '\0') {
                    error_message_dialog("错误", "班级毕业人数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMonitorNameEnrtry)) == '\0') {
                    error_message_dialog("错误", "班长姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMonitorNoEntry)) == '\0') {
                    error_message_dialog("错误", "班长联系电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMentorNameEntry)) == '\0') {
                    error_message_dialog("错误", "班主任姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(classMentorNoEntry)) == '\0') {
                    error_message_dialog("错误", "班主任联系电话不能为空！");
                } else {
                    const char *str[] = {gtk_combo_box_get_active_text(GTK_COMBO_BOX(classGradeNoCombo)),
                                         gtk_entry_get_text(GTK_ENTRY(classNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMajorEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classInNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classInAgeEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classGradEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMonitorNameEnrtry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMonitorNoEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMentorNameEntry)),
                                         gtk_entry_get_text(GTK_ENTRY(classMentorNoEntry))
                    };
                    if (changeClassInfo(head, classNode->CNo, str) == 1) {
                        warning_message_dialog("修改成功", "原班级下的学生信息将丢失");
                    }
                    reload_classInfo_list();
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
Function: on_case_delete_clicked
Description: called back when delete button clicked. Delete certain case node.
Input: GtkWidget * indicating the widget that activates the signal
Output: None
Return: None
Others: None
*************************************************/
void on_classInfo_delete_clicked(GtkWidget *widget) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode = NULL;
    ClassInfo classNode = NULL;
    if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(classInfo_list))),
                                        &model, &iter)) {
        gtk_tree_model_get(model, &iter, CLASS_GRADE_ADDRESS_COLUMN, &gradeNode, CLASS_ADDRESS_COLUMN, &classNode,
                           -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }
    deleteClassInfo(head, classNode->CNo);
    reload_classInfo_list();
}

/*************************************************
Function: reload_case_list
Description: reload all data, this usually because of the change of data such as adding, modifying and deleting data.
Input: None
Output: None
Return: None
Others: None
*************************************************/
void reload_classInfo_list(void) {
    GtkListStore *store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(classInfo_list)));
    gtk_list_store_clear(store);
    GradeInfo grade_node = head->next;
    ClassInfo class_node = NULL;
    while (grade_node != NULL) {
        class_node = grade_node->Classes->next;
        while (class_node != NULL) {
            gtk_list_store_append(store, &iter);
            gtk_list_store_set(store, &iter, CLASS_GRADENO_COLUMN, class_node->GradeNo, CLASSNO_COLUMN,
                               class_node->CNo, CLASS_MAJOR_COLUMN, class_node->FullName, CLASS_INNO_COLUMN,
                               class_node->InNo, CLASS_AGE_COLUMN, class_node->AverageAge, CLASS_GRAD_COLUMN,
                               class_node->GraduateNo, CLASS_MONITORNA_COLUMN, class_node->MonitorName,
                               CLASS_MONITORNO_COLUMN, class_node->MonitorNo, CLASS_MENTORNA_COLUMN,
                               class_node->MentorName, CLASS_MENTORNO_COLUMN, class_node->MentorNo,
                               CLASS_GRADE_ADDRESS_COLUMN,
                               grade_node, CLASS_ADDRESS_COLUMN, class_node, -1);

            class_node = class_node->next;
        }
        grade_node = grade_node->next;
    }
}

