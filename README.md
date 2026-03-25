# Maaş Bordro Sistemi 2026

2025/2026 Türkiye vergi mevzuatı dikkate alınarak, C dili ile geliştirilmiş bir bordro hesaplama motorudur.

Sistem, personellerin çalışma verilerini içeren `personel.txt` dosyasını okuyarak yasal kesintileri, güncel gelir vergisi dilimlerini, aile ve çocuk yardımlarını ve özel indirimleri (BES, engelli indirimi vb.) otomatik olarak hesaplar. Hesaplama sonucunda her personel için detaylı bordro dökümünü `bordro_sonuclari.txt` dosyasına raporlar.

## Özellikler

- 2026 yılı gelir vergisi tarifesine göre kümülatif matrah üzerinden artan oranlı vergi hesabı (%15 - %40)
- SGK işçi payı (%14), işsizlik sigortası (%1) ve damga vergisi (%0,759) otomatik kesintileri
- Çocuk yardımları (6 yaş altı ve üstü için farklı katsayılar)
- Engelli indirimi ve Bireysel Emeklilik Sistemi (BES) desteği
- Asgari Geçim İndirimi (AGİ) personel bazında etkinleştirilebilir
- Dosya tabanlı, sade ve hızlı hesaplama

## Kurulum ve Çalıştırma

### Gereksinimler
- Standart C derleyicisi (GCC, Clang veya MSVC önerilir)

### Adımlar

1. Proje klasöründe `personel.txt` dosyasının bulunduğundan emin olun.
2. Projeyi derleyin:

bash:
gcc main.c -o bordro_hesaplayici -Wall -Wextra -O2
Programı çalıştırın:

Bash./bordro_hesaplayici
Program tamamlandığında bordro_sonuclari.txt dosyası oluşturulacaktır.
Veri Yapısı ve Girdi Formatı
Program, her satırda bir personeli temsil eden verileri fscanf ile 22 parametre olarak okumaktadır. Alanlar arasında tek boşluk bulunmalıdır.
Girdi dosyasının doğru formatı ve veri sırası için aşağıdaki görsellere bakabilirsiniz:

Veri Yapısı Şeması(Aşağıdaki sıraya göre personel txt dosyası hazırlanmalıdır):

1- id (int): Personel Numarası 

2- tcKimlik (string): 11 Haneli TC Kimlik No 

3- ad (string): Personel Adı 

4- soyad (string): Personel Soyadı 

5- besDurumu (int): 1: Var, 0: Yok 

6- agiDurumu (int): 1: Yararlanıyor, 0: Yok 

7- medeniDurum (int): 1: Evli, 0: Bekar 

8- esiCalisiyorMu (int): 1: Evet, 0: Hayır 

9- prim (float): Aylık toplam prim ödemesi 

10- yolUcreti (float): Günlük yol yardımı tutarı 

11- yemekUcreti (float): Günlük yemek yardımı tutarı 

12- gunSayisi (int): Ay içinde çalışılan gün 

13- cocukSayisi (int): Toplam çocuk sayısı 

14- engelliCocuk_B (int): 6 yaş+ engelli çocuk sayısı 

15- engelliCocuk_K (int): 6 yaş- engelli çocuk sayısı 

16- normalCocuk_B (int): 6 yaş+ engelsiz çocuk sayısı 

17-normalCocuk_K (int): 6 yaş- engelsiz çocuk sayısı 

18- brutSaatUcret (float): 1 saatlik brüt ücret 

19- normalSaat (int): Aylık normal çalışma saati 

20- mesaiSaati (int): Aylık mesai (1.5x) saati 

21- kumulatifMatrah (float): Devreden vergi matrahı 

22- engelOrani (int): Engel yüzdesi (örn: 45, 80)
Örnek Girdi Satırı:

<img width="881" height="134" alt="Ekran görüntüsü 2025-12-10 220350" src="https://github.com/user-attachments/assets/66dee176-2584-4933-9153-b6e43bf6eb3a" />






Hesaplama Mantığı

Gelir vergisi kümülatif matrah üzerinden ilgili dilimlere göre hesaplanır.
Sosyal güvenlik ve işsizlik kesintileri brüt ücret üzerinden otomatik uygulanır.
Aile ve çocuk yardımları, yaş gruplarına göre dinamik olarak belirlenir.
BES ve engelli indirimi gibi özel indirimler personel bazında dikkate alınır.

Örnek çıktı raporu için aşağıdaki görsele bakabilirsiniz:
Örnek Bordro Çıktısı:


<img width="651" height="752" alt="Ekran görüntüsü 2025-12-10 214758" src="https://github.com/user-attachments/assets/ecd0c0d8-25b1-4d57-8747-5c5c1ba3041a" />

Proje word : 
[AlgoFinalMaas_Bordro2026.docx](https://github.com/user-attachments/files/26250399/AlgoFinalMaas_Bordro2026.docx)
