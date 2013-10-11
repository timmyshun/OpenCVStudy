#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
#include <math.h>
#include <stdio.h>
#include "iostream"
using namespace cv;


IplImage* getInputImg(const uchar inImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = cvCreateImage(cvSize(width,height),depth,nChannels);//新建一个一样大小的图像
    int bytes = in->widthStep*in->height;
    memcpy((uchar*)in->imageData,inImgData,bytes);//将数据拷贝进in图像
    return in;
}

void outputData(uchar outImgData[],IplImage* out)
{
    int bytes = out->widthStep*out->height;
    memcpy(outImgData,(uchar*)out->imageData,bytes);//将缩小后数据拷贝进out图像
}



