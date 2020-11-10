#include <Arduino.h>

#ifdef ESP32
    #include <WiFi.h>
#else
    #include <ESP8266WiFi.h>
#endif
#include "AudioFileSourceICYStream.h"
#include "AudioFileSourceBuffer.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"



// To run, set your ESP8266 build to 160MHz, update the SSID info, and upload.

// Enter your WiFi setup here:
#ifndef STASSID
#define STASSID "wifiabc"
#define STAPSK  "123456"
#endif

//const char* ssid = STASSID;
//const char* password = STAPSK;

// Randomly picked URL
//const char *URL="http://streaming.shoutcast.com/80sPlanet?lang=en-US";
//const char *URL="http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=25.9ee292b3a326087e9b2f4bbf083fbd44.315360000.1919593231.282335-17872447&tex=父亲的差使也交卸了&vol=9&per=0&spd=6&pit=5";
//char *URL;
//char URL[5000];
const char* URL;
AudioGeneratorMP3 *mp3;
AudioFileSourceICYStream *file;
AudioFileSourceBuffer *buff;
AudioOutputI2S *out;

// Called when a metadata event occurs (i.e. an ID3 tag, an ICY block, etc.
void MDCallback(void *cbData, const char *type, bool isUnicode, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  (void) isUnicode; // Punt this ball for now
  // Note that the type and string may be in PROGMEM, so copy them to RAM for printf
  char s1[32], s2[64];
  strncpy_P(s1, type, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  strncpy_P(s2, string, sizeof(s2));
  s2[sizeof(s2)-1]=0;
  Serial.printf("METADATA(%s) '%s' = '%s'\n", ptr, s1, s2);
  Serial.flush();
}

// Called when there's a warning or error (like a buffer underflow or decode hiccup)
void StatusCallback(void *cbData, int code, const char *string)
{
  const char *ptr = reinterpret_cast<const char *>(cbData);
  // Note that the string may be in PROGMEM, so copy it to RAM for printf
  char s1[64];
  strncpy_P(s1, string, sizeof(s1));
  s1[sizeof(s1)-1]=0;
  Serial.printf("STATUS(%s) '%d' = '%s'\n", ptr, code, s1);
  Serial.flush();
}


void speechSynsetup(const char* ssid, const char* password, const char* token, const char *speechtext, int volID, int perID, int spdID, int pitID)
{
	String urlstr;
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi");
  //sprintf(URL,"http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=%s&tex=%s&vol=%d&per=%d&spd=%d&pit=%d",token,speechtext,volID,perID,spdID,pitID);
  urlstr += "http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=";
  urlstr += token;
  urlstr += "&tex=";
  urlstr += speechtext;
  urlstr += "&vol=";
  urlstr += volID;
  urlstr += "&per=";
  urlstr += perID;
  urlstr += "&spd=";
  urlstr += spdID;
  urlstr += "&pit=";
  urlstr += pitID;
  URL = urlstr.c_str();
  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  
  WiFi.begin(ssid, password);

  // Try forever
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("...Connecting to WiFi");
    delay(1000);
  }
  Serial.println("Connected");

  audioLogger = &Serial;
  file = new AudioFileSourceICYStream(URL);
  file->RegisterMetadataCB(MDCallback, (void*)"ICY");
  buff = new AudioFileSourceBuffer(file, 2048);
  buff->RegisterStatusCB(StatusCallback, (void*)"buffer");
  out = new AudioOutputI2S(0, 0, 128);
  out -> SetPinout(26, 25, 27);
  out -> SetGain(3);
  mp3 = new AudioGeneratorMP3();
  mp3->RegisterStatusCB(StatusCallback, (void*)"mp3");
  mp3->begin(buff, out);
}


void speechSynloop()
{
  static int lastms = 0;

  if (mp3->isRunning()) {
    if (millis()-lastms > 1000) {
      lastms = millis();
      Serial.printf("Running for %d ms...\n", lastms);
      Serial.flush();
     }
    if (!mp3->loop()) mp3->stop();
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}
