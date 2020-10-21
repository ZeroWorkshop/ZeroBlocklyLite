#include <Arduino.h>
#include "NextionAll.h"
#include <math.h>
#include <Streaming.h>  //https://www.arduinolibraries.info/libraries/streaming
#include <Vector.h>   //https://www.arduinolibraries.info/libraries/vector
#include <iostream>
#include <string>

#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <stdlib.h>



NexPage page1 =  NexPage(1, 0, "page1");
NexCrop p1q0 = NexCrop(1, 1, "q0");
NexCrop p1q1 = NexCrop(1, 2, "q1");
NexCrop p1q2 = NexCrop(1, 3, "q2");
NexButton p1b0 = NexButton(1, 4, "b0");
NexButton p1b1 = NexButton(1, 5, "b1");



NexPage page2 = NexPage(2, 0, "page2");
NexText p2t0 = NexText(2, 1, "t0");
NexText p2t1 = NexText(2, 2, "t1");
NexText p2t2 = NexText(2, 3, "t2");
NexButton p2b0 = NexButton(2, 4, "b0");
NexButton p2b1 = NexButton(2, 5, "b1");


NexTouch *nex_listen_list[] = 
{
    &p1q0,
    &p1q1,
    &p1q2,
    &p1b0,
    &p1b1,
    &p2t0,
    &p2t1,
    &p2t2,
    &p2b0,
    &p2b1,
    NULL
};


AudioGeneratorMP3 *mp3;
AudioFileSourceSD *MP3file = NULL;
AudioOutputI2S *out;
AudioFileSourceID3 *id3;

#define DEBUG 1


const uint8_t String01[] = "Password ok!";
const uint8_t String02[] = "Password error!";
const uint8_t String03[] = "Error";

const uint8_t String04[] = "Input number ok!";
const uint8_t String05[] = "Input number error!";

const uint8_t String06[] = "Bach";
const uint8_t String07[] = "Mozart";
const uint8_t String08[] = "Beethoven";


int num_classic, num_pop, num_country;
const char* to_be_printed;
int num_classic_page, num_pop_page, num_country_page;
uint8_t page_before_punching_index;

#define  CMD_MAX_SIZE 255
uint8_t   identifier, cnt;
uint8_t   cmd_buffer[CMD_MAX_SIZE];
uint8_t   data_size;
uint8_t   update_en;
uint8_t   command_cmd;
uint8_t   command_statu;
uint8_t   command_length;
uint8_t   page_Id_bk = 0;
uint8_t   page_Id = 0;
uint8_t   targe_Id = 0;
int       sub_classic_page = 0;
int       sub_pop_page = 0;
int       sub_country_page = 0;
//LiquidCrystal TFTlcd(12);//RST pin13

#define PAGE_LENGTH 600
#define DELAY_SCALE 0.1
#define ELEMENT_COUNT_MAX 1000
#define MAX_LINE_IN_FILE 2000
Vector<String> fileLineContent;
Vector<String> classicFileName;
Vector<String> popFileName;
Vector<String> countryFileName;
Vector<String> allFileName;
String storage_fileLineContent[MAX_LINE_IN_FILE];
String storage_classicArray[ELEMENT_COUNT_MAX];
String storage_popArray[ELEMENT_COUNT_MAX];
String storage_countryArray[ELEMENT_COUNT_MAX];
String storage_allArray[ELEMENT_COUNT_MAX * 3];

char* sysFolder = "System Volume Information";
char* classicFolder = "/Classic/";
char* popFolder = "/Pop/";
char* countryFolder = "/Country/";
char* MIDIstring = ".mp3";
double step = 4.000 / 4096;
char* musicFolder;
volatile bool readI2C_flag = false;
uint8_t playMode = 0;
bool ifPlayMusic = true;
uint8_t index_of_MP3 = 0;
bool playALL = false;
bool stopMusic = false;

void listDir(fs::FS &fs, const char * dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root) {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(fs, file.name(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());

      String nm = file.name();
      String filename;

      if (strstr(nm.c_str(), sysFolder) == NULL && strstr(nm.c_str(), classicFolder) != NULL &&  strstr(nm.c_str(), MIDIstring) != NULL) {
        filename = nm;
        nm = nm.substring(9, nm.indexOf(".mp3"));  //截取/classic/ 和.之前字符串
        classicFileName.push_back(nm);

        allFileName.push_back(filename);
      }
      if (strstr(nm.c_str(), sysFolder) == NULL && strstr(nm.c_str(), countryFolder) != NULL &&  strstr(nm.c_str(), MIDIstring) != NULL) {
        filename = nm;
        nm = nm.substring(9, nm.indexOf(".mp3"));  //截取/country/和.之前字符串

        countryFileName.push_back(nm);

        allFileName.push_back(filename);
      }
      if (strstr(nm.c_str(), sysFolder) == NULL && strstr(nm.c_str(), popFolder) != NULL &&  strstr(nm.c_str(), MIDIstring) != NULL) {
        filename = nm;
        nm = nm.substring(5, nm.indexOf(".mp3"));  //截取/pop/和.之前字符串

        popFileName.push_back(nm);

        allFileName.push_back(filename);
      }
    }
    file = root.openNextFile();
  }
}


void readFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available()) {
    Serial.write(file.read());
  }
  file.close();
}

void readXYfromFile(fs::FS &fs, const char * path) {
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  String line;

  Serial.print("Read from file: ");
  while (file.available()) {
    line += char(file.read());
  }

  file.close();
  Serial.println("=====================================");
  Serial.println(line);
  Serial.println("=====================================");
}

void readFilebyLine(fs::FS &fs, const char * path) {
  //Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }

  //  Serial.print("Read from file: ");
  char buffer[64];
  fileLineContent.clear();
  while (file.available()) {
    int l = file.readBytesUntil('\n', buffer, sizeof(buffer));
    buffer[l] = 0;
    //Serial.println(buffer);
    fileLineContent.push_back(buffer);
  }
  file.close();
}


int currentNum = 0;
int totalNum = 0;
int currentFolder = 0;  //1 - pop  2 - classic  3 country
String p2t0Text="";
String p2t1Text="";
String p2t2Text="";


void p1q0PopCallback(void *ptr)
{
  page2.show();
  dbSerialPrintln("Button b0 is pressed");
  dbSerialPrintln(popFileName[currentNum]);
  dbSerialPrintln(popFileName[currentNum+1]);
  dbSerialPrintln(popFileName[currentNum+2]);
  p2t0Text = popFileName[currentNum];
  p2t1Text = popFileName[currentNum+1];
  p2t2Text = popFileName[currentNum+2];
  p2t0.setText(p2t0Text.c_str());
  p2t1.setText(p2t1Text.c_str());
  p2t2.setText(p2t2Text.c_str());
  sub_pop_page = 0;
  musicFolder = "/Pop/"; 

}


void p1q1PopCallback(void *ptr)
{
  page2.show();
  p2t0Text = classicFileName[0];
  p2t1Text = classicFileName[1];
  p2t2Text = classicFileName[2];
  p2t0.setText(p2t0Text.c_str());
  p2t1.setText(p2t1Text.c_str());
  p2t2.setText(p2t2Text.c_str());
  sub_classic_page = 0;
  musicFolder = "/Classic/";
}

void p1q2PopCallback(void *ptr)
{
  page2.show();
  p2t0Text = countryFileName[0];
  p2t1Text = countryFileName[1];
  p2t2Text = countryFileName[2];
  p2t0.setText(p2t0Text.c_str());
  p2t1.setText(p2t1Text.c_str());
  p2t2.setText(p2t2Text.c_str());
  sub_country_page = 0;
  musicFolder = "/Country/";
}

void p1b3PopCallback(void *ptr)
{
 

  
}

void p1b4PopCallback(void *ptr)
{
  
}



void p2t0PopCallback(void *ptr)
{
  char tempN[100];
  const char* musicFile;
  double volume;
  sprintf(tempN, "%s%s\.mp3", musicFolder, p2t0Text.c_str());
  musicFile = tempN;
  dbSerialPrintln(p2t0Text);
  dbSerialPrintln(musicFile);
  MP3file = new AudioFileSourceSD(musicFile);  
  mp3->begin(MP3file, out);
  
}

void p2t1PopCallback(void *ptr)
{
  char tempN[100];
  const char* musicFile;
  double volume;
  sprintf(tempN, "%s%s\.mp3", musicFolder, p2t1Text.c_str());
   musicFile = tempN;
  dbSerialPrintln(p2t1Text);
  dbSerialPrintln(musicFile);
  MP3file = new AudioFileSourceSD(musicFile);
  mp3->begin(MP3file, out);
}

void p2t2PopCallback(void *ptr)
{
   char tempN[100];
  const char* musicFile;
  double volume;
  sprintf(tempN, "%s%s\.mp3", musicFolder, p2t2Text.c_str());
  musicFile = tempN;
  dbSerialPrintln(p2t2Text);
  dbSerialPrintln(musicFile);
  MP3file = new AudioFileSourceSD(musicFile);


  mp3->begin(MP3file, out);
  
}

void p2b0PopCallback(void *ptr)
{  
  dbSerialPrintln("last page button is pressed");
  if(strstr(musicFolder,popFolder)!= NULL)
  {
    
    sub_pop_page--;
    if(sub_pop_page <0) sub_pop_page=0;
    dbSerialPrintln(sub_pop_page);
    

    p2t0Text = popFileName[sub_pop_page * 3 ];
    p2t1Text = popFileName[sub_pop_page * 3 +1];
    p2t2Text = popFileName[sub_pop_page * 3 +2];
  }
  else if(strstr(musicFolder,classicFolder)!= NULL)
  {
    sub_classic_page--;
    if(sub_classic_page <0) sub_classic_page=0;
    p2t0Text = classicFileName[sub_classic_page * 3 ];
    p2t1Text = classicFileName[sub_classic_page * 3 +1];
    p2t2Text = classicFileName[sub_classic_page * 3 +2];
  }
  else if(strstr(musicFolder,countryFolder)!= NULL)
  {
    sub_country_page--;
    if(sub_country_page <0) sub_country_page=0;
    p2t0Text = countryFileName[sub_country_page * 3 ];
    p2t1Text = countryFileName[sub_country_page * 3 +1];
    p2t2Text = countryFileName[sub_country_page * 3 +2];
  }
  p2t0.setText(p2t0Text.c_str());
  p2t1.setText(p2t1Text.c_str());
  p2t2.setText(p2t2Text.c_str());
}


void p2b1PopCallback(void *ptr)
{
  dbSerialPrintln("next page button is pressed");
   if(strstr(musicFolder,popFolder)!= NULL)
  {
    sub_pop_page++;
    dbSerialPrintln(sub_pop_page);
    if(sub_pop_page >= num_pop_page) sub_pop_page=num_pop_page -1;

    dbSerialPrint("totlal num:");dbSerialPrintln(popFileName.size());
    dbSerialPrint(sub_pop_page * 3 + currentNum);
    if((sub_pop_page * 3 +currentNum+1) < popFileName.size())p2t0Text = popFileName[sub_pop_page * 3];
    if((sub_pop_page * 3 +currentNum+1) < popFileName.size())p2t1Text = popFileName[sub_pop_page * 3 +1];
    if((sub_pop_page * 3 +currentNum+2) < popFileName.size())p2t2Text = popFileName[sub_pop_page * 3 +2];

    dbSerialPrintln(p2t0Text);
  }
  else if(strstr(musicFolder,classicFolder)!= NULL)
  {
    sub_classic_page++;
    if(sub_classic_page >= num_classic_page) sub_classic_page=num_classic_page -1 ;
    if((sub_classic_page * 3 +currentNum) < classicFileName.size())p2t0Text = classicFileName[sub_classic_page * 3 ];
    if((sub_classic_page * 3 +currentNum+1) < classicFileName.size())p2t1Text = classicFileName[sub_classic_page * 3+1];
    if((sub_classic_page * 3 +currentNum+2) < classicFileName.size())p2t2Text = classicFileName[sub_classic_page * 3+2];
  }
  else if(strstr(musicFolder,countryFolder)!= NULL)
  {
    sub_country_page++;
    if(sub_country_page >=num_country_page) sub_country_page=num_country_page -1;
    if((sub_country_page * 3 +currentNum) < countryFileName.size())p2t0Text = countryFileName[sub_country_page * 3 ];
    if((sub_country_page * 3 +currentNum+1) < countryFileName.size())p2t1Text = countryFileName[sub_country_page * 3 +1];
    if((sub_country_page * 3 +currentNum+2) < countryFileName.size())p2t2Text = countryFileName[sub_country_page * 3 +2];
  }
  p2t0.setText(p2t0Text.c_str());
  p2t1.setText(p2t1Text.c_str());
  p2t2.setText(p2t2Text.c_str());
}

void MP3Selsetup()
{
  nexInit();
  dbSerialPrintln("Test begin");
  p1q0.attachPop(p1q0PopCallback);
  p1q1.attachPop(p1q1PopCallback);
  p1q2.attachPop(p1q2PopCallback);
//  p1b3.attachPop(p1b3PopCallback);
//  p1b4.attachPop(p1b4PopCallback);

  p2t0.attachPop(p2t0PopCallback);
  p2t1.attachPop(p2t1PopCallback);
  p2t2.attachPop(p2t2PopCallback);
  p2b0.attachPop(p2b0PopCallback);
  p2b1.attachPop(p2b1PopCallback);
  
  
  //Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  update_en = 0;
  data_size = 0;

  fileLineContent.setStorage(storage_fileLineContent);
  classicFileName.setStorage(storage_classicArray);
  popFileName.setStorage(storage_popArray);
  countryFileName.setStorage(storage_countryArray);
  allFileName.setStorage(storage_allArray);

 // TFTlcd.queue_reset();

  

  audioLogger = &Serial;
  MP3file = new AudioFileSourceSD("/Classic/turkish-march.mp3");

  //  out = new AudioOutputI2S();
  out = new AudioOutputI2S(0, 0, 128);
  out -> SetPinout(26, 25, 27);
  out -> SetGain(0.03 * 80);
  mp3 = new AudioGeneratorMP3();
  
  if (!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }
  uint8_t cardType = SD.cardType();

  if (cardType == CARD_NONE) {
    Serial.println("No SD card attached");
    return;
  }


  Serial.println(F("Paint!"));
  Serial.print("SD Card Type: ");
  if (cardType == CARD_MMC) {
    Serial.println("MMC");
  } else if (cardType == CARD_SD) {
    Serial.println("SDSC");
  } else if (cardType == CARD_SDHC) {
    Serial.println("SDHC");
  } else {
    Serial.println("UNKNOWN");
  }

  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);


  listDir(SD, "/", 2);



  classicFileName.push_back("");
  popFileName.push_back("");
  countryFileName.push_back("");
  num_classic = classicFileName.size();
  num_classic_page = num_classic / 3;
  num_pop = popFileName.size();
  num_pop_page = num_pop / 3;
  num_country = countryFileName.size();
  num_country_page = num_country / 3;

  Serial.printf("Number of classic melodies: %d\n", classicFileName.size());
  for (int i = 0; i < classicFileName.size(); i++) {
    Serial.print("Files are : No.");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(classicFileName[i]);
  }

  Serial.printf("Number of pop melodies: %d\n", popFileName.size());
  for (int i = 0; i < popFileName.size(); i++) {
    Serial.print("Files are : No.");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(popFileName[i]);
  }

  Serial.printf("Number of country melodies: %d\n", countryFileName.size());
  for (int i = 0; i < countryFileName.size(); i++) {
    Serial.print("Files are : No.");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(countryFileName[i]);
  }


  Serial.printf("Sample MP3 playback begins...\n");
  //pinMode(36, INPUT);

  //TFTlcd.SetPage(2);
  //Serial2.println("$X;");
  
}


void MP3Selloop(){
  nexLoop(nex_listen_list);
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop();
    //Serial.println("doing something here");
    delay(10);
  } 
 
}