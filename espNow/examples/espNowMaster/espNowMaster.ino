#include "espnow.h"
#include <M5Stack.h>

EspNowMaster espnow;

void setLcd() {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.clear(WHITE);
  M5.Lcd.setTextColor(RED);
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("espnow slave test");
  M5.Lcd.print(WiFi.macAddress());
}


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  setLcd();
  espnow.Init();
}

void printPeerList() {
  M5.Lcd.setCursor(0, 50);
  for(int i = 0; i < espnow.peerlist.count; i++) {
    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           espnow.peerlist.list[i].peer_addr[0], 
           espnow.peerlist.list[i].peer_addr[1],
           espnow.peerlist.list[i].peer_addr[2],
           espnow.peerlist.list[i].peer_addr[3],
           espnow.peerlist.list[i].peer_addr[4],
           espnow.peerlist.list[i].peer_addr[5]);
    M5.Lcd.println(macStr);
  }
}

int choice = 0;
void loop() {
  // put your main code here, to run repeatedly:
  M5.update();
  espnow.Broadcast();

  printPeerList();
  
  Serial.printf("peer count: %d\r\n", espnow.peerlist.count);
  if(M5.BtnB.wasPressed()) {
    Serial.println("confirm");
    espnow.confirmPeer(espnow.peerlist.list[choice]);
    
    if (espnow.isConnected) {
      char *str = "hi";
      espnow.sendData(str, 3);
    }
  } else if(M5.BtnA.wasPressed()) {
    choice--;
    if (choice < 0) {
      choice = 0;
    }
    setLcd();
    M5.Lcd.fillCircle(220, choice*15 + 60, 3, RED);
  } else if(M5.BtnC.wasPressed()) {
    choice++;
    if (choice > espnow.peerlist.count - 1) {
      choice = espnow.peerlist.count - 1;
    }
    setLcd();
    M5.Lcd.fillCircle(220, choice*15 + 60, 3, RED);
  }
  delay(30);
}
