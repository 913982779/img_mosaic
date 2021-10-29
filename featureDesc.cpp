/*******************************************************************************
 *
 * \file    featureDesc.cpp
 * \brief   ͼ����������
 * \author  1851738��𩶬
 * \version 2.0
 * \date    2021-06-17
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-11  | v1.0    | 1851738��𩶬  |
 * 2021-06-11  | v2.0    | 1853735�����  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "featureDesc.h"

/*
 * @breif:��������������ORB�㷨
 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
 * @retval:None
 */
void featureDesc::getFeatureDesc_ORB(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc)
{
	Ptr<ORB> OrbFeature = ORB::create();
	OrbFeature->detectAndCompute(srcGray, Mat(), keyPoint, Desc);
}

/*
 * @breif:��������������SIFT�㷨
 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
 * @retval:None
 */
void featureDesc::getFeatureDesc_SIFT(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc)
{
	Ptr<Feature2D> siftFeature = SIFT::create();
	siftFeature->detect(srcGray, keyPoint);
	siftFeature->compute(srcGray, keyPoint, Desc);
}

/*
 * @breif:��������������SURF�㷨
 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
 * @retval:None
 */
//void featureDesc::getFeatureDesc_SURF(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc)
//{
//	Ptr<cv::xfeatures2d::SURF> surfFeature = cv::xfeatures2d::SURF::create(1000);
//	surfFeature->detect(srcGray, keyPoint);
//	surfFeature->compute(srcGray, keyPoint, Desc);
//}

/*
 * @breif:��������������BRISK�㷨
 * @prama[in]:srcGray->Դͼ��ĻҶ�ͼ; keyPoint->�������������; Desc->����������Ӧ��������
 * @retval:None
 */
void featureDesc::getFeatureDesc_BRISK(Mat& srcGray, vector<KeyPoint>& keyPoint, Mat& Desc)
{
	Ptr<Feature2D> BriskFeature = BRISK::create();
	BriskFeature->detect(srcGray, keyPoint);
	BriskFeature->compute(srcGray, keyPoint, Desc);
}