// Copyright Pololu Corporation.  For more information, see http://www.pololu.com/

#include "Buzzer.h"



int NOTE[] = {
  c5, c4, d4, e4, f4, g4, a4, b4, c5, d5, e5, f5
};




void playNote(int Note, int Meter, int Length) {
  tone(BEEP, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.3 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
}

void playNoteShort(int Note, int Meter, int Length) {
  tone(BEEP, Note, Meter * Length);
  //  delay(Meter * 1.3 * Length);
  long duration_time = millis();
  for (int i = 0; i < Meter * 1.3 * Length * 200; i++) {
    //    Serial.println(i);
    if (millis() - duration_time > Meter * 1.0 * Length) break;
    //digitalRead(ZW_A1);
  }
  //  noTone(BuzzerPin);
}


void playStart()
{
  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  delay(100);

  playNoteShort(e7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(f7, sixteenthNote * 0.25, meters_x1);
  playNoteShort(g7, sixteenthNote * 0.25, meters_x1);
}

void playPowerOn()
{
	playNote(c4, eighthNote, meters_x1);
  playNote(e4, eighthNote, meters_x1);
  playNote(g4, eighthNote, meters_x1);
  playNote(c5, quaterNote, meters_x1);
}

void playSong(int songSelected) {
  switch (songSelected) {
  case 1:
    playNote(e4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(d4, eighthNote, meters_x2);



    playNote(e4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(f4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);

    playNote(d4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(c4, eighthNote, meters_x2);


    for (int i = 0; i < 2; i++) {
      playNote(d4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);

      playNote(d4, eighthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(f4, sixteenthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);

      playNote(d4, eighthNote, meters_x1);
      playNote(e4, sixteenthNote, meters_x1);
      playNote(f4, sixteenthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(g3, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x2);

      //playNote(e4,eighthNote,meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(g4, eighthNote, meters_x1);

      playNote(g4, eighthNote, meters_x1);
      playNote(f4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);

      playNote(c4, eighthNote, meters_x1);
      playNote(c4, eighthNote, meters_x1);
      playNote(d4, eighthNote, meters_x1);
      playNote(e4, eighthNote, meters_x1);

      playNote(d4, sixteenthNote, meters_x3);
      playNote(c4, sixteenthNote, meters_x1);
      playNote(c4, eighthNote, meters_x2);
    }
    break;

  case 2:
    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);
    playNote(g3, quaterNote / 3, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(g3, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x3);
    playNote(c4, eighthNote, meters_x1);

    playNote(c4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g3, eighthNote, meters_x1);
    playNote(a3, sixteenthNote, meters_x1);
    playNote(b3, sixteenthNote, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(e4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(e4, sixteenthNote, meters_x1);

    playNote(g4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);

    playNote(g4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(d4, quaterNote, meters_x1);

    playNote(d4, quaterNote, meters_x2);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(d4, quaterNote, meters_x1);
    playNote(e4, quaterNote, meters_x1);

    playNote(g4, eighthNote, meters_x1);
    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(e4, quaterNote, meters_x1);
    delay(quaterNote * 1.3 * meters_x1);

    playNote(g3, sixteenthNote, meters_x3);
    playNote(a3, sixteenthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);
    playNote(c4, eighthNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(d4, eighthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(d4, sixteenthNote, meters_x1);
    playNote(a3, quaterNote, meters_x1);

    playNote(d4, eighthNote, meters_x3);
    playNote(g3, eighthNote, meters_x1);

    playNote(c4, eighthNote, meters_x3);
    playNote(c4, eighthNote, meters_x1);

    playNote(e4, eighthNote, meters_x3);
    playNote(e4, eighthNote, meters_x1);

    playNote(g4, quaterNote, meters_x2);

    playNote(c4, sixteenthNote, meters_x3);
    playNote(e4, sixteenthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);
    playNote(g4, eighthNote, meters_x1);

    playNote(a4, quaterNote, meters_x1);
    playNote(g4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(c4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(e4, sixteenthNote, meters_x3);
    playNote(c4, sixteenthNote, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);
    playNote(g4, quaterNote / 3, meters_x1);

    playNote(e4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);
    playNote(c4, eighthNote, meters_x1);
    delay(eighthNote * 1.3 * meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(g3, quaterNote, meters_x1);
    playNote(c4, quaterNote, meters_x1);

    playNote(c4, quaterNote, meters_x1);
    delay(quaterNote * 1.3 * meters_x1);
    break;

  case 3:
    break;
  case 4:
    break;

  case 5:
    break;

  default:
    break;
  }

}
