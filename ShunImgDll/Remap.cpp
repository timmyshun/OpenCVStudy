#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;

extern "C" __declspec(dllexport) bool doWrapAffineWrap(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCloneImage(in);//�½����ͼ��

    CvPoint2D32f srcTri[3], dstTri[3];
    CvMat*      warp_mat = cvCreateMat(2,3,CV_32FC1);

    out->origin = in->origin;
    cvZero(out);
    //����������
    srcTri[0].x = 0;            //����
    srcTri[0].y = 0;
    srcTri[1].x = in->width-1;  //����
    srcTri[1].y = 0;
    srcTri[2].x = 0;            //���� ����ƽ���ı���
    srcTri[2].y = in->height-1;

    dstTri[0].x = in->width*0.0;    //�任�������
    dstTri[0].y = in->height*0.33;
    dstTri[1].x = in->width*0.85;   //�任�������
    dstTri[1].y = in->height*0.25;
    dstTri[2].x = in->width*0.15;   //�任�������
    dstTri[2].y = in->height*0.7;

    cvGetAffineTransform( srcTri, dstTri,warp_mat);
    cvWarpAffine(in,out,warp_mat);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;

}


//����任  ��ת
extern "C" __declspec(dllexport) bool doWrapAffineRot(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCloneImage(in);//�½����ͼ��

    CvPoint2D32f pointCenter =cvPoint2D32f(in->width/2,in->height/2);
    CvMat*      rot_mat = cvCreateMat(2,3,CV_32FC1);

    double angle = -50.0;
    double scale = 0.6;
    cv2DRotationMatrix( pointCenter, angle, scale , rot_mat);

    cvWarpAffine(in,out,rot_mat);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;

}

//͸�ӱ任
extern "C" __declspec(dllexport) bool doWrapAffinePerspective(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCloneImage(in);//�½����ͼ��

    CvPoint2D32f srcQuad[4], dstQuad[4];
    CvMat*      warp_mat = cvCreateMat(3,3,CV_32FC1);

    out->origin = in->origin;
    cvZero(out);
    //����������
    srcQuad[0].x = 0;            //����
    srcQuad[0].y = 0;
    srcQuad[1].x = in->width-1;  //����
    srcQuad[1].y = 0;
    srcQuad[2].x = 0;            //���� ����ƽ���ı���
    srcQuad[2].y = in->height-1;
    srcQuad[3].x = in->width-1;     //����
    srcQuad[3].y = in->height-1;

    dstQuad[0].x = in->width*0.05;    //�任�������
    dstQuad[0].y = in->height*0.33;
    dstQuad[1].x = in->width*0.9;   //�任�������
    dstQuad[1].y = in->height*0.25;
    dstQuad[2].x = in->width*0.2;   //�任�������
    dstQuad[2].y = in->height*0.7;
    dstQuad[3].x = in->width*0.8;   //�任�������
    dstQuad[3].y = in->height*0.9;

    cvGetPerspectiveTransform( srcQuad, dstQuad,warp_mat);
    cvWarpPerspective(in,out,warp_mat);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;

}

//����������任
extern "C" __declspec(dllexport) bool doLogPolar(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels){
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��

    cvLogPolar(in,out,cvPoint2D32f(in->width/2,in->height/2),40);

    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;

}
