//
// Created by victor on 8/17/17.
// email: chengyiwang@hustunique.com
// blog:  www.victorwang.science
//

#include "head.h"

int main(int argc, char *argv[]) {

    gtk_init(&argc, &argv);
    show_window(&main_window);
    int n = initInfo(&head);
    switch (n) {
        case -1:
            warning_message_dialog("年级信息打开失败", "年级信息打开失败,可能是第一次打开软件");
            break;
        case -2:
            warning_message_dialog("班级信息打开失败", "班级信息打开失败,可能是第一次打开软件");
            break;
        case -3:
            warning_message_dialog("班级信息有误", "班级信息有误,可能是第一次打开软件");
            break;
        case -4:
            warning_message_dialog("学生信息打开失败", "学生信息打开失败,可能是第一次打开软件");
            break;
        case -5:
            warning_message_dialog("学生信息有误", "学生信息有误,可能是第一次打开软件");
            break;
        default:
            break;
    }
    gtk_main();
    return 0;
}