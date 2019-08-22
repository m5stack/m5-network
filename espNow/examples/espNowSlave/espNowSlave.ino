#include "espnow.h"
#include <M5Stack.h>

EspNowSlave espnow;

void setLcd() {
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.setBrightness(200);
  M5.Lcd.setTextSize(2);
  M5.Lcd.println("espnow slave test");
  M5.Lcd.print(WiFi.softAPmacAddress());
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
}

void printPeerList() {
  setLcd();
  M5.Lcd.setCursor(0, 50);
  M5.Lcd.printf("who is broadcasting :\r\n");
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
    M5.Lcd.println();
    
  }
  M5.Lcd.setCursor(50, 200);
  M5.Lcd.print("Up");
  M5.Lcd.setCursor(120, 200);
  M5.Lcd.print("select");
  M5.Lcd.setCursor(230, 200);
  M5.Lcd.print("down");
}

int lastCount = 0;
int choice = 0;
void loop() {
  M5.update();
  
  delay(50);

  if (espnow.peerlist.count > lastCount) {
    printPeerList();  
    lastCount = espnow.peerlist.count;
  }
  
  Serial.printf("peerCount: %d\r\n", espnow.peerlist.count);
  char *str = "ack";
  
  if(M5.BtnB.isPressed()) {
    if(!espnow.Ack(espnow.peerlist.list[choice])){
      Serial.println("set addr error");
    }
    setLcd();
    if(espnow.isConnected){
      // M5.Lcd.println("connected");
    }
  }

  if (!espnow.isConnected){
    if(M5.BtnA.wasPressed()) {
		  choice--;
		  if (choice < 0) {
			  choice = 0;
		  }
		  printPeerList();
		  M5.Lcd.fillCircle(220, choice*15 + 80, 3, RED);
	  } else if(M5.BtnC.wasPressed()) {
		  choice++;
		  if (choice > espnow.peerlist.count - 1) {
			  choice = espnow.peerlist.count - 1;
		  }
      if (espnow.peerlist.count == 0) {
        choice = 0;
      }
		  printPeerList();
		  M5.Lcd.fillCircle(220, choice*15 + 80, 3, RED);
    }
  }

  delay(10);
}