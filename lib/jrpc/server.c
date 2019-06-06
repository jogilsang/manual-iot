#include <time.h>
#include "jrpc_server.h"
#include "bt.h"

#define PORT 50800  // Server Port
#define DEVICE_ID "b827eb9fff02" //Raspberry PI MAC Address
//Sensors name Setting = DEVICE_ID + "-SensorType-index"

//sensor ID 
#define TEMP0 DEVICE_ID "-temperature-0"
#define GYRO_X0 DEVICE_ID "-gyroscope-x-0"
#define GYRO_Y0 DEVICE_ID "-gyroscope-y-0"
#define GYRO_Z0 DEVICE_ID "-gyroscope-z-0"
#define CDS0 DEVICE_ID "-light-0"
#define HUMI0 DEVICE_ID "-humidity-0"
#define PSD0 DEVICE_ID "-psd-0"
#define GAS0 DEVICE_ID "-gas-0"
#define FLAME0 DEVICE_ID "-flame-0"
#define COLOR_R0 DEVICE_ID "-color-r-0"
#define COLOR_G0 DEVICE_ID "-color-g-0"
#define COLOR_B0 DEVICE_ID "-color-b-0"
#define ULTRASONIC0 DEVICE_ID "-ultrasonic-0"
#define INPUT_X0 DEVICE_ID "-input-x-0"
#define INPUT_Y0 DEVICE_ID "-input-y-0"
#define VR0 DEVICE_ID "-VR-0"

//ACT ID
#define LED_RED DEVICE_ID "-led_red-0"
#define LED_GREEN DEVICE_ID "-led_green-0"
#define LED_BLUE DEVICE_ID "-led_blue-0"
#define DCMOTOR0 DEVICE_ID "-dcmotor-0"
#define STEPMOTOR0 DEVICE_ID "-stepmotor-0"
#define BUZZER0 DEVICE_ID "-buzzer-0"

//Event ID
#define BUTTON_UP DEVICE_ID "-button-up-0"
#define BUTTON_DOWN DEVICE_ID "-button-down-0"
#define BUTTON_LEFT DEVICE_ID "-button-left-0"
#define BUTTON_RIGHT DEVICE_ID "-button-right-0"
#define BUTTON_SEL DEVICE_ID "-button-SEL-0"
#define PIR0 DEVICE_ID "-motion-0"
#define SOUND0 DEVICE_ID "-sound-0"
#define SWITCH1 DEVICE_ID "-switch-1"
#define SWITCH2 DEVICE_ID "-switch-2"
#define SWITCH3 DEVICE_ID "-switch-3"
#define SWITCH4 DEVICE_ID "-switch-4"

series_sensor_send_data_t series_send_data;
event_sensor_send_data_t event_send_data;
event_sensor_temp_data_t event_temp_data;
act_recv_data_t act_recv_data;
int act_flg;
void handle_kill_signal() {
	jrpc_server_stop(my_server);
	signal(SIGINT, SIG_DFL);
	signal(SIGTERM, SIG_DFL);
	signal(SIGHUP, SIG_DFL);
}
// AtThing + Potal Sensor Set
cJSON *discover(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
	cJSON* devices = NULL, *device = NULL, *sensor = NULL, *all=NULL, *sensors = NULL;
  all = cJSON_CreateObject();
  devices = cJSON_CreateArray();
  device = cJSON_CreateObject();  
  cJSON_AddItemToArray(devices, device);

  cJSON_AddItemToObject(all, "jsonrpc",cJSON_CreateString(JRPC_VERSION));
  cJSON_AddItemToObject(device, "deviceAddress", cJSON_CreateString(DEVICE_ID));

   sensors = cJSON_CreateArray();
	
  cJSON_AddItemToObject(device, "sensors", sensors);
	
  cJSON_AddItemToObject(all, "result", devices);
	return all;
}

// 
cJSON *sensor_set(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
  cJSON *result = cJSON_CreateObject(),*result2 = cJSON_CreateObject(),
        *sensorId = NULL,*sensorId2 = NULL;
  char *sensorIdStr = NULL,*sensorIdStr2 = NULL;
 
	cJSON_AddItemToObject(result2, "jsonrpc",cJSON_CreateString(JRPC_VERSION));
    sensorId = cJSON_GetArrayItem(params, 0);
    sensorId2 = cJSON_GetArrayItem(params, 1);
    if (NULL != sensorId) {
      sensorIdStr = sensorId->valuestring;
      sensorIdStr2 = sensorId2->valuestring;
    }
	if (sensorIdStr != NULL) { //very simple simulation
		if(strcmp(sensorIdStr,DCMOTOR0)== 0){
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.dc_motor = ACT_ON;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.dc_motor = ACT_OFF;
			}	
		}else if(strcmp(sensorIdStr,STEPMOTOR0)== 0){
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.step_motor = STEP_FORWARD;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.step_motor = STEP_REVERSE;
			}	
		}else if(strcmp(sensorIdStr, LED_RED) == 0) {
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led = RED_ON;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led = RED_OFF;
			}
		}else if(strcmp(sensorIdStr,LED_GREEN) == 0){
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led = GREEN_ON;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led = GREEN_OFF;
			}	
		}else if(strcmp(sensorIdStr,LED_BLUE) == 0){
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led =BLUE_ON;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.led = BLUE_OFF;
			}	
		}else if(strcmp(sensorIdStr,BUZZER0) == 0){
			if(!strcmp(sensorIdStr2,"on")){	 
				result = cJSON_CreateString("on");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.buzzer =ACT_ON;
			}else if(!strcmp(sensorIdStr2,"off")){	
				result = cJSON_CreateString("off");
				cJSON_AddStringToObject(result, "error", "NULL");
				act_recv_data.buzzer = ACT_OFF;
			}	
		}
		setActflag(1);
	}
	cJSON_AddItemToObject(result2, "result",result);
	return result2;
}

// send Event sensor function
cJSON *sensor_notification(int event) {	
  cJSON *result = cJSON_CreateObject(),*params = cJSON_CreateArray(),*status = cJSON_CreateObject();
  int re = 0;
  char *head = "{\"method\":\"sensor.notification\",\"params\":[\"";
  char *end = "\",{\"value\":";
  char msg[200];
  
  switch(event){
		case 1:
				if(event_send_data.sound != event_temp_data.sound){
					sprintf(msg,"%s%s%s%d}]}",head,SOUND0,end,event_send_data.sound);
					send_notification(gateway_fd,msg);
					event_temp_data.sound = event_send_data.sound;
				}
		break;
		case 2:
				if(event_send_data.pir != event_temp_data.pir){
					sprintf(msg,"%s%s%s%d}]}",head,PIR0,end,event_send_data.pir);
					send_notification(gateway_fd,msg);
					event_temp_data.pir = event_send_data.pir;
				}
		break;
		case 3:
				if(event_send_data.up != event_temp_data.up){
					sprintf(msg,"%s%s%s%d}]}",head,BUTTON_UP,end,event_send_data.up);
					send_notification(gateway_fd,msg);
					event_temp_data.up = event_send_data.up;
				}
		break;
		case 4:
				if(event_send_data.down != event_temp_data.down){
					sprintf(msg,"%s%s%s%d}]}",head,BUTTON_DOWN,end,event_send_data.down);
					send_notification(gateway_fd,msg);
					event_temp_data.down = event_send_data.down;
				}
		break;
		case 5:
				if(event_send_data.left != event_temp_data.left){
					sprintf(msg,"%s%s%s%d}]}",head,BUTTON_LEFT,end,event_send_data.left);
					send_notification(gateway_fd,msg);
					event_temp_data.left = event_send_data.left;
				}
		break;
		case 6:
				if(event_send_data.right != event_temp_data.right){
					sprintf(msg,"%s%s%s%d}]}",head,BUTTON_RIGHT,end,event_send_data.right);
					send_notification(gateway_fd,msg);
					event_temp_data.right = event_send_data.right;
				}
		break;
		case 7:
				if(event_send_data.sel != event_temp_data.sel){
					sprintf(msg,"%s%s%s%d}]}",head,BUTTON_SEL,end,event_send_data.sel);
					send_notification(gateway_fd,msg);
					event_temp_data.sel = event_send_data.sel;
				}
		break;
		case 8:
				if(event_send_data.sw1 != event_temp_data.sw1){
					sprintf(msg,"%s%s%s%d}]}",head,SWITCH1,end,event_send_data.sw1);
					send_notification(gateway_fd,msg);
					event_temp_data.sw1 = event_send_data.sw1;
				}
		break;
		case 9:
				if(event_send_data.sw2 != event_temp_data.sw2){
					sprintf(msg,"%s%s%s%d}]}",head,SWITCH2,end,event_send_data.sw2);
					send_notification(gateway_fd,msg);
					event_temp_data.sw2 = event_send_data.sw2;
				}
		break;
		case 10:
				if(event_send_data.sw3 != event_temp_data.sw3){
					sprintf(msg,"%s%s%s%d}]}",head,SWITCH3,end,event_send_data.sw3);
					send_notification(gateway_fd,msg);
					event_temp_data.sw3 = event_send_data.sw3;
				}
		break;
		case 11:
				if(event_send_data.sw4 != event_temp_data.sw4){
					sprintf(msg,"%s%s%s%d}]}",head,SWITCH4,end,event_send_data.sw4);
					send_notification(gateway_fd,msg);
					event_temp_data.sw4 = event_send_data.sw4;
				}
		break;
	}
	eventFlg = 0;
	
	return result;
}


cJSON *ping(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
  cJSON *result = cJSON_CreateObject();
  
	cJSON_AddNullToObject(result, "result");
  return result;
}


cJSON *sensor_setNotification(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
	
  cJSON *result = cJSON_CreateObject();
  cJSON_AddStringToObject(result, "result", "success");
  cJSON_AddNullToObject(result, "error");
	return result;
}

//서버로부터 요청을 받아 해당 데이터의 데이터 전송
cJSON *sensor_get(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
  cJSON *result = cJSON_CreateObject(),  *result2 = cJSON_CreateObject(),  
        *sensorId = NULL;
  char *sensorIdStr = NULL;
  
	cJSON_AddItemToObject(result2, "jsonrpc",cJSON_CreateString(JRPC_VERSION));
    sensorId = cJSON_GetArrayItem(params, 0);
	if (NULL != sensorId) 
		sensorIdStr = sensorId->valuestring;
	
	if (sensorIdStr != NULL) { //very simple simulation
		if(strcmp(sensorIdStr, TEMP0) == 0 )  
			cJSON_AddNumberToObject(result, "value", series_send_data.temp);
		else if(strcmp(sensorIdStr, HUMI0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.humi);
		else if(strcmp(sensorIdStr, PSD0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.psd);
		else if(strcmp(sensorIdStr, CDS0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.cds); 
		else if(strcmp(sensorIdStr, GAS0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.gas);
		else if(strcmp(sensorIdStr, FLAME0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.flame);
		else if(strcmp(sensorIdStr, GYRO_X0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.gyro_x);
		else if(strcmp(sensorIdStr, GYRO_Y0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.gyro_y);
		else if(strcmp(sensorIdStr, GYRO_Z0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.gyro_z);
		else if(strcmp(sensorIdStr, COLOR_R0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.color_r);
		else if(strcmp(sensorIdStr, COLOR_G0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.color_g);
		else if(strcmp(sensorIdStr, COLOR_B0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.color_b);
		else if(strcmp(sensorIdStr, ULTRASONIC0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.ultra);
		else if(strcmp(sensorIdStr, INPUT_X0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.input_x);
		else if(strcmp(sensorIdStr, INPUT_Y0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.input_y);
		else if(strcmp(sensorIdStr, VR0) == 0) 
			cJSON_AddNumberToObject(result, "value", series_send_data.vr);
	}
	cJSON_AddItemToObject(result2, "result",result);

	return result2;
}

// Server connection close function
cJSON *exit_server(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
	jrpc_server_stop(my_server);
	return cJSON_CreateString("Bye!");
}

//jrpc thread create function
void *jrpc_thread_create(void *arg){
	struct sigaction action;
	act_flg = 0;
	is_GW_running = 0;
	eventFlg = 0;
	setenv("JRPC_DEBUG", "1", 1); /* uncomment to active debug */

	memset(&event_send_data, 0, sizeof(event_send_data));
	memset(&event_temp_data, 0, sizeof(event_temp_data));
	my_server = jrpc_server_init(PORT);
	jrpc_server_init_socket(my_server, PORT);
	jrpc_register_procedure(&my_server->procedure_list, discover, "discover", NULL);
	jrpc_register_procedure(&my_server->procedure_list, sensor_get, "sensor.get", NULL);
	jrpc_register_procedure(&my_server->procedure_list, sensor_set, "sensor.set", NULL);
	jrpc_register_procedure(&my_server->procedure_list, ping, "ping", NULL);
	jrpc_register_procedure(&my_server->procedure_list, sensor_setNotification, "sensor.setNotification", NULL);
	jrpc_register_procedure(&my_server->procedure_list, exit_server, "exit", NULL);
	// Add signal handler to terminate server
	action.sa_handler = handle_kill_signal;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;
	sigaction(SIGINT, &action, NULL);
	sigaction(SIGTERM, &action, NULL);
	sigaction(SIGHUP, &action, NULL);

	jrpc_server_run(my_server);

	jrpc_server_destroy(my_server);
	if (my_server->debug_level)
		printf("close jrpc-server\n");
	//return 0;
}

// jrpc init function
int jrpc_init() {
	pthread_t pth_jrpc;
	pthread_create(&pth_jrpc,0,jrpc_thread_create,0);
	pthread_detach(pth_jrpc);
	return 0;
}

int jrpc_exit(){
	jrpc_server_stop(my_server);
	
}
//
void sensor_send(int sensor,int value){
	switch(sensor){
		case TEMPERATURE_C : 
			series_send_data.temp = value;
		break;
		case HUMIDITY_C : 
			series_send_data.humi = value;
		break;
		case PSD_C : 
			series_send_data.psd = value;
		break;
		case CDS_C : 
			series_send_data.cds = value;
		break;
		case GAS_C : 
			series_send_data.gas = value;
		break;
		case FLAME_C : 
			series_send_data.flame = value;
		break;
		case COLOR_R_C : 
			series_send_data.color_r = value;
		break;
		case COLOR_G_C : 
			series_send_data.color_g = value;
		break;
		case GYRO_X_C : 
			series_send_data.gyro_x = value;
		break;
		case GYRO_Y_C : 
			series_send_data.gyro_y = value;
		break;
		case GYRO_Z_C : 
			series_send_data.gyro_z = value;
		break;
		case ULTRASONIC_C : 
			series_send_data.ultra = value;
		break;
		case INPUT_X_C : 
			series_send_data.input_x = value;
		break;
		case INPUT_Y_C : 
			series_send_data.input_y = value;
		break;
		case VR_C :
			series_send_data.vr = value;
		break;
		default :
			printf("Sensor Not Found\n");
			break;
		
	}
}
void event_send(int event,int value){
	switch(event){
		case SOUND_C : 
			event_send_data.sound = value;
			sensor_notification(1);
		break;
		case PIR_C : 
			event_send_data.pir = value;
			sensor_notification(2);
		break;
		case BUTTON_UP_C : 
			event_send_data.up = value;
			sensor_notification(3);
		break;
		case BUTTON_DOWN_C : 
			event_send_data.down = value;
			sensor_notification(4);
		break;
		case BUTTON_LEFT_C : 
			event_send_data.left = value;
			sensor_notification(5);
		break;
		case BUTTON_RIGHT_C : 
			event_send_data.right = value;
			sensor_notification(6);
		break;
		case BUTTON_SEL_C : 
			event_send_data.sel = value;
			sensor_notification(7);
		break;
		case SW1_C : 
			event_send_data.sw1 = value;
			sensor_notification(8);
		break;
		case SW2_C : 
			event_send_data.sw2 = value;
			sensor_notification(9);
		break;
		case SW3_C : 
			event_send_data.sw3 = value;
			sensor_notification(10);
		break;
		case SW4_C : 
			event_send_data.sw4 = value;
			sensor_notification(11);
		break;
		default :
			printf("Event Sensor Not Found\n");
			break;
	}
	eventFlg =1;
}

int act_recv(int sensor){
	switch(sensor){
		case LED_C:
			return act_recv_data.led;
		break;
		case DC_MOTOR_C:
			return act_recv_data.dc_motor;
		break;
		case STEP_MOTOR_C:
			return act_recv_data.step_motor;
		break;
		case BUZZER_C:
			return act_recv_data.buzzer;
		break;
		default :
			printf("Actuator Not Found\n");
			break;
	}
	
}

int getActflag(){
	
	return act_flg;
}

void setActflag(int flg){
	act_flg = flg;
}

