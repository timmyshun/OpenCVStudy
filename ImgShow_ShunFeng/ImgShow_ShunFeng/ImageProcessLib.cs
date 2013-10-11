using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;//bitmap

using System.Drawing.Imaging;//bitmapData
using System.Runtime.InteropServices;//Marshal.Copy DllImport

namespace ImageProcessLib
{
    class ImageProcess
    {
        //公共函数
        private static Byte[] getImgData(Bitmap inImg)
        {
            Rectangle rect = new Rectangle(0, 0, inImg.Width, inImg.Height);//图片的大小矩阵
            BitmapData inImgData = inImg.LockBits(rect, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //将输入图片数据拷贝出来
            int bytes = inImgData.Stride * inImgData.Height;//数据组长度
            Byte[] inByteData = new Byte[bytes];//新建byte数组缓存图片数据
            Marshal.Copy(inImgData.Scan0, inByteData, 0, bytes);//将图片数据复制进缓存数组中
            inImg.UnlockBits(inImgData);//释放掉图像数据锁
            return inByteData;
        }
        //缩小图像
        [DllImport("libShunImgDll.dll")]
        public static extern bool doPyrDown(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap pyrDownImage(Bitmap inImg)
        {
            if (inImg.Width < 2 || inImg.Height < 2)
            {
                Bitmap blankImg = new Bitmap(1, 1);
                return blankImg;
            }

            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width / 2, inImg.Height / 2);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);
   
            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//一半长度
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doPyrDown(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像缩小
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //光滑图像
        [DllImport("libShunImgDll.dll")]
        public static extern bool doSmooth(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap smoothImage(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doSmooth(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像模糊
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        [DllImport("libShunImgDll.dll")]
        public static extern bool doCanny(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels,
                                           double lowThresh, double highThresh,double aperture);
        public static Bitmap cannyImage(Bitmap inImg, double lowThresh, double highThresh, double aperture)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doCanny(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3, lowThresh, highThresh, aperture);//图像边缘检测
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //通道增强
        [DllImport("libShunImgDll.dll")]
        public static extern bool doSaturate_sv(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap saturate_sv(Bitmap inImg) 
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据

            //处理图像
            doSaturate_sv(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像增强

            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;   
        }
        //二值化
        [DllImport("libShunImgDll.dll")]
        public static extern bool doBinaryzationOSTU(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap binaryzationImageOSTU(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doBinaryzationOSTU(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //二值化
        [DllImport("libShunImgDll.dll")]
        public static extern bool doBinaryzationGAUSS(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap binaryzationImageGAUSS(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doBinaryzationGAUSS(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //图像反转
        [DllImport("libShunImgDll.dll")]
        public static extern bool doReverse(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap reverseImage(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doReverse(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //图像对数变换
        [DllImport("libShunImgDll.dll")]
        public static extern bool doLogTransform(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap logTransformImage(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doLogTransform(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //图像指数变换
        [DllImport("libShunImgDll.dll")]
        public static extern bool doPowerTransform(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap powerTransformImage(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doPowerTransform(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //Hough直线检测
        [DllImport("libShunImgDll.dll")]
        public static extern bool doHoughLinePPHT(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap HoughLinePPHT(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doHoughLinePPHT(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //Hough直线检测
        [DllImport("libShunImgDll.dll")]
        public static extern bool doHoughLineSHT(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap HoughLineSHT(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doHoughLineSHT(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //Hough圆检测
        [DllImport("libShunImgDll.dll")]
        public static extern bool doHoughCircleGHT(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap HoughCircleGHT(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doHoughCircleGHT(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //DFT
        [DllImport("libShunImgDll.dll")]
        public static extern bool doDFT(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap DFT(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doDFT(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //直方图均衡
        [DllImport("libShunImgDll.dll")]
        public static extern bool doEqualizeHist(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap EqualizeHist(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doEqualizeHist(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //直方图均衡
        [DllImport("libShunImgDll.dll")]
        public static extern bool doEqualizeHistEX(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap EqualizeHistEX(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doEqualizeHistEX(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //直方图均衡
        [DllImport("libShunImgDll.dll")]
        public static extern bool doDisplayHist(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap DisplayHist(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doDisplayHist(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //皮肤检测
        [DllImport("libShunImgDll.dll")]
        public static extern bool doCheckSkin(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap CheckSkin(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doCheckSkin(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
        //反向投影
        [DllImport("libShunImgDll.dll")]
        public static extern bool doBackProject(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap BackProject(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doBackProject(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //寻找轮廓
        [DllImport("libShunImgDll.dll")]
        public static extern bool doFindContours(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap FindContours(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doFindContours(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }

        //多边形逼近
        [DllImport("libShunImgDll.dll")]
        public static extern bool doApproxPoly(Byte[] inImgData, Byte[] outImgData, int width, int height, int depth, int nChannels);
        public static Bitmap ApproxPoly(Bitmap inImg)
        {
            //新建输出图像
            Bitmap outImg = new Bitmap(inImg.Width, inImg.Height);
            Rectangle rectOut = new Rectangle(0, 0, outImg.Width, outImg.Height);//图片的大小矩阵
            BitmapData outImgData = outImg.LockBits(rectOut, ImageLockMode.ReadWrite, PixelFormat.Format24bppRgb);//获取图片的数据锁
            //获取输入图片的数据
            Byte[] inByteData = getImgData(inImg);

            //新建输出图片数据的缓存数组
            int bytes = outImgData.Stride * outImgData.Height;//数据
            Byte[] outByteData = new Byte[bytes];//新建byte数组缓存图片数据
            //处理图像
            doApproxPoly(inByteData, outByteData, inImg.Width, inImg.Height, 8, 3);//图像二值化
            Marshal.Copy(outByteData, 0, outImgData.Scan0, bytes);//将图片数据复制进缓存数组中
            outImg.UnlockBits(outImgData);//释放掉图像数据锁
            return outImg;
        }
    }
}
