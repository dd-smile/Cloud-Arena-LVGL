




#include "ui_app.h"

DevicePageData partition_curtain_data = {0};
DevicePageData *pc_data = &partition_curtain_data; // 分隔幕的详情页信息

extern bool stop_flag;

bool patition_flag = false; // true为收拢
// 分隔幕
void partition_Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    
    index_t *user_data = lv_event_get_user_data(e);
    uint8_t index = user_data->ind; // 判断按钮号
    //printf("index %d\n",index);
    if (code == LV_EVENT_CLICKED)   
    {
        switch (index)
        {
        case 0:
            if(stop_flag == false && stand_flag)
            {
                ReadSerialDiNum = 13;
                SetAllDoClose(0xFE);
                usleep(100 * 1000);
                SetSerialDo(3, 0, 1); // 打开D01                               
            }    
            break;            
        case 1:
            if(stop_flag == false)
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
        case 2:
            if(stop_flag == false)
            {
                ReadSerialDiNum = 14;
                SetAllDoClose(0xFE);
                usleep(100 * 1000);                
                SetSerialDo(3, 1, 1); // 打开D02
            }          
            break;
        }
    }
}
void CreatePartitionCurtianPage(uint8_t device_num)
{

  
  pc_data->deviceName = "自动分隔幕";
  pc_data->intro = "设备简介: 可变场地分隔，结构轻巧灵\n"
                    "活、安全高效、阻隔噪音\n";
  pc_data->date = "2023-7-4";
  pc_data->period = "6 months";
  pc_data->phoneNumber = "+86 755 26490688";
  pc_data->image = &partition_curtain_img;
  pc_data->expandBtnText = "一键打开";
  pc_data->emergencyStopBtnText = "急停";
  pc_data->collapseBtnText = "一键收合";

  pc_data->StandOpenBtnText = NULL;
  pc_data->StandClosureBtnText = NULL;
  pc_data->SeatRiseBtnText = NULL;
  pc_data->SeatTipBtnText = NULL;

  pc_data->ManufacturingTel = "12345678";
  pc_data->SalehAfterotline = "12345679";
  pc_data->SolveProblem = "Solution";
  pc_data->Description = "Condition";
  pc_data->PopupTitlie = "Inspection personnel must perform the inspection in a timely manner\n"
                            "            according to the inspection time and contents";
  pc_data->PopupContent = " Maintenance\n"
                            "normal report";

  CreatePartitionPageBg(pc_data, device_num);


}
