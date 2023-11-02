/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-07-03 15:48:41
 * @LastEditTime: 2023-07-07 16:34:15
 * @FilePath: /lingxiantiyu_compile/lv_node/src/device/device.c
 */
#include "ui_app.h"

// static const widget_info_t WIDGETS_INFO[] = {
//     {0, 0, "伸缩活动看台", TelescopicStand},  
//     {1, 0, "悬空球架1", BasketballStands},  
//     {2, 0, "悬空球架2", BasketballStands}, 
//     {3, 0, "悬空球架3", BasketballStands},  
//     {0, 1, "悬空球架4", BasketballStands},  
//     {1, 1, "自动分隔幕", PartitionCurtain}, 
//     {2, 1, "场馆灯光", Light}, 
// };

index_t *add_index_t(uint8_t num, uint8_t ind)
{
    index_t *index = (index_t *)malloc(sizeof(index_t));

    index->num = num;
    index->ind = ind;

    return index;
}


static void set_common_style(lv_obj_t *obj)
{
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_bg_opa(obj, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(obj, 0, LV_STATE_DEFAULT);
}


/* index 包含设备号和按钮编号，type 设备类型 */
static void create_button(lv_obj_t *obj, const char *text, lv_coord_t x_ofs, uint8_t type, index_t *index)
{
    lv_obj_t *btn = lv_obj_create(obj);
    lv_obj_set_size(btn, 55, 30);
    lv_obj_clear_flag(btn, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_radius(btn, 15, LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(26, 31, 46), LV_PART_MAIN);
    lv_obj_set_style_bg_color(btn, lv_color_make(33, 150, 243), LV_STATE_PRESSED);
    lv_obj_set_style_border_opa(btn, 80, LV_PART_MAIN);

    switch (type)
    {
    case 0:
        lv_obj_add_event_cb(btn, telescoopic_Controls_event_cb, LV_EVENT_ALL, index); // 传入设备号和按钮号
        break;
    case 1:
        lv_obj_add_event_cb(btn, basketball_Controls_event_cb, LV_EVENT_ALL, index);
        break;
    case 2:
        lv_obj_add_event_cb(btn, partition_Controls_event_cb, LV_EVENT_ALL, index);
        break;
    case 3:
        lv_obj_add_event_cb(btn, lights_Controls_event_cb, LV_EVENT_ALL, index);
        break;
    default:
        break;
    }
    
    lv_obj_align(btn, LV_ALIGN_CENTER, x_ofs, 0);

    lv_obj_t *label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_PART_MAIN);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_PART_MAIN);
    lv_obj_center(label);
}


static lv_obj_t *swich_btn_card(lv_obj_t *obj)
{
    lv_obj_t *box = lv_obj_create(obj);
    lv_obj_set_size(box, 201, 70);
    lv_obj_set_style_bg_color(box, lv_color_hex(0x1A1F2E), LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(box, 0, LV_STATE_DEFAULT);
    lv_obj_set_style_radius(box, 10, LV_STATE_DEFAULT);
    lv_obj_clear_flag(box, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_align(box, LV_ALIGN_BOTTOM_MID, 0, 0);
    return box;
}

static lv_obj_t *lv_box_create(lv_obj_t *parent, int x, int y, const char *text, const char *text1, const char *text2, index_t *index)
{
    lv_obj_t *card = lv_img_create(parent);
    lv_img_set_src(card, &card_background);

    index_t *index0 = add_index_t(index->num, 0);  // 设备号和按钮号
    index_t *index1 = add_index_t(index->num, 1);
    index_t *index2 = add_index_t(index->num, 2);

    lv_obj_t *btn_card = swich_btn_card(card);
    if(text != NULL)
        create_button(btn_card, text, -60, index->ind, index0); // index[0]为设备类型, 后面传入设备号和按钮号
    if(text1 != NULL)
        create_button(btn_card, text1, 0, index->ind, index1); 
    if(text2 != NULL)
        create_button(btn_card, text2, 60, index->ind, index2);

    lv_obj_set_pos(card, LV_CARD_WIDTH * x, LV_CARD_HEIGHT * y);

    return card;
}

static void lv_create_device(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    index_t *user_data = (uint8_t *)lv_event_get_user_data(e);

    uint8_t type = user_data->ind; 
    uint8_t device_num = user_data->num;
    if (code == LV_EVENT_CLICKED)
    {printf("user_data: %d %d\n", type, device_num);
        switch (type)
        {
        case 0:
            CreateTelescopicStandPage(device_num);
            break;

        case 1:
            
            CreateBasketballStandsPage(device_num); // 篮球架传入设备号
            break;
        case 2:
            
            CreatePartitionCurtianPage(device_num);
            break;
        case 3:
            
            CreateLightsPage(device_num);
            break;
        default :
            break;
        }
    }
}

static lv_obj_t *card_class(lv_obj_t *parent, int x, int y, const char *name, uint8_t image, uint8_t device_num)
{
    index_t *index = add_index_t(device_num, image); // 这里为设备号和设备类型
    
    // 创建设备卡片背景
    lv_obj_t *dev_card;
    if(image == 0)
        dev_card = lv_box_create(parent, x, y, "展开", "急停", "收合", index); // 传入设备类型和设备号
    else if(image == 1)
        dev_card = lv_box_create(parent, x, y, "放下", "急停", "收合", index);
    else if(image == 2)
        dev_card = lv_box_create(parent, x, y, "放下", "急停", "收合", index);
    else if(image == 3)
        dev_card = lv_box_create(parent, x, y, "打开", "关闭", NULL, index);
    
    printf("index:%d %d\n", index->num, index->ind);

    lv_obj_t *cont = lv_obj_create(dev_card);
    lv_obj_set_size(cont, 107, 107);
    lv_obj_align(cont, LV_ALIGN_CENTER, 0, -20);
    set_common_style(cont);
    // 选择设备图片
    lv_obj_t *imgbutton = lv_img_create(cont);
    lv_obj_align(imgbutton, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(imgbutton, LV_OBJ_FLAG_SCROLLABLE);
    static const lv_img_dsc_t *img_table[] = {&stand, &basketball_stands, &partition_curtain, &lights}; // 设备图片数组
    lv_img_set_src(imgbutton, img_table[image]);
    lv_obj_add_flag(imgbutton, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(imgbutton, lv_create_device, LV_EVENT_ALL, (void *)index); // 传入设备类型和设备号

    lv_obj_t *label = lv_label_create(dev_card);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 15);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_16, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_label_set_text(label, name);
    set_common_style(label);

    return dev_card;
}


void CreateDevicePage(lv_obj_t *parent)
{
    
    card_class(parent, 0, 0, "伸缩活动看台", 0, 1); // 加设备识别id
    card_class(parent, 1, 0, "悬空球架1", 1, 1);
    card_class(parent, 2, 0, "悬空球架2", 1, 2);
    card_class(parent, 3, 0, "悬空球架3", 1, 3);
    card_class(parent, 0, 1, "悬空球架4", 1, 4);
    card_class(parent, 1, 1, "自动分隔幕", 2, 1);
    card_class(parent, 2, 1, "场馆灯光", 3, 1);


}