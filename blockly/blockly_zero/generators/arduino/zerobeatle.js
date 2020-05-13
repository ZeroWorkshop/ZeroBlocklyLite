'use strict';

goog.provide('Blockly.Arduino.beatle');
goog.require('Blockly.Arduino');

Blockly.Arduino.allfunc = function() {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(0);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(0);\n"
  return beatleSingleFunc;
};

var beatleSingleFunc = "";
Blockly.Arduino.beatleCruise = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(7);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(7);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleFollowline = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(3);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(3);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleMaze = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(4);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(4);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleEdgedetect = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(2);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(2);\n"
  return beatleSingleFunc;
};



Blockly.Arduino.beatleAvoid = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(1);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;
  beatleSingleFunc = "beatle.LoopAll(1);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleSumo = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(5);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;


  beatleSingleFunc = "beatle.LoopAll(5);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleControl = function () {
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	var setup_code = '';
	setup_code = 'beatle.SetupAll(6);\n';


	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_wandering'] = setup_code;


  beatleSingleFunc = "beatle.LoopAll(6);\n"
  return beatleSingleFunc;
};

Blockly.Arduino.beatleWheel = function() {
	var dropdown_MotorName = this.getFieldValue('MotorName');
	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

	var dropdown_MotorName = this.getFieldValue('MotorName');


	var MotorStatus = this.getFieldValue('RunningStatus');
	var speedValue = Blockly.Arduino.valueToCode(this, 'speedValue', Blockly.Arduino.ORDER_ATOMIC);//this.getFieldValue('speedValue');

	var whichMotor;

	if (dropdown_MotorName == "M1")      whichMotor = 'setLeftSpeed';
	else if (dropdown_MotorName == "M2") whichMotor = 'setRightSpeed';

	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}


  if (MotorStatus == "BACKWARD") {
  	speedValue = -speedValue;
  	}
  if (MotorStatus == "STOP")     speedValue = 0;

	var code = 'beatle.motors.' + whichMotor + '(' + speedValue +');\n';
	return code;
};

Blockly.Arduino.beatleLRWheels = function() {


	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

	var LMotorStatus = this.getFieldValue('LRunningStatus');
	var LspeedValue = Blockly.Arduino.valueToCode(this, 'LspeedValue', Blockly.Arduino.ORDER_ATOMIC); //this.getFieldValue('LspeedValue');
	var RMotorStatus = this.getFieldValue('RRunningStatus');
	var RspeedValue = Blockly.Arduino.valueToCode(this, 'RspeedValue', Blockly.Arduino.ORDER_ATOMIC); //this.getFieldValue('RspeedValue');

	if(LspeedValue < 0) {
		LspeedValue = 0;
	}
	if(LspeedValue > 255) {
		LspeedValue = 255;
	}

	if(RspeedValue < 0) {
		RspeedValue = 0;
	}
	if(RspeedValue > 255) {
		RspeedValue = 255;
	}

  if (LMotorStatus == "BACKWARD") LspeedValue = -LspeedValue;
  if (LMotorStatus == "STOP")     LspeedValue = 0;
  if (RMotorStatus == "BACKWARD") RspeedValue = -RspeedValue;
  if (RMotorStatus == "STOP")     RspeedValue = 0;

	var code = 'beatle.motors.setSpeeds(' + LspeedValue + ', ' + RspeedValue + ');\n';
	return code;

};

Blockly.Arduino.beatle_lists_create_melody = function() {
  // Create a list with any number of elements of any type.

  var dropdown_type = 'const char';

  var varName =  this.getFieldValue('MYLIST'); //'my_melody';

  //Blockly.Arduino.definitions_['include_Wire'] = '#include <Wire.h>';
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  var code = new Array(this.itemCount_);
  for (var n = 0; n < this.itemCount_; n++) {
    code[n] = Blockly.Arduino.valueToCode(this, 'ADD' + n,
      Blockly.Arduino.ORDER_NONE) || '0';
  }
  Blockly.Arduino.definitions_[varName + '_declare'+varName] = dropdown_type+' ' + varName+'[] PROGMEM ' + '=\n'+ code.join('\n') + ';\n';
  //var code =''+varName+'['+size+"]"+'='+ '{' + code.join(', ') + '};\n';
  //Blockly.Arduino.setups_['setup_lists'+varName] = code;
  return '';
};

Blockly.Arduino.beatleBuzzerPlaynote = function () {

  var value = Blockly.Arduino.valueToCode(this, 'VALUE', Blockly.Arduino.ORDER_ATOMIC);
  var volume = Blockly.Arduino.valueToCode(this, 'VOL', Blockly.Arduino.ORDER_ATOMIC);

  var note = this.getFieldValue('Note');
  var octave = '(' + this.getFieldValue('Octave') + ')';

  var noteVar;
  if      (note == "C")  noteVar = "NOTE_C";
  else if (note == "C#") noteVar = "NOTE_C_SHARP";
  else if (note == "D")  noteVar = "NOTE_D";
  else if (note == "D#") noteVar = "NOTE_D_SHARP";
  else if (note == "E")  noteVar = "NOTE_E";
  else if (note == "F")  noteVar = "NOTE_F";
  else if (note == "F#") noteVar = "NOTE_F_SHARP";
  else if (note == "G")  noteVar = "NOTE_G";
  else if (note == "G#") noteVar = "NOTE_G_SHARP";
  else if (note == "A")  noteVar = "NOTE_A";
  else if (note == "A#") noteVar = "NOTE_A_SHARP";
  else if (note == "B")  noteVar = "NOTE_B";
  else if (note == "SILENT")  {
    noteVar = "SILENT_NOTE";
    octave = "";
  }

	//Blockly.Arduino.definitions_['include_Wire'] = '#include <Wire.h>';
  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  return 'beatle.buzzer.playNote(' + noteVar  + octave + ', ' + value  + ', ' + volume + ');\n';

};

Blockly.Arduino.beatleBuzzer = function () {
  var value = Blockly.Arduino.valueToCode(this, 'VALUE', Blockly.Arduino.ORDER_ATOMIC);
	//Blockly.Arduino.definitions_['include_Wire'] = '#include <Wire.h>';


  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  Blockly.Arduino.definitions_['var_declare_playMelody'] = 'const char melody[] PROGMEM = ' + value + ';\n';

  var code = 'if (!beatle.buzzer.isPlaying()) {\n';
  code += '  beatle.buzzer.playFromProgramSpace(melody);\n';
  code += '}\n';
  return code;
};

Blockly.Arduino.beatleBuzzerPlaylist = function () {
  var value = Blockly.Arduino.valueToCode(this, 'VALUE', Blockly.Arduino.ORDER_ATOMIC);

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  var code = 'if (!beatle.buzzer.isPlaying()) {\n';
  code +=  '  beatle.buzzer.playFromProgramSpace(' + value + ');\n';
  code += '}\n';
  return code;


};
Blockly.Arduino.beatleLED = function () {

    var code = "try "
    return code;
};

Blockly.Arduino.beatle_display_rgb_show = function () {

  var dropdown_rgbpin = Blockly.Arduino.valueToCode(this, 'PIN', Blockly.Arduino.ORDER_ATOMIC);

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;

  var code1 = 'ZeroRGBLED ' + LEDstrip + '(' + dropdown_rgbpin + ',12);\n';

  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;



  var code = LEDstrip + '.strip.show();\n';
  return code;
};

Blockly.Arduino.beatle_RGB_color_rgb = function () {

  var R = Blockly.Arduino.valueToCode(this, 'R', Blockly.Arduino.ORDER_ATOMIC);
  var G = Blockly.Arduino.valueToCode(this, 'G', Blockly.Arduino.ORDER_ATOMIC);
  var B = Blockly.Arduino.valueToCode(this, 'B', Blockly.Arduino.ORDER_ATOMIC);
  var colour = R + "*65536" + "+" + G + "*256" + "+" + B;
  
  var code = 'strip.Color(' + R + ',' + G + ',' + B + ')';
  return [code, Blockly.Arduino.ORDER_NONE];
  //return code;
};


Blockly.Arduino.beatle_display_rgb = function () {
  //var dropdown_rgbpin = this.getFieldValue('PIN');
  //var dropdown_rgbpin = 'BeatleLEDPIN';
  var dropdown_rgbpin = Blockly.Arduino.valueToCode(this, 'PIN', Blockly.Arduino.ORDER_ATOMIC);
  var value_led = Blockly.Arduino.valueToCode(this, '_LED_', Blockly.Arduino.ORDER_ATOMIC);
  var Brightness = Blockly.Arduino.valueToCode(this, 'Brightness', Blockly.Arduino.ORDER_ATOMIC);
  var COLOR = Blockly.Arduino.valueToCode(this, 'COLOR');

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;

  //Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';

  var code1 = 'ZeroRGBLED ' + LEDstrip + '(' + dropdown_rgbpin + ',12);\n';

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	
	Blockly.Arduino.setups_['beatle_display_rgb_setup'] = 'LEDStrip_2.init();\n';

  if (Blockly.Arduino.definitions_["RGBLED_function_def1"] == null) Blockly.Arduino.definitions_["RGBLED_function_def1"] = "";
  if (Blockly.Arduino.definitions_["RGBLED_function_def2"] == null) Blockly.Arduino.definitions_["RGBLED_function_def2"] = "";

  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;

  /*
  var code1 = '#include <Adafruit_NeoPixel.h>\n';
  code1 += 'uint8_t LEDBrightness = 255; //default LEDBrightness is set to 255;\n';
  code1 += 'Adafruit_NeoPixel  rgb_display_' + dropdown_rgbpin + '= Adafruit_NeoPixel(12,' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);';

  Blockly.Arduino.definitions_["display_rgb"] = code1;
  */

  COLOR = COLOR.replace(/#/g, "0x");
  var code = LEDstrip + '.strip.setPixelColor((' + value_led + ')-1, ' + LEDstrip + '.' + COLOR + ');\n';
  return code;
};

Blockly.Arduino.display_rainbow_stream = function () {
  //var dropdown_rgbpin = Blockly.Arduino.valueToCode(this, 'PIN', Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_rgbpin = '2';
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  var lednum = Blockly.Arduino.valueToCode(this, 'LEDN', Blockly.Arduino.ORDER_ATOMIC);
  var lednum = '12';

  var code0 = "\n";
  var code1 = "\n";

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;
  code0 = 'Adafruit_NeoPixel  ' + stripName + ' = Adafruit_NeoPixel(' + lednum + ',' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);\n';
  code1 = 'ZeroRGBLED ' + LEDstrip + '(' + dropdown_rgbpin + ',' + lednum + ');\n';
  //Blockly.Arduino.definitions_["RGBLED_function_include"] = '#include "ZeroRGBLED.h"\n';

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  if (Blockly.Arduino.definitions_["RGBLED_function_def1"] == null) Blockly.Arduino.definitions_["RGBLED_function_def1"] = "";
  if (Blockly.Arduino.definitions_["RGBLED_function_def2"] == null) Blockly.Arduino.definitions_["RGBLED_function_def2"] = "";
  //Blockly.Arduino.definitions_["RGBLED_function_def1"] += code0;
  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;

  var option = this.getFieldValue('OPTION');
  var func_op;

  if (option == "option_1") {
      func_op = 'rainbow_stream';
  }
  else if (option == "option_2") {
      func_op = 'theaterChaseRainbow';
  }

  //Blockly.Arduino.setups_[LEDstrip] = LEDstrip + '.begin();\n';

  var code;
  code = LEDstrip + '.' + func_op + '(' + wait_time + ');\n';
  return code;
};


Blockly.Arduino.RGBLED_functions = function () {

  var dropdown_rgbpin = Blockly.Arduino.valueToCode(this, 'PIN', Blockly.Arduino.ORDER_ATOMIC);
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  var lednum = Blockly.Arduino.valueToCode(this, 'LEDN', Blockly.Arduino.ORDER_ATOMIC);

  var code0 = "\n";
  var code1 = "\n";

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;
  code0 = 'Adafruit_NeoPixel  ' + stripName + ' = Adafruit_NeoPixel(' + lednum + ',' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);\n';
  code1 = 'ZeroRGBLED ' + LEDstrip + '(' + dropdown_rgbpin + ',' + lednum + ');\n';
  //Blockly.Arduino.definitions_["RGBLED_function_include"] = '#include "ZeroRGBLED.h"\n';

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  if (Blockly.Arduino.definitions_["RGBLED_function_def1"] == null) Blockly.Arduino.definitions_["RGBLED_function_def1"] = "";
  if (Blockly.Arduino.definitions_["RGBLED_function_def2"] == null) Blockly.Arduino.definitions_["RGBLED_function_def2"] = "";
  //Blockly.Arduino.definitions_["RGBLED_function_def1"] += code0;
  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;

  var option = this.getFieldValue('OPTION');
  var func_op;

  if (option == "option_1") {
      func_op = 'rainbow_stream';
  }
  else if (option == "option_2") {
      func_op = 'theaterChaseRainbow';
  }

  //Blockly.Arduino.setups_[LEDstrip] = LEDstrip + '.begin();\n';

  var code;
  code = LEDstrip + '.' + func_op + '(' + wait_time + ');\n';
  return code;
};

Blockly.Arduino.RGBLED_policelight = function() {

  var dropdown_rgbpin = "2";

  var lednum = this.getFieldValue('number'); //Blockly.Arduino.valueToCode(this, 'number', Blockly.Arduino.ORDER_ATOMIC);

  var code0 = "\n";
  var code1 = "\n";
  var code2 = "\n";

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;
  code0 = 'Adafruit_NeoPixel  ' + stripName + ' = Adafruit_NeoPixel(' + lednum + ',' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);\n';
  //code1 = 'ZeroRGBLED ' + LEDstrip + '(' + stripName + ');\n';
  code1 = 'ZeroRGBLED ' + LEDstrip + '(' + dropdown_rgbpin + ',' + lednum + ');\n';
  code2 = 'int pix;'

  Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

  if (Blockly.Arduino.definitions_["RGBLED_function_def1"] == null) Blockly.Arduino.definitions_["RGBLED_function_def1"] = "";
  if (Blockly.Arduino.definitions_["RGBLED_function_def2"] == null) Blockly.Arduino.definitions_["RGBLED_function_def2"] = "";
  //Blockly.Arduino.definitions_["RGBLED_function_def1"] += code0;
  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;
  Blockly.Arduino.definitions_["RGBLED_function_def3"] = code2;

  //Blockly.Arduino.setups_[LEDstrip] = LEDstrip + '.begin();\n';
  Blockly.Arduino.setups_["policeLight"] = 'pix = ' + lednum/2 + ';\n';
  var code;
  code = LEDstrip + '.policeLightRun(' + lednum + ', &pix);\n';
  return code;

  /*
	var NumberOfLED = this.getFieldValue('number');

	Blockly.Arduino.setups_['TseriesCommonRGBLED'] = 'strip.begin();\n  ' + 'strip.show();\n  ' +
		'OnOffState = OFF;\n  ' +
		'pix = ' + NumberOfLED / 2 + ';\n\n';

	Blockly.Arduino.definitions_['TseriesCommonRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel strip;\n' +
		'bool OnOffState;\n' +
		'int pix;\n\n';

	var code = 'policeLightRun(' + NumberOfLED + ', &pix);\n';

	return code;
	*/
}

Blockly.Arduino.beatleIRsensor = function () {
    var IRsensor = this.getFieldValue('SensorName');
    var IRvalue = this.getFieldValue('IRStatus');

    var code;
    if (IRvalue == "IRsensored")
      code = "(digitalRead(" + IRsensor + ") == LOW)";
    else if (IRvalue == "unIRsensored")
      code = "(digitalRead(" + IRsensor + ") == HIGH)";

   //var code = (this.getFieldValue('BOOL') == 'IRsensored') ? 'TRUE' : 'FALSE';
    return [code, Blockly.Arduino.ORDER_ATOMIC];
   //return code;
};

Blockly.Arduino.beatleReadLineIRsensors = function () {
    Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	  
    Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';
    
    Blockly.Arduino.definitions_['beatle_IRsensor_def'] = 'unsigned int sensor_values[7];\n';
  
    Blockly.Arduino.setups_['beatle_IRsensor'] = 'beatle.LineSensors.init();\n';
    
    Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

    var code = 'beatle.LineSensors.read(sensor_values);\n';
    return code;
};

Blockly.Arduino.readLineIRSensorValue = function () {
	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	  
    Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';
    
    Blockly.Arduino.definitions_['beatle_IRsensor_def'] = 'unsigned int sensor_values[7];\n';
  
    Blockly.Arduino.setups_['beatle_IRsensor'] = 'beatle.LineSensors.init();\n';
    
    Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
 var rgb = this.getFieldValue('Sensor_Value');
	var code  = rgb;

	return [code, Blockly.Arduino.ORDER_ATOMIC];
}


Blockly.Arduino.setCalibration4lineSensors = function () {



	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	Blockly.Arduino.setups_['setCalibration4lineSensors'] = 'beatle.writeCalibrationData(max_value,min_value);\n';

	var max0 = this.getFieldValue('0max');
	var max1 = this.getFieldValue('1max');
	var max2 = this.getFieldValue('2max');
	var max3 = this.getFieldValue('3max');
	var max4 = this.getFieldValue('4max');
	var max5 = this.getFieldValue('5max');
	var max6 = this.getFieldValue('6max');

  var min0 = this.getFieldValue('0min');
	var min1 = this.getFieldValue('1min');
	var min2 = this.getFieldValue('2min');
	var min3 = this.getFieldValue('3min');
	var min4 = this.getFieldValue('4min');
	var min5 = this.getFieldValue('5min');
	var min6 = this.getFieldValue('6min');

  Blockly.Arduino.definitions_['setCalibration4lineSensors_def'] = 'unsigned int max_value[] = {'
                                                                 + max0 + ','
                                                                 + max1 + ','
                                                                 + max2 + ','
                                                                 + max3 + ','
                                                                 + max4 + ','
                                                                 + max5 + ','
                                                                 + max6 + '};\n' 
                                                                 + 'unsigned int min_value[] = {'
                                                                 + min0 + ','
                                                                 + min1 + ','
                                                                 + min2 + ','
                                                                 + min3 + ','
                                                                 + min4 + ','
                                                                 + min5 + ','
                                                                 + min6 + '};\n' ;
                                                                 
	var code = "";
	return code;


}


Blockly.Arduino.beatleLineSensorCalibration = function () {

  var AllowCal = this.getFieldValue('AllowCal');

	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';

  
  
	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
	

	var speed = this.getFieldValue('speed');
	var time = this.getFieldValue('time');
  
  if (speed < 0) speed = -speed;
  if (speed > 255) speed = 255;
	Blockly.Arduino.setups_['beatleLineSensorCalibration'] = 'beatle.LineSensorCalibration(' + AllowCal + ',' + speed + ',' + time + ');\n';
	var code = "";
	return code;
}


Blockly.Arduino.beatleReadLinePostion = function () {
	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	  
    Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';
    
    Blockly.Arduino.definitions_['beatle_IRsensor_def'] = 'unsigned int sensor_values[7];\n';
  
    //Blockly.Arduino.setups_['beatle_IRsensor'] = 'beatle.LineSensors.init();\n';
    
    Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
 
	var code  = 'beatle.LineSensors.readLine(sensor_values);\n';

	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.beatlewaitforButton = function () {
    Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	  
    Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';
    
    
    Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';

    var code = 'beatle.button.waitForButton();\n';
    return code;
};

Blockly.Arduino.PS2_button = function () {
	
	Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';
	Blockly.Arduino.definitions_['zeroPS2_def'] = 'int PS2_Button_Read[6];';
  Blockly.Arduino.definitions_['declare_Beatle_beatle'] = 'Beatle beatle;\n';
  
	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

  Blockly.Arduino.setups_['beatle_basicSetup'] = 'beatle.StartProgram();\n';
    var button = this.getFieldValue('BUTTON');
    
    var code;
    if (button == "../../media/ZeroWorkshop/Bup.png") 
        code = "_ButtonUp";
    else if (button == "../../media/ZeroWorkshop/Bleft.png") 
        code = "_ButtonLeft";
    else if (button == "../../media/ZeroWorkshop/Bright.png") 
        code = "_ButtonRight";
    else if (button == "../../media/ZeroWorkshop/Bdown.png") 
        code = "_ButtonDown";
    else if (button == "../../media/ZeroWorkshop/Btriangle.png") 
        code = "_ButtonTriangle";    
    else if (button == "../../media/ZeroWorkshop/Bsquare.png") 
        code = "_ButtonSquare"; 
    else if (button == "../../media/ZeroWorkshop/Bcross.png") 
        code = "_ButtonCross"; 
    else if (button == "../../media/ZeroWorkshop/Bcircle.png") 
        code = "_ButtonCircle";    
    else if (button == "../../media/ZeroWorkshop/BL1.png") 
        code = "_ButtonL1"; 
    else if (button == "../../media/ZeroWorkshop/BL2.png") 
        code = "_ButtonL2"; 
    else if (button == "../../media/ZeroWorkshop/BR1.png") 
        code = "_ButtonR1"; 
    else if (button == "../../media/ZeroWorkshop/BR2.png") 
        code = "_ButtonR2";    
    else if (button == "../../media/ZeroWorkshop/Bstart.png") 
        code = "_ButtonStart"; 
    else if (button == "../../media/ZeroWorkshop/Bselect.png") 
        code = "_ButtonSelect";   
                 
    return [code, Blockly.Arduino.ORDER_ATOMIC];
};


