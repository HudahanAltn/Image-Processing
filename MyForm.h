#pragma once
#include <atlstr.h>
#include <iostream>
#include "Image.h";
#include "Processing.h";

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

/// <summary>
/// MyForm i�in �zet
/// </summary>
public ref class MyForm : public System::Windows::Forms::Form{

public:
	MyForm(void)
	{
		InitializeComponent();
		//
		//TODO: Olu�turucu kodunu buraya ekle
		//
	}

protected:
	/// <summary>
	///Kullan�lan t�m kaynaklar� temizleyin.
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
	///Gerekli tasar�mc� de�i�keni.
	/// </summary>

	unsigned char* img_data = NULL; // al�nan g�r�nt�n�n de�erleininin t�m class baz�nda kullan�lmas� i�in yarat�lan veri �yeleri.s�n�f i�inde globalle�tirdik.
	int img_w, img_h, img_c;

	unsigned char* img_data2 = NULL; // al�nan g�r�nt�n�n de�erleininin t�m class baz�nda kullan�lmas� i�in yarat�lan veri �yeleri.s�n�f i�inde globalle�tirdik.
	int img_w2, img_h2, img_c2;
private: System::Windows::Forms::ToolStripMenuItem^ convertBinaryToolStripMenuItem;



	System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
	/// <summary>
	/// Tasar�mc� deste�i i�in gerekli metot - bu metodun 
	///i�eri�ini kod d�zenleyici ile de�i�tirmeyin.
	/// </summary>
	/// 
	void ShowGrayScale(image im) {//Pictureboxta rgb g�r�nt� g�sterilir.

		//picture box y�kseklik/geni�lik setlemesi
		pictureBox1->Width = im.w;
		pictureBox1->Height = im.h;
		pictureBox1->Refresh();

		Bitmap^ surface = gcnew Bitmap(im.w, im.h);/*ald���m�z resim jpg veya png uzant�l� ama biz pictureboxta bitmap olarak g�sterece�iz.
												   bu y�zden al�nan resmin y�kseklik ve geni�lik de�erlerinden bo� bir bitmap resmi olu�turduk.*/
		pictureBox1->Image = surface;//picture box a att�k.

		// imageRGb[w][h][c] == imageRDB1Dimension[w*h*c]
		Color c;//k
		int psw, bufpos;
		psw = im.w * im.c;

		for (int row = 0; row < im.h; row++)
			for (int col = 0; col < im.w; col++) {
				bufpos = row * psw + col * im.c;
				c = Color::FromArgb(im.data[bufpos], im.data[bufpos + 1], im.data[bufpos + 2]);
				surface->SetPixel(col, row, c);
				std::cout << c.A  << std::endl;
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
		psw = im.w * im.c; //rgb nesneler i�in weight*3;
		//for d�ng�s� ile h*w*3 imagenin her bir pixel de�erini al�r�z.
		for (int row = 0; row < im.h; row++)
			for (int col = 0; col < im.w; col++) {
				bufpos = row * psw + col * im.c;
				c = Color::FromArgb(im.data[bufpos], im.data[bufpos + 1], im.data[bufpos + 2]);
				surface->SetPixel(col, row, c);
			}

	}
	void InitializeComponent(void)
	{
		System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
		System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
		System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
		this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
		this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->processingTypeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->convertGrayScaleToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->convertBinaryToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
		this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
		this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
		this->chart1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
		this->menuStrip1->SuspendLayout();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
		(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart1))->BeginInit();
		this->SuspendLayout();
		// 
		// menuStrip1
		// 
		this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
		this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
			this->fileToolStripMenuItem,
				this->processingTypeToolStripMenuItem
		});
		this->menuStrip1->Location = System::Drawing::Point(0, 0);
		this->menuStrip1->Name = L"menuStrip1";
		this->menuStrip1->Size = System::Drawing::Size(1217, 30);
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
		this->openToolStripMenuItem->Size = System::Drawing::Size(128, 26);
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
		this->convertBinaryToolStripMenuItem->Name = L"convertBinaryToolStripMenuItem";
		this->convertBinaryToolStripMenuItem->Size = System::Drawing::Size(216, 26);
		this->convertBinaryToolStripMenuItem->Text = L"Convert Binary";
		this->convertBinaryToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::convertBinaryToolStripMenuItem_Click);
		// 
		// pictureBox1
		// 
		this->pictureBox1->Location = System::Drawing::Point(12, 45);
		this->pictureBox1->Name = L"pictureBox1";
		this->pictureBox1->Size = System::Drawing::Size(682, 496);
		this->pictureBox1->TabIndex = 1;
		this->pictureBox1->TabStop = false;
		// 
		// openFileDialog1
		// 
		this->openFileDialog1->FileName = L"openFileDialog1";
		// 
		// chart1
		// 
		chartArea3->Name = L"ChartArea1";
		this->chart1->ChartAreas->Add(chartArea3);
		legend3->Name = L"Legend1";
		this->chart1->Legends->Add(legend3);
		this->chart1->Location = System::Drawing::Point(756, 45);
		this->chart1->Name = L"chart1";
		series3->ChartArea = L"ChartArea1";
		series3->Legend = L"Legend1";
		series3->Name = L"Histogram";
		this->chart1->Series->Add(series3);
		this->chart1->Size = System::Drawing::Size(1000, 348);
		this->chart1->TabIndex = 2;
		this->chart1->Text = L"chart1";
		this->chart1->Visible = false;
		// 
		// MyForm
		// 
		this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
		this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
		this->ClientSize = System::Drawing::Size(1217, 617);
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

private: System::Void openToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {//file->open ile g�r�nt� se�ilir.

	CString str;

	if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
		//pictureBox1->ImageLocation = openFileDialog1->FileName;
		str = openFileDialog1->FileName; // a��lmak istenen resmin dosya yolunu string olarak ald�k.
		CStringA s2(str);// CStingA s�n�f�ndan s2 nesnesi �rettik ve str'yi(ald���m�z path) buraya kopyalad�k.
		const char* input = s2;// s2'yi input de�i�kenine atad�k.
		image im = loadImage(input);/*kendi yazd���m�z load_image fonk bu path'i yollad�k.b�ylece resmi alm�� olduk.gelen
	   resim image.h klas�rnde tan�mlad���m�z struct tipindedir.*/

	   // global de�ikenlere shallow copy
		img_data = im.data;
		img_w = im.w;
		img_h = im.h;
		img_c = im.c;

		ShowRGBImage(im);// rgb resim picturebox'ta g�sterilir.

		// cmd ekran�nda resim ile ilgili y�kseklik,geni�lik,color,data bilgisi g�sterilir.
		std::cout << "h: " << im.h << std::endl;
		std::cout << "w: " << im.w << std::endl;
		std::cout << "c: " << im.c << std::endl;
		std::cout << "data " << (int)im.data[10] << std::endl;//bir noktadaki de�eri g�steirlir.
	}//
}
private: System::Void convertGrayScaleToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

	//RGB ---> intensity

	if (img_data == NULL) {

		MessageBox::Show("Okunacak g�r�nt� dosyas� �nceden se�ilmelidir.");
	}
	else {

		image im;
		im.w = img_w;
		im.h = img_h;
		im.c = img_c;
		im.data = img_data;

		image im2 = convertGrayScale(im);
		ShowGrayScale(im2);
		int* hist = createHistogram(im2);

		//binary d�n���m� i�in gri seviye g�r�nt� de�erlerini global de�i�kenlere atad�k
		img_data2 = im2.data;
		img_w2 = im2.w;
		img_h2 = im2.h;
		img_c2 = im2 .c;
		//burada itibaren k-means clustering ile resmi binary ye �evirmemiz gerekecek.
		//raw_Data = im2.data;

		chart1->Visible = true;// ilk ba�ta chart g�r�nmez histgorama t�klay�nca g�r�n�r hale gelsin
		chart1->Series["Histogram"]->Points->Clear();// chart ilk ba�ta s�f�rlans�n
		//chart1->Series["KMeans"]->Points->Clear();

		chart1->Location = System::Drawing::Point(pictureBox1->Width + 20, 34);//histogra konumu

		for (int i = 0; i < 256; i++) {
			chart1->Series["Histogram"]->Points->AddXY(i, hist[i]);
		}
	}



}
private: System::Void convertBinaryToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {


	if (img_data2 == NULL) {

		MessageBox::Show("Okunacak g�r�nt� dosyas� �nceden se�ilmelidir.");
	}
	else {

		image im;
		im.w = img_w2;
		im.h = img_h2;
		im.c = img_c2;
		im.data = img_data2;

		image im2 = convertGrayScale(im);
		ShowGrayScale(im2);
		int* hist = createHistogram(im2);

		//raw_Data = im2.data;

		chart1->Visible = true;// ilk ba�ta chart g�r�nmez histgorama t�klay�nca g�r�n�r hale gelsin
		chart1->Series["Histogram"]->Points->Clear();// chart ilk ba�ta s�f�rlans�n
		//chart1->Series["KMeans"]->Points->Clear();

		chart1->Location = System::Drawing::Point(pictureBox1->Width + 20, 34);

		for (int i = 0; i < 256; i++) {
			chart1->Series["Histogram"]->Points->AddXY(i, hist[i]);
		}
	}


}

};