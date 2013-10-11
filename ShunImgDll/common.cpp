#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
#include <math.h>
#include <stdio.h>
#include "iostream"
using namespace cv;


IplImage* getInputImg(const uchar inImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = cvCreateImage(cvSize(width,height),depth,nChannels);//�½�һ��һ����С��ͼ��
    int bytes = in->widthStep*in->height;
    memcpy((uchar*)in->imageData,inImgData,bytes);//�����ݿ�����inͼ��
    return in;
}

void outputData(uchar outImgData[],IplImage* out)
{
    int bytes = out->widthStep*out->height;
    memcpy(outImgData,(uchar*)out->imageData,bytes);//����С�����ݿ�����outͼ��
}



