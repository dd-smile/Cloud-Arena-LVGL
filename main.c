#include "lvgl/lvgl.h"
#include "lv_drivers/display/fbdev.h"
#include "lv_examples/lv_examples.h"
#include "lv_drivers/indev/evdev.h"
#include "lvgl/src/hal/lv_hal_indev.h"
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/time.h>
#include "ui_app.h"
#include "lv_node/serial/serial_mutex.h"
#define DISP_BUF_SIZE (LV_VER_RES_MAX * LV_HOR_RES_MAX)

__attribute__((weak)) int main(void)
{
  /*LittlevGL init*/
lv_init();

/*Linux frame buffer device init*/
fbdev_init();


// serial_init(&serial_handler);
/*A small buffer for LittlevGL to draw the screen's content*/
static lv_color_t buf[DISP_BUF_SIZE];
static lv_color_t buf1x[DISP_BUF_SIZE];
/*Initialize a descriptor for the buffer*/
static lv_disp_draw_buf_t disp_buf;
lv_disp_draw_buf_init(&disp_buf, buf, buf1x, DISP_BUF_SIZE);

/*Initialize and register a display driver*/
lv_disp_drv_t disp_drv;
lv_disp_drv_init(&disp_drv);
disp_drv.draw_buf = &disp_buf;
disp_drv.flush_cb = fbdev_flush;
disp_drv.hor_res = 1024;
disp_drv.ver_res = 600;
lv_disp_drv_register(&disp_drv);

/* Create a black rectangle to cover the entire screen */
lv_obj_t *screen_bg = lv_obj_create(lv_scr_act());
lv_obj_set_size(screen_bg, disp_drv.hor_res, disp_drv.ver_res);
lv_obj_set_style_border_width(screen_bg, 0, 0);
lv_obj_set_style_bg_color(screen_bg, lv_color_black(), 0);
lv_obj_set_pos(screen_bg, 0, 0);
lv_obj_add_flag(screen_bg, LV_OBJ_FLAG_CLICKABLE);

/* Create a label for the "正在启动应用程序..." text */
lv_obj_t *startup_label = lv_label_create(screen_bg);
lv_label_set_text(startup_label, "正在启动应用程序...");
lv_obj_set_style_text_color(startup_label, lv_color_white(), 0);
lv_obj_set_style_text_font(startup_label,&PuHuiTi_Regular_20, 0);
lv_obj_align(startup_label, LV_ALIGN_CENTER, 0, -30); // Adjust -30 according to your preference


/* Force an immediate screen update to display the black rectangle */
lv_refr_now(NULL);


lv_indev_drv_t indev_drv;
lv_indev_drv_init(&indev_drv); /*Basic initialization*/
evdev_init();
indev_drv.type = LV_INDEV_TYPE_POINTER; /*See below.*/
indev_drv.read_cb = evdev_read;         /*See below.*/
lv_indev_drv_register(&indev_drv);      /*Register the driver in LittlevGL*/

/* Remove the startup screen */
lv_obj_del(screen_bg);


create_lv_layout(lv_scr_act()); // 界面函数入口

/*Create a Demo*/
//
// lv_demo_widgets();
// lv_demo_printer();
// lv_demo_music();
/*Handle LitlevGL tasks (tickless mode)*/
while (1)
{
    lv_task_handler();
    usleep(5000);
}

return 0;

}


/*Set in lv_conf.h as `LV_TICK_CUSTOM_SYS_TIME_EXPR`*/
uint32_t custom_tick_get(void)
{
    static uint64_t start_ms = 0;
    if (start_ms == 0)
    {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);
    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}