#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
#include "Binaryzation.hpp"
using namespace cv;
// FindContours
bool FindContours(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//�洢����Ҷ�ͼ��

    BinaryzationOSTU(in,in);
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* seq = NULL;

    cvFindContours(inGray,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    cvCvtColor(inGray,out,CV_GRAY2BGR);//��ȡ����ĻҶ�ͼ
    cvDrawContours(out,seq,cvScalar(255,0,0),cvScalar(0,0,255),100,1,8,cvPoint(0,0));
    cvReleaseImage(&inGray);


    return true;

}

// ApproxPoly
bool ApproxPoly(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//�洢����Ҷ�ͼ��


    BinaryzationOSTU(in,in);
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* seq = NULL;

    cvFindContours(inGray,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    CvMemStorage* pollystorage = cvCreateMemStorage(0);
    CvSeq* polly = cvApproxPoly(seq,sizeof(CvContour),pollystorage,CV_POLY_APPROX_DP,3,1);

    cvZero(out);
    for(CvSeq* cseq = polly;cseq!=NULL;cseq= cseq->h_next)
    {
        cvDrawContours(out,cseq,cvScalar(255,0,0),cvScalar(0,0,255),20,1,8,cvPoint(0,0));
    }

    cvReleaseImage(&inGray);


    return true;

}


void DrawBounding(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//�洢����Ҷ�ͼ��

    BinaryzationOSTU(in,in);
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ

    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* seq = NULL;

    cvFindContours(inGray,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);


    cvZero(out);
    for( CvSeq* cseq = seq;  cseq!=NULL;cseq=cseq->h_next)
    {
        //cout<<"���ȣ�"<<cvContourPerimeter(cseq)<<"�����"<<cvContourArea(cseq)<<endl;
        CvRect BRect =  cvBoundingRect(cseq,0);
        cvDrawRect(out,cvPoint(BRect.x,BRect.y),cvPoint(BRect.x+BRect.width,BRect.y+BRect.height),cvScalar(0,0,255));
        CvBox2D Box2D = cvMinAreaRect2(cseq,NULL); //������Сб�߿�
        cvDrawCircle(out,cvPointFrom32f(Box2D.center),2,cvScalar(255,255,255));
    }

    cvReleaseImage(&inGray);

}

void GetMoment(IplImage* in,IplImage* out)
{
    IplImage* inGray = cvCreateImage(cvGetSize(in),8,1);//�洢����Ҷ�ͼ��


    BinaryzationOSTU(in,in);
    cvCvtColor(in,inGray,CV_BGR2GRAY);//��ȡ����ĻҶ�ͼ


    CvMemStorage* storage = cvCreateMemStorage(0);
    CvSeq* seq = NULL;

    cvFindContours(inGray,storage,&seq,sizeof(CvContour),CV_RETR_LIST,CV_CHAIN_APPROX_NONE);

    cvReleaseImage(&inGray);

    CvMoments menents;
    /*
    for( CvSeq* cseq = seq;  cseq!=NULL;cseq=cseq->h_next)
    {
        cout<<"���ȣ�"<<cvContourPerimeter(cseq)<<"�����"<<cvContourArea(cseq)<<endl;
        cvContourMoments(cseq,&menents);
        cout<<"��00:"<<menents.m00<<endl;
        cout<<"���ľ�:"<<cvGetCentralMoment(&menents,0,0)<<endl;
        cout<<"��һ�����ľأ�"<<cvGetNormalizedCentralMoment(&menents,0,0)<<endl;
        CvHuMoments huMoments;
        cvGetHuMoments(&menents,&huMoments);
        cout<<" Hu1:"<<huMoments.hu1<<"  Hu2:"<<huMoments.hu2<<"  Hu3:"<<huMoments.hu3<<"  Hu4:"<<huMoments.hu4<<endl;
        if(cseq->h_next)
            cout<<"MatchNext:"<<cvMatchShapes(cseq,cseq->h_next,CV_CONTOURS_MATCH_I1)<<endl;
    }
    */
}

// FindContours
extern "C" __declspec(dllexport) bool doFindContours(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    FindContours(in,out);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}

//����αƽ�
extern "C" __declspec(dllexport) bool doApproxPoly(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    ApproxPoly(in,out);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}


//�߽�
extern "C" __declspec(dllexport) bool doDrawBounding(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    DrawBounding(in,out);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);
    return true;
}
