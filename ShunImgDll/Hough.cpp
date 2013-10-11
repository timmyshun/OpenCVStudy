#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;
// SHT
extern "C" __declspec(dllexport) bool doHoughLineSHT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像
    cvCopyImage(in,out);
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//存储输入灰度图像

    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图

    cvCanny(inGray, inGray, 30,100);//做边缘检测

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* comp = NULL;
    comp = cvHoughLines2(inGray, storage,CV_HOUGH_STANDARD,1,CV_PI/360,100);
    int n_comp = comp->total;
    CvMat* mag = cvCreateMat( 1, n_comp, CV_32FC1 );
    CvMat* angle = cvCreateMat( 1, n_comp, CV_32FC1 );
    CvMat* x = cvCreateMat( 1, n_comp, CV_32FC1 );
    CvMat* y = cvCreateMat( 1, n_comp, CV_32FC1 );
    for( int i=0; i<n_comp; i++ )
    {
        float*  fppoint = (float*)cvGetSeqElem( comp, i );
        CV_MAT_ELEM(*mag,float,0,i) = fppoint[0];
        CV_MAT_ELEM(*angle,float,0,i) = fppoint[1];
    }
    cvPolarToCart(mag,angle,x,y);
    for( int i=0; i<n_comp; i++ )
    {
        CvPoint pStart = cvPoint(0,cvRound(CV_MAT_ELEM(*y,float,0,i)-CV_MAT_ELEM(*x,float,0,i)*tan(CV_PI/2+CV_MAT_ELEM(*angle,float,0,i))));
        CvPoint pEnd = cvPoint(in->width,cvRound(CV_MAT_ELEM(*y,float,0,i)+(in->width-CV_MAT_ELEM(*x,float,0,i))*tan(CV_PI/2+CV_MAT_ELEM(*angle,float,0,i))));
        cvDrawLine(out,pStart,pEnd,cvScalar(255,0,0),1);

    }

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}
// PPHT
extern "C" __declspec(dllexport) bool doHoughLinePPHT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像
    cvCopyImage(in,out);
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//存储输入灰度图像

    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图

    cvCanny(inGray, inGray, 30,100);//做边缘检测

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* comp = NULL;
    comp = cvHoughLines2(inGray, storage,CV_HOUGH_PROBABILISTIC,1,CV_PI/360,100,30,30);
    int n_comp = comp->total;

    for( int i=0; i<n_comp; i++ )
    {
        CvPoint*  line = (CvPoint*)cvGetSeqElem( comp, i );
        cvLine( out , line[0], line[1], CV_RGB(255,0,0), 1 );

    }

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}

// GHT
extern "C" __declspec(dllexport) bool doHoughCircleGHT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像
    cvCopyImage(in,out);
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//存储输入灰度图像

    cvCvtColor(in,inGray,CV_BGR2GRAY);//获取输入的灰度图
    cvSmooth(inGray,inGray);

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* comp = NULL;
    comp = cvHoughCircles(inGray, storage,CV_HOUGH_GRADIENT,1,inGray->width/10);
    int n_comp = comp->total;

    for( int i=0; i<n_comp; i++ )
    {
        float* p = (float*)cvGetSeqElem( comp, i );
        CvPoint pt = cvPoint( cvRound(p[0]),cvRound(p[1]));
        cvCircle( out , pt, cvRound(p[2]), CV_RGB(0,255,0) );

    }

    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}
