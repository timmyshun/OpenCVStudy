#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;

// DFT
//���ݵĴ洢��ʽ���д�����
extern "C" __declspec(dllexport) bool doIntegral(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//��ȡ����ͼ��
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//�½����ͼ��


//    void cvIntegral(
//        const CvArr*  image,
//        CvArr*        sum,
//        CvArr*        sqsum      = NULL,
//        CvArr*        tilted_sum = NULL
//        );
    outputData(outImgData,out);//���ͼ��
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;
}
