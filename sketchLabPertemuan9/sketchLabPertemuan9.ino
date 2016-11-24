#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 device(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial);

  SPI.begin();
  device.PCD_Init();
  device.PCD_DumpVersionToSerial();
  Serial.println("Silakan pindai kartu/tag RFID Anda.");
}

void loop() {
  if ( ! device.PICC_IsNewCardPresent() ) {
    return;
  }

  if ( ! device.PICC_ReadCardSerial() ) {
    Serial.println("Kartu tidak sah. Silakan coba lagi.");
    return;
  }

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++)
    key.keyByte[i] = 0xFF;
  
  String content = "";
  Serial.print("UID: ");
  for (byte i = 0; i < device.uid.size; i++) {
    Serial.print(device.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(device.uid.uidByte[i], HEX);
  }

  Serial.println();
  Serial.print("Jenis kartu: ");
  MFRC522::PICC_Type piccType = device.PICC_GetType(device.uid.sak);
  Serial.println(device.PICC_GetTypeName(piccType));

  byte buffer[34];
  byte block;

  MFRC522::StatusCode status;
  byte len;

  Serial.setTimeout(20000L);
  Serial.println("Ketikkan nama lengkap, akhiri dengan tanda #");
  len = Serial.readBytesUntil('#', (char*) buffer, 30);
  for (byte i = len; i < 30; i++)
    buffer[i] = ' ';

  block = 1;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println(F("Otentikasi key A pada kartu RFID berhasil."));
  }

  status = device.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan penulisan data: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println("Proses penulisan data berhasil.");
  }
  
  block = 2;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
      Serial.print(F("Kesalahan penulisan data: "));
      Serial.println(device.GetStatusCodeName(status));
      return;
  } else {
    Serial.println(F("Penulisan data berhasil."));
  }

  Serial.println(F("Ketikkan NIM Anda, akhiri dengan huruf #"));
  len = Serial.readBytesUntil('#', (char*) buffer, 20);
  for (byte i = len; i < 20; i++) buffer[i] = ' ';

  block = 4;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan penulisan data: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println(F("Penulisan data berhasil."));
  }

  block = 5;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan penulisan data: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println(F("Penulisan data berhasil."));
  }

  Serial.println(F("Isi nama fakultas (misal: FASILKOM-TI), akhiri dengan huruf #"));
  len = Serial.readBytesUntil('#', (char*) buffer, 20);
  
  block = 8;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan penulisan data: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println(F("Penulisan data berhasil."));
  }

  block = 9;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan otentikasi: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Write(block, &buffer[16], 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Kesalahan penulisan data: "));
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.println(F("Proses penulisan data berhasil."));
  }

  device.PICC_HaltA();
  device.PCD_StopCrypto1();
}

