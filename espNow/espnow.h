#ifndef __ESPNOW_H
#define __ESPNOW_H

#include <Preferences.h>
#include <esp_now.h>
#include <WiFi.h>
#include <String>

//#define CHANNEL 1

#define CHANNEL 3
#define PRINTSCANRESULTS 0
#define DELETEBEFOREPAIR 0

class EspNow {

public:
	esp_now_peer_info_t slave;
	char* device_name = NULL;

	EspNow();
	~EspNow();
	// void setDeviceName(char* name) { sprintf(device_name, name); };
	// void InitESPNow(void);
	void deletePeer(void); 
	void sendData(void *buf, int len);
	bool manageSlave(void);
	void setRecvCallBack(void (*cb)(const unsigned char *, const unsigned char *, int));
	void setSendCallBack(void (*cb)(const unsigned char *, esp_now_send_status_t));
	static void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
	static void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len);
};

class EspNowMaster :public EspNow {
public:
	bool onRecvEnable = false;
	bool onSentEnable = false;

	EspNowMaster();
	~EspNowMaster();
	void ScanForSlave(void);
	void setDeviceName(char* name) { sprintf(device_name, name); };
	void InitESPNow(void);

private:
	Preferences preferences; 
};

class EspNowSlave :public EspNow {
public:
	bool onRecvEnable = false;
	bool onSentEnable = false;

	EspNowSlave();
	~EspNowSlave();
	void setDeviceName(char* name) { sprintf(device_name, name); };
	void InitESPNow(void);

};
#endif
