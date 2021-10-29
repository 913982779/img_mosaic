/*******************************************************************************
 *
 * \file    featureDesc.h
 * \brief   ͼ����������
 * \author  1851738��𩶬  +   1853735�����
 * \version 3.0
 * \date    2021-06-17
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-11  | v2.0    | 1851738��𩶬  |
 * 2021-06-17  | v3.0    | 1853735�����  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d.hpp>
//#include <opencv2/xfeatures2d.hpp>
using namespace cv;
using namespace std;

#pragma once
#ifndef FEATUREDESC_H
#define FEATUREDESC_H

class featureDesc
{
public:
	/*
	 * @breif:��������������ORB�㷨
	 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
	 * @retval:None
	 */
	void getFeatureDesc_ORB(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc);

	/*
	 * @breif:��������������SIFT�㷨
	 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
	 * @retval:None
	 */
	void getFeatureDesc_SIFT(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc);

	/*
	 * @breif:��������������BRISK�㷨
	 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
	 * @retval:None
	 */
	void getFeatureDesc_BRISK(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc);
	/*
	 * @breif:��������������SURF�㷨
	 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
	 * @retval:None
	 */
	void getFeatureDesc_SURF(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc);
};


#endif // !FEATUREDESC_H