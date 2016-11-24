# Praktikum Komunikasi Data dan Jaringan Nirkabel
## Pertemuan 9: RFID

### Deskripsi Singkat

Pada pertemuan ini, akan diperagakan cara penulisan data RFID dengan 
jenis kartu MIFARE 1KB, menggunakan modul MIFARE MFRC522. Modul ini 
dipasang pada unit Arduino Uno.

Arduino Uno merupakan sebuah komponen mikrokontroler yang dapat 
digunakan untuk menjalankan operasi-operasi sederhana. Arduino Uno juga 
dapat digunakan untuk menerapkan konsep IoT (Internet of Things), di 
mana dengan bantuan network shield, seperti Ethernet Shield, WiFi 
Shield, dan GSM Shield; dapat berkomunikasi dalam jaringan internet, 
untuk melakukan operasi-operasi sesuai dengan modul yang ditanamkan 
padanya.

### Kebutuhan Perangkat

Perangkat yang dibutuhkan adalah sebagai berikut:

* Arduino Uno
* MFRC522
* Kabel Jumper x 7, disarankan menggunakan Male to Female Jumper
* PC dengan Arduino IDE terpasang di dalamnya

Library yang akan digunakan di dalam pertemuan ini adalah MFRC522 
(https://github.com/miguelbalboa/rfid)

### Cara Pemasangan

MFRC522 dipasang ke Arduino Uno menggunakan kabel jumper dengan mapping 
pin sebagai berikut:

* Pin 3.3V / VCC ke pin 3.3V di Arduino (sebelah kiri, bagian Power)
* Pin RST ke pin digital nomor 9 (sebelah kanan, bagian atas, kedua dari 
bawah)
* Pin GND ke pin GND di Arduino (sebelah kiri, bagian Power)
* Pin IRQ tidak dihubungkan
* Pin MISO ke pin digital nomor 12 (3 pin di atas pin RST)
* Pin MOSI ke pin digital nomor 11 (2 pin di atas pin RST)
* Pin SCK ke pin digital nomor 13 (4 pin di atas pin RST)
* Pin SDA ke pin digital nomor 10 (1 pin di atas pin RST)
