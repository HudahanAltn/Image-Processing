//#include "image.h"
//#include <vector>
//#include <map>
//#include<set>
//using namespace std;
//
//bool isValidCoordinate(int x, int y, image im) {/*pixeller bazen matirisin k��elerinde veya s�n�rlar�nda olabiliyor.i
//                                                bu y�zden koordinat kontrol� yap�lmas� gerekir*/
//    //kom�uluk koordinatlar� i�in hesaplanan sat�r ve sutun de�erleri negatif olamamal� ve ayr�ca matirisnin sat�r vve sutun boyutunu ge�memeli.
//    return x >= 0 && x < im.w && y >= 0 && y < im.h;
//}
//
//bool isAllFourNeighborPixelsZero(const vector<int>& vec) {/*bu fonksiyon t�m 4 kom�u pixel 0 ise true d�nd�r�r
//                                             b�ylece yeni bir nesne pixelinde oldu�umuzu anlar�z.*/
//
//    bool allZeros = true;
//
//    for (int i = 0; i < vec.size(); i++) {
//        if (vec[i] != 0) {
//            allZeros = false;
//            break;
//        }
//    }
//
//    return allZeros;
//}
//
// 
//bool isAllFourNeighborPixelsSame(const vector<int>& vec) {/*bu fonksiyon t�m 4 kom�u pixel labellar� ayn�  ise true d�nd�r�r
//                                             b�ylece ayn� nesne pixelinde oldu�umuzu anlar�z.*/
//
//    bool allSame = true;
//
//    for (int i = 1; i < vec.size(); i++) {
//        if (vec[i] != vec[0]) {
//            allSame = false;
//            break;
//        }
//    }
//
//    return allSame;
//}
//
//bool allVectorElementsSame(const vector<int>& vec) {//kom�u pixellerin t�m elemanlar� e�itse
//
//    if (vec.empty()) { // E�er vector bo� ise true d�n
//        return true;
//    }
//
//    int firstElement = vec[0]; // Vector�n ilk eleman�n� al
//
//    // Vector�n di�er elemanlar�n� kontrol et, e�er farkl� bir eleman bulunursa false d�n
//    for (int i = 1; i < vec.size(); i++) {
//        if (vec[i] != firstElement) {
//            return false;
//        }
//    }
//
//    // E�er t�m elemanlar ayn� ise true d�n
//    return true;
//}
//
//vector<int> removeZeros(const vector<int>& vec) {//kom�u pixellerin eleman e�itli�inin tespti i�in backgorund label alanlar� kald�r.
//
//    vector<int> newArr;
//
//    for (int i = 0; i < 4; i++) {
//
//        if (vec[i] != 0) {
//
//            newArr.push_back(vec[i]);
//        }
//    }
//
//    return newArr;
//}
//
//
//image hoshenKopelman(image im) {
//
// 
//    map<int,int> occlusionMap;
//    int OBJECT_LABEL = 1;//nesne say� takibi i�in etiketlemeyi 1 den ba�lataca��z.
//    int OCCLUSION = -1;
//    image tempImage;
//    tempImage.h = im.h;
//    tempImage.w = im.w;
//    tempImage.c = im.c;
//    tempImage.data = new unsigned char[im.w*im.h];/*bu ge�ici image ekranda fln g�sterilmeyecek.sadece labellar� ge�ici tutacak.*/
//		
//    image occlusionImage;
//    occlusionImage.h = im.h;
//    occlusionImage.w = im.w;
//    occlusionImage.c = im.c;
//    occlusionImage.data = new unsigned char[im.w*im.h];/*bu ge�ici image ekranda fln g�sterilmeyecek.sadece labellar� ge�ici tutacak.*/
//
//    for (int row = 0; row < im.h; row++) {
//        for (int column = 0; column < im.w; column++) {
//
//            vector<int> fourNeighborPixel;/*ba�tan s�rayla kuzeybat�,kuzey,kuzeydo�u ve bat� pixellerini tutacak olan ge�ici vector dizisi
//                                                   yaratt�k.her yeni pixele etiket verece�imiz zaman bu dizi tekrar yarat�lacak.*/
//
//            int ZERO_LABEL = 0;//background pixel etiketi.background pixellerimiz 255 oldu�u i�in bu de�ere sahip olanlar 0 etiketini alacak.
//
//            occlusionImage.data[row * im.w + column] = ZERO_LABEL;
//            tempImage.data[row * im.w + column] = ZERO_LABEL;//ba�ta her bir pixele 0 etiketi veriyoruz.
//
//            
//            if (im.data[row * im.w + column] == 0) {/* gelen yeni pixel siyah ise bu bir nesnedir deriz.�imdi ise kom�u pixellerine bak�p
//                                                    etiket verme i�lemine ge�ece�iz.*/
//                
//                
//                int counter = 0;//bu saya� mevcut kom�u pixelleri vectore eklememizi sa�layacak.
//                /*etiketlenecek pixelden �nceki 4 kom�uyu incelemek i�in for d�ng�s� yazd�k*/
//                for (int neighborRow = -1 ; neighborRow < 0; neighborRow++) {
//                    for (int neighborCol = -1; neighborCol < 1; neighborCol++) {
//
//                        if (neighborRow == 0 && neighborCol == 0) {//bu de�erler etiketlenecek pix ifade etti�i i�in d�ng�den ��kmak gerekir.
//                            break;//zaten bu ifade gelince d�ng�den ��akca�� i�in do�u,gb,g,gd kom�uyu kontrol etmeye gerek yok.
//                        }
//
//                        //4 kom�u pixel konumlar� hesaplan�r
//                        int nRow = row + neighborRow;
//                        int nCol = column + neighborCol;
//                        
//                        /*m�mk�n kom�uluk pixel konumlar� bulundu.(etiketleme yap�lacak pixel ilk ve 
//                        son sutunda ,ilk ve son sat�rda olursa hesaplanan nRow ve nCol de� degatif ��kar bunlarda matriste bir yeri ifade
//                        etmez o y�zden bu de�erler gelince eleme olmas� gerekir.)*/
//                        if (isValidCoordinate(nRow, nCol, im)){
//
//                            fourNeighborPixel.push_back(tempImage.data[nRow * im.w + nCol]);
//                           
//                            
//                        }
//                        
//                        
//                    }
//                }//buradan itibaren kom�u pixellerin label de�erleri elimizde �imdi yeni pixeli etiketleme yapaca��z.
//
//
//                if (row == 0 && column == 0) {//�lk pixel i�in �zel durum va r��nk� fourneighborpixels dizisi bo�.ilk atama
//
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;
//
//                }
//                else if (isAllFourNeighborPixelsZero(fourNeighborPixel)) {//t�m komu�ular 0 ise bu yeni bir nesne belirtir etiketle
//
//                    OBJECT_LABEL = OBJECT_LABEL + 1;
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;// etiketi 1 art�raca��z b�ylece yeni nesne etiketini elde ederiz.
//                }
//                else if (isAllFourNeighborPixelsSame(fourNeighborPixel)) {// t�m komu�lar ayn� etikete sahipse 0 haric yeni pixelde ayn� nesye ait
//
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;
//
//                }
//                else {//di�er durumlar . 1- occlusion durumu 2- 4 pixelden bir k�sm� arkaplana di�erleir ayn� nesneye ait etiketler
//
//                    vector<int> otherSituations = removeZeros(fourNeighborPixel);//bu yeni vectorde s�f�rlar yok
//
//                    /*bu a�amadan sonra iki durum 
//                    1-geri kalan elemanlar hepsi ayn� ise  yeni pixel  kom�ular ile ayn� nesneye ait
//                    2- geri kalan elemanlardan en az ikisi birb farkl� ise occlusion durumu var*/
//
//                    if (allVectorElementsSame(otherSituations)) {//ayn� ensne
//
//                        tempImage.data[row * im.w + column] = OBJECT_LABEL;
//                    }
//                    else {//oclusion durumunda kom�u etiketler  birb fakrl�d�r. bu pixele hem occlusion ver hemde ge�ici olarak d���k etiketi ver.
//
//                        occlusionImage.data[row * im.w + column] = OCCLUSION;
//                        //zaten occlusion durumunda 2 etiket kal�r.
//                        
//                        int occBegin = fourNeighborPixel[0], occEnd = fourNeighborPixel[1];
//                        int smallerOcc, biggerOcc;
//
//                        if (occBegin < occEnd) {
//
//                            smallerOcc = occBegin;
//                            biggerOcc = occEnd;
//                        }else{
//
//                            smallerOcc = occEnd;
//                            biggerOcc = occBegin;
//                        }
//
//                        tempImage.data[row * im.w + column] = smallerOcc;//en d���k etiketi ge�ici olarak ver.
//                        occlusionMap.insert(make_pair(biggerOcc, smallerOcc));
//                    }
//                }
//                
//
//
//            }
//            else {//yeni pixel nesne de�il arka pland�r o y�zden etiketi 0 olacak.san�r�m buraya gerek yok
//
//
//            }
//        }
//
//    }//etiketleme bitti �imdi s�rada occlusion etiketlerini normal etikete �evirme var. occlusion etiketi -1 ile temsil edildi.
//
//    for (int row = 0; row < tempImage.h; row++) {
//        for (int column = 0; column < tempImage.w; column++) {
//
//            for (auto it = occlusionMap.begin(); it != occlusionMap.end(); ++it) {
//                
//                if (tempImage.data[row * im.w + column] == it->first) {
//
//                    tempImage.data[row * im.w + column] = it->second;
//                }
//
//            }
//        }
//    }//burdan sonra bounding boxa alma i�lemi ger�ekle�tirilecek.
//    
//    set<int> object;
//    for (int row = 0; row < tempImage.h; row++) {
//        for (int column = 0; column < tempImage.w; column++) {
//
//          
//        }
//    }
//    for (int row = tempImage.h; row >= 0; row--) {
//        for (int column = tempImage.w; column >= 0; column--) {
//
//           
//        }
//    }
//       
//
//
//    
//
//}
//
///*8 kom�uluk matris elemanlar�n� dola��r ve 1 de kendisi �zerinden ge�er. toplam 9 d�ng�. bu 9 pixelden 4 tanesini yani
// �u anki pixelimizden �nce gelen kom�ular� incelemek gerekir.geri kalan 5 pixelin etiketi yok  ��nk� onlara daha s�ra
// gelmemi�tir.Kom�uluk incelemesi yaparken etiketi olanlara bak�p karar verece�iz.BU KISIM OCCLUS�ON A�IKLAMASI*/
