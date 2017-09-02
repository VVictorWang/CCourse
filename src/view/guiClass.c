//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//
#include "../head.h"

GtkWidget *classInfo_list;

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
    CLASS_GRADE_ADDRESS_COLUMN,
    CLASS_ADDRESS_COLUMN,
    CASE_COLUMNS
};


/*************************************************
 @name: classInfo_method
 @function: configure a window to display information(listview) about case.
 @return None
*************************************************/
void classInfo_method() {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_window_set_title(GTK_WINDOW(window), "班级信息管理");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_window_set_transient_for(GTK_WINDOW(window), GTK_WINDOW(main_window));
    gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
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

    GtkListStore *store = gtk_list_store_new(CASE_COLUMNS, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_INT,
                                             G_TYPE_FLOAT, G_TYPE_INT, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_POINTER,
                                             G_TYPE_POINTER);
    classInfo_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
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

    GtkWidget *hbox = gtk_hbox_new(FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), cancelbtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), deletebtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), modifybtn, FALSE, FALSE, 5);
    gtk_box_pack_end(GTK_BOX(hbox), addbtn, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 5);
    gtk_container_set_border_width(GTK_CONTAINER(vbox), 5);
    gtk_container_add(GTK_CONTAINER(window), vbox);

    g_signal_connect(G_OBJECT(addbtn), "clicked", G_CALLBACK(on_classInfo_add_clicked), window);
    g_signal_connect(G_OBJECT(modifybtn), "clicked", G_CALLBACK(on_classInfo_modify_clicked),
                     window);
    g_signal_connect(G_OBJECT(deletebtn), "clicked", G_CALLBACK(on_classInfo_delete_clicked), NULL);
    g_signal_connect(G_OBJECT(cancelbtn), "clicked", G_CALLBACK(on_cancel_clicked), window);

    reload_classInfo_list();

    gtk_widget_show_all(window);
}

/*************************************************
 @name: on_classInfo_add_clicked
 @function called back when add button clicked.Run a dialog for information adding.
 @param widget: the widget that activates the signal
 @param data: the window that passes
 @return None
*************************************************/
void on_classInfo_add_clicked(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("班级信息录入", GTK_WINDOW(data), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
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
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, "text",
                                   0, NULL);
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

    GtkWidget *labels[] = {classGradeNoLabel, classNoLabel, classMajorLabel, classInNoLabel,
                           classInAgeLabel,
                           classGradLabel, classMonitorNameLabel, classMonitorNoLabel,
                           classMentorNameLabel,
                           classMentorNoLabel, NULL};
    GtkWidget *entries[] = {classGradeNoCombo, classNoEntry, classMajorEntry, classInNoEntry,
                            classInAgeEntry,
                            classGradEntry, classMonitorNameEnrtry, classMonitorNoEntry,
                            classMentorNameEntry,
                            classMentorNoEntry, NULL};
    setTableView(labels, entries, dialog);

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
                } else if (testClassInfo(gtk_entry_get_text(GTK_ENTRY(classNoEntry)))) {
                    error_message_dialog("错误", "班级编号已存在");
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
                    const char *str[] = {
                            gtk_combo_box_get_active_text(GTK_COMBO_BOX(classGradeNoCombo)),
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
 @name: on_classInfo_modify_clicked
 @function: called back when modify button clicked.Run a dialog for information modifying.
 @param widget: the widget that activates the signal
 @param data: indicating the window that passes
 @return None
*************************************************/
void on_classInfo_modify_clicked(GtkWidget *widget, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode;
    ClassInfo classNode;
    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(classInfo_list))), &model,
            &iter)) {
        gtk_tree_model_get(model, &iter, CLASS_GRADE_ADDRESS_COLUMN, &gradeNode,
                           CLASS_ADDRESS_COLUMN, &classNode,
                           -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }

    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("班级信息修改", GTK_WINDOW(data), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
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
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(classGradeNoCombo), classGradeNoRenderer, "text",
                                   0, NULL);
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
    gtk_entry_set_text(GTK_ENTRY(classMajorEntry), classNode->Major);
    gtk_entry_set_text(GTK_ENTRY(classInNoEntry), inNo);
    gtk_entry_set_text(GTK_ENTRY(classInAgeEntry), age);
    gtk_entry_set_text(GTK_ENTRY(classGradEntry), graduateNo);
    gtk_entry_set_text(GTK_ENTRY(classMonitorNameEnrtry), classNode->MonitorName);
    gtk_entry_set_text(GTK_ENTRY(classMonitorNoEntry), classNode->MonitorNo);
    gtk_entry_set_text(GTK_ENTRY(classMentorNameEntry), classNode->MentorName);
    gtk_entry_set_text(GTK_ENTRY(classMentorNoEntry), classNode->MentorNo);

    GtkWidget *labels[] = {classGradeNoLabel, classNoLabel, classMajorLabel, classInNoLabel,
                           classInAgeLabel,
                           classGradLabel, classMonitorNameLabel, classMonitorNoLabel,
                           classMentorNameLabel,
                           classMentorNoLabel, NULL};
    GtkWidget *entries[] = {classGradeNoCombo, classNoEntry, classMajorEntry, classInNoEntry,
                            classInAgeEntry,
                            classGradEntry, classMonitorNameEnrtry, classMonitorNoEntry,
                            classMentorNameEntry,
                            classMentorNoEntry, NULL};
    setTableView(labels, entries, dialog);

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
                    const char *str[] = {
                            gtk_combo_box_get_active_text(GTK_COMBO_BOX(classGradeNoCombo)),
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
 @name: on_classInfo_delete_clicked
 @function: called back when delete button clicked. Delete certain case node.
 @param widget: the widget that activates the signal
 @return None
*************************************************/
void on_classInfo_delete_clicked(GtkWidget *widget) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode = NULL;
    ClassInfo classNode = NULL;
    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(classInfo_list))),
            &model, &iter)) {
        gtk_tree_model_get(model, &iter, CLASS_GRADE_ADDRESS_COLUMN, &gradeNode,
                           CLASS_ADDRESS_COLUMN, &classNode,
                           -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }
    deleteClassInfo(head, classNode->CNo);
    reload_classInfo_list();
}

/*************************************************
 @name: reload_classInfo_list
 @function reload all data, this usually because of the change of data such as adding, modifying and deleting data.
 @param none
 @return None
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
            gtk_list_store_set(store, &iter, CLASS_GRADENO_COLUMN, class_node->GradeNo,
                               CLASSNO_COLUMN,
                               class_node->CNo, CLASS_MAJOR_COLUMN, class_node->Major,
                               CLASS_INNO_COLUMN,
                               class_node->InNo, CLASS_AGE_COLUMN, class_node->AverageAge,
                               CLASS_GRAD_COLUMN,
                               class_node->GraduateNo, CLASS_MONITORNA_COLUMN,
                               class_node->MonitorName,
                               CLASS_MONITORNO_COLUMN, class_node->MonitorNo, CLASS_MENTORNA_COLUMN,
                               class_node->MentorName, CLASS_MENTORNO_COLUMN, class_node->MentorNo,
                               CLASS_GRADE_ADDRESS_COLUMN,
                               grade_node, CLASS_ADDRESS_COLUMN, class_node, -1);

            class_node = class_node->next;
        }
        grade_node = grade_node->next;
    }
}

