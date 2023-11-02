/*
 * @Description: 伸缩活动看台
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-07-03 13:58:49
 * @LastEditTime: 2023-07-07 19:33:15
 * @FilePath: /lingxiantiyu_compile/lv_node/src/device/telescopic_stand.c
 */
#include "ui_app.h"
DevicePageData lvPageData = {0};
DevicePageData *pPageData = &lvPageData;
uint8_t ReadSerialDiNum;

int Swich_status = -1;

bool stop_flag = false;

bool stand_flag = false; // 看台标志位，true为收拢
bool chair_flag = false; // 座椅标志位，true为收拢
 
/* 判断球架和分隔幕有没有全部收起，全部收起返回 true */
bool are_all_devices_close()
{
    // 判断球架
    bool state_basketball = true;
    for(int i = 0; i < 4; i++)
    {
        if(basketball_flag[i] == false)
            state_basketball = false;
    }

    bool state_all = false;
    if(state_basketball == true && patition_flag == true)
    {
        state_all = true;
    }

    return state_all;
}

/* 
    设备卡片看台控制，
    从机1的DO1控制看台展开电机，DO2看台收拢电机，
    DO3座椅展开电机，DO4座椅收拢电机 
*/
void telescoopic_Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    index_t *user_data = lv_event_get_user_data(e);
    uint8_t index = user_data->ind; // 判断按钮号

    if (code == LV_EVENT_CLICKED)
    {
        switch (index)
        {
        case 0: // 一键打开
            if(stop_flag == false) /*  && are_all_devices_close() */
            {
                ReadSerialDiNum = 1;
                SetAllDoClose(0xFE);
                usleep(100 * 1000);
                SetSerialDo(1, 0, 1); // 展开看台              
            }    
            break;            
        case 1:
            if(stop_flag == false)
            {
                stop_flag = true;
                lv_obj_add_state(obj, LV_STATE_PRESSED);
                SetAllDoClose(0xFE);
            }
            else
            {
                stop_flag = false;
                lv_obj_clear_state(obj, LV_STATE_PRESSED);
            }
            
            break;          
        case 2: // 一键关闭
            if(stop_flag == false)
            {
                ReadSerialDiNum = 4;
                SetAllDoClose(0xFE);
                usleep(100*1000);               
                SetSerialDo(1, 3, 1); // 先收拢座椅       
            } 
            break;
        }
        Swich_status = index;
    }
}

/* 详情页面控制按钮 */
void Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    index_t *user_data = lv_event_get_user_data(e);
    uint8_t index = user_data->ind; // 判断按钮号

    if (code == LV_EVENT_CLICKED)
    {
        if (index >= 3) // 若是下方4个按钮   && are_all_devices_close()
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (i != index - 3)
                {
                    SetSerialDo(1, i, 0); // 其余电机关闭
                }
            }
        }
        switch (index)
        {
        case 0:  // 一键打开
           if(stop_flag == false)  //  && are_all_devices_close()
            {
                ReadSerialDiNum = 1;
                SetAllDoClose(0xFE);
                usleep(100 * 1000);
                SetSerialDo(1, 0, 1); // 展开看台
            } 
            break;

        case 1:  // 急停
            if(stop_flag == false)
            {
                stop_flag = true;
                lv_obj_add_state(obj, LV_STATE_PRESSED);
                SetAllDoClose(0xFE);
            }
            else
            {
                stop_flag = false;
                lv_obj_clear_state(obj, LV_STATE_PRESSED);
            }
            break;

        case 2:  // 一键关闭
            if(stop_flag == false)
            {
                ReadSerialDiNum = 4;
                SetAllDoClose(0xFE);
                usleep(100*1000);               
                SetSerialDo(1, 3, 1); // 先收拢座椅       
            } 
            
            break;

        case 3:  // 打开看台
            if(stop_flag == false ) // && are_all_devices_close()
            {
                ReadSerialDiNum = 1;
                SetSerialDo(1, 0, 1);
            }
            break;

        case 4: // 收拢看台，座椅收起是才能收拢
            if(stop_flag == false && chair_flag) 
            {
                ReadSerialDiNum = 2;
                SetSerialDo(1, 1, 1);
            }              
            break;

        case 5: // 打开座椅，看台打开才能打开
            if(stop_flag == false && !stand_flag)
            {
                ReadSerialDiNum = 3;
                SetSerialDo(1, 2, 1);
            }
            break;

        case 6: // 收拢座椅
            if(stop_flag == false)
            {
                ReadSerialDiNum = 4;
                SetSerialDo(1, 3, 1);
            }
            break;
        }
        Swich_status = index; // 保存区分按钮一键或单独控制
    }
}

void CreateTelescopicStandPage(uint8_t device_num)
{

    pPageData->deviceName = "伸缩活动看台";
    pPageData->intro = "设备简介: 解决高规格场馆对于高排数、\n"
                       "静音稳定的看台需求。\n";
    pPageData->date = "2023-7-4";
    pPageData->period = "6 months";
    pPageData->phoneNumber = "+86 755 26490688";
    pPageData->image = &telescopic_stand_big;
    pPageData->expandBtnText = "一键打开";
    pPageData->emergencyStopBtnText = "急停";
    pPageData->collapseBtnText = "一键收合";

    pPageData->StandOpenBtnText = "看台展开";
    pPageData->StandClosureBtnText = "看台收缩";
    pPageData->SeatRiseBtnText = "座椅上升";
    pPageData->SeatTipBtnText = "座椅下降";

    pPageData->ManufacturingTel = "12345678";
    pPageData->SalehAfterotline = "12345679";
    pPageData->SolveProblem = "Solution";
    pPageData->Description = "Condition";
    pPageData->PopupTitlie = "Inspection personnel must perform the inspection in a timely manner\n"
                             "            according to the inspection time and contents";
    pPageData->PopupContent = " Maintenance\n"
                              "normal report";

    CreateDevicePageBg(pPageData, device_num);
}
