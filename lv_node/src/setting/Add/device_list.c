#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "ui_app.h"

lv_device_list_t *head = NULL;

// 创建设备节点
lv_device_list_t *createNode(int device_id, int device_num, int device_type, const char *device_name)
{
    lv_device_list_t *node = (lv_device_list_t *)malloc(sizeof(lv_device_list_t));
    
    if (node == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        return NULL;
    }
    node->device_id = device_id;
    node->device_num = device_num;
    node->device_type = device_type;

    size_t name_length = strlen(device_name);
    node->device_name = (char *)malloc((name_length + 1) * sizeof(char));
    if (node->device_name == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        free(node);
        return NULL;
    }
    strcpy(node->device_name, device_name);

    node->next = NULL;

    return node;
}

// 添加节点到链表
void addNode(lv_device_list_t **head, int device_id, int device_num, int device_type,  const char *device_name)
{
    lv_device_list_t *node = createNode(device_id, device_num, device_type,device_name);
    if (node == NULL)
    {
        return;
    }

    if (*head == NULL)
    {
        *head = node;
    }
    else
    {
        lv_device_list_t *current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = node;
    }
}

/**
 * @brief ** 遍历链表查找匹配的节点
 *
 * @param head  链表头
 * @param device_id     设备id
 * @return ** lv_device_list_t*
 */
lv_device_list_t *searchNode(lv_device_list_t *head, int device_id)
{
    lv_device_list_t *temp = head;

    // 遍历链表直到找到匹配的节点或者到达链表末尾
    while (temp != NULL)
    {
        // 如果当前节点的device_id与目标device_id匹配，则返回该节点
        if (temp->device_id == device_id)
        {
            return temp;
        }
        temp = temp->next; // 移动到下一个节点
    }

    return NULL; // 没有找到匹配的节点，返回NULL
}