#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;

// DFT
//数据的存储格式还有待考究
extern "C" __declspec(dllexport) bool doDFT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像

    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//存储输入灰度图像
    IplImage* outGray = cvCreateImage(cvSize(out->width,out->height),8,1);//存储输入灰度图像


    IplImage* inFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,1);//存储输入灰度图像
    IplImage* outFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//存储输出灰度图像

    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图
    for( int x = 0; x < inGray->width; x++)
        for( int y = 0; y < inGray->height; y++)
        {
            ((float *)(inFloat->imageData + y*inFloat->widthStep))[x*inFloat->nChannels + 0] = \
                                ((x+y)%2==0?1:-1)*((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
        }
    //cvConvert(inGray,inFloat);

    cvDFT(inFloat,outFloat,CV_DXT_FORWARD);//离散傅里叶变换

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            float re = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 0]/(in->width*in->height)*255;
            float im = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 1]/(in->width*in->height)*255;
            ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0]= cvRound(sqrt(re*re+im*im)) ;

        }
    cvCvtColor(outGray,out,CV_GRAY2BGR);//获取输入的灰度图

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}

// IDFI
extern "C" __declspec(dllexport) bool doIDFT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像

    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//存储输入灰度图像
    IplImage* outGray = cvCreateImage(cvSize(out->width,out->height),8,1);//存储输入灰度图像


    IplImage* inFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,1);//存储输入灰度图像
    IplImage* outFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//存储输出灰度图像
    IplImage* inverseFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//存储输入灰度图像

    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图
    for( int x = 0; x < inGray->width; x++)
        for( int y = 0; y < inGray->height; y++)
        {
            ((float *)(inFloat->imageData + y*inFloat->widthStep))[x*inFloat->nChannels + 0] = \
                                ((x+y)%2==0?1:-1)*((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
        }
    //cvConvert(inGray,inFloat);

    cvDFT(inFloat,outFloat,CV_DXT_FORWARD);//离散傅里叶变换

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            float re = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 0]/(in->width*in->height)*255;
            float im = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 1]/(in->width*in->height)*255;
            ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0]= cvRound(sqrt(re*re+im*im)) ;

        }
    cvCvtColor(outGray,out,CV_GRAY2BGR);//获取输入的灰度图

    cvDFT( outFloat,inverseFloat,CV_DXT_INVERSE_SCALE);

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            ((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0] =\
            ((x+y)%2==0?1:-1)*cvRound(((float *)( inverseFloat->imageData + y* inverseFloat->widthStep))[x* inverseFloat->nChannels + 0]) ;
        }
    cvCvtColor(inGray,in,CV_GRAY2BGR);//获取输入的灰度图

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}
