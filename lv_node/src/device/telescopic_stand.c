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

void Controls_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    uint8_t index = lv_event_get_user_data(e);
    if (code == LV_EVENT_CLICKED)
    {
        if (index >= 3)
        {
            for (size_t i = 0; i < 4; i++)
            {
                if (i != index - 3)
                {
                    SetSerialDo(i, 0);
                }
            }
        }
        switch (index)
        {
        case 0:
            SetSerialDo(0, 1); // 打开D01
            ReadSerialDiNum = 1;
            break;

        case 1:
            SetSerialDo(3, 1); // 打开D04
            ReadSerialDiNum = 4;
            break;

        case 2:
            for (size_t i = 0; i < 4; i++)
            {
                SetSerialDo(i, 0);
            }
            break;

        case 3:
            SetSerialDo(0, 1);

            break;
        case 4:
            SetSerialDo(1, 1);

            break;

        case 5:
            SetSerialDo(2, 1);

            break;
        case 6:
            SetSerialDo(3, 1);

            break;
        }
        Swich_status = index;
    }
}

void CreateTelescopicStandPage(void)
{

    pPageData->deviceName = "Retractable Seating System";
    pPageData->intro = "Brief Introduction: Comply requirement\n"
                       "of high-standard venues for high-row, \n"
                       "quiet and stableseating system\n";
    pPageData->date = "2023-7-4";
    pPageData->period = "6 months";
    pPageData->phoneNumber = "+86 755 26490688";
    pPageData->image = &telescopic_stand_big;
    pPageData->expandBtnText = "Open";
    pPageData->emergencyStopBtnText = "Close";
    pPageData->collapseBtnText = "Stop";

    pPageData->StandOpenBtnText = "StandOpen";
    pPageData->StandClosureBtnText = "StandClose";
    pPageData->SeatRiseBtnText = "SeatRise";
    pPageData->SeatTipBtnText = "SeatDown";

    pPageData->ManufacturingTel = "12345678";
    pPageData->SalehAfterotline = "12345679";
    pPageData->SolveProblem = "Solution";
    pPageData->Description = "Condition";
    pPageData->PopupTitlie = "Inspection personnel must perform the inspection in a timely manner\n"
                             "            according to the inspection time and contents";
    pPageData->PopupContent = " Maintenance\n"
                              "normal report";

    CreateDevicePageBg(pPageData);
}
