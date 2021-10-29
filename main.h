/*******************************************************************************
 *
 * \file    main.h
 * \brief   ͼ��ƴ��������
 * \author  1851738��𩶬
 * \version 3.0
 * \date    2021-06-17
 *
 * -----------------------------------------------------------------------------
 *
 * -----------------------------------------------------------------------------
 * �ļ��޸���ʷ��
 * <ʱ��>       | <�汾>  | <����>         |
 * 2021-06-11  | v1.0    | 1851738��𩶬  |
 * 2021-06-12  | v2.0    | 1851738��𩶬  |
 * 2021-06-17  | v3.0    | 1853735�����  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "imgProcess.h"
#include "homoEstimation.h"
#include "featureDesc.h"
#include "featureMatch.h"

#pragma once
#ifndef MAIN_H
#define MAIN_H

/*
 * @breif:ͼ��ƴ��������
 * @prama[in]:handle->ͼ������;leftImg->��ƴ�ӵ���ͼ;rightImg->��ƴ�ӵ���ͼ;
 * @prama[in]:detectMode->���ģʽ(SIFT��ORB��BRISK��)
 * @prama[in]:matchType->ƥ������(minmax�㷨��low's�㷨)
 * @prama[in]:debug->����ģʽ
 * @retval:mosaicImg->��leftImg��rightImgƴ�Ӷ��ɵ�ͼ��
 */
Mat imageMosaic(imgProcess handle, Mat leftImg, Mat rightImg,int detectMode, int matchType, int debug = DEBUGMODE_SHOW)
{
    /*===================================================================================*/
    /******************************** �����������Դ�� **************************************/
    /*===================================================================================*/
    featureDesc featureDescHandle;                          // ���������������
    featureMatch featureMatchHandle;                        // ��������ƥ����
    MatSize imgSize = rightImg.size;                        // ����ƴ��ͼ��ߴ�
    vector<KeyPoint> keyPtRight, keyPtLeft;                 // �����ؼ���
    Mat imgDescRight, imgDescLeft;                          // ����������
    vector<DMatch> goodMatchPt;                             // ��������ƥ����
    vector<Point2f> goodPtLeft, goodPtRight;                // ��������ƥ���
    Mat grayImgLeft, grayImgRight;                          // �����Ҷ�ͼ
    cvtColor(leftImg, grayImgLeft, COLOR_RGB2GRAY);
    cvtColor(rightImg, grayImgRight, COLOR_RGB2GRAY);
    /*-----------------------------------------------------------------------------------*/


    /*===================================================================================*/
    /******************************** ������⡢������ƥ�� ***********************************/
    /*===================================================================================*/
    if (detectMode == SIFTDETECT)
    {
        featureDescHandle.getFeatureDesc_SIFT(grayImgLeft, keyPtLeft, imgDescLeft);
        featureDescHandle.getFeatureDesc_SIFT(grayImgRight, keyPtRight, imgDescRight);
        goodMatchPt = featureMatchHandle.featureMatch_MinMax(imgDescLeft, imgDescRight, 2, MATCHMODE_NORML2);
    }
    else if (detectMode == SURFDETECT)
    {
        featureDescHandle.getFeatureDesc_SURF(grayImgLeft, keyPtLeft, imgDescLeft);
        featureDescHandle.getFeatureDesc_SURF(grayImgRight, keyPtRight, imgDescRight);
        goodMatchPt = featureMatchHandle.featureMatch_MinMax(imgDescLeft, imgDescRight, 2, MATCHMODE_NORML2);
    }
    else if (detectMode == ORBDETECT)
    {
        featureDescHandle.getFeatureDesc_ORB(grayImgLeft, keyPtLeft, imgDescLeft);
        featureDescHandle.getFeatureDesc_ORB(grayImgRight, keyPtRight, imgDescRight);
        if (matchType)
            goodMatchPt = featureMatchHandle.featureMatch_MinMax(imgDescLeft, imgDescRight, 2.4, MATCHMODE_HAMMING);
        else
            goodMatchPt = featureMatchHandle.featureMatch_Lows(imgDescLeft, imgDescRight, 0.5, MATCHMODE_HAMMING);
    }
    else if (detectMode == BRISKDETECT)
    {
        featureDescHandle.getFeatureDesc_BRISK(grayImgLeft, keyPtLeft, imgDescLeft);
        featureDescHandle.getFeatureDesc_BRISK(grayImgRight, keyPtRight, imgDescRight);
        goodMatchPt = featureMatchHandle.featureMatch_MinMax(imgDescLeft, imgDescRight, 2.3, MATCHMODE_HAMMING);
    }
    featureMatchHandle.getGoodPt(goodMatchPt, keyPtRight, keyPtLeft, goodPtRight, goodPtLeft);
    //++++

    if (debug == DEBUGMODE_GETMATCH)
    {
        Mat imgMatch;
        drawMatches(leftImg, keyPtLeft, rightImg, keyPtRight, goodMatchPt, imgMatch, Scalar(0, 255, 255));
        return imgMatch;
    }
    /*-----------------------------------------------------------------------------------*/


    /*===================================================================================*/
    /************************************ ��Ӧ�Թ��� ***************************************/
    /*===================================================================================*/
    homoEst homographyMap(goodPtRight, goodPtLeft, imgSize);         // ����ͼΪ��׼,��ͼӳ�䵽��ͼ
    homographyMap.findHomography_Base();    //++++change++++
    homographyMap.calTransBound();
    Size mapSize = Size(homographyMap.rightBound, imgSize[0]);       // ӳ��ͼƬ��С
    Mat imgMapByHomo = homographyMap.imgMapByHomo(rightImg, homographyMap.H, mapSize);
    if (debug == DEBUGMODE_GETHOMO)  return imgMapByHomo;
    /*-----------------------------------------------------------------------------------*/


    /*===================================================================================*/
    /************************************ ͼ����׼������ ***********************************/
    /*===================================================================================*/
    Mat dstImg = handle.imgMosaic(leftImg, imgMapByHomo);
    if (debug == DEBUGMODE_GETMOSAIC)   return dstImg;
    handle.seamOpt_alpha(leftImg, imgMapByHomo, dstImg, homographyMap.leftBound, imgSize[1]);
    if(debug==DEBUGMODE_SHOW)           return dstImg;
    /*-----------------------------------------------------------------------------------*/
}

#endif // !MAIN_H
