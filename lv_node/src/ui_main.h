#ifndef _LV_NODE_HOME_H
#define _LV_NODE_HOME_H

#define LV_CARD_WIDTH 221
#define LV_CARD_HEIGHT 250

typedef struct
{
    lv_obj_t *home_button[3]; // 主页按钮
    lv_obj_t *home_pages[3];  // 主页页面
    lv_obj_t *content;        // 主页内容

    lv_obj_t *home_page;    // 首页页面
    lv_obj_t *mode_page;    // 模式页面
    lv_obj_t *setting_page; // 设置页面


    lv_obj_t *mode_page_box; // 首页页面盒子

} All_Data;
extern All_Data home_data;
typedef struct
{
    uint8_t brightness; //滑动条的值（外面）
    uint32_t ScreenSaveid;
    uint32_t Btnmid;
    int screen_save_time;

    char On_screen[8];  // 外面的亮度
    char In_screen[8];  // 外面的亮度

    

} lv_setting_data_t;
extern  lv_setting_data_t setting;


void create_lv_layout(lv_obj_t *scr);

#endif