#ESPNOW Libarary
This library for somebody want to use EspNow in a easy way.

##Get Started
###master side
```
#include <espnow.h>
EspNowMaster espnow;

void setup() {
	espnow.Init();
}

void loop() {
	espnow.Broadcast();
}
```

####after this 
you need to wait for the slave Ack.
if the slave send ack back to the master, you will have to use this.

- ```espnow.peerlist```, a list with the type of ```esp_now_peer_info_t```, all slave's addr will update here.
- ```espnow.confirmPeer(esp_now_peer_info_t peer)```. confirm the slave you want from the list. then you can send data to it.
- ```espnow.sendData```.use it after you confirm a slave. 

###slave side
```
#include <espnow.h>
EspNowSlave espnow;

void setup() {
	espnow.Init();
}

void loop() {
	
}
```

####after this
you need to check the broadcast list, and know who is broadcasting right now, select the master you want and send him an Ack.

- ```espnow.peerlist```, a list with the master who is broadcasting.
- ```espnow.Ack(esp_now_peer_info_t peer)```,select one from the list, and use this function to send him ack.
- ```espnow.sendData```, use it to send Data to the master you want.

 
