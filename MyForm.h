#pragma once
#include <atlstr.h>
#include <iostream>
#include "Image.h";
#include "Clustering.h";
#include "Morphology.h"
#include "GaussianFiltering.h"
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// MyForm için özet
/// </summary>
public ref class MyForm : public System::Windows::Forms::Form{


public:
	MyForm(void)
	{
		InitializeComponent();
		//
		//TODO: Oluþturucu kodunu buraya ekle
		//
	}

protected:
	/// <summary>
	///Kullanýlan tüm kaynaklarý temizleyin.
	/// </summary>
	~MyForm()
	{
		if (components)
		{
			delete components;
		}
	}
private: System::Windows::Forms::MenuStrip^ menuStrip1;
protected:
private: System::Windows::Forms::ToolStripMenuItem^ fileToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ openToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ processingTypeToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ convertGrayScaleToolStripMenuItem;
private: System::Windows::Forms::PictureBox^ pictureBox1;
private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
private: System::Windows::Forms::DataVisualization::Charting::Chart^ chart1;

private:
	/// <summary>
	///Gerekli tasarýmcý deðiþkeni.
	/// </summary>


	int* hist = NULL;//grayscale resmin histogramýný iþaret eden pointer

	unsigned char* RGBImg_data = NULL; // alýnan görüntünün deðerleininin tüm class bazýnda kullanýlmasý için yaratýlan veri üyeleri.sýnýf içinde globalleþtirdik.
	int RGBImg_w, RGBImg_h, RGBImg_c;

	unsigned char* grayImg_data = NULL; // alýnan görüntünün deðerleininin tüm class bazýnda kullanýlmasý için yaratýlan veri üyeleri.sýnýf içinde globalleþtirdik.
	int grayImg_w, grayImg_h, grayImg_c;

	unsigned char* binaryImg_data = NULL; // alýnan görüntünün deðerleininin tüm class bazýnda kullanýlmasý için yaratýlan veri üyeleri.sýnýf içinde globalleþtirdik.
	int binaryImg_w, binaryImg_h, binaryImg_c;

	unsigned char* morphImg_data = NULL;
	int morphImg_w, morphImg_h, morphImg_c;
private: System::Windows::Forms::ToolStripMenuItem^ cCAToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ hosheToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ edgeDetectionToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ sobelToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ prewittToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ cannyToolStripMenuItem;



private: System::Windows::Forms::ToolStripMenuItem^ convertBinaryToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ kMeansClusteringToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ otsuThresholdingToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ morphologyToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ dilationToolStripMenuItem;
private: System::Windows::Forms::ToolStripMenuItem^ erosionToolStripMenuItem;



	   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	   /// <summary>
	   /// Tasarýmcý desteði için gerekli metot - bu metodun 
	   ///içeriðini kod düzenleyici ile deðiþtirmeyin.
	   /// </summary>
	   /// 
	   void ShowGrayScaleImage(image im) {//Pictureboxta rgb görüntü gösterilir.

		   //picture box yükseklik/geniþlik setlemesi
		   pictureBox1->Width = im.w;
		   pictureBox1->Height = im.h;
		   pictureBox1->Refresh();

		   Bitmap^ surface = gcnew Bitmap(im.w, im.h);/*aldýðýmýz resim jpg veya png uzantýlý ama biz pictureboxta bitmap olarak göstereceðiz.
													  bu yüzden alýnan resmin yükseklik ve geniþlik deðerlerinden boþ bir bitmap resmi oluþturduk.*/
		   pictureBox1->Image = surface;//picture box a attýk.

		   // imageRGb[w][h][c] == imageRDB1Dimension[w*h*c]
		   Color c;//k
		   int psw, bufpos;
		   psw = im.w * im.c;

		   for (int row = 0; row < im.h; row++)
			   for (int col = 0; col < im.w; col++) {
				   bufpos = row * psw + col * im.c;
				   c = Color::FromArgb(im.data[bufpos], im.data[bufpos], im.data[bufpos]);
				   surface->SetPixel(col, row, c);
				   std::cout << c.A << std::endl;
			   }



	   }

	   void ShowRGBImage(image im) {

		   pictureBox1->Width = im.w;
		   pictureBox1->Height = im.h;
		   pictureBox1->Refresh();

		   Bitmap^ surface = gcnew Bitmap(im.w, im.h);
		   pictureBox1->Image = surface;

		   Color c;
		   int psw, bufpos;
		   psw = im.w * im.c; //rgb nesneler için weight*3;
		   //for döngüsü ile h*w*3 imagenin her bir pixel deðerini alýrýz.
		   for (int row = 0; row < im.h; row++)
			   for (int col = 0; col < im.w; col++) {
				   bufpos = row * psw + col * im.c;
				   c = Color::FromArgb(im.data[bufpos], im.data[bufpos + 1], im.data[bufpos + 2]);
				   surface->SetPixel(col, row, c);
			   }

	   }

	   void ShowBinaryImage(image im) {//Pictureboxta rgb görüntü gösterilir.

		   //picture box yükseklik/geniþlik setlemesi
		   pictureBox1->Width = im.w;
		   pictureBox1->Height = im.h;
		   pictureBox1->Refresh();

		   Bitmap^ surface = gcnew Bitmap(im.w, im.h);/*aldýðýmýz resim jpg veya png uzantýlý ama biz pictureboxta bitmap olarak göstereceðiz.
													  bu yüzden alýnan resmin yükseklik ve geniþlik deðerlerinden boþ bir bitmap resmi oluþturduk.*/
		   pictureBox1->Image = surface;//picture box a attýk.

		   // imageRGb[w][h][c] == imageRDB1Dimension[w*h*c]
		   Color c;//k
		   int psw, bufpos;
		   psw = im.w * im.c;

		   for (int row = 0; row < im.h; row++)
			   for (int col = 0; col < im.w; col++) {
				   bufpos = row * psw + col * im.c;
				   c = Color::FromArgb(im.data[bufpos], im.data[bufpos], im.data[bufpos]);
				   surface->SetPixel(col, row, c);
				   std::cout << c.A << std::endl;
			   }



	   }
	   void InitializeComponent(void)
	   {
		   System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		   System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
		   System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		   this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->processingTypeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->convertGrayScaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->convertBinaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->kMeansClusteringToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->otsuThresholdingToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->morphologyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->dilationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->erosionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->cCAToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->hosheToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		   this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		   this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		   this->edgeDetectionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->sobelToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->prewittToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->cannyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		   this->menuStrip1->SuspendLayout();
		   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
		   this->SuspendLayout();
		   // 
		   // menuStrip1
		   // 
		   this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
		   this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
			   this->fileToolStripMenuItem,
				   this->processingTypeToolStripMenuItem, this->morphologyToolStripMenuItem, this->cCAToolStripMenuItem, this->edgeDetectionToolStripMenuItem
		   });
		   this->menuStrip1->Location = System::Drawing::Point(0, 0);
		   this->menuStrip1->Name = L"menuStrip1";
		   this->menuStrip1->Size = System::Drawing::Size(1360, 28);
		   this->menuStrip1->TabIndex = 0;
		   this->menuStrip1->Text = L"menuStrip1";
		   // 
		   // fileToolStripMenuItem
		   // 
		   this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->openToolStripMenuItem });
		   this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
		   this->fileToolStripMenuItem->Size = System::Drawing::Size(46, 24);
		   this->fileToolStripMenuItem->Text = L"File";
		   // 
		   // openToolStripMenuItem
		   // 
		   this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
		   this->openToolStripMenuItem->Size = System::Drawing::Size(224, 26);
		   this->openToolStripMenuItem->Text = L"Open";
		   this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::openToolStripMenuItem_Click);
		   // 
		   // processingTypeToolStripMenuItem
		   // 
		   this->processingTypeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			   this->convertGrayScaleToolStripMenuItem,
				   this->convertBinaryToolStripMenuItem
		   });
		   this->processingTypeToolStripMenuItem->Name = L"processingTypeToolStripMenuItem";
		   this->processingTypeToolStripMenuItem->Size = System::Drawing::Size(128, 24);
		   this->processingTypeToolStripMenuItem->Text = L"Processing Type";
		   // 
		   // convertGrayScaleToolStripMenuItem
		   // 
		   this->convertGrayScaleToolStripMenuItem->Name = L"convertGrayScaleToolStripMenuItem";
		   this->convertGrayScaleToolStripMenuItem->Size = System::Drawing::Size(216, 26);
		   this->convertGrayScaleToolStripMenuItem->Text = L"Convert Gray Scale";
		   this->convertGrayScaleToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::convertGrayScaleToolStripMenuItem_Click);
		   // 
		   // convertBinaryToolStripMenuItem
		   // 
		   this->convertBinaryToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			   this->kMeansClusteringToolStripMenuItem,
				   this->otsuThresholdingToolStripMenuItem
		   });
		   this->convertBinaryToolStripMenuItem->Name = L"convertBinaryToolStripMenuItem";
		   this->convertBinaryToolStripMenuItem->Size = System::Drawing::Size(216, 26);
		   this->convertBinaryToolStripMenuItem->Text = L"Convert Binary";
		   // 
		   // kMeansClusteringToolStripMenuItem
		   // 
		   this->kMeansClusteringToolStripMenuItem->Name = L"kMeansClusteringToolStripMenuItem";
		   this->kMeansClusteringToolStripMenuItem->Size = System::Drawing::Size(214, 26);
		   this->kMeansClusteringToolStripMenuItem->Text = L"KMeans Clustering";
		   this->kMeansClusteringToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::kMeansClusteringToolStripMenuItem_Click);
		   // 
		   // otsuThresholdingToolStripMenuItem
		   // 
		   this->otsuThresholdingToolStripMenuItem->Name = L"otsuThresholdingToolStripMenuItem";
		   this->otsuThresholdingToolStripMenuItem->Size = System::Drawing::Size(214, 26);
		   this->otsuThresholdingToolStripMenuItem->Text = L"Otsu Thresholding";
		   this->otsuThresholdingToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::otsuThresholdingToolStripMenuItem_Click);
		   // 
		   // morphologyToolStripMenuItem
		   // 
		   this->morphologyToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			   this->dilationToolStripMenuItem,
				   this->erosionToolStripMenuItem
		   });
		   this->morphologyToolStripMenuItem->Name = L"morphologyToolStripMenuItem";
		   this->morphologyToolStripMenuItem->Size = System::Drawing::Size(105, 24);
		   this->morphologyToolStripMenuItem->Text = L"Morphology";
		   // 
		   // dilationToolStripMenuItem
		   // 
		   this->dilationToolStripMenuItem->Name = L"dilationToolStripMenuItem";
		   this->dilationToolStripMenuItem->Size = System::Drawing::Size(145, 26);
		   this->dilationToolStripMenuItem->Text = L"Dilation";
		   this->dilationToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::dilationToolStripMenuItem_Click);
		   // 
		   // erosionToolStripMenuItem
		   // 
		   this->erosionToolStripMenuItem->Name = L"erosionToolStripMenuItem";
		   this->erosionToolStripMenuItem->Size = System::Drawing::Size(145, 26);
		   this->erosionToolStripMenuItem->Text = L"Erosion";
		   this->erosionToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::erosionToolStripMenuItem_Click);
		   // 
		   // cCAToolStripMenuItem
		   // 
		   this->cCAToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->hosheToolStripMenuItem });
		   this->cCAToolStripMenuItem->Name = L"cCAToolStripMenuItem";
		   this->cCAToolStripMenuItem->Size = System::Drawing::Size(51, 24);
		   this->cCAToolStripMenuItem->Text = L"CCA";
		   // 
		   // hosheToolStripMenuItem
		   // 
		   this->hosheToolStripMenuItem->Name = L"hosheToolStripMenuItem";
		   this->hosheToolStripMenuItem->Size = System::Drawing::Size(216, 26);
		   this->hosheToolStripMenuItem->Text = L"Hoshen-Kopelman";
		   this->hosheToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::hosheToolStripMenuItem_Click);
		   // 
		   // pictureBox1
		   // 
		   this->pictureBox1->Location = System::Drawing::Point(12, 45);
		   this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
		   this->pictureBox1->Name = L"pictureBox1";
		   this->pictureBox1->Size = System::Drawing::Size(800, 552);
		   this->pictureBox1->TabIndex = 1;
		   this->pictureBox1->TabStop = false;
		   // 
		   // openFileDialog1
		   // 
		   this->openFileDialog1->FileName = L"openFileDialog1";
		   // 
		   // chart1
		   // 
		   chartArea4->Name = L"ChartArea1";
		   this->chart1->ChartAreas->Add(chartArea4);
		   legend4->Name = L"Legend1";
		   this->chart1->Legends->Add(legend4);
		   this->chart1->Location = System::Drawing::Point(838, 45);
		   this->chart1->Name = L"chart1";
		   series4->ChartArea = L"ChartArea1";
		   series4->Legend = L"Legend1";
		   series4->Name = L"Histogram";
		   this->chart1->Series->Add(series4);
		   this->chart1->Size = System::Drawing::Size(522, 347);
		   this->chart1->TabIndex = 2;
		   this->chart1->Text = L"chart1";
		   this->chart1->Visible = false;
		   // 
		   // edgeDetectionToolStripMenuItem
		   // 
		   this->edgeDetectionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
			   this->sobelToolStripMenuItem,
				   this->prewittToolStripMenuItem, this->cannyToolStripMenuItem
		   });
		   this->edgeDetectionToolStripMenuItem->Name = L"edgeDetectionToolStripMenuItem";
		   this->edgeDetectionToolStripMenuItem->Size = System::Drawing::Size(126, 24);
		   this->edgeDetectionToolStripMenuItem->Text = L"Edge Detection";
		   // 
		   // sobelToolStripMenuItem
		   // 
		   this->sobelToolStripMenuItem->Name = L"sobelToolStripMenuItem";
		   this->sobelToolStripMenuItem->Size = System::Drawing::Size(224, 26);
		   this->sobelToolStripMenuItem->Text = L"Sobel ";
		   this->sobelToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::sobelToolStripMenuItem_Click);
		   // 
		   // prewittToolStripMenuItem
		   // 
		   this->prewittToolStripMenuItem->Name = L"prewittToolStripMenuItem";
		   this->prewittToolStripMenuItem->Size = System::Drawing::Size(224, 26);
		   this->prewittToolStripMenuItem->Text = L"Prewitt";
		   this->prewittToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::prewittToolStripMenuItem_Click);
		   // 
		   // cannyToolStripMenuItem
		   // 
		   this->cannyToolStripMenuItem->Name = L"cannyToolStripMenuItem";
		   this->cannyToolStripMenuItem->Size = System::Drawing::Size(224, 26);
		   this->cannyToolStripMenuItem->Text = L"Canny";
		   this->cannyToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::cannyToolStripMenuItem_Click);
		   // 
		   // MyForm
		   // 
		   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
		   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		   this->ClientSize = System::Drawing::Size(1360, 617);
		   this->Controls->Add(this->chart1);
		   this->Controls->Add(this->pictureBox1);
		   this->Controls->Add(this->menuStrip1);
		   this->MainMenuStrip = this->menuStrip1;
		   this->Name = L"MyForm";
		   this->Text = L"MyForm";
		   this->menuStrip1->ResumeLayout(false);
		   this->menuStrip1->PerformLayout();
		   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
		   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->EndInit();
		   this->ResumeLayout(false);
		   this->PerformLayout();

	   }
#pragma endregion

private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {//file->open ile görüntü seçilir.

	CString str;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//pictureBox1->ImageLocation = openFileDialog1->FileName;
		str = openFileDialog1->FileName; // açýlmak istenen resmin dosya yolunu string olarak aldýk.
		CStringA s2(str);// CStingA sýnýfýndan s2 nesnesi ürettik ve str'yi(aldýðýmýz path) buraya kopyaladýk.
		const char* input = s2;// s2'yi input deðiþkenine atadýk.
		image im = loadImage(input);/*kendi yazdýðýmýz load_image fonk bu path'i yolladýk.böylece resmi almýþ olduk.gelen
	   resim image.h klasörnde tanýmladýðýmýz struct tipindedir.*/

	   // global deðikenlere shallow copy
		RGBImg_data = im.data;
		RGBImg_w = im.w;
		RGBImg_h = im.h;
		RGBImg_c = im.c;

		ShowRGBImage(im);// rgb resim picturebox'ta gösterilir.

		// cmd ekranýnda resim ile ilgili yükseklik,geniþlik,color,data bilgisi gösterilir.
		std::cout << "h: " << im.h << std::endl;
		std::cout << "w: " << im.w << std::endl;
		std::cout << "c: " << im.c << std::endl;
		std::cout << "data " << (int)im.data[10] << std::endl;//bir noktadaki deðeri gösteirlir.
	}//
}

private: System::Void convertGrayScaleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	//RGB ---> intensity

	if (RGBImg_data == NULL) {

		MessageBox::Show("Gri seviye dönüþüm için önce RGB görüntü dosyasý seçilmelidir.");
	}
	else {

		image im;
		im.w = RGBImg_w;
		im.h = RGBImg_h;
		im.c = RGBImg_c;
		im.data = RGBImg_data;

		image im2 = convertGrayScale(im);
		ShowGrayScaleImage(im2);
		hist = createHistogram(im2);

		//binary dönüþümü için gri seviye görüntü deðerlerini global deðiþkenlere atadýk
		grayImg_data = im2.data;
		grayImg_w = im2.w;
		grayImg_h = im2.h;
		grayImg_c = im2.c;
		//burada itibaren k-means clustering ile resmi binary ye çevirmemiz gerekecek.
		//raw_Data = im2.data;

		chart1->Visible = true;// ilk baþta chart görünmez histgorama týklayýnca görünür hale gelsin
		chart1->Series["Histogram"]->Points->Clear();// chart ilk baþta sýfýrlansýn
		//chart1->Series["KMeans"]->Points->Clear();

		chart1->Location = System::Drawing::Point(pictureBox1->Width + 20, 34);//histogra konumu

		for (int i = 0; i < 256; i++) {
			chart1->Series["Histogram"]->Points->AddXY(i, hist[i]);
		}
	}



}


private: System::Void kMeansClusteringToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (grayImg_data == NULL) {

		MessageBox::Show("Gri Seviye görüntü olmadan binary seviyeye dönüþüm yapýlamaz");
	}
	else {

		image im;
		im.w = grayImg_w;
		im.h = grayImg_h;
		im.c = grayImg_c;
		im.data = grayImg_data;

		//image im2 = OtsuThresholding(im, hist);
		int k = 2;
		float* kmeans = KMeans_Eucliden(im, k);
		image im2 = KBasedSegmentation(im, kmeans, k);

		ShowBinaryImage(im2);
		binaryImg_data = im2.data;
		binaryImg_w = im2.w;
		binaryImg_h = im2.h;
		binaryImg_c = im2.c;  
	
	}
}
private: System::Void otsuThresholdingToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (grayImg_data == NULL) {

		MessageBox::Show("Gri Seviye görüntü olmadan binary seviyeye dönüþüm yapýlamaz");
	}
	else {

		image im;
		im.w = grayImg_w;
		im.h = grayImg_h;
		im.c = grayImg_c;
		im.data = grayImg_data;

		image im2 = OtsuThresholding(im, hist);


		ShowBinaryImage(im2);

		binaryImg_data = im2.data;
		binaryImg_w = im2.w;
		binaryImg_h = im2.h;
		binaryImg_c = im2.c;

		//chart1->Visible = true;// ilk baþta chart görünmez histgorama týklayýnca görünür hale gelsin
		//chart1->Series["Histogram"]->Points->Clear();// chart ilk baþta sýfýrlansýn
		////chart1->Series["KMeans"]->Points->Clear();

		//chart1->Location = System::Drawing::Point(pictureBox1->Width + 20, 34);

		//for (int i = 0; i < 256; i++) {
		//	chart1->Series["Histogram"]->Points->AddXY(i, hist[i]);
		//}
	}
}
private: System::Void dilationToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (binaryImg_data == NULL) {

		MessageBox::Show("Morfolojik iþlemler binary görüntü üzerinde yapýlýr.Önce binary görüntü elde edin!");
	}
	else {

		if (morphImg_data == NULL) {//ilk kez morfolojik iþlem yapýlýyorsa

			image im;
			im.w = binaryImg_w;
			im.h = binaryImg_h;
			im.c = binaryImg_c;
			im.data = binaryImg_data;

			image im2 = Dilation(im);

			ShowBinaryImage(im2);

			morphImg_data = im2.data;
			morphImg_w = im2.w;
			morphImg_h = im2.h;
			morphImg_c = im2.c;



		}
		else {//morfolojik iþlemin üzerine bir daha morfolojik iþlem yapýlacaksa

			image im;
			im.w = morphImg_w;
			im.h = morphImg_h;
			im.c = morphImg_c;
			im.data = morphImg_data;

			image im2 = Dilation(im);

			ShowBinaryImage(im2);

			morphImg_data = im2.data;
			morphImg_w = im2.w;
			morphImg_h = im2.h;
			morphImg_c = im2.c;


		}


	}
}
private: System::Void erosionToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (binaryImg_data == NULL) {

		MessageBox::Show("Morfolojik iþlemler binary görüntü üzerinde yapýlýr.Önce binary görüntü elde edin!");
	}
	else {

		if (morphImg_data == NULL) {//ilk kez morfolojik iþlem yapýlýyorsa

			image im;
			im.w = binaryImg_w;
			im.h = binaryImg_h;
			im.c = binaryImg_c;
			im.data = binaryImg_data;

			image im2 = Erosion(im);

			ShowBinaryImage(im2);

			morphImg_data = im2.data;
			morphImg_w = im2.w;
			morphImg_h = im2.h;
			morphImg_c = im2.c;



		}
		else {//morfolojik iþlemin üzerine bir daha morfolojik iþlem yapýlacaksa

			image im;
			im.w = morphImg_w;
			im.h = morphImg_h;
			im.c = morphImg_c;
			im.data = morphImg_data;

			image im2 = Erosion(im);

			ShowBinaryImage(im2);

			morphImg_data = im2.data;
			morphImg_w = im2.w;
			morphImg_h = im2.h;
			morphImg_c = im2.c;


		}


	}
}
private: System::Void hosheToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {





}

private: System::Void sobelToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (grayImg_data == NULL) {

		MessageBox::Show("Gri Seviye görüntü olmadan sobel edge detection yapýlamaz");
	}
	else {

		image im;
		im.w = grayImg_w;
		im.h = grayImg_h;
		im.c = grayImg_c;
		im.data = grayImg_data;

		image im2 = sobelFilter(im);


		ShowBinaryImage(im2);

	}

}
private: System::Void prewittToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	if (grayImg_data == NULL) {

		MessageBox::Show("Gri Seviye görüntü olmadan prewitt edge detection yapýlamaz");
	}
	else {

		image im;
		im.w = grayImg_w;
		im.h = grayImg_h;
		im.c = grayImg_c;
		im.data = grayImg_data;

		image im2 = prewittFilter(im);


		ShowBinaryImage(im2);

	}

}
private: System::Void cannyToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	

}
};