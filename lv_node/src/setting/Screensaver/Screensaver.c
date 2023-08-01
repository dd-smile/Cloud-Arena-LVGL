/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-04-25 16:02:15
 * @LastEditTime: 2023-04-25 19:50:29
 * @FilePath: /SmartBox_Power/lv_node/src/setting/all_setting/all_setting.c
 */
#include "ui_app.h"




void CreateScreensave(lv_obj_t *parent)
{

    image_create(parent, &Screensave, -100, -30);
    card_create_24_text(parent, "Screen saver", 2, -30);                        // 创建标题
    card_create_16_text(parent, "Brand new screen saver", -16, 35); // 创建标题

}