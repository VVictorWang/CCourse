//
// Created by victor on 8/17/17.
//
#include "head.h"

/**
 * 函数名称: TestProv
 * 函数功能: 测试省份信息是否存在.
 * 输入参数: str 要测试的省份名称
 * 输出参数: 无
 * 返 回 值: flag 1表示修改了省份名 0没有
 *
 * 调用说明:
 */

int testGradeInfo(char *str)//测试年级信息是否存在
{
    GradeInfo tail = head;
    int flag = 0;
    while (tail->next != NULL) {
        tail = tail->next;
        if (!strcmp(str, tail->CSNo)) {
            flag = 1;
            break;
        }
    }
    return flag;
}