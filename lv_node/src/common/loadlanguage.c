// /*
//  * @Description: 
//  * @Author: mai
//  * @LastEditors: mai
//  * @Date: 2023-07-03 15:15:49
//  * @LastEditTime: 2023-07-03 15:18:11
//  * @FilePath: /new_home_smart/lv_node/src/common/loadlanguage.c
//  */
// /*
//  * @Description:
//  * @Author: mai
//  * @LastEditors: mai
//  * @Date: 2023-03-09 11:28:42
//  * @LastEditTime: 2023-07-03 15:17:55
//  * @FilePath: /new_home_smart/lv_node/src/mode.c
//  */

// #include "ui_app.h"

// lv_obj_t *mode_labels[4];
// bool is_english;

// // 加载语言文件并更新文本内容
// // 定义关联数组 lang_strings
// static lv_obj_t *lang_strings[4];

// // 加载语言文件并更新文本内容
// void load_language(const char *filename)
// {
//     FILE *file = fopen(filename, "r");
//     if (file == NULL)
//     {
//         printf("Failed to open language file: %s\n", filename);
//         return;
//     }

//     // 清空关联数组
//     // for (int i = 0; i < 4; i++)
//     // {
//     //     lang_strings[i] = NULL;
//     // }

//     // 解析文件并将文本字符串存储到关联数组中
//     char key[100];
//     char value[100];
//     int index = 0;
//     while (fscanf(file, "%s = %[^\n]", key, value) == 2)
//     {
//         printf("key: %s, value: %s\n", key, value);

       

//         if (index >= 0 && index < 4)
//         {
//             // 检查 lang_strings[index] 是否为空，如果为空则创建新的文本对象并添加到数组中
//             // if (lang_strings[index] == NULL)
//             // {
//             //     lang_strings[index] = lv_label_create(lv_scr_act());  // 或者使用适当的父对象
//             // }

//             // 更新对象的文本内容
//             lv_label_set_text(lang_strings[index], value);
//             // 更新对象的文本字体样式
//             // lv_obj_set_style_text_font(lang_strings[index], LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &your_font);
//             // 更新对象的文本颜色样式
//             lv_obj_set_style_text_color(lang_strings[index], lv_color_hex(0xffffff), LV_STATE_DEFAULT);
//             // 更新对象的文本不透明度样式
//             lv_obj_set_style_text_opa(lang_strings[index], 255, LV_STATE_DEFAULT);
//         }
//          index++;
//     }

//     fclose(file);
// }

// // 切换语言
// void switch_language(bool is_english)
// {
//     if (is_english)
//     {
//         load_language("language_en.txt");
//     }
//     else
//     {
//         load_language("language_cn.txt");
//     }

//     // 重新绘制界面以更新文本显示
//     lv_obj_invalidate(lv_scr_act());
// }

// void toggle_label(lv_obj_t *label, bool state)
// {
//     const char *text = state ? "已开启" : "未开启";
//     lv_color_t color = state ? lv_color_hex(0x14E7F0) : lv_color_hex(0xffffff);

//     lv_label_set_text(label, text);
//     lv_obj_set_style_text_color(label, color, 0);
// }

// static void lv_event_handler(lv_event_t *e)
// {
//     lv_event_code_t code = lv_event_get_code(e);
//     lv_obj_t *obj = lv_event_get_target(e);

//     if (code == LV_EVENT_CLICKED)
//     {

//         switch_language(true);
//         printf("Clicked\n");
//         // static bool states[] = {false, false, false, false};
//         // for (int i = 0; i < 4; i++)
//         // {
//         //     if (obj == mode_labels[i]->parent)
//         //     {
//         //         states[i] = !states[i];
//         //     }
//         //     else
//         //     {
//         //         states[i] = false;
//         //     }
//         //     toggle_label(mode_labels[i], states[i]);
//         // }
//     }
// }

// void CreateModePage(lv_obj_t *obj)
// {
//     static const char *mode_names[] = {"智能模式", "节能模式", "手动模式", "长假模式"};
//     // static lv_obj_t *mode_cards[4];
//     static lv_obj_t *mode_images[4];

//     for (int i = 0; i < 4; i++)
//     {
//         // mode_cards[i] = lv_obj_create(obj);
//         // lv_obj_set_size(mode_cards[i], LV_CARD_WIDTH, LV_CARD_HEIGHT);

//         mode_images[i] = lv_img_create(obj);
//         lv_obj_set_pos(mode_images[i], 10 + 221 * i, 150);
//         lv_obj_add_flag(mode_images[i], LV_OBJ_FLAG_CLICKABLE);
//         lv_img_set_src(mode_images[i], &home_auto_mode_img_map);
//         // lv_obj_align(mode_images[i], LV_ALIGN_CENTER, 0, 0);
//         lv_obj_add_event_cb(mode_images[i], lv_event_handler, LV_EVENT_CLICKED, NULL);

//         mode_labels[i] = lv_label_create(mode_images[i]);
//         lv_label_set_text(mode_labels[i], mode_names[i]);
//         lv_obj_set_style_text_font(mode_labels[i], &PuHuiTi_Regular_30, LV_STATE_DEFAULT);
//         lv_obj_set_style_text_color(mode_labels[i], lv_color_hex(0xffffff), LV_STATE_DEFAULT);
//         lv_obj_align(mode_labels[i], LV_ALIGN_CENTER, 0, 10);

//         lang_strings[i] = mode_labels[i];
//         // 创建用于显示模式状态的标签
//         // lv_obj_t *status_label = lv_label_create(mode_images[i]);
//         // // lv_label_set_long_mode(status_label, LV_LABEL_LONG_WRAP);
//         // lv_obj_align_to(status_label, mode_images[i], LV_ALIGN_OUT_TOP_MID, 0, -10);
//         // toggle_label(status_label, false);
//     }
// }
