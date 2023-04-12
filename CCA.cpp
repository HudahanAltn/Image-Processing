#include "image.h"
#include <vector>

using namespace std;

bool isValidCoordinate(int x, int y, image im) {/*pixeller bazen matirisin köþelerinde veya sýnýrlarýnda olabiliyor.i
                                                bu yüzden koordinat kontrolü yapýlmasý gerekir*/
    //komþuluk koordinatlarý için hesaplanan satýr ve sutun deðerleri negatif olamamalý ve ayrýca matirisnin satýr vve sutun boyutunu geçmemeli.
    return x >= 0 && x < im.w && y >= 0 && y < im.h;
}

bool isAllFourNeighborPixelsZero(const vector<int>& vec) {/*bu fonksiyon tüm 4 komþu pixel 0 ise true döndürür
                                             böylece yeni bir nesne pixelinde olduðumuzu anlarýz.*/

    if (vec[0] == 0 && vec[1] == 0 && vec[2] == 0 && vec[3] == 0) {
        return true;
    }
    else {
        return false;
    }
}

bool isAllFourNeighborPixelsSame(const vector<int>& vec) {/*bu fonksiyon tüm 4 komþu pixel labellarý ayný  ise true döndürür
                                             böylece ayný nesne pixelinde olduðumuzu anlarýz.*/

    if (vec[0] == vec[1] == vec[2] == vec[3]) {
        return true;
    }
    else {
        return false;
    }
}

bool allVectorElementsSame(const vector<int>& vec) {//komþu pixellerin tüm elemanlarý eþitse
    if (vec.empty()) { // Eðer vector boþ ise true dön
        return true;
    }

    int firstElement = vec[0]; // Vectorün ilk elemanýný al

    // Vectorün diðer elemanlarýný kontrol et, eðer farklý bir eleman bulunursa false dön
    for (int i = 1; i < vec.size(); i++) {
        if (vec[i] != firstElement) {
            return false;
        }
    }

    // Eðer tüm elemanlar ayný ise true dön
    return true;
}

vector<int> removeZeros(const vector<int>& vec) {//komþu pixellerin eleman eþitliðinin tespti için backgorund label alanlarý kaldýr.

    vector<int> newArr;

    for (int i = 0; i < 4; i++) {

        if (vec[i] != 0) {

            newArr.push_back(vec[i]);
        }
    }

    return newArr;
}


image hoshenKopelman(image im) {

    int OBJECT_LABEL = 1;//nesne sayý takibi için etiketlemeyi 1 den baþlatacaðýz.
    int OCCLUSION = -1;
    image tempImage;
    tempImage.h = im.h;
    tempImage.w = im.w;
    tempImage.c = im.c;
    tempImage.data = new unsigned char[im.w*im.h];/*bu geçici image ekranda fln gösterilmeyecek.sadece labellarý geçici tutacak.*/
		
    

    for (int row = 0; row < im.h; row++) {
        for (int column = 0; column < im.w; column++) {

            vector<int> fourNeighborPixel;/*baþtan sýrayla kuzeybatý,kuzey,kuzeydoðu ve batý pixellerini tutacak olan geçici vector dizisi
                                                   yarattýk.her yeni pixele etiket vereceðimiz zaman bu dizi tekrar yaratýlacak.*/

            int ZERO_LABEL = 0;//background pixel etiketi.background pixellerimiz 255 olduðu için bu deðere sahip olanlar 0 etiketini alacak.

            tempImage.data[row * im.w + column] = ZERO_LABEL;//baþta her pixele 0 etiketi veriyoruz.

            
            if (im.data[row * im.w + column] == 0) {/* gelen yeni pixel siyah ise bu bir nesnedir deriz.þimdi ise komþu pixellerine bakýp
                                                    etiket verme iþlemine geçeceðiz.*/
                
                
                int counter = 0;//bu sayaç mevcut komþu pixelleri vectore eklememizi saðlayacak.
                /*etiketlenecek pixelden önceki 4 komþuyu incelemek için for döngüsü yazdýk*/
                for (int neighborRow = -1 ; neighborRow < 0; neighborRow++) {
                    for (int neighborCol = -1; neighborCol < 1; neighborCol++) {

                        if (neighborRow == 0 && neighborCol == 0) {//bu deðerler etiketlenecek pix ifade ettiði için döngüden çýkmak gerekir.
                            break;//zaten bu ifade gelince döngüden çýakcaðý için east komþuyu kontrol etmeye gerek yok.
                        }

                        //4 komþu pixel konumlarý hesaplanýr
                        int nRow = row + neighborRow;
                        int nCol = column + neighborCol;
                        
                        /*mümkün komþuluk pixel konumlarý bulundu.(etiketleme yapýlacak pixel ilk ve 
                        son sutunda ,ilk ve son satýrda olursa hesaplanan nRow ve nCol deð degatif çýkar bunlarda matriste bir yeri ifade
                        etmez o yüzden bu deðerler gelince eleme olmasý gerekir.)*/
                        if (isValidCoordinate(nRow, nCol, im)){

                            fourNeighborPixel[counter] = tempImage.data[nRow * im.w + nCol];
                           

                        }
                        counter++;
                    }
                }//buradan itibaren komþu pixellerin label deðerleri elimizde þimdi yeni pixeli etiketleme yapacaðýz.

                if (isAllFourNeighborPixelsZero(fourNeighborPixel)) {//tüm komuþular 0 ise bu yeni bir nesne belirtir etiketle

                    tempImage.data[row * im.w + column] = OBJECT_LABEL + 1;// etiketi 1 artýracaðýz böylece yeni nesne etiketini elde ederiz.
                }
                else if (isAllFourNeighborPixelsSame(fourNeighborPixel)) {// tüm komuþlar ayný etikete sahipse yeni pixelde ayný nesye ait

                    tempImage.data[row * im.w + column] = OBJECT_LABEL;

                }
                else {//diðer durumlar . 1- occlusion durumu 2- 4 pixelden bir kýsmý arkaplana diðerleir ayný nesneye ait etiketler

                    vector<int> otherSituations = removeZeros(fourNeighborPixel);//bu yeni vectorde sýfýrlar yok

                    /*bu aþamadan sonra iki durum 
                    1-geri kalan elemanlar hepsi ayný ise  yeni pixel  komþular ile ayný nesneye ait
                    2- geri kalan elemanlardan en az ikisi birb farklý ise occlusion durumu var*/

                    if (allVectorElementsSame(otherSituations)) {//ayný ensne

                        tempImage.data[row * im.w + column] = OBJECT_LABEL;
                    }
                    else {//oclusion

                        tempImage.data[row * im.w + column] = OCCLUSION;
                    }
                }
                


            }
            else {//yeni pixel nesne deðil arka plandýr o yüzden etiketi 0 olacak.sanýrým buraya gerek yok


            }
        }

    }//etiketleme bitti þimdi sýrada occlusion etiketlerini normal etikete çevirme var. occlusion etiketi -1 ile temsil edildi.

    for (int row = 0; row < tempImage.h; row++) {
        for (int column = 0; column < tempImage.w; column++) {

            if (tempImage.data[row * tempImage.w + column] == OCCLUSION) {//occlusion etiketine sahp pixeller için 


            }
        }
    }//burdan sonra bounding boxa alma iþlemi gerçekleþtirilecek.
    

}

/*8 komþuluk matris elemanlarýný dolaþýr ve 1 de kendisi üzerinden geçer. toplam 9 döngü. bu 9 pixelden 4 tanesini yani
 þu anki pixelimizden önce gelen komþularý incelemek gerekir.geri kalan 5 pixelin etiketi yok  çünkü onlara daha sýra
 gelmemiþtir.Komþuluk incelemesi yaparken etiketi olanlara bakýp karar vereceðiz.BU KISIM OCCLUSÝON AÇIKLAMASI*/
