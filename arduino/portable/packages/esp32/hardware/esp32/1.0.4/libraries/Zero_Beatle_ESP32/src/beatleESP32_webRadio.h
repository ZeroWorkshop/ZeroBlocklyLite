#include "Arduino.h"
#include "WiFi.h"
#include "Audio.h"

// Digital I/O used
#define I2S_DOUT      27  // DIN connection
#define I2S_BCLK      26  // Bit clock
#define I2S_LRC       25  // Left Right Clock

Audio audio;



void webradiosetup(const char* ssid, const char* password, String host) {
    Serial.begin(115200);
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) delay(1500);
    Serial.println("Wifi connected!");
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(21); // 0...21

//    audio.connecttohost("http://www.wdr.de/wdrlive/media/einslive.m3u");
//    audio.connecttohost("http://macslons-irish-pub-radio.com/media.asx");
//    audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.aac"); //  128k aac
//     audio.connecttohost("http://mp3.ffh.de/radioffh/hqlivestream.mp3"); //  128k mp3
//      audio.connecttohost("http://vis.media-ice.musicradio.com/CapitalMP3"); //  128k mp3
//    audio.connecttospeech("Wenn die Hunde schlafen, kann der Wolf gut Schafe stehlen.", "de");
//    audio.connecttohost("http://media.ndr.de/download/podcasts/podcast4161/AU-20190404-0844-1700.mp3"); // podcast
//audio.connecttohost("mms://60.199.213.68/42");
//audio.connecttohost("http://lhttp.qingting.fm/live/1208/64k.mp3");
//audio.connecttohost("http://lhttp.qingting.fm/live/1209/64k.mp3");
//audio.connecttohost("http://lhttp.qingting.fm/live/5021641/64k.mp3");
//audio.connecttohost("http://lhttp.qingting.fm/live/1206/64k.mp3");
//audio.connecttohost("http://tsn.baidu.com/text2audio?lan=zh&ctp=1&cuid=abcdxxx&tok=25.9ee292b3a326087e9b2f4bbf083fbd44.315360000.1919593231.282335-17872447&tex=%E5%90%84%E7%A7%8D%E4%BA%BA%E7%B1%BB%E4%BC%9A%E6%9C%89%E4%B8%8D%E5%90%8C%E7%9A%84%E5%8F%91%E5%B1%95%E5%8E%86%E5%8F%B2&vol=9&per=0&spd=6&pit=5");
audio.connecttohost(host);
}

void webradioloop()
{
    audio.loop();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}