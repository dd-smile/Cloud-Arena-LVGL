/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-07-03 17:19:59
 * @LastEditTime: 2023-07-07 14:08:11
 * @FilePath: /lingxiantiyu_compile/lv_node/src/device/device_common.c
 */
#include "ui_app.h"
#include "device_common.h"

// static lv_timer_t *timer = NULL;
static lv_style_t style_radio;
static lv_style_t style_radio_chk;
static uint32_t active_index_1 = 0;
lv_obj_t *act_cb;
const char *RadioText;
static lv_obj_t *WinpageLabel;

static void CreateBiaoge(lv_obj_t *parent)
{
    lv_obj_t *lvLogo = lv_img_create(parent);
    lv_img_set_src(lvLogo, &biaoge);
    lv_obj_align(lvLogo, LV_ALIGN_CENTER, 185, 100);

    create_12_text(lvLogo, "Inspection time", -105, -30);
    create_12_text(lvLogo, "Inspection status", 0, -30);
    create_12_text(lvLogo, "Result", 105, -30);

    create_12_Green_text(lvLogo, "2023/06/27", -105, -7);
    create_12_Green_text(lvLogo, "exception", 0, -7);
    create_12_Green_text(lvLogo, "solved", 105, -7);

    create_12_Green_text(lvLogo, "2023/06/26", -104, 20);
    create_12_Green_text(lvLogo, "exception", 1, 20);
    create_12_Green_text(lvLogo, "solved", 106, 20);
}

static void CreateLoge(lv_obj_t *parent)
{

    lv_obj_t *logo = lv_img_create(parent);
    lv_img_set_src(logo, &logo_square);
    lv_obj_clear_flag(logo, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(logo, 120, 120);
    lv_obj_set_pos(logo, 415, 40);


    lv_obj_t *text = lv_img_create(parent);
    lv_img_set_src(text, &texts);
    lv_obj_clear_flag(text, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(text, 202, 168);
    lv_obj_set_pos(text, 565, 20); 

}

static lv_obj_t *CreateFeatureButton(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, lv_event_cb_t event_cb)
{

    lv_obj_t *btn = lv_btn_create(obj);
    lv_obj_set_size(btn, 85, 35);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, 185);
    lv_obj_add_flag(btn, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(btn, event_cb, LV_EVENT_ALL, NULL);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);


    lv_obj_center(label);
    return btn;
}


/*创建控制按钮*/
static void CreateControlsButton(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, lv_coord_t y_ofs, index_t *index)
{

    lv_obj_t *btn = lv_obj_create(obj);

    lv_obj_set_size(btn, 90, 35);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, Controls_event_cb, LV_EVENT_ALL, index);
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, y_ofs);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);
    lv_obj_center(label);
}

/*创建控制按钮*/
static void CreateLightControlsButton(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, lv_coord_t y_ofs, index_t *index)
{

    lv_obj_t *btn = lv_obj_create(obj);

    lv_obj_set_size(btn, 90, 35);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, lights_Controls_event_cb, LV_EVENT_ALL, index);
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, y_ofs);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);
    lv_obj_center(label);
}

static void CreateBasketballControlsButton(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, lv_coord_t y_ofs, index_t *index)
{

    lv_obj_t *btn = lv_obj_create(obj);

    lv_obj_set_size(btn, 90, 35);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, basketball_Controls_event_cb, LV_EVENT_ALL, index);
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, y_ofs);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);
    lv_obj_center(label);
}


static void CreatePartitionControlsButton(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, lv_coord_t y_ofs, index_t *index)
{

    lv_obj_t *btn = lv_obj_create(obj);

    lv_obj_set_size(btn, 90, 35);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 20, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);
    lv_obj_add_event_cb(btn, partition_Controls_event_cb, LV_EVENT_ALL, index);
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, y_ofs);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);
    lv_obj_center(label);
}


/*创建分割线*/
static void CreatrLine(lv_obj_t *parent)
{
    static lv_point_t line_points[] = {{0, 5}, {0, 409}};
    static lv_style_t style_line;
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, 2);
    lv_style_set_line_color(&style_line, lv_color_hex(0x34415B));
    lv_style_set_line_rounded(&style_line, true);

    lv_obj_t *line1;
    line1 = lv_line_create(parent);
    lv_line_set_points(line1, line_points, 2); /*Set the points*/
    lv_obj_add_style(line1, &style_line, 0);
    lv_obj_center(line1);
}

/*创建滚动页面*/
static lv_obj_t *CreateWinPage(lv_obj_t *obj, const lv_font_t *value, const char *text, lv_coord_t x_ofs, lv_coord_t y_ofs, uint16_t width, uint16_t height)
{

    lv_obj_t *win = lv_win_create(obj, 0);
    lv_obj_set_size(win, width, height);
    lv_obj_align(win, LV_ALIGN_BOTTOM_LEFT, x_ofs, y_ofs);
    lv_obj_t *cont = lv_win_get_content(win); /*Content can be added here*/
    lv_obj_set_style_bg_color(cont, lv_color_make(26, 37, 57), LV_STATE_DEFAULT);
    lv_obj_set_style_width(cont, 0, LV_PART_SCROLLBAR);

    WinpageLabel = lv_label_create(cont);
    lv_obj_set_style_text_font(WinpageLabel, value, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(WinpageLabel, lv_color_make(255, 255, 255), LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(WinpageLabel, 0, LV_STATE_DEFAULT);
    lv_label_set_text(WinpageLabel, text);
    lv_obj_set_pos(WinpageLabel, -20, -24);

    return cont;
}

/*创建背景底图*/
static lv_obj_t *CreateDeviceBgCard(lv_obj_t *mask)
{

    lv_obj_t *bg = lv_obj_create(mask); // 创建背景
    lv_obj_set_size(bg, 814, 468);
    lv_obj_align(bg, LV_ALIGN_CENTER, 40, 20);
    lv_obj_set_style_bg_color(bg, lv_color_make(26, 37, 57), LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(bg, lv_color_make(49, 61, 85), LV_STATE_DEFAULT);

    return bg;
}

/*创建输入框*/
static lv_obj_t *CreateInputBox(lv_obj_t *parent, lv_coord_t x_ofs, lv_coord_t y_ofs, uint16_t width, uint16_t height)
{

    lv_obj_t *box = lv_obj_create(parent);
    lv_obj_set_size(box, width, height);
    lv_obj_align(box, LV_ALIGN_TOP_RIGHT, x_ofs, y_ofs);
    lv_obj_set_style_bg_color(box, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(box, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(box, lv_color_make(49, 61, 85), LV_STATE_DEFAULT);
    lv_obj_set_style_radius(box, 0, LV_PART_MAIN);
    lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE); // 禁用滚动条

    return box;
}

// 单选框选择点击事件
static void radio_event_handler(lv_event_t *e)
{
    uint32_t *active_id = lv_event_get_user_data(e);
    lv_obj_t *cont = lv_event_get_current_target(e);
    act_cb = lv_event_get_target(e);
    lv_obj_t *old_cb = lv_obj_get_child(cont, *active_id);

    /*Do nothing if the container was clicked*/
    if (act_cb == cont)
        return;

    lv_obj_clear_state(old_cb, LV_STATE_CHECKED); /*Uncheck the previous radio button*/
    lv_obj_add_state(act_cb, LV_STATE_CHECKED);   /*Uncheck the current radio button*/

    // 获取索引
    *active_id = lv_obj_get_index(act_cb);
    // 获取单选框的值
    RadioText = lv_checkbox_get_text(act_cb);
    printf("选择类型：%d ====================== %s\n", (int)active_index_1, RadioText);
}

// 创建选择框
static void CreateRadioButton(lv_obj_t *parent, const char *txt)
{
    lv_obj_t *obj = lv_checkbox_create(parent);
    lv_checkbox_set_text(obj, txt);
    lv_obj_set_style_text_font(obj, &fout_12_text, 0); // set font
    lv_obj_set_style_text_color(obj, lv_color_hex(0xffffff), LV_STATE_DEFAULT);

    lv_obj_add_flag(obj, LV_OBJ_FLAG_EVENT_BUBBLE);
    lv_obj_add_style(obj, &style_radio, LV_PART_INDICATOR);
    lv_style_set_bg_opa(&style_radio, LV_OPA_TRANSP);
    lv_style_set_border_color(&style_radio, lv_color_hex(0xffffff));

    lv_obj_add_style(obj, &style_radio_chk, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_style_set_bg_color(&style_radio_chk, lv_color_hex(0xffffff));
}

// 创建单选框
static lv_obj_t *CreateRadioBox(lv_obj_t *parent, lv_coord_t x, lv_coord_t y)
{

    lv_style_init(&style_radio);                         // 初始化单选按钮的样式
    lv_style_set_radius(&style_radio, LV_RADIUS_CIRCLE); // 设置单选框圆形形状
    lv_style_init(&style_radio_chk);                     // 初始化选中状态
    lv_style_set_bg_img_src(&style_radio_chk, NULL);     // 不使用任何背景图

    lv_obj_t *cont1 = lv_obj_create(parent);     // 创建一个标签
    lv_obj_set_flex_flow(cont1, LV_FLEX_FLOW_ROW);
    lv_obj_set_size(cont1, 300, 70);
    lv_obj_align(cont1, LV_ALIGN_TOP_MID, x, y); // 230, 249
    lv_obj_set_style_bg_opa(cont1, LV_OPA_0, 0);
    lv_obj_set_style_border_width(cont1, 0, LV_PART_MAIN);
    lv_obj_add_event_cb(cont1, radio_event_handler, LV_EVENT_CLICKED, &active_index_1);

    // 创建单选框
    CreateRadioButton(cont1, "Solved");
    CreateRadioButton(cont1, "Pending");

    lv_obj_add_state(lv_obj_get_child(cont1, 0), LV_STATE_CHECKED);

    return cont1;
}

static void draw_part_event_cb(lv_event_t *e)
{ 
    // 初始化表格样式
    lv_obj_t *obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t *dsc = lv_event_get_param(e);
    if (dsc->part == LV_PART_ITEMS)
    {
        uint32_t row = dsc->id / lv_table_get_col_cnt(obj);
        uint32_t col = dsc->id - row * lv_table_get_col_cnt(obj);
        dsc->rect_dsc->bg_color = lv_color_hex(0x313d55);
        dsc->label_dsc->color = lv_color_hex(0xffffff);
        dsc->label_dsc->align = LV_TEXT_ALIGN_CENTER;
        if (row != 0 && col == 2)
        {
            dsc->label_dsc->align = LV_TEXT_ALIGN_LEFT;
            dsc->label_dsc->ofs_x = 10;
        }
        const char *cell_value = lv_table_get_cell_value(obj, row, col);
        if (row == 0)
        {
            dsc->rect_dsc->bg_color = lv_color_hex(0x313d55);
            dsc->label_dsc->color = lv_color_hex(0x00bfff);
        }
        if (row % 2 == 1)
            dsc->rect_dsc->bg_color = lv_color_hex(0x1a2539);

        if (strcmp(cell_value, "exception") == 0)
        {
            dsc->label_dsc->color = lv_palette_main(LV_PALETTE_RED);
            const char *solution = lv_table_get_cell_value(obj, row, 2);
            const char *result = lv_table_get_cell_value(obj, row, 4);
            if (strcmp(solution, "repaired") == 0)
            {
                dsc->label_dsc->color = lv_palette_main(LV_PALETTE_GREEN);
            }
            else if (strcmp(solution, "arranging") == 0)
            {
                dsc->label_dsc->color = lv_palette_main(LV_PALETTE_RED);
            }
            if (strcmp(result, "solved") == 0)
            {
                dsc->label_dsc->color = lv_palette_main(LV_PALETTE_GREEN);
            }
            else if (strcmp(result, "pending") == 0)
            {
                dsc->label_dsc->color = lv_palette_main(LV_PALETTE_RED);
            }
        }
        const char *Celsolution = lv_table_get_cell_value(obj, row, col);
        if (strcmp(Celsolution, "repaired") == 0)
            dsc->label_dsc->color = lv_palette_main(LV_PALETTE_GREEN);

        if (strcmp(Celsolution, "arranging") == 0)
            dsc->label_dsc->color = lv_palette_main(LV_PALETTE_RED);

        const char *Celresult = lv_table_get_cell_value(obj, row, col);
        if (strcmp(Celresult, "solved") == 0)
            dsc->label_dsc->color = lv_palette_main(LV_PALETTE_GREEN);

        if (strcmp(Celresult, "pending") == 0)
            dsc->label_dsc->color = lv_palette_main(LV_PALETTE_RED);
    }
}

static lv_obj_t *ui_alert_obj(lv_obj_t *parent)
{ 
    // 长1000宽480的参数设置页面
    lv_obj_t *halert_table = lv_table_create(parent);
    lv_obj_align(halert_table, LV_ALIGN_TOP_LEFT, 10, 50);
    lv_obj_set_style_outline_width(halert_table, 1, LV_PART_ITEMS);
    lv_obj_set_style_border_width(halert_table, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(halert_table, lv_color_hex(0x313d55), LV_PART_MAIN);
    lv_obj_set_style_text_font(halert_table, &PuHuiTi_Regular_16, LV_STATE_DEFAULT);
    lv_obj_set_style_pad_all(halert_table, 2, LV_PART_ITEMS);

    lv_obj_add_event_cb(halert_table, draw_part_event_cb, LV_EVENT_DRAW_PART_BEGIN, NULL);

    lv_table_set_col_width(halert_table, 0, 140);
    lv_table_set_col_width(halert_table, 1, 100);
    lv_table_set_col_width(halert_table, 2, 140);
    lv_table_set_col_width(halert_table, 3, 350);
    lv_table_set_col_width(halert_table, 4, 100);

    lv_table_set_cell_value(halert_table, 0, 0, "Inspection time");
    lv_table_set_cell_value(halert_table, 0, 1, "Inspection status");
    lv_table_set_cell_value(halert_table, 0, 2, "Solution measure");
    lv_table_set_cell_value(halert_table, 0, 3, "Device fault Symptom");
    lv_table_set_cell_value(halert_table, 0, 4, "Result");

    lv_create_alarm(halert_table, 1, "2023/06/26", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 2, "2023/06/20", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 3, "2023/06/19", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 4, "2023/06/12", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 5, "2023/06/05", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 6, "2023/06/01", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 7, "2023/05/29", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 8, "2023/05/18", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 9, "2023/05/15", "exception", "repaired", "Click operation abnormal, no rotation, no noise", "solved");
    lv_create_alarm(halert_table, 10, "2023/05/13", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 11, "2023/05/05", "normal", " ", " ", " ");
    lv_create_alarm(halert_table, 12, "2023/04/12", "normal", " ", " ", " ");

    // lv_create_alarm();
}

void lv_create_alarm(lv_obj_t *halert_table, uint8_t id, const char *DeviceName, const char *AlarmTime, const char *AlarmType, const char *AlarmInfo, const char *AlarmLevel)
{
    lv_table_set_cell_value(halert_table, id, 0, DeviceName);
    lv_table_set_cell_value(halert_table, id, 1, AlarmTime);
    lv_table_set_cell_value(halert_table, id, 2, AlarmType);
    lv_table_set_cell_value(halert_table, id, 3, AlarmInfo);
    lv_table_set_cell_value(halert_table, id, 4, AlarmLevel);
}

// 创建检查故障表
lv_obj_t *CreateInspectTable(lv_obj_t *parent)
{
    lv_obj_t *mask = lv_c_create_mask_box(parent); // 创建遮罩
    lv_obj_t *Tablebg = CreateDeviceBgCard(mask);
    lv_obj_set_size(Tablebg, 900, 500);
    card_create_16_text(Tablebg, "Device name: ", -380, -220);       // 创建设备名称
    card_create_16_text(Tablebg, pPageData->deviceName, -220, -220); // 创建设备名称

    ui_alert_obj(Tablebg);

    return Tablebg;
}

/*------------------------------------------创建按钮点击事件-----------------------------------------*/

static void AddDescriptionEvent(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        // memset(add_device_list[0].device_name, 0, sizeof(add_device_list[0].device_name)); // 清空数组
        char *inputVal = lv_textarea_get_text(Textarea_Pinyin);
        printf("描述故障：%s\n", inputVal);

        // strcat(add_device_list[0].device_name, inputVal);                                  // 拼接字符串
        lv_label_set_text(WinpageLabel, inputVal); // 设置标签的值
        lv_obj_del(obj->parent);
    }
}

// 点击描述故障输入框的点击事件
static void DescriptionInputHandler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        lv_keypage_create(lv_scr_act(), AddDescriptionEvent);
    }
}

static void AddRenameEventBtn(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    if (code == LV_EVENT_CLICKED)
    {
        char *inputVal = lv_textarea_get_text(Textarea_Pinyin); // 获取添加设备名称输入框的值
        printf("添加文本:%s\n", inputVal);
        lv_obj_del(obj->parent);
    }
}

// 点击重命名按钮的点击事件
static void RenameCreateButton(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        lv_keypage_create(lv_scr_act(), AddRenameEventBtn);
    }
}

static void MaintenanceCreateButton(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {
        create_popup(lv_scr_act(), pPageData->PopupTitlie, "Ok", "Cancel", pPageData->PopupContent, lv_back_Mask, NULL);
    }
}

static void ReportCreateButton(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {

        CreateBreakdownPageBg(lv_scr_act());
    }
}

static void InspectCreateButton(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED)
    {

        CreateInspectTable(lv_scr_act());
        printf("Create\n");
    }
}

// 创建描述故障输入框
static lv_obj_t *CreateDescriptionInput(lv_obj_t *parent)
{
    card_create_16_text(parent, "Description of the fault symptom: ", 152, -190); // 设备故障现象描述
    lv_obj_t *WinPage = CreateWinPage(parent, &fout_16_text,"Condition ", 410, -298, 300, 80); // 设备故障现象描述
    lv_obj_set_style_bg_color(WinPage, lv_color_make(0, 0, 0), LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(WinPage, 1, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(WinPage, lv_color_make(49, 61, 85), LV_STATE_DEFAULT);
    lv_obj_add_event_cb(WinPage, DescriptionInputHandler, LV_EVENT_ALL, NULL);
}

//创建解决问题输入框


// 创建设备故障详情页
lv_obj_t *CreateBreakdownPageBg(lv_obj_t *parent)
{
    lv_obj_t *mask = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩层

    lv_obj_t *bg = CreateDeviceBgCard(mask);                               // 创建背景
    CreatrLine(bg);                                                        // 创建分割线
    card_create_16_text(bg, "Device name: ", -300, 30);                    // 创建设备名称
    card_create_16_text(bg, pPageData->deviceName, -140, 30);              // 创建设备名称
    image_create(bg, pPageData->image, -200, -100);                        // 创建图片
    CreateWinPage(bg, &fout_16_text, pPageData->intro, 31, -100, 300, 59); // 创建产品简介

    create_12_text(bg, "Manufacturing TEL : ", 88, -50); // 制造商服务电话
    create_12_text(bg, pPageData->ManufacturingTel, 180, -50);
    create_12_text(bg, "After-sales hotline :", 87, 5);
    create_12_text(bg, pPageData->SalehAfterotline, 180, 5);

    create_12_text(bg, "Solve the problem: ", 88, 50);
    lv_obj_t *SolveInputBox = CreateInputBox(bg, -43, 244, 190, 35);
    lv_obj_set_style_text_font(SolveInputBox, &lv_font_montserrat_12, 0);  // set font
    lv_obj_set_style_text_color(SolveInputBox, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    // lv_obj_add_event_cb(SolveInputBox, RenameCreateButton, LV_EVENT_ALL, NULL);

    // Input_label = lv_label_create(SolveInputBox); // 创建标签
    // lv_label_set_text(Input_label, "Solution");
    // lv_obj_align(Input_label, LV_ALIGN_LEFT_MID, -10, 0);

    create_12_text(bg, "Result : ", 55, 105);
    CreateRadioBox(bg, 230, 287);//结果选择框

    CreateDescriptionInput(bg);//描述设备故障输入框

    lv_obj_t *InspectButton = CreateFeatureButton(bg, "inspection record form", 50, InspectCreateButton); // 创建检查故障按钮
    lv_obj_set_size(InspectButton, 320, 39);
    lv_obj_align(InspectButton, LV_ALIGN_DEFAULT, 22, 350);

    lv_obj_t *ConfirmBtn = btn_create_text(bg, false, "OK", 480, 353);     // 创建按钮
    lv_obj_add_event_cb(ConfirmBtn, lv_back_Mask, LV_EVENT_CLICKED, NULL); // 添加返回事件
    lv_obj_t *BackBtn = btn_create_text(bg, false, "Cancel", 620, 353);    // 创建按钮
    lv_obj_add_event_cb(BackBtn, lv_back_Mask, LV_EVENT_CLICKED, NULL);    // 添加返回事件

    return bg;
}

/*创建设备详情页*/
lv_obj_t *CreateDevicePageBg(const DevicePageData *data, uint8_t device_num)
{
    lv_obj_t *mask = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩层

    lv_obj_t *bg = CreateDeviceBgCard(mask);             // 创建背景
    CreatrLine(bg);                                      // 创建分割线
    card_create_16_text(bg, "设备名称: ", -320, 30);  // 创建设备名称
    card_create_16_text(bg, data->deviceName, -240, 30); // 创建设备名称
    card_create_16_text(bg, "制造商简介: ", 100, -195);
    card_create_12_text(bg, "采购时间: ", 80, -5);
    card_create_12_text(bg, data->date, 140, -5);
    card_create_12_text(bg, "检修周期: ", 260, -5);
    card_create_12_text(bg, data->period, 330, -5);
    card_create_12_text(bg, "供应商服务电话: ", 95, 25);
    card_create_12_text(bg, data->phoneNumber, 225, 25);
    image_create(bg, data->image, -200, -100);                        // 创建图片
    CreateWinPage(bg, &fout_16_text, data->intro, 31, -100, 300, 59); // 创建产品简介

    index_t *index1 = add_index_t(device_num, 0);
    index_t *index2 = add_index_t(device_num, 1);
    index_t *index3 = add_index_t(device_num, 2);
    index_t *index4 = add_index_t(device_num, 3);
    index_t *index5 = add_index_t(device_num, 4);
    index_t *index6 = add_index_t(device_num, 5);
    index_t *index7 = add_index_t(device_num, 6);
    CreateControlsButton(bg, data->expandBtnText, -320, 142, index1);            // 一键打开按钮
    CreateControlsButton(bg, data->emergencyStopBtnText, -200, 142, index2);     // 创建急停按钮
    CreateControlsButton(bg, data->collapseBtnText, -80, 142, index3);           // 一键收合按钮
    CreateControlsButton(bg, data->StandOpenBtnText, -350, 188, index4);     // 看台展开按钮
    CreateControlsButton(bg, data->StandClosureBtnText, -250, 188, index5);  // 看台收缩按钮
    CreateControlsButton(bg, data->SeatRiseBtnText, -150, 188, index6);      // 座椅上升按钮
    CreateControlsButton(bg, data->SeatTipBtnText, -50, 188, index7);        // 座椅下降按钮
    
    CreateFeatureButton(bg, "故障申报", 245, ReportCreateButton);       // 故障申报按钮
    CreateFeatureButton(bg, "重命名", 50, RenameCreateButton);          // 重命名按钮
    CreateFeatureButton(bg, "检修正常", 145, MaintenanceCreateButton);  // 检修正常按钮   
    CreateFeatureButton(bg, "返回", 340, lv_back_Mask);                 // 返回按钮

    CreateLoge(bg); // 制造商Logo

    CreateBiaoge(bg); // 表格

    return bg;
}

lv_obj_t *CreateLightsPageBg(const DevicePageData *data, uint8_t device_num)
{
    lv_obj_t *mask = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩层

    lv_obj_t *bg = CreateDeviceBgCard(mask);             // 创建背景
    CreatrLine(bg);                                      // 创建分割线
    card_create_16_text(bg, "设备名称: ", -320, 30);  // 创建设备名称
    card_create_16_text(bg, data->deviceName, -240, 30); // 创建设备名称
    card_create_16_text(bg, "制造商简介: ", 100, -195);
    card_create_12_text(bg, "采购时间: ", 80, -5);
    card_create_12_text(bg, data->date, 140, -5);
    card_create_12_text(bg, "检修周期: ", 260, -5);
    card_create_12_text(bg, data->period, 330, -5);
    card_create_12_text(bg, "供应商服务电话: ", 95, 25);
    card_create_12_text(bg, data->phoneNumber, 225, 25);
    image_create(bg, data->image, -200, -100);                        // 创建图片
    CreateWinPage(bg, &fout_16_text, data->intro, 31, -100, 300, 59); // 创建产品简介

    index_t *index1 = add_index_t(device_num, 0);
    index_t *index2 = add_index_t(device_num, 1);
    CreateLightControlsButton(bg, data->expandBtnText, -320, 142, index1);  // 一键打开按钮
    CreateLightControlsButton(bg, data->collapseBtnText, -80, 142, index2); // 一键收合按钮

   

    CreateFeatureButton(bg, "故障申报", 245, ReportCreateButton);       // 故障申报按钮
    CreateFeatureButton(bg, "重命名", 50, RenameCreateButton);          // 重命名按钮
    CreateFeatureButton(bg, "检修正常", 145, MaintenanceCreateButton);  // 检修正常按钮   
    CreateFeatureButton(bg, "返回", 340, lv_back_Mask);                 // 返回按钮

    CreateLoge(bg); // 制造商Logo

    CreateBiaoge(bg); // 表格

    return bg;
}

lv_obj_t *CreatebasketballPageBg(const DevicePageData *data, uint8_t device_num)
{
    lv_obj_t *mask = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩层

    lv_obj_t *bg = CreateDeviceBgCard(mask);             // 创建背景
    CreatrLine(bg);                                      // 创建分割线
    card_create_16_text(bg, "设备名称: ", -320, 30);  // 创建设备名称
    card_create_16_text(bg, data->deviceName, -240, 30); // 创建设备名称
    card_create_16_text(bg, "制造商简介: ", 100, -195);
    card_create_12_text(bg, "采购时间: ", 80, -5);
    card_create_12_text(bg, data->date, 140, -5);
    card_create_12_text(bg, "检修周期: ", 260, -5);
    card_create_12_text(bg, data->period, 330, -5);
    card_create_12_text(bg, "供应商服务电话: ", 95, 25);
    card_create_12_text(bg, data->phoneNumber, 225, 25);
    image_create(bg, data->image, -200, -100);                        // 创建图片
    CreateWinPage(bg, &fout_16_text, data->intro, 31, -100, 300, 59); // 创建产品简介

    index_t *index1 = add_index_t(device_num, 0);
    index_t *index2 = add_index_t(device_num, 1);
    index_t *index3 = add_index_t(device_num, 2);
    CreateBasketballControlsButton(bg, data->expandBtnText, -320, 142, index1);            // 一键打开按钮
    CreateBasketballControlsButton(bg, data->emergencyStopBtnText, -200, 142,index2);     // 创建急停按钮
    CreateBasketballControlsButton(bg, data->collapseBtnText, -80, 142,index3);           // 一键收合按钮
   

    CreateFeatureButton(bg, "故障申报", 245, ReportCreateButton);       // 故障申报按钮
    CreateFeatureButton(bg, "重命名", 50, RenameCreateButton);          // 重命名按钮
    CreateFeatureButton(bg, "检修正常", 145, MaintenanceCreateButton);  // 检修正常按钮   
    CreateFeatureButton(bg, "返回", 340, lv_back_Mask);                 // 返回按钮

    CreateLoge(bg); // 制造商Logo

    CreateBiaoge(bg); // 表格

    return bg;
}

lv_obj_t *CreatePartitionPageBg(const DevicePageData *data, uint8_t device_num)
{
    lv_obj_t *mask = lv_c_create_mask_box(lv_scr_act()); // 创建遮罩层

    lv_obj_t *bg = CreateDeviceBgCard(mask);             // 创建背景
    CreatrLine(bg);                                      // 创建分割线
    card_create_16_text(bg, "设备名称: ", -320, 30);  // 创建设备名称
    card_create_16_text(bg, data->deviceName, -240, 30); // 创建设备名称
    card_create_16_text(bg, "制造商简介: ", 100, -195);
    card_create_12_text(bg, "采购时间: ", 80, -5);
    card_create_12_text(bg, data->date, 140, -5);
    card_create_12_text(bg, "检修周期: ", 260, -5);
    card_create_12_text(bg, data->period, 330, -5);
    card_create_12_text(bg, "供应商服务电话: ", 95, 25);
    card_create_12_text(bg, data->phoneNumber, 225, 25);
    image_create(bg, data->image, -200, -100);                        // 创建图片
    CreateWinPage(bg, &fout_16_text, data->intro, 31, -100, 300, 59); // 创建产品简介

    index_t *index1 = add_index_t(device_num, 0);
    index_t *index2 = add_index_t(device_num, 1);
    index_t *index3 = add_index_t(device_num, 2);
    CreatePartitionControlsButton(bg, data->expandBtnText, -320, 142, index1);        // 一键打开按钮
    CreatePartitionControlsButton(bg, data->emergencyStopBtnText, -200, 142, index2); // 创建急停按钮
    CreatePartitionControlsButton(bg, data->collapseBtnText, -80, 142, index3);       // 一键收合按钮
   
    
    CreateFeatureButton(bg, "故障申报", 245, ReportCreateButton);       // 故障申报按钮
    CreateFeatureButton(bg, "重命名", 50, RenameCreateButton);          // 重命名按钮
    CreateFeatureButton(bg, "检修正常", 145, MaintenanceCreateButton);  // 检修正常按钮   
    CreateFeatureButton(bg, "返回", 340, lv_back_Mask);                 // 返回按钮

    CreateLoge(bg); // 制造商Logo

    CreateBiaoge(bg); // 表格

    return bg;
}
