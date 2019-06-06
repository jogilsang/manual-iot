#include "bt.h"    //include header files
#include "main.h"

int sendFlg=0,mConnect=1,eventFlg=0;
pthread_t pth_send,pth_recv;
int send_pth = 0, recv_pth = 0;


//Send Thread function
void * send_message(void *arg){ 
	int sockt = (int)arg;
	int i,res,actCount=0;
	memset(&send_packet,0,sizeof(send_packet_t));
	send_packet.stx = STX;
	send_packet.cmd = 0x00;
	send_packet.data = ETX;
	while(!send_pth) {
		if(sendFlg == 1){
			res = send(sockt, &send_packet,sizeof(send_packet_t), MSG_NOSIGNAL);
			sendFlg = 0;
		}
		sleep(1);
	}
	close((int)arg);
}
int  sensor_read(int sensor){
	int temp=0;
	send_packet.cmd = sensor;
	send_packet.data = ETX;
	sendFlg = 1; 
	sleep(1);
	switch(sensor){
		case GAS_C:
			temp = sensor_data.gas;
			break;
		case FLAME_C:
			temp = sensor_data.flame;
			break;
		case PIR_C:
			temp = sensor_data.pir;
			break;
		case PSD_C:
			temp = sensor_data.psd;
			break;
		case CDS_C:
			temp = sensor_data.cds;
			break;
		case TEMPERATURE_C:
			temp = sensor_data.temp;
			break;
		case HUMIDITY_C:
			temp = sensor_data.humi;
			break;
		case ULTRASONIC_C:
			temp = sensor_data.ultra;
			break;
			default : 
			break;
	}
	return temp;
}
void act_send(int actuator, int status){
	send_packet.cmd = actuator;
	send_packet.data = status;
	sendFlg = 1; 
}

//Receive Thread function
void * recv_message(void *arg){ 
	char recv_buf[100];
	int sockt = (int)arg;
	int str_len,i,tmp_val;

	while(!recv_pth){ 
		if(mConnect == 0){
			str_len = recv(sockt, recv_buf,sizeof(recv_buf),MSG_NOSIGNAL);
		}
		if(str_len == 1){
			if(recv_buf[0] == STX){
					sensor_packet.stx = recv_buf[0];
				str_len = recv(sockt, recv_buf,sizeof(recv_buf),MSG_NOSIGNAL);
				if(str_len == 3){
					sensor_packet.sensor = recv_buf[0];
					sensor_packet.data_H = recv_buf[1];
					sensor_packet.data_L = recv_buf[2];
				}
			}
		}else if(str_len == 4){
			memcpy(&sensor_packet,recv_buf,sizeof(sensor_t));
		}
		if(sensor_packet.stx == 0x76){
			tmp_val = sensor_packet.data_H & 0xff;
			tmp_val = (tmp_val << 8 | sensor_packet.data_L& 0xff);
			switch(sensor_packet.sensor){			
				case GAS_C:
					sensor_data.gas = tmp_val;
					break;
				case FLAME_C:
					sensor_data.flame = tmp_val;
					break;
				case PIR_C:
					sensor_data.pir = tmp_val;
					setEventFlag(1);
					break;
				case PSD_C:
					sensor_data.psd = tmp_val;
					break;
				case CDS_C:
					sensor_data.cds = tmp_val;
					break;
				case TEMPERATURE_C:
					sensor_data.temp = tmp_val;
					break;
				case HUMIDITY_C:
					sensor_data.humi = tmp_val;
					break;
				case ULTRASONIC_C:
					sensor_data.ultra = tmp_val;
					break;
			}

		}else{
			 printf("The error has been occured,while receiving a sensor message" );
		}
		memset(&recv_buf,0,sizeof(recv_buf));
	}
}

void bt_release(int socket){
	close(socket);
	recv_pth = 1;
	send_pth = 1;
	printf("Bluetooth release\n");
}

int getEventFlag(){
	return eventFlg;
}
void setEventFlag(int flag){
	eventFlg = flag;
}
//Bluetooth Initialize function
int bt_init(char *bt_name){
	int sockt;
	memset(&sensor_data,0,sizeof(sensor_data_t));
	struct sockaddr_rc addr = { 0 };

	system("sudo hciconfig hci0 down");
	system("sudo hciconfig hci0 up");
	system("sudo hciconfig hci0 piscan");
	system("sudo sdptool add sp");
	sleep(1);

	printf("Bluetooth bt_init() start..\n");
	while(1){
		if(mConnect == 1){
			while(mConnect){
				close(sockt);
				sockt=socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);
				if(sockt==-1){
					printf("Bluetooth Socket Error()\n");
					exit(1);
				}

				addr.rc_family = AF_BLUETOOTH;
				addr.rc_channel = (uint8_t) 1;
				str2ba( bt_name, &addr.rc_bdaddr );

				if(connect(sockt, (struct sockaddr *)&addr, sizeof(addr))==-1){
					close(sockt);
				}else{
					sleep (1);
					printf("Bluetooth Socket Connect OK\n");
					mConnect=0;
					break;
				}
			}
			break;
		}
	}
	printf("Bluetooth bt_init() end..\n");
	return sockt;
}
//Bluetooth Configure function 
void bt_config(int socket){
	pthread_create(&pth_send, NULL, send_message, (void*)socket);
	pthread_create(&pth_recv, NULL, recv_message, (void*)socket);
	pthread_detach(pth_send);
	pthread_detach(pth_recv);
}
