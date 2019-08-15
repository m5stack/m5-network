#include "espnow.h"
#include <M5Stack.h>

EspNowSlave espnow;

void setLcd() {
  M5.Lcd.clear(WHITE);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(2);
  M5.Lcd.print("espnow slave test");
}

void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  if (data_len == 2 && data[0] == 0xaa && data[1] == 0x66) {
    //we do nothing here
  } else {
    char macStr[18];
  	snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  	M5.Lcd.print("Last Packet Recv from: "); M5.Lcd.println(macStr);
  }
}

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  setLcd();
  espnow.Init();
  espnow.setRecvCallBack(OnDataRecv);
  M5.Lcd.println();
  M5.Lcd.print(WiFi.softAPmacAddress());
}

void loop() {
  M5.update();
  
  Serial.printf("peerCount: %d\r\n", espnow.peerlist.count);
  char *str = "ack";
//  espnow.sendData(str, 4);
//  if (espnow.peerlist.count > 0) {
//    espnow.Ack(espnow.peerlist.list[0]);
//  }
  
  if(M5.BtnB.isPressed()) {
    espnow.Ack(espnow.peerlist.list[0]);
  }
  delay(10);
}
