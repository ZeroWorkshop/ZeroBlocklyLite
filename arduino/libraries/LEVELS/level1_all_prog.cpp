#include   <stdlib.h>
#include   <time.h>

#include "ZeroWorkshop_lib_levelS.h"
#include "ZeroWorkshop_Macro_Definitions.h"

#include <Arduino.h>
//#include <Servo.h>
#include <EEPROM.h>

#define FF  1
#define LL  2
#define RR  3


struct defaultProg {
  int lastProgSelected;
};
static void (*reset_this_CPU)(void) = 0x0000; // ***婵犮垼娉涚粔宕囩礊閸涙潙瀚夐柣婵堢潓U闂佸憡鍨兼慨銈夊汲閻旂厧绠伴柛銉墯鐎氾拷

long StartTime;
bool firstRun = true;

bool KEYPUSH = false; //闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷 婵ǜ鍊ч幏鐑芥閹惧懏瀚�
int COUNT = 0;
int MOVE_MOTOR[100];

int SENSOR_A1 = 0; //A1 闂傚牐顫夐ˉ鍛村礉閿熶粙鎳涜閹凤拷 闂傚绻愰幏鐑芥濞戣櫕瀚� 婵ǜ鍊ч幏鐑芥閹惧懏瀚�
int SENSOR_A2 = 0; //A2 闂傚牐顫夐ˉ鍛村礉閿燂拷
int RANDOM = 0;
int SWINPUT = 0;

int B_RANDOM = 0; //闂傚绻傜�氭挳鎯岄敓锟� 闂傚洦绻冪划鏍х暦娴ｅ啫娈柨鐕傛嫹
signed int GAMESPEED = 1500; //闁烩剝娼欓惌鍛存倵閿燂拷 闂傚牐顕х粔鐓庮嚕閿燂拷 閻熸瑨娅曢敃銉ヮ焽閹剧懓娈柨鐕傛嫹
int GAMEFALE = 5; //闂傚闄嶉崐锝囦焊閿燂拷 闂傚鐗忛崰娑㈠垂閿燂拷
int istep = 0; //7闂傚棛鈷堥悡鍐兜閿燂拷 闂傚鎷烽柕鍫濈Т楠烇拷

void on(int zwB1) {
  digitalWrite(zwB1, HIGH);
}

void on(int zwB1, int zwB2) {
  digitalWrite(zwB1, HIGH);
  digitalWrite(zwB2, HIGH);
}

void on(int zwB1, int zwB2, int zwB3) {
  digitalWrite(zwB1, HIGH);
  digitalWrite(zwB2, HIGH);
  digitalWrite(zwB3, HIGH);

}

void on(int zwB1, int zwB2, int zwB3, int zwB4) {
  digitalWrite(zwB1, HIGH);
  digitalWrite(zwB2, HIGH);
  digitalWrite(zwB3, HIGH);
  digitalWrite(zwB4, HIGH);
}

void off(int zwB1) {
  digitalWrite(zwB1, LOW);
}

void off(int zwB1, int zwB2) {
  digitalWrite(zwB1, LOW);
  digitalWrite(zwB2, LOW);
}

void off(int zwB1, int zwB2, int zwB3) {
  digitalWrite(zwB1, LOW);
  digitalWrite(zwB2, LOW);
  digitalWrite(zwB3, LOW);

}

void off(int zwB1, int zwB2, int zwB3, int zwB4) {
  digitalWrite(zwB1, LOW);
  digitalWrite(zwB2, LOW);
  digitalWrite(zwB3, LOW);
  digitalWrite(zwB4, LOW);
}

void default_prog(int *ProgSelected) {
  defaultProg lastRunProg;

  int eepromAddr = eeAddr_LEVEL1_DEFAULT_PROG;

  EEPROM.get(eepromAddr, lastRunProg);

  (*ProgSelected) = lastRunProg.lastProgSelected;

}
bool inputButtonPushed = false;
bool LedOnState = false;

void lesson_1_interrupt() {

  playSong(3);
  /*
    if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3) || isLow(ZW_A4)) { //
    inputButtonPushed = true;
    }
    if (!inputButtonPushed) {
    if (millis() - StartTime < 100) {
      on(ZW_B1, ZW_B2, ZW_B3, ZW_B4);    // LED1,2,3 ON
      //      StartTime = millis();
    }
    else if (millis() - StartTime < 200) {
      off(ZW_B1, ZW_B2, ZW_B3, ZW_B4);    // LED1,2,3 ON
      //      StartTime = millis();
    }
    else
      StartTime = millis();
    //    delay(100);
    //    off(ZW_B1, ZW_B2, ZW_B3);   // LED1,2,3 OFF
    //    delay(100);
    }
  */
}
void lesson_1() {
  //  if (!inputButtonPushed) {
  //    on(ZW_B1, ZW_B2, ZW_B3);		// LED1,2,3 ON
  //    delay(100);
  //    off(ZW_B1, ZW_B2, ZW_B3);		// LED1,2,3 OFF
  //    delay(100);
  //  }
  if (!inputButtonPushed) {
    if (millis() - StartTime < 100) {
      on(ZW_B1, ZW_B2, ZW_B3, ZW_B4);    // LED1,2,3 ON
      //      StartTime = millis();
    }
    else if (millis() - StartTime < 200) {
      off(ZW_B1, ZW_B2, ZW_B3, ZW_B4);    // LED1,2,3 ON
      //      StartTime = millis();
    }
    else
      StartTime = millis();
  }

  if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3) || isLow(ZW_A4)) { //
    inputButtonPushed = true;

    if (isLow(ZW_A1)) {
      on(ZW_B1);
      Left_Motor(FORWARD);
      Right_Motor(STOP);
    }

    if (isLow(ZW_A2)) {
      on(ZW_B2);
      Left_Motor(BACKWARD);
      Right_Motor(STOP);
    }

    if (isLow(ZW_A3)) {
      on(ZW_B3);
      Left_Motor(STOP);
      Right_Motor(FORWARD);
    }

    if (isLow(ZW_A4)) {
      on(ZW_B4);
      Left_Motor(STOP);
      Right_Motor(BACKWARD);
    }
  }
  else {
    if (isHigh(ZW_A1)) {
      off(ZW_B1);
      Left_Motor(STOP);
    }
    if (isHigh(ZW_A2)) {
      off(ZW_B2);
      Left_Motor(STOP);
    }
    if (isHigh(ZW_A3)) {
      off(ZW_B3);
      Right_Motor(STOP);
    }
    if (isHigh(ZW_A4)) {
      off(ZW_B4);
      Right_Motor(STOP);
    }
  }


}

void lesson_2() {
  if (firstRun) {
    StartTime = millis();
    firstRun = false;
    Left_Motor(FORWARD);
    Right_Motor(FORWARD);
  }

  if (millis() - StartTime < 2000)				//2濠碘剝鎷濋幏锟� 闂佺鑻悧鎾舵兜閹间焦鍎婇柨鐕傛嫹 闂佸憡蓱瀹�绋款焽濮樿泛绠ラ柨鐕傛嫹 闂佸搫鐗婄换锟藉ù婊愭嫹 濠电偛琚崕闈涒枖濞嗘挸纾奸柨鐕傛嫹
  {
    on(ZW_B1, ZW_B2);
    off(ZW_B3);
    Right_Motor(BACKWARD);					//闂佸憡蓱瀹�绋款焽濮樿泛绠ラ柨鐕傛嫹 闂佹垝鐒︾粙鎾凰夐敓锟� 閻庢鍣幏鐑芥⒒閸☆厽瀚归梺绋跨焿閹凤拷
    //melody(timer_read()*500);		//缂傚倸娲﹀Λ渚�宕戦妶澶婄煑闁跨噦鎷� 濠电媭婢侀幏锟� = 闂佹椿鍙庨崑鍕倿閿燂拷 * 500
    playNote(e5, sixteenthNote, meters_x1);
  }
  else if (millis() - StartTime < 3000)			//3濠碘剝鎷濋幏锟� 闂佺鑻悧鎾舵兜閹间焦鍎婇柨鐕傛嫹 闂佸憡蓱瀹�绋款焽濮樿泛绠ラ柨鐕傛嫹 闂佸搫鐗婄换锟藉ù婊愭嫹 閻庢鍣幏鐑芥⒒閸☆厽瀚归梺绋跨焿閹凤拷
  {
    off(ZW_B1, ZW_B2);
    on(ZW_B3);
    Right_Motor(FORWARD);						//闂佸憡蓱瀹�绋款焽濮樿泛绠ラ柨鐕傛嫹 闂佹垝鐒︾粙鎾凰夐敓锟� 濠电偛琚崕闈涒枖濞嗘挸纾奸柨鐕傛嫹
    //melody(timer_read()*500);		//缂傚倸娲﹀Λ渚�宕戦妶澶婄煑闁跨噦鎷� 濠电媭婢侀幏锟� = 闂佹椿鍙庨崑鍕倿閿燂拷 * 500
    playNote(g5, sixteenthNote, meters_x1);
  }
  else								//3濠碉紕铏庨崜姘暦椤掑嫬绠氶柟瀵稿仜閼稿綊鏌熺涵閿嬪 闁荤姵鍔曢幉锛勬閼稿灚濯撮柡鍥╁濡拷 婵烇絽娲ら崯浼存偂閿燂拷
  {
    StartTime = millis(); //timer(0);						//闂佺厧顫曢崐鎾寸椤掑倸顥氶柨鐕傛嫹 婵°倧璐熼崕鎻掔暦椤掑倹灏庨柨鐕傛嫹 闂佸憡妫忔禍婊呰姳閼姐倗纾奸柨鐕傛嫹
    //melody(0);						//缂傚倸娲﹀Λ渚�宕戦妶澶婄煑闁跨噦鎷� 濠电偛琚崕鍐参ｉ敓锟�

  }

}

void motor(int Left_speed, int Right_speed, double delayT) {
  if (Left_speed < 0)
    LeftWheelBackward_SpeedControl(abs(Left_speed));
  else if (Left_speed >= 0)
    LeftWheelForward_SpeedControl(Left_speed);

  if (Right_speed < 0)
    RightWheelBackward_SpeedControl(abs(Right_speed));
  else if (Right_speed >= 0)
    RightWheelForward_SpeedControl(Right_speed);

  delay(delayT);

  LeftWheelBackward_SpeedControl(0);
  RightWheelBackward_SpeedControl(0);

}

void lesson_3() {
  if (isLow(ZW_A1))
  {
    //motor(-20,-20,300);			//闁瑰吋瀵х划鏍閿燂拷 闂傚顦�氱敻锝為敓锟�
    motor(-200, -200, 300);
    //motor(20,-20,100);			//闁瑰吋瀵х划鏍閿燂拷 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹
    motor(200, -200, 100);
  }
  else if (isLow(ZW_A2))						//闂傚鎸堕崐鐘诲Χ閹间緡妫楅柨鐕傛嫹 婵ǚ鏅滃Λ搴＄暤閹剧懓娈柨鐕傛嫹 闂傚棛鍘ч幓鈺呭疾閸ф浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
  {
    //motor(-20,-20,300);			//闁瑰吋瀵х划鏍閿燂拷 闂傚顦�氱敻锝為敓锟�
    motor(-200, -200, 300);
    //motor(-20,20,100);			//闁瑰吋瀵х划鏍閿燂拷 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹
    motor(-200, 200, 100);
  }
  else							//婵ǚ鏅滃Λ搴＄暤閹剧懓娈柨鐕傛嫹 婵ê娴傞悡鍕箟閿燂拷 闂傚棛鍘ч幓鈺咃綖閿燂拷 闂傚楠搁…顏堝疾閸ф浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
  {
    //wheel(20,20);				//闁瑰吋瀵х划鏍閿燂拷 闂傚绻傜�氱敻锝為敓锟�
    goForward();
  }
}

void lesson_4() {
  COUNT = 0;						//闁哄啫鍟亸妤�袙濮樺墎鍚橀柨鐕傛嫹 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
  KEYPUSH = false;					//闂傚鍔婇崐鐘诲垂婵犲喚鍤ラ柨鐕傛嫹 闂傚鍊搁惌鍕偉閵堝棙鏆ラ柨鐕傛嫹 濮掔粯鍨甸悧鏃傛導绾惧娈柨鐕傛嫹 FALSE
  //timer(0);						//闂傚牆顨庨崜锝呅掗崟顖滀邯闁跨噦鎷� 闂傚鍣幏鐑芥濮橆厼濡囬懣锟� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
  StartTime = millis();
  while (1)						//婵ê绉归弫濠囧汲閸涱喚姣ｆ慨妤�鍊藉┃锟�
  {
    if (isLow(ZW_A3))						//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 3婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷
    {
      //melody(do5);
      playNote(c5, sixteenthNote, meters_x1);
      if (COUNT != 99)	COUNT++;	//闁哄啫鍟亸妤�袙濮樺墎鍚樺Δ锕佹椤拷 99闁哄喚鍨伴惌鍛达綖閿燂拷 闂傚绻愰幏鐑芥濞戞牕鍔伴柡鍡嫹 闂傚牊鎷濋幏锟� 闂傚绋戦悧妤�顭囬敓锟�

      while (isLow(ZW_A3));					//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 3婵ǚ鏅涢悧妤�顭块敓锟� 闂傚楠搁…鈺呭垂閺嶎厽鑰块柨鐔剁矙閻忓洭鏁撻敓锟� 闂傚洦鍨甸惌鍐不閵堝棛鎼搁柨鐕傛嫹 闁哄喚鍠栧畷鎰拷姘卞枑椤曟煡鏁撻敓锟�
      //melody(0);					//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
      delay(100);
      while (isLow(ZW_A3));
      KEYPUSH = true;				//闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕偋閹剁晫浜為柤浣冲懏顫岄柟鐓庡皡閹凤拷 TRUE闂傚绻愰幏鐑芥濞戣櫕瀚�
      //timer(0);					//闂傚牆顨庨崜锝呅掗崟顖滀邯闁跨噦鎷� 闁哄啫鍟亸妤�顭挎繝鍐惧殸闁跨噦鎷� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
      StartTime = millis();
    }
    if ((KEYPUSH == true) && (millis() - StartTime > 2000)) //闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亷闁烩�冲皡閹凤拷 2濮掔粯鍨甸悧鏇°亹婵犲洨锟藉鏁撻敓锟� 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚楠搁…顏勨攦閸屾稓娈归柨鐕傛嫹 婵ê绉归弫濠囧汲閸涘府鎷烽崟鐢靛帣闁猴拷閿燂拷 闁绘绉舵繛瀣偋閿燂拷 闂傚棭鍠楅敃銉ノｉ敓锟�
    {
      break;
    }
  }

  //play(do6,n32);play(mi6,n32);play(sol6,n32);play(do7,n32);
  playNote(c6, sixteenthNote, meters_x1);
  playNote(e6, sixteenthNote, meters_x1);
  playNote(g6, sixteenthNote, meters_x1);
  playNote(c7, sixteenthNote, meters_x1);

  for (int i = 0; i < COUNT; i++)					//闂傚鐓夐幏锟� 闂傚棛顭堢�氭挳銆呴敓锟� 闂傚牏铏庨崑鎰版倵閿燂拷 婵綁娼ч惌鍥ㄥ閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
  {
    //motor(20,20,500);					//婵ê娴傞悡鍥礉閿燂拷 闂傚绻傜�氱敻锝為敓锟� 0.5濮掔粯鍩婇幏锟�
    motor(200, 200, 580);
  }
  //play(do6,n8);							//闁艰绠戦幊鐐核夐幋锔句海闁跨噦鎷�
  playNote(c6, quaterNote, meters_x1);
}


void lesson_5() {
  COUNT = 0;						//闁哄啫鍟亸妤�袙濮樺墎鍚橀柨鐕傛嫹 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
  KEYPUSH = false;					//闂傚鍔婇崐鐘诲垂婵犲喚鍤ラ柨鐕傛嫹 闂傚鍊搁惌鍕偉閵堝棙鏆ラ柨鐕傛嫹 濮掔粯鍨甸悧鏃傛導绾惧娈柨鐕傛嫹 FALSE
  //timer(0);						//闂傚牆顨庨崜锝呅掗崟顖滀邯闁跨噦鎷� 闂傚鍣幏鐑芥濮橆厼濡囬懣锟� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
  StartTime = millis();
  while (1)						//婵ê绉归弫濠囧汲閸涱喚姣ｆ慨妤�鍊藉┃锟�
  {
    if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3))				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1,2,3婵ǚ鏅涢悧妤�顭块敓锟� 闂傚鍟敃銈夊磹閸洘绠块柤浣冲啫寮� 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷
    {
      if (isLow(ZW_A1))					//闂傚娲橀ˉ鍛搭敁閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷
      {
        //melody(do5);				//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
        playNote(c5, quaterNote, meters_x1);
        MOVE_MOTOR[COUNT] = LL;		//闂傚绻傜�氱敻锝為敓锟� 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      else if (isLow(ZW_A2))						//闂傚鎸堕崐鐘诲Χ閹间緡妫楅柨鐕傛嫹 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 2婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷
      {
        //melody(mi5);				//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
        playNote(e5, quaterNote, meters_x1);
        MOVE_MOTOR[COUNT] = RR;		//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      else if (isLow(ZW_A3))
      {
        //melody(sol5);				//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
        playNote(g5, quaterNote, meters_x1);
        MOVE_MOTOR[COUNT] = FF;		//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      if (COUNT != 99)	COUNT++;		//闁哄啫鍟亸妤�袙濮樺墎鍚樺Δ锕佹椤拷 99闁哄喚鍨伴惌鍛达綖閿燂拷 闂傚绻愰幏鐑芥濞戞牕鍔伴柡鍡嫹 闂傚牊鎷濋幏锟� 闂傚绋戦悧妤�顭囬敓锟�

      while (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3));					//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1,2婵ǚ鏅涢悧妤�顭块敓锟� 闂傚洤锕ラ敃銈囷拷姘炬嫹 闂傚楠搁…鈺呭垂閺嶎厽鑰块柨鐔剁矙閻忓洭鏁撻敓锟� 闂傚洦鍨甸惌鍐不閵堝棛鎼搁柨鐕傛嫹 闁哄喚鍠栧畷鎰拷姘卞枑椤曟煡鏁撻敓锟�
      //melody(0);						//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
      delay(50);
      while (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3));
      KEYPUSH = true;					//闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕偋閹剁晫浜為柤浣冲懏顫岄柟鐓庡皡閹凤拷 TRUE闂傚绻愰幏鐑芥濞戣櫕瀚�
      //timer(0);						//闂傚牆顨庨崜锝呅掗崟顖滀邯闁跨噦鎷� 闁哄啫鍟亸妤�顭挎繝鍐惧殸闁跨噦鎷� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
      StartTime = millis();
    }
    if ((KEYPUSH == true) && (millis() - StartTime > 2000)) //闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亷闁烩�冲皡閹凤拷 2濮掔粯鍨甸悧鏇°亹婵犲洨锟藉鏁撻敓锟� 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚楠搁…顏勨攦閸屾稓娈归柨鐕傛嫹 婵ê绉归弫濠囧汲閸涘府鎷烽崟鐢靛帣闁猴拷閿燂拷 闁绘绉舵繛瀣偋閿燂拷 闂傚棭鍠楅敃銉ノｉ敓锟�
    {
      break;
    }
  }
  //play(do5,n32);play(mi5,n32);play(sol5,n32);play(do6,n32); //闂傚洤鍟悷顒勬倵妤ｅ啰浜ｉ柨鐕傛嫹
  playNote(c5, sixteenthNote, meters_x1);
  playNote(e5, sixteenthNote, meters_x1);
  playNote(g5, sixteenthNote, meters_x1);
  playNote(c6, sixteenthNote, meters_x1);

  for (int i = 0; i < COUNT; i++)					//闂傚鐓夐幏锟� 闂傚棛顭堢�氭挳銆呴敓锟� 闂傚牏铏庨崑鎰版倵閿燂拷 婵綁娼ч惌鍥ㄥ閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
  {
    motor(0, 0, 50);						//婵ê娴傞悡鍥礉濞嗘挾浜伴柡鍥ュ労濞硷拷
    if (MOVE_MOTOR[i] == FF)				//闂傚绻傜�氱敻锝為敓锟� 闂傚纰嶉崹鎰版儍閿燂拷?
    {
      //motor(20,20,500);				//婵ê娴傞悡鍥礉閿燂拷 闂傚绻傜�氱敻锝為敓锟� 0.5濮掔粯鍩婇幏锟�
      motor(200, 200, 500);
    }
    else if (MOVE_MOTOR[i] == LL)			//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 闂傚纰嶉崹鎰版儍閿燂拷?
    {
      //motor(-20,20,100);				//婵ê娴傞悡鍥礉閿燂拷 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 0.1濮掔粯鍩婇幏锟�
      motor(-200, 200, 100);
    }
    else if (MOVE_MOTOR[i] == RR)			//闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹 闂傚纰嶉崹鎰版儍閿燂拷?
    {
      //motor(20,-20,100);				//婵ê娴傞悡鍥礉閿燂拷 闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹 0.1濮掔粯鍩婇幏锟�
      motor(200, -200, 100);
    }
    motor(0, 0, 50);						//婵ê娴傞悡鍥礉濞嗘挾浜伴柡鍥ュ労濞硷拷

  }
  //play(do6,n8);							//闁艰绠戦幊鐐核夐幋锔句海闁跨噦鎷�
  playNote(c6, quaterNote, meters_x1);
}

void lesson_6() {
  if (firstRun) {
    StartTime = millis();
    firstRun = false;
  }
  if (isLow(ZW_A1) && isLow(ZW_A2))						//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1,2婵ǚ鏅涢悧妤�顭块敓锟� 闂傚洤锕ラ敃銈囷拷姘炬嫹 闂傚棛顭堥惌鍕亾 闁烩剝娼欓惇鎯掗敓锟�
  {
    //on(B1+B2);					//LED1,2 ON
    on(ZW_B1, ZW_B2);
    //wheel(20,20);				//闁瑰吋瀵х划鏍閿燂拷 闂傚绻傜�氱敻锝為敓锟�
    goForward();
  }
  else if (isLow(ZW_A1))						//闂傚娲橀ˉ鍛搭敁閿燂拷 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亾 闁烩剝娼欓惇鎯掗敓锟�
  {
    on(ZW_B1);						//LED1 ON
    off(ZW_B2);					//LED2 OFF
    //wheel(0,20);				//闂傚绻傜�氱敻锝為敓锟� 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 闂傚洤鍟悷顒勬倵閿燂拷
    goLeftTurn();
  }
  else if (isLow(ZW_A2))						//闂傚鎸堕崐鐘诲Χ閹间緡妫楅柨鐕傛嫹 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亾 闁烩剝娼欓惇鎯掗敓锟�
  {
    on(ZW_B2);						//LED2 ON
    off(ZW_B1);					//LED1 OFF
    //wheel(20,0);				//闂傚绻傜�氱敻锝為敓锟� 闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹 闂傚洤鍟悷顒勬倵閿燂拷
    goRightTurn();
  }
  else							//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚楠搁…顏勵焽閿燂拷 闁烩剝娼欓惇鎯掗敓锟�
  {
    //off(B1+B2);					//LED1,2 OFF
    off(ZW_B1, ZW_B2);
    //wheel(0,0);					//闁瑰吋瀵х划鏍閿燂拷 闂傚绻冨ú銏わ綖閿燂拷
    goBrake();
  }

  if (millis() - StartTime < 100)			//闂傚鍣幏鐑芥濮橆厼濡囬懣褔鎳涜閹凤拷 0.1濮掔粯鍨甸悧妤呮偉閻樿崵浜ｉ柟渚簴閺�锟�
  {
    on(ZW_B3);						//LED3 ON
    //melody(timer_read()*600);	//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闂傚鐔幏锟� = 闂傚鍣幏鐑芥濮橆厼濡囬懣锟� * 600
    playNote(c5, sixteenthNote, meters_x1);
  }
  else if (millis() - StartTime < 200)		//闂傚鍣幏鐑芥濮橆厼濡囬懣褔鎳涜閹凤拷 0.2濮掔粯鍨甸悧妤呮偉閻樿崵浜ｉ柟渚簴閺�锟�
  {
    off(ZW_B3);					//LED3 OFF
    //melody(timer_read()*600);	//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闂傚鐔幏锟� = 闂傚鍣幏鐑芥濮橆厼濡囬懣锟� * 600
    playNote(g5, sixteenthNote, meters_x1);
  }
  else							//闂傚鍣幏鐑芥濮橆厼濡囬懣褔鎳涜閹凤拷 0.2濮掔粯鍩婇幏锟� 闂傚宀搁弫濠傗枖閻斿吋绠块柤浣筹拷閺�锟�
  {
    //timer(0);					//闂傚牆顨庨崜锝呅掗崟顖滀邯闁跨噦鎷� 闂傚鍣幏鐑芥濮橆厼濡囬懣锟� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
    StartTime = millis();
    //melody(0);					//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闂傚绻冨ú銏わ綖閿燂拷
  }

}


void lesson_7() {
  if (firstRun) {
    SENSOR_A1 = analogRead(ZW_A1);
    SENSOR_A2 = analogRead(ZW_A2);
    firstRun = false;
    Serial.print("A1 value:");
    Serial.println(SENSOR_A1);
    Serial.print("A2 value:");
    Serial.println(SENSOR_A2);
  }
  while (1)								//婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
  {
    if (isLow(ZW_A3))								//闂傚洤顑囩槐鎶筋敁閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
    {
      for (int i = 0; i < 5; i++)				//5婵ǚ鏅幏锟� 婵ɑ纰嶉敃銈嗘姜閿燂拷
      {
        //motor(20,-20,100);			//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 0.1濮掔粯鍩婇幏锟�
        motor(200, -200, 100);
        //motor(-20,20,100);			//闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹 0.1濮掔粯鍩婇幏锟�
        motor(-200, 200, 100);
      }
      //play(do6,n16);play(ci5,n16);play(ra5,n16);play(sol5,n16);play(pa5,n16);play(mi5,n16);play(re5,n16);play(do5,n16);
      playNote(c6, sixteenthNote, meters_x1);
      playNote(b5, sixteenthNote, meters_x1);
      playNote(a5, sixteenthNote, meters_x1);
      playNote(g5, sixteenthNote, meters_x1);
      playNote(f5, sixteenthNote, meters_x1);
      playNote(e5, sixteenthNote, meters_x1);
      playNote(d5, sixteenthNote, meters_x1);
      playNote(c5, sixteenthNote, meters_x1);

      delay(5000);
      break;							//闂傚绻傜�氶潧鈻旈敓锟� 婵ê绉归弫濠囧汲閿燂拷 闁兼澘瀚烽悡鍥绩閿燂拷 闁绘绉舵繛瀣偋閿燂拷 闂傚棭鍠楅敃銉ノｉ敓锟�
    }
    else if (analogRead(ZW_A1) < (SENSOR_A1 - 50))			//闂傚绻傜�氭挳鎯傞敓锟� 闂傚绻�缁剁喎鈻嶉姀銈嗙番闁绘鍋撻ˉ锟� 婵ê绉甸ˉ鍛枖婵犲懎娈柨鐕傛嫹 闁艰垂鍕Б妞ゎ偄鎳樺〒钘夘潨閸屾鏁�
    {
      //on(B1+B2);						//LED1,2 ON
      on(ZW_B1, ZW_B2);
      //motor(-20,-20,500);				//闂傚顦�氱敻锝為敓锟� 0.2濮掔粯鍩婇幏锟�
      motor(-200, -200, 500);
      //motor(-20,20,400);				//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 0.4濮掔粯鍩婇幏锟�
      motor(-200, 200, 400);
      //off(B1+B2);
      off(ZW_B1, ZW_B2);
    }
    else if (analogRead(ZW_A2) > (SENSOR_A2 + 50))			//婵ɑ纰嶅Λ鍛拷姘炬嫹 闂傚绻�缁剁喎鈻嶉姀銈嗙番闁绘鍋愬▓锟� 闂傚棭鍣崣鍛村几閸ф锟藉ジ骞愰顐ｇ秱婵絿顒查幏锟� 闁艰垂鍕Б妞ゎ偄鎳橀悥鐔奉潨閸屾鏁�
    {
      //on(B1+B2);						//LED1,2 ON
      on(ZW_B1, ZW_B2);
      //motor(-20,-20,500);				//闂傚顦�氱敻锝為敓锟� 0.2濮掔粯鍩婇幏锟�
      motor(-200, -200, 500);
      //motor(-20,20,400);				//闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹 0.4濮掔粯鍩婇幏锟�
      motor(-200, 200, 400);
      //off(B1+B2);
      off(ZW_B1, ZW_B2);
    }
    else								//闂傚牐顫夐ˉ鍛村礉閿燂拷 闁艰垂鍕Б妞ゎ偄鎳撻崵娆撴晸閿燂拷 闂傚鍔曞Λ锕�鈹冮崒娑氭闁跨噦鎷�
    {
      //wheel(20,20);					//闁瑰吋瀵х划鏍閿燂拷 闂傚绻傜�氱敻锝為敓锟�
      goForward();
    }
  }
}

int user_random(int range) {
  int random_data;
  int a = 1;
  int b = range;
  srand((unsigned)millis());
  //  Serial.println(rand() % range);
  random_data = (rand() % (b - a + 1)) + a;
  return random_data;
}

void lesson_8() {

  if (firstRun) {
    //motor(20,-20,1000);          //闂傚楠搁幊銏ゅ蓟閿燂拷
    motor(-200, -200, 1000);
    RANDOM = user_random(30) + 1; //闂傚洦绻冪划鏍х暦娴ｅ啫娈柨鐕傛嫹 2~31
    on(ZW_B1, ZW_B2, ZW_B3);       //LED1,2,3 婵ê娴傞悡鍕箟閿燂拷 ON
    firstRun = false;
  }

  while (1)							//婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
  {
    if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3))					//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1,2,3 婵炲棗鍤栭幏锟� 闂傚鍟敃銈夊磹閸洘绠块柤浣冲啫寮� 闂傚棛顭堥惌鍕亷婵ê鎷戦幏锟�
    {
      //melody(ci7);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 闂傚棛顭堥惌鍕�栭敓锟� 婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
      playNote(b7, sixteenthNote, meters_x1);
      if (isLow(ZW_A1))						//1婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
      {
        off(ZW_B1);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED1 OFF
        SWINPUT |= 0x01;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 1婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      else if (isLow(ZW_A2))					//2婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
      {
        off(ZW_B2);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 2婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED2 OFF
        SWINPUT |= 0x02;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 2婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      else if (isLow(ZW_A3))					//3婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
      {
        off(ZW_B3);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 3婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED3 OFF
        SWINPUT |= 0x04;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 3婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
      }
      delay(20);					//闂傚娴烽弸濂告儍閻樿崵浜ｉ柨鐕傛嫹 闂傚洦鍔栫划鏍偉閵堝浜ｉ柨鐕傛嫹
      while (1)					//婵ê娴傞悡鍕箺閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚楠搁…鈺呭垂閺嶎厽鑰块柤瀹犳珪缂嶏拷 闂傚洦鍨甸惌鍐不閵堝棛鎼搁柨鐕傛嫹 婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
      {
        if (isHigh(ZW_A1) && isHigh(ZW_A2) && isHigh(ZW_A3))
        {
          //melody(0);			//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
          delay(20);			//闂傚娴烽弸濂告儍閻樿崵浜ｉ柨鐕傛嫹 闂傚洦鍔栫划鏍偉閵堝浜ｉ柨鐕傛嫹
          break;
        }
      }
      if (SWINPUT == 0x07)			//婵ê娴傞悡鍕箺閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚棛銆嬮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟� 闂傚棛顑曢崐銏狀焽閿燂拷 闂傚棛鈷堥悡鍐兜閻樿櫕鍎堕柨鐕傛嫹
      {
        //play(do5,n16);play(re5,n16);play(mi5,n16);	//闂傚棛顑曢崐銏狀焽閿燂拷 闂傚棛鈷堥悡鍐兜閿燂拷 闂傚鎼╅崜銏狀熆閺団�虫闁跨喍绮欏ù鏇㈡晸閿燂拷 婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
        playNote(c5, sixteenthNote, meters_x1);
        playNote(d5, sixteenthNote, meters_x1);
        playNote(e5, sixteenthNote, meters_x1);
        break;
      }

    }
  }


  while (1)
  {
    RANDOM = user_random(30) + 1;			//闂傚洦绻冪划鏍х暦娴ｅ啫娈柨鐕傛嫹 1~30
    //on(B1+B2+B3);						//LED1,2,3 婵ê娴傞悡鍕箟閿燂拷 ON
    on(ZW_B1, ZW_B2, ZW_B3);
    SWINPUT = 0;							//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 闂傚绋戦幊鐐烘偋閿燂拷 婵ǜ鍊ч幏鐑芥閹惧懏瀚� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
    COUNT = 0;							//闁哄啫鍟亸妤�袙濮樺墎鍙為柣鈽呯悼濮ｏ拷 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
    while (1)							//婵ɑ菧閸婏綁寮抽崨顔炬婵鍊藉┃锟�
    {
      if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3))					//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1,2,3 婵炲棗鍤栭幏锟� 闂傚鍟敃銈夊磹閸洘绠块柤浣冲啫寮� 闂傚棛顭堥惌鍕亷婵ê鎷戦幏锟�
      {
        //melody(ci7);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 闂傚棛顭堥惌鍕�栭敓锟� 婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷

        if (isLow(ZW_A1))						//1婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
        {
          off(ZW_B1);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 1婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED1 OFF
          SWINPUT |= 0x01;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 1婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
        }
        else if (isLow(ZW_A2))					//2婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
        {
          off(ZW_B2);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 2婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED2 OFF
          SWINPUT |= 0x02;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 2婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
        }
        else if (isLow(ZW_A3))					//3婵ǚ鏅幏锟� 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
        {
          off(ZW_B3);				//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 3婵ǚ鏅涢悧妤�螞閿燂拷 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED3 OFF
          SWINPUT |= 0x04;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閻愵剨鏀绘俊顐嫹 3婵ǚ鏅涢悧妤�顭块敓锟� 闂傚棛顭堥惌鍕偋閹惰姤绂嗛柕鍫濐儏椤拷 闁艰垂宥嗗 闂傚绻愰幏鐑芥濞戣櫕瀚�
        }
        playNote(b7, sixteenthNote, meters_x1);
        delay(20);					//闂傚娴烽弸濂告儍閻樿崵浜ｉ柨鐕傛嫹 闂傚洦鍔栫划鏍偉閵堝浜ｉ柨鐕傛嫹
        while (1)					//婵ê娴傞悡鍕箺閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚楠搁…鈺呭垂閺嶎厽鑰块柤瀹犳珪缂嶏拷 闂傚洦鍨甸惌鍐不閵堝棛鎼搁柨鐕傛嫹 婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
        {
          if (isHigh(ZW_A1) && isHigh(ZW_A2) && isHigh(ZW_A3))
          {
            //melody(0);			//婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
            delay(20);			//闂傚娴烽弸濂告儍閻樿崵浜ｉ柨鐕傛嫹 闂傚洦鍔栫划鏍偉閵堝浜ｉ柨鐕傛嫹
            break;
          }
        }
        ++COUNT;					//闁哄啫鍟亸妤�袙濮樺墎鍙為柨鐕傛嫹 婵繂鍟换澶愭儍閿燂拷
        if (COUNT != RANDOM)			//闂傚洦绻冪划鏍х暦娴ｅ啫娈柟鐑樼懆閸わ拷 闂傚棛顑曢崐鐘诲Χ閹绢喗绂嗛柕鍫濐儌閺�锟�
        {
          if (SWINPUT == 0x07)		//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 3闁艰垂鍕煋闁活煉鎷� 闂傚棛銆嬮幏锟� 闂傚棛顭堥惌鍕偋閹剁晫浜為柤浣筹拷閺�锟�
          {
            SWINPUT = 0;			//闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鎸庡 婵ǜ鍊ч幏鐑芥閹惧懏瀚� 闂傚鍎茬敮鎹愮亷闂傚楠忛幏锟�
            on(ZW_B1, ZW_B2, ZW_B3);		//LED1,2,3 婵ê娴傞悡鍕箟閿燂拷 ON
            //play(do5, n16); play(re5, n16); play(mi5, n16); //
            playNote(c5, sixteenthNote, meters_x1);
            playNote(d5, sixteenthNote, meters_x1);
            playNote(e5, sixteenthNote, meters_x1);
          }
        }
        else						//闁哄啫鍟亸妤�袙濮樺墎鍙為柛鏃傚仦椤庯拷 闂傚洦绻冪划鏍х暦娴ｅ啫娈柟鐑樼♁缁讹拷 闁艰垂鍕噷閻庢氨鍠愰惃锟犳晸閿燂拷 闂傚楠搁幊銏ゅ蓟鎼淬劎浜柨鐕傛嫹 闂傚棛鈷堥崑鎰焽閿燂拷
        {
          //motor(-20, 20, 500);		//闂傚楠搁幊銏ゅ蓟鎼淬劎浜柨鐕傛嫹 闂傚棛銆嬮幏锟�
          motor(-200, 200, 500);    //闂傚鐔幏锟�
          //motor(20, -20, 300); motor(-20, 20, 300); motor(20, -20, 300); motor(-20, 20, 300);	//闂傚楠搁幊銏ゅ蓟鎼淬劎浜柨鐕傛嫹 闂傚鍔栭幃锛勫枈閿燂拷
          motor(200, -200, 300); motor(-200, 200, 300); motor(200, -200, 300); motor(-200, 200, 300);  //闂傚棛鈷堥崑鎰焽閿燂拷
          //play(do6, n16); play(ci5, n16); play(ra5, n16); play(sol5, n16); play(pa5, n16); play(mi5, n16); play(re5, n16); play(do5, n16); 	//闁艰绠戦幊鐐核夐幋锔句海闁跨噦鎷� 闁哄倻銆嬮幏锟�
          playNote(c6, sixteenthNote, meters_x1);
          playNote(b5, sixteenthNote, meters_x1);
          playNote(a5, sixteenthNote, meters_x1);
          playNote(g5, sixteenthNote, meters_x1);
          playNote(f5, sixteenthNote, meters_x1);
          playNote(e5, sixteenthNote, meters_x1);
          playNote(d5, sixteenthNote, meters_x1);
          playNote(c5, sixteenthNote, meters_x1);

          delay(1000);			//1濮掔粯鍨甸悧鏇°亹婵犲洨锟藉鏁撻敓锟� 闂傚洦鍔栫划鏍偉閵堝浜ｉ柨鐕傛嫹
          //motor(20, -20, 1000);		//閻熸瑨娅曢敃銉ヮ焽閹惧瓨鏆╅柨鐔剁矙閻撲即鏁撻敓锟� 闂傚棛顑曢崐銏拷姘炬嫹
          motor(200, -200, 1000);    //閻熸瑨娅曢敃銉╋綖婢舵劗鍨瑰鑸垫尰缂嶏拷 闂傚鐟ョ�氬爼寮抽敓锟� 闂傚楠搁幊銏ゅ蓟鎼淬劎浜柨鐕傛嫹 闂傚鎼╅崜銏ｇ亷闁哄喚鍣幏锟�
          break;
        }

      }
    }
  }

}

void wheel(int LeftSpeed, int RightSpeed) {
  if (LeftSpeed < 0)
    LeftWheelBackward_SpeedControl(abs(LeftSpeed));
  else if (LeftSpeed >= 0)
    LeftWheelForward_SpeedControl(LeftSpeed);

  if (RightSpeed < 0)
    RightWheelBackward_SpeedControl(abs(RightSpeed));
  else if (RightSpeed >= 0)
    RightWheelForward_SpeedControl(RightSpeed);

}
void lesson_9() {
  if (isLow(ZW_A1) && isLow(ZW_A3))       //闂傚绻傜�氱敻锝為敓锟� + 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //wheel(0,20);    //
    wheel(0, 200);
  }
  else if (isLow(ZW_A1) && isLow(ZW_A4))    //闂傚绻傜�氱敻锝為敓锟� + 闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //wheel(20,0);    //闂傚绻傜�氱敻锝為敓锟� 闂傚鐗幏锟�
    wheel(200, 0);
  }
  else if (isLow(ZW_A2) && isLow(ZW_A3))    //闂傚顦�氱敻锝為敓锟� + 闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //wheel(0, -20);  //闂傚顧�閹凤拷
    wheel(0, -200);
  }
  else if (isLow(ZW_A2) && isLow(ZW_A4))  //闂傚顦�氱敻锝為敓锟� + 闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //    wheel(-20, 0);  //闂傚顧�閹凤拷
    wheel(-200, 0);
  }
  else if (isLow(ZW_A1))      //闂傚绻傜�氱敻锝為敓锟�
  {
    //    wheel(20, 20);  //闂傚绻愰幏锟�
    wheel(200, 200);
  }
  else if (isLow(ZW_A2))      //闂傚顦�氱敻锝為敓锟�
  {
    //    wheel(-20, -20);  //
    wheel(-200, -200);
  }
  else if (isLow(ZW_A3))      //闁艰绠戦惌鍥р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //    wheel(-20, 20);   //闁艰绠戦惌鍥р枔閿燂拷
    wheel(-200, 200);
  }
  else if (isLow(ZW_A4))      //闂傚鐗滅划鏍р枔閻愯櫣浜伴柨鐕傛嫹
  {
    //    wheel(20, -20);   //闂傚鐗滅划鏍р枔閿燂拷
    wheel(200, -200);
  }
  else          //闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕亷婵繂妫撮幏锟� 闂傚楠搁…顏堝疾閸ф绂嗛柕鍫濐儌閺�锟�
  {
    wheel(0, 0);    //闂傚绻冨ú銏わ綖閿燂拷 闂傚洤鍟悷顒勬倵閿燂拷
  }
}


void lesson_10() {
  int LEDpin;

  if (firstRun) {
    //motor2(-7);          //闂傚绻冮崝銈夊垂閿燂拷 闁烩�冲皡閹凤拷
    RightWheelBackward_SpeedControl(70);
    delay(1000);
    //motor2(0);
    RightWheelBackward_SpeedControl(0);
    //    play(do5, n16); play(re5, n16); play(mi5, n16); play(pa5, n16); //闁烩剝娼欓惌鍛存倵閿燂拷 闂傚绶ら幏锟�
    playNote(c5, sixteenthNote, meters_x1);
    playNote(d5, sixteenthNote, meters_x1);
    playNote(e5, sixteenthNote, meters_x1);
    playNote(f5, sixteenthNote, meters_x1);
    //    play(sol5, n16); play(ra5, n16); play(ci5, n16); play(do6, n16);
    playNote(g5, sixteenthNote, meters_x1);
    playNote(a5, sixteenthNote, meters_x1);
    playNote(b5, sixteenthNote, meters_x1);
    playNote(c6, sixteenthNote, meters_x1);
    firstRun = false;
  }
  for (istep = 0; istep < 7;) //闂傚洨濮撮悧鏇炩枖閿燂拷 7闂傚棛鈷堥悡鍐兜閿燂拷
  {
    while (1)     //闂傚鍠氶崣鍡涘磿閿燂拷 闂傚牏顭堥悧鏇€�侀敓鐘典簷闁跨噦鎷� 闂傚洦绻冪划鏍х暦娴ｅ啫娈柟鐑樼♁缁讹拷 闂傚棭鍠楅敃銉ノｉ锔藉瘜闁告洖妯婇弫锟� 婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷
    {
      RANDOM = (user_random(4) - 1); //闂傚洦绻冪划鏍х暦閿燂拷 闂傚绻愰幏鐑芥濞戣櫕瀚�  (1~4) - 1 = 0 ~ 3
      //      Serial.print("RANDOM=");
      //      Serial.println(RANDOM);
      if (B_RANDOM != RANDOM)   //闂傚绻傜�氭挳鎯岄敓锟� 闂傚洦绻冪划鏍х暦閻㈠灚鎳￠柨鐕傛嫹 闂傚妫楃�氱敻鎮橀敓锟� 闂傚洦绻冪划鏍х暦閻㈠摜浜ｉ柨鐕傛嫹 闁艰垂鍕噸妞ゎ偓鎷� 闂傚楠搁…鈺傛叏閿燂拷 闁烩剝娼欓惇鎯掗敓锟�
      {
        B_RANDOM = RANDOM;      //闂傚绻傜�氭挳鎯岄敓锟� 闂傚洦绻冪划鏍х暦閻㈠摜锟戒粙鏁撻敓锟� 闂傚妫楃�氱敻鎮橀敓锟� 闂傚洦绻冪划鏍х暦閿燂拷 闂傚绻愰幏鐑芥濞戣櫕瀚�
        break;            //婵ê绉归弫濠囧汲閿燂拷 婵ɑ纰嶉敃銈嗘姜閿燂拷 闁绘绉舵繛瀣偋閹惰姤绐楁慨妤�鍟瀷
      }
    }
    //    on(1 << (RANDOM + 4));      //闂傚洦绻嶉悡鍕暦閻㈠摜锟戒粙鏁撻敓锟� 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED 闁哄啯甯幏锟� (B1)0x10 (B2)0x20 (B3)0x40 (B4)0x80
    int random_temp;
    random_temp = (1 << (RANDOM + 4));
    //    Serial.print("RANDOM in HEX: ");
    //    Serial.println(random_temp,HEX);
    switch (random_temp) {
      case 0x10:
        LEDpin = ZW_B1;
        //        Serial.println("case 0x10");
        break;
      case 0x20:
        LEDpin = ZW_B2;
        //        Serial.println("case 0x20");
        break;
      case 0x40:
        LEDpin = ZW_B3;
        //        Serial.println("case 0x40");
        break;
      case 0x80:
        LEDpin = ZW_B4;
        //        Serial.println("case 0x80");
        break;
      default:
        break;
    }
    on(LEDpin);


    if (RANDOM % 2)
      //      motor1(10);
      LeftWheelForward_SpeedControl(100);
    else
      //      motor1(-10);
      LeftWheelBackward_SpeedControl(100);
    //    timer(0);             //
    StartTime = millis();
    while (1)
    {
      if (millis() - StartTime > 100)
        //      motor1(0);
        LeftWheelForward_SpeedControl(0);

      if (millis() - StartTime >= GAMESPEED) //婵繂妫撮幏鐑芥濠靛洦纭�闁诡噯鎷� 闁烩剝娼欓惌鍛存倵閿燂拷 闂傚牐顕х粔鐓庮嚕閻楀牊灏愰柟渚簻閻濓拷 闂傚棙妞块悘浣肝涢崘顔句海闁跨噦鎷� 闁烩剝娼欓惇鎯掗敓锟�
      {
        //        buzzer(do4, 2, 200, 50); //闂傚闄嶉崐锝囦焊閿燂拷
        playNote(c4, eighthNote, meters_x2);
        if (GAMEFALE != 0) GAMEFALE--; //闂傚闄嶉崐锝囦焊閿燂拷 闁哄啫鍟亸妤�袙濮樺墎鍙為柨鐕傛嫹 闁艰垂鍕Б闁哥儑鎷�
        //        motor1(0);
        LeftWheelForward_SpeedControl(0);
        break;
      }
      else              //婵繂妫撮幏鐑芥濠靛洦纭�闁诡噯鎷� 闁烩剝娼欓惌鍛存倵閿燂拷 闂傚牐顕х粔鐓庮嚕閿燂拷 闂傚楠搁悧妤�螞閿燂拷 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚棛顭堥惌鍕偋閹惰姤绂冮柡鍐ㄧ▉濞硷拷 闂傚娲﹀ú銏狀熆閿燂拷
      {
        int INPUT_VAL = 0;
        if (isLow(ZW_A1)) INPUT_VAL += 0x01;
        if (isLow(ZW_A2)) INPUT_VAL += 0x02;
        if (isLow(ZW_A3)) INPUT_VAL += 0x04;
        if (isLow(ZW_A4)) INPUT_VAL += 0x08;

        if ((INPUT_VAL & 0x0f) & (~(1 << RANDOM))) //闂傚洦绻嶉悡鍕暦閻㈠摜锟戒粙鏁撻敓锟� 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崘鐐秱 闂傚楠搁…鈺傛叏閿燂拷
          //        if((INPUT_VAL & random_temp) != random_temp)
        {
          //          motor1(0);
          LeftWheelForward_SpeedControl(0);
          //          buzzer(do4, 2, 200, 50); //闂傚绶ら幏锟�
          playNote(c4, eighthNote, meters_x2);
          if (GAMEFALE != 0) GAMEFALE--; //闂傚闄嶉崐锝囦焊閿燂拷 闁哄啫鍟亸妤�袙濮樺墎鍙為柨鐕傛嫹 闁艰垂鍕Б闁哥儑鎷�

          break;
        }
        else if (INPUT_VAL & (1 << RANDOM)) //闂傚洦绻愰幏锟�
          //        else if ((INPUT_VAL & random_temp) == random_temp)
        {
          istep++;         //婵絿鏁搁崑顏呮叏閿燂拷 闂傚鍔婇崐鐐烘儍閿燂拷 闂傚洤琚崐銏ゅ蓟鎼淬劎浜楅柨鐔剁矙閻庡鎳犺濞硷拷 闂傚棛顑曢崐銏狀焽閹捐崵浜為柤浣冲本鏅�
          //          play(do6, 8); play(mi6, 8); play(sol6, 8); play(do7, 8); //婵絿鏁搁崕搴ㄥ疾閿燂拷
          playNote(c7, sixteenthNote * 0.5*0.5, meters_x1);
          playNote(e7, sixteenthNote * 0.5*0.5, meters_x1);
          playNote(g7, sixteenthNote * 0.5*0.5, meters_x1);
          playNote(c8, sixteenthNote * 0.5*0.5, meters_x1);
          //          motor1(0);
          LeftWheelForward_SpeedControl(0);
          break;
        }

      }
    }
    //    off(1 << (RANDOM + 4));     //闂傚洦绻冪划鏍х暦閻㈠摜锟戒粙鏁撻敓锟� 闂傚鍟敮鍓э拷姘煼閻栫喎顫滈崒姘兼綉 LED 闂傚棭鍙忛幏锟�
    switch (random_temp) {
      case 0x10:
        LEDpin = ZW_B1;
        //        Serial.println("case 0x10");
        break;
      case 0x20:
        LEDpin = ZW_B2;
        //        Serial.println("case 0x20");
        break;
      case 0x40:
        LEDpin = ZW_B3;
        //        Serial.println("case 0x40");
        break;
      case 0x80:
        LEDpin = ZW_B4;
        //        Serial.println("case 0x80");
        break;
      default:
        break;
    }
    off(LEDpin);

    if (GAMEFALE == 0) break;     //闂傚闄嶉崐锝囦焊閿燂拷 闁哄啫鍟亸妤�袙濮樺墎鍙為柣鈽呯悼濞堬拷 0闂傚纰嶇敮楣冨煘閿燂拷 for婵ê绋勯幏锟� 闁绘绉舵繛瀣偋閿燂拷 闂傚棭鍠楅敃銉ノｉ敓锟�
  }
  if (GAMEFALE != 0)          //7闂傚棛鈷堥悡鍐兜閻樻剚鍤氶柨鐕傛嫹 婵絿鏁搁崕搴ㄥ疾閸ф浜為柤浣筹拷閺�锟� 闂傚棛顑曢崐銏狀焽閿燂拷 LEVEL闁圭厧灏呴幏锟� 婵繂妫楃�氬爼寮搁敓锟�
  {
    //    play(do6, n16); play(mi6, n16); play(sol6, n16); play(do7, n16); //LEVEL UP 闂傚鐔幏锟� 闁哄倻銆嬮幏锟�
    playNote(c6, sixteenthNote, meters_x1);
    playNote(e6, sixteenthNote, meters_x1);
    playNote(g6, sixteenthNote, meters_x1);
    playNote(c7, sixteenthNote, meters_x1);
    //motor2(7);                        //LEVEL 闂傚鎼╅崜銏狀熆閺団�虫闁割値鍕彧 婵絿顣幏锟�
    RightWheelForward_SpeedControl(70);
    delay(100);
    //    motor2(0);
    RightWheelForward_SpeedControl(0);
    if (GAMESPEED >= 50) GAMESPEED -= 50; //闁烩剝娼欓惌鍛存倵閿燂拷 闂傚牐顕х粔鐓庮嚕閿燂拷 婵繂鍟换澶愭儍閿燂拷
  }
  else                    //闂傚闄嶉崐锝囦焊閹邦収鍤氶柨鐕傛嫹 5婵ǚ鏅幏锟� 婵ê娴傞悡鍕箟閿燂拷 闂傚瀚悧妤�鈹冮崒娑氭闁跨噦鎷�
  {

    //    play(do7, n16); play(ci6, n16); play(ra6, n16); play(sol6, n16); //闁烩剝娼欓惌鍛存倵閿燂拷 闁艰绠戦幊鐐核夐敓锟�
    playNote(c7, sixteenthNote, meters_x1);
    playNote(b6, sixteenthNote, meters_x1);
    playNote(a6, sixteenthNote, meters_x1);
    playNote(g6, sixteenthNote, meters_x1);
    //    play(pa6, n16); play(mi6, n16); play(re6, n16); play(do6, n16);
    playNote(f6, sixteenthNote, meters_x1);
    playNote(e6, sixteenthNote, meters_x1);
    playNote(d6, sixteenthNote, meters_x1);
    playNote(c6, sixteenthNote, meters_x1);
    //    motor2(-7);
    RightWheelBackward_SpeedControl(70);
    delay(1500);
    //    motor2(0);
    RightWheelForward_SpeedControl(0);
    //    break;

    firstRun = true;
    GAMEFALE = 5; //
    return;
  }
}
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};


void playOneNote(int songNumber, int *noteNumber) {
  int noteDuration;
  int pauseBetweenNotes;
  int sizeOfMelody;
  int note_played;

  switch (songNumber) {
    case 1:
      sizeOfMelody = sizeof(melody) / sizeof(int);
      noteDuration = 1000 / tempo[(*noteNumber)];
      note_played  = melody[(*noteNumber)];
      break;

    case 2:
      sizeOfMelody = sizeof(underworld_melody) / sizeof(int);
      noteDuration = 1000 / underworld_tempo[(*noteNumber)];
      note_played  = underworld_melody[(*noteNumber)];
      break;

  }

  tone(SpeakerPIN, note_played, noteDuration);         //each loop run plays one note
  pauseBetweenNotes = noteDuration * 1.30;
  delay(pauseBetweenNotes);

  (*noteNumber)++;

  if ((*noteNumber) >= sizeOfMelody) (*noteNumber) = 0;
}

int noteNumberofSong1 = 0;
int noteNumberofSong2 = 0;
void lesson_11() {
  if (isLow(ZW_A1) || isLow(ZW_A2)) {
    if (isLow(ZW_A1) && isHigh(ZW_A2)) {
      playOneNote(1, &noteNumberofSong1);
      on(ZW_B1);
      Right_Motor(BACKWARD);
    }
    else if (isLow(ZW_A2) && isHigh(ZW_A1)) {
      playOneNote(2, &noteNumberofSong2);
      on(ZW_B1);
      Right_Motor(FORWARD);
    }
    else {
      off(ZW_B1);
      Right_Motor(STOP);
    }
  }
  else {
    off(ZW_B1);
    Right_Motor(STOP);
  }
}

void lesson_11_old() {
  if (firstRun) {
    SENSOR_A1 = analogRead(ZW_A1) - 10;
    SENSOR_A2 = analogRead(ZW_A2) - 10;
    firstRun = false;
    Serial.print("A1 value:");
    Serial.println(SENSOR_A1);
    Serial.print("A2 value:");
    Serial.println(SENSOR_A2);
  }
  if ((analogRead(ZW_A1) < SENSOR_A1) && (analogRead(ZW_A2) < SENSOR_A2)) //闂傚绻戦崺鍕敁濠婂牊绂嗛柨鐕傛嫹 闁艰垂鍕Б妞ゎ偄鎳樺〒钘夘潨閸愨晩妫冮梻澶嬬啲閹凤拷 闁烩剝娼欓惇鎯掗敓锟�
  {
    //      melody(mi7);          //婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� 闁哄倸鍚嬬划鏍偋閿燂拷
    playNote(e7, sixteenthNote, meters_x1);
    on(ZW_B1, ZW_B2);           //LED1, LED2 ON
    wheel(200, 200);
  }
  else if (analogRead(ZW_A1) < SENSOR_A1)     //闂傚娲橀ˉ鍛搭敁閿燂拷 闁艰垂鍕Б妞ゎ偄鎳樺〒钘夘潨閸愨晩妫冮梻澶嬬啲閹凤拷 闁烩剝娼欓惇鎯掗敓锟�
  {
    //      melody(sol7);         //婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷�
    playNote(g7, sixteenthNote, meters_x1);
    on(ZW_B1);             //LED1 ON
    off(ZW_B2);
    wheel(0, 150);         //闁瑰吋瀵х划鏍閿燂拷 闂傚娲橀ˉ鍛搭敁濠婂牏浜為柤浣冲本鏅� 闂傚绻傜�氱敻锝為敓锟�
  }
  else if (analogRead(ZW_A2) < SENSOR_A2)     //闂傚娲橀ˉ鍛搭敁閿燂拷 闁艰垂鍕Б妞ゎ偄鎳樺〒钘夘潨閸愨晩妫冮梻澶嬬啲閹凤拷 闁烩剝娼欓惇鎯掗敓锟�
  {
    //      melody(sol7);         //婵ê鎷戦幏锟�
    playNote(g7, sixteenthNote, meters_x1);
    on(ZW_B2);             //LED2 ON
    off(ZW_B1);
    wheel(150, 0);         //闁瑰吋瀵х划鏍閿燂拷 闂傚鎸堕崐鐘诲Χ閹间緡妫楅悘鐐诧攻缁ㄦ粓骞栭崠鈩冨 闂傚绻傜�氱敻锝為敓锟�
  }
  else if (isLow(ZW_A3))            //闁艰垂宥嗗闂傚鐗楃敮鎯х暤閿燂拷 闂傚鎷烽柕鍫濇湰鐠侊綁寮崘鈺嬫闁活煉鎷� 闂傚棛顭堥惌鍕偋閹剁晫浜ｉ柨鐕傛嫹 闁烩剝娼欓惇鎯掗敓锟�
  {
    motor(-200, 0, 100);     //闂傚鐗曞畷鎰般�侀敓锟� 闂傚顦�氱敻锝為敓锟�
    for (int i = 0; i < 10; i++) //for婵ê绉烽崗鍌氼焽閿燂拷 闂傚纰嶇亸妤�袙閸曨垳鍨烽柨鐕傛嫹 10婵ǚ鏅幏锟� 婵ɑ纰嶉敃銈嗘姜閿燂拷
    {
      on(ZW_B1);           //LED1 ON
      off(ZW_B2);          //LED2 OFF
      //        melody(mi7);        //婵ê鎳忕划鏍�侀敓锟�
      playNote(e7, sixteenthNote, meters_x1);
      motor(0, -200, 100);   //闁艰绠戦惌鍕�侀敓锟� 闂傚顦�氱敻锝為敓锟�
      on(ZW_B2);           //LED1 OFF
      off(ZW_B1);          //LED2 ON
      //        melody(0);          //婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
      motor(-200, 0, 100);   //闂傚鐗曞畷鎰般�侀敓锟� 闂傚顦�氱敻锝為敓锟�
    }

  }
  else                //闂傚楠哥�氭挳顢栭敓锟� 闂傚绋戦幊鐐烘偋閹剧粯瀵岄柨鐕傛嫹 闂傚洤琚崐銏ゅ蓟鎼淬劎浜愰柕鍫濈焾濞硷拷 闂傚楠搁…鈺傛叏閿燂拷 闁烩剝娼欓惇鎯掗敓锟�
  {
    //      melody(0);            //婵ê鎳忕划鏍�侀敓鐘崇疇闁跨噦鎷� OFF
    off(ZW_B1, ZW_B2);          //LED1, LED2 OFF
    wheel(0, 0);          //闁瑰吋瀵х划鏍閿燂拷 闂傚绻冨ú銏わ綖閿燂拷
  }
}





