/*******************************************************************************
 *
 * \file    featureMatch.h
 * \brief   ͼ������ƥ��
 * \author  1851738��𩶬
 * \version 1.0
 * \date    2021-06-11
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-11  | v2.0    | 1851738��𩶬  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
using namespace cv;
using namespace std;
using namespace cvflann;
using namespace flann;

/*===================================================================================*/
/******************************** �궨�� *********************************************/
/*===================================================================================*/
#define MAXNUMBER		   10000					// ����
#define MATCHMODE_HAMMING  0						// ��������ƥ��ģʽ
#define MATCHMODE_NORML2   1						// ���η���ƥ��ģʽ
/*-----------------------------------------------------------------------------------*/

#pragma once
#ifndef FEATUREMATCH_H
#define FEATUREMATCH_H

class featureMatch
{
public:
	/*
	 * @breif:����ƥ�䣬����Low's�㷨
	 * @prama[in]:Desc_1,Desc_2->��ƥ��ͼƬ������������,threshold->��ֵ,matchMode->ƥ��ģʽ,�궨��
	 * @retval:GoodMatchPoints->ɸѡ��������������ƥ���
	 */
	vector<DMatch> featureMatch_Lows(const Mat Desc_1, const Mat Desc_2, float threshold, int matchMode);

	/*
	 * @breif:����ƥ�䣬����minMax�㷨
	 * @prama[in]:Desc_1,Desc_2->��ƥ��ͼƬ������������,threshold->��ֵ,matchMode->ƥ��ģʽ,�궨��
	 * @retval:GoodMatchPoints->ɸѡ��������������ƥ���
	 */
	vector<DMatch> featureMatch_MinMax(const Mat Desc_1, const Mat Desc_2, float threshold, int matchMode);

	//void drawMatchImg();

	/*
	 * @breif:�������������Զ�Ӧ��ԭͼ��������
	 * @prama[in]:goodMatchPoints->ɸѡ��������������ƥ���;keyPtLeft,keyPtRight->���������㼯
	 * @prama[in]:goodPtLeft,goodPtRight->��������������
	 * @retval:None
	 */
	void getGoodPt(vector<DMatch> goodMatchPoints, vector<KeyPoint> keyPtRight, vector<KeyPoint>keyPtLeft,
		vector<Point2f>&goodPtRight, vector<Point2f>&goodPtLeft);

private:
	/*
	 * @breif:ƥ��ģʽת��ΪFlann��BFM
	 * @prama[in]:matchMode->int��ʽƥ��ģʽ
	 * @retval:matchMode->flann_distance_t��int��ʽƥ��ģʽ
	 */
	flann_distance_t matchModeTransFlann(int matchMode);
	int matchModeTransBFM(int matchMode);

	/*
	 * @breif:��ö����н�С���ϴ��������
	 * @prama[in]:Desc_1��Desc_2->����������
	 * @retval:smallDesc or largeDesc
	 */
	Mat getSmallDesc(const Mat Desc_1, const Mat Desc_2);
	Mat getLargeDesc(const Mat Desc_1, const Mat Desc_2);
};

#endif // !FEATUREMATCH_H