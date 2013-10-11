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

//ͼ����ǿ--��򷨶�ֵ��
bool BinaryzationOSTU(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvGetSize(out),8,1);//�½����ͼ��
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ

    int iinPix = 0;
    int iHist[256];//ͼ��ֱ��ͼ
    int iThresholdValue = 1;

    int x,y,k;
    int sumfx,iAccumulate,icAccumulate;
    double m1,m2,sumxfx,csumxfx,fmax,sb;
    // ��ֱ��ͼ����
    memset(iHist, 0, sizeof(iHist));
    // ����ֱ��ͼ
    for( x = 0; x < inGray->width; x++)
        for( y = 0; y < inGray->height; y++)
        {
            iinPix = ((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
            iHist[iinPix] ++;

        }
    //��������
    sumxfx = csumxfx = 0.0;
    sumfx = 0;
    for( k = 0; k < 256; k++ )
    {
        sumxfx +=(double)k*(double)iHist[k]; // x*f(x) ������
        sumfx += iHist[k]; //f(x)����
    }
    if(!sumfx ) return false;
    //��������ֵ
    fmax = - 1.0;
    iAccumulate = 0;
    //�ٶ���ֵΪk������g = w0(ǰ��ƽ��Ϊu0�ĸ���)*(u0-u)^2+w1(����ƽ��Ϊu1�ĸ���)*(u1-u)^2
    /*
    ͼ�������صĻҶ�ֵС����ֵT�����ظ�������N0,���ػҶȴ�����ֵT�����ظ�������N1,����:
        ��0=N0/ M��N        (1)
        ��1=N1/ M��N        (2)
        N0+N1=M��N       (3)
        ��0+��1=1          (4)
        ��=��0*��0+��1*��1   (5)
        g=��0(��0-��)^2+��1(��1-��)^2    (6)
        ��ʽ(5)����ʽ(6),�õ��ȼ۹�ʽ:
        g=��0��1(��0-��1)^2    (7)
    */
    for( k = 0; k < 256; k++ )
    {
        iAccumulate += iHist[k];
        if(!iAccumulate) continue; //����ۼ�Ϊ0 ������
        icAccumulate = sumfx - iAccumulate;
        if(icAccumulate == 0) break; //��0ֵ�������
        csumxfx += (double) k* iHist[k];
        m1 = csumxfx /iAccumulate ;//ǰK����ֵ
        m2 = (sumxfx - csumxfx ) /icAccumulate ;//����ľ�ֵ
        sb = (double) iAccumulate*(double)icAccumulate*(m1-m2)*(m1-m2);//���㷽��
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
            if( iinPix < iThresholdValue + 1 ) //С�ڵ��� �Ա��ܶ�ζ�ֵ���������
            {
                ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0] = 0;
            }
            else
            {
                ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0] = 255;
            }
        }


    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}

//ͼ����ǿ--��ֵ��
extern "C" __declspec(dllexport) bool doBinaryzation(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(width,height),depth,1);//�½����ͼ��
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ
    /*
    �������ַ���ֱ�Ӹ���������ͼ��
    CvMat mathdr;
    CvMat* imgMat = cvGetMat(inGray,&mathdr);//����һ��ָ��CvMat�����ָ��
    */
    //ȡ������ͼ�������
    CvMat* imgMat = cvCreateMat(inGray->height,inGray->width,CV_8U);//����һ��ָ��CvMat�����ָ��
    cvConvert(inGray,imgMat);
    CvScalar sum= cvSum(imgMat);
    int avg = sum.val[0]/(imgMat->width*imgMat->height);
    //��ֵ������
    for(int row=0;row<imgMat->rows;row++)
        for(int col=0;col<imgMat->cols;col++)
    if(CV_MAT_ELEM(*imgMat,uchar,row,col)<avg){
        CV_MAT_ELEM(*imgMat,uchar,row,col) = 0;
    }else CV_MAT_ELEM(*imgMat,uchar,row,col) = 255;
    cvConvert(imgMat,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}


//ͼ����ǿ--��򷨶�ֵ��
extern "C" __declspec(dllexport) bool doBinaryzationOSTU(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��


    BinaryzationOSTU(in,out);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;
}


//ͼ����ǿ--��ֵ��
extern "C" __declspec(dllexport) bool doBinaryzationGAUSS(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(width,height),depth,1);//�½����ͼ��
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ

    cvAdaptiveThreshold(inGray,outGray,255,CV_ADAPTIVE_THRESH_GAUSSIAN_C,CV_THRESH_BINARY);

    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}


