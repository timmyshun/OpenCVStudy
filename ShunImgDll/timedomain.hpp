#ifndef TIMEDOMAIN_HPP_INCLUDED
#define TIMEDOMAIN_HPP_INCLUDED

//ͼ����С
extern "C" __declspec(dllexport) bool doPyrDown(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//ͼ��ģ��
extern "C" __declspec(dllexport) bool doSmooth(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//��Ե���
extern "C" __declspec(dllexport) bool doCanny(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels,\
                                              double lowThresh, double highThresh,double aperture);

//���ͨ��
extern "C" __declspec(dllexport) bool doSaturate_sv(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//ͼ����ǿ--��ֵ��
extern "C" __declspec(dllexport) bool doBinaryzation(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//ͼ����ǿ-��ת
extern "C" __declspec(dllexport) bool doReverse(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//ͼ����ǿ-�����任
extern "C" __declspec(dllexport) bool doLogTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);

//ͼ����ǿ-ָ���任
extern "C" __declspec(dllexport) bool doPowerTransform(const uchar inImgData[],uchar outImgData[],int width,int height,int depth,int nChannels);


#endif // TIMEDOMAIN_HPP_INCLUDED
