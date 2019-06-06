#ifndef __BT_H__
#define __BT_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>
#include <pthread.h>
#include <fcntl.h>
#include <termios.h>
#include <time.h>

//#define DEBUG

#ifdef DEBUG
#define DBG(fmt, args...)       printf(fmt, ##args)
#else
#define DBG(fmt, args...)
#endif

#define STX     0x76
#define ETX     0x00

typedef unsigned char uchar;
typedef unsigned short ushort;
typedef unsigned int uint;

// ADK send & recv struct
typedef struct {
    uchar stx;
    uchar cmd;
    uchar data;
} send_packet_t;

// Event Sensor packet structure
typedef struct {
    uchar stx;
	 uchar sensor;
    uchar data_H;
	 uchar data_L;
} sensor_t;

//data packet structure to store the returned data
typedef struct {
	int gas;
	int flame;
	int pir;
	int psd;
	int cds;
	int temp;
	int humi;
	int ultra;
} sensor_data_t;

//bluetooth socket function ..
void act_send(int actuator, int status);
int sensor_read(int sensor);
int bt_init(char *bt_name);
void bt_config(int socket);
int getEventFlag();
void setEventFlag(int flag);

//bluetooth value
send_packet_t send_packet;
sensor_t sensor_packet;
sensor_data_t sensor_data;

#endif /* __BT_H__ */
