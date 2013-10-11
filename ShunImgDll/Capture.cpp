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


//��ȡ����Ƭ��
void storeRMVB()
{
    CvCapture*  rmvb_1 = cvCreateFileCapture("one piece.rmvb");
    int max_buffer;
    IplImage* rawImage;
    cvNamedWindow("Onepiece",CV_WINDOW_AUTOSIZE);
   // int r[10000],g[10000],b[10000];
    CvLineIterator iterator_1;

    FILE *fptrb = fopen("blines.csv","w");
    FILE *fptrg = fopen("glines.csv","w");
    FILE *fptrr = fopen("rlines.csv","w");

    for(;;){
        if( !cvGrabFrame( rmvb_1))
            break;
        rawImage = cvRetrieveFrame(rmvb_1);;
        max_buffer = cvInitLineIterator(rawImage,cvPoint(50,50),cvPoint(50,150),&iterator_1,8,0);
        for(int j=0;j<max_buffer;j++){
            fprintf(fptrb,"%d,",iterator_1.ptr[0]);
            fprintf(fptrg,"%d,",iterator_1.ptr[1]);
            fprintf(fptrr,"%d,",iterator_1.ptr[2]);

            iterator_1.ptr[2] = 255;

            CV_NEXT_LINE_POINT(iterator_1);
        }
        cvShowImage("Onepiece",rawImage);
        cvWaitKey(33);
        fprintf(fptrb,"\n");
        fprintf(fptrg,"\n");
        fprintf(fptrr,"\n");
    }
    fclose(fptrb);
    fclose(fptrg);
    fclose(fptrr);
    cvReleaseCapture(&rmvb_1);

}

//�򵥵Ļ�ȡǰ��
void Getforeword()
{
    CvCapture*  rmvb_1 = cvCreateFileCapture("one piece.rmvb");

    IplImage* rawImage;
    IplImage* rawImage1;
    cvNamedWindow("Onepiece",CV_WINDOW_AUTOSIZE);


    for(;;){
        if( !cvGrabFrame( rmvb_1))
            break;
        rawImage = cvRetrieveFrame(rmvb_1);
        IplImage* rawGray = cvCreateImage(cvGetSize(rawImage),8,1);
        cvCvtColor(rawImage,rawGray,CV_BGR2GRAY);

        if( !cvGrabFrame( rmvb_1))
            break;
        rawImage1 = cvRetrieveFrame(rmvb_1);
        IplImage* rawGray1 = cvCreateImage(cvGetSize(rawImage1),8,1);
        cvCvtColor(rawImage1,rawGray1,CV_BGR2GRAY);

        cvAbsDiff(rawGray,rawGray1,rawGray);
        cvThreshold(rawGray,rawGray,15,255,CV_THRESH_BINARY);
        cvShowImage("Onepiece",rawGray);
        cvWaitKey(33);
        cvReleaseImage(&rawGray);
        cvReleaseImage(&rawGray1);
    }

    cvReleaseCapture(&rmvb_1);
}
//3ͨ����Ƶ��ȡǰ��
void Getforeword3C()
{
    CvCapture*  rmvb_1 = cvCreateFileCapture("one piece.rmvb");

    IplImage* rawImage1;
    IplImage* rawImage2;
    cvNamedWindow("Onepiece",CV_WINDOW_AUTOSIZE);


    for(;;){
        if( !cvGrabFrame( rmvb_1))
            break;
        rawImage1 = cvRetrieveFrame(rmvb_1);
        IplImage* rawImage1B = cvCreateImage(cvGetSize(rawImage1),8,1);
        IplImage* rawImage1G = cvCreateImage(cvGetSize(rawImage1),8,1);
        IplImage* rawImage1R = cvCreateImage(cvGetSize(rawImage1),8,1);

        cvSplit(rawImage1,rawImage1B,rawImage1G,rawImage1R,NULL);
        if( !cvGrabFrame( rmvb_1))
            break;
        rawImage2 = cvRetrieveFrame(rmvb_1);

        IplImage* rawImage2B = cvCreateImage(cvGetSize(rawImage2),8,1);
        IplImage* rawImage2G = cvCreateImage(cvGetSize(rawImage2),8,1);
        IplImage* rawImage2R = cvCreateImage(cvGetSize(rawImage2),8,1);
        cvSplit(rawImage2,rawImage2B,rawImage2G,rawImage2R,NULL);

        cvAbsDiff(rawImage1B,rawImage2B,rawImage1B);
       // cvThreshold(rawImage1B,rawImage1B,15,255,CV_THRESH_BINARY);
        cvAbsDiff(rawImage1G,rawImage2G,rawImage1G);
       // cvThreshold(rawImage1G,rawImage1G,15,255,CV_THRESH_BINARY);
        cvAbsDiff(rawImage1R,rawImage2R,rawImage1R);
       // cvThreshold(rawImage1R,rawImage1R,15,255,CV_THRESH_BINARY);

       //����ֵ��������л�������ǰ��

        IplImage* rawImageBuff = cvCreateImage(cvGetSize(rawImage1),8,3);
        cvMerge(rawImage1B,rawImage1G,rawImage1R,NULL,rawImageBuff);
        cvShowImage("Onepiece",rawImageBuff);
        cvWaitKey(33);
        cvReleaseImage(&rawImage1B);
        cvReleaseImage(&rawImage1G);
        cvReleaseImage(&rawImage1R);
        cvReleaseImage(&rawImage2B);
        cvReleaseImage(&rawImage2G);
        cvReleaseImage(&rawImage2R);
        cvReleaseImage(&rawImageBuff);

    }

    cvReleaseCapture(&rmvb_1);
}


//------------------------------------------------------------------------
//ƽ�������챳��ģ��
//------------------------------------------------------------------------

//Float 3-channel imgaes
IplImage *IavgF,*IdiffF,*IprevF,*IhiF,*IlowF;

IplImage *Iscratch,*Iscratch2;

//Float 1-channel imgaes
IplImage *Igray1,*Igray2,*Igray3;
IplImage *Ilow1,*Ilow2,*Ilow3;
IplImage *Ihi1,*Ihi2,*Ihi3;

//Byte 1-channel image
IplImage *Imaskt;

//����ͼƬ����
float Icount;

void AllocateImages(IplImage* I)
{
    CvSize sz = cvGetSize(I);

    //����ͼ���ڴ�
    IavgF = cvCreateImage(sz,IPL_DEPTH_32F,3);
    IdiffF = cvCreateImage(sz,IPL_DEPTH_32F,3);
    IprevF = cvCreateImage(sz,IPL_DEPTH_32F,3);
    IhiF = cvCreateImage(sz,IPL_DEPTH_32F,3);
    IlowF = cvCreateImage(sz,IPL_DEPTH_32F,3);

    cvZero( IavgF );
    cvZero( IdiffF );
    cvZero( IprevF );
    cvZero( IhiF );
    cvZero( IlowF );

    Ilow1 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Ilow2 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Ilow3 = cvCreateImage(sz,IPL_DEPTH_32F,1);

    Ihi1 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Ihi2 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Ihi3 = cvCreateImage(sz,IPL_DEPTH_32F,1);

    Icount = 0.00001;//��ֹ����Ϊ0

    Iscratch = cvCreateImage(sz,IPL_DEPTH_32F,3);
    Iscratch2 = cvCreateImage(sz,IPL_DEPTH_32F,3);

    cvZero(Iscratch);
    cvZero(Iscratch2);

    Igray1 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Igray2 = cvCreateImage(sz,IPL_DEPTH_32F,1);
    Igray3 = cvCreateImage(sz,IPL_DEPTH_32F,1);

    Imaskt = cvCreateImage(sz,IPL_DEPTH_8U,1);
}

void accumulateBackground(IplImage* I)
{
    static int first = 1;
    cvCvtScale(I,Iscratch,1,0);
    if(!first)
    {
        cvAcc(Iscratch,IavgF);//�ۼ�ͼ��
        cvAbsDiff(Iscratch,IprevF,Iscratch2);
        cvAcc(Iscratch2,IdiffF);//�ۼӲ�
        Icount += 1.0;
    }
    first = 0;
    cvCopy(Iscratch,IprevF);
}


void setHighThreshold(float scale)
{
    //��ñȾ�ֵ�� scale����ֵ��ͼ����Ϊ����ֵ
    //ͼ��С�ڸ���ֵ���ڵ���ֵ��Ϊ�Ǳ���
    cvConvertScale(IdiffF, Iscratch,scale);
    cvAdd(Iscratch,IavgF,IhiF);
    cvSplit(IhiF,Ihi1,Ihi2,Ihi3,NULL);

}
void setLowThreshold(float scale)
{
    //��ñȾ�ֵС scale����ֵ��ͼ����Ϊ����ֵ
    //ͼ��С�ڸ���ֵ���ڵ���ֵ��Ϊ�Ǳ���
    cvConvertScale(IdiffF, Iscratch,scale);
    cvSub(IavgF,Iscratch,IlowF);
    cvSplit(IlowF,Ilow1,Ilow2,Ilow3,NULL);
}


void createModelsFromStats()
{
    //����ͼ���ƽ��ֵ
    cvConvertScale(IavgF,IavgF,(double)(1.0/Icount));
    //�������ֵ���ƽ��ֵ
    cvConvertScale(IdiffF,IdiffF,(double)(1.0/Icount));

    cvAddS(IdiffF,cvScalar(1.0,1.0,1.0),IdiffF);
    setHighThreshold(7.0);
    setLowThreshold(6.0);
}

void backgroundDiff(IplImage *I,IplImage *Imask)
{
    cvCvtScale(I,Iscratch,1,0);
    cvSplit(Iscratch,Igray1,Igray2,Igray3,NULL);

    //�ڷ�Χ�ڣ������� Imask(x,y) = 255
    cvInRange(Igray1,Ilow1,Ihi1,Imask);
    cvInRange(Igray2,Ilow2,Ihi2,Imaskt);
    cvOr(Imask,Imaskt,Imask);
    cvInRange(Igray3,Ilow3,Ihi3,Imaskt);
    cvOr(Imask,Imaskt,Imask);

    //Imaskȡ����������0  ǰ����255
    cvSubRS(Imask,cvScalar(255),Imask);
}
void DeallocateImages()
{
    cvReleaseImage( &IavgF );
    cvReleaseImage( &IdiffF );
    cvReleaseImage( &IprevF );
    cvReleaseImage( &IhiF );
    cvReleaseImage( &IlowF );

    cvReleaseImage( &Ilow1 );
    cvReleaseImage( &Ilow2 );
    cvReleaseImage( &Ilow3 );

    cvReleaseImage( &Ihi1 );
    cvReleaseImage( &Ihi2 );
    cvReleaseImage( &Ihi3 );

    cvReleaseImage( &Iscratch );
    cvReleaseImage( &Iscratch2 );

    cvReleaseImage( &Igray1 );
    cvReleaseImage( &Igray2 );
    cvReleaseImage( &Igray3 );

    cvReleaseImage( &Imaskt );

}
void ForegroundDetection_MeanBackground()
{
    //ƽ����������׼�� ����ø�����ٶ�
    CvCapture*  rmvb_1 = cvCreateFileCapture("one piece.rmvb");

    IplImage *frame = cvQueryFrame(rmvb_1);

    IplImage* Imask = cvCreateImage(cvGetSize(frame),IPL_DEPTH_8U,1);
    AllocateImages(frame);

    for(int i=0; i<35; i++)
    {
        frame = cvQueryFrame(rmvb_1);
        accumulateBackground(frame);
    }
    createModelsFromStats();

    int iHalfPix  = Imask->width*Imask->height/2;
    for(;;)
    {
        frame = cvQueryFrame(rmvb_1);
        if( !frame )
            break;
        backgroundDiff(frame,Imask);
        cvShowImage("Onepiece",Imask);
        cvWaitKey(33);
        int iCountNonZero = cvCountNonZero(Imask);
        if(iCountNonZero>iHalfPix)
        {
            cvZero( IavgF );
            cvZero( IdiffF );
            Icount = 0.00001;
            for(int i=0; i<35; i++)
            {
                frame = cvQueryFrame(rmvb_1);
                accumulateBackground(frame);
            }
            createModelsFromStats();
        }
    }
    cvReleaseImage(&Imask);
    DeallocateImages();
}

//------------------------------------------------------------------------
//
//------------------------------------------------------------------------

