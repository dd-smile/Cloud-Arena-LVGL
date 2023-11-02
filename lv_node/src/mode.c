/*
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-03-09 11:28:42
 * @LastEditTime: 2023-07-05 10:34:31
 * @FilePath: /new_home_smart/lv_node/src/mode.c
 */

#include "ui_app.h"

static lv_obj_t *mode_labels[3];
static bool states[] = {false, false, false};
// 事件
static void toggle_label(lv_obj_t *label, bool state)
{
    const char *text = state ? "已开启" : "未开启";
    lv_color_t color = state ? lv_color_hex(0x14E7F0) : lv_color_hex(0xffffff);

    lv_label_set_text(label, text);
    lv_obj_set_style_text_color(label, color, 0);
}
static void toggle_image(lv_obj_t *obj, uint8_t index, bool type)
{
    static const lv_img_dsc_t *mode_images[] = {
        &mode1_on, &mode2_on, &mode3_on,
        &mode1_off, &mode2_off, &mode3_off
    };

    uint8_t image_index = (type ? index + 3 : index);
    lv_img_set_src(obj, mode_images[image_index]);
}

/* 训练模式 */
void *mode1_handler()
{
    // 收拢看台
    if(stand_flag == false)
    {
        ReadSerialDiNum = 4;
        SetAllDoClose(0xFE);
        usleep(100*1000);               
        SetSerialDo(1, 3, 1); // 先收拢座椅 
        Swich_status = 2; 
        while (stand_flag == false)
        {
            usleep(100 * 1000); // 等到收拢
            if(states[0] == false)
                pthread_exit(0);
        }
    }
    // 分隔幕打开
    if(patition_flag == true)
    {      
        ReadSerialDiNum = 13;
        SetAllDoClose(0xFE);
        usleep(100 * 1000);
        SetSerialDo(3, 0, 1); // 打开D01 
        while (patition_flag == true)
        {
            usleep(100 * 1000); // 等到下降
            if(states[0] == false)
                pthread_exit(0);
        }
    }
    // 球架下降
    for(int i = 1; i < 5; i++)
    {
        if(basketball_flag[i - 1] == true)
        {
            set_basketball_stands_state(i, 1); 
            while (basketball_flag[i - 1] == true)
            {
                usleep(100 * 1000); // 等到下降
                if(states[0] == false)
                    pthread_exit(0);
            }
        }       
    }
}
/* 演出模式 */
void *mode2_handler()
{
     // 分隔幕收拢
    if(patition_flag == false)
    {      
        ReadSerialDiNum = 14;
        SetAllDoClose(0xFE);
        usleep(100 * 1000);                
        SetSerialDo(3, 1, 1); // 打开D02
        while (patition_flag == false)
        {
            usleep(100 * 1000);
            if(states[1] == false)
                pthread_exit(0);
        }
    }
    // 球架上升
    for(int i = 1; i < 5; i++)
    {
        if(basketball_flag[i - 1] == false)
        {
            set_basketball_stands_state(i, 0);
            while (basketball_flag[i - 1] == false)
            {
                usleep(100 * 1000);
                if(states[1] == false)
                    pthread_exit(0);
            }
        } 
    }
    if(stand_flag == true)
    {
        // 展开看台 
        ReadSerialDiNum = 1;
        SetAllDoClose(0xFE);
        usleep(100 * 1000);
        SetSerialDo(1, 0, 1); 
        Swich_status = 0; 
        while (stand_flag == true)
        {
            usleep(100 * 1000); // 等到收拢
            if(states[1] == false)
                pthread_exit(0);
        }
    }
}
/* 退场模式 */
void *mode3_handler()
{
    // 收拢看台
    if(stand_flag == false)
    {
        ReadSerialDiNum = 4;
        SetAllDoClose(0xFE);
        usleep(100*1000);               
        SetSerialDo(1, 3, 1); // 先收拢座椅 
        Swich_status = 2; 
        while (stand_flag == false)
        {
            usleep(100 * 1000); // 等到收拢
            if(states[0] == false)
                pthread_exit(0);
        }
    }
    // 分隔幕打开
    if(patition_flag == true)
    {      
        ReadSerialDiNum = 13;
        SetAllDoClose(0xFE);
        usleep(100 * 1000);
        SetSerialDo(3, 0, 1); // 打开D01 
        while (patition_flag == true)
        {
            usleep(100 * 1000); // 等到下降
            if(states[0] == false)
                pthread_exit(0);
        }
    }
    // 球架下降
    for(int i = 1; i < 5; i++)
    {
        if(basketball_flag[i - 1] == true)
        {
            set_basketball_stands_state(i, 1); 
            while (basketball_flag[i - 1] == true)
            {
                usleep(100 * 1000); // 等到下降
                if(states[0] == false)
                    pthread_exit(0);
            }
        }       
    }
    // 关灯
    usleep(100 *1000);
    SetSerialDo(3, 2, 0);
}

static void lv_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    int num = (int)lv_event_get_user_data(e);

    if (code == LV_EVENT_CLICKED)  
    { 
        
        for (int i = 0; i < 3; i++)
        {
            if (obj == mode_labels[i]->parent)
            {
                states[i] = !states[i];
                toggle_image(obj, i, 0);
            }
            else
            {
                states[i] = false;
                toggle_image(mode_labels[i]->parent, i, 1);
            }
        }
        printf("%d\n",num);
        if(num == 0)   // 训练模式
        {
            pthread_t mode1_pid;
            pthread_create(&mode1_pid, NULL, mode1_handler, NULL);
            pthread_detach(mode1_pid);
        }
        else if(num == 1)  // 演出模式
        {
            pthread_t mode2_pid;
            pthread_create(&mode2_pid, NULL, mode2_handler, NULL);
            pthread_detach(mode2_pid);
        }

        else if(num == 2)  // 退场模式
        {
            pthread_t mode3_pid;
            pthread_create(&mode3_pid, NULL, mode3_handler, NULL);
            pthread_detach(mode3_pid);
        }
    }
}

static lv_obj_t *lv_d_label_create(lv_obj_t *obj)
{
    lv_obj_t *label = lv_label_create(obj);
    lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -20);
    lv_label_set_text(label, "");
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_20, LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(label, lv_color_hex(0x14E7F0), LV_STATE_CHECKED);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_add_flag(obj, LV_OBJ_FLAG_CLICKABLE);
    return label;
}

static lv_obj_t *lv_c_label_create(lv_obj_t *obj, char *txt)
{
    lv_obj_t *label = lv_label_create(obj);
    lv_label_set_text(label, txt);
    lv_obj_set_style_text_font(label, &PuHuiTi_Regular_20, 0);
    lv_obj_set_style_text_color(label, lv_color_hex(0xffffff), 0);
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    return label;
}
static lv_obj_t *lv_home_card_create(lv_obj_t *parent, int x, int y)
{
    lv_obj_t *card = lv_img_create(parent);
    lv_img_set_src(card, &card_background);
    lv_obj_set_pos(card, x, y);
    lv_obj_set_style_bg_opa(card, LV_OPA_0, 0);
    return card;
}

void CreateModePage(lv_obj_t *obj)
{
    static const char *mode_names[] = {"训练模式", "演出模式", "退场模式"};
    static lv_obj_t *mode_cards[3];
    static lv_obj_t *mode_images[3];
    // 创建卡片
    for (int i = 0; i < 3; i++)
    {   
        mode_cards[i] = lv_home_card_create(obj, 30 + 270 * i, 150);
        mode_images[i] = lv_img_create(mode_cards[i]);
        lv_img_set_src(mode_images[i], i == 0 ? &mode1_on : i == 1 ? &mode2_off
                                                        :  &mode3_off
                                                                   );
        lv_c_label_create(mode_cards[i], mode_names[i]);
        mode_labels[i] = lv_d_label_create(mode_images[i]);
        
        lv_obj_add_event_cb(mode_images[i], lv_event_handler, LV_EVENT_ALL, (void *)i);
    }

}
