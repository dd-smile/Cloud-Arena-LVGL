/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-04-25 16:02:15
 * @LastEditTime: 2023-04-25 19:50:29
 * @FilePath: /SmartBox_Power/lv_node/src/setting/all_setting/all_setting.c
 */
#include "ui_app.h"

static lv_obj_t *lv_select_label = NULL;
static lv_obj_t *Screen_Background[6];
extern lv_setting_data_t setting_buf;

struct
{
    const void *img_bg;
    int x;
    int y;

} obj_Images[] = {
    {&Image1, -340, -125},
    {&Image2, -10, -125},
    {&Image3, 330, -125},
    {&Image4, -340, 100},
    {&Image5, -10, 100},
    {&Image6, 330, 100},
};

static void background_click_event(lv_event_t *e)
{

    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        for (int i = 0; i < 6; i++)
        {
            if(obj == Screen_Background[i])
            {
                lv_obj_align_to(lv_select_label, obj, LV_ALIGN_TOP_RIGHT, 0, 0);
                setting_buf.ScreenSaveid = i;
            }    
        }
    }
}

static lv_obj_t *Screen_Background_Create(lv_obj_t *parent)
{
    for (int i = 0; i < 6; i++)
    {
        Screen_Background[i] = image_create(parent, obj_Images[i].img_bg, obj_Images[i].x, obj_Images[i].y);
        lv_obj_add_flag(Screen_Background[i], LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(Screen_Background[i], background_click_event, LV_EVENT_ALL, NULL); // 添加点击事件回调函数
    }

    lv_select_label = lv_img_create(parent);
    lv_img_set_src(lv_select_label, &select_label);
    lv_obj_align_to(lv_select_label, Screen_Background[setting.ScreenSaveid], LV_ALIGN_TOP_RIGHT , 0, 0);
    
    return parent;
}

// 创建屏保设置页面
static void *CreateScreenSaveStlye(lv_obj_t *parent)
{
    lv_obj_t *scr = lv_c_create_mask_box(parent); // 创建遮罩
    lv_obj_t *popup_page = create_popup_page(scr, "屏保设置", 0, 0);
    Screen_Background_Create(popup_page);

    return scr;
}

/**点击事件**/
static void add_Screensave_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        CreateScreenSaveStlye(lv_scr_act());
    }
}

void CreateScreensave(lv_obj_t *parent)
{
    lv_obj_t *ImageObj = CreateOBJclick(parent);
    image_create(parent, &Screensave, -100, -30);
    card_create_24_text(parent, "屏保设置", 2, -30);            // 创建标题
    card_create_16_text(parent, "全新升级屏保", -16, 35); // 创建标题
    lv_obj_add_event_cb(ImageObj, add_Screensave_event_cb, LV_EVENT_ALL, NULL);
}
