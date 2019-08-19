# ESPNOW Libarary
This library for somebody want to use EspNow in a easy way.

## Get Started
### master side Init
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

#### after this 
you need to wait for the slave Ack.
if the slave send ack back to the master, you will have to use this.

- ```espnow.peerlist```: all slave mac_addr will be save here when the slave device send back their ack.
- ```espnow.confirmPeer(esp_now_peer_info_t peer)```: choice a mac_addr in the list and confirm it.
- ```espnow.sendData```.then you can send data to the device that you confirm. 

### slave side Init
```
#include <espnow.h>
EspNowSlave espnow;

void setup() {
	espnow.Init();
}

void loop() {
	
}
```

#### after this
you need to check the broadcast list, and know who is broadcasting right now, select the master you want and send him an Ack.

- ```espnow.peerlist```, all master mac_addr will be save here when there is master is broadcasting.
- ```espnow.Ack(esp_now_peer_info_t peer)```: choice one in the ```peerlist```, and send back the Ack to this master.
- ```espnow.sendData```: then you can send data to the master you choice.

 
