/*******************************************************************************
 *
 * \file    publicElement.h
 * \brief   项目公用组件
 * \author  1851738杨皓冬  +   1853735赵祉淇
 * \version 3.0
 * \date    2021-06-12
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * 文件修改历史：
 * <时间>       | <版本>  | <作者>         |
 * 2021-06-11  | v1.0    | 1851738杨皓冬  |
 * 2021-06-12  | v2.0    | 1851738杨皓冬  |
 * 2021-06-12  | v3.0    | 1851738赵祉淇  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#pragma once
#ifndef PUBLICELEMENT_H
#define PUBLICELEMENT_H

/*===================================================================================*/
/******************************** 宏定义 *********************************************/
/*===================================================================================*/
#define DEBUGMODE_NORMAL        0               // 调试时不显示图片
#define DEBUGMODE_SHOW          1               // 调试时显示最终图片
#define DEBUGMODE_GETMATCH      2               // 调试时获取匹配图像
#define DEBUGMODE_GETHOMO       3               // 调试时获取单应变换图像
#define DEBUGMODE_GETMOSAIC     4               // 调试时获取拼接图像

#define SIFTDETECT              0               // SIFT特征扫描
#define ORBDETECT               1               // ORB特征扫描
#define BRISKDETECT             2               // BRISK特征扫描
#define SURFDETECT              3               // SURF特征扫描


#define MATCHMODE_LOWS          0               // LOW'S匹配法
#define MATCHMODE_MINMAX        1               // MINMAX匹配法

#define WINDOW_NAME         "【图像拼接展示程序界面】"
/*-----------------------------------------------------------------------------------*/

/*===================================================================================*/
/********************************** 泛型 *********************************************/
/*===================================================================================*/
template< typename... Args >
std::string getFormatStr(const char* format, Args... args) {
    int length = std::snprintf(nullptr, 0, format, args...);
    assert(length >= 0);
    char* buf = new char[length + (long)1];
    std::snprintf(buf, length + (long)1, format, args...);
    std::string str(buf);
    delete[] buf;
    return str;
}
/*-----------------------------------------------------------------------------------*/


/*===================================================================================*/
/******************************* 内联函数 *********************************************/
/*===================================================================================*/
inline int cmpMax(int x, int y)
{
    return (x > y) ? x : y;
}

inline int cmpMin(int x, int y)
{
    return (x > y) ? y : x;
}
/*-----------------------------------------------------------------------------------*/

#endif // !PUBLICELEMENT_H