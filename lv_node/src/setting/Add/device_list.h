/***
 * @Description:
 * @Author: mai
 * @LastEditors: mai
 * @Date: 2023-05-16 18:13:23
 * @LastEditTime: 2023-05-16 18:21:02
 * @FilePath:lingxiantiyu/lv_node/src/setting/Add/device_list.h
 */

#ifndef _LV_DEVICE_LIST_H
#define _LV_DEVICE_LIST_H

extern  lv_device_list_t *head;

/**
 * @brief Create a Node object
 *
 * @param device_id   设备ID
 * @param device_num    设备编号
 * @param device_type   设备类型
 * @param device_name   设备名称
 */
lv_device_list_t *createNode(int device_id, int device_num, int device_type, const char *device_name);

/**
 * @brief Add a Node object
 *
 * @param head  头指针
 * @param device_id     设备ID
 * @param device_num    设备编号
 * @param device_type   设备类型
 * @param device_name
 * @return ** void
 */
void addNode(lv_device_list_t **head, int device_id, int device_num, int device_type, const char *device_name);

/**
 * @brief   查找节点
 *
 * @param head      头指针
 * @param device_id
 * @return ** lv_device_list_t*
 */
lv_device_list_t *searchNode(lv_device_list_t *head, int device_id);

#endif

