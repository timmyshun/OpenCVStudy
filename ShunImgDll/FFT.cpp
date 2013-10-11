#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;

// DFT
//���ݵĴ洢��ʽ���д�����
extern "C" __declspec(dllexport) bool doDFT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(out->width,out->height),8,1);//�洢����Ҷ�ͼ��


    IplImage* inFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,1);//�洢����Ҷ�ͼ��
    IplImage* outFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//�洢����Ҷ�ͼ��

    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ
    for( int x = 0; x < inGray->width; x++)
        for( int y = 0; y < inGray->height; y++)
        {
            ((float *)(inFloat->imageData + y*inFloat->widthStep))[x*inFloat->nChannels + 0] = \
                                ((x+y)%2==0?1:-1)*((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
        }
    //cvConvert(inGray,inFloat);

    cvDFT(inFloat,outFloat,CV_DXT_FORWARD);//��ɢ����Ҷ�任

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            float re = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 0]/(in->width*in->height)*255;
            float im = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 1]/(in->width*in->height)*255;
            ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0]= cvRound(sqrt(re*re+im*im)) ;

        }
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ����ĻҶ�ͼ

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}

// IDFI
extern "C" __declspec(dllexport) bool doIDFT(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(out->width,out->height),8,1);//�洢����Ҷ�ͼ��


    IplImage* inFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,1);//�洢����Ҷ�ͼ��
    IplImage* outFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//�洢����Ҷ�ͼ��
    IplImage* inverseFloat = cvCreateImage(cvSize(in->width,in->height),IPL_DEPTH_32F,2);//�洢����Ҷ�ͼ��

    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ
    for( int x = 0; x < inGray->width; x++)
        for( int y = 0; y < inGray->height; y++)
        {
            ((float *)(inFloat->imageData + y*inFloat->widthStep))[x*inFloat->nChannels + 0] = \
                                ((x+y)%2==0?1:-1)*((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0];
        }
    //cvConvert(inGray,inFloat);

    cvDFT(inFloat,outFloat,CV_DXT_FORWARD);//��ɢ����Ҷ�任

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            float re = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 0]/(in->width*in->height)*255;
            float im = ((float *)(outFloat->imageData + y*outFloat->widthStep))[x*outFloat->nChannels + 1]/(in->width*in->height)*255;
            ((uchar *)(outGray->imageData + y*outGray->widthStep))[x*outGray->nChannels + 0]= cvRound(sqrt(re*re+im*im)) ;

        }
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ����ĻҶ�ͼ

    cvDFT( outFloat,inverseFloat,CV_DXT_INVERSE_SCALE);

    for( int x = 0; x < outGray->width; x++)
        for( int y = 0; y < outGray->height; y++)
        {
            ((uchar *)(inGray->imageData + y*inGray->widthStep))[x*inGray->nChannels + 0] =\
            ((x+y)%2==0?1:-1)*cvRound(((float *)( inverseFloat->imageData + y* inverseFloat->widthStep))[x* inverseFloat->nChannels + 0]) ;
        }
    cvCvtColor(inGray,in,CV_GRAY2BGR);//��ȡ����ĻҶ�ͼ

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    return true;
}
