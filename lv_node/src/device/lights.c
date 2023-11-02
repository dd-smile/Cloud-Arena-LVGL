






#include "ui_app.h"
DevicePageData lights_Data = {0};
DevicePageData *l_data = &lights_Data; // 场馆灯的详情页面信息


// 灯
void lights_Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);

    index_t *user_data = lv_event_get_user_data(e);
    uint8_t index = user_data->ind;
    if (code == LV_EVENT_CLICKED)
    {
        switch (index)
        {
        case 0:          
                SetSerialDo(3, 2, 1); // 打开D01              
            break; 

        case 1:                               
                SetSerialDo(3, 2, 0); // 打开D04                   
            break;
        }
    }
}

void CreateLightsPage(uint8_t device_num)
{

    l_data->deviceName = "灯光";
    l_data->intro = "设备简介: 智能灯光，自动调节灯光亮\n"
                    "度和色温，提高场馆舒适度。\n";
    l_data->date = "2023-7-4";
    l_data->period = "6 months";
    l_data->phoneNumber = "+86 755 26490688";
    l_data->image = &lights_img;
    l_data->expandBtnText = "打开";
    l_data->emergencyStopBtnText = NULL;
    l_data->collapseBtnText = "关闭";

    l_data->StandOpenBtnText = NULL;
    l_data->StandClosureBtnText = NULL;
    l_data->SeatRiseBtnText = NULL;
    l_data->SeatTipBtnText = NULL;

    l_data->ManufacturingTel = "12345678";
    l_data->SalehAfterotline = "12345679";
    l_data->SolveProblem = "Solution";
    l_data->Description = "Condition";
    l_data->PopupTitlie = "Inspection personnel must perform the inspection in a timely manner\n"
                             "            according to the inspection time and contents";
    l_data->PopupContent = " Maintenance\n"
                              "normal report";

    CreateLightsPageBg(l_data, device_num);
}
