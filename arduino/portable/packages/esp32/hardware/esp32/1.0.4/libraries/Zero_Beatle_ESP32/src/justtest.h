//char URL[1000];
const char* URL;
void speechSynsetup(const char* ssid, const char* password, const char* token, const char *speechtext, int volID, int perID, int spdID, int pitID)
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi");
  Serial.println(speechtext);
  String newstr(speechtext);
  String urlstr;
  //sprintf(URL,"http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=%s&tex=%s&vol=%d&per=%d&spd=%d&pit=%d",token,newstr.c_str(),volID,perID,spdID,pitID);
  urlstr += "http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=";
  urlstr += token;
  //urlstr += "&tex=";
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
  Serial.println(URL);

}


void speechSynloop()
{
  static int lastms = 0;


}
