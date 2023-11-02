









#ifndef __BASKETBALL_STANDS_H__
#define __BASKETBALL_STANDS_H__

extern bool basketball_flag[4];

void basketball_Controls_event_cb(lv_event_t *e);
void CreateBasketballStandsPage(uint8_t device_num);
void set_basketball_stands_state(uint8_t num, uint8_t state);


#endif //__SMART_SEAT_BIG_H__