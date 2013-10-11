namespace ImgShow_ShunFeng
{
    partial class ImgShowForm
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.buttonPyrDown = new System.Windows.Forms.Button();
            this.buttonSmooth = new System.Windows.Forms.Button();
            this.buttonCanny = new System.Windows.Forms.Button();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.文件FToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.打开图片ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.恢复原图ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.图像增强ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.二值化ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.图像反转ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gR通道增强ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.对数变换ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.指数变换ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.直方图均衡ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.多通道直方图均衡ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.显示直方图ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.皮肤检测ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.反向投影ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.houghToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pPHTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.pPHTToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.sHTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.圆检测ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.gHTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.基本变换ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.傅里叶ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dFTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.iDFTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.轮廓ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.画出轮廓ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.二值化大津法ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.二值化局部平均ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.多边形逼近ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Location = new System.Drawing.Point(14, 53);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(560, 327);
            this.pictureBox1.TabIndex = 1;
            this.pictureBox1.TabStop = false;
            // 
            // buttonPyrDown
            // 
            this.buttonPyrDown.Location = new System.Drawing.Point(79, 27);
            this.buttonPyrDown.Name = "buttonPyrDown";
            this.buttonPyrDown.Size = new System.Drawing.Size(64, 22);
            this.buttonPyrDown.TabIndex = 2;
            this.buttonPyrDown.Text = "缩小图片";
            this.buttonPyrDown.UseVisualStyleBackColor = true;
            this.buttonPyrDown.Click += new System.EventHandler(this.buttonPyrDown_Click);
            // 
            // buttonSmooth
            // 
            this.buttonSmooth.Location = new System.Drawing.Point(149, 27);
            this.buttonSmooth.Name = "buttonSmooth";
            this.buttonSmooth.Size = new System.Drawing.Size(66, 22);
            this.buttonSmooth.TabIndex = 3;
            this.buttonSmooth.Text = "光滑图片";
            this.buttonSmooth.UseVisualStyleBackColor = true;
            this.buttonSmooth.Click += new System.EventHandler(this.buttonSmooth_Click);
            // 
            // buttonCanny
            // 
            this.buttonCanny.Location = new System.Drawing.Point(221, 27);
            this.buttonCanny.Name = "buttonCanny";
            this.buttonCanny.Size = new System.Drawing.Size(63, 22);
            this.buttonCanny.TabIndex = 4;
            this.buttonCanny.Text = "边缘检测";
            this.buttonCanny.UseVisualStyleBackColor = true;
            this.buttonCanny.Click += new System.EventHandler(this.buttonCanny_Click);
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.文件FToolStripMenuItem,
            this.图像增强ToolStripMenuItem,
            this.houghToolStripMenuItem,
            this.基本变换ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(583, 25);
            this.menuStrip1.TabIndex = 6;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // 文件FToolStripMenuItem
            // 
            this.文件FToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.打开图片ToolStripMenuItem,
            this.恢复原图ToolStripMenuItem});
            this.文件FToolStripMenuItem.Name = "文件FToolStripMenuItem";
            this.文件FToolStripMenuItem.Size = new System.Drawing.Size(50, 21);
            this.文件FToolStripMenuItem.Text = "文件&F";
            // 
            // 打开图片ToolStripMenuItem
            // 
            this.打开图片ToolStripMenuItem.Name = "打开图片ToolStripMenuItem";
            this.打开图片ToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.打开图片ToolStripMenuItem.Text = "打开图片...";
            this.打开图片ToolStripMenuItem.Click += new System.EventHandler(this.buttonLoad_Click);
            // 
            // 恢复原图ToolStripMenuItem
            // 
            this.恢复原图ToolStripMenuItem.Name = "恢复原图ToolStripMenuItem";
            this.恢复原图ToolStripMenuItem.Size = new System.Drawing.Size(133, 22);
            this.恢复原图ToolStripMenuItem.Text = "重载原图";
            this.恢复原图ToolStripMenuItem.Click += new System.EventHandler(this.buttonBack_Click);
            // 
            // 图像增强ToolStripMenuItem
            // 
            this.图像增强ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.二值化ToolStripMenuItem,
            this.图像反转ToolStripMenuItem,
            this.gR通道增强ToolStripMenuItem,
            this.对数变换ToolStripMenuItem,
            this.指数变换ToolStripMenuItem,
            this.直方图均衡ToolStripMenuItem,
            this.多通道直方图均衡ToolStripMenuItem,
            this.显示直方图ToolStripMenuItem,
            this.皮肤检测ToolStripMenuItem,
            this.反向投影ToolStripMenuItem});
            this.图像增强ToolStripMenuItem.Name = "图像增强ToolStripMenuItem";
            this.图像增强ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.图像增强ToolStripMenuItem.Text = "图像增强";
            // 
            // 二值化ToolStripMenuItem
            // 
            this.二值化ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.二值化大津法ToolStripMenuItem,
            this.二值化局部平均ToolStripMenuItem});
            this.二值化ToolStripMenuItem.Name = "二值化ToolStripMenuItem";
            this.二值化ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.二值化ToolStripMenuItem.Text = "二值化";
            this.二值化ToolStripMenuItem.ToolTipText = "简化图像,凸显轮廓";
            this.二值化ToolStripMenuItem.Click += new System.EventHandler(this.buttonBinaryzation_Click);
            // 
            // 图像反转ToolStripMenuItem
            // 
            this.图像反转ToolStripMenuItem.Name = "图像反转ToolStripMenuItem";
            this.图像反转ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.图像反转ToolStripMenuItem.Text = "图像反转";
            this.图像反转ToolStripMenuItem.ToolTipText = "显现在暗区域的灰白点";
            this.图像反转ToolStripMenuItem.Click += new System.EventHandler(this.buttonReverse_Click);
            // 
            // gR通道增强ToolStripMenuItem
            // 
            this.gR通道增强ToolStripMenuItem.Name = "gR通道增强ToolStripMenuItem";
            this.gR通道增强ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.gR通道增强ToolStripMenuItem.Text = "GR通道增强";
            this.gR通道增强ToolStripMenuItem.Click += new System.EventHandler(this.buttonSaturate_sv_Click);
            // 
            // 对数变换ToolStripMenuItem
            // 
            this.对数变换ToolStripMenuItem.Name = "对数变换ToolStripMenuItem";
            this.对数变换ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.对数变换ToolStripMenuItem.Text = "对数变换";
            this.对数变换ToolStripMenuItem.ToolTipText = "图像灰度扩展和压缩的功能。让图像的灰度分布更加符合人的视觉特征。";
            this.对数变换ToolStripMenuItem.Click += new System.EventHandler(this.buttonLogTransform_Click);
            // 
            // 指数变换ToolStripMenuItem
            // 
            this.指数变换ToolStripMenuItem.Name = "指数变换ToolStripMenuItem";
            this.指数变换ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.指数变换ToolStripMenuItem.Text = "指数变换";
            this.指数变换ToolStripMenuItem.ToolTipText = "校正图片亮度";
            this.指数变换ToolStripMenuItem.Click += new System.EventHandler(this.buttonPowerTransform_Click);
            // 
            // 直方图均衡ToolStripMenuItem
            // 
            this.直方图均衡ToolStripMenuItem.Name = "直方图均衡ToolStripMenuItem";
            this.直方图均衡ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.直方图均衡ToolStripMenuItem.Text = "直方图均衡";
            this.直方图均衡ToolStripMenuItem.Click += new System.EventHandler(this.直方图均衡ToolStripMenuItem_Click);
            // 
            // 多通道直方图均衡ToolStripMenuItem
            // 
            this.多通道直方图均衡ToolStripMenuItem.Name = "多通道直方图均衡ToolStripMenuItem";
            this.多通道直方图均衡ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.多通道直方图均衡ToolStripMenuItem.Text = "多通道直方图均衡";
            this.多通道直方图均衡ToolStripMenuItem.Click += new System.EventHandler(this.多通道直方图均衡ToolStripMenuItem_Click);
            // 
            // 显示直方图ToolStripMenuItem
            // 
            this.显示直方图ToolStripMenuItem.Name = "显示直方图ToolStripMenuItem";
            this.显示直方图ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.显示直方图ToolStripMenuItem.Text = "显示直方图";
            this.显示直方图ToolStripMenuItem.Click += new System.EventHandler(this.显示直方图ToolStripMenuItem_Click);
            // 
            // 皮肤检测ToolStripMenuItem
            // 
            this.皮肤检测ToolStripMenuItem.Name = "皮肤检测ToolStripMenuItem";
            this.皮肤检测ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.皮肤检测ToolStripMenuItem.Text = "皮肤检测";
            this.皮肤检测ToolStripMenuItem.Click += new System.EventHandler(this.皮肤检测ToolStripMenuItem_Click);
            // 
            // 反向投影ToolStripMenuItem
            // 
            this.反向投影ToolStripMenuItem.Name = "反向投影ToolStripMenuItem";
            this.反向投影ToolStripMenuItem.Size = new System.Drawing.Size(172, 22);
            this.反向投影ToolStripMenuItem.Text = "反向投影";
            this.反向投影ToolStripMenuItem.Click += new System.EventHandler(this.反向投影ToolStripMenuItem_Click);
            // 
            // houghToolStripMenuItem
            // 
            this.houghToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pPHTToolStripMenuItem,
            this.圆检测ToolStripMenuItem});
            this.houghToolStripMenuItem.Name = "houghToolStripMenuItem";
            this.houghToolStripMenuItem.Size = new System.Drawing.Size(59, 21);
            this.houghToolStripMenuItem.Text = "Hough";
            this.houghToolStripMenuItem.Click += new System.EventHandler(this.houghToolStripMenuItem_Click);
            // 
            // pPHTToolStripMenuItem
            // 
            this.pPHTToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.pPHTToolStripMenuItem1,
            this.sHTToolStripMenuItem});
            this.pPHTToolStripMenuItem.Name = "pPHTToolStripMenuItem";
            this.pPHTToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.pPHTToolStripMenuItem.Text = "直线检测";
            // 
            // pPHTToolStripMenuItem1
            // 
            this.pPHTToolStripMenuItem1.Name = "pPHTToolStripMenuItem1";
            this.pPHTToolStripMenuItem1.Size = new System.Drawing.Size(106, 22);
            this.pPHTToolStripMenuItem1.Text = "PPHT";
            this.pPHTToolStripMenuItem1.Click += new System.EventHandler(this.pPHTToolStripMenuItem1_Click);
            // 
            // sHTToolStripMenuItem
            // 
            this.sHTToolStripMenuItem.Name = "sHTToolStripMenuItem";
            this.sHTToolStripMenuItem.Size = new System.Drawing.Size(106, 22);
            this.sHTToolStripMenuItem.Text = "SHT";
            this.sHTToolStripMenuItem.Click += new System.EventHandler(this.sHTToolStripMenuItem_Click);
            // 
            // 圆检测ToolStripMenuItem
            // 
            this.圆检测ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.gHTToolStripMenuItem});
            this.圆检测ToolStripMenuItem.Name = "圆检测ToolStripMenuItem";
            this.圆检测ToolStripMenuItem.Size = new System.Drawing.Size(124, 22);
            this.圆检测ToolStripMenuItem.Text = "圆检测";
            // 
            // gHTToolStripMenuItem
            // 
            this.gHTToolStripMenuItem.Name = "gHTToolStripMenuItem";
            this.gHTToolStripMenuItem.Size = new System.Drawing.Size(101, 22);
            this.gHTToolStripMenuItem.Text = "GHT";
            this.gHTToolStripMenuItem.Click += new System.EventHandler(this.gHTToolStripMenuItem_Click);
            // 
            // 基本变换ToolStripMenuItem
            // 
            this.基本变换ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.傅里叶ToolStripMenuItem,
            this.轮廓ToolStripMenuItem});
            this.基本变换ToolStripMenuItem.Name = "基本变换ToolStripMenuItem";
            this.基本变换ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.基本变换ToolStripMenuItem.Text = "基本变换";
            // 
            // 傅里叶ToolStripMenuItem
            // 
            this.傅里叶ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.dFTToolStripMenuItem,
            this.iDFTToolStripMenuItem});
            this.傅里叶ToolStripMenuItem.Name = "傅里叶ToolStripMenuItem";
            this.傅里叶ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.傅里叶ToolStripMenuItem.Text = "傅里叶";
            // 
            // dFTToolStripMenuItem
            // 
            this.dFTToolStripMenuItem.Name = "dFTToolStripMenuItem";
            this.dFTToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.dFTToolStripMenuItem.Text = "DFT";
            this.dFTToolStripMenuItem.Click += new System.EventHandler(this.dFTToolStripMenuItem_Click);
            // 
            // iDFTToolStripMenuItem
            // 
            this.iDFTToolStripMenuItem.Name = "iDFTToolStripMenuItem";
            this.iDFTToolStripMenuItem.Size = new System.Drawing.Size(102, 22);
            this.iDFTToolStripMenuItem.Text = "IDFT";
            // 
            // 轮廓ToolStripMenuItem
            // 
            this.轮廓ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.画出轮廓ToolStripMenuItem,
            this.多边形逼近ToolStripMenuItem});
            this.轮廓ToolStripMenuItem.Name = "轮廓ToolStripMenuItem";
            this.轮廓ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.轮廓ToolStripMenuItem.Text = "轮廓";
            // 
            // 画出轮廓ToolStripMenuItem
            // 
            this.画出轮廓ToolStripMenuItem.Name = "画出轮廓ToolStripMenuItem";
            this.画出轮廓ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.画出轮廓ToolStripMenuItem.Text = "画出轮廓";
            this.画出轮廓ToolStripMenuItem.Click += new System.EventHandler(this.画出轮廓ToolStripMenuItem_Click);
            // 
            // 二值化大津法ToolStripMenuItem
            // 
            this.二值化大津法ToolStripMenuItem.Name = "二值化大津法ToolStripMenuItem";
            this.二值化大津法ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.二值化大津法ToolStripMenuItem.Text = "二值化大津法";
            this.二值化大津法ToolStripMenuItem.Click += new System.EventHandler(this.二值化大津法ToolStripMenuItem_Click);
            // 
            // 二值化局部平均ToolStripMenuItem
            // 
            this.二值化局部平均ToolStripMenuItem.Name = "二值化局部平均ToolStripMenuItem";
            this.二值化局部平均ToolStripMenuItem.Size = new System.Drawing.Size(160, 22);
            this.二值化局部平均ToolStripMenuItem.Text = "二值化局部平均";
            this.二值化局部平均ToolStripMenuItem.Click += new System.EventHandler(this.二值化局部平均ToolStripMenuItem_Click);
            // 
            // 多边形逼近ToolStripMenuItem
            // 
            this.多边形逼近ToolStripMenuItem.Name = "多边形逼近ToolStripMenuItem";
            this.多边形逼近ToolStripMenuItem.Size = new System.Drawing.Size(152, 22);
            this.多边形逼近ToolStripMenuItem.Text = "多边形逼近";
            this.多边形逼近ToolStripMenuItem.Click += new System.EventHandler(this.多边形逼近ToolStripMenuItem_Click);
            // 
            // ImgShowForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(583, 386);
            this.Controls.Add(this.buttonCanny);
            this.Controls.Add(this.buttonSmooth);
            this.Controls.Add(this.buttonPyrDown);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "ImgShowForm";
            this.Text = "ImgShow_ShunFeng";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Button buttonPyrDown;
        private System.Windows.Forms.Button buttonSmooth;
        private System.Windows.Forms.Button buttonCanny;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 文件FToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 打开图片ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 图像增强ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 二值化ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 图像反转ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem gR通道增强ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 恢复原图ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 对数变换ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 指数变换ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 基本变换ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 傅里叶ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dFTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem iDFTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem houghToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pPHTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem pPHTToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem sHTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 圆检测ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem gHTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 直方图均衡ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 多通道直方图均衡ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 显示直方图ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 皮肤检测ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 反向投影ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 轮廓ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 画出轮廓ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 二值化大津法ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 二值化局部平均ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 多边形逼近ToolStripMenuItem;
    }
}

