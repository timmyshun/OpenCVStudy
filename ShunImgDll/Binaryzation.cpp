#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgproc/imgproc_c.h"
#include "opencv2/legacy/legacy.hpp"
#include <math.h>
#include <stdio.h>
#include "iostream"

#include "common.hpp"
using namespace cv;

//图像增强--大津法二值化
bool BinaryzationOSTU(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//存储输入灰度图像
    IplImage* outGray = cvCreateImage(cvGetSize(out),8,1);//新建输出图像
    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图

    int iinPix = 0;
    int iHist[256];//图像直方图
    int iThresholdValue = 1;

    int x,y,k;
    int sumfx,iAccumulate,icAccumulate;
    double m1,m2,sumxfx,csumxfx,fmax,sb;
    // 对直方图置零
    memset(iHist, 0, sizeof(iHist));
    // 生成直方图
    for( x = 0; x < inGray->width; x++)
        for( y = 0; y < inGray->height; y++)
        {
            iinPix = ((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
            iHist[iinPix] ++;

        }
    //计算所需
    sumxfx = csumxfx = 0.0;
    sumfx = 0;
    for( k = 0; k < 256; k++ )
    {
        sumxfx +=(double)k*(double)iHist[k]; // x*f(x) 质量矩
        sumfx += iHist[k]; //f(x)质量
    }
    if(!sumfx ) return false;
    //计算大津法阈值
    fmax = - 1.0;
    iAccumulate = 0;
    //假定阈值为k遍历求g = w0(前景平均为u0的概率)*(u0-u)^2+w1(背景平均为u1的概率)*(u1-u)^2
    /*
    图像中像素的灰度值小于阈值T的像素个数记作N0,像素灰度大于阈值T的像素个数记作N1,则有:
        ω0=N0/ M×N        (1)
        ω1=N1/ M×N        (2)
        N0+N1=M×N       (3)
        ω0+ω1=1          (4)
        μ=ω0*μ0+ω1*μ1   (5)
        g=ω0(μ0-μ)^2+ω1(μ1-μ)^2    (6)
        将式(5)代入式(6),得到等价公式:
        g=ω0ω1(μ0-μ1)^2    (7)
    */
    for( k = 0; k < 256; k++ )
    {
        iAccumulate += iHist[k];
        if(!iAccumulate) continue; //如果累计为0 不计算
        icAccumulate = sumfx - iAccumulate;
        if(icAccumulate == 0) break; //非0值计算完毕
        csumxfx += (double) k* iHist[k];
        m1 = csumxfx /iAccumulate ;//前K个均值
        m2 = (sumxfx - csumxfx ) /icAccumulate ;//其余的均值
        sb = (double) iAccumulate*(double)icAccumulate*(m1-m2)*(m1-m2);//计算方差
        if( sb > fmax)
        {
            fmax = sb;
            iThresholdValue = k ;
        }
    }
    for( x = 0; x < inGray->width; x++ )
        for( y = 0; y < inGray->height; y++)
        {
            iinPix = ((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
            if( iinPix < iThresholdValue + 1 ) //小于等于 以便能多次二值化不变白条
            {
                ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0] = 0;
            }
            else
            {
                ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0] = 255;
            }
        }


    cvCvtColor(outGray,out,CV_GRAY2BGR);//获取输出的BGR图
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}

//图像增强--二值化
extern "C" __declspec(dllexport) bool doBinaryzation(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//存储输入灰度图像
    IplImage* outGray = cvCreateImage(cvSize(width,height),depth,1);//新建输出图像
    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图
    /*
    下面这种方法直接更改了输入图像
    CvMat mathdr;
    CvMat* imgMat = cvGetMat(inGray,&mathdr);//定义一个指向CvMat对象的指针
    */
    //取出输入图像的数据
    CvMat* imgMat = cvCreateMat(inGray->height,inGray->width,CV_8U);//定义一个指向CvMat对象的指针
    cvConvert(inGray,imgMat);
    CvScalar sum= cvSum(imgMat);
    int avg = sum.val[0]/(imgMat->width*imgMat->height);
    //二值化处理
    for(int row=0;row<imgMat->rows;row++)
        for(int col=0;col<imgMat->cols;col++)
    if(CV_MAT_ELEM(*imgMat,uchar,row,col)<avg){
        CV_MAT_ELEM(*imgMat,uchar,row,col) = 0;
    }else CV_MAT_ELEM(*imgMat,uchar,row,col) = 255;
    cvConvert(imgMat,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);//获取输出的BGR图
    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}


//图像增强--大津法二值化
extern "C" __declspec(dllexport) bool doBinaryzationOSTU(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像


    BinaryzationOSTU(in,out);

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;
}


//图像增强--二值化
extern "C" __declspec(dllexport) bool doBinaryzationGAUSS(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//存储输入灰度图像
    IplImage* outGray = cvCreateImage(cvSize(width,height),depth,1);//新建输出图像
    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图

    cvAdaptiveThreshold(inGray,outGray,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY);

    cvCvtColor(outGray,out,CV_GRAY2BGR);//获取输出的BGR图
    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}


