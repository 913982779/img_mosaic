/*******************************************************************************
 *
 * \file    homoEstimation.h
 * \brief   ��Ӧ�Թ���ģ��
 * \author  1851738��𩶬
 * \version 2.0
 * \date    2021-06-11
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-09  | v1.0    | 1851738��𩶬  |
 * 2021-06-11  | v2.0    | 1851738��𩶬  |
 * 2021-06-17  | v3.0    | 1853735�����  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/calib3d/calib3d.hpp"
#include "publicElement.h"
#include"ransac_personal.h"
#include <iostream>
using namespace cv;
using namespace std;

#pragma once
#ifndef HOMOESTIMATION_H
#define HOMOESTIMATION_H

class homoEst
{
public:
    typedef struct
    {
        Point2f left_top;
        Point2f left_bottom;
        Point2f right_top;
        Point2f right_bottom;
    }homo_corners;

    homo_corners corners;                       // ��Ӧ�Ա任��ͼ����ĸ���
    vector<Point2f> srcPoints_1, srcPoints_2;   // ӳ��㼯
    int imgHeight;                              // ͼ��� .pix
    int imgWidth;                               // ͼ��� .pix
    Mat H;                                      // ��Ӧ�Ծ���
    int rightBound;                             // ��Ӧ�任��ͼ����ұ߽�
    int leftBound;                              // ��Ӧ�任��ͼ�����߽�
    int topBound;                               // ��Ӧ�任��ͼ����ϱ߽�
    int bottomBound;                            // ��Ӧ�任��ͼ����±߽�

public:
    /*
     * @breif:���캯��
     * @prama[in]:InputArray srcPoints_1, InputArray srcPoints_2->����ӳ��㼯(����4��)
     * @prama[in]:MatSize imgSize->Դͼ��ߴ�
     */
    homoEst(vector<Point2f> srcPoints_1, vector<Point2f> srcPoints_2, MatSize imgSize);
    homoEst();

    /*
     * @breif:��ӡӳ���ͼ����Ľǵ����ꡢ��ӡ�任��ͼ��߽�����
     * @prama[in]:None
     * @retval:None
     */
    void printCorner();
    void printBound();

    /*
     * @breif:����ӳ���ԣ���Դͼ���ĵ�Ӧ�Ծ���(����)
     * @prama[in]:dir:1->��src1��src2��ӳ��(Ĭ��),dir:0->��src2��src1��ӳ��
     * @retval:None
     */
    void findHomography_Base(int dir=1);

    /*
     * @breif:���㵥Ӧ�Ա任��ͼ��ı߽�����
     * @prama[in]:dir:1->��src1��src2��ӳ��(Ĭ��),dir:0->��src2��src1��ӳ��
     * @retval:None
     */
    void calTransBound(int dir=1);

    /*
     * @breif:��ȡ������Ӧ�任���ͼ��
     * @prama[in]:srcImg->�任ǰ��ԭͼ��H->��Ӧ�任����; mapSize->�任��ͼ��Ĵ�С��debug->����ģʽ
     * @retval:dstImg->�任���ͼ��
     */
    Mat imgMapByHomo(Mat& srcImg, Mat& H, Size mapSize, int debug= DEBUGMODE_NORMAL);

private:
    /*
     * @breif:���㵥Ӧ�Ա任��ͼ����ĸ�������
     * @prama[in]:dir:1->��src1��src2��ӳ��(Ĭ��),dir:0->��src2��src1��ӳ��
     * @retval:None
     */
    void calCorners(int dir = 1);
};

#endif // !HOMOESTIMATION_H
