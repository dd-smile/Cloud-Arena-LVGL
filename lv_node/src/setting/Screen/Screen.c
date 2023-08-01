#include "ui_app.h"

lv_Brightting_data_t setting;
static lv_obj_t *slider_label;
static lv_obj_t *slider_label1;

lv_obj_t *In_slider;
lv_obj_t *On_slider;




// 外面的亮度
void slider_event_cb(lv_event_t *e)
{
    lv_obj_t *slider = lv_event_get_target(e);

    setting.brightness = lv_slider_get_value(slider);
    char buf[8];
    lv_snprintf(buf, sizeof(buf), "%d", (int)lv_slider_get_value(slider));
    lv_label_set_text(setting.slider_label, buf);
    sprintf(setting.On_screen, "%s", buf);

    char cmd[128];
    sprintf(cmd, "echo %s > /sys/class/pwm/pwmchip0/pwm0/duty_cycle", setting.On_screen);
    system(cmd);
}

static lv_obj_t *create_switch(lv_obj_t *parent)
{
    lv_obj_t *swich = lv_switch_create(parent); // 创建开关
    lv_obj_align(swich, LV_ALIGN_CENTER, 100, 0);
    lv_obj_t *lv_sw_obj = lv_obj_create(parent);
    lv_obj_set_size(lv_sw_obj, 60, 40);
    lv_obj_align(lv_sw_obj, LV_ALIGN_CENTER, -80, -15);
    lv_obj_set_style_opa(lv_sw_obj, LV_OPA_TRANSP, LV_STATE_DEFAULT);
    lv_obj_add_flag(lv_sw_obj, LV_OBJ_FLAG_CLICKABLE);

    return swich;
}

// 弹出页面返回上一级按钮
lv_obj_t *create_page_back(lv_obj_t *obj)
{
    lv_obj_t *lv_obj = lv_obj_create(obj);
    lv_obj_set_size(lv_obj, 90, 50);
    lv_obj_add_flag(lv_obj, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_align(lv_obj, LV_ALIGN_TOP_LEFT, 0, -13);
    lv_obj_set_style_bg_opa(lv_obj, 0, LV_STATE_DEFAULT); // 设置背景透明
    lv_obj_set_style_border_width(lv_obj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(lv_obj, LV_OBJ_FLAG_SCROLLABLE);                 // 禁用滚动条
    lv_obj_add_event_cb(lv_obj, lv_back_Mask, LV_EVENT_CLICKED, time); // 添加返回事件
    lv_obj_t *back_btn = lv_label_create(lv_obj);
    lv_label_set_text(back_btn, LV_SYMBOL_LEFT);
    lv_obj_align(back_btn, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_color(back_btn, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    return lv_obj;
}

// 创建一个弹出页面
lv_obj_t *create_popup_page(lv_obj_t *parent, const char *title, lv_coord_t x, lv_coord_t y)
{
    lv_obj_t *popup_page = lv_obj_create(parent);
    lv_obj_set_size(popup_page, 1024, 600);
    lv_obj_align(popup_page, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_bg_color(popup_page, lv_color_hex(0x141a23), 0);
    lv_obj_set_style_border_width(popup_page, 0, LV_STATE_DEFAULT);

    lv_obj_t *Titleobj = lv_obj_create(parent);
    lv_obj_set_size(Titleobj, 1024, 64);
    lv_obj_align(Titleobj, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(Titleobj, lv_color_hex(0x1f2633), 0);
    lv_obj_set_style_border_width(Titleobj, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(Titleobj, 0, LV_PART_MAIN);
    lv_obj_clear_flag(Titleobj, LV_OBJ_FLAG_SCROLLABLE); // 禁用滚动条
    card_create_24_text(Titleobj, title, x, y);
    create_page_back(Titleobj); // 返回上一级按钮

    lv_obj_t *label = card_create_20_text(Titleobj, "开关", 100, 0);

    lv_obj_t *lv_switch = create_switch(Titleobj); // 开关

    return popup_page;
}

/*------------------------------点击事件----------------------------------*/

/**点击屏保事件**/
void add_Screen_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        lv_obj_t *scr = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩
        lv_obj_t *popup_page = create_popup_page(scr, "屏幕设置", 0, 0);
    }
}

void CreateScreen(lv_obj_t *parent)
{
    lv_obj_t *ImageObj = CreateOBJclick(parent);
    image_create(parent, &Screen, -100, -30);
    card_create_24_text(parent, "Screen settings", 20, -30); // 创建标题

    setting.brightness = 63;  // 什么都没有设置的时候默认值为63
    sprintf(setting.On_screen, "%d", setting.brightness);
    On_slider = CreateSlider(parent, 17, 35, 0, 100, lv_color_hex(0xffffff), setting.brightness, 200, 6, false); // 创建进度条
    setting.slider_label = card_create_16_text(parent, setting.On_screen, -100, 35);                             // 创建标题
}
