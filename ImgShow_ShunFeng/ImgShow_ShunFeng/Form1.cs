using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

using ImageProcessLib;

namespace ImgShow_ShunFeng
{
    public partial class ImgShowForm : Form
    {
        string filePath = string.Empty;//初始化文件路径
        public ImgShowForm()
        {
            InitializeComponent();
        }
      
        private void showImgInBox(Bitmap rawImage)
        {
            Size formSize = rawImage.Size;//根据图像改变窗体大小
            formSize.Width = formSize.Width > 380 ? formSize.Width+20 : 400;
            formSize.Height = formSize.Height+50;
            if (ImgShowForm.ActiveForm !=null)
                ImgShowForm.ActiveForm.ClientSize = formSize;
            pictureBox1.Width = rawImage.Width ;//根据图像改变图框大小
            pictureBox1.Height = rawImage.Height;
            pictureBox1.Image = (Image)rawImage;//将图片载入图框
        }
        private void buttonLoad_Click(object sender, EventArgs e)
        {
            OpenFileDialog fileDialog = new OpenFileDialog();//新建一个文件对话框
            fileDialog.Filter = "图像文件|*.jpg|图像文件|*.bmp|图像文件|*.png|所有文件|*.*";//文件格式过滤设置
            fileDialog.RestoreDirectory = true;//保存上一次文件路径
            if (fileDialog.ShowDialog() == DialogResult.OK)//如果选择了文件
            {
                this.filePath = fileDialog.FileName;//读入文件路径
                if (this.filePath.Length > 3 && (
                    (this.filePath.ToUpper().Contains("JPG")) ||
                    (this.filePath.ToUpper().Contains("BMP")) ||
                    (this.filePath.ToUpper().Contains("PNG")))
                    )//粗略判断是否为图像文件
                {
                    Bitmap rawImage = new Bitmap(filePath);//新建图像对象
                    this.showImgInBox(rawImage);
                }
                else
                {   //如果不是图像文件，清空路径并提示错误。
                    this.filePath = string.Empty;
                    MessageBox.Show("请载入jpg,bmp,png图像文件");
                    return;
                }
            }
        }
        private void buttonBack_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            else
            {
                Bitmap rawImage = new Bitmap(filePath);
                this.showImgInBox(rawImage);
            }
           
        }
        
        private void buttonPyrDown_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.pyrDownImage((Bitmap)pictureBox1.Image));

        }

        private void buttonSmooth_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.smoothImage((Bitmap)pictureBox1.Image));
        }

        private void buttonCanny_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.cannyImage((Bitmap)pictureBox1.Image, 10, 100, 3));
        }

        private void buttonSaturate_sv_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.saturate_sv((Bitmap)pictureBox1.Image));

        }
        private void buttonBinaryzation_Click(object sender, EventArgs e)
        {
            

        }
        private void buttonReverse_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.reverseImage((Bitmap)pictureBox1.Image));

        }
        private void buttonLogTransform_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.logTransformImage((Bitmap)pictureBox1.Image));

        }
        private void buttonPowerTransform_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.powerTransformImage((Bitmap)pictureBox1.Image));

        }

        private void pPHTToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.HoughLinePPHT((Bitmap)pictureBox1.Image));
        }

        private void gHTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.HoughCircleGHT((Bitmap)pictureBox1.Image));
        }

        private void sHTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.HoughLineSHT((Bitmap)pictureBox1.Image));
        }

        private void dFTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.DFT((Bitmap)pictureBox1.Image));
        }

        private void houghToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void 直方图均衡ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.EqualizeHist((Bitmap)pictureBox1.Image));
        }

        private void 多通道直方图均衡ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.EqualizeHistEX((Bitmap)pictureBox1.Image));
        }

        private void 显示直方图ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.DisplayHist((Bitmap)pictureBox1.Image));
        }

        private void 皮肤检测ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.CheckSkin((Bitmap)pictureBox1.Image));
        }

        private void 反向投影ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.BackProject((Bitmap)pictureBox1.Image));
        }

        private void 画出轮廓ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.FindContours((Bitmap)pictureBox1.Image));
        }

        private void 二值化大津法ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.binaryzationImageOSTU((Bitmap)pictureBox1.Image));
        }

        private void 二值化局部平均ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.binaryzationImageGAUSS((Bitmap)pictureBox1.Image));
        }

        private void 多边形逼近ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (filePath == string.Empty)//如果还未有有效的图片则提示
            {
                MessageBox.Show("请先载入图像");
                return;
            }
            this.showImgInBox(ImageProcess.ApproxPoly((Bitmap)pictureBox1.Image));
        }
    }
}
