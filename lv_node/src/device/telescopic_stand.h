/*** 
 * @Description: 伸缩活动看台
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-07-03 13:58:54
 * @LastEditTime: 2023-07-07 19:33:22
 * @FilePath: /lingxiantiyu_compile/lv_node/src/device/telescopic_stand.h
 */
#ifndef __TELESCOPIC_STAND_H__
#define __TELESCOPIC_STAND_H__
 void Controls_event_cb(lv_event_t *e);

void CreateTelescopicStandPage(void);


extern uint8_t ReadSerialDiNum;    //读取DI的编号 
extern int Swich_status;
#endif //__TELESCOPIC_STAND_H__