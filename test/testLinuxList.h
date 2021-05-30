#ifndef TEST_LINUXLIST_H_
#define TEST_LINUXLIST_H_

#include "gtest/gtest.h"
#include "LinuxList.h"
#include <string>

/**
 * @fn
 * @brief      测试Linux内核链表，将list_head放在结构体头部
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinuxList, list_headInStructHead)
{
    struct Node 
    {
        struct list_head head;
        int value;
    };

    /* 链表头结点 */
    struct Node headNode = {0};
    struct list_head * list = (struct list_head *)&headNode;

    struct list_head * slide = nullptr;

    /* 初始化list_head */
    INIT_LIST_HEAD(list);

    /* 插入结点 */
    for(int i = 0; i < 5; i++)
    {
        /* 创建结点 */
        struct Node * node = (struct Node *)malloc(sizeof(struct Node));
        node->value = i;

        /* 插入链表尾部 */
        list_add_tail((struct list_head *)node, list);
    }

    /* 遍历获取结点值 */
    {
        int index = 0;
        list_for_each(slide, list)
        {
            EXPECT_EQ(((struct Node*)slide)->value, index);
            index++;
        }
    }

    /* 删除值为3的结点 */
    list_for_each(slide, list)
    {
        int value = ((struct Node*)slide)->value;
        if(value == 3)
        {
            list_del(slide);
            free(slide);

            /* 删除完成后立即跳出循环 */
            break;
        }
    }

    /* 遍历获取结点值 */
    {
        int index = 0;
        int buf[] = {0, 1, 2, 4};
        list_for_each(slide, list)
        {
            EXPECT_EQ(((struct Node*)slide)->value, buf[index]);
            index++;
        }
    }
}

/**
 * @fn
 * @brief      测试Linux内核链表，将list_head放在结构体尾部
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinuxList, list_headInStructTail)
{
    typedef struct 
    {
        char str[64];
    }Message;

    struct Node 
    {
        Message message;
        struct list_head head;
    };

    /* 链表头结点 */
    struct Node headNode = {0};

    struct list_head * list = &headNode.head;
    struct list_head * slide = nullptr, * tempSlide = nullptr;

    /* 初始化list_head */
    INIT_LIST_HEAD(list);

    /* 插入结点 */
    for(int i=0;i<5;i++)
    {
        Message temp = {0};
        /* 创建结点 */
        struct Node * node = (struct Node*)malloc(sizeof(struct Node));
        snprintf(temp.str, sizeof(temp.str), "hello%d",i);
        node->message = temp;


        /* 插入链表头部 */
        list_add(&node->head, list);
    }

    /* 遍历获取结点值 */
    {
        int index = 4;
        list_for_each(slide, list)
        {
            Message temp = {0};
            snprintf(temp.str, sizeof(temp.str), "hello%d", index);
            index--;

            EXPECT_STREQ(list_entry(slide, struct Node, head)->message.str, temp.str);
        }    
    }


    /* 删除某个结点 */
    list_for_each_safe(slide, tempSlide, list)
    {
        struct Node * node = list_entry(slide, struct Node, head);
        if(std::string(node->message.str) == std::string("hello3"))
        {
            list_del(slide);
            free(node);
            break;
        }
    }

    /* 遍历获取结点值 */
    {
        int index = 0;
        list_for_each_safe(slide, tempSlide, list)
        {
            int buf[] = {4, 2, 1, 0};
            Message temp = {0};

            snprintf(temp.str, sizeof(temp.str), "hello%d", buf[index]);
            index++;

            EXPECT_STREQ(list_entry(slide, struct Node, head)->message.str, temp.str);
        }
    }
}

#endif
