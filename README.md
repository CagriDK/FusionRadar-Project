# FusionRadar-Project

Kullanılacak Teknolojiler:
*VSCode
*Boost Kütüphanesi
*NLohman Json
*ZeroMQ
*Docker
*CMake
*WSL
*Jenkins Test Automation?

Proje Gereksinimi:
2 Adet Uygulama yazılımı. 1 adet Radar , 1 adet Füzyon.

App1:
-A.noktasından B noktasına 2 saniyede bir veri TCP/IP üzerinden veri aktarımı yapılacaktır.
-Radar konumuna göre enu veya ecef output json formatında gönderilecek.
-Veri hassasiyeti 10^-6 olacaktır.
-Loglama yapılacak.

App2:
-Json Output veri alacak.
-App 1 den konum sorgusu çekecektir.
-Bu konuma göre App 2 data işlenecek ve 0.5 saniyede bir konum gönderecek(LLA).
-Loglama yapılacak.

Proje devamında web servis üzerinde çalışma yapılması ve test otomasyonu üzerinde geliştirme denemesi düşünülmektedir.
