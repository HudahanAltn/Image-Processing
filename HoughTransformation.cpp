#include "image.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "SinglyLinkedList.h"
using namespace std;

int triEquation(int x, int y, double theta) { // ger�ek uzayda her bir kenar oolabilecek pixel i�in xiy koord. kullanarak p ve Q de�. �ret
     
    const double PI = 3.14;
    double  radian;
    int result;

    radian = theta * PI / 180;

    result = x * cos(radian) + y * sin(radian);

    return result;
}


bool drawLine(int p, double t, int x, int y) { // hough uzay�nda bulunan en y�ksek saya� de�.sahip p ve Q nok i�in ger�ek uzayda x,y

    const double PI = 3.14159265;
    double radian = t * PI / 180;
    int result = x * cos(radian) + y * sin(radian);

    if (p == result) {
        return true;
    }
    else {
        return false;
    }
}

image findLine(image cannyImg, image orjImg) {

    int thetaMax = 90; //houghy uzay� a�� s�n�r�
    int temp = cannyImg.h * cannyImg.h + cannyImg.w * cannyImg.w;
    int pMax = sqrt(temp);//hough uzay� p s�n�r�

    int* houghSpace = new  int[thetaMax * pMax];//hough uzay�n� temsili 2d dizi. sat�r= pmax sutun = theta



    for (int i = 0; i < pMax; i++) {//ba�lang��ta houghSpace dizisinin her bir eleman�n� s�f�rlar�z�
        for (int j = 0; j < thetaMax; j++) {

            houghSpace[i * thetaMax + j] = 0;
        }

    }



    //binary edge image in her bir pixelini tek tek al.  im.h = p , im.w = theta
    for (int i = 1; i < cannyImg.h - 1; i++) {
        for (int j = 1; j < cannyImg.w - 1; j++) {

            if (cannyImg.data[i * cannyImg.w + j] == 255) {//pixel de�eri 1 olanlar kenar pixelleridir.

                for (int t = 0; t < thetaMax; t++) {//x.cost +r.sint = p denk den bilininen her x,y noktas� i�in (p,r) nokt bul.

                    int p = triEquation(j, i, t);//p noktas� bul.

                    houghSpace[p * thetaMax + t]++; //hough uzay�nda (t,p) nok kar��l�k gelen pix de�erini 1 artt�r.
                }

            }

        }
    }


    //9 adet line bulmak istiyoruz.Bunun i�in en y�ksek saya� de�erli hough noktas� bize laz�m.Bu noktan�nx-y bile�eninin �iftler halinde tutar�z.

  
    int maxLines = 10; // 9 tane �izgi bulmak istiyoruz.
    int lineCounter = 0;//�izgi say�s�n� tutmas� i�in counter tan�mlad�k.
    SinglyLinkedList List;//hough uzay�ndaki 10 adet en y�ksek saya� de�erine sahip de�erleri tutmas� i�in SLL tan�mlad�k.


    //houghUzay�nda dola��yoruz.
    for (int i = 0; i < pMax; i++) {
        for (int j = 0; j < thetaMax; j++) {

            if (i == 0 && j == 0) { // ilk noktay al.Ve listenin ilk eleman� yap

                List.head = new SinglyNode;
                List.head->x = i;
                List.head->y = j;
                List.head->counterSize = houghSpace[i * thetaMax + j];
                List.head->next = NULL;
            }
            else {// ilk noktadan sonra geri kalan noktalar incelenecek.

                if (lineCounter < maxLines) {//9 tane �izgi bulaca��z. 

                    if (houghSpace[i * thetaMax + j] > List.head->counterSize) {/*hough'da gelen yeni noktan�n saya� de�eri listenin head'inin saya�
                        de�eriden y�ksek ise(head Listenin en y�ksek saya� de�erine sahip pixel'i g�sterir)*/

                        List.addFront(i, j, houghSpace[i * thetaMax + j]);// yeni pixeli ekle
                        lineCounter++;// lineCounter'� 1 artt�r.
                    }

                }
                else {//t�m noktalar dolsa bile hen�z reel max de�erlere ula�mam�� olabiliriz.

                    if (houghSpace[i * thetaMax + j] > List.head->counterSize) {/*hough'da gelen yeni noktan�n saya� de�eri listenin head'inin saya�
                        de�eriden y�ksek ise(head Listenin en y�ksek saya� de�erine sahip pixel'i g�sterir)*/

                        List.removeBack();//bu sefer listenin en sonundaki de�eri kald�r(bu en k���k saya� de�erli pixel'i g�sterir.
                        List.addFront(i, j, houghSpace[i * thetaMax + j]);// yeni geleni liste ba��na ekle.
                    }
                    
                    
                }
                
                
                

            }
            
        }
    }

    delete houghSpace;
   //List'te art�k hough uzay�nda en y�ksek saya� de�erli 9 pixel konumu bulunmaktad�r.
    SinglyNode* current = List.head;// List'te gezinmek i�in pointer tan�ml�yoruz.

    image finalImage;//Final image kenaralar� tespit edilmi� orj RGB image olacak.
    finalImage.h = orjImg.h;
    finalImage.w = orjImg.w;
    finalImage.c = 3;
    finalImage.data = new unsigned char[orjImg.w * orjImg.h * 3];

    while (current->next != NULL) {//listenin her bir eleman� al�yoruz ve g�r�nt� �zerinde dola��yoruz.
        for (int i = 1; i < orjImg.h - 1; i++) {
            for (int j = 1; j < orjImg.w - 1; j++) {

                if (drawLine(current->x, current->y, j, i)) {//true ise iligili pixeli ye�ile setliyoruz.

                    finalImage.data[i * finalImage.w * 3 + j * 3] = 0;
                    finalImage.data[i * finalImage.w * 3 + j * 3 + 1] = 255;
                    finalImage.data[i * finalImage.w * 3 + j * 3 + 2] = 0;
                }
                else {

                    if (finalImage.data[i * finalImage.w * 3 + j * 3 + 1] != 255) {
                        /*bunun amac� ise List'teki di�er konumlar� test ederken bir �ncekiler ile �ak��mamas� i�in bu if'i yazd�k.*/

                        finalImage.data[i * finalImage.w * 3 + j * 3] = orjImg.data[i * orjImg.w * 3 + j * 3];
                        finalImage.data[i * finalImage.w * 3 + j * 3 + 1] = orjImg.data[i * orjImg.w * 3 + j * 3 + 1];
                        finalImage.data[i * finalImage.w * 3 + j * 3 + 2] = orjImg.data[i * orjImg.w * 3 + j * 3 + 2];
                    }
                    
                }

            }
        }

        current = current->next;//g�r�nt� loop'u bitince Listenin bir sonraki eleman�na ge�i� yap�yoruz.
    }

    return finalImage;
}



