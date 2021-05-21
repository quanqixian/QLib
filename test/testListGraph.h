#ifndef _TEST_LISTGRAPH_H_
#define _TEST_LISTGRAPH_H_

#include "ListGraph.h"
#include "gtest/gtest.h"
#include <SharedPointer.h>
#include <iostream>

using namespace QLib;

/**
 * @fn
 * @brief      测试Graph抽象类定义指针
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testListGraph, testGraph)
{
    Graph<int, int> * p = nullptr;
    EXPECT_EQ(p, nullptr);
}

/**
 * @fn
 * @brief      测试顶点的添加和删除
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testListGraph, testAddDelVertex)
{
    /**
     * 创建以下图结构：
     *
     *             1 
     *        ----------->          3
     *     [0]             [1] ----------->[2]
     *        <-----------
     *             2
     */
    ListGraph<int, int>  g;

    g.addVertex(100);
    g.addVertex(200);
    g.addVertex(300);

    /* 测试获取顶点值 */
    EXPECT_EQ(g.getVertex(0), 100);
    EXPECT_EQ(g.getVertex(1), 200);
    EXPECT_EQ(g.getVertex(2), 300);


    /* 测试设置边 */
    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    /* 测试删除顶点 */
    g.removeVertex();

    /* 测试边的数量 */
    EXPECT_EQ(g.eCount(), 2);

}

/**
 * @fn
 * @brief      测试顶点的获取和设置
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testListGraph, testSetGetVertex)
{
    /**
     * 创建以下图结构：
     *
     *             1 
     *        ----------->          3
     *     [0]             [1] ----------->[2]
     *        <-----------
     *             2
     */
    ListGraph<int, int>  g;

    g.addVertex();
    g.addVertex();
    g.addVertex();

    /* 测试设置顶点值 */
    g.setVertex(0, 100);
    g.setVertex(1, 200);
    g.setVertex(2, 300);

    /* 测试获取顶点值 */
    EXPECT_EQ(g.getVertex(0), 100);
    EXPECT_EQ(g.getVertex(1), 200);
    EXPECT_EQ(g.getVertex(2), 300);

    int val = 0;
    g.getVertex(0, val);
    EXPECT_EQ(val, 100);

    g.getVertex(1, val);
    EXPECT_EQ(val, 200);

    g.getVertex(2, val);
    EXPECT_EQ(val, 300);

    /* 测试顶点数量 */
    EXPECT_EQ(g.vCount(), 3);
}

/**
 * @fn
 * @brief      测试边的获取和设置
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testListGraph, testSetGetEdge)
{
    /**
     * 创建以下图结构：
     *
     *             1 
     *        ----------->          3
     *     [0]             [1] ----------->[2]
     *        <-----------
     *             2
     */

    ListGraph<int, int>  g;

    g.addVertex();
    g.addVertex();
    g.addVertex();

    /* 测试设置边 */
    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    /* 测试获取边的值 */
    EXPECT_EQ(g.getEdge(0, 1), 1);
    EXPECT_EQ(g.getEdge(1, 0), 2);
    EXPECT_EQ(g.getEdge(1, 2), 3);

    int val = 0;
    g.getEdge(0, 1, val);
    EXPECT_EQ(val, 1);

    g.getEdge(1, 0, val);
    EXPECT_EQ(val, 2);

    g.getEdge(1, 2, val);
    EXPECT_EQ(val, 3);

    /* 测试边的数量 */
    EXPECT_EQ(g.eCount(), 3);
}

/**
 * @fn
 * @brief      ListGraph综合测试
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testListGraph, comprehensiveTest)
{
    /**
     * 创建以下图结构：
     *
     *             1 
     *        ----------->          3
     *     [0]             [1] ----------->[2]
     *        <-----------
     *             2
     */

    ListGraph<int, int>  g;

    g.addVertex();
    g.addVertex();
    g.addVertex();

    g.setEdge(0, 1, 1);
    g.setEdge(1, 0, 2);
    g.setEdge(1, 2, 3);

    /* 测试顶点数量 */
    EXPECT_EQ(g.vCount(), 3);

    /* 测试边的数量 */
    EXPECT_EQ(g.eCount(), 3);

    /* 测试顶点1的入度 */
    EXPECT_EQ(g.ID(1), 1);

    /* 测试顶点1的出度 */
    EXPECT_EQ(g.OD(1), 2);

    /* 测试顶点1的度 */
    EXPECT_EQ(g.TD(1), 3);

    /* 测试边的值 */
    EXPECT_EQ(g.getEdge(0, 1), 1);
    EXPECT_EQ(g.getEdge(1, 0), 2);
    EXPECT_EQ(g.getEdge(1, 2), 3);

    /* 测试获取顶点的邻接顶点 */
    SharedPointer<Array<int> > aj = g.getAdjacent(1);
    int array[] = {0, 2};/* 存放邻接顶点，用于与获取结果做对比 */

    for(int i = 0; i < aj->length(); i++)
    {
        bool findFlag = false;
        for(int j = 0; j < sizeof(array) / sizeof(array[0]); j++)
        {
            if(array[j] == (*aj)[i])
            {
                findFlag = true;
            }
        }
        EXPECT_TRUE(findFlag);
    }
    /* 测试是否相邻 */
    EXPECT_TRUE(g.isAdjacent(0, 1));
    EXPECT_TRUE(g.isAdjacent(1, 0));
    EXPECT_TRUE(g.isAdjacent(1, 2));

    EXPECT_FALSE(g.isAdjacent(0, 2));
    EXPECT_FALSE(g.isAdjacent(2, 1));

    /* 测试删除一条边 */
    g.removeEdge(0, 1);
    EXPECT_EQ(g.eCount(), 2);

    /* 测试设置顶点值 */
    g.setVertex(0, 100);
    EXPECT_EQ(g.getVertex(0), 100);

    /* 测试获取不存在的边抛出异常 */
    bool throwFlag = false;
    try
    {
        g.getEdge(0, 1);
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);
}

#endif
