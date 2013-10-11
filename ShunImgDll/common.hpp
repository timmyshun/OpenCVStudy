#ifndef COMMON_HPP_INCLUDED
#define COMMON_HPP_INCLUDED

IplImage* getInputImg(const uchar inImgData[],int width,int height,int depth,int nChannels);
void outputData(uchar outImgData[],IplImage* out);

#endif // COMMON_HPP_INCLUDED


