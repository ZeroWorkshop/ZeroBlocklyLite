
#include "justtest.h"

const char* ssid = "zeroworkshop-2.4G";
const char* password = "zerotech105";
const char* token = "25.9ee292b3a326087e9b2f4bbf083fbd44.315360000.1919593231.282335-17872447";
const char* speechtext = "你好，欢迎使用文字转语音功能";
int volID = 9;
int spdID = 6;
int pitID = 5;
int perID = 1;

void setup(){
  speechSynsetup(ssid, password, token, speechtext, volID, perID, spdID, pitID);

}

void loop(){
  speechSynloop();

}