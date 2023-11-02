





/* 
    四个球架8个DI和DO
    第一个6路继电器的5、6号
    和第二个6路继电器的所有
 */


#include "ui_app.h"

DevicePageData basketball_stands_data = {0};
DevicePageData *bs_data = &basketball_stands_data;
extern bool stop_flag;

bool basketball_flag[4] = {false, false, false, false}; // true为收拢

/* 通过state的值选择打开的电机 */
void set_basketball_stands_state(uint8_t num, uint8_t state)
{
    
    switch (num) // 选择设备号
    {
    case 1:// 球架1, 使用从机1的DO5控制展开电机，DO6控制收拢电机
        ReadSerialDiNum = 6 - state;  // 打开哪个DO就检测对应DI 
        SetSerialDo(1, 5 - state, 1); // state为1时展开球架，打开DO5，为0时打开DO6
        break;

    case 2:// 球架2, 使用从机2的DO1控制展开电机，DO2控制收拢电机
        ReadSerialDiNum = 8 - state;
        SetSerialDo(2, 1 - state, 1);  
        break;

    case 3:// 球架3, 使用从机2的DO3控制展开电机，DO4控制收拢电机
        ReadSerialDiNum = 10 - state;
        SetSerialDo(2, 3 - state, 1); 
        break;

    case 4:// 球架4, 使用从机2的DO5控制展开电机，DO6控制收拢电机
        ReadSerialDiNum = 12 - state;
        SetSerialDo(2, 5 - state, 1); 
        break;

    default:
        break;
    }
    
}


// 篮球架控制
void basketball_Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    index_t *user_data = lv_event_get_user_data(e);
    uint8_t index = user_data->ind; // 判断按钮号
    uint8_t device_num = user_data->num;

    if (code == LV_EVENT_CLICKED)
    {
        switch (index)
        {
        case 0: // 看台收拢才能打开球架
            if(stop_flag == false && stand_flag)
            {            
                SetAllDoClose(0xFE); // 广播地址全关  
                usleep(100 * 1000);
                set_basketball_stands_state(device_num, 1);
            }    
            break;            
        case 1:
            if(stop_flag == false) // 急停
            {
                stop_flag = true;
                lv_obj_add_state(obj, LV_STATE_PRESSED);
                SetAllDoClose(0xFE); // 广播地址全关
            
            }
            else
            {
                stop_flag = false;
                lv_obj_clear_state(obj, LV_STATE_PRESSED);
            }
            break;          
        case 2: // 收拢球架
            if(stop_flag == false)
            {
                SetAllDoClose(0xFE);
                usleep(100 * 1000);
                set_basketball_stands_state(device_num, 0);
            }
            break;
        }
    }
}
void CreateBasketballStandsPage(uint8_t device_num)
{

  
  bs_data->deviceName = "悬空球架";
  bs_data->intro = "设备简介: 篮球架悬挂空中，远程联网\n"
                   "控制，释放场地空间\n";
  bs_data->date = "2023-7-4";
  bs_data->period = "6 months";
  bs_data->phoneNumber = "+86 755 26490688";
  bs_data->image = &basketball_stands_img;
  bs_data->expandBtnText = "一键打开";
  bs_data->emergencyStopBtnText = "急停";
  bs_data->collapseBtnText = "一键收合";

  bs_data->StandOpenBtnText = NULL;
  bs_data->StandClosureBtnText = NULL;
  bs_data->SeatRiseBtnText = NULL;
  bs_data->SeatTipBtnText = NULL;

  bs_data->ManufacturingTel = "12345678";
  bs_data->SalehAfterotline = "12345679";
  bs_data->SolveProblem = "Solution";
  bs_data->Description = "Condition";
  bs_data->PopupTitlie = "Inspection personnel must perform the inspection in a timely manner\n"
                            "            according to the inspection time and contents";
  bs_data->PopupContent = " Maintenance\n"
                            "normal report";

  CreatebasketballPageBg(bs_data, device_num);

}
