/*******************************************************************************
 *
 * \file    imgProcess.h
 * \brief   ͼ���������������롢�ü����ҶȻ���ƴ�ӵ�
 * \author  1851738��𩶬
 * \version 3.0
 * \date    2021-06-12
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-09  | v1.0    | 1851738��𩶬  |
 * 2021-06-11  | v2.0    | 1851738��𩶬  |
 * 2021-06-12  | v3.0    | 1851738��𩶬  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "publicElement.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;

/*===================================================================================*/
/******************************** �궨�� *********************************************/
/*===================================================================================*/
#define SHOWMODE_GRAY			   0							// �Ҷ�ģʽ
#define SHOWMODE_RGB			   1							// ��ɫģʽ
#define PYRWIDTH				  736							// ͼ�������ԭͼƬ���
#define PYRHEIGHT				  240							// 
/*-----------------------------------------------------------------------------------*/

#pragma once
#ifndef IMGPROCESS_H
#define IMGPROCESS_H

class imgProcess
{
public:
	vector<Mat> RGBImgs;							// ͼƬ����(RGB)
	vector<Mat> GrayImgs;							// ͼƬ����(�Ҷ�)
	int imgNum;										// ͼƬ����

public:
	/*
	 * @breif:���캯��,����·���µĲ�ɫ���Ӧ�Ҷ�ͼƬ��
	 * @prama[in]:string srcFileTxt->.txt��ʽ��ԴͼƬ·���ļ�
	 */
	imgProcess();
	imgProcess(string srcFileTxt);

	/*
	 * @breif:ԭͼ��ʾ
	 * @prama[in]:mode->
	 * @retval:dstImg->ƴ�Ӻ��ͼ��
	 */
	void showSrcImg(int mode = SHOWMODE_RGB);

	/*
	 * @breif:ͼ��ƴ��
	 * @prama[in]:leftImg->��ƴ��ͼ��; rightImg->��ƴ��ͼ��; debug->����ģʽ
	 * @retval:dstImg->ƴ�Ӻ��ͼ��
	 */
	Mat imgMosaic(Mat& leftImg, Mat& rightImg, int debug = DEBUGMODE_NORMAL);

	/*
	 * @breif:��ͼ��淶��ĳ����С������ԭͼ�Ĳ����ú�ɫ�������
	 * @prama[in]:srcImg->ԭͼ��; height,width->�淶�Ŀ��;
	 * @retval:dstImg->�淶���ͼ��
	 */
	Mat imgCanonical(const Mat srcImg, int height, int width);

	/*
	 * @breif:ͼ��õ���
	 * @prama[in]:srcImg->ԭͼ��; gamma->��ֵ;
	 * @note:�ù�ʽ->O=(I/255)^�� ��255
	 * @retval:dstImg->�������ͼ��
	 */
	Mat imgGammaProcess(Mat& srcImg, double gamma);

	/*
	 * @breif:ƴ�Ӵ��Ż�������alpha�Ż�����
	 * @prama[in]:leftImg->��ƴ��ͼ��; rightImg->��ƴ��ͼ��; dstImg->ƴ�Ӻ�ͼ�񡪡��Ż�����; 
	 * @prama[in]:start->�Ż��������;end->�Ż������յ�;debug->����ģʽ
	 * @retval:None
	 */
	void seamOpt_alpha(Mat& leftImg, Mat& rightImg,Mat& dstImg, int start, int end, int debug = DEBUGMODE_NORMAL);

	/*
	 * @breif:ƴ�Ӵ��Ż�������Laplace�Ż�����
	 * @prama[in]:leftImg->��ƴ��ͼ��; rightImg->��ƴ��ͼ��; dstImg->ƴ�Ӻ�ͼ�񡪡��Ż�����;
	 * @prama[in]:threshold->�Ż���ֵ;debug->����ģʽ
	 * @retval:None
	 */
	void seamOpt_laplace(Mat leftImg, Mat rightImg, Mat& dstImg, float threshold, int debug);

private:
	/*
	 * @breif:������˹������
	 * @prama[in]:srcImg->����˹����������Դͼ��;imgPyr->����������ͼ�񼯺�;level->����������
	 * @retval:None
	 */
	void buildGaussPyr(Mat srcImg, vector<Mat>& imgPyr, int level);

	/*
	 * @breif:����������˹������
	 * @prama[in]:imgGaussPyr->ͼ��ĸ�˹������;imgLaplacePyr->�����ͼ��������˹������;level->����������
	 * @retval:None
	 */
	void buildLaplacePyr(const vector<Mat> imgGaussPyr, vector<Mat>& imgLaplacePyr, int level);

	/*
	 * @breif:�����ں�������˹������
	 * @prama[in]:imgLp_1��imgLp_2->���ں�ͼ���������˹������;maskGauss->����ĸ�˹������
	 * @prama[in]:blendLp->������ں�������˹������
	 * @retval:None
	 */
	void blendLaplacePyr(const vector<Mat> imgLp_1, const vector<Mat> imgLp_2, const vector<Mat> maskGauss,
		vector<Mat>& blendLp);

	/*
	 * @breif:ͼ��������˹�ں�
	 * @prama[in]:imgHighest->ͼ���ϵ����,���������ں�ͼ���˹��������߲㰴mask��Ȩ��͵Ľ��
	 * @prama[in]:blendLp->������ں�������˹������
	 * @retval:dstImg->�ںϵ�ͼ��
	 */
	Mat imgLaplaceBlend(Mat& imgHighest, vector<Mat> blendLp);
};

#endif // !PREPROCESS_H
