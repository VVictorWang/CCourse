//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "../head.h"

GtkWidget *student_list;
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
    STUDENT_GRADE_ADDRESS_COLUMN,
    STUDENT_CLASS_ADDRESS_COLUMN,
    STUDENT_ADDRESS_COLUMN,
    STUDENT_COLUMNS
};


/*************************************************
 @name:  studentInfo_method
 @function: configure a window to display information(listview) about media.
 @param none
 @return none
*************************************************/
void studentInfo_method(void) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_icon(GTK_WINDOW(window), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;
    gtk_window_set_title(GTK_WINDOW(window), "学生信息管理");
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

    GtkListStore *store = gtk_list_store_new(STUDENT_COLUMNS, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING,
                                             G_TYPE_FLOAT, G_TYPE_STRING,
                                             G_TYPE_STRING, G_TYPE_POINTER, G_TYPE_POINTER,
                                             G_TYPE_POINTER);
    student_list = gtk_tree_view_new_with_model(GTK_TREE_MODEL(store));
    g_object_unref(store);
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();

    addTreeColumnView(student_list, renderer, "所属班级编号", STUDENT_CLASSNO_COLUMN);
    addTreeColumnView(student_list, renderer, "学号", STUDENTNO_COLUMN);
    addTreeColumnView(student_list, renderer, "姓名", STUDENT_NAME_COLUMN);
    addTreeColumnView(student_list, renderer, "性别", STUDENT_SEX_COLUMN);
    addTreeColumnView(student_list, renderer, "籍贯", STUDENT_BIRTHPLACE_COLUMN);
    addTreeColumnView(student_list, renderer, "生日", STUDENT_BIRTHDAY_COLUMN);
    addTreeColumnView(student_list, renderer, "联系电话", STUDENT_NUMBER_COLUMN);
    addTreeColumnView(student_list, renderer, "入学分数", STUDENT_INSCORE_COLUMN);
    addTreeColumnView(student_list, renderer, "已经毕业", STUDENT_ISGRAD_COLUMN);
    addTreeColumnView(student_list, renderer, "毕业去向", STUDENT_GRADUATETO_COLUMN);


    GtkWidget *scrolledwindow = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolledwindow), GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_scrolled_window_add_with_viewport(GTK_SCROLLED_WINDOW(scrolledwindow), student_list);

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

    g_signal_connect(G_OBJECT(addbtn), "clicked", G_CALLBACK(on_studentInfo_add_clicked), window);
    g_signal_connect(G_OBJECT(modifybtn), "clicked", G_CALLBACK(on_studentInfo_modify_clicked),
                     window);
    g_signal_connect(G_OBJECT(deletebtn), "clicked", G_CALLBACK(on_studentInfo_delete_clicked),
                     NULL);
    g_signal_connect(G_OBJECT(cancelbtn), "clicked", G_CALLBACK(on_cancel_clicked), window);

    reload_studentInfo_list();

    gtk_widget_show_all(window);
}

/*************************************************
 @name: on_studentInfo_add_clicked
 @function called back when add button clicked.Run a dialog for information adding.
 @param widget: the widget that activates the signal
 @param data: indicating the window that passes
 @return none
*************************************************/
void on_studentInfo_add_clicked(GtkWidget *widget, gpointer data) {
    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("学生信息录入", GTK_WINDOW(data), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *studentClassNoLabel = gtk_label_new("所属班级编号：");
    GtkWidget *studentNoLabel = gtk_label_new("学号：");
    GtkWidget *studentNameLabel = gtk_label_new("姓名：");
    GtkWidget *studentSexLabel = gtk_label_new("性别：");
    GtkWidget *studentBirthplaceLabel = gtk_label_new("籍贯：");
    GtkWidget *studentBirthdayLabel = gtk_label_new("生日：");
    GtkWidget *studentNumberLabel = gtk_label_new("联系电话：");
    GtkWidget *studentInScoreLabel = gtk_label_new("入学分数：");
    GtkWidget *studentIsGradLabel = gtk_label_new("已经毕业：");
    GtkWidget *studentGraduaToLabel = gtk_label_new("毕业去向：");

    GtkListStore *studentClassNoStore = gtk_list_store_new(1, G_TYPE_STRING);
    GtkTreeIter iter;
    GradeInfo node = head->next;
    while (node != NULL) {
        ClassInfo classNode = node->Classes->next;
        while (classNode != NULL) {
            gtk_list_store_append(studentClassNoStore, &iter);
            gtk_list_store_set(studentClassNoStore, &iter, 0, classNode->CNo, -1);
            classNode = classNode->next;
        }
        node = node->next;
    }
    GtkWidget *studentClassNoCombo = gtk_combo_box_new_with_model(
            GTK_TREE_MODEL(studentClassNoStore));
    g_object_unref(studentClassNoStore);
    GtkCellRenderer *studentClassNoRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(studentClassNoCombo), studentClassNoRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(studentClassNoCombo), studentClassNoRenderer,
                                   "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(studentClassNoCombo), 0);

    GtkWidget *studentNoEntry = gtk_entry_new();
    GtkWidget *studentNameEntry = gtk_entry_new();

    GtkWidget *hboxButton = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
    GtkWidget *manButton = gtk_radio_button_new_with_label(NULL, "男");
    GtkWidget *womanButton = gtk_radio_button_new_with_label_from_widget(
            GTK_RADIO_BUTTON(manButton), "女");
    gtk_box_pack_start(GTK_BOX(hboxButton), manButton, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hboxButton), womanButton, TRUE, TRUE, 1);

    GtkWidget *studentBirthplaceEntry = gtk_entry_new();
    GtkWidget *studentBirthdayCalendar = gtk_calendar_new();
    GtkWidget *studentNumberEntry = gtk_entry_new();
    GtkWidget *studentInScoreEntry = gtk_entry_new();

    GtkWidget *yesButton = gtk_check_button_new_with_label("是");


    GtkWidget *studentGraduaToEntry = gtk_entry_new();


    GtkWidget *labels[] = {studentClassNoLabel, studentNoLabel, studentNameLabel, studentSexLabel,
                           studentBirthplaceLabel, studentBirthdayLabel, studentNumberLabel,
                           studentInScoreLabel,
                           studentIsGradLabel, studentGraduaToLabel, NULL};

    GtkWidget *entries[] = {studentClassNoCombo, studentNoEntry, studentNameEntry, hboxButton,
                            studentBirthplaceEntry,
                            studentBirthdayCalendar, studentNumberEntry, studentInScoreEntry,
                            yesButton,
                            studentGraduaToEntry, NULL};
    setTableView(labels, entries, dialog);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);

    int error;
    do {
        error = 1;
        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        unsigned int year = 0, month = 0, day = 0;
        switch (result) {
            case GTK_RESPONSE_OK:
                gtk_calendar_get_date(GTK_CALENDAR(studentBirthdayCalendar), &year, &month, &day);
                if (gtk_combo_box_get_active(GTK_COMBO_BOX(studentClassNoCombo)) == -1) {
                    error_message_dialog("错误", "请先录入对应的年级信息！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNoEntry)) == '\0') {
                    error_message_dialog("错误", "学号不能为空！");
                } else if (testStudentInfo(gtk_entry_get_text(GTK_ENTRY(studentNoEntry)))) {
                    error_message_dialog("错误", "学号已存在");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNameEntry)) == '\0') {
                    error_message_dialog("错误", "学生姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentBirthplaceEntry)) == '\0') {
                    error_message_dialog("错误", "学生籍贯不能为空！");
                } else if (year == 0 || month == 0 || day == 0) {
                    error_message_dialog("错误", "学生生日不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNumberEntry)) == '\0') {
                    error_message_dialog("错误", "学生联系电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentInScoreEntry)) == '\0') {
                    error_message_dialog("错误", "学生入学分数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentGraduaToEntry)) == '\0') {
                    error_message_dialog("错误", "学生毕业去向不能为空！");
                } else {
                    char sex, isGraduated;
                    if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(manButton)) == TRUE) {
                        sex = '1';
                    } else
                        sex = '0';
                    if (gtk_toggle_button_get_active(GTK_CHECK_BUTTON(yesButton)) == TRUE)
                        isGraduated = '1';
                    else
                        isGraduated = '0';
                    char time[9];
                    snprintf(time, 9, "%d", year * 10000 + (month + 1) * 100 + day);
                    const char *str[] = {
                            gtk_combo_box_get_active_text(GTK_COMBO_BOX(studentClassNoCombo)),
                            gtk_entry_get_text(GTK_ENTRY(studentNoEntry)),
                            gtk_entry_get_text(GTK_ENTRY(studentNameEntry)),
                            &sex,
                            gtk_entry_get_text(GTK_ENTRY(studentBirthplaceEntry)),
                            time,
                            gtk_entry_get_text(GTK_ENTRY(studentNumberEntry)),
                            gtk_entry_get_text(GTK_ENTRY(studentInScoreEntry)),
                            &isGraduated,
                            gtk_entry_get_text(GTK_ENTRY(studentGraduaToEntry))
                    };
                    inputStudentInfo(head, str);
                    reload_studentInfo_list();
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
 @name: on_studentInfo_modify_clicked
 @function called back when modify button clicked. Run a dialog for information modifying.
 @param widget： the widget that activates the signal
 @param data: the window that passes
 @return none
*************************************************/
void on_studentInfo_modify_clicked(GtkWidget *widget, gpointer data) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode;
    ClassInfo classNode;
    StudentInfo studentNode;
    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(student_list))),
            &model, &iter)) {
        gtk_tree_model_get(model, &iter, STUDENT_GRADE_ADDRESS_COLUMN, &gradeNode,
                           STUDENT_CLASS_ADDRESS_COLUMN,
                           &classNode, STUDENT_ADDRESS_COLUMN, &studentNode, -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }

    GdkPixbuf *pixbuf = create_pixbuf(MYIMAGEPATH.iconPath);
    GtkWidget *dialog = gtk_dialog_new_with_buttons("学生信息修改", GTK_WINDOW(data), GTK_DIALOG_MODAL,
                                                    GTK_STOCK_OK,
                                                    GTK_RESPONSE_OK, GTK_STOCK_CANCEL,
                                                    GTK_RESPONSE_CANCEL, NULL);
    gtk_window_set_icon(GTK_WINDOW(dialog), pixbuf);
    g_object_unref(pixbuf), pixbuf = NULL;

    GtkWidget *studentClassNoLabel = gtk_label_new("所属班级编号：");
    GtkWidget *studentNoLabel = gtk_label_new("学号：");
    GtkWidget *studentNameLabel = gtk_label_new("姓名：");
    GtkWidget *studentSexLabel = gtk_label_new("性别：");
    GtkWidget *studentBirthplaceLabel = gtk_label_new("籍贯：");
    GtkWidget *studentBirthdayLabel = gtk_label_new("生日：");
    GtkWidget *studentNumberLabel = gtk_label_new("联系电话：");
    GtkWidget *studentInScoreLabel = gtk_label_new("入学分数：");
    GtkWidget *studentIsGradLabel = gtk_label_new("已经毕业：");
    GtkWidget *studentGraduaToLabel = gtk_label_new("毕业去向：");

    GtkListStore *studentClassNoStore = gtk_list_store_new(1, G_TYPE_STRING);
    GradeInfo node = head->next;
    while (node != NULL) {
        ClassInfo classNode = node->Classes->next;
        while (classNode != NULL) {
            gtk_list_store_append(studentClassNoStore, &iter);
            gtk_list_store_set(studentClassNoStore, &iter, 0, classNode->CNo, -1);
            classNode = classNode->next;
        }
        node = node->next;
    }
    GtkWidget *studentClassNoCombo = gtk_combo_box_new_with_model(
            GTK_TREE_MODEL(studentClassNoStore));
    g_object_unref(studentClassNoStore);
    GtkCellRenderer *studentClassNoRenderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(studentClassNoCombo), studentClassNoRenderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(studentClassNoCombo), studentClassNoRenderer,
                                   "text", 0, NULL);
    gtk_combo_box_set_active(GTK_COMBO_BOX(studentClassNoCombo), 0);

    GtkWidget *studentNoEntry = gtk_entry_new();
    GtkWidget *studentNameEntry = gtk_entry_new();


    GtkWidget *hboxButton = gtk_hbox_new(GTK_ORIENTATION_HORIZONTAL, 3);
    GtkWidget *manButton = gtk_radio_button_new_with_label(NULL, "男");
    GtkWidget *womanButton = gtk_radio_button_new_with_label_from_widget(
            GTK_RADIO_BUTTON(manButton), "女");
    gtk_box_pack_start(GTK_BOX(hboxButton), manButton, TRUE, TRUE, 1);
    gtk_box_pack_start(GTK_BOX(hboxButton), womanButton, TRUE, TRUE, 1);

    GtkWidget *studentBirthplaceEntry = gtk_entry_new();
    GtkWidget *studentBirthdayCalendar = gtk_calendar_new();
    GtkWidget *studentNumberEntry = gtk_entry_new();
    GtkWidget *studentInScoreEntry = gtk_entry_new();

    GtkWidget *yesButton = gtk_check_button_new_with_label("是");

    GtkWidget *studentGraduaToEntry = gtk_entry_new();

    //得到此学生所属的班级编号的index
    GradeInfo temp = head->next;
    int index = 0, flag = 0;
    while (temp != NULL) {
        ClassInfo classTemp = temp->Classes->next;
        while (classTemp != NULL) {
            if (strcmp(studentNode->ClassNo, classTemp->CNo) == 0) {
                flag = 1;
                break;
            }
            classTemp = classTemp->next;
        }
        if (flag)
            break;
        temp = temp->next;
        index++;
    }
    gtk_combo_box_set_active(GTK_COMBO_BOX(studentClassNoCombo), index);

    if (studentNode->sex == '1')
        gtk_toggle_button_set_active(GTK_RADIO_BUTTON(manButton), TRUE);
    else
        gtk_toggle_button_set_active(GTK_RADIO_BUTTON(womanButton), TRUE);

    if (studentNode->HasGraduated == '1')
        gtk_toggle_button_set_active(GTK_CHECK_BUTTON(yesButton), TRUE);
    else if (studentNode->HasGraduated == '0')
        gtk_toggle_button_set_active(GTK_CHECK_BUTTON(yesButton), FALSE);

    char inScore[8];
    snprintf(inScore, 8, "%f", studentNode->InScore);

    unsigned int year = (unsigned int) atoi(strsub(studentNode->Birthday, 0, 4));
    unsigned int month = (unsigned int) atoi(strsub(studentNode->Birthday, 4, 6));
    unsigned int day = (unsigned int) atoi(strsub(studentNode->Birthday, 6, 8));
    gtk_calendar_select_month(GTK_CALENDAR(studentBirthdayCalendar), month - 1, year);
    gtk_calendar_select_day(GTK_CALENDAR(studentBirthdayCalendar), day);

    gtk_entry_set_text(GTK_ENTRY(studentNoEntry), studentNode->CNo);
    gtk_entry_set_text(GTK_ENTRY(studentNameEntry), studentNode->Name);
    gtk_entry_set_text(GTK_ENTRY(studentBirthplaceEntry), studentNode->Birthplace);
    gtk_entry_set_text(GTK_ENTRY(studentNumberEntry), studentNode->Number);
    gtk_entry_set_text(GTK_ENTRY(studentInScoreEntry), inScore);
    gtk_entry_set_text(GTK_ENTRY(studentGraduaToEntry), studentNode->GraduateTo);

    GtkWidget *labels[] = {studentClassNoLabel, studentNoLabel, studentNameLabel, studentSexLabel,
                           studentBirthplaceLabel, studentBirthdayLabel, studentNumberLabel,
                           studentInScoreLabel,
                           studentIsGradLabel, studentGraduaToLabel, NULL};

    GtkWidget *entries[] = {studentClassNoCombo, studentNoEntry, studentNameEntry, hboxButton,
                            studentBirthplaceEntry,
                            studentBirthdayCalendar, studentNumberEntry, studentInScoreEntry,
                            yesButton,
                            studentGraduaToEntry, NULL};
    setTableView(labels, entries, dialog);

    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    gtk_widget_show_all(dialog);

    int error;
    do {
        error = 1;
        gint result = gtk_dialog_run(GTK_DIALOG(dialog));
        switch (result) {
            case GTK_RESPONSE_OK:
                year = 0, month = 0, day = 0;
                gtk_calendar_get_date(GTK_CALENDAR(studentBirthdayCalendar), &year, &month, &day);
                if (gtk_combo_box_get_active(GTK_COMBO_BOX(studentClassNoCombo)) == -1) {
                    error_message_dialog("错误", "请先录入对应的年级信息！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNoEntry)) == '\0') {
                    error_message_dialog("错误", "学号不能为空！");
                } else if (testStudentInfo(gtk_entry_get_text(GTK_ENTRY(studentNoEntry)))) {
                    error_message_dialog("错误", "学号已存在");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNameEntry)) == '\0') {
                    error_message_dialog("错误", "学生姓名不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentBirthplaceEntry)) == '\0') {
                    error_message_dialog("错误", "学生籍贯不能为空！");
                } else if (year == 0 || month == 0 || day == 0) {
                    error_message_dialog("错误", "学生生日不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentNumberEntry)) == '\0') {
                    error_message_dialog("错误", "学生联系电话不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentInScoreEntry)) == '\0') {
                    error_message_dialog("错误", "学生入学分数不能为空！");
                } else if (*gtk_entry_get_text(GTK_ENTRY(studentGraduaToEntry)) == '\0') {
                    error_message_dialog("错误", "学生毕业去向不能为空！");
                } else {
                    char sex, isGraduated;
                    if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON(manButton)) == TRUE) {
                        sex = '1';
                    } else
                        sex = '0';
                    if (gtk_toggle_button_get_active(GTK_CHECK_BUTTON(yesButton)) == TRUE)
                        isGraduated = '1';
                    else
                        isGraduated = '0';
                    char time[9];
                    snprintf(time, 9, "%d", year * 10000 + (month + 1) * 100 + day);
                    const char *str[] = {
                            gtk_combo_box_get_active_text(GTK_COMBO_BOX(studentClassNoCombo)),
                            gtk_entry_get_text(GTK_ENTRY(studentNoEntry)),
                            gtk_entry_get_text(GTK_ENTRY(studentNameEntry)),
                            &sex,
                            gtk_entry_get_text(GTK_ENTRY(studentBirthplaceEntry)),
                            time,
                            gtk_entry_get_text(GTK_ENTRY(studentNumberEntry)),
                            gtk_entry_get_text(GTK_ENTRY(studentInScoreEntry)),
                            &isGraduated,
                            gtk_entry_get_text(GTK_ENTRY(studentGraduaToEntry))
                    };
                    changeStudentInfo(head, studentNode->CNo, str);
                    reload_studentInfo_list();
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
 @name: on_studentInfo_delete_clicked
 @function: called back when delete button clicked. Delete certain media node.
 @param widget: the widget that activates the signal
 @return none
*************************************************/
void on_studentInfo_delete_clicked(GtkWidget *widget) {
    GtkTreeIter iter;
    GtkTreeModel *model;
    GradeInfo gradeNode;
    ClassInfo classNode;
    StudentInfo studentNode;
    if (gtk_tree_selection_get_selected(
            GTK_TREE_SELECTION(gtk_tree_view_get_selection(GTK_TREE_VIEW(student_list))),
            &model, &iter)) {
        gtk_tree_model_get(model, &iter, STUDENT_GRADE_ADDRESS_COLUMN, &gradeNode,
                           STUDENT_CLASS_ADDRESS_COLUMN,
                           &classNode, STUDENT_ADDRESS_COLUMN, &studentNode, -1);
    } else {
        warning_message_dialog("未选中任何条目", "请先选中一个条目");
        return;
    }
    deleteStudentInfo(head, studentNode->CNo);
    reload_studentInfo_list();
}

/*************************************************
 @name reload_studentInfo_list
 @function: reload all data, this usually because of the change of data such as adding, modifying and deleting data.
 @param none
 @return none
*************************************************/
void reload_studentInfo_list(void) {
    GtkListStore *store;
    GtkTreeIter iter;
    store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(student_list)));
    gtk_list_store_clear(store);
    GradeInfo gradeNode = head->next;
    ClassInfo classNode = NULL;
    StudentInfo studentNode = NULL;
    while (gradeNode != NULL) {
        classNode = gradeNode->Classes->next;
        while (classNode != NULL) {
            studentNode = classNode->Students->next;
            while (studentNode != NULL) {
                char sex[4], isGraduated[4];
                if (studentNode->sex == '1')
                    strcpy(sex, "男");
                else
                    strcpy(sex, "女");
                if (studentNode->HasGraduated == '1')
                    strcpy(isGraduated, "是");
                else
                    strcpy(isGraduated, "否");


                gtk_list_store_append(store, &iter);
                gtk_list_store_set(store, &iter, STUDENT_CLASSNO_COLUMN, studentNode->ClassNo,
                                   STUDENTNO_COLUMN,
                                   studentNode->CNo, STUDENT_NAME_COLUMN, studentNode->Name,
                                   STUDENT_SEX_COLUMN,
                                   sex, STUDENT_BIRTHPLACE_COLUMN, studentNode->Birthplace,
                                   STUDENT_BIRTHDAY_COLUMN,
                                   studentNode->Birthday, STUDENT_NUMBER_COLUMN,
                                   studentNode->Number,
                                   STUDENT_INSCORE_COLUMN, studentNode->InScore,
                                   STUDENT_ISGRAD_COLUMN, isGraduated,
                                   STUDENT_GRADUATETO_COLUMN, studentNode->GraduateTo,
                                   STUDENT_GRADE_ADDRESS_COLUMN, gradeNode,
                                   STUDENT_CLASS_ADDRESS_COLUMN, classNode,
                                   STUDENT_ADDRESS_COLUMN,
                                   studentNode, -1);
                studentNode = studentNode->next;
            }
            classNode = classNode->next;
        }
        gradeNode = gradeNode->next;
    }
}
