
#ifndef _LV_SCREEN_SETTING_H
#define _LV_SCREEN_SETTING_H

typedef struct
{
    uint8_t brightness;

    char On_screen[8];  // 里面的亮度

    lv_obj_t *slider_label;

} lv_Brightting_data_t;

extern  lv_Brightting_data_t setting;

void CreateScreen(lv_obj_t *parent);
void add_Screen_event_cb(lv_event_t *e);
lv_obj_t *create_page_back(lv_obj_t *obj);

lv_obj_t *create_popup_page(lv_obj_t *parent, const char *title, lv_coord_t x, lv_coord_t y);

#endif
