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

void CheckSkin(IplImage* in,IplImage* out)
{
    IplImage* inHSV = cvCreateImage(cvSize(in->width,in->height),8,3);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��

    cvCvtColor(in,inHSV,CV_BGR2HSV);
    cvZero(outGray);

    for( int x = 0; x < outGray->width; x++ )
        for(int  y = 0; y < outGray->height; y++)
        {
            int iinPix = ((uchar *)(inHSV->imageData + y*inHSV->widthStep))[x*inHSV->nChannels + 0];
            if(iinPix>5 && iinPix < 24 )
            {
                ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0] = 255;
            }
        }
    cvCvtColor(outGray,out,CV_GRAY2BGR);
    cvReleaseImage(&inHSV);
    cvReleaseImage(&outGray);

}

//ͼ����ǿ--����Ƥ�����
extern "C" __declspec(dllexport) bool doCheckSkin(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    CheckSkin(in,out);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;
}

//ͼ����ǿ--����ͶӰ
extern "C" __declspec(dllexport) bool doBackProject(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    IplImage* inHSV = cvCreateImage(cvSize(in->width,in->height),8,3);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��
    cvZero(outGray);

    cvCvtColor(in,inHSV,CV_BGR2HSV);
    IplImage* h_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    IplImage* s_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    IplImage* v_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    IplImage* planes[] = { h_plane };
    cvCvtPixToPlane( inHSV, h_plane, s_plane, v_plane, 0 );
    int    hist_size[] = { 30 };
    float  h_ranges[]  = { 0, 180 };          // hue is [0,180]
    float* ranges[]    = { h_ranges };
    CvHistogram* hist = cvCreateHist(1,hist_size,CV_HIST_ARRAY,ranges,1);
    cvCalcHist( planes, hist, 0, 0 ); //Compute histogram
    cvNormalizeHist( hist, 255.0 );  //Normalize it
    cvCalcBackProject( planes ,outGray ,hist);
    cvCvtColor(outGray,out,CV_GRAY2BGR);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inHSV);
    cvReleaseImage(&outGray);
    return true;
}

//������������� ֻ������ ��¼ �鷴��ͶӰ
extern "C" __declspec(dllexport) bool doBackProjectPatch(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    IplImage* part = cvLoadImage("skin1part.jpg");//�������������

    IplImage* inHSV = cvCreateImage(cvSize(in->width,in->height),8,3);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(in->width-part->width+1,in->height-part->height+1),IPL_DEPTH_32F,1);//�洢����Ҷ�ͼ��
    cvZero(outGray);

    cvCvtColor(in,inHSV,CV_BGR2HSV);
    IplImage* inh_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    IplImage* ins_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    IplImage* inv_plane  = cvCreateImage( cvGetSize(in), 8, 1 );
    cvCvtPixToPlane( inHSV, inh_plane, ins_plane, inv_plane, 0 );
    IplImage* inplanes[] = { inh_plane , ins_plane };

    IplImage* partHSV = cvCreateImage(cvSize(part->width,part->height),8,3);//�洢����Ҷ�ͼ��
    cvCvtColor(part,partHSV,CV_BGR2HSV);
    IplImage* h_plane  = cvCreateImage( cvGetSize(part), 8, 1 );
    IplImage* s_plane  = cvCreateImage( cvGetSize(part), 8, 1 );
    IplImage* v_plane  = cvCreateImage( cvGetSize(part), 8, 1 );
    IplImage* planes[] = { h_plane , s_plane };
    cvCvtPixToPlane( partHSV, h_plane, s_plane, v_plane, 0 );
    int    hist_size[] = { 30 , 32 };
    float  h_ranges[]  = { 0, 180 };          // hue is [0,180]
    float  s_ranges[]  = { 0, 255 };
    float* ranges[]    = { h_ranges , s_ranges };
    CvHistogram* hist = cvCreateHist(2,hist_size,CV_HIST_ARRAY,ranges,1);
    cvCalcHist( planes, hist, 0, 0 ); //Compute histogram
    cvNormalizeHist( hist, 255.0 );  //Normalize it
    cvCalcBackProjectPatch( inplanes ,outGray ,cvGetSize(part),hist,CV_COMP_BHATTACHARYYA,1);
    cvCvtColor(outGray,out,CV_GRAY2BGR);

    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inHSV);
    cvReleaseImage(&outGray);
    return true;
}


//������������� ֻ������ ��¼ ģ��ƥ��
extern "C" __declspec(dllexport) bool doMatchTemplate(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    IplImage* part = cvLoadImage("skin1part.jpg");//�������������

    IplImage* outGray = cvCreateImage(cvSize(in->width-part->width+1,in->height-part->height+1),IPL_DEPTH_32F,1);//�洢����Ҷ�ͼ��
    cvMatchTemplate( in, part,outGray,CV_TM_CCOEFF_NORMED);
    cvPow(outGray,outGray,5);
    cvNormalize(outGray,outGray,1.0,0,CV_MINMAX);
    IplImage* outtemp = cvCreateImage(cvSize(in->width-part->width+1,in->height-part->height+1),IPL_DEPTH_32F,3);
    cvCvtColor(outGray,outtemp,CV_GRAY2BGR);
    cvScale(outtemp,out,255,0);

    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&outtemp);
    cvReleaseImage(&outGray);
    return true;
}

