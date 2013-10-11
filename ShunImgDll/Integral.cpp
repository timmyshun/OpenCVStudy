#include "opencv2/core/core.hpp"
#include "opencv/cv.h"
#include "opencv2/imgproc/imgproc.hpp"

#include "common.hpp"
using namespace cv;

// DFT
//数据的存储格式还有待考究
extern "C" __declspec(dllexport) bool doIntegral(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels)
{
    IplImage* in = getInputImg(inImgData,width,height,depth,nChannels);//获取输入图像
    IplImage* out = cvCreateImage(cvSize(width,height),depth,nChannels);//新建输出图像


//    void cvIntegral(
//        const CvArr*  image,
//        CvArr*        sum,
//        CvArr*        sqsum      = NULL,
//        CvArr*        tilted_sum = NULL
//        );
    outputData(outImgData,out);//输出图像
    cvReleaseImage(&in);
    cvReleaseImage(&out);

    return true;
}
