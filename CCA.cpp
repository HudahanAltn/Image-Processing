//#include "image.h"
//#include <vector>
//#include <map>
//#include<set>
//using namespace std;
//
//bool isValidCoordinate(int x, int y, image im) {/*pixeller bazen matirisin köþelerinde veya sýnýrlarýnda olabiliyor.i
//                                                bu yüzden koordinat kontrolü yapýlmasý gerekir*/
//    //komþuluk koordinatlarý için hesaplanan satýr ve sutun deðerleri negatif olamamalý ve ayrýca matirisnin satýr vve sutun boyutunu geçmemeli.
//    return x >= 0 && x < im.w && y >= 0 && y < im.h;
//}
//
//bool isAllFourNeighborPixelsZero(const vector<int>& vec) {/*bu fonksiyon tüm 4 komþu pixel 0 ise true döndürür
//                                             böylece yeni bir nesne pixelinde olduðumuzu anlarýz.*/
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
//bool isAllFourNeighborPixelsSame(const vector<int>& vec) {/*bu fonksiyon tüm 4 komþu pixel labellarý ayný  ise true döndürür
//                                             böylece ayný nesne pixelinde olduðumuzu anlarýz.*/
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
//bool allVectorElementsSame(const vector<int>& vec) {//komþu pixellerin tüm elemanlarý eþitse
//
//    if (vec.empty()) { // Eðer vector boþ ise true dön
//        return true;
//    }
//
//    int firstElement = vec[0]; // Vectorün ilk elemanýný al
//
//    // Vectorün diðer elemanlarýný kontrol et, eðer farklý bir eleman bulunursa false dön
//    for (int i = 1; i < vec.size(); i++) {
//        if (vec[i] != firstElement) {
//            return false;
//        }
//    }
//
//    // Eðer tüm elemanlar ayný ise true dön
//    return true;
//}
//
//vector<int> removeZeros(const vector<int>& vec) {//komþu pixellerin eleman eþitliðinin tespti için backgorund label alanlarý kaldýr.
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
//    int OBJECT_LABEL = 1;//nesne sayý takibi için etiketlemeyi 1 den baþlatacaðýz.
//    int OCCLUSION = -1;
//    image tempImage;
//    tempImage.h = im.h;
//    tempImage.w = im.w;
//    tempImage.c = im.c;
//    tempImage.data = new unsigned char[im.w*im.h];/*bu geçici image ekranda fln gösterilmeyecek.sadece labellarý geçici tutacak.*/
//		
//    image occlusionImage;
//    occlusionImage.h = im.h;
//    occlusionImage.w = im.w;
//    occlusionImage.c = im.c;
//    occlusionImage.data = new unsigned char[im.w*im.h];/*bu geçici image ekranda fln gösterilmeyecek.sadece labellarý geçici tutacak.*/
//
//    for (int row = 0; row < im.h; row++) {
//        for (int column = 0; column < im.w; column++) {
//
//            vector<int> fourNeighborPixel;/*baþtan sýrayla kuzeybatý,kuzey,kuzeydoðu ve batý pixellerini tutacak olan geçici vector dizisi
//                                                   yarattýk.her yeni pixele etiket vereceðimiz zaman bu dizi tekrar yaratýlacak.*/
//
//            int ZERO_LABEL = 0;//background pixel etiketi.background pixellerimiz 255 olduðu için bu deðere sahip olanlar 0 etiketini alacak.
//
//            occlusionImage.data[row * im.w + column] = ZERO_LABEL;
//            tempImage.data[row * im.w + column] = ZERO_LABEL;//baþta her bir pixele 0 etiketi veriyoruz.
//
//            
//            if (im.data[row * im.w + column] == 0) {/* gelen yeni pixel siyah ise bu bir nesnedir deriz.þimdi ise komþu pixellerine bakýp
//                                                    etiket verme iþlemine geçeceðiz.*/
//                
//                
//                int counter = 0;//bu sayaç mevcut komþu pixelleri vectore eklememizi saðlayacak.
//                /*etiketlenecek pixelden önceki 4 komþuyu incelemek için for döngüsü yazdýk*/
//                for (int neighborRow = -1 ; neighborRow < 0; neighborRow++) {
//                    for (int neighborCol = -1; neighborCol < 1; neighborCol++) {
//
//                        if (neighborRow == 0 && neighborCol == 0) {//bu deðerler etiketlenecek pix ifade ettiði için döngüden çýkmak gerekir.
//                            break;//zaten bu ifade gelince döngüden çýakcaðý için doðu,gb,g,gd komþuyu kontrol etmeye gerek yok.
//                        }
//
//                        //4 komþu pixel konumlarý hesaplanýr
//                        int nRow = row + neighborRow;
//                        int nCol = column + neighborCol;
//                        
//                        /*mümkün komþuluk pixel konumlarý bulundu.(etiketleme yapýlacak pixel ilk ve 
//                        son sutunda ,ilk ve son satýrda olursa hesaplanan nRow ve nCol deð degatif çýkar bunlarda matriste bir yeri ifade
//                        etmez o yüzden bu deðerler gelince eleme olmasý gerekir.)*/
//                        if (isValidCoordinate(nRow, nCol, im)){
//
//                            fourNeighborPixel.push_back(tempImage.data[nRow * im.w + nCol]);
//                           
//                            
//                        }
//                        
//                        
//                    }
//                }//buradan itibaren komþu pixellerin label deðerleri elimizde þimdi yeni pixeli etiketleme yapacaðýz.
//
//
//                if (row == 0 && column == 0) {//Ýlk pixel için özel durum va rçünkü fourneighborpixels dizisi boþ.ilk atama
//
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;
//
//                }
//                else if (isAllFourNeighborPixelsZero(fourNeighborPixel)) {//tüm komuþular 0 ise bu yeni bir nesne belirtir etiketle
//
//                    OBJECT_LABEL = OBJECT_LABEL + 1;
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;// etiketi 1 artýracaðýz böylece yeni nesne etiketini elde ederiz.
//                }
//                else if (isAllFourNeighborPixelsSame(fourNeighborPixel)) {// tüm komuþlar ayný etikete sahipse 0 haric yeni pixelde ayný nesye ait
//
//                    tempImage.data[row * im.w + column] = OBJECT_LABEL;
//
//                }
//                else {//diðer durumlar . 1- occlusion durumu 2- 4 pixelden bir kýsmý arkaplana diðerleir ayný nesneye ait etiketler
//
//                    vector<int> otherSituations = removeZeros(fourNeighborPixel);//bu yeni vectorde sýfýrlar yok
//
//                    /*bu aþamadan sonra iki durum 
//                    1-geri kalan elemanlar hepsi ayný ise  yeni pixel  komþular ile ayný nesneye ait
//                    2- geri kalan elemanlardan en az ikisi birb farklý ise occlusion durumu var*/
//
//                    if (allVectorElementsSame(otherSituations)) {//ayný ensne
//
//                        tempImage.data[row * im.w + column] = OBJECT_LABEL;
//                    }
//                    else {//oclusion durumunda komþu etiketler  birb fakrlýdýr. bu pixele hem occlusion ver hemde geçici olarak düþük etiketi ver.
//
//                        occlusionImage.data[row * im.w + column] = OCCLUSION;
//                        //zaten occlusion durumunda 2 etiket kalýr.
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
//                        tempImage.data[row * im.w + column] = smallerOcc;//en düþük etiketi geçici olarak ver.
//                        occlusionMap.insert(make_pair(biggerOcc, smallerOcc));
//                    }
//                }
//                
//
//
//            }
//            else {//yeni pixel nesne deðil arka plandýr o yüzden etiketi 0 olacak.sanýrým buraya gerek yok
//
//
//            }
//        }
//
//    }//etiketleme bitti þimdi sýrada occlusion etiketlerini normal etikete çevirme var. occlusion etiketi -1 ile temsil edildi.
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
//    }//burdan sonra bounding boxa alma iþlemi gerçekleþtirilecek.
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
///*8 komþuluk matris elemanlarýný dolaþýr ve 1 de kendisi üzerinden geçer. toplam 9 döngü. bu 9 pixelden 4 tanesini yani
// þu anki pixelimizden önce gelen komþularý incelemek gerekir.geri kalan 5 pixelin etiketi yok  çünkü onlara daha sýra
// gelmemiþtir.Komþuluk incelemesi yaparken etiketi olanlara bakýp karar vereceðiz.BU KISIM OCCLUSÝON AÇIKLAMASI*/
