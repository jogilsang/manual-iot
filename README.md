# manual-iot

### 라즈베리파이-노트북 랜선 연결하기
```
1. 무선인터넷 - 속성 - 공유 - 다른 네트워크 사용자 사용가능 체크
2. 랜선연결 - 로컬네트워크 ( 192.168.137.1)
3. putty, raspberrypi.mshome.net의 호스트네임으로 접속
   호스트네임 변경했으면 hufs_iot_2019_01_5.mshome.net 이런식으로 
```

### 라즈베리파이 OS, SD카드세팅
라즈베리파이 os 다운로드 :
https://www.raspberrypi.org/downloads/raspbian/

SD카드 포맷 :  
https://www.sdcard.org/downloads/formatter/  

SD카드에 OS설치 :  
https://www.balena.io/etcher/  

### 라즈베리파이 키보드,와이파이 등 세팅
와이파이 국적 : uk united kingdom  
키보드 :  

en_GB.UTF-8
en_US.UTF-8
ko_KR.EUC-KR
ko_KR.UTF-8

(preference - setting)
model : generic 105-key intl pc  
layout : korean  
variant : korean (101/104 key compatible)  
lang : ko (korean)  
Counry : kR (south korea)  
character set : utf-8  

(커맨드라인)
sudo apt-get --purge remove ibus  
sudo apt-get -y install fonts-unfonts-core  
sudo apt-get -y install fonts-unfonts-extra  
sudo apt-get -y install nabi  
sudo reboot  



### 라즈베리 파이 wiringPi
```
설치해야 사용가능
git clone git://git.drogon.net/wiringPi
dir
cd wiringPi
./build
```

"![](/KakaoTalk_20190501_104953050.png)"

### 라즈베리파이 Geany Programmer's Editor
```
ctrl + e : 
```

### 라즈베리파이 파일권한
```
chmod 777 someFile
```

### 라즈베리파이 초기 설정 및 설치
```
(커맨드라인, 세팅)
sudo apt-get update (업그레이드 할 목록 갱신)
sudo apt-get upgrade (실제 업그레이드)

(가상키보드설치)
sudo apt-get install mathbox-keyboard

(와이파이)
United Kingdom, UK
putty - ipaddr.txt, ifconfig ip로 접속

(원격접속가능, ssh enable 시켜야함)
id : pi
password : raspberry


(파일 시스템 확장, 설치 제외 공간 사용, 재부팅해야 적용)
sudo raspi-config, Expand FileSystem - os 

(삼바 사용시)
sudo apt-get install samba
sudo vi /etc/samba/smb.conf
sudo smbpasswd -a pi
sudo /etc/init.d/samba restart

(블루투스 사용시)
sudo apt-get install bluetooth
sudo apt-get install libbluetooth-dev
```


### 라즈베리파이에 Thingplus(띵플러스) 세팅
```
0. 사이트주소
https://trial.sandbox.thingplus.net/

1. 시스템시간변경. (데이터전송에 문제생김)
sudo apt-get install -y --force-yes ntp ntpdate
sudo ntpdate -u ntp.ubuntu.com

2. Thing+와 클라우드 구분위해 호스트명 변경필요 (동일한 이름으로 변경해야함. 명칭이 다르면동작안함)
sudo vi /etc/hostname, ex) jogilsang 
sudo vi /etc/hosts, ex) 127.0.1.1 jogilsang
sudo reboot

3. Thing+ Gateway 설치
wget http://support.thingplus.net/download/install/thingplus_embedded_sdk_pi_install.sh

4. Thing+ Embedded 패키지 설치 (스크립트 실행권한 부여 후0 
sudo chmod 755 thingplus_embedded_sdk_pi_install.sh
sudo ./thingplus_embedded_sdk_pi_install.sh

5. Thing+ Embedded 설치후 재부팅
sudo reboot

6. mqtt와 api의 host설정
/opt/thingplus/gateway/thingplus-gateway/device/config 경로에
runtime.json 파일을 아래처럼 추가하던지 수정
{
  "Server" : {
    "mqtt" : {
      "host":"mqtt.sandbox.thingplus.net"
   },
"service":{
  "host" : "api.sandbox.thingplus.net"
}
}
}

7. 아래 둘중에 하나로 맥주소 확인
7.1 cd /opt/thingplus/gateway/scripts로 이동후 ./getGatewayID.sh 명령어 입력
7.2 ifconfig 명령어로 MAC주소 확인해도됨

8. 사이트로 들어가서 게이트관리를 누른뒤, 게이트웨이 인증서 및 API키 발급받기 클릭

9. 하단 커맨드를 입력하여 게이트웨이 관련내용 진행
cd /opt/thingplus/gateway로 이동
sudo APIKEY='복사한 API키' ./thingplus.sh start

10. 띵플러스 사이트에서 게이트웨이 등록하기 버튼클릭
게이트웨이 이름은 (라즈베리파이의 호스트명)
디바이스 모델은 (오픈소스 디바이스)
나머지는 수동으로 자동입력됨
게이트웨이 디바이스센서 등록 진행

11. 띵플러스 접속해서 둘러보기
대시보드 : 게이트웨이에 등록된 센서의 현재 상태정보를 확인하거나
          엑츄에이터 동작 등 모니터링 및 제어 용도로 사용된다.
타임라인 : 게이트웨이에 등록되어있는 센서에 관한 규칙을 사용자가
          직접 규정하여 해당 규칙에 관한 메세지를 모니터링 가능한 페이지
센서목록 : 페이지는 사용자 게이트웨이에 등록되어 있는 모든 센서를
          한눈에 확인 가능하다.
센서분석 : 게이트웨이에 등록되어있는 센서 목록 중 원하는 센서 지정하여
          차트형태로 확인이 가능한 페이지
4가지 기능 사용가능
```

### 라즈베리파이 압축풀기
```
예를들어 agent_base.zip이라는 파일을 압축푸는상황
agent_base라는 폴더를 만들고 거기에 압축풀기

sudo mkdir agent_base
sudo unzip agent_base -d ./agent_base
```

### 라즈베리파이 nodejs
```
설치
sudo apt-get install npm
sudo npm install onoff
(sudo apt-get upgrade 하기전에 해야됨.에러날수있음)

삭제
sudo apt-get remove nodejs
sudo apt-get autoremove
sudo apt-get remove npm

그외
sudo apt-get update
sudo apt-get dist-upgrade
sudo install socket.io --save

(실행방법)
node blink.js 

(업데이트)
wget node-arm.herokuapp.com/node_archive_armhf.deb
sudo dpkg -i node_archive_armhf.deb

(const error, Undexpected error, 발생시)
npm cache clean -f
sudo npm install -g n
sudo n stable
node --version
node 파일.js
```

### 라즈베리파이 실습 with Thing+
```
make : 작성한 소스 코드를 실행 가능하게 함
sudo ./main : thing+ cloud와 연결되면 센서등록과정이 출력됨
클라우드의 엑츄에이터에서 제어가능
```

-LED server.c 파일 수정
```
cp -rf agent_base/ iot_smart_led
cd iot_smart_led

sudo vi lib/jrpc/server.c
#define DEVICE_ID "" // gateway ID로 수정
cJSON_AddItemToObject(device, "deviceModelId", cJSON_CreateString("jsonrpcFullV1.0")); // discover 함수쪽 수정
sensors = cJSON_CreateArray();

sensor = cJSON_CreateObject();
cJSON_AddStringToObject(sensor, "id", LED_RED);
cJSON_AddStringToObject(sensor, "type", "led");
cJSON_AddStringToObject(sensor, "name", "led_red");
cJSON_AddItemToArray(sensors, sensor);

sensor = cJSON_CreateObject();
cJSON_AddStringToObject(sensor, "id", LED_GREEN);
cJSON_AddStringToObject(sensor, "type", "led");
cJSON_AddStringToObject(sensor, "name", "led_green");
cJSON_AddItemToArray(sensors, sensor);

sensor = cJSON_CreateObject();
cJSON_AddStringToObject(sensor, "id", LED_BLUE);
cJSON_AddStringToObject(sensor, "type", "led");
cJSON_AddStringToObject(sensor, "name", "led_blue");
cJSON_AddItemToArray(sensors, sensor);

cJSON_AddItemToObject(device, "sensors", sensors);
cJSON_AddItemToObject(all, "result", devices);


```
-pir(인체감지) server.c 파일 수정
```
cp -rf agent_base/ iot_smart_pir
cd iot_smart_pir

sudo vi lib/jrpc/server.c
#define DEVICE_ID "" // gateway ID로 수정
cJSON_AddItemToObject(device, "deviceModelId", cJSON_CreateString("jsonrpcFullV1.0")); // discover 함수쪽 수정
// 
sensor = cJSON_CreateObject();
cJSON_AddStringToObject(sensor, "id", PIR0);
cJSON_AddStringToObject(sensor, "type", "motion");
cJSON_AddStringToObject(sensor, "name", "pir0");
cJSON_AddItemToArray(sensors, sensor);
```

-소리감지센서(SOUND) server.c 파일수정
```
cJSON *discover(jrpc_context_t *ctx, cJSON *params, cJSON *id) {
  sensor = cJSON_CreateObject();
  cJSON_AddStringToObject(sensor, "id", SOUND0);
  cJSON_AddStringToObject(sensor, "type", "onoff");
  cJSON_AddStringToObject(sensor, "name", "SOUND0");
  cJSON_AddTrueToObject(sensor, "notification");
  cJSON_AddItemToArray(sensors, sensor);
}
```


