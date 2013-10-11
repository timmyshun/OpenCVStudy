#ifndef TIMEDOMAIN_HPP_INCLUDED
#define TIMEDOMAIN_HPP_INCLUDED

//图像缩小
extern "C" __declspec(dllexport) bool doPyrDown(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//图像模糊
extern "C" __declspec(dllexport) bool doSmooth(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//边缘检测
extern "C" __declspec(dllexport) bool doCanny(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels,\
                                              double lowThresh, double highThresh,double aperture);

//最大化通道
extern "C" __declspec(dllexport) bool doSaturate_sv(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//图像增强--二值化
extern "C" __declspec(dllexport) bool doBinaryzation(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//图像增强-反转
extern "C" __declspec(dllexport) bool doReverse(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//图像增强-对数变换
extern "C" __declspec(dllexport) bool doLogTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//图像增强-指数变换
extern "C" __declspec(dllexport) bool doPowerTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);


#endif // TIMEDOMAIN_HPP_INCLUDED
