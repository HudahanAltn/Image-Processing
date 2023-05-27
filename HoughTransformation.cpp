#include "image.h"
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "SinglyLinkedList.h"
using namespace std;

int triEquation(int x, int y, double theta) { // gerçek uzayda her bir kenar oolabilecek pixel için xiy koord. kullanarak p ve Q deð. üret
     
    const double PI = 3.14;
    double  radian;
    int result;

    radian = theta * PI / 180;

    result = x * cos(radian) + y * sin(radian);

    return result;
}


bool drawLine(int p, double t, int x, int y) { // hough uzayýnda bulunan en yüksek sayaç deð.sahip p ve Q nok için gerçek uzayda x,y

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

    int thetaMax = 90; //houghy uzayý açý sýnýrý
    int temp = cannyImg.h * cannyImg.h + cannyImg.w * cannyImg.w;
    int pMax = sqrt(temp);//hough uzayý p sýnýrý

    int* houghSpace = new  int[thetaMax * pMax];//hough uzayýný temsili 2d dizi. satýr= pmax sutun = theta



    for (int i = 0; i < pMax; i++) {//baþlangýçta houghSpace dizisinin her bir elemanýný sýfýrlarýzç
        for (int j = 0; j < thetaMax; j++) {

            houghSpace[i * thetaMax + j] = 0;
        }

    }



    //binary edge image in her bir pixelini tek tek al.  im.h = p , im.w = theta
    for (int i = 1; i < cannyImg.h - 1; i++) {
        for (int j = 1; j < cannyImg.w - 1; j++) {

            if (cannyImg.data[i * cannyImg.w + j] == 255) {//pixel deðeri 1 olanlar kenar pixelleridir.

                for (int t = 0; t < thetaMax; t++) {//x.cost +r.sint = p denk den bilininen her x,y noktasý için (p,r) nokt bul.

                    int p = triEquation(j, i, t);//p noktasý bul.

                    houghSpace[p * thetaMax + t]++; //hough uzayýnda (t,p) nok karþýlýk gelen pix deðerini 1 arttýr.
                }

            }

        }
    }


    //9 adet line bulmak istiyoruz.Bunun için en yüksek sayaç deðerli hough noktasý bize lazým.Bu noktanýnx-y bileþeninin çiftler halinde tutarýz.

  
    int maxLines = 10; // 9 tane çizgi bulmak istiyoruz.
    int lineCounter = 0;//çizgi sayýsýný tutmasý için counter tanýmladýk.
    SinglyLinkedList List;//hough uzayýndaki 10 adet en yüksek sayaç deðerine sahip deðerleri tutmasý için SLL tanýmladýk.


    //houghUzayýnda dolaþýyoruz.
    for (int i = 0; i < pMax; i++) {
        for (int j = 0; j < thetaMax; j++) {

            if (i == 0 && j == 0) { // ilk noktay al.Ve listenin ilk elemaný yap

                List.head = new SinglyNode;
                List.head->x = i;
                List.head->y = j;
                List.head->counterSize = houghSpace[i * thetaMax + j];
                List.head->next = NULL;
            }
            else {// ilk noktadan sonra geri kalan noktalar incelenecek.

                if (lineCounter < maxLines) {//9 tane çizgi bulacaðýz. 

                    if (houghSpace[i * thetaMax + j] > List.head->counterSize) {/*hough'da gelen yeni noktanýn sayaç deðeri listenin head'inin sayaç
                        deðeriden yüksek ise(head Listenin en yüksek sayaç deðerine sahip pixel'i gösterir)*/

                        List.addFront(i, j, houghSpace[i * thetaMax + j]);// yeni pixeli ekle
                        lineCounter++;// lineCounter'ý 1 arttýr.
                    }

                }
                else {//tüm noktalar dolsa bile henüz reel max deðerlere ulaþmamýþ olabiliriz.

                    if (houghSpace[i * thetaMax + j] > List.head->counterSize) {/*hough'da gelen yeni noktanýn sayaç deðeri listenin head'inin sayaç
                        deðeriden yüksek ise(head Listenin en yüksek sayaç deðerine sahip pixel'i gösterir)*/

                        List.removeBack();//bu sefer listenin en sonundaki deðeri kaldýr(bu en küçük sayaç deðerli pixel'i gösterir.
                        List.addFront(i, j, houghSpace[i * thetaMax + j]);// yeni geleni liste baþýna ekle.
                    }
                    
                    
                }
                
                
                

            }
            
        }
    }

    delete houghSpace;
   //List'te artýk hough uzayýnda en yüksek sayaç deðerli 9 pixel konumu bulunmaktadýr.
    SinglyNode* current = List.head;// List'te gezinmek için pointer tanýmlýyoruz.

    image finalImage;//Final image kenaralarý tespit edilmiþ orj RGB image olacak.
    finalImage.h = orjImg.h;
    finalImage.w = orjImg.w;
    finalImage.c = 3;
    finalImage.data = new unsigned char[orjImg.w * orjImg.h * 3];

    while (current->next != NULL) {//listenin her bir elemaný alýyoruz ve görüntü üzerinde dolaþýyoruz.
        for (int i = 1; i < orjImg.h - 1; i++) {
            for (int j = 1; j < orjImg.w - 1; j++) {

                if (drawLine(current->x, current->y, j, i)) {//true ise iligili pixeli yeþile setliyoruz.

                    finalImage.data[i * finalImage.w * 3 + j * 3] = 0;
                    finalImage.data[i * finalImage.w * 3 + j * 3 + 1] = 255;
                    finalImage.data[i * finalImage.w * 3 + j * 3 + 2] = 0;
                }
                else {

                    if (finalImage.data[i * finalImage.w * 3 + j * 3 + 1] != 255) {
                        /*bunun amacý ise List'teki diðer konumlarý test ederken bir öncekiler ile çakýþmamasý için bu if'i yazdýk.*/

                        finalImage.data[i * finalImage.w * 3 + j * 3] = orjImg.data[i * orjImg.w * 3 + j * 3];
                        finalImage.data[i * finalImage.w * 3 + j * 3 + 1] = orjImg.data[i * orjImg.w * 3 + j * 3 + 1];
                        finalImage.data[i * finalImage.w * 3 + j * 3 + 2] = orjImg.data[i * orjImg.w * 3 + j * 3 + 2];
                    }
                    
                }

            }
        }

        current = current->next;//görüntü loop'u bitince Listenin bir sonraki elemanýna geçiþ yapýyoruz.
    }

    return finalImage;
}



