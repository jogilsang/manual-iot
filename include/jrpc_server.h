/*
 * jrpc_server.h
 *
 * Created on: Feb 20, 2013
 *	Author: mathben
 */

#ifndef JRPC_SERVER_H_
#define JRPC_SERVER_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <pthread.h>
#include <wiringPi.h>
#include <signal.h>
#include "jsonrpc-c.h"
#include "jrpc_select.h"
#include "main.h"


typedef unsigned char uchar;

typedef struct {
	int fd;
	int pos; //index of buffer, set it to 0
	unsigned int buffer_size;
	char *buffer;
	int debug_level;
} jrpc_conn_t;

typedef struct {
	int is_running;
	jrpc_select_t jrpc_select;
	procedure_list_t procedure_list;
	int debug_level;
	int sockfd;
	struct termios *options;
} jrpc_server_t;

typedef struct {
	jrpc_server_t *server;
	jrpc_conn_t *conn;
} jrpc_loop_t;

typedef struct {
	int gas;
	int flame;
	int psd;
	int cds;
	int temp;
	int humi;
	int color_r;
	int color_g;
	int color_b;
	int gyro_x;
	int gyro_y;
	int gyro_z;
	int ultra;
	int input_x;
	int input_y;
	int vr;
} series_sensor_send_data_t;

typedef struct {
	int pir;
	int sound;
	int up;
	int down;
	int left;
	int right;
	int sel;
	int sw1;
	int sw2;
	int sw3;
	int sw4;
} event_sensor_send_data_t;

typedef struct {
	int pir;
	int sound;
	int up;
	int down;
	int left;
	int right;
	int sel;
	int sw1;
	int sw2;
	int sw3;
	int sw4;
} event_sensor_temp_data_t;

typedef struct {
    int led;
    int dc_motor;
    int step_motor;
    int buzzer;
} act_recv_data_t;

void discover_create(char* id, char* type, char* name, int notification);
int send_notification(int fd,char *response);
int System_fd,eventFlg,is_GW_running;
void * send_message(void *arg);
void * recv_message(void *arg);
jrpc_server_t *jrpc_server_init();
jrpc_server_t *my_server;
int jrpc_server_init_socket(jrpc_server_t *server, int port);
int jrpc_server_init_serial(jrpc_server_t *server, char *serial);
void jrpc_server_run(jrpc_server_t *server);
int jrpc_server_stop(jrpc_server_t *server);
void jrpc_server_destroy(jrpc_server_t *server);
void sensor_send(int sensor,int value);
void event_send(int event,int value);
void *jrpc_thread_create(void *arg);
int jrpc_init();
int getActflag();
void setActflag(int flg);
int jrpc_exit();
#endif
