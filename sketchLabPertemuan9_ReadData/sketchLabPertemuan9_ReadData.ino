#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN 9
#define SS_PIN 10
MFRC522 device(SS_PIN, RST_PIN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while(! Serial);

  SPI.begin();
  device.PCD_Init();
  device.PCD_DumpVersionToSerial();
  Serial.println(F("Silakan pindai kartu/tag RFID Anda."));
}

void loop() {
  // put your main code here, to run repeatedly:
  if (! device.PICC_IsNewCardPresent()) {
    return;
  }

  if (! device.PICC_ReadCardSerial()) {
    return;
  }

  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.print(F("UID: "));
  for (byte i = 0; i < device.uid.size; i++) {
    Serial.print(device.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(device.uid.uidByte[i], HEX);
  }
  Serial.println();

  byte block;
  byte buffer[34];
  byte size = sizeof(buffer);
  block = 1;

  MFRC522::StatusCode status;
  byte len;

  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan otentikasi: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Read(block, (char*) buffer, &size);
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan pembacaan: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.print("NAMA LENGKAP\t:\t");
    for (byte i = 0; i < 16; i++) {
      Serial.print(char(buffer[i]));
    }
  }
  Serial.println();

  block = 4;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan otentikasi: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Read(block, (char*) buffer, &size);
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan pembacaan: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.print("NOMOR INDUK\t:\t");
    for (byte i = 0; i < 16; i++) {
      Serial.print(char(buffer[i]));
    }
  }
  Serial.println();

  block = 8;
  status = device.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(device.uid));
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan otentikasi: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  }

  status = device.MIFARE_Read(block, (char*) buffer, &size);
  if (! (status == MFRC522::STATUS_OK)) {
    Serial.print("Kesalahan pembacaan: ");
    Serial.println(device.GetStatusCodeName(status));
    return;
  } else {
    Serial.print("FAKULTAS\t:\t");
    for (byte i = 0; i < 16; i++) {
      Serial.print(char(buffer[i]));
    }
  }
  Serial.println();

  device.PICC_HaltA();
  device.PCD_StopCrypto1();
}

