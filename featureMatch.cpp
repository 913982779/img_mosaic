/*******************************************************************************
 *
 * \file    featureMatch.cpp
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
 * 2021-06-11  | v1.0    | 1851738��𩶬  |
 * -----------------------------------------------------------------------------
 ******************************************************************************/
#include "featureMatch.h"

 /*===================================================================================*/
 /******************************* ���к��� *********************************************/
 /*===================================================================================*/

 /*
  * @breif:����ƥ�䣬����Low's�㷨
  * @prama[in]:Desc_1,Desc_2->��ƥ��ͼƬ������������,threshold->��ֵ,matchMode->ƥ��ģʽ,�궨��
  * @retval:GoodMatchPoints->ɸѡ��������������ƥ���
  */
vector<DMatch> featureMatch::featureMatch_Lows(const Mat Desc_1, const Mat Desc_2, float threshold, int matchMode)
{
    Mat smallDesc = featureMatch::getSmallDesc(Desc_1, Desc_2);
    Mat largeDesc = featureMatch::getLargeDesc(Desc_1, Desc_2);
    vector<DMatch> GoodMatchPoints;

    // �����������
    if (matchMode == MATCHMODE_HAMMING)
    {
        Index flannIndex(smallDesc, LshIndexParams(12, 20, 2), featureMatch::matchModeTransFlann(matchMode));
        Mat matchIndex(largeDesc.rows, 2, CV_32SC1), matchDistance(largeDesc.rows, 2, CV_32FC1);
        flannIndex.knnSearch(largeDesc, matchIndex, matchDistance, 2, SearchParams());
        for (int i = 0; i < matchDistance.rows; i++)
        {
            if (matchDistance.at<float>(i, 0) < threshold * matchDistance.at<float>(i, 1))
            {
                DMatch dmatches(i, matchIndex.at<int>(i, 0), matchDistance.at<float>(i, 0));
                GoodMatchPoints.push_back(dmatches);
            }
        }
    }

    // L2��������
    else if (matchMode == MATCHMODE_NORML2)
    {
        FlannBasedMatcher matcher;
        vector<vector<DMatch> > matchePoints;

        vector<Mat> train_desc(1, Desc_1);
        matcher.add(train_desc);
        matcher.train();
        matcher.knnMatch(Desc_2, matchePoints, 2);
        for (int i = 0; i < matchePoints.size(); i++)
        {
            if (matchePoints[i][0].distance < threshold * matchePoints[i][1].distance)
            {
                GoodMatchPoints.push_back(matchePoints[i][0]);
            }
        }
    }

    return GoodMatchPoints;
}

/*
 * @breif:����ƥ�䣬����minMax�㷨
 * @prama[in]:Desc_1,Desc_2->��ƥ��ͼƬ������������,threshold->��ֵ,matchMode->ƥ��ģʽ,�궨��
 * @retval:GoodMatchPoints->ɸѡ��������������ƥ���
 */
vector<DMatch> featureMatch::featureMatch_MinMax(const Mat Desc_1, const Mat Desc_2, float threshold, int matchMode)
{
    BFMatcher matcher(featureMatch::matchModeTransBFM(matchMode));          // ����ƥ����ģʽ
    Mat smallDesc = featureMatch::getSmallDesc(Desc_1, Desc_2);             
    Mat largeDesc = featureMatch::getLargeDesc(Desc_1, Desc_2);
    vector<DMatch> matchPoints,GoodMatchPoints;

    matcher.match(smallDesc, largeDesc, matchPoints);
    sort(matchPoints.begin(), matchPoints.end());                           // ���վ��볤������
    double minDist = matchPoints[0].distance;
    double maxDist = matchPoints[size(matchPoints) - 1].distance;

    for (int i = 0; i < smallDesc.rows; i++)
    {
        if (matchPoints[i].distance <= max(threshold * minDist, 30.0))  GoodMatchPoints.push_back(matchPoints[i]);
    }
    return GoodMatchPoints;
}

/*
 * @breif:�������������Զ�Ӧ��ԭͼ��������
 * @prama[in]:goodMatchPoints->ɸѡ��������������ƥ���;keyPtLeft,keyPtRight->���������㼯
 * @prama[in]:goodPtLeft,goodPtRight->��������������
 * @retval:None
 */
void featureMatch::getGoodPt(vector<DMatch> goodMatchPoints, vector<KeyPoint> keyPtRight, vector<KeyPoint>keyPtLeft,
    vector<Point2f>&goodPtRight, vector<Point2f>&goodPtLeft)
{
    for (int i = 0; i < goodMatchPoints.size(); i++)
    {
        if (keyPtLeft.size() < keyPtRight.size())
        {
            goodPtLeft.push_back(keyPtLeft[goodMatchPoints[i].queryIdx].pt);
            goodPtRight.push_back(keyPtRight[goodMatchPoints[i].trainIdx].pt);
        }
        else
        {
            goodPtLeft.push_back(keyPtLeft[goodMatchPoints[i].trainIdx].pt);
            goodPtRight.push_back(keyPtRight[goodMatchPoints[i].queryIdx].pt);
        }
    }
}
/*-----------------------------------------------------------------------------------*/


/*===================================================================================*/
/******************************* ˽�к��� *********************************************/
/*===================================================================================*/

/*
 * @breif:ƥ��ģʽת��ΪFlann��BFM
 * @prama[in]:matchMode->int��ʽƥ��ģʽ
 * @retval:matchMode->flann_distance_t��int��ʽƥ��ģʽ
 */
flann_distance_t featureMatch::matchModeTransFlann(int matchMode)
{
    switch (matchMode)
    {
    case(MATCHMODE_HAMMING):    return FLANN_DIST_HAMMING;
    case(MATCHMODE_NORML2):     return FLANN_DIST_L2;
    default:                    return FLANN_DIST_HAMMING;
        break;
    }  
}

int featureMatch::matchModeTransBFM(int matchMode)
{
    switch (matchMode)
    {
    case(MATCHMODE_HAMMING):    return NORM_HAMMING;
    case(MATCHMODE_NORML2):     return NORM_L2;
    default:                    return NORM_HAMMING;
        break;
    }
}

/*
 * @breif:��ö����н�С���ϴ��������
 * @prama[in]:Desc_1��Desc_2->����������
 * @retval:smallDesc or largeDesc
 */
Mat featureMatch::getSmallDesc(const Mat Desc_1, const Mat Desc_2)
{
    if (Desc_1.rows > Desc_2.rows)  return Desc_2;
    else                            return Desc_1;
}

Mat featureMatch::getLargeDesc(const Mat Desc_1, const Mat Desc_2)
{
    if (Desc_1.rows > Desc_2.rows)  return Desc_1;
    else                            return Desc_2;
}
/*-----------------------------------------------------------------------------------*/