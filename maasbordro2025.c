#include <stdio.h>
#define SGK_ISCI_ORAN          0.14
#define ISSIZLIK_ISCI_ORAN     0.01    
#define DAMGA_VERGISI_ORAN     0.00759 
#define BES_ORAN               0.03
#define MESAI_KATSAYI          1.5
#define GV_DILIM_1_ORAN        0.15    
#define GV_DILIM_2_ORAN        0.20    
#define GV_DILIM_3_ORAN        0.27    
#define GV_DILIM_4_ORAN        0.35   
#define GV_DILIM_5_ORAN        0.40    
#define GV_DILIM_1_LIMIT       158000
#define GV_DILIM_2_LIMIT       330000
#define GV_DILIM_3_LIMIT       800000
#define GV_DILIM_4_LIMIT       4300000
#define GV_DILIM_2_TABAN   (GV_DILIM_1_LIMIT * GV_DILIM_1_ORAN)
#define GV_DILIM_3_TABAN   (GV_DILIM_2_TABAN + (GV_DILIM_2_LIMIT - GV_DILIM_1_LIMIT) * GV_DILIM_2_ORAN)
#define GV_DILIM_4_TABAN   (GV_DILIM_3_TABAN + (GV_DILIM_3_LIMIT - GV_DILIM_2_LIMIT) * GV_DILIM_3_ORAN)
#define GV_DILIM_5_TABAN   (GV_DILIM_4_TABAN + (GV_DILIM_4_LIMIT - GV_DILIM_3_LIMIT) * GV_DILIM_4_ORAN)
#define ENGEL_DERECESI_1_UCRET 9900
#define ENGEL_DERECESI_2_UCRET 5700
#define ENGEL_DERECESI_3_UCRET 2400
#define BIRINCI_DERECE_ENGEL_ORANI_ALT_SINIR 80
#define IKINCI_DERECE_ENGEL_ORANI_ALT_SINIR 60
#define UCUNCU_DERECE_ENGEL_ORANI_ALT_SINIR 40
#define MIN_AGI_ORAN 0.5
#define AGI_ESI_CALISMAYAN_ORAN 0.1
#define AGI_BIRINCI_COCUK_ORAN 0.075
#define AGI_IKINCI_COCUK_ORAN 0.075
#define AGI_UCUNCU_COCUK_ORAN 0.1   
#define AGI_DORDUNCU_COCUK_VE_USTU_ORAN 0.05
#define AGI_MAX_ORAN 0.85
#define BRUT_ASGARI_UCRET 26005.50f
#define EVLI_YARDIMI 2659.89
#define COCUK_YARDIMI_ALTI_YASINDAN_KUCUK_YARDIM 585.11
#define COCUK_YARDIMI_ALTI_YASINDAN_BUYUK_YARDIM 292.55
#define ENGELLI_COCUK_YARDIM_KATSAYISI 1.5
#define ENGELLI_ALTI_YASINDAN_BUYUK_YARDIM (COCUK_YARDIMI_ALTI_YASINDAN_KUCUK_YARDIM * ENGELLI_COCUK_YARDIM_KATSAYISI)
#define ENGELLI_ALTI_YASINDAN_KUCUK_YARDIM  (COCUK_YARDIMI_ALTI_YASINDAN_BUYUK_YARDIM * ENGELLI_COCUK_YARDIM_KATSAYISI)

FILE *fpr,*fpw;
char ad[50];
char soyad[50];
char tcKimlik[12];
char okunacakDosyaAdi[50] =     "personel.txt";
char yazdirilacakDosyaAdi[50] = "bordro_sonuclari.txt";
int id, agiDurumu,besDurumu,normalCalisilanSaat, mesaiCalisilanSaat, engelDerecesi, engelOrani, medeniDurum, cocukSay, esiCalisiyorMu;
float yolUcretiGunluk, yemekUcretiGunluk,prim;
int calisilanGunSayisi;
int altiYasindanBuyukCocukSay, altiYasindanKucukCocukSay;
int engelliAltiYasindanBuyukCocukSay, engelliAltiYasindanKucukCocukSay;
float kumulatifVergilendirilebilirGelir;
float normalCalismaBrutUcreti, mesaiCalismaBrutUcreti,toplamBrutUcret;
float brutSaatlikUcret;
float yolYardimi,yemekYardimi;
float sgkIsciKesintisi, issizlikSigortasiIsciKesintisi, besKesintisi;
float toplamKesinti;
float vergilendirilebilirGelir;
float buAyOdenecekGelirVergisi;
float damgaVergisi;
float netUcret;
float yeniKumulatifGelirVergisiMatrahi;
int engelliIndirimi;
char tabloBaslangic[43] ="----------------------------------------\n";
char idMsj[5] = "ID: ";
char adMsj[5] = "AD: ";
char soyadMsj[8] = "SOYAD: ";
char tcMesaj[5] = "TC: ";
char medeniDurumMsj[15] = "MEDENI DURUM: ";
char esiCalisiyorMuMsj[22] = "ESI CALISIYOR MU ? : ";
char cocukSayMsj[14] = "COCUK SAYISI: ";
char engelOraniMsj[14] = "ENGEL ORANI: ";
char engelDerecesiMsj[17] = "ENGEL DERECESİ: ";
char brurtSaatlikUcretMsj[20] = "BRUT SAATLIK UCRET: ";
char mesaiCalisilanSaatMsj[22] = "MESAI CALISILAN SAAT: ";
char normalCalisilanSaatMsj[24] = "NORMAL CALISILAN SAAT: ";
char toplamBrutMsj[20] = "TOPLAM BRUT UCRET: ";
char toplamNetMsj[19] = "TOPLAM NET UCRET: ";
char issizlikSigortasiIsciKesintisiMsj[31] = "ISSIZLIK SIGORTASI KESINTISI: ";
char besKesintisiMsj[16] = "BES KESINTISI: ";
char sgkIsciKesintisiMsj[21] = "SGK ISCI KESINTISI: ";
char damgaVergisiMsj[16] = "DAMGA VERGISI: ";
char buAyGvMsj[31] = "BU AY ODENECEK GELIR VERGISI: ";
char vergilendirilebilirGelirMsj[28] = "VERGILENDIRILEBILIR GELIR: ";
char yeniKumulatifVergiMsj[39] = "YENI KUMULATIF GELIR VERGISI MATRAHI: ";
char topKesintiMsj[17] ="TOPLAM KESINTI: ";
char engelIndirimiMsj[17] ="ENGEL INDIRIMI: ";
char eklenenYardimlarMsj[21] = "Eklenen Yardimlar : ";
char yemekYardimiMsj[17] = "Yemek Yardimi : ";
char yolYardimiMsj[15] = "Yol Yardimi : ";
char primMsj[8] = "Prim : ";
char calisilanGunSayisiMsj[24] = "Calisilan Gun Sayisi : ";
char tabloBitis[44] = "*****************************************\n";
char kisielBilgilerBaslik[61] ="--------------------PERSONEL BILGILERI--------------------\n";
char kesintilerBaslik[53] = "--------------------KESINTILER--------------------\n";
char ucretlerBaslik[51] = "--------------------UCRETLER--------------------\n";
char eklentilerBaslik[53] = "--------------------EKLENTİLER--------------------\n";




float normalCalismaBrutUcretiHesapla(float brutSaatlikUcret, int normalCalisilanSaat){
    float sonuc = brutSaatlikUcret * normalCalisilanSaat;
    return sonuc;
}
float mesaiCalismaBrutUcretiHesapla(float brutSaatlikUcret, int mesaiCalisilanSaat){
    float sonuc = brutSaatlikUcret * mesaiCalisilanSaat * MESAI_KATSAYI;
    return sonuc;
}
float yolYardimiHesapla(int calisilanGunSayisi, float yolUcretiGunluk){
    float sonuc = 0;
    sonuc = calisilanGunSayisi * yolUcretiGunluk;

    return sonuc;
}
float yemekYardimiHesapla(int calisilanGunSayisi, float yemekUcretiGunluk){
    float sonuc = 0;
    sonuc = calisilanGunSayisi * yemekUcretiGunluk;
    
    return sonuc;
}
float toplamBrutUcretHesapla(float normalCalismaBrutUcreti , float mesaiCalismaBrutUcreti,float yolUcretiGunluk,
float yemekUcretiGunluk,float prim,int calisilanGunSayisi){
    float sonuc =0;
    sonuc = prim + normalCalismaBrutUcreti + mesaiCalismaBrutUcreti + yolYardimiHesapla(calisilanGunSayisi,yolUcretiGunluk)
    +yemekYardimiHesapla(calisilanGunSayisi,yemekUcretiGunluk);

    return sonuc;
}

float sgkIsciKesintisiHesapla(float toplamBrutUcret){
    float sonuc =toplamBrutUcret * SGK_ISCI_ORAN;
    return sonuc;
}
float issizlikSigortasiIsciKesintisiHesapla(float toplamBrutUcret){
    float sonuc = toplamBrutUcret * ISSIZLIK_ISCI_ORAN;
    return sonuc; 
}
float besKesintisiHesapla(float toplamBrutUcret){
    float sonuc = toplamBrutUcret * BES_ORAN;
    return sonuc;
}
float vergilendirilebilirGelirHesapla(float toplamBrutUcret,float sgkIsciKesintisi,float issizlikSigortasiIsciKesintisi,
    float besKesintisi, int engelliIndirimi){
    float sonuc = toplamBrutUcret - (sgkIsciKesintisi+ issizlikSigortasiIsciKesintisi+ besKesintisi + engelliIndirimi);
    return sonuc;
}

float yeniKumulatifGelirVergisiHesapla(float oncekiAylaraAitToplamVergilendirilebilirGelir, float vergilendirilebilirGelir){
    float sonuc = oncekiAylaraAitToplamVergilendirilebilirGelir + vergilendirilebilirGelir;
    return sonuc;
}
float birikimliGelirVergisiHesapla2025(float birikimliGelirVergisiMatrahi)
{
    if (birikimliGelirVergisiMatrahi <= GV_DILIM_1_LIMIT) {
        float sonuc =birikimliGelirVergisiMatrahi * GV_DILIM_1_ORAN;
        return sonuc;
    }
    else if (birikimliGelirVergisiMatrahi <= GV_DILIM_2_LIMIT) {
        float sonuc = GV_DILIM_2_TABAN+ (birikimliGelirVergisiMatrahi - GV_DILIM_1_LIMIT) * GV_DILIM_2_ORAN;
        return sonuc;
    }
    else if (birikimliGelirVergisiMatrahi <= GV_DILIM_3_LIMIT) {
        float sonuc = GV_DILIM_3_TABAN+ (birikimliGelirVergisiMatrahi - GV_DILIM_2_LIMIT) * GV_DILIM_3_ORAN;
        return sonuc;
    }
    else if (birikimliGelirVergisiMatrahi <= GV_DILIM_4_LIMIT) {
        float sonuc = GV_DILIM_4_TABAN+ (birikimliGelirVergisiMatrahi - GV_DILIM_3_LIMIT) * GV_DILIM_4_ORAN;
        return sonuc;
    }
    else {
        float sonuc =GV_DILIM_5_TABAN+ (birikimliGelirVergisiMatrahi - GV_DILIM_4_LIMIT) * GV_DILIM_5_ORAN;
        return sonuc;
    }
}

float buAyGelirVergisiHesapla(float oncekiBirikimliMatrah,float buAyVergilendirilebilirGelir){
    float eskiVergi = birikimliGelirVergisiHesapla2025(oncekiBirikimliMatrah);
    float yeniMatrah = oncekiBirikimliMatrah + buAyVergilendirilebilirGelir;
    float yeniVergi  = birikimliGelirVergisiHesapla2025(yeniMatrah);
    float sonuc = yeniVergi - eskiVergi;
    return sonuc ;
}

float damgaVergisiHesapla(float toplamBrutUcret){
    float sonuc = toplamBrutUcret * DAMGA_VERGISI_ORAN;
    return sonuc;
}
float toplamKesintiHesapla(float sgkIsciKesintisi, float issizlikSigortasiIsciKesintisi, float besKesintisi,
float buAyOdenecekGelirVergisi, float damgaVergisi){
    float sonuc = sgkIsciKesintisi + issizlikSigortasiIsciKesintisi + besKesintisi + buAyOdenecekGelirVergisi + damgaVergisi;
    return sonuc;
}
float netUcretHesapla(float toplamBrutUcret, float toplamKesinti){
    float sonuc = toplamBrutUcret - toplamKesinti;
    return sonuc;
}
int engelDerecesiBul(int engelOrani){

    if (engelOrani >= BIRINCI_DERECE_ENGEL_ORANI_ALT_SINIR)
        return 1;
    else if (engelOrani >= IKINCI_DERECE_ENGEL_ORANI_ALT_SINIR)
        return 2;
    else if (engelOrani >= UCUNCU_DERECE_ENGEL_ORANI_ALT_SINIR)
        return 3;
    else
        return 0; 
}
int engelliIndirimiAl(int engelDerecesi){
    switch(engelDerecesi){
        case 1:
         return ENGEL_DERECESI_1_UCRET;
        case 2:
         return ENGEL_DERECESI_2_UCRET;
        case 3:
         return ENGEL_DERECESI_3_UCRET;
        default:
         return 0;
    }
}
float agiOraniBul(int medeniDurum,int esiCalisiyorMu,int cocukSay)
{
    float sonuc = MIN_AGI_ORAN;
    if(medeniDurum == 1 && esiCalisiyorMu == 0 )
        sonuc += AGI_ESI_CALISMAYAN_ORAN;

    if(cocukSay>=1)
        sonuc += AGI_BIRINCI_COCUK_ORAN;

    if(cocukSay>=2)
        sonuc += AGI_IKINCI_COCUK_ORAN;

    if(cocukSay>=3)
        sonuc+= AGI_UCUNCU_COCUK_ORAN;

    if(cocukSay>=4)
        sonuc += AGI_DORDUNCU_COCUK_VE_USTU_ORAN * (cocukSay - 3);

    if(sonuc > AGI_MAX_ORAN)
        sonuc = AGI_MAX_ORAN;

    return sonuc;
}
float agiHesapla(int medeniDurum, int esiCalisiyorMu, int cocukSay)
{
    float sonuc = 0;
    sonuc = BRUT_ASGARI_UCRET * agiOraniBul(medeniDurum,esiCalisiyorMu,cocukSay) * GV_DILIM_1_ORAN;
    return sonuc;
}
float cocukVeEsYardimiHesapla(int medeniDurum,int altiYasindanBuyukCocukSay,int altiYasindanKucukCocukSay,
int engelliAltiYasindanBuyukCocukSay, int engelliAltiYasindanKucukCocukSay)
{   
    float sonuc = 0;    
    if(medeniDurum == 1)
        sonuc += EVLI_YARDIMI;

    sonuc += altiYasindanBuyukCocukSay * COCUK_YARDIMI_ALTI_YASINDAN_BUYUK_YARDIM;
    sonuc += altiYasindanKucukCocukSay * COCUK_YARDIMI_ALTI_YASINDAN_KUCUK_YARDIM;
    sonuc += engelliAltiYasindanBuyukCocukSay * ENGELLI_ALTI_YASINDAN_BUYUK_YARDIM;
    sonuc += engelliAltiYasindanKucukCocukSay * ENGELLI_ALTI_YASINDAN_KUCUK_YARDIM;



    return sonuc;
}
void bordroHesapla(){
    normalCalismaBrutUcreti = normalCalismaBrutUcretiHesapla(brutSaatlikUcret, normalCalisilanSaat);
    mesaiCalismaBrutUcreti  = mesaiCalismaBrutUcretiHesapla(brutSaatlikUcret, mesaiCalisilanSaat);
    toplamBrutUcret = toplamBrutUcretHesapla(normalCalismaBrutUcreti, mesaiCalismaBrutUcreti,yolUcretiGunluk,yemekUcretiGunluk,prim,calisilanGunSayisi);
    yolYardimi = yolYardimiHesapla(calisilanGunSayisi,yolUcretiGunluk);
    yemekYardimi = yemekYardimiHesapla(calisilanGunSayisi,yemekUcretiGunluk);        
    sgkIsciKesintisi = sgkIsciKesintisiHesapla(toplamBrutUcret);
    issizlikSigortasiIsciKesintisi = issizlikSigortasiIsciKesintisiHesapla(toplamBrutUcret);  
    if(besDurumu == 1)
        besKesintisi = besKesintisiHesapla(toplamBrutUcret);
    else
        besKesintisi = 0;

    if(engelOrani>0)
    {
        engelDerecesi = engelDerecesiBul(engelOrani);
        engelliIndirimi = engelliIndirimiAl(engelDerecesi);
    }
    else
    {   
        engelliIndirimi=0;
        engelDerecesi = 0;
    }
    vergilendirilebilirGelir = vergilendirilebilirGelirHesapla(toplamBrutUcret, sgkIsciKesintisi, issizlikSigortasiIsciKesintisi,
         besKesintisi, engelliIndirimi);
    buAyOdenecekGelirVergisi = buAyGelirVergisiHesapla(kumulatifVergilendirilebilirGelir, vergilendirilebilirGelir);
    damgaVergisi = damgaVergisiHesapla(toplamBrutUcret);
    toplamKesinti = toplamKesintiHesapla(sgkIsciKesintisi, issizlikSigortasiIsciKesintisi, besKesintisi, buAyOdenecekGelirVergisi, damgaVergisi);
    netUcret = netUcretHesapla(toplamBrutUcret, toplamKesinti);
    yeniKumulatifGelirVergisiMatrahi = yeniKumulatifGelirVergisiHesapla(kumulatifVergilendirilebilirGelir, vergilendirilebilirGelir);
    if(agiDurumu == 1) 
        netUcret += agiHesapla(medeniDurum,esiCalisiyorMu,cocukSay);
    if(medeniDurum == 1 || cocukSay>0)
        netUcret += cocukVeEsYardimiHesapla(medeniDurum,altiYasindanBuyukCocukSay,altiYasindanKucukCocukSay
    ,engelliAltiYasindanBuyukCocukSay,engelliAltiYasindanKucukCocukSay);
        
}

void bordroYaz(){
        fprintf(fpw,"%s",tabloBaslangic);

                                fprintf(fpw,"%s",kisielBilgilerBaslik);

        fprintf(fpw,"%s%d\n", idMsj,id);     
        fprintf(fpw,"%s%s\n",adMsj,ad);      
        fprintf(fpw,"%s%s\n",soyadMsj,soyad);      
        fprintf(fpw,"%s%s\n",tcMesaj,tcKimlik);   
        fprintf(fpw,"%s%d\n",medeniDurumMsj,medeniDurum);  
        fprintf(fpw,"%s%d\n",esiCalisiyorMuMsj,esiCalisiyorMu);    
        fprintf(fpw,"%s%d\n",cocukSayMsj,cocukSay);    
        fprintf(fpw,"%s%d\n",engelOraniMsj,engelOrani);   
        fprintf(fpw,"%s%d\n",engelDerecesiMsj,engelDerecesi);  
        fprintf(fpw,"%s%d\n",calisilanGunSayisiMsj,calisilanGunSayisi);

                                fprintf(fpw,"%s",ucretlerBaslik);

        fprintf(fpw,"%s%f\n",brurtSaatlikUcretMsj,brutSaatlikUcret);    
        fprintf(fpw,"%s%d\n",mesaiCalisilanSaatMsj,mesaiCalisilanSaat);   
        fprintf(fpw,"%s%d\n",normalCalisilanSaatMsj,normalCalisilanSaat); 
        fprintf(fpw,"%s%f\n",yemekYardimiMsj,yemekYardimi);
        fprintf(fpw,"%s%f\n",yolYardimiMsj,yolYardimi);
        fprintf(fpw,"%s%f\n",primMsj,prim);
        fprintf(fpw,"%s%f\n",toplamBrutMsj,toplamBrutUcret);
        fprintf(fpw,"%s%f\n",toplamNetMsj,netUcret);

                                fprintf(fpw,"%s",kesintilerBaslik);

        fprintf(fpw,"%s%f\n",issizlikSigortasiIsciKesintisiMsj,issizlikSigortasiIsciKesintisi);
        fprintf(fpw,"%s%f\n",besKesintisiMsj,besKesintisi);    
        fprintf(fpw,"%s%f\n",sgkIsciKesintisiMsj,sgkIsciKesintisi);  
        fprintf(fpw,"%s%f\n",damgaVergisiMsj,damgaVergisi);   
        fprintf(fpw,"%s%f\n",buAyGvMsj,buAyOdenecekGelirVergisi);   
        fprintf(fpw,"%s%f\n",vergilendirilebilirGelirMsj,vergilendirilebilirGelir);     
        fprintf(fpw,"%s%f\n",yeniKumulatifVergiMsj,yeniKumulatifGelirVergisiMatrahi);  
        fprintf(fpw,"%s%f\n",topKesintiMsj,toplamKesinti);   
        fprintf(fpw,"%s%d\n",engelIndirimiMsj,engelliIndirimi); 

                                fprintf(fpw,"%s",eklentilerBaslik);
                                
        fprintf(fpw,"%s%f\n",eklenenYardimlarMsj,cocukVeEsYardimiHesapla(medeniDurum,altiYasindanBuyukCocukSay,altiYasindanKucukCocukSay,
            engelliAltiYasindanBuyukCocukSay,engelliAltiYasindanKucukCocukSay));
        
        
        fprintf(fpw,"%s",tabloBitis);

        
}

int main() {

    fpr = fopen(okunacakDosyaAdi, "r");    
    fpw = fopen(yazdirilacakDosyaAdi, "w"); 

    while (fscanf(fpr, "%d %s %s %s %d %d %d %d %f %f %f %d %d %d %d %d %d %f %d %d %f %d",&id, tcKimlik, ad ,soyad,&besDurumu,&agiDurumu,
        &medeniDurum,&esiCalisiyorMu,&prim,&yolUcretiGunluk,&yemekUcretiGunluk,&calisilanGunSayisi,&cocukSay,&engelliAltiYasindanBuyukCocukSay,
        &engelliAltiYasindanKucukCocukSay,&altiYasindanBuyukCocukSay,
        &altiYasindanKucukCocukSay,&brutSaatlikUcret, &normalCalisilanSaat, &mesaiCalisilanSaat,&kumulatifVergilendirilebilirGelir,&engelOrani) == 22 )
    {
        bordroHesapla();
        bordroYaz();
    }

    fclose(fpr);
    fclose(fpw);

}


// AGI fonksıyonu yapılacak ama bordrohesapla fonksıyonu ıcınde kullanılamyacak agı kalktı çünkü. Yapılam sebebi bir daha kullanılmaya başlanırsa karışıklık olamamsı için.
//Brut maas hesaplanırken yol + yemek + primde eklenecek.
/*5510 (5 puan indirimi)

6111 teşviki

Genç ve kadın istihdam teşviki

Asgari ücret desteği

Geçici vergi muafiyetleri

Ar-Ge teşvikleri

BU TEŞVİKLER ARAŞTIRILIP EKLENECEK.

BUNLAR ARAŞTIRILACAK : 

EK DÖNEMSEL ÖDEMELER

Kıdem tazminatı

İhbar tazminatı

yıllık izin ücreti

Ücretsiz izin durumları
*/