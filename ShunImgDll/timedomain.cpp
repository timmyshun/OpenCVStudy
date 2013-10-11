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


//ͼ����С
extern "C" __declspec(dllexport) bool doPyrDown(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);
    IplImage* out = cvCreateImage(cvSize(width/2,height/2),depth,nChannels);//�½�һ��һ���С��ͼ��
    cvPyrDown(in,out);//ͼ����С
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);//�ͷ���Դ
    cvReleaseImage(&out);
    return true;
}
//ͼ��ģ��
extern "C" __declspec(dllexport) bool doSmooth(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    cvSmooth(in,out,CV_GAUSSIAN,5,5);//��˹�⻬���� ���� ��� ���� ����5*5���ص�ƽ��
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);//�ͷ���Դ
    cvReleaseImage(&out);
    return true;
}
//��Ե���
extern "C" __declspec(dllexport) bool doCanny(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels,\
                                              double lowThresh, double highThresh,double aperture)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��
    IplImage* inGray = cvCreateImage(cvSize(width,height),depth,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(width,height),depth,1);//�½����ͼ��
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ
    cvCanny(inGray, outGray, lowThresh,highThresh,aperture);//����Ե���
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);//�ͷ���Դ
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);//�ͷ���Դ
    cvReleaseImage(&outGray);
    return true;
}
//���ͨ��
extern "C" __declspec(dllexport) bool doSaturate_sv(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��

    for(int y=0; y<in->height;y++){
        uchar* ptr = (uchar*)(in->imageData+y*in->widthStep);
        for(int x=0;x<in->width;x++){
            ptr[3*x+1] = 255;
            ptr[3*x+2] = 255;
        }
    }
    outputData(outImgData,in);//���ͼ��
    cvReleaseImage(&in);//�ͷ���Դ
    return true;
}

//ͼ����ǿ-��ת
extern "C" __declspec(dllexport) bool doReverse(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
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
    //��ת����
    for(int row=0;row<imgMat->rows;row++)
        for(int col=0;col<imgMat->cols;col++)
            CV_MAT_ELEM(*imgMat,uchar,row,col) = 255-CV_MAT_ELEM(*imgMat,uchar,row,col);
    cvConvert(imgMat,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}

//ͼ����ǿ-�����任
extern "C" __declspec(dllexport) bool doLogTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
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
    //�����任����
    for(int row=0;row<imgMat->rows;row++)
        for(int col=0;col<imgMat->cols;col++)
        {
            CV_MAT_ELEM(*imgMat,uchar,row,col) = (uchar)(46*log(1+CV_MAT_ELEM(*imgMat,uchar,row,col)));
        }
    cvConvert(imgMat,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}
//ͼ����ǿ-ָ���任
extern "C" __declspec(dllexport) bool doPowerTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
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
    //�����任����
    for(int row=0;row<imgMat->rows;row++)
        for(int col=0;col<imgMat->cols;col++)
        {
            CV_MAT_ELEM(*imgMat,uchar,row,col) = (uchar)(1.64*pow(1.02,CV_MAT_ELEM(*imgMat,uchar,row,col)));
        }
    cvConvert(imgMat,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);//��ȡ�����BGRͼ
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    cvReleaseImage(&inGray);
    cvReleaseImage(&outGray);
    return true;
}


//ͼ��ָ�
extern "C" __declspec(dllexport) bool doPyrSegmentation(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��


    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* comp = NULL;
    cvPyrSegmentation( in, out, storage, &comp, 4, 200, 50 );
    int n_comp = comp->total;
    for( int i=0; i<n_comp; i++ ) {
        CvConnectedComp* cc = (CvConnectedComp*) cvGetSeqElem( comp, i );
        cvRectangle(out,cvPoint(cc->rect.x,cc->rect.y),cvPoint(cc->rect.x+cc->rect.width,cc->rect.y+cc->rect.height),cvScalar(255,255,255));
    }

    cvReleaseMemStorage( &storage );

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}

//ֱ��ͼ����
extern "C" __declspec(dllexport) bool doEqualizeHist(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��


    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��
    IplImage* outGray = cvCreateImage(cvSize(out->width,out->height),8,1);//�洢����Ҷ�ͼ��

    cvCvtColor(in,inGray,CV_BGR2GRAY);
    cvEqualizeHist(inGray,outGray);
    cvCvtColor(outGray,out,CV_GRAY2BGR);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}

//��ͨ��ֱ��ͼ����
extern "C" __declspec(dllexport) bool doEqualizeHistEX(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    int iHistB[256],iHistG[256],iHistR[256];
    int widthStep = in->widthStep;

    //����set0
    for(int i =0; i<256; i++)
    {
        iHistB[i] = 0;
        iHistG[i] = 0;
        iHistR[i] = 0;
    }

    //��ȡ��ͨ��ֱ��ͼ
    for(int x=0;x<in->width;x++)
        for(int y=0;y<in->height;y++)
        {
            iHistB[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 0]]++;
            iHistG[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 1]]++;
            iHistR[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 2]]++;
        }
    float N = in->width*in->height;
    float sumB = 0, sumG = 0, sumR = 0;
    //�����Ӧ
    for(int i =0; i<256; i++)
    {
        sumB += iHistB[i];
        sumG += iHistG[i];
        sumR += iHistR[i];

        iHistB[i] = cvRound(sumB/N*255);
        iHistG[i] = cvRound(sumG/N*255);
        iHistR[i] = cvRound(sumR/N*255);
    }
    for(int x=0;x<out->width;x++)
        for(int y=0;y<out->height;y++)
        {
            ((uchar *)(out->imageData + y*widthStep))[x*nChannels + 0] = iHistB[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 0]];
            ((uchar *)(out->imageData + y*widthStep))[x*nChannels + 1] = iHistG[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 1]];
            ((uchar *)(out->imageData + y*widthStep))[x*nChannels + 2] = iHistR[((uchar *)(in->imageData + y*widthStep))[x*nChannels + 2]];
        }

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}

//��ʾֱ��ͼ
extern "C" __declspec(dllexport) bool doDisplayHist(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��


    IplImage* inGray = cvCreateImage(cvSize(in->width,in->height),8,1);//�洢����Ҷ�ͼ��

    cvCvtColor(in,inGray,CV_BGR2GRAY);

    int bins = 256;
    int hist_size[] = {bins};
    float range[] = {0,255};
    float* ranges[] = {range};
    CvHistogram* hist = cvCreateHist(1,hist_size,CV_HIST_ARRAY,ranges,1);
    IplImage* planes[] = {inGray};
    cvCalcHist(planes,hist,0,0);
    cvNormalizeHist(hist,1.0);

    // populate our visualization with little gray squares.
    //
    float max_value = 0;
    float step = out->width/300.0;
    float unit = out->height/256.0;
    cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );

    for( int i = 0; i < bins; i++ ) {
        float bin_val = cvQueryHistValue_1D( hist, i );
        int intensity = cvRound( bin_val * 255 / max_value );
        cvRectangle(
            out,
            cvPoint( cvRound((i+9)*step), cvRound(out->height-255*unit) ),
            cvPoint( cvRound((i+10)*step), out->height),
            CV_RGB(0,25,0),
            1
            );
        cvRectangle(
            out,
            cvPoint( cvRound((i+9)*step), cvRound(out->height-intensity*unit) ),
            cvPoint( cvRound((i+10)*step), cvRound(out->height)),
            CV_RGB(intensity,intensity,intensity),
            CV_FILLED
            );
    }


    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}
