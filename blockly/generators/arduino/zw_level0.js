'use strict';

goog.provide('Blockly.Arduino.level0');

goog.require('Blockly.Arduino');

Blockly.Arduino.level_s = function() {
	// TODO: Assemble JavaScript into code variable.
var str = '';
str+='  \n';
str+='  digitalWrite(ZW_A1,HIGH);\n';
str+='  digitalWrite(ZW_A2,HIGH);\n';
str+='  digitalWrite(ZW_A3,HIGH);\n';
str+='  digitalWrite(ZW_A4,HIGH);\n';
str+='  \n';
str+='  Serial.print("ProgramSelected = ");\n';
str+='  Serial.println(ProgramSelected);\n';
str+='  pinMode(MOTOR1P, OUTPUT);\n';
str+='  pinMode(MOTOR1M, OUTPUT);\n';
str+='  pinMode(MOTOR2P, OUTPUT);\n';
str+='  pinMode(MOTOR2M, OUTPUT);\n';
str+='\n';
str+='  pinMode(ZW_B1, OUTPUT);\n';
str+='  pinMode(ZW_B2, OUTPUT);\n';
str+='  pinMode(ZW_B3, OUTPUT);\n';
str+='  pinMode(ZW_B4, OUTPUT);\n';
str+='  Serial.begin(115200);\n';
str+='\n';
str+='\n';
str+='  Serial.println("Program begin...");\n';
str+='\n';
str+='//  playNoteShort(c7, sixteenthNote * 0.5, meters_x1);\n';
str+='  playNoteShort(e7, sixteenthNote * 0.5, meters_x1);\n';
str+='  playNoteShort(g7, sixteenthNote * 0.5, meters_x1);\n';
str+='//  playNoteShort(c8, sixteenthNote * 0.5, meters_x1);\n';
str+='  delay(100);\n';
str+='//  playNoteShort(c7, sixteenthNote * 0.5, meters_x1);\n';
str+='  playNoteShort(e7, sixteenthNote * 0.5, meters_x1);\n';
str+='  playNoteShort(g7, sixteenthNote * 0.5, meters_x1);\n';
str+='//  playNoteShort(c8, sixteenthNote * 0.5, meters_x1);\n';
str+='  if (ProgramSelected == 1) { // || ProgramSelected == 11) {\n';
str+='\n';
str+='    cli();//stop interrupts\n';
str+='    //set timer1 interrupt at 10Hz\n';
str+='    TCCR1A = 0;// set entire TCCR1A register to 0\n';
str+='    TCCR1B = 0;// same for TCCR1B\n';
str+='    TCNT1  = 0;//initialize counter value to 0\n';
str+='    // set timer count for 10hz increments\n';
str+='    OCR1A = 1562;// = (16*10^6) / (10*1024) - 1\n';
str+='\n';
str+='    // turn on CTC mode\n';
str+='    TCCR1B |= (1 << WGM12);\n';
str+='    // Set CS11 bit for 8 prescaler\n';
str+='    //  TCCR1B |= (1 << CS11);\n';
str+='    // Set CS10 and CS12 bits for 1024 prescaler\n';
str+='    TCCR1B |= (1 << CS12) | (1 << CS10);\n';
str+='\n';
str+='    // enable timer compare interrupt\n';
str+='    TIMSK1 |= (1 << OCIE1A);\n';
str+='    sei();//allow interrupts\n';
str+='  }\n';
Blockly.Arduino.setups_['levelS'] = str;
var sth='';
sth+='volatile bool firstRunFlag = true;\n';
sth+='volatile bool NoButtonPressedFlag = true;\n';
sth+='volatile int NumOfTicks = 0;\n';
sth+='boolean toggle = 0;\n';
sth+='ISR(TIMER1_COMPA_vect) {\n';
sth+='  if (ProgramSelected == 1) {\n';
sth+='    if (NoButtonPressedFlag) {\n';
sth+='      if (toggle) {\n';
sth+='        digitalHigh(ZW_B1);\n';
sth+='        digitalHigh(ZW_B2);\n';
sth+='        digitalHigh(ZW_B3);\n';
sth+='        digitalHigh(ZW_B4);\n';
sth+='        toggle = 0;\n';
sth+='      }\n';
sth+='      else {\n';
sth+='        digitalLow(ZW_B1);\n';
sth+='        digitalLow(ZW_B2);\n';
sth+='        digitalLow(ZW_B3);\n';
sth+='        digitalLow(ZW_B4);\n';
sth+='        toggle = 1;\n';
sth+='      }\n';
sth+='    }\n';
sth+='    else {                    //After any input button is pressed, the LEDs stop flashing\n';
sth+='      if (isHigh(ZW_A1)) {\n';
sth+='        off(ZW_B1);\n';
sth+='        Left_Motor(STOP);\n';
sth+='      }\n';
sth+='      if (isHigh(ZW_A2)) {\n';
sth+='        off(ZW_B2);\n';
sth+='        Left_Motor(STOP);\n';
sth+='      }\n';
sth+='      if (isHigh(ZW_A3)) {\n';
sth+='        off(ZW_B3);\n';
sth+='        Right_Motor(STOP);\n';
sth+='      }\n';
sth+='      if (isHigh(ZW_A4)) {\n';
sth+='        off(ZW_B4);\n';
sth+='        Right_Motor(STOP);\n';
sth+='      }\n';
sth+='    }\n';
sth+='    NumOfTicks++;\n';
sth+='    if (isLow(ZW_A1) || isLow(ZW_A2) || isLow(ZW_A3) || isLow(ZW_A4)) { //\n';
sth+='      NoButtonPressedFlag = false;\n';
sth+='\n';
sth+='      if (isLow(ZW_A1)) {\n';
sth+='        on(ZW_B1);\n';
sth+='        Left_Motor(FORWARD);\n';
sth+='        Right_Motor(STOP);\n';
sth+='      }\n';
sth+='\n';
sth+='      if (isLow(ZW_A2)) {\n';
sth+='        on(ZW_B2);\n';
sth+='        Left_Motor(BACKWARD);\n';
sth+='        Right_Motor(STOP);\n';
sth+='      }\n';
sth+='\n';
sth+='      if (isLow(ZW_A3)) {\n';
sth+='        on(ZW_B3);\n';
sth+='        Left_Motor(STOP);\n';
sth+='        Right_Motor(FORWARD);\n';
sth+='      }\n';
sth+='\n';
sth+='      if (isLow(ZW_A4)) {\n';
sth+='        on(ZW_B4);\n';
sth+='        Left_Motor(STOP);\n';
sth+='        Right_Motor(BACKWARD);\n';
sth+='      }\n';
sth+='    }\n';
sth+='\n';
sth+='  }\n';
sth+='}\n';
Blockly.Arduino.definitions_['levelS'] = sth;
var st = '';
st+=' switch (ProgramSelected) {\n';
st+='\n';
st+='    case 1:\n';
st+='      lesson_1_interrupt();\n';
st+='      break;\n';
st+='\n';
st+='    case 2:\n';
st+='      lesson_2();\n';
st+='      break;\n';
st+='\n';
st+='    case 3:\n';
st+='      lesson_3();\n';
st+='      break;\n';
st+='\n';
st+='    case 4:\n';
st+='      lesson_4();\n';
st+='      break;\n';
st+='\n';
st+='    case 5:\n';
st+='      lesson_5();\n';
st+='      break;\n';
st+='\n';
st+='    case 6:\n';
st+='      lesson_6();\n';
st+='      break;\n';
st+='\n';
st+='    case 7:\n';
st+='   \n';
st+='      lesson_7();\n';
st+='      break;\n';
st+='\n';
st+='    case 8:\n';
st+='      lesson_8();\n';
st+='      break;\n';
st+='\n';
st+='    case 9:\n';
st+='      lesson_9();\n';
st+='      break;\n';
st+='\n';
st+='    case 10:\n';
st+='      lesson_10();\n';
st+='      break;\n';
st+='\n';
st+='    case 11:\n';
st+='      lesson_11();\n';
st+='      break;\n';
st+='  }\n';
var code = st;
return code;
};

Blockly.Arduino.handlebarLeft = function() {
	Blockly.Arduino.setups_['bar_b1'] = 'handlebarservo.attach(handlebar_B1_SERVO);\n' +
		'  barPosition = barinitPos;\n' +
		'  handlebarservo.write(barPosition);\n\n	';

	Blockly.Arduino.definitions_['bar_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['bar_b1'] = 
		'Servo    handlebarservo;\n' +
		'double   barPosition;\n';
	var code = 'handlebar(handlebarservo,&barPosition,-2,60);\n';

	return code;
};

Blockly.Arduino.handlebarRight = function() {
	Blockly.Arduino.setups_['paw_b2'] = 'handlebarservo.attach(handlebar_B1_SERVO);\n' +
		'  barPosition = barinitPos;\n' +
		'  handlebarservo.write(barPosition);\n\n	';

	Blockly.Arduino.definitions_['bar_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['bar_b1'] = 
		'Servo    handlebarservo;\n' +
		'double   barPosition;\n';
	var code = 'handlebar(handlebarservo,&barPosition,2,120);\n';
	
	return code;
};

Blockly.Arduino.handlebarReturn = function() {
	Blockly.Arduino.setups_['paw_b2'] = 'handlebarservo.attach(handlebar_B1_SERVO);\n' +
		'  barPosition = barinitPos;\n' +
		'  handlebarservo.write(barPosition);\n\n	';

	Blockly.Arduino.definitions_['bar_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['bar_b1'] = 
		'Servo    handlebarservo;\n' +
		'double   barPosition;\n';
	var code = 'motorbikeDirectionReturnBack(handlebarservo,&barPosition);\n';
	
	return code;
};

Blockly.Arduino.shovelUp = function() {
	Blockly.Arduino.setups_['shovel_b2'] = 'shovelservo.attach(shovel_B2_SERVO);\n' +
		'  shovelPosition = shovelinitPos;\n' +
		'  shovelservo.write(shovelPosition);\n\n	';

	Blockly.Arduino.definitions_['servo'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['shovel_b2'] = 
		'Servo    shovelservo;\n' +
		'double   shovelPosition;\n';
	var code = 'shovel(shovelservo,&shovelPosition,2,180);\n';

	return code;
};

Blockly.Arduino.shovelDown = function() {
	Blockly.Arduino.setups_['shovel_b2'] = 'shovelservo.attach(shovel_B2_SERVO);\n' +
		'  shovelPosition = shovelinitPos;\n' +
		'  shovelservo.write(shovelPosition);\n\n	';

	Blockly.Arduino.definitions_['servo'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['shovel_b2'] = 
		'Servo    shovelservo;\n' +
		'double   shovelPosition;\n';
	var code = 'shovel(shovelservo,&shovelPosition,-2,0);\n';
	
	return code;
};

Blockly.Arduino.armUp = function() {
	Blockly.Arduino.setups_['arm_b1'] = 'armservo.attach(arm_B1_SERVO);\n' +
		'  armPosition = arminitPos;\n' +
		'  armservo.write(armPosition);\n\n	';

	Blockly.Arduino.definitions_['servo'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['arm_b1'] = 
		'Servo    armservo;\n' +
		'double   armPosition;\n';
	var code = 'arm(armservo,&armPosition,2,180);\n';

	return code;
};

Blockly.Arduino.armDown = function() {
	Blockly.Arduino.setups_['arm_b1'] = 'armservo.attach(arm_B1_SERVO);\n' +
		'  armPosition = arminitPos;\n' +
		'  armservo.write(armPosition);\n\n	';

	Blockly.Arduino.definitions_['servo'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['arm_b1'] = 
		'Servo    armservo;\n' +
		'double   armPosition;\n';
	var code = 'arm(armservo,&armPosition,-1,0);\n';
	
	return code;
};

Blockly.Arduino.pawOpen = function() {
	Blockly.Arduino.setups_['paw_b1'] = 'OpenCloseservo.attach(paw_B1_SERVO);\n' +
		'  OpenClosePosition = OpenCloseinitPos;\n' +
		'  OpenCloseservo.write(OpenClosePosition);\n';

	Blockly.Arduino.definitions_['paw_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['paw_b1'] = 
		'Servo    OpenCloseservo;\n' +
		'double   OpenClosePosition;\n\n';
	var code = 'servoChange(OpenCloseservo,&OpenClosePosition,-2,90);\n';

	return code;
};

Blockly.Arduino.pawClose = function() {
	Blockly.Arduino.setups_['paw_b1'] = 'OpenCloseservo.attach(paw_B1_SERVO);\n' +
		'  OpenClosePosition = OpenCloseinitPos;\n' +
		'  OpenCloseservo.write(OpenClosePosition);\n  ';

	Blockly.Arduino.definitions_['paw_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['paw_b1'] = 
		'Servo    OpenCloseservo;\n' +
		'double   OpenClosePosition;\n\n';
	var code = 'servoChange(OpenCloseservo,&OpenClosePosition,2,20);\n';

	return code;
};

Blockly.Arduino.pawUp = function() {
	Blockly.Arduino.setups_['paw_b2'] = 'UpDownservo.attach(paw_B2_SERVO);\n' +
		'  UpDownPosition = UpDowninitPos;\n' +
		'  UpDownservo.write(UpDownPosition);\n\n	';

	Blockly.Arduino.definitions_['paw_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['paw_b2'] = 
		'Servo    UpDownservo;\n' +
		'double   UpDownPosition;\n';
	var code = 'servoChange(UpDownservo,&UpDownPosition,-2,90);\n';

	return code;
};

Blockly.Arduino.pawDown = function() {
	Blockly.Arduino.setups_['paw_b2'] = 'UpDownservo.attach(paw_B2_SERVO);\n' +
		'  UpDownPosition = UpDowninitPos;\n' +
		'  UpDownservo.write(UpDownPosition);\n\n  ';
	Blockly.Arduino.definitions_['paw_b'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' ;
	Blockly.Arduino.definitions_['paw_b2'] = 
		'Servo    UpDownservo;\n' +
		'double   UpDownPosition;\n';
	var code = 'servoChange(UpDownservo,&UpDownPosition,2,60);\n';

	return code;
};

Blockly.Arduino.MotorControl = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var dropdown_MotorName = this.getFieldValue('MotorName');
	var MotorStatus = this.getFieldValue('RunningStatus');
	var speedValue = this.getFieldValue('speedValue');
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'MotorControl(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ');\n';
	return code;
};
Blockly.Arduino.MotorControlLT = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var dropdown_MotorName = this.getFieldValue('MotorName');
	var MotorStatus = this.getFieldValue('RunningStatus');
	var speedValue = this.getFieldValue('speedValue');
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'MotorControl(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ');\n';
	return code;
};

Blockly.Arduino.left_motor = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	var dropdown_MotorName = '1';
	var MotorStatus = this.getFieldValue('direction');
	var speedValue = this.getFieldValue('motorSpeed');
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'MotorControl(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ');\n';
	return code;
};

Blockly.Arduino.right_motor = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	var dropdown_MotorName = '2';
	var MotorStatus = this.getFieldValue('direction');
	var speedValue = this.getFieldValue('motorSpeed');
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'MotorControl(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ');\n';
	return code;
};

Blockly.Arduino.fireBoom = function() {//main-b1,throw-b2
	Blockly.Arduino.setups_['fireBoom'] ='  MainPos = Main_initPos;\n ThrowPos = Throw_initPos;\n'+ 'B1_mian_servo.attach(Main_SERVO);\n  B1_mian_servo.write(MainPos);\n'+'  B2_throw_servo.attach(Throw_SERVO);\n  B2_throw_servo.write(ThrowPos);\n' ; 

	Blockly.Arduino.definitions_['filter'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo B2_throw_servo;\n\n'+ 'Servo B1_mian_servo;\n\n' + '\n' +
		'double MainPos ;\n'+'double ThrowPos ;\n' + 'double angB1 ;\n'+ 'double angB2 ;\n';
	var code = 'throwTheBall(B1_mian_servo,B2_throw_servo);';
	return code;
};

Blockly.Arduino.filter = function() {//b1,b2
	Blockly.Arduino.setups_['fireBoom'] ='  MainPos = Main_initPos;\n ThrowPos = Throw_initPos;\n'+ 'B1_mian_servo.attach(Main_SERVO);\n  B1_mian_servo.write(MainPos);\n'+'  B2_throw_servo.attach(Throw_SERVO);\n  B2_throw_servo.write(ThrowPos);\n' ; 

	Blockly.Arduino.definitions_['filter'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo B2_throw_servo;\n\n'+ 'Servo B1_mian_servo;\n\n' + '\n' +
		'double MainPos ;\n'+'double ThrowPos ;\n' + 'double angB1 ;\n'+ 'double angB2 ;\n';
	var code = 'filterTheBall(B1_mian_servo,B2_throw_servo);';
	return code;
};


Blockly.Arduino.lfet_punches = function() {//b2
	Blockly.Arduino.setups_['lfet_punches'] ='leftPos = Left_initPos;\n '+ ' left_fist_servo.attach(Left_Fist_SERVO);\n  left_fist_servo.write(leftPos);\n';

	Blockly.Arduino.definitions_['punches'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo left_fist_servo;\n\n'+  '\n' +
		'double leftPos ;\n'  + 'Servo right_fist_servo;\n\n'+  '\n' +
		'double rightPos ;\n' ;
	var code = 'leftPunches(left_fist_servo);';
	return code;
};

Blockly.Arduino.lfet_takeAFist = function() {//b2
	Blockly.Arduino.setups_['lfet_punches'] ='leftPos = Left_initPos;\n '+ ' left_fist_servo.attach(Left_Fist_SERVO);\n  left_fist_servo.write(leftPos);\n';

	Blockly.Arduino.definitions_['punches'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo left_fist_servo;\n\n'+  '\n' +
		'double leftPos ;\n'  + 'Servo right_fist_servo;\n\n'+  '\n' +
		'double rightPos ;\n' ;
	var code = 'leftTakeAFist(left_fist_servo);';
	return code;
};

Blockly.Arduino.right_punches = function() {//b1
	Blockly.Arduino.setups_['right_punches'] ='rightPos = Right_initPos;\n '+ ' right_fist_servo.attach(Right_Fist_SERVO);\n  right_fist_servo.write(rightPos);\n';

	Blockly.Arduino.definitions_['punches'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo left_fist_servo;\n\n'+  '\n' +
		'double leftPos ;\n'  + 'Servo right_fist_servo;\n\n'+  '\n' +
		'double rightPos ;\n' ;
	var code = 'rightPunches(right_fist_servo);';
	return code;
};

Blockly.Arduino.right_takeAFist = function() {//b1
	Blockly.Arduino.setups_['right_punches'] ='rightPos = Right_initPos;\n '+ ' right_fist_servo.attach(Right_Fist_SERVO);\n  right_fist_servo.write(rightPos);\n';

	Blockly.Arduino.definitions_['punches'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo left_fist_servo;\n\n'+  '\n' +
		'double leftPos ;\n'  + 'Servo right_fist_servo;\n\n'+  '\n' +
		'double rightPos ;\n' ;
	var code = 'rightTakeAFist(right_fist_servo);';
	return code;
};

Blockly.Arduino.loadingCarriage = function() {//b1
	Blockly.Arduino.setups_['loadingCarriage'] ='carriagePos = Carriage_initPos;\n '+ ' carrriage_servo.attach(Carriage_SERVO);\n  carrriage_servo.write(carriagePos);\n';

	Blockly.Arduino.definitions_['loadingCarriage'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo carrriage_servo;\n\n'+  '\n' +
		'double carriagePos ;\n' ;
	var code = 'loadingCarriage(carrriage_servo);';
	return code;
};

Blockly.Arduino.unloadingCarriage = function() {//b1
	Blockly.Arduino.setups_['loadingCarriage'] ='carriagePos = Carriage_initPos;\n '+ ' carrriage_servo.attach(Carriage_SERVO);\n  carrriage_servo.write(carriagePos);\n';

	Blockly.Arduino.definitions_['loadingCarriage'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo carrriage_servo;\n\n'+  '\n' +
		'double carriagePos ;\n' ;
	var code = 'unloadingCarriage(carrriage_servo);';
	return code;
};


var colorArr = '';
var indexN = 0;
var strColorArr;
Blockly.Arduino.colorChoose = function() {
  // Create a list with any number of elements of any type.
//var dropdown_type = this.getFieldValue('TYPE');
//var varName = Blockly.Arduino.variableDB_.getName(this.getFieldValue('VAR'),
//    Blockly.Variables.NAME_TYPE);
//var size=window.parseFloat(this.getFieldValue('SIZE'));    
  var code = new Array(this.itemCount_);
  for (var n = 0; n < this.itemCount_; n++) {
    code[n] = Blockly.Arduino.valueToCode(this, 'ADD' + n, 
        Blockly.Arduino.ORDER_NONE);
       var  codePro =  code;	
       codePro = codePro.join('');
//     console.log(codePro[0].split('=')[1])	
        (function (){
        var tempa = codePro.split('=');
        	for(var x=0;x<tempa.length;x++){
        		
        		(function (){
        			var tempaIndex = x+1;
        			var p = /[a-z]/i;
        			if(tempa[x]==''||p.test(tempa[x])==false){
        				tempa.splice(x, 1);
        			}else{
        				tempa[x]= tempa[x].replace(/[0-9]/g,'');
        				tempa[x] = tempa[x]+'='+tempaIndex;
        			}
        		})()
        		code=tempa;
//      		var temp_num = tempa.length+1;
//      		code.push('INVALID='+temp_num);
        		        	}
        	
        })()
  }
  var temp_num = code.length+1;
  code.push('INVALID='+temp_num);
strColorArr = code;
//for(var codeIndex = 0;codeIndex<code.length;codeIndex++){
//	var p = /[a-z]/i;
//	if(p.test(code[codeIndex])==false){
//		code.splice(codeIndex, 1);
//	}
//}
//console.log(code)
if(code.length == 0){
	var hasComma = '';
}else{
	var hasComma = ',';
}
var max_num = this.itemCount_+1;
var stc = '';
stc+='         Serial.begin(115200);       \n'
stc+='         pinMode(ZW_A1,INPUT);\n'
stc+='         pinMode(ZW_B1,OUTPUT);\n'
stc+='         \n'
stc+='            rgb.red = 0;\n'
stc+='            rgb.red_min = 255;\n'
stc+='            rgb.red_max = 0;\n'
stc+='            rgb.green = 0;\n'
stc+='            rgb.green_min = 255;\n'
stc+='            rgb.green_max = 0;\n'
stc+='            rgb.blue = 0;\n'
stc+='            rgb.blue_min = 255;\n'
stc+='            rgb.blue_max = 0;\n'
stc+='         if (tcs.begin()) {\n'
stc+='           Serial.println(F("Sensor founded!"));\n'
stc+='         } else {\n'
stc+='           Serial.println(F("TCS34725 is not available, please try check it !"));\n'
stc+='           while (1); \n'
stc+='         } \n'
stc+='     \n'
stc+='         tcs.setInterrupt(false);\n'
stc+='         digitalWrite(ZW_B1,HIGH);\n'
stc+='     \n'
stc+='     if(CALIBRATION_COLOR)\n'
stc+='     {\n'
stc+='          Serial.println(F("======================================================================="));\ndelay(50);\n'
stc+='          Serial.println(F("Please follow bellow steps to calibration those colors."));  \ndelay(50);\n'
stc+='          Serial.println(F("Step 1: Read the color of surrounding."));\ndelay(50);\n'
stc+='          Serial.println(F("\t  Please keep nothing and try to adjust the position of the sensor, then press button A1."));\ndelay(50);\n'
stc+='          Serial.print  (F("\t  Please do the same steps and try ")); Serial.print(COLOR_CALIBRATION_TIMES); Serial.println(F(" times at least."));\ndelay(50);\n'
stc+='          Serial.println(F("\t  Please press button A2 when finished. It will save the surrounding color data to EEPROM."));   \ndelay(50);\n'
stc+='     }\n'
stc+='     else\n'
stc+='     {\n'
stc+='           for(int i = 0; i< COLOR_NUM_MAX; i++)\n'
stc+='           {\n'
stc+='           int COLOR_START_POS;\n'
stc+='           COLOR_START_POS  =COLOR1_START_POS +  i * COLOR_LENGTH;\n'
stc+='           EEPROM.get(COLOR_START_POS,RGB_STORE_DATA[i]);\n'
stc+='           Serial.print(F("Read Color ")); Serial.print(i);Serial.print(F(" data from EEPROM "));Serial.print(COLOR_START_POS); Serial.print(F(":\t"));    \n'
stc+='           Serial.print(F(" red:")); Serial.print(RGB_STORE_DATA[i].red, DEC); Serial.print(F(":"));Serial.print(RGB_STORE_DATA[i].red_max, DEC); Serial.print(F(":"));Serial.print(RGB_STORE_DATA[i].red_min, DEC);\n'
stc+='           Serial.print(F(" green:"));Serial.print(RGB_STORE_DATA[i].green, DEC);Serial.print(F(":")); Serial.print(RGB_STORE_DATA[i].green_max, DEC); Serial.print(F(":"));Serial.print(RGB_STORE_DATA[i].green_min, DEC);\n'
stc+='           Serial.print(F(" blue:")); Serial.print(RGB_STORE_DATA[i].blue, DEC);Serial.print(F(":"));Serial.print(RGB_STORE_DATA[i].blue_max, DEC); Serial.print(F(":"));Serial.print(RGB_STORE_DATA[i].blue_min, DEC);\n'
stc+='           Serial.println(F(""));\n'
stc+='     }\n'
stc+='     }\n'
stc+='     \n'
stc+='     \n'


  //Blockly.Arduino.definitions_['colorChoose'] = '#include "PS2.h"\n';   //added by Liang 20190912
  Blockly.Arduino.definitions_['colorChoose'] = '#include <EasyButton.h>\n';
  Blockly.Arduino.definitions_['colorChoose'] += '#include "Adafruit_TCS34725.h"\n';
  Blockly.Arduino.definitions_['colorChoose'] += '#include "EEPROM.h"\n'; 
  Blockly.Arduino.definitions_['colorChoose'] += 'enum'+' '+'color_type'+'\n'+ '{NOTHING =0'+hasComma+ code.join(', ') + '};\n'+'#define  COLOR_NUM_MAX       '+max_num+'\n';
   Blockly.Arduino.setups_['colorChoose'] = stc;
  //var code =''+varName+'['+size+"]"+'='+ '{' + code.join(', ') + '};\n';
  //Blockly.Arduino.setups_['setup_lists'+varName] = code;
  return ;
};

Blockly.Arduino.bollColor = function() {
	
//	if(colorArr.indexOf(Blockly.Arduino.variableDB_.getName(this.getFieldValue('bollColor'), Blockly.Variables.NAME_TYPE)) == -1 ){
//	if(typeof(indexN) == 'string'){
//	var    b = a.split('=').length -1;
//	}
//	indexN = colorArr.replace(/[^0-9]/ig,""); 
//	console.log(indexN)
//	if(indexN == 0){
//		indexN = 1;
//	}else if(indexN == 1){
//		indexN = 2;
//	}else if(indexN == 2){
//		indexN = 3;
//	}
//	var 	b = a.split('=').length;
//			console.log(typeof(a))
//var b=a;
  		var code   = Blockly.Arduino.variableDB_.getName(this.getFieldValue('bollColor'), Blockly.Variables.NAME_TYPE)+'=';
//	}
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.bollChoosed = function() {
	
	var bollChoose = this.getFieldValue('bollChoose');
	Blockly.Arduino.definitions_['bollChoosed'] ='';
	var code = 'checkBolls('+bollChoose+')';
	
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.intelligentLearning = function() {   //219 220 行a1 a2(确认按钮)
	
	var isTrue = this.getFieldValue('intelligent');
	var intelligentLearning = '';
	if(isTrue == 1){
		intelligentLearning = true;
	}else if(isTrue == 0){
		intelligentLearning = false;
	}
	var strColorArrLength = strColorArr.length+1;
	var newStrColorString='';
	for (var i=0;i<strColorArr.length;i++) {
		newStrColorString +=strColorArr[i].replace('=','","');
	}
	newStrColorString=newStrColorString.replace(/\d+/g,'');
	newStrColorString=newStrColorString.substring(0,newStrColorString.length-2);
	newStrColorString="\""+newStrColorString;
	var str = '';
	str+='bool  CALIBRATION_COLOR ='+intelligentLearning+';\n\n';
	str+='     String StrColor['+strColorArrLength+']={"NOTHING",'+newStrColorString+'};\n'
str+='     int PS2_Button_Read[6];\n'
str+='     \n'
str+='     typedef struct{\n'
str+='     uint8_t red;\n'
str+='     uint8_t green;\n'
str+='     uint8_t blue;\n'
str+='     uint8_t red_max;\n'
str+='     uint8_t red_min;\n'
str+='     uint8_t green_max;\n'
str+='     uint8_t green_min;\n'
str+='     uint8_t blue_max;\n'
str+='     uint8_t blue_min;\n'
str+='     } RGB_type;\n'
str+='     \n'
str+='     RGB_type rgb;\n'
str+='     \n'
str+='     RGB_type RGB_STORE_DATA[COLOR_NUM_MAX];\n'
str+='     Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);  \n'
str+='        \n'
str+='     const int buttonPin = ZW_A1;  \n' 
str+='     const int buttonPinConfirm = ZW_A2;  \n'
str+='     \n'
str+='     int num = 0;\n'
str+='     int ColorNum = 0;\n'
str+='     \n'
str+='     void sensorMode();\n'
str+='     \n'
str+='        EasyButton button(buttonPin,sensorMode,CALL_IN_PUSHED);\n'
str+='        EasyButton buttonConfirm(buttonPinConfirm);\n'
str+='     \n'
str+='     void sensorMode(){  \n'
str+='     uint16_t clearcol, red, green, blue;\n'
str+='     tcs.getRawData(&red,&green,&blue,&clearcol);\n'
str+='     uint32_t sum = clearcol;\n'
str+='     float r, g, b;\n'
str+='     r = red; r /= sum;\n'
str+='     g = green; g /= sum;\n'
str+='     b = blue; b /= sum;\n'
str+='     r *= 256; g *= 256; b *= 256;   \n'
str+='        \n'
str+='     rgb.red = (int)r;\n'
str+='     rgb.green = (int)g;\n'
str+='     rgb.blue = (int)b;\n'
str+='        \n'
str+='     if(rgb.red_max < rgb.red)\n'
str+='     rgb.red_max = rgb.red;\n'
str+='        if(rgb.red_min > rgb.red)\n'
str+='     rgb.red_min = rgb.red;\n'
str+='     \n'
str+='         if(rgb.green_max < rgb.green)\n'
str+='     rgb.green_max = rgb.green;\n'
str+='        if(rgb.green_min > rgb.green)\n'
str+='     rgb.green_min = rgb.green;\n'
str+='     \n'
str+='         if(rgb.blue_max < rgb.blue)\n'
str+='     rgb.blue_max = rgb.blue;\n'
str+='        if(rgb.blue_min > rgb.blue)\n'
str+='     rgb.blue_min = rgb.blue;\n'
str+='     \n'
str+='     num++;\n'
str+='     \n'
str+='     Serial.print((int)num, DEC);\n'
str+='     Serial.print(":\t");\n'
str+='     \n'
str+='     if( CALIBRATION_COLOR == true)\n'
str+='     {\n'
str+='         Serial.print(rgb.red, DEC); Serial.print(F("\t"));Serial.print(rgb.green, DEC); Serial.print(F("\t"));Serial.print(rgb.blue, DEC);\n'
str+='         Serial.print(F(" R:")); Serial.print(rgb.red_max, DEC); Serial.print(F(":"));Serial.print(rgb.red_min, DEC);\n'
str+='         Serial.print(F(" G:")); Serial.print(rgb.green_max, DEC); Serial.print(F(":"));Serial.print(rgb.green_min, DEC);\n'
str+='         Serial.print(F(" B:")); Serial.print(rgb.blue_max, DEC); Serial.print(F(":"));Serial.print(rgb.blue_min, DEC);\n'
str+='     }\n'
str+='     else\n'
str+='     {\n'
str+='        Serial.print(rgb.red, HEX);Serial.print(rgb.green, HEX);Serial.print(rgb.blue, HEX); \n'
str+='     }\n'
str+='     Serial.println();\n'
str+='     \n'
str+='        }\n'
str+='     \n'
str+='        \n'
str+='        \n'
str+='     \n'
str+='     \n'
str+='     color_type CheckColor(RGB_type rgb_data)\n'
str+='     {\n'
str+='        color_type color = INVALID;\n'
str+='           for(int i = 0; i< COLOR_NUM_MAX; i++)\n'
str+='           {\n'
str+='               boolean red_in_limit = false;\n'
str+='               boolean green_in_limit = false;\n'
str+='               boolean blue_in_limit = false;\n'
str+='               if((rgb_data.red <   RGB_STORE_DATA[i].red_max) &&  (rgb_data.red >   RGB_STORE_DATA[i].red_min)) \n'
str+='               {\n'
str+='                  red_in_limit = true;  \n'
str+='               }  \n'
str+='               if((rgb_data.green <   RGB_STORE_DATA[i].green_max) &&  (rgb_data.green >   RGB_STORE_DATA[i].green_min)) \n'
str+='               {\n'
str+='                  green_in_limit = true;  \n'
str+='               }  \n'
str+='               if((rgb_data.blue <   RGB_STORE_DATA[i].blue_max) &&  (rgb_data.blue >   RGB_STORE_DATA[i].blue_min)) \n'
str+='               {\n'
str+='                  blue_in_limit = true;  \n'
str+='               }  \n'
str+='     \n'
str+='               if(red_in_limit && green_in_limit && blue_in_limit)\n'
str+='               {\n'
str+='                 color = i;\n'
str+='               }\n'
str+='             \n'
str+='           }\n'
str+='         return color;\n'
str+='     }\n'
str+='     \n'
str+='     \n'
str+='     boolean checkBolls(char bollChoosed)\n'
str+='     {  	\n'
str+='     \n'
str+='     if( CALIBRATION_COLOR == true)\n'
str+='     {\n'
str+='         button.update();\n'
str+='         buttonConfirm.update();\n'
str+='         if(buttonConfirm.IsPushed() &&( num >=COLOR_CALIBRATION_TIMES)  )\n'
str+='         {       \n'
str+='           if((rgb.red_max  - rgb.red_min) >COLOR_TOLERANCE_MAX  ||\n'
str+='               (rgb.green_max  - rgb.green_min) >COLOR_TOLERANCE_MAX  ||\n'
str+='               (rgb.blue_max  - rgb.blue_min) >COLOR_TOLERANCE_MAX )\n'
str+='           {\n'
str+='             Serial.println("ERROR, please re-calibration this object");\n'
str+='             num = 0;\n'
str+='             rgb.red = 0;\n'
str+='             rgb.red_min = 255;\n'
str+='             rgb.red_max = 0;\n'
str+='             rgb.green = 0;\n'
str+='             rgb.green_min = 255;\n'
str+='             rgb.green_max = 0;\n'
str+='             rgb.blue = 0;\n'
str+='             rgb.blue_min = 255;\n'
str+='             rgb.blue_max = 0;\n'
str+='           }\n'
str+='           else\n'
str+='           {        \n'
str+='              int COLOR_START_POS;\n'
str+='             COLOR_START_POS  =COLOR1_START_POS +  ColorNum * COLOR_LENGTH;\n'
str+='         \n'
str+='             RGB_STORE_DATA[ColorNum].red =(int) (rgb.red_max + rgb.red_min)/2;\n'
str+='             RGB_STORE_DATA[ColorNum].green =(int) (rgb.green_max + rgb.green_min)/2;\n'
str+='             RGB_STORE_DATA[ColorNum].blue =(int) (rgb.blue_max + rgb.blue_min)/2;\n'
str+='         \n'
str+='             rgb.red_max     += COLOR_TOLERANCE;\n'
str+='             rgb.red_min     -=  COLOR_TOLERANCE;\n'
str+='             rgb.green_max   += COLOR_TOLERANCE;\n'
str+='             rgb.green_min   -= COLOR_TOLERANCE;\n'
str+='             rgb.blue_max    += COLOR_TOLERANCE;\n'
str+='             rgb.blue_min    -= COLOR_TOLERANCE;\n'
str+='     \n'
str+='             RGB_STORE_DATA[ColorNum].red_max = constrain(rgb.red_max,0,255);\n'
str+='             RGB_STORE_DATA[ColorNum].red_min = constrain(rgb.red_min,0,255);\n'
str+='             RGB_STORE_DATA[ColorNum].green_max = constrain(rgb.green_max,0,255);\n'
str+='             RGB_STORE_DATA[ColorNum].green_min = constrain(rgb.green_min,0,255);\n'
str+='             RGB_STORE_DATA[ColorNum].blue_max = constrain(rgb.blue_max,0,255);\n'
str+='             RGB_STORE_DATA[ColorNum].blue_min = constrain(rgb.blue_min,0,255);\n'
str+='         \n'
str+='             EEPROM.put(COLOR_START_POS, RGB_STORE_DATA[ColorNum]); \n'
str+='             Serial.print(F("Write Color ")); Serial.print(ColorNum);Serial.print(F(" data to EEPROM "));Serial.print(COLOR_START_POS); Serial.println(F(":\t"));    \n'
str+='             Serial.print(F(" red:")); Serial.print(rgb.red, DEC); Serial.print(F(":"));Serial.print(rgb.red_max, DEC); Serial.print(F(":"));Serial.print(rgb.red_min, DEC);\n'
str+='             Serial.print(F(" green:"));Serial.print(rgb.green, DEC);Serial.print(F(":")); Serial.print(rgb.green_max, DEC); Serial.print(F(":"));Serial.print(rgb.green_min, DEC);\n'
str+='             Serial.print(F(" blue:")); Serial.print(rgb.blue, DEC);Serial.print(F(":"));Serial.print(rgb.blue_max, DEC); Serial.print(F(":"));Serial.print(rgb.blue_min, DEC);\n'
str+='             Serial.println(F(""));\n'
str+='           num = 0;\n'
str+='           rgb.red = 0;\n'
str+='           rgb.red_min = 255;\n'
str+='           rgb.red_max = 0;\n'
str+='           rgb.green = 0;\n'
str+='           rgb.green_min = 255;\n'
str+='           rgb.green_max = 0;\n'
str+='           rgb.blue = 0;\n'
str+='           rgb.blue_min = 255;\n'
str+='           rgb.blue_max = 0;\n'
str+='           ColorNum++;\n'
str+='     \n'
str+='           if((ColorNum > 0) && (ColorNum <COLOR_NUM_MAX)  ) \n'
str+='           {\n'
str+='               Serial.print(F("Step ")); Serial.print(ColorNum+1); Serial.print(F(": Read the color of No."));Serial.print(ColorNum); Serial.println(F(" object"));\n'
str+='               Serial.print(F("\t  Please put No."));Serial.print(ColorNum); Serial.println(F(" object and try to adjust the position of the sensor, then press button A1."));\n'
str+='               Serial.print(F("\t  Please do the same steps and try ")); Serial.print(COLOR_CALIBRATION_TIMES); Serial.println(F(" times at least."));\n'
str+='               Serial.print(F("\t  Please press button A2 when finished. it will save the color data of No."));Serial.print(ColorNum);Serial.println(F(" object to EEPROM."));\n'
str+='           } \n'
str+='           if( ColorNum >= COLOR_NUM_MAX) {\n'
str+='             CALIBRATION_COLOR = false;\n'
str+='             Serial.println(F("Calibrantion finished.!!!"));\n'
str+='             };\n'
str+='           }\n'
str+='         }\n'
str+='     \n'
str+='     }\n'
str+='     else\n'
str+='     {\n'
str+='         color_type color;\n'
str+='         sensorMode();\n'
str+='     \n'
str+='         color = CheckColor(rgb);\n'
str+='         Serial.print(F(" The bollChose of this object is ")); Serial.println(bollChoosed); Serial.print(F(" The color of this object is ")); Serial.println(color);\n'
str+='         delay(1000);\n'
str+='         \n'
str+='        if(color == bollChoosed){\n'
str+='        	return true;\n'
str+='        }else{\n'
str+='     		return false;\n'
str+='        }\n'
str+='     }\n'
str+='     \n'
str+='     }\n'
	   
	
	Blockly.Arduino.definitions_['intelligentLearning'] = str;
  return 
};




Blockly.Arduino.intoAuto = function() {
	// TODO: Assemble JavaScript into code variable.
//	Blockly.Arduino.setups_['intoAuto'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(LEFT_IR_SENSOR,INPUT);\n  pinMode(RIGHT_IR_SENSOR,INPUT);';
	

	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'changeFollowFlagTrue();\n';
	return code; 
};

Blockly.Arduino.isAuto = function() {
	// TODO: Assemble JavaScript into code variable.
//	Blockly.Arduino.setups_['intoAuto'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(LEFT_IR_SENSOR,INPUT);\n  pinMode(RIGHT_IR_SENSOR,INPUT);';
	

	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'isAuto()';
	return [code,0];
};

Blockly.Arduino.outAuto = function() {
	// TODO: Assemble JavaScript into code variable.
//	Blockly.Arduino.setups_['intoAuto'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n   pinMode(LEFT_IR_SENSOR,INPUT);\n pinMode(RIGHT_IR_SENSOR,INPUT);';
	

	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'changeFollowFlagFalse();\n';
	return code; 
};


Blockly.Arduino.twoSensor = function() {//a1.a2
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['intoAuto'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(LEFT_IR_SENSOR,INPUT);\n  pinMode(RIGHT_IR_SENSOR,INPUT);\n  Serial.begin(115200);';
	var leftOne = this.getFieldValue('leftSensor');
    var rightOne = this.getFieldValue('rightSensor');	
//	Blockly.Arduino.definitions_['intoAuto'] = 'boolean h;';
	var h = '';
	h='howFollow(LEFT_IR_SENSOR,RIGHT_IR_SENSOR,'+leftOne+','+rightOne+')';
	
	var code = h;
	return [code,0];
};





Blockly.Arduino.left_turn_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	var speed = this.getFieldValue('left_turn_speed');
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'left_turn_speed('+speed+');\n';
	return code;
};
Blockly.Arduino.right_turn_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	var speed = this.getFieldValue('right_turn_speed');
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'right_turn_speed('+speed+');\n';
	return code;
};
Blockly.Arduino.go_forward_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
var speed = this.getFieldValue('go_forward_speed');
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'go_forward_speed('+speed+');\n';
	return code;
};
Blockly.Arduino.go_reverse_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
var speed = this.getFieldValue('go_reverse_speed');
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'go_reverse_speed('+speed+');\n';
	return code;
};






Blockly.Arduino.left_turn = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';

	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'goLeftTurn();\n';
	return code;
};

Blockly.Arduino.right_turn = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'goRightTurn();\n';
	return code;
};

Blockly.Arduino.go_forward = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
//	Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];\n enum colorType\n{'+LIST+'}'
	var code = 'goForward();\n';
	return code;
};
Blockly.Arduino.readyFire = function() {//b1
	Blockly.Arduino.setups_['readyFire'] = 'goFire_servo.attach(FIRE_SERVO);\n  goFire_servo.write(fire_initPos);' + 'firePos = fire_initPos;\n' + '  moveFlag = true; \n ';

	Blockly.Arduino.definitions_['readyFire'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo goFire_servo;\n\n' + '\n' +
		'double firePos ;' + 'double ang ;' + 'bool moveFlag;';
	var code = 'fire(goFire_servo,&ang);';
	return code;
};
Blockly.Arduino.accumulating = function() {//b1
	Blockly.Arduino.setups_['readyFire'] = 'goFire_servo.attach(FIRE_SERVO);\n  goFire_servo.write(fire_initPos);' + 'firePos = fire_initPos;\n' + '  moveFlag = true; \n ';

	Blockly.Arduino.definitions_['readyFire'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo goFire_servo;\n\n' + '\n' +
		'double firePos ;' + 'double ang ;' + 'bool moveFlag;';
	var code = 'acc(goFire_servo,&ang);';
	return code;
};
Blockly.Arduino.fire = function() {//b1
	Blockly.Arduino.setups_['readyFire'] = 'goFire_servo.attach(FIRE_SERVO);\n  goFire_servo.write(fire_initPos);' + 'firePos = fire_initPos;\n' + '  moveFlag = true; \n ';

	Blockly.Arduino.definitions_['readyFire'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo goFire_servo;\n\n' + '\n' +
		'double firePos ;' + 'double ang ;' + 'bool moveFlag;';
	var code = 'fired(goFire_servo,&ang);';
	return code;
};
Blockly.Arduino.pull = function() {//M1
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['pull'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'pull();\n';
	return code;
};
Blockly.Arduino.pull2 = function() {//M1
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['pull2'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'pull2();\n';
	return code;
};

Blockly.Arduino.pull_another = function() {//M2
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['pull_another'] = 'pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'pull_another();\n';
	return code;
};
Blockly.Arduino.pull_another2 = function() {//M2
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['pull_another2'] = 'pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'pull_another2();\n';
	return code;
};
//、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
Blockly.Arduino.leftwards = function() {//b1
	Blockly.Arduino.setups_['leftwards'] = 'lamp_servo.attach(LAMP_SERVO);\n  lamp_servo.write(lamp_initPos_new);';

	Blockly.Arduino.definitions_['leftwards'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo lamp_servo;\n\n' + '\n'  + 'double angL ;';
	var code = 'lampMoveL(lamp_servo,&angL);';
	return code;
};

Blockly.Arduino.rightwards = function() {//b1
	Blockly.Arduino.setups_['rightwards'] = 'lamp_servo.attach(LAMP_SERVO);\n  lamp_servo.write(lamp_initPos_new);';

	Blockly.Arduino.definitions_['leftwards'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo lamp_servo;\n\n' + '\n'  + 'double angL ;';
	var code = 'lampMoveR(lamp_servo,&angL);';
	return code;
};

//、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、

Blockly.Arduino.chassis_leftwards = function() {//b2
	Blockly.Arduino.setups_['chassis_leftwards'] = 'chassis_servo.attach(CHASSIS_SERVO);\n  chassis_servo.write(lamp_initPos);';

	Blockly.Arduino.definitions_['chassis_leftwards'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo chassis_servo;\n\n' + '\n' +
		'double ang ;' + 'bool moveFlag;';
	var code = 'chassisMoveL(chassis_servo,&ang);';
	return code;
};

Blockly.Arduino.chassis_rightwards = function() {//b2
	Blockly.Arduino.setups_['chassis_rightwards'] = 'chassis_servo.attach(CHASSIS_SERVO);\n  chassis_servo.write(lamp_initPos);';

	Blockly.Arduino.definitions_['chassis_leftwards'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo chassis_servo;\n\n' + '\n' +
		'double ang ;' + 'bool moveFlag;';
	var code = 'chassisMoveR(chassis_servo,&ang);';
	return code;
};
//开灯 关灯 530
Blockly.Arduino.turnonlight = function() {//b3
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['turnonlight'] = 'lampLED.begin();\n  ' + 'lampLED.show();\n\n';

	Blockly.Arduino.definitions_['turnonlight'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel lampLED;\n\n';
	var code = 'turnonlight();\n';
	return code;
};
Blockly.Arduino.turnofflight = function() {//b3
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['turnofflight'] = 'lampLED.begin();\n  ' + 'lampLED.show();\n\n';

	Blockly.Arduino.definitions_['turnofflight'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel lampLED;\n\n';
	var code = 'turnofflight();\n';
	return code;
};








Blockly.Arduino.forwards = function() {//b1
	Blockly.Arduino.setups_['leftwards'] = 'lamp_servo.attach(LAMP_SERVO);\n  lamp_servo.write(lamp_initPos);' + 'lampPos = lamp_initPos;\n' + '  moveFlag = true; \n ';

	Blockly.Arduino.definitions_['leftwards'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo lamp_servo;\n\n' + '\n' +
		'double lampPos ;' + 'double ang ;' + 'bool moveFlag;';
	var code = 'lampMoveF(lamp_servo,&ang);';
	return code;
};

Blockly.Arduino.go_reverse = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'goReverse();\n';
	return code;
};

Blockly.Arduino.left_goahead = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelForward();\n';
	return code;
};

Blockly.Arduino.left_goahead_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	var speed = this.getFieldValue('left_goahead_speed');

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelForward_SpeedControl(' + speed + ');\n';
	return code;
};

Blockly.Arduino.left_back = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelBackward();\n';
	return code;
};

Blockly.Arduino.left_back_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	var speed = this.getFieldValue('left_back_speed');

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelBackward_SpeedControl(' + speed + ');\n';
	return code;
};

Blockly.Arduino.right_goahead = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelForward();\n';
	return code;
};

Blockly.Arduino.right_goahead_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	var speed = this.getFieldValue('right_goahead_speed');

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelForward_SpeedControl(' + speed + ');\n';
	return code;
};

Blockly.Arduino.right_back = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelBackward();\n';
	return code;
};

Blockly.Arduino.right_back_speed = function() {
	// TODO: Assemble JavaScript into code variable.
	var speed = this.getFieldValue('right_back_speed');

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelBackward_SpeedControl(' + speed + ');\n';
	return code;
};

Blockly.Arduino.right_Stop = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelStop();\n';
	return code;
};

Blockly.Arduino.left_Stop = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelStop();\n';
	return code;
};

Blockly.Arduino.left_CW = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelClockwise();\n';
	return code;
};

Blockly.Arduino.left_ACW = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'LeftWheelCounterClockwise();\n';
	return code;
};

Blockly.Arduino.right_CW = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelClockwise();\n';
	return code;
};

Blockly.Arduino.right_ACW = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'RightWheelCounterClockwise();\n';
	return code;
};

Blockly.Arduino.steeringRight = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['steer'] = 'steering_servo1.attach(STEERING_SERVO1);\n  steering_servo2.attach(STEERING_SERVO2);\n  steering_servo1.write(initPos);\n  steering_servo2.write(initPos);\n  ' +
		'steering_pos = initPos;\n';

	Blockly.Arduino.definitions_['steeringTurn_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    steering_servo1;\nServo    steering_servo2;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   steering_pos;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ServoSteeringRight(steering_servo1, steering_servo2, &steering_pos);\n';
	return code;
};

Blockly.Arduino.steeringLeft = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['steer'] = 'steering_servo1.attach(STEERING_SERVO1);\n  steering_servo2.attach(STEERING_SERVO2);\n  steering_servo1.write(initPos);\n  steering_servo2.write(initPos);\n  ' +
		'steering_pos = initPos;\n';

	Blockly.Arduino.definitions_['steeringTurn_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    steering_servo1;\nServo    steering_servo2;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   steering_pos;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ServoSteeringLeft(steering_servo1, steering_servo2, &steering_pos);\n';
	return code;
};

Blockly.Arduino.steeringCenter = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['steer'] = 'steering_servo1.attach(STEERING_SERVO1);\n  steering_servo2.attach(STEERING_SERVO2);\n  steering_servo1.write(initPos);\n  steering_servo2.write(initPos);\n  ' +
		'steering_pos = initPos;\n';

	Blockly.Arduino.definitions_['steeringTurn_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    steering_servo1;\nServo    steering_servo2;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   steering_pos;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ServoSteeringCenter(steering_servo1, steering_servo2, &steering_pos);\n';
	return code;
};

Blockly.Arduino.go_brake = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'goBrake();\n';
	return code;
};

Blockly.Arduino.stop = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n  ';
	//Blockly.Arduino.definitions_['movement_header'] = 'int PS2_Button_Read[6];';
	var code = 'goBrake();\n';
	return code;
};

Blockly.Arduino.pan_clockwise = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	Blockly.Arduino.setups_['pantilt'] = 'myservo_pan.attach(PAN_SERVO);\n  myservo_tilt.attach(TILT_SERVO);\n  myservo_pan.write(initPos);\n  myservo_tilt.write(initPos);\n  ' +
		'pan_pos = initPos;\n  tilt_pos = initPos;\n';

	Blockly.Arduino.definitions_['pantilt_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    myservo_pan;\nServo    myservo_tilt;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   pan_pos;\n' +
		'double   tilt_pos;\n\n';

	var code = 'PanMoveClockwise(myservo_pan, &pan_pos);\n';
	return code;
};

Blockly.Arduino.pan_counterclockwise = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	Blockly.Arduino.setups_['pantilt'] = 'myservo_pan.attach(PAN_SERVO);\n  myservo_tilt.attach(TILT_SERVO);\n  myservo_pan.write(initPos);\n  myservo_tilt.write(initPos);\n  ' +
		'pan_pos = initPos;\n  tilt_pos = initPos;\n';

	Blockly.Arduino.definitions_['pantilt_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    myservo_pan;\nServo    myservo_tilt;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   pan_pos;\n' +
		'double   tilt_pos;\n\n';

	var code = 'PanMoveCounterclockwise(myservo_pan, &pan_pos);\n';
	return code;
};

Blockly.Arduino.tilt_up = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	Blockly.Arduino.setups_['pantilt'] = 'myservo_pan.attach(PAN_SERVO);\n  myservo_tilt.attach(TILT_SERVO);\n  myservo_pan.write(initPos);\n  myservo_tilt.write(initPos);\n  ' +
		'pan_pos = initPos;\n  tilt_pos = initPos;\n';

	Blockly.Arduino.definitions_['pantilt_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    myservo_pan;\nServo    myservo_tilt;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   pan_pos;\n' +
		'double   tilt_pos;\n\n';

	var code = 'TiltMoveUp(myservo_tilt, &tilt_pos);\n';
	return code;
};

Blockly.Arduino.tilt_down = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	Blockly.Arduino.setups_['pantilt'] = 'myservo_pan.attach(PAN_SERVO);\n  myservo_tilt.attach(TILT_SERVO);\n  myservo_pan.write(initPos);\n  myservo_tilt.write(initPos);\n  ' +
		'pan_pos = initPos;\n  tilt_pos = initPos;\n';

	Blockly.Arduino.definitions_['pantilt_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    myservo_pan;\nServo    myservo_tilt;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   pan_pos;\n' +
		'double   tilt_pos;\n\n';

	var code = 'TiltMoveDown(myservo_tilt, &tilt_pos);\n';
	return code;
};

Blockly.Arduino.cam_init = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	Blockly.Arduino.setups_['pantilt'] = 'myservo_pan.attach(PAN_SERVO);\n  myservo_tilt.attach(TILT_SERVO);\n  myservo_pan.write(initPos);\n  myservo_tilt.write(initPos);\n  ' +
		'pan_pos = initPos;\n  tilt_pos = initPos;\n';

	Blockly.Arduino.definitions_['pantilt_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    myservo_pan;\nServo    myservo_tilt;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   pan_pos;\n' +
		'double   tilt_pos;\n\n';

	var code = 'myservo_pan.write(initPos);\nmyservo_tilt.write(initPos);\n pan_pos = initPos;\ntilt_pos = initPos;\n';
	return code;
};

Blockly.Arduino.greenLED = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';

	Blockly.Arduino.definitions_['SingleRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';

	var code = 'onGreenLED();\n';
	return code;
};

Blockly.Arduino.redLED = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';

	Blockly.Arduino.definitions_['SingleRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	var code = 'onRedLED();\n';
	return code;
};

Blockly.Arduino.blueLED = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';

	Blockly.Arduino.definitions_['SingleRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	return code;
};

Blockly.Arduino.yellowLED = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';

	Blockly.Arduino.definitions_['SingleRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	return code;
};

Blockly.Arduino.offLED = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';

	
	var code = 'offLED();\n';
	
};

Blockly.Arduino.optional_LED = function () {
	Blockly.Arduino.setups_['yellowLED'] = 'singleLED.begin();\n  '+ 'pinMode(ZW_B1,OUTPUT);\n'+'  pinMode(ZW_B2,OUTPUT);\n'+'  pinMode(ZW_B3,OUTPUT);\n'+ '  pinMode(ZW_B4,OUTPUT);\n' + '  singleLED.show();\n\n';
	Blockly.Arduino.setups_['SingleRGBLED'] = 'singleLED.begin();\n  ' + 'singleLED.show();\n\n';
	Blockly.Arduino.definitions_['SingleRGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	var pin = this.getFieldValue("lampPin");
	var state = this.getFieldValue("state");
	var code = 'optional_LED('+pin+','+state+');\n';
	return code;
};

Blockly.Arduino.leftturn_light_flash = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['leftturn_light'] = 'pinMode(LED_left,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'leftLightFlash();\n';
	return code;
};

Blockly.Arduino.leftturn_light_on = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['leftturn_light'] = 'pinMode(LED_left,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'leftLightOn();\n';
	return code;
};

Blockly.Arduino.leftturn_light_off = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['leftturn_light'] = 'pinMode(LED_left,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'leftLightOff();\n';
	return code;
};

Blockly.Arduino.rightturn_light_flash = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['rightturn_light'] = 'pinMode(LED_right,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'rightLightFlash();\n';
	return code;
};

Blockly.Arduino.rightturn_light_on = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['rightturn_light'] = 'pinMode(LED_right,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'rightLightOn();\n';
	return code;
};

Blockly.Arduino.rightturn_light_off = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['rightturn_light'] = 'pinMode(LED_right,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'rightLightOff();\n';
	return code;
};

Blockly.Arduino.rear_light = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['rear_light'] = 'pinMode(LED_left,OUTPUT);\n  pinMode(LED_right,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'rearLightOn();\n';
	return code;
};

Blockly.Arduino.rear_light_off = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['rear_light'] = 'pinMode(LED_left,OUTPUT);\n  pinMode(LED_right,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'rearLightOff();\n';
	return code;
};
Blockly.Arduino.movement_img_dropdown = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';

	var dropdown_movement = this.getFieldValue('Movement');
	var code;

	if(dropdown_movement == '../../media/ZeroWorkshop/ZW_leftturn.png') {
		code = 'goLeftTurn();\n';
	} else if(dropdown_movement == '../../media/ZeroWorkshop/ZW_rightturn.png') {
		code = 'goRightTurn();\n';
	} else if(dropdown_movement == '../../media/ZeroWorkshop/ZW_forward.png') {
		code = 'goForward();\n';
	} else if(dropdown_movement == '../../media/ZeroWorkshop/ZW_reverse.png') {
		code = 'goReverse();\n';
	} else if(dropdown_movement == '../../media/ZeroWorkshop/ZW_brake.png') {
		code = 'goBrake();\n';
	}
	return code;
};

Blockly.Arduino.play_note = function() {
	// TODO: Assemble JavaScript into code variable.
	//Blockly.Arduino.setups_['music'] = 'pinMode(BuzzerPin,OUTPUT);\n';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';

	var dropdown_notename = this.getFieldValue('varNote');
	var dropdown_rythem = this.getFieldValue('rythem');
	var dropdown_length = this.getFieldValue('meters_length');

	var code = 'playNote(' + dropdown_notename + ',' + dropdown_rythem + ',' + dropdown_length + ');\n';

	return code;
};

Blockly.Arduino.play_song = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var dropdown_songName = this.getFieldValue('songName');

	var code = 'playSong(' + dropdown_songName + ');\n';
	return code;
};

Blockly.Arduino.control_if_gamepad = function() {

	//Blockly.Arduino.definitions_['RF_controller'] = '#include    <PS2X_lib.h>\nPS2X        ps2x;';
	//Blockly.Arduino.setups_['RF_controller'] = 'ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);\n';

	//Blockly.Arduino.definitions_['RF_controller'] = 'byte     RF_buffer[6];';
	Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['RF_controller'] = 'Serial.begin(115200);\n';

	var option_name = new Array("../../media/ZeroWorkshop/ps2_Lup.png",
		"../../media/ZeroWorkshop/ps2_Lleft.png",
		"../../media/ZeroWorkshop/ps2_Ldown.png",
		"../../media/ZeroWorkshop/ps2_Lright.png",
		"../../media/ZeroWorkshop/ps2_Rtriangle.png",
		"../../media/ZeroWorkshop/ps2_Rsquare.png",
		"../../media/ZeroWorkshop/ps2_Rcross.png",
		"../../media/ZeroWorkshop/ps2_Rcircle.png");

	// If/elseif/else condition.
	var n = 0;
	//var argument = Blockly.Arduino.valueToCode(this, 'IF' + n,
	//    Blockly.Arduino.ORDER_NONE) || 'false';

	var argument_pad = this.getFieldValue('Movement_' + n);
	var button_;

	for(var i = 0; i < option_name.length; i++) {
		if(argument_pad == option_name[i]) {
			switch(i) {
				case 0:
					button_ = 'ButtonUp';
					break;
				case 1:
					button_ = 'ButtonLeft';
					break;
				case 2:
					button_ = 'ButtonDown';
					break;
				case 3:
					button_ = 'ButtonRight';
					break;
				case 4:
					button_ = 'ButtonTriangle';
					break;
				case 5:
					button_ = 'ButtonSquare';
					break;
				case 6:
					button_ = 'ButtonCross';
					break;
				case 7:
					button_ = 'ButtonCircle';
					break;
				default:
					break;
			}
		}

	}

	//var code =  'ps2x.read_gamepad(false, 0);\n';  //read controller and set large motor to spin at 'vibrate' speed

	var code = 'PS2_RF_ReadButton(PS2_Button_Read);\n';

	if(argument_pad = option_name)
		var branch = Blockly.Arduino.statementToCode(this, 'DO' + n);

	code += 'if (' + button_ + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {
		//argument = Blockly.Arduino.valueToCode(this, 'IF' + n,
		//  Blockly.Arduino.ORDER_NONE) || 'false';

		argument_pad = this.getFieldValue('Movement_' + n);

		for(var j = 0; j < option_name.length; j++) {
			if(argument_pad == option_name[j]) {
				switch(j) {
					case 0:
						button_ = 'ButtonUp';
						break;
					case 1:
						button_ = 'ButtonLeft';
						break;
					case 2:
						button_ = 'ButtonDown';
						break;
					case 3:
						button_ = 'ButtonRight';
						break;
					case 4:
						button_ = 'ButtonTriangle';
						break;
					case 5:
						button_ = 'ButtonSquare';
						break;
					case 6:
						button_ = 'ButtonCross';
						break;
					case 7:
						button_ = 'ButtonCircle';
						break;
					default:
						break;
				}
			}

		}
		branch = Blockly.Arduino.statementToCode(this, 'DO' + n);
		code += '\nelse if (' + button_ + ') {\n' + branch + '}';
	}
	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}
	code += '\n\ndelay(50); \n';

	return code;
};

Blockly.Arduino.control_IRsensor_if = function() {
	//
	var dropdown_IR = this.getFieldValue('IR_Input0');
	Blockly.Arduino.setups_[dropdown_IR] = 'pinMode(' + dropdown_IR + ',INPUT);';

	var n = 0;
	var argument = Blockly.Arduino.valueToCode(this, 'IF_IR' + n,
		Blockly.Arduino.ORDER_NONE) || 'false';
	var argument_IR = '!digitalRead(' + dropdown_IR + ')';
	var branch = Blockly.Arduino.statementToCode(this, 'DO_IR' + n);
	var code = 'if (' + argument_IR + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {
		var dropdown_IR_else = this.getFieldValue('IR_Input' + n);
		var argument_IR_else = '!digitalRead(' + dropdown_IR_else + ')';
		argument = Blockly.Arduino.valueToCode(this, 'IF_IR' + n,
			Blockly.Arduino.ORDER_NONE) || 'false';
		branch = Blockly.Arduino.statementToCode(this, 'DO_IR' + n);
		code += '\nelse if (' + argument_IR_else + ') {\n' + branch + '}';
	}
	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}

	return code + '\n';
};

Blockly.Arduino.control_IR_if = function() {
	//
	var dropdown_IR = this.getFieldValue('IR_Input0');
	Blockly.Arduino.setups_['IR'] = 'pinMode(' + dropdown_IR + ',INPUT);\n  ';

	var n = 0;
	var argument = Blockly.Arduino.valueToCode(this, 'IF_IR0',
		Blockly.Arduino.ORDER_NONE) || 'false';
	var argument_IR = '!digitalRead(' + dropdown_IR + ')';
	var branch = Blockly.Arduino.statementToCode(this, 'DO_IR0');
	var code = 'if (' + argument_IR + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {
		var dropdown_IR_else = this.getFieldValue('IR_Input' + n);
		Blockly.Arduino.setups_['IR'] += 'pinMode(' + dropdown_IR_else + ',INPUT);\n  ';
		var argument_IR_else = '!digitalRead(' + dropdown_IR_else + ')';
		argument = Blockly.Arduino.valueToCode(this, 'IF_IR' + n,
			Blockly.Arduino.ORDER_NONE) || 'false';
		branch = Blockly.Arduino.statementToCode(this, 'DO_IR' + n);
		code += '\nelse if (' + argument_IR_else + ') {\n' + branch + '}';
	}
	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}

	return code + '\n';
};

Blockly.Arduino.control_Button_if = function() {

	var dropdown_Button = this.getFieldValue('Button_Input0');
	Blockly.Arduino.setups_['Button'] = 'pinMode(' + dropdown_Button + ',INPUT);\n  ';

	var n = 0;
	var argument = Blockly.Arduino.valueToCode(this, 'IF_Button0',
		Blockly.Arduino.ORDER_NONE) || 'false';
	var argument_Button = 'INPUT_VALUE_' + dropdown_Button;
	var branch = Blockly.Arduino.statementToCode(this, 'DO_Button0');
	var code = 'if (' + argument_Button + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {
		var dropdown_Button_else = this.getFieldValue('Button_Input' + n);
		Blockly.Arduino.setups_['Button'] += 'pinMode(' + dropdown_Button_else + ',INPUT);\n  ';
		var argument_Button_else = 'INPUT_VALUE_' + dropdown_Button_else;
		argument = Blockly.Arduino.valueToCode(this, 'IF_Button' + n,
			Blockly.Arduino.ORDER_NONE) || 'false';
		branch = Blockly.Arduino.statementToCode(this, 'DO_Button' + n);
		code += '\nelse if (' + argument_Button_else + ') {\n' + branch + '}';
	}
	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}

	return code + '\n';
};

Blockly.Arduino.control_PS2_if = function() {

	Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['RF_controller'] = 'Serial.begin(115200);\n';

	var code = 'PS2_RF_ReadButton(PS2_Button_Read);\n';

	var branch = Blockly.Arduino.statementToCode(this, 'DO_PS2_' + 0);

	var n = 0;
	var button_ = '';

	var buttonUp = this.getFieldValue('UP0');
	var buttonRight = this.getFieldValue('RIGHT0');
	var buttonDown = this.getFieldValue('DOWN0');
	var buttonLeft = this.getFieldValue('LEFT0');
	var buttonTriangle = this.getFieldValue('TRIANGLE0');
	var buttonCircle = this.getFieldValue('CIRCLE0');
	var buttonCross = this.getFieldValue('CROSS0');
	var buttonSquare = this.getFieldValue('SQUARE0');
	var buttonSelect = this.getFieldValue('SELECT0');
	var buttonStart = this.getFieldValue('START0');
	var buttonL1 = this.getFieldValue('L10');
	var buttonR1 = this.getFieldValue('R10');
	var buttonL2 = this.getFieldValue('L20');
	var buttonR2 = this.getFieldValue('R20');

	var UP_pressed = 0;
	var RIGHT_pressed = 0;
	var DOWN_pressed = 0;
	var LEFT_pressed = 0;
	var TRIANGLE_pressed = 0;
	var CIRCLE_pressed = 0;
	var CROSS_pressed = 0;
	var SQUARE_pressed = 0;
	var SELECT_pressed = 0;
	var START_pressed = 0;
	var L1_pressed = 0;
	var R1_pressed = 0;
	var L2_pressed = 0;
	var R2_pressed = 0;

	if(buttonUp == 'TRUE') UP_pressed = 1;
	else UP_pressed = 0;
	if(buttonRight == 'TRUE') RIGHT_pressed = 1;
	else RIGHT_pressed = 0;
	if(buttonDown == 'TRUE') DOWN_pressed = 1;
	else DOWN_pressed = 0;
	if(buttonLeft == 'TRUE') LEFT_pressed = 1;
	else LEFT_pressed = 0;
	if(buttonTriangle == 'TRUE') TRIANGLE_pressed = 1;
	else TRIANGLE_pressed = 0;
	if(buttonCircle == 'TRUE') CIRCLE_pressed = 1;
	else CIRCLE_pressed = 0;
	if(buttonCross == 'TRUE') CROSS_pressed = 1;
	else CROSS_pressed = 0;
	if(buttonSquare == 'TRUE') SQUARE_pressed = 1;
	else SQUARE_pressed = 0;
	if(buttonSelect == 'TRUE') SELECT_pressed = 1;
	else SELECT_pressed = 0;
	if(buttonStart == 'TRUE') START_pressed = 1;
	else START_pressed = 0;
	if(buttonL1 == 'TRUE') L1_pressed = 1;
	else L1_pressed = 0;
	if(buttonR1 == 'TRUE') R1_pressed = 1;
	else R1_pressed = 0;
	if(buttonL2 == 'TRUE') L2_pressed = 1;
	else L2_pressed = 0;
	if(buttonR2 == 'TRUE') R2_pressed = 1;
	else R2_pressed = 0;

	var button_pressed_num = UP_pressed + RIGHT_pressed + DOWN_pressed + LEFT_pressed +
		TRIANGLE_pressed + CIRCLE_pressed + CROSS_pressed + SQUARE_pressed + SELECT_pressed + START_pressed +
		L1_pressed + R1_pressed + L2_pressed + R2_pressed;

	if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonL1 && ';
	else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonL1';

	if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonR1 && ';
	else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonR1';

	if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonL2 && ';
	else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonL2';

	if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonR2 && ';
	else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonR2';

	if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonSelect && ';
	else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonSelect';

	if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonStart && ';
	else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonStart';

	if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonUp && ';
	else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonUp';

	if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonRight && ';
	else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonRight';

	if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonDown && ';
	else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonDown';

	if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonLeft && ';
	else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonLeft';

	if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonTriangle && ';
	else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonTriangle';

	if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonCircle && ';
	else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonCircle';

	if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonCross && ';
	else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonCross';

	if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonSquare';
	else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonSquare';

	code += 'if (' + button_ + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {

		button_ = '';

		buttonUp = this.getFieldValue('UP' + n);
		buttonRight = this.getFieldValue('RIGHT' + n);
		buttonDown = this.getFieldValue('DOWN' + n);
		buttonLeft = this.getFieldValue('LEFT' + n);
		buttonTriangle = this.getFieldValue('TRIANGLE' + n);
		buttonCircle = this.getFieldValue('CIRCLE' + n);
		buttonCross = this.getFieldValue('CROSS' + n);
		buttonSquare = this.getFieldValue('SQUARE' + n);
		buttonSelect = this.getFieldValue('SELECT' + n);
		buttonStart = this.getFieldValue('START' + n);
		buttonL1 = this.getFieldValue('L1' + n);
		buttonR1 = this.getFieldValue('R1' + n);
		buttonL2 = this.getFieldValue('L2' + n);
		buttonR2 = this.getFieldValue('R2' + n);

		UP_pressed = 0;
		RIGHT_pressed = 0;
		DOWN_pressed = 0;
		LEFT_pressed = 0;
		TRIANGLE_pressed = 0;
		CIRCLE_pressed = 0;
		CROSS_pressed = 0;
		SQUARE_pressed = 0;
		SELECT_pressed = 0;
		START_pressed = 0;
		L1_pressed = 0;
		R1_pressed = 0;
		L2_pressed = 0;
		R2_pressed = 0;

		if(buttonUp == 'TRUE') UP_pressed = 1;
		else UP_pressed = 0;
		if(buttonRight == 'TRUE') RIGHT_pressed = 1;
		else RIGHT_pressed = 0;
		if(buttonDown == 'TRUE') DOWN_pressed = 1;
		else DOWN_pressed = 0;
		if(buttonLeft == 'TRUE') LEFT_pressed = 1;
		else LEFT_pressed = 0;
		if(buttonTriangle == 'TRUE') TRIANGLE_pressed = 1;
		else TRIANGLE_pressed = 0;
		if(buttonCircle == 'TRUE') CIRCLE_pressed = 1;
		else CIRCLE_pressed = 0;
		if(buttonCross == 'TRUE') CROSS_pressed = 1;
		else CROSS_pressed = 0;
		if(buttonSquare == 'TRUE') SQUARE_pressed = 1;
		else SQUARE_pressed = 0;
		if(buttonSelect == 'TRUE') SELECT_pressed = 1;
		else SELECT_pressed = 0;
		if(buttonStart == 'TRUE') START_pressed = 1;
		else START_pressed = 0;
		if(buttonL1 == 'TRUE') L1_pressed = 1;
		else L1_pressed = 0;
		if(buttonR1 == 'TRUE') R1_pressed = 1;
		else R1_pressed = 0;
		if(buttonL2 == 'TRUE') L2_pressed = 1;
		else L2_pressed = 0;
		if(buttonR2 == 'TRUE') R2_pressed = 1;
		else R2_pressed = 0;

		button_pressed_num = UP_pressed + RIGHT_pressed + DOWN_pressed + LEFT_pressed + TRIANGLE_pressed +
			CIRCLE_pressed + CROSS_pressed + SQUARE_pressed + SELECT_pressed + START_pressed +
			L1_pressed + R1_pressed + L2_pressed + R2_pressed;

		if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonL1 && ';
		else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonL1';

		if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonR1 && ';
		else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonR1';

		if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonL2 && ';
		else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonL2';

		if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonR2 && ';
		else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonR2';

		if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonSelect && ';
		else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonSelect';

		if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonStart && ';
		else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonStart';

		if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonUp && ';
		else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonUp';

		if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonRight && ';
		else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonRight';

		if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonDown && ';
		else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonDown';

		if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonLeft && ';
		else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonLeft';

		if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonTriangle && ';
		else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonTriangle';

		if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonCircle && ';
		else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonCircle';

		if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonCross && ';
		else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonCross';

		if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += 'ButtonSquare';
		else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += 'ButtonSquare';

		branch = Blockly.Arduino.statementToCode(this, 'DO_PS2_' + n);
		code += '\nelse if (' + button_ + ') {\n' + branch + '\n}';

	}

	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}
	code += '\n\ndelay(10); \n';

	return code;

};
Blockly.Arduino.spin_start = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code0 = 'fanRunningStatus = true;\n';
	var code1 = 'FanRunning(fanSpeed, fanRunningStatus);\n';
	sessionStorage.setItem('spin_start_code1', 'FanRunning(fanSpeed, fanRunningStatus);\n')

	if(isNeedStrengthen('controls_if_new', 'spin_start')) {
		var code = code0;
		sessionStorage.setItem('god', 'FanRunning(fanSpeed, fanRunningStatus);\n')

	} else {
		var code = code0 + code1;

	}

	return code;
};

function isNeedStrengthen(a, b) {
	var xml = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
	//var blocks = workspace.getTopBlocks(true);

	//var xml = Blockly.Xml.blockToDom("controls_if_new"));
	var x = xml.getElementsByTagName("block");

	var flag = false;

	for(var i = 0; i < x.length; i++) {
		if(x[i].getAttribute('type') == a) {
			var ifBlockEle = x[i].getElementsByTagName("block");

			for(var j = 0; j < ifBlockEle.length; j++) {
				//console.log(ifBlockEle[j])
				if(ifBlockEle[j].getAttribute('type') == b) {
					flag = true;
				}
			}
			ifBlockEle = null;
		}
	}
	//console.log(flag)
	return flag;
}
Blockly.Arduino.spin_stop = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code0 = 'fanRunningStatus = false;\n';
	var code1 = 'FanRunning(fanSpeed, fanRunningStatus);\n';
	sessionStorage.setItem('spin_stop_code1', 'FanRunning(fanSpeed, fanRunningStatus);\n')

	if(isNeedStrengthen('controls_if_new', 'spin_stop')) {
		var code = code0;
		sessionStorage.setItem('god', 'FanRunning(fanSpeed, fanRunningStatus);\n')
	} else {
		var code = code0 + code1;

	}

	return code;
};

Blockly.Arduino.LRspin_start = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code0 = 'fanHeadMovingStatus = true;\n';
	var code1 = 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n';

	sessionStorage.setItem('LRspin_start_code1', 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n')

	if(isNeedStrengthen('controls_if_new', 'LRspin_start')) {
		var code = code0;
		sessionStorage.setItem('god', 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n')
	} else {
		var code = code0 + code1;

	}
	return code;
};

Blockly.Arduino.LRspin_stop = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code0 = 'fanHeadMovingStatus = false;\n';
	var code1 = 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n';

	sessionStorage.setItem('LRspin_stop_code1', 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n')

	if(isNeedStrengthen('controls_if_new', 'LRspin_stop')) {
		var code = code0;
		sessionStorage.setItem('god', 'FanHeadMove(fanHeadHorizontal_servo, fanHeadMovingStatus, &fanHeadHorizontalPosition);\n')

	} else {
		var code = code0 + code1;

	}
	return code;
};



Blockly.Arduino.controls_if_new = function() {

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['RF_controller'] = 'Serial.begin(115200);\n';

	//var code = 'PS2_RF_ReadButton(PS2_Button_Read);\n';
	
	var code = '';

	var branch = Blockly.Arduino.statementToCode(this, 'DO' + 0);

	var n = 0;
	var button_ = '';
	var buttonLogic = '';

	var buttonUp = this.getFieldValue('UP0');
	var buttonRight = this.getFieldValue('RIGHT0');
	var buttonDown = this.getFieldValue('DOWN0');
	var buttonLeft = this.getFieldValue('LEFT0');
	var buttonTriangle = this.getFieldValue('TRIANGLE0');
	var buttonCircle = this.getFieldValue('CIRCLE0');
	var buttonCross = this.getFieldValue('CROSS0');
	var buttonSquare = this.getFieldValue('SQUARE0');
	var buttonSelect = this.getFieldValue('SELECT0');
	var buttonStart = this.getFieldValue('START0');
	var buttonL1 = this.getFieldValue('L10');
	var buttonR1 = this.getFieldValue('R10');
	var buttonL2 = this.getFieldValue('L20');
	var buttonR2 = this.getFieldValue('R20');

	var UP_pressed = 0;
	var RIGHT_pressed = 0;
	var DOWN_pressed = 0;
	var LEFT_pressed = 0;
	var TRIANGLE_pressed = 0;
	var CIRCLE_pressed = 0;
	var CROSS_pressed = 0;
	var SQUARE_pressed = 0;
	var SELECT_pressed = 0;
	var START_pressed = 0;
	var L1_pressed = 0;
	var R1_pressed = 0;
	var L2_pressed = 0;
	var R2_pressed = 0;

	if(buttonUp == 'TRUE') UP_pressed = 1;
	else UP_pressed = 0;
	if(buttonRight == 'TRUE') RIGHT_pressed = 1;
	else RIGHT_pressed = 0;
	if(buttonDown == 'TRUE') DOWN_pressed = 1;
	else DOWN_pressed = 0;
	if(buttonLeft == 'TRUE') LEFT_pressed = 1;
	else LEFT_pressed = 0;
	if(buttonTriangle == 'TRUE') TRIANGLE_pressed = 1;
	else TRIANGLE_pressed = 0;
	if(buttonCircle == 'TRUE') CIRCLE_pressed = 1;
	else CIRCLE_pressed = 0;
	if(buttonCross == 'TRUE') CROSS_pressed = 1;
	else CROSS_pressed = 0;
	if(buttonSquare == 'TRUE') SQUARE_pressed = 1;
	else SQUARE_pressed = 0;
	if(buttonSelect == 'TRUE') SELECT_pressed = 1;
	else SELECT_pressed = 0;
	if(buttonStart == 'TRUE') START_pressed = 1;
	else START_pressed = 0;
	if(buttonL1 == 'TRUE') L1_pressed = 1;
	else L1_pressed = 0;
	if(buttonR1 == 'TRUE') R1_pressed = 1;
	else R1_pressed = 0;
	if(buttonL2 == 'TRUE') L2_pressed = 1;
	else L2_pressed = 0;
	if(buttonR2 == 'TRUE') R2_pressed = 1;
	else R2_pressed = 0;

	var button_pressed_num = UP_pressed + RIGHT_pressed + DOWN_pressed + LEFT_pressed +
		TRIANGLE_pressed + CIRCLE_pressed + CROSS_pressed + SQUARE_pressed + SELECT_pressed + START_pressed +
		L1_pressed + R1_pressed + L2_pressed + R2_pressed;
	
	var buttonSelectedNum = button_pressed_num;	
		var isAnd = this.getFieldValue('andOr');
	if(isAnd == '&&'){
	
	if (button_pressed_num > 0) button_ = 'Rx_Buffer[5] == ';
	
	if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_L1 + ';
	else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_L1';

	if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_R1 + ';
	else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_R1';

	if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_L2 + ';
	else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_L2';

	if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_R2 + ';
	else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_R2';

	if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_SELECT + ';
	else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_SELECT';

	if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_START + ';
	else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_START';

	if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_UP + ';
	else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_UP';

	if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_RIGHT + ';
	else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_RIGHT';

	if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_DOWN + ';
	else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_DOWN';

	if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_LEFT + ';
	else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_LEFT';

	if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_TRIANGLE + ';
	else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_TRIANGLE';

	if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_CIRCLE + ';
	else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_CIRCLE';

	if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_CROSS + ';
	else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_CROSS';

	if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_SQUARE';
	else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_SQUARE';
	
	if(buttonL1 == 'TRUE') buttonLogic += ' && _ButtonL1';
	

	if(buttonR1 == 'TRUE') buttonLogic += ' && _ButtonR1';
	

	if(buttonL2 == 'TRUE') buttonLogic += ' && _ButtonL2';
	

	if(buttonR2 == 'TRUE') buttonLogic += ' && _ButtonR2';
	

	if(buttonSelect == 'TRUE') buttonLogic += ' && _ButtonSelect';
	

	if(buttonStart == 'TRUE' ) buttonLogic += ' && _ButtonStart';
	

	if(buttonUp == 'TRUE') buttonLogic += ' && _ButtonUp';
	

	if(buttonRight == 'TRUE') buttonLogic += ' && _ButtonRight';
	

	if(buttonDown == 'TRUE') buttonLogic += ' && _ButtonDown';
	

	if(buttonLeft == 'TRUE') buttonLogic += ' && _ButtonLeft';
	

	if(buttonTriangle == 'TRUE') buttonLogic += ' && _ButtonTriangle';
	

	if(buttonCircle == 'TRUE') buttonLogic += ' && _ButtonCircle';
	

	if(buttonCross == 'TRUE') buttonLogic += ' && _ButtonCross';
	

	if(buttonSquare == 'TRUE') buttonLogic += ' && _ButtonSquare';
	
	
	}else{
		
	

	if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonL1 || ';
	else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonL1';

	if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonR1 || ';
	else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonR1';

	if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonL2 || ';
	else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonL2';

	if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonR2 || ';
	else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonR2';

	if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonSelect || ';
	else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonSelect';

	if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonStart || ';
	else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonStart';

	if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonUp || ';
	else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonUp';

	if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonRight || ';
	else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonRight';

	if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonDown || ';
	else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonDown';

	if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonLeft || ';
	else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonLeft';

	if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonTriangle || ';
	else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonTriangle';

	if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonCircle || ';
	else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonCircle';

	if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonCross || ';
	else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonCross';

	if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonSquare';
	else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonSquare';
	
	
		
	}
  
  if (buttonSelectedNum == 0) code += 'if (false) {\n//CAUTION: NO BUTTON is selected on the game pad for the \'if\' branch!\n//Nothing will run here!\n}';
	else code += 'if ((' + button_ + ')' + buttonLogic + ') {\n' + branch + '\n}';

	for(n = 1; n <= this.elseifCount_; n++) {

		button_ = '';
		buttonLogic = '';

		buttonUp = this.getFieldValue('UP' + n);
		buttonRight = this.getFieldValue('RIGHT' + n);
		buttonDown = this.getFieldValue('DOWN' + n);
		buttonLeft = this.getFieldValue('LEFT' + n);
		buttonTriangle = this.getFieldValue('TRIANGLE' + n);
		buttonCircle = this.getFieldValue('CIRCLE' + n);
		buttonCross = this.getFieldValue('CROSS' + n);
		buttonSquare = this.getFieldValue('SQUARE' + n);
		buttonSelect = this.getFieldValue('SELECT' + n);
		buttonStart = this.getFieldValue('START' + n);
		buttonL1 = this.getFieldValue('L1' + n);
		buttonR1 = this.getFieldValue('R1' + n);
		buttonL2 = this.getFieldValue('L2' + n);
		buttonR2 = this.getFieldValue('R2' + n);

		UP_pressed = 0;
		RIGHT_pressed = 0;
		DOWN_pressed = 0;
		LEFT_pressed = 0;
		TRIANGLE_pressed = 0;
		CIRCLE_pressed = 0;
		CROSS_pressed = 0;
		SQUARE_pressed = 0;
		SELECT_pressed = 0;
		START_pressed = 0;
		L1_pressed = 0;
		R1_pressed = 0;
		L2_pressed = 0;
		R2_pressed = 0;

		if(buttonUp == 'TRUE') UP_pressed = 1;
		else UP_pressed = 0;
		if(buttonRight == 'TRUE') RIGHT_pressed = 1;
		else RIGHT_pressed = 0;
		if(buttonDown == 'TRUE') DOWN_pressed = 1;
		else DOWN_pressed = 0;
		if(buttonLeft == 'TRUE') LEFT_pressed = 1;
		else LEFT_pressed = 0;
		if(buttonTriangle == 'TRUE') TRIANGLE_pressed = 1;
		else TRIANGLE_pressed = 0;
		if(buttonCircle == 'TRUE') CIRCLE_pressed = 1;
		else CIRCLE_pressed = 0;
		if(buttonCross == 'TRUE') CROSS_pressed = 1;
		else CROSS_pressed = 0;
		if(buttonSquare == 'TRUE') SQUARE_pressed = 1;
		else SQUARE_pressed = 0;
		if(buttonSelect == 'TRUE') SELECT_pressed = 1;
		else SELECT_pressed = 0;
		if(buttonStart == 'TRUE') START_pressed = 1;
		else START_pressed = 0;
		if(buttonL1 == 'TRUE') L1_pressed = 1;
		else L1_pressed = 0;
		if(buttonR1 == 'TRUE') R1_pressed = 1;
		else R1_pressed = 0;
		if(buttonL2 == 'TRUE') L2_pressed = 1;
		else L2_pressed = 0;
		if(buttonR2 == 'TRUE') R2_pressed = 1;
		else R2_pressed = 0;

		button_pressed_num = UP_pressed + RIGHT_pressed + DOWN_pressed + LEFT_pressed + TRIANGLE_pressed +
			CIRCLE_pressed + CROSS_pressed + SQUARE_pressed + SELECT_pressed + START_pressed +
			L1_pressed + R1_pressed + L2_pressed + R2_pressed;
	  buttonSelectedNum = button_pressed_num;	
			var isAndx = this.getFieldValue('andOr'+n);
			
			if(isAndx == '&&'){
				
			if (button_pressed_num > 0) button_ = 'Rx_Buffer[5] == ';

		if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_L1 + ';
		else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_L1';

		if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_R1 + ';
		else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_R1';

		if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_L2 + ';
		else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_L2';

		if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_R2 + ';
		else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_R2';

		if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_SELECT + ';
		else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_SELECT';

		if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_START + ';
		else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_START';

		if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_UP + ';
		else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_UP';

		if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_RIGHT + ';
		else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_RIGHT';

		if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_DOWN + ';
		else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_DOWN';

		if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_LEFT + ';
		else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_LEFT';

		if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_TRIANGLE + ';
		else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_TRIANGLE';

		if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_CIRCLE + ';
		else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_CIRCLE';

		if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_CROSS + ';
		else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_CROSS';

		if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += 'PS2_SQUARE';
		else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += 'PS2_SQUARE';
		
		if(buttonL1 == 'TRUE') buttonLogic += ' && _ButtonL1';
	

	if(buttonR1 == 'TRUE') buttonLogic += ' && _ButtonR1';
	

	if(buttonL2 == 'TRUE') buttonLogic += ' && _ButtonL2';
	

	if(buttonR2 == 'TRUE') buttonLogic += ' && _ButtonR2';
	

	if(buttonSelect == 'TRUE') buttonLogic += ' && _ButtonSelect';
	

	if(buttonStart == 'TRUE' ) buttonLogic += ' && _ButtonStart';
	

	if(buttonUp == 'TRUE') buttonLogic += ' && _ButtonUp';
	

	if(buttonRight == 'TRUE') buttonLogic += ' && _ButtonRight';
	

	if(buttonDown == 'TRUE') buttonLogic += ' && _ButtonDown';
	

	if(buttonLeft == 'TRUE') buttonLogic += ' && _ButtonLeft';
	

	if(buttonTriangle == 'TRUE') buttonLogic += ' && _ButtonTriangle';
	

	if(buttonCircle == 'TRUE') buttonLogic += ' && _ButtonCircle';
	

	if(buttonCross == 'TRUE') buttonLogic += ' && _ButtonCross';
	

	if(buttonSquare == 'TRUE') buttonLogic += ' && _ButtonSquare';
		}else{
				
			

		if(buttonL1 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonL1 || ';
		else if(buttonL1 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonL1';

		if(buttonR1 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonR1 || ';
		else if(buttonR1 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonR1';

		if(buttonL2 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonL2 || ';
		else if(buttonL2 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonL2';

		if(buttonR2 == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonR2 || ';
		else if(buttonR2 == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonR2';

		if(buttonSelect == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonSelect || ';
		else if(buttonSelect == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonSelect';

		if(buttonStart == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonStart || ';
		else if(buttonStart == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonStart';

		if(buttonUp == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonUp || ';
		else if(buttonUp == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonUp';

		if(buttonRight == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonRight || ';
		else if(buttonRight == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonRight';

		if(buttonDown == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonDown || ';
		else if(buttonDown == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonDown';

		if(buttonLeft == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonLeft || ';
		else if(buttonLeft == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonLeft';

		if(buttonTriangle == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonTriangle || ';
		else if(buttonTriangle == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonTriangle';

		if(buttonCircle == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonCircle || ';
		else if(buttonCircle == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonCircle';

		if(buttonCross == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonCross || ';
		else if(buttonCross == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonCross';

		if(buttonSquare == 'TRUE' && --button_pressed_num > 0) button_ += '_ButtonSquare';
		else if(buttonSquare == 'TRUE' && button_pressed_num == 0) button_ += '_ButtonSquare';
		
			
		}

		branch = Blockly.Arduino.statementToCode(this, 'DO' + n);
		
    if (buttonSelectedNum == 0) code += '\n//CAUTION: NO BUTTON is selected on the game pad for the ' + n + ' \'else if\' branch!\n';
		else code += '\nelse if ((' + button_ + ')' + buttonLogic + ') {\n' + branch + '\n}';

	}

	if(this.elseCount_) {
		branch = Blockly.Arduino.statementToCode(this, 'ELSE');
		code += '\nelse {\n' + branch + '\n}';
	}
	//code += '\n\ndelay(10); \n';

	var spin_flag = false;
	var headmove_flag = false;

	//var block_ID = Block.id;
	function isNeed(a) {
		var xml = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
		//var blocks = workspace.getTopBlocks(true);

		//var xml = Blockly.Xml.blockToDom("controls_if_new"));
		var x = xml.getElementsByTagName("block");

		var flag = false;

		for(var i = 0; i < x.length; i++) {
			if(x[i].getAttribute('type') == a) {
				flag = true;
			}
		}
		return flag;
	}

//	var fanrunning_code;
//	var fanheadmoving_code;
//	var radarMove_code;
//	var radarLight_code;
//	var forkliftLamp_code;
//	var forkliftTopLamp_code;
	
	var dance_flag = isNeed('dance') || isNeed('danceStop');
 	var isVolume_flag = isNeed('volume');
	var fanspin_status_flag = isNeed('spin_start') || isNeed('spin_stop');
	var fanheadmove_status_flag = isNeed('LRspin_start') || isNeed('LRspin_stop');
	var radar_flag = isNeed('radarMove') || isNeed('radarStop');
	var radarLight_flag = isNeed('indicatorLight') || isNeed('indicatorLightOff');
	var forkliftLamp_flag = isNeed('forkliftLampOn') || isNeed('forkliftLampOff');
	var forkliftTopLamp_flag = isNeed('forkliftTopLampOn') || isNeed('forkliftTopLampOff');
	
	
	if(dance_flag) {
		code += sessionStorage.getItem('dance_code1');
		sessionStorage.setItem('dance_code1', '');
	}
	if(isVolume_flag) {
		code += sessionStorage.getItem('volume_code1');
		sessionStorage.setItem('volume_code1', '');
	}
	if(radarLight_flag) {
		code += sessionStorage.getItem('radarLight_code1');
		sessionStorage.setItem('radarLight_code1', '');
	}
	
	if(radar_flag) {
		code += sessionStorage.getItem('radarMove_code1');
		sessionStorage.setItem('radarMove_code1', '');
	}

	if(fanspin_status_flag) {
		code += sessionStorage.getItem('god');
		sessionStorage.setItem('god', '')
	}
	if(fanheadmove_status_flag) {
		code += sessionStorage.getItem('god');
		sessionStorage.setItem('god', '')
	}
	if(forkliftLamp_flag) {
		code += sessionStorage.getItem('forkliftLamp');
		sessionStorage.setItem('forkliftLamp', '')
	}
	if(forkliftTopLamp_flag) {
		code += sessionStorage.getItem('forkliftTopLamp');
		sessionStorage.setItem('forkliftTopLamp', '')
	}
	/*
	if(isNeed('spin_start') || isNeed('spin_stop')) {
		if (spin_flag)
		 code +=sessionStorage.getItem('spin_start_code1');
		
		
	}else{
		
	}

  if(isNeed('spin_stop')) {
		code +=sessionStorage.getItem('spin_stop_code1');
		
	}else{
		
		
	}
  
  
  
  if(isNeed('LRspin_start') || isNeed('LRspin_stop')) {
		code +=sessionStorage.getItem('LRspin_start_code1');
		
	}else{
		
		
	}
	
  if(isNeed('LRspin_stop')) {
		code +=sessionStorage.getItem('LRspin_stop_code1');
		
	}else{
		
		
	}
	*/
	//code += fanrunning_code;
	//code += fanheadmoving_code;
	//code = Blockly.mainWorkspace.getBlockById("controls_if_new");
	return code;

	//return this.getNextBlock();

};


Blockly.Arduino.upwards = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticTail'] = 'tail_servo.attach(FTAIL_SERVO);\n  tail_servo.write(tail_initPos);\n  ' + 'tail_position = tail_initPos;\n  ';

	Blockly.Arduino.definitions_['roboticTail_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    tail_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   tail_position;\n';

	//	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'TailControlUp(tail_servo, &tail_position);\n';
	return code;
};

//void TailControlUp(Servo tail_servo, double *tail_position) {//0
//
//Serial.print("up init = ");
//Serial.println(*tail_position);
//
//if (*tail_position < TAIL_STOP_UP) *tail_position = TAIL_STOP_UP;
//
//tail_servo.write(*tail_position);
//
//Serial.print("upTail Pos = ");
//Serial.println(*tail_position);
//delay(10);
//}

Blockly.Arduino.downwards = function() { //伺服 B1
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticTail'] = 'tail_servo.attach(FTAIL_SERVO);\n  tail_servo.write(tail_initPos);\n  ' + 'tail_position = tail_initPos;\n  ';

	Blockly.Arduino.definitions_['roboticTail_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    tail_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   tail_position;\n';

	//	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'TailControlDown(tail_servo, &tail_position);\n';
	return code;
};

//void TailControlDown(Servo tail_servo, double *tail_position) {//90
//
//Serial.print("down init = ");
//Serial.println(*tail_position);
//if ((*tail_position) >  TAIL_STOP_DOWN) *tail_position =  TAIL_STOP_DOWN;
//tail_servo.write(*tail_position);
//Serial.print("Tail Pos = ");
//Serial.println(*tail_position);
//delay(10);
//
//}

Blockly.Arduino.catchUp = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'arm_position = arm_initPos;\n  ' + 'hand_position = hand_initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   arm_position;\n' +
		'double   hand_position;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ArmControlUp(arm_servo, &arm_position);\n';
	return code;
};

Blockly.Arduino.catchDown = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'arm_position = arm_initPos;\n  ' + 'hand_position = hand_initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   arm_position;\n' +
		'double   hand_position;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ArmControlDown(arm_servo, &arm_position);\n';
	return code;
};

Blockly.Arduino.catchClose = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'arm_position = arm_initPos;\n  ' + 'hand_position = hand_initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   arm_position;\n' +
		'double   hand_position;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'HandControlClose(hand_servo, &hand_position);\n';
	return code;
};

Blockly.Arduino.catchOpen = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'arm_position = arm_initPos;\n  ' + 'hand_position = hand_initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   arm_position;\n' +
		'double   hand_position;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'HandControlOpen(hand_servo, &hand_position);\n';
	return code;
	hand_position
};

Blockly.Arduino.catch = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'steering_pos = initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   steering_pos;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ActionGrab(arm_servo, hand_servo);\n';
	return code;
};

Blockly.Arduino.place = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticArm'] = 'arm_servo.attach(ARM_SERVO);\n  hand_servo.attach(HAND_SERVO);\n  arm_servo.write(arm_initPos);\n  hand_servo.write(hand_initPos);\n  ' +
		'steering_pos = initPos;\n';

	Blockly.Arduino.definitions_['roboticArm_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    arm_servo;\nServo    hand_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   steering_pos;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'ActionPut(arm_servo, hand_servo);\n';
	return code;
};

Blockly.Arduino.AdjustLoaderAngle = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['bulletGun'] = 'getServoAngleEEPROM(&loaderStandby_pos);\n\n  ' +
		'bulletTrigger_servo.attach(bulletTRIGGER_SERVO);\n  bulletLoader_servo.attach(bulletLOADER_SERVO);\n  ' +
		'bulletTrigger_servo.write(trigger_initPos);\n  bulletLoader_servo.write(loaderStandby_pos);\n  ' +
		'bulletLeft = bulletNumber;\n\n  ';
	Blockly.Arduino.definitions_['shotheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    bulletTrigger_servo;\nServo    bulletLoader_servo;\n' +
		'int      loaderStandby_pos;\n' +
		'int      bulletLeft;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'TuningLoader(bulletLoader_servo, bulletTrigger_servo, &bulletLeft) ;\n';
	return code;
};

Blockly.Arduino.loaded = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['bulletGun'] = 'getServoAngleEEPROM(&loaderStandby_pos);\n\n  ' +
		'bulletTrigger_servo.attach(bulletTRIGGER_SERVO);\n  bulletLoader_servo.attach(bulletLOADER_SERVO);\n  ' +
		'bulletTrigger_servo.write(trigger_initPos);\n  bulletLoader_servo.write(loaderStandby_pos);\n  ' +
		'bulletLeft = bulletNumber;\n\n  ';

	Blockly.Arduino.definitions_['shotheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    bulletTrigger_servo;\nServo    bulletLoader_servo;\n' +
		'int      loaderStandby_pos;\n' +
		'int      bulletLeft;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'loadBullet(bulletLoader_servo, &bulletLeft);\n';
	return code;
};

Blockly.Arduino.shot = function() {
	
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['bulletGun'] = 'getServoAngleEEPROM(&loaderStandby_pos);\n\n  ' +
		'bulletTrigger_servo.attach(bulletTRIGGER_SERVO);\n  bulletLoader_servo.attach(bulletLOADER_SERVO);\n  ' +
		'bulletTrigger_servo.write(trigger_initPos);\n  bulletLoader_servo.write(loaderStandby_pos);\n  ' +
		'bulletLeft = bulletNumber;\n\n  ';

	Blockly.Arduino.definitions_['shotheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    bulletTrigger_servo;\nServo    bulletLoader_servo;\n' +
		'int      loaderStandby_pos;\n' +
		'int      bulletLeft;\n\n';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fireBullet(bulletTrigger_servo, bulletLoader_servo, &bulletLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n\n';
	return code;
};

Blockly.Arduino.singleShot = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['bulletGun'] = 'getServoAngleEEPROM(&loaderStandby_pos);\n\n  ' +
		'bulletTrigger_servo.attach(bulletTRIGGER_SERVO);\n  bulletLoader_servo.attach(bulletLOADER_SERVO);\n  ' +
		'bulletTrigger_servo.write(trigger_initPos);\n  bulletLoader_servo.write(loaderStandby_pos);\n  ' +
		'bulletLeft = bulletNumber;\n\n  ';

	Blockly.Arduino.definitions_['shotheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    bulletTrigger_servo;\nServo    bulletLoader_servo;\n' +
		'int      loaderStandby_pos;\n' +
		'int      bulletLeft;\n\n';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'RubberbandFireSingle(bulletLoader_servo, bulletTrigger_servo, &bulletLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n';
	return code;
};

Blockly.Arduino.Bursts = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['bulletGun'] = 'getServoAngleEEPROM(&loaderStandby_pos);\n\n  ' +
		'bulletTrigger_servo.attach(bulletTRIGGER_SERVO);\n  bulletLoader_servo.attach(bulletLOADER_SERVO);\n  ' +
		'bulletTrigger_servo.write(trigger_initPos);\n  bulletLoader_servo.write(loaderStandby_pos);\n  ' +
		'bulletLeft = bulletNumber;\n\n  ';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.definitions_['shotheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    bulletTrigger_servo;\nServo    bulletLoader_servo;\n' +
		'int      loaderStandby_pos;\n' +
		'int      bulletLeft;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'RubberbandFireAll(bulletLoader_servo, bulletTrigger_servo, &bulletLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n';
	return code;
};

function isNeed(a) {
	var xml = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
	var x = xml.getElementsByTagName("block");

	var flag = false;
	for(var i = 0; i < x.length; i++) {
		if(x[i].getAttribute('type') == a) {
			flag = true;
		}
	}
	return flag;
}

Blockly.Arduino.UCD_U = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanHeadPosition(fanHeadVertical_servo, UP,&fanHeadVerticalPosition);\n';

	return code;
};

Blockly.Arduino.UCD_C = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanHeadPosition(fanHeadVertical_servo, CENTER,&fanHeadVerticalPosition);\n';

	return code;
};

Blockly.Arduino.UCD_D = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanHeadPosition(fanHeadVertical_servo, DOWN,&fanHeadVerticalPosition);\n';

	return code;
};

Blockly.Arduino.big_wind = function() {//大风
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanSpeed = spinFAST;\n';

	return code;
};

Blockly.Arduino.mid_wind = function() {//中风
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanSpeed = spinMEDIUM;\n';

	return code;
};

Blockly.Arduino.small_wind = function() {//小风
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['fan'] = 'fanHeadHorizontal_servo.attach(fanHeadHORIZONTAL_SERVO);\n  fanHeadVertical_servo.attach(fanHeadVERTICAL_SERVO);\n  ' +
		'fanHeadHorizontalPosition = fanHeadHori_initPos;\n  fanHeadVerticalPosition = fanHeadVerti_initPos;\n  ' +
		'fanHeadHorizontal_servo.write(fanHeadHori_initPos);\n  ' +
		'fanHeadVertical_servo.write(fanHeadVerti_initPos);\n\n  ' +
		'fanSpeed = spinFAST;\n\n';

	Blockly.Arduino.definitions_['fanheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    fanHeadHorizontal_servo;\nServo    fanHeadVertical_servo;\n' +
		'bool     fanRunningStatus;\n' +
		'bool     fanHeadMovingStatus;\n' +
		'int      fanHeadMovingDirection;\n' +
		'int      fanSpeed;\n' +
		'double   fanHeadHorizontalPosition;\n' +
		'double   fanHeadVerticalPosition;\n\n';

	//Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fanSpeed = spinSLOW;\n';

	return code;
};

Blockly.Arduino.shell_loaded = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['batteryGun'] = 'batteryTrigger_servo.attach(batteryTRIGGER_SERVO);\n  batteryLoader_servo.attach(batteryLOADER_SERVO);\n  batteryTrigger_servo.write(Batt_trigger_initPos);\n  batteryLoader_servo.write(Batt_loader_initPos);\n  ' +
		'batteryLeft = batteryNumber;\n\n  ';

	Blockly.Arduino.definitions_['batterGunheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    batteryTrigger_servo;\nServo    batteryLoader_servo;\n' +
		'int      batteryLeft;\n\n';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'loadBatteryBullet(batteryLoader_servo, &batteryLeft);\n';
	return code;
};

Blockly.Arduino.shell_shot = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['batteryGun'] = 'batteryTrigger_servo.attach(batteryTRIGGER_SERVO);\n  batteryLoader_servo.attach(batteryLOADER_SERVO);\n  batteryTrigger_servo.write(Batt_trigger_initPos);\n  batteryLoader_servo.write(Batt_loader_initPos);\n  ' +
		'batteryLeft = batteryNumber;\n\n  ';

	Blockly.Arduino.definitions_['batterGunheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    batteryTrigger_servo;\nServo    batteryLoader_servo;\n' +
		'int      batteryLeft;\n\n';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'fireBatteryBullet(batteryTrigger_servo, &batteryLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n\n';

	return code;
};

Blockly.Arduino.burstsShell = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['batteryGun'] = 'batteryTrigger_servo.attach(batteryTRIGGER_SERVO);\n  batteryLoader_servo.attach(batteryLOADER_SERVO);\n  batteryTrigger_servo.write(Batt_trigger_initPos);\n  batteryLoader_servo.write(Batt_loader_initPos);\n  ' +
		'batteryLeft = batteryNumber;\n\n  ';

	Blockly.Arduino.definitions_['batterGunheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    batteryTrigger_servo;\nServo    batteryLoader_servo;\n' +
		'int      batteryLeft;\n\n';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'BatteryFireAll(batteryLoader_servo, batteryTrigger_servo, &batteryLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n\n';

	return code;
};

Blockly.Arduino.singleShell = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['batteryGun'] = 'batteryTrigger_servo.attach(batteryTRIGGER_SERVO);\n  batteryLoader_servo.attach(batteryLOADER_SERVO);\n  batteryTrigger_servo.write(Batt_trigger_initPos);\n  batteryLoader_servo.write(Batt_loader_initPos);\n  ' +
		'batteryLeft = batteryNumber;\n\n  ';

	Blockly.Arduino.definitions_['batterGunheader'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    batteryTrigger_servo;\nServo    batteryLoader_servo;\n' +
		'int      batteryLeft;\n\n';

	Blockly.Arduino.definitions_['RF_controller_header'] = 'int PS2_Button_Read[6];';

	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'BatteryFireSingle(batteryLoader_servo, batteryTrigger_servo, &batteryLeft);\n' +
		'PS2_Button_Read[2]=0;\n' +
		'PS2_Button_Read[3]=0;\n\n';

	return code;
};

//Blockly.Arduino.MotorControl = function() {
//	// TODO: Assemble JavaScript into code variable.
//	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT); \n pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
//	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
//	var dropdown_MotorName = this.getFieldValue('MotorName');
//	var MotorStatus = this.getFieldValue('RunningStatus');
//
//	var code = 'MotorControl(' + dropdown_MotorName + ', ' + MotorStatus + ');\n';
//	return code;
//};

Blockly.Arduino.Score = function() {
	Blockly.Arduino.setups_['TseriesClass_1'] = 'resetScoreboard();\n  ' +
		'basket_servo.attach(BASKET_SERVO);\n  pinAsInput(BALL_SENSOR);\n  pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  ' +
		'backBoard_Pos = backboard_initPos;\n  ' +
		'scoredPoints = 0;\n\n  ';

	Blockly.Arduino.definitions_['TseriesClass_1'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    basket_servo;\n' +
		'double   backBoard_Pos;\n' +
		'int      scoredPoints;\n\n';

	var scoreSelection = this.getFieldValue('score');

	var code = 'checkBall(' + scoreSelection + ', ' + 'BALL_SENSOR' + ', ' + '&scoredPoints);\n';

	return code;
}

Blockly.Arduino.basketSpeed = function() {
	Blockly.Arduino.setups_['TseriesClass_1'] = 'resetScoreboard();\n  ' +
		'basket_servo.attach(BASKET_SERVO);\n  pinAsInput(BALL_SENSOR);\n  pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  ' +
		'backBoard_Pos = backboard_initPos;\n  ' +
		'scoredPoints = 0;\n\n  ';

	Blockly.Arduino.definitions_['TseriesClass_1'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		//'#include    ' + '\<' + 'EEPROM.h' + '\>' + '\n' + '\n' +
		'Servo    basket_servo;\n' +
		'double   backBoard_Pos;\n' +
		'int      scoredPoints;\n\n';

	var noMoveLim = this.getFieldValue('noMoveLimit');
	var slowMoveLim = this.getFieldValue('slowMoveLimit');
	var fastMoveLim = this.getFieldValue('fastMoveLimit');

	var code = 'backboardMove(&scoredPoints' + ', ' + 'basket_servo' + ', ' + '&backBoard_Pos' + ', ' +
		noMoveLim + ', ' + slowMoveLim + ', ' + fastMoveLim + ');\n';

	return code;
}

Blockly.Arduino.catHandle = function() {
	Blockly.Arduino.setups_['TseriesClass_2'] = 'cathand_servo.attach(CAT_HAND_SERVO);\n  pinAsInput(CAT_MOUTH_SENSORPIN);\n\n';

	Blockly.Arduino.definitions_['TseriesClass_2'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    cathand_servo;\n\n';

	var code = 'checkMouthTouch(CAT_MOUTH_SENSORPIN, cathand_servo);\n';

	return code;
}

Blockly.Arduino.upwards = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['roboticTail'] = 'tail_servo.attach(FTAIL_SERVO);\n  tail_servo.write(tail_initPos);\n  ' + 'tail_position = tail_initPos;\n  ';

	Blockly.Arduino.definitions_['roboticTail_header'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    tail_servo;\n' +
		//'int      PS2_Button_Read[6];\n\n' +
		'double   tail_position;\n';

	//	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(ENA,OUTPUT);\n  pinMode(ENB,OUTPUT);';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var code = 'TailControlUp(tail_servo, &tail_position);\n';
	return code;
};

Blockly.Arduino.radarMove = function() {//b1       
	Blockly.Arduino.setups_['radarMove'] = 'radar_servo.attach(FRADAR_SERVO);\n  radar_servo.write(radar_initPos);\n  radarPos = radar_initPos;\n   moveFlag = true;\n ';

	Blockly.Arduino.definitions_['radarMove'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo       radar_servo;\n\n' + '\n' +
		                                          'double      radarPos;\n' + 'double      ang;\n' + 'bool        moveFlag;';

	var code0 = 'moveFlag = true;\n';
	var code1 = 'radarStart(radar_servo , moveFlag ,&ang );\n';
	sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	if(isNeedStrengthen('controls_if_new', 'radarMove')) {
		var code = code0;
		sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	} else {
		var code = code0 + code1;
	}      
	return code;
}

Blockly.Arduino.indicatorLight = function() {//b1 ,sensor-a1.a2
  
  Blockly.Arduino.setups_['Tseries2RGBLED'] = 'radarStrip.begin();\n  ' + 'radarStrip.show();\n  pinAsInput(RADAR1_SENSORPIN);\n ';
  
  Blockly.Arduino.definitions_['radarMove'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo       radar_servo;\n\n' + '\n' +
		                                          'double      radarPos;\n' + 'double      ang;\n' + 'bool        moveFlag;';


	Blockly.Arduino.definitions_['Tseries2RGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n'  + '\n' + 'extern Adafruit_NeoPixel radarStrip;\n' + 'bool        runFlag;';
	
	
	var code0 = 'runFlag = true;\n';
	var code1 = 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n';
	sessionStorage.setItem('radarLight_code1', 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n')
	if(isNeedStrengthen('controls_if_new', 'indicatorLight')) {
		var code = code0;
		sessionStorage.setItem('radarLight_code1', 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n')
	} else {
		var code = code0 + code1;
	}      


	return code;
}

Blockly.Arduino.indicatorLightOff = function() {

	Blockly.Arduino.setups_['Tseries2RGBLED'] = 'radarStrip.begin();\n  ' + 'radarStrip.show();\n  ';

	Blockly.Arduino.definitions_['Tseries2RGBLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel radarStrip;\n' + 'bool        runFlag;';
		
	var code0 = 'runFlag = false;\n';
	var code1 = 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n';
	sessionStorage.setItem('radarLight_code1', 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n')
	if(isNeedStrengthen('controls_if_new', 'indicatorLightOff')) {
		var code = code0;
		sessionStorage.setItem('radarLight_code1', 'indicatorLightRun(runFlag,RADAR1_SENSORPIN,&ang);\n')
	} else {
		var code = code0 + code1;
	}


	return code;
}

Blockly.Arduino.radarStop = function() {
	Blockly.Arduino.setups_['radarMove'] = 'radar_servo.attach(FRADAR_SERVO);\n  radar_servo.write(radar_initPos);' + 'radarPos = radar_initPos;\n; ';

	Blockly.Arduino.definitions_['radarMove'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo radar_servo;\n\n' + '\n' +
		'double radarPos ;' + 'double ang ;' + 'bool moveFlag;';

	var code0 = 'moveFlag = false;\n';
	var code1 = 'radarStart(radar_servo , moveFlag ,&ang );\n';
	sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	if(isNeedStrengthen('controls_if_new', 'radarMove')) {
		var code = code0;
		sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	} else {
		var code = code0 + code1;
	}
	return code;
}

Blockly.Arduino.catSound = function() {
	Blockly.Arduino.setups_['TseriesClass_2'] = 'cathand_servo.attach(CAT_HAND_SERVO);\n  pinAsInput(CAT_MOUTH_SENSORPIN);\n  pinAsInput(CAT_HEAD_SENSORPIN);\n\n';

	Blockly.Arduino.definitions_['TseriesClass_2'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    cathand_servo;\n\n';

	var code = 'checkHeadTouch(CAT_HEAD_SENSORPIN);\n';

	return code;
}



Blockly.Arduino.scanningGoForward = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n';
	Blockly.Arduino.setups_['TseriesClass_3'] = 'raptorHead_servo.attach(CAT_HAND_SERVO);\n  raptorHead_servo.write(raptorHead_initPos);\n  pinAsInput(RAPTORHEAD_SENSORPIN);\n\n ' +
		' raptorHead_Pos = raptorHead_initPos;\n  raptorHead_movingDirection = POSITIVE;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_3'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    raptorHead_servo;\n\n' +
		'double   raptorHead_Pos;\n' +
		'int      raptorHead_movingDirection;\n\n';

	var code = 'RaptorCruise(raptorHead_servo, &raptorHead_Pos, &raptorHead_movingDirection);\n';

	return code;
}

Blockly.Arduino.obstacleGoBack = function() {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n';
	Blockly.Arduino.setups_['TseriesClass_3'] = 'raptorHead_servo.attach(CAT_HAND_SERVO);\n  raptorHead_servo.write(raptorHead_initPos);\n  pinAsInput(RAPTORHEAD_SENSORPIN);\n\n ' +
		' raptorHead_Pos = raptorHead_initPos;\n  raptorHead_movingDirection = POSITIVE;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_3'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    raptorHead_servo;\n\n' +
		'double   raptorHead_Pos;\n' +
		'int      raptorHead_movingDirection;\n\n';

	var code = 'avoidObstacle(RAPTORHEAD_SENSORPIN, &raptorHead_movingDirection, &raptorHead_Pos, raptorHead_servo);\n';

	return code;
}

Blockly.Arduino.firstBtn = function() {
	Blockly.Arduino.setups_['TseriesClass_4'] = 'Hammer_servo.attach(HAMMER_SERVO);\n  Hammer_servo.write(hammer_initPos);\n\n  ' +
		'pinAsInput(LEFT_WHEEL_BUTTON);\n  pinAsInput(RIGHT_WHEEL_BUTTON);\n  pinAsInput(BACKWARD_BUTTON);\n\n  ' +
		'attacked_times = 0;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_4'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    Hammer_servo;\n\n' +
		'int      attacked_times;\n\n';

	var code = 'ControlLeftWheel(LEFT_WHEEL_BUTTON, BACKWARD_BUTTON);\n';

	return code;
}

Blockly.Arduino.secondBtn = function() {
	Blockly.Arduino.setups_['TseriesClass_4'] = 'Hammer_servo.attach(HAMMER_SERVO);\n  Hammer_servo.write(hammer_initPos);\n\n  ' +
		'pinAsInput(LEFT_WHEEL_BUTTON);\n  pinAsInput(RIGHT_WHEEL_BUTTON);\n  pinAsInput(BACKWARD_BUTTON);\n\n  ' +
		'attacked_times = 0;\n\n';
   
	Blockly.Arduino.definitions_['TseriesClass_4'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    Hammer_servo;\n\n' +
		'int      attacked_times;\n\n';

	var code = 'ControlRightWheel(RIGHT_WHEEL_BUTTON, BACKWARD_BUTTON);\n';

	return code;
}

Blockly.Arduino.backBtn = function() {
	Blockly.Arduino.setups_['TseriesClass_4'] = 'Hammer_servo.attach(HAMMER_SERVO);\n  Hammer_servo.write(hammer_initPos);\n\n  ' +
		'pinAsInput(LEFT_WHEEL_BUTTON);\n  pinAsInput(RIGHT_WHEEL_BUTTON);\n  pinAsInput(BACKWARD_BUTTON);\n\n  ' +
		'attacked_times = 0;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_4'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    Hammer_servo;\n\n' +
		'int      attacked_times;\n\n';

	var code = 'ControlTwoWheelBackward(BACKWARD_BUTTON, LEFT_WHEEL_BUTTON, RIGHT_WHEEL_BUTTON);\n';

	return code;
}

Blockly.Arduino.hammerKnock = function() {//B1舵机
	Blockly.Arduino.setups_['TseriesClass_4'] = 'Hammer_servo.attach(HAMMER_SERVO);\n  Hammer_servo.write(hammer_initPos);\n\n  ' +
//		'pinAsInput(LEFT_WHEEL_BUTTON);\n  pinAsInput(RIGHT_WHEEL_BUTTON);\n  pinAsInput(BACKWARD_BUTTON);\n\n  ' +
		'hammer_position  = hammer_initPos;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_4'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n'+'double    hammer_position;\n\n '+'\n' +'Servo    Hammer_servo;\n\n';

	var code = 'HammerKnock(Hammer_servo);\n';//A4

	return code;
}

Blockly.Arduino.optionalServe = function() {
	
	var whichServe = this.getFieldValue('optionalServe');
	var whichAng = this.getFieldValue('optionalAng');
	if(whichAng>180){
		whichAng = 180;
	}
	if(whichAng<0){
		whichAng = 0;
	}
	var giveServe ='';
	if(whichServe == 'B1'){
		giveServe ='B1_SERVO';
	}else if(whichServe == 'B2'){
		giveServe ='B2_SERVO';
	}else if(whichServe == 'B3'){
		giveServe ='B3_SERVO';
	}else if(whichServe == 'B4'){
		giveServe ='B4_SERVO';
	}
	
	Blockly.Arduino.setups_['optionalServe'] = 'o_servo.attach('+giveServe+');\n  o_servo.write(0);\n\n  ';

	Blockly.Arduino.definitions_['optionalServe'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    o_servo;\n\n';

	var code = 'optionalServeAng(o_servo,'+whichAng+');\n';//A4

	return code;
}


Blockly.Arduino.bumperCar = function() {
	
	
	Blockly.Arduino.setups_['optionalServe'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);';

	Blockly.Arduino.definitions_['optionalServe'] = '';

	var code = 'lesson_3();\n';

	return code;
}




Blockly.Arduino.numberLives = function() {
	Blockly.Arduino.setups_['TseriesClass_4'] = 'Hammer_servo.attach(HAMMER_SERVO);\n  Hammer_servo.write(hammer_initPos);\n\n  ' +
		'pinAsInput(LEFT_WHEEL_BUTTON);\n  pinAsInput(RIGHT_WHEEL_BUTTON);\n  pinAsInput(BACKWARD_BUTTON);\n\n  pinAsOutput(LED_b1);\n  pinAsOutput(LED_b2);\n ' +
		' attacked_times = 0;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_4'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo    Hammer_servo;\n\n' +
		'int      attacked_times;\n\n';

	var AttackedNumber = this.getFieldValue('number');

	var code = 'checkIfAttacked(&attacked_times, ATTACKED_SENSORPIN, ' + AttackedNumber + ');\n';

	return code;
}

Blockly.Arduino.policeLight = function() {
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
}

Blockly.Arduino.presShake = function() {
	Blockly.Arduino.setups_['TseriesClass_6'] = 'TailServo.attach(TAIL_SERVO);\n  TailServo.write(TailServo_Init_Pos);\n\n  ' +
		'pinAsInput(LEFT_SENSOR);\n  pinAsInput(RIGHT_SENSOR);\n  pinAsInput(NOSE_BUTTON);\n  ' +
		'pinAsOutput(LEFT_LED);\n  pinAsOutput(RIGHT_LED);\n\n  ' +
		'TailPos = TailServo_Init_Pos;\n\n';

	Blockly.Arduino.definitions_['TseriesClass_6'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + '\n' +
		'Servo       TailServo;\n\n' +
		'double      TailPos;\n\n';

	var code = 'BirdTailSwing(NOSE_BUTTON, TailServo, &TailPos);\n';

	return code;
}

Blockly.Arduino.pursuit = function() {
	Blockly.Arduino.setups_['TseriesClass_6'] = 'singleLED.begin();\n  '+ 'pinMode(ZW_B1,OUTPUT);\n'+'  pinMode(ZW_B2,OUTPUT);\n' + '  singleLED.show();\n\n  TailServo.attach(TAIL_SERVO);\n  TailServo.write(TailServo_Init_Pos);\n\n  ' +
		'pinAsInput(LEFT_SENSOR);\n  pinAsInput(RIGHT_SENSOR);\n  pinAsInput(NOSE_BUTTON);\n  ' +
		'pinAsOutput(LEFT_LED);\n  pinAsOutput(RIGHT_LED);\n\n  ' +
		'TailPos = TailServo_Init_Pos;\n\n  pinMode(MOTOR1P,OUTPUT);\n\n  pinMode(MOTOR1M,OUTPUT);\n\n  pinMode(MOTOR2P,OUTPUT);\n\n  pinMode(MOTOR2M,OUTPUT);';

	Blockly.Arduino.definitions_['TseriesClass_6'] = '#include    ' + '\<' + 'Servo.h' + '\>'+ '\n'+  '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>'  + '\n' + '\n' +
		'Servo       TailServo;\n\n' +
		'double      TailPos;\n\n' +'extern Adafruit_NeoPixel singleLED;\n\n';;

	var code = 'BirdFollowTarget(LEFT_SENSOR, RIGHT_SENSOR);\n';

	return code;
}

Blockly.Arduino.delay = function() {

	var delayT = this.getFieldValue('delay') * 1000;

	var code = 'delay(' + delayT + ');\n';

	return code;
}

Blockly.Arduino.yellowLED = function() {
    var 	whichLamp = this.getFieldValue('lampName');
	
	Blockly.Arduino.setups_['yellowLED'] = 'singleLED.begin();\n  '+ 'pinMode(ZW_B1,OUTPUT);\n'+'  pinMode(ZW_B2,OUTPUT);\n'+'  pinMode(ZW_B3,OUTPUT);\n'+ '  pinMode(ZW_B4,OUTPUT);\n' + '  singleLED.show();\n\n';

	Blockly.Arduino.definitions_['yellowLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	var code = 'yellowLEDOn('+whichLamp+');\n';
	return code;
		
};


Blockly.Arduino.offLED = function() {
	var 	whichLampOff = this.getFieldValue('lampNameOff');
	// TODO: Assemble JavaScript into code variable.

	Blockly.Arduino.definitions_['yellowLED'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n' +
		'extern Adafruit_NeoPixel singleLED;\n\n';
	var code = 'offLED('+whichLampOff+');\n';
	return code;
};


var angleOrigin;
var isHide = 0;
Blockly.Arduino.ServoOrigin = function() {
	angleOrigin = this.getFieldValue('servoOrigin');
	var servo='';
	if(angleOrigin > 180) {
		angleOrigin = 180
	}
	if(angleOrigin < 0) {
		angleOrigin = 0;
	}
	var whichB = this.getFieldValue('ServoName'); //哪个端口
	
	if(whichB == 1) {
		servo = 'ZW_B1';  
		isHide  =  1;
	} else if(whichB == 2) {
		servo = 'ZW_B2';
		isHide  =  2;
	} else if(whichB == 3) {
		servo = 'ZW_B3';
		isHide  =  3;
	} else if(whichB == 4) {
		servo = 'ZW_B4';
		isHide  =  4;
	}
	Blockly.Arduino.setups_['ServoOrigin'+servo] = 'Self_servo'+servo+'.attach(' + servo + ');';
	Blockly.Arduino.setups_['ServoOriginSetvalue'+servo] = 'ang'+servo+' = ' + angleOrigin + ';\n  Self_servo'+servo+'.write(ang'+servo+');';
	
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['ServoOrigin'+servo] = 'Servo  Self_servo'+servo+';' + '\n' + 'double ang'+servo+';';
		

	var code = '';
	return code;
};


Blockly.Arduino.ServoControl = function() {
	var angleValue = this.getFieldValue('angleValue'); //转的角度
	var whichB = this.getFieldValue('ServoName'); //哪个端口
	var maxValue = this.getFieldValue('maxValue');//极值
	var servo = '';
	if(whichB == 1) {
		servo = 'ZW_B1';
	} else if(whichB == 2) {
		servo = 'ZW_B2';
	} else if(whichB == 3) {
		servo = 'ZW_B3';
	} else if(whichB == 4) {
		servo = 'ZW_B4';
	}
	
	if(angleValue > 10) {
		angleValue = 10
	}
	if(angleValue < -10) {
		angleValue = -10;
	}
	
	if(whichB != isHide){
		Blockly.Arduino.setups_['ServoOrigin'+servo] = 'Self_servo'+servo+'.attach(' + servo + '); ';
	}
	
	
	

	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['ServoOrigin'+servo] = 'Servo  Self_servo'+servo+';' + '\n' + 'double ang'+servo+';';
	var code = 'servoChange(Self_servo'+servo+',&ang'+servo+',' + angleValue + ','+maxValue+');';
	return code;
};

Blockly.Arduino.ServoTurnto = function() {
	var Servoangle = this.getFieldValue('Servoangle'); //转的角度
	var whichB = this.getFieldValue('ServoName'); //哪个端口
	var servo='';
	if(whichB == 1) {
		servo = 'ZW_B1';
	} else if(whichB == 2) {
		servo = 'ZW_B2';
	} else if(whichB == 3) {
		servo = 'ZW_B3';
	} else if(whichB == 4) {
		servo = 'ZW_B4';
	}
	
	if(Servoangle > 180) {
		Servoangle = 180
	}
	if(Servoangle < 0) {
		Servoangle = 0;
	}
	
	
	if(whichB != isHide){
		Blockly.Arduino.setups_['ServoOrigin'+servo] = 'Self_servo'+servo+'.attach(' + servo + '); ';	}
	
		Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
Blockly.Arduino.definitions_['ServoOrigin'+servo] = 'Servo Self_servo'+servo+';' + '\n' + 'double ang'+servo+';';
	var code = 'servoTurnto(Self_servo'+servo+','+Servoangle+');';
	return code;
};


Blockly.Arduino.lampOn = function() {
	
	var whichColor = this.getFieldValue('lampName');

	Blockly.Arduino.setups_['lampLED'] = 'lampRGB.begin();\n  ' + 'lampRGB.show();\n  ' ;
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['lampLED'] = 
		'extern Adafruit_NeoPixel lampRGB;\n';

	var code = 'LEDLampOn('+whichColor+');\n';

	return code;
}

Blockly.Arduino.lampOff = function() {
	Blockly.Arduino.setups_['lampLED'] = 'lampRGB.begin();\n  ' + 'lampRGB.show();\n  '
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['lampLED'] = 
		'extern Adafruit_NeoPixel lampRGB;\n';

	var code = 'LEDLampOff(2);\n';

	return code;
}

Blockly.Arduino.radarStop = function() {
	Blockly.Arduino.setups_['radarMove'] = 'radar_servo.attach(FRADAR_SERVO);\n  radar_servo.write(radar_initPos);' + 'radarPos = radar_initPos;\n; ';

	Blockly.Arduino.definitions_['radarMove'] = '#include    ' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo radar_servo;\n\n' + '\n' +
		'double radarPos ;' + 'double ang ;' + 'bool moveFlag;';

	var code0 = 'moveFlag = false;\n';
	var code1 = 'radarStart(radar_servo , moveFlag ,&ang );\n';
	sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	if(isNeedStrengthen('controls_if_new', 'radarMove')) {
		var code = code0;
		sessionStorage.setItem('radarMove_code1', 'radarStart(radar_servo , moveFlag ,&ang );\n')
	} else {
		var code = code0 + code1;
	}
	return code;
}

Blockly.Arduino.forkliftLampOn = function() {
	Blockly.Arduino.setups_['forkliftLamp1'] = 'forkliftRGB.begin();\n  ';
	Blockly.Arduino.setups_['forkliftLamp2'] = 'forkliftLampOn(0);\n';
	Blockly.Arduino.setups_['forkliftLamp3'] = 'forkliftRGB.show();\n  ';
	
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['forkliftLampD'] = 'int forkliftFlag;\n'+
		'extern Adafruit_NeoPixel forkliftRGB;\n';
	
	var code0 = 'forkliftFlag = 1;\n';
	var code1 = 'forkliftLampOn(forkliftFlag);\n';
	sessionStorage.setItem('forkliftLamp','forkliftLampOn(forkliftFlag);\n');
	if(isNeedStrengthen('controls_if_new', 'forkliftLampOn')){
		var code = code0;
		sessionStorage.setItem('forkliftLamp','forkliftLampOn(forkliftFlag);\n');
	}else {
		var code = code0 + code1;
	}

	return code;
}

Blockly.Arduino.forkliftLampOff = function() {
	Blockly.Arduino.setups_['forkliftLamp1'] = 'forkliftRGB.begin();\n  ';
	Blockly.Arduino.setups_['forkliftLamp3'] = 'forkliftRGB.show();\n  ';
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['forkliftLampD'] = 'int forkliftFlag;\n'+
		'extern Adafruit_NeoPixel forkliftRGB;\n';

	var code = 'forkliftFlag = 2;\n';

	return code;
}


Blockly.Arduino.forkliftTopLampOn = function() {
	Blockly.Arduino.setups_['forkliftTopLamp1'] = 'forkliftTopRGB.begin();\n  ';
	Blockly.Arduino.setups_['forkliftTopLamp2'] = 'forkliftTopLampOn(0);\n';
	Blockly.Arduino.setups_['forkliftTopLamp3'] = 'forkliftTopRGB.show();\n  ';
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['forkliftTopLamp'] = 'int forkliftTopFlag;\n'+
		'extern Adafruit_NeoPixel forkliftTopRGB;\n';

	var code = 'forkliftTopLampOn(1);\n';
	var code0 = 'forkliftTopFlag = 1;\n';
	var code1 = 'forkliftTopLampOn(forkliftTopFlag);\n';
	sessionStorage.setItem('forkliftTopLamp','forkliftTopLampOn(forkliftTopFlag);\n');
	if(isNeedStrengthen('controls_if_new', 'forkliftTopLampOn')){
		var code = code0;
		sessionStorage.setItem('forkliftTopLamp','forkliftTopLampOn(forkliftTopFlag);\n');
	}else{
		var code = code0+code1;
	}
	return code;
}

Blockly.Arduino.forkliftTopLampOff = function() {
	Blockly.Arduino.setups_['forkliftTopLamp1'] = 'forkliftTopRGB.begin();\n  ';
	Blockly.Arduino.setups_['forkliftTopLamp3'] = '  forkliftTopRGB.show();\n  ';
	Blockly.Arduino.setups_['forkliftTopLamp'] = 'forkliftTopRGB.begin();\n' + 'forkliftTopRGB.show();\n  '
	Blockly.Arduino.definitions_['AN'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' + '\n';
	Blockly.Arduino.definitions_['forkliftTopLamp'] = 'int forkliftTopFlag;\n'+
		'extern Adafruit_NeoPixel forkliftTopRGB;\n';

	var code = 'forkliftTopFlag = 2;\n';

	return code;
}
//t4 舵机模块
Blockly.Arduino.servoSpeed = function() {
  var code ='s' + (this.getFieldValue('servoSpeed'));
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}

Blockly.Arduino.servoInit = function() {
  var code ='i' + (this.getFieldValue('servorOriginAngle'));
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}

Blockly.Arduino.servoRotate = function() {
  var code ='r' + (this.getFieldValue('servorAngle'));
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}

Blockly.Arduino.servoRotate_t5 = function() {
  var code ='r' + (Blockly.Arduino.valueToCode(this,'Servot5',Blockly.Arduino.ORDER_ASSIGNMENT)||'0');
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}

Blockly.Arduino.servoIncrement = function() {
  var code ='c' + (this.getFieldValue('incrementAngle'));
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}
Blockly.Arduino.servoIncrementPro = function() {
  var code ='p' + (this.getFieldValue('incrementAnglePro'))+ ':' +(this.getFieldValue('limit'));
  var order = code < 0 ? Blockly.Arduino.ORDER_UNARY_PREFIX : Blockly.Arduino.ORDER_ATOMIC;
  return [code, order];
}
Blockly.Arduino.chooseServo = function() { // ServoOrigin
	var servo = '';	
	var whichPin = this.getFieldValue('ServoName'); //哪个端口
	if(whichPin == 1) {
		servo = 'ZW_B1';  
		isHide  =  1;
	} else if(whichPin == 2) {
		servo = 'ZW_B2';
		isHide  =  2;
	} else if(whichPin == 3) {
		servo = 'ZW_B3';
		isHide  =  3;
	} else if(whichPin == 4) {
		servo = 'ZW_B4';
		isHide  =  4;
	}
	
	Blockly.Arduino.setups_['ServoOrigin'+servo] = 'Self_servo'+servo+'.attach(' + servo + ');\n  ang'+servo+' = 0;\n  Self_servo'+servo+'.write(ang'+servo+');';
	
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['ServoOrigin'+servo] = 'Servo Self_servo'+servo+';' + '\n' + 'double ang'+servo+';';
	
	var arg = Blockly.Arduino.valueToCode(this,'VALUE',Blockly.Arduino.ORDER_ASSIGNMENT)||'0';
	var firstLetter = arg.substr(0,1);
	var extremum = 0;
	var number = 0;
	if(firstLetter == 'i'){//init servo angle
		var argRest = arg.split("i");
		if(argRest[1]>180){
			argRest[1] = 180;
		}else if (argRest[1]<0){
			argRest[1] = 0;
		}
		Blockly.Arduino.setups_['ServoOrigin'+servo] = 'Self_servo'+servo+'.attach(' + servo + ');';
		var code = '';
	    code += '\nang'+servo+' = '+argRest[1]+';\nSelf_servo'+servo+'.write(ang'+servo+');';
		return code ;
	}else if(firstLetter == 's'){//set servo speed
		var argRest = arg.split("s");
		Blockly.Arduino.definitions_['ServoSpeed'+servo] = 'double  ServoSpeed'+servo+' = '+argRest[1]+';\n';
		var code = '';
		return code ; 
	}else if(firstLetter == 'r'){// servo rotate to 
		var argRest = arg.split("r");
		//这里要判断是否有设置舵机速度的块
			
		Blockly.Arduino.definitions_['ServoSpeed'+servo] = 'double  ServoSpeed'+servo+' = 5;';
		var code = '';
		code += 'servoSpeedTurnto(Self_servo'+servo+argRest+',ServoSpeed'+servo+',&ang'+servo+');\n';
		return code;
	}else if(firstLetter == 'c'){// servo increment
		var argRest = arg.split("c");
		Blockly.Arduino.definitions_['ServoSpeed'+servo] = 'double  ServoSpeed'+servo+' = 5;';
		var code = '';
		code += 'servoIncrement(Self_servo'+servo+',&ang'+servo+','+argRest[1]+');\n';
		return code;
	}else if(firstLetter == 'p'){// servo incrementPro
		var argRest = arg.split("p");
		var argIncre = argRest[1].split(":");
		Blockly.Arduino.definitions_['ServoSpeed'+servo] = 'double  ServoSpeed'+servo+' = 5;';
		var code = '';
		code += 'servoIncrementPro(Self_servo'+servo+',&ang'+servo+','+argIncre[0]+','+argIncre[1]+');\n';
		return code;
	}else{
		var code = '';
		return code;
	}
	
		

}



Blockly.Arduino.dance = function () {
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	
	Blockly.Arduino.definitions_['ServoOriginZW_B1'] = 'Servo Self_servoZW_B1;' + '\n' + 'double angZW_B1;';
	Blockly.Arduino.definitions_['ServoOriginZW_B2'] = 'Servo Self_servoZW_B2;' + '\n' + 'double angZW_B2;';
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['dance'] = 'int danceflag = 0;\n';
	
	Blockly.Arduino.setups_['ServoOriginZW_B1'] = 'Self_servoZW_B1.attach(ZW_B1);\n  angZW_B1 = 0;\n  Self_servoZW_B1.write(angZW_B1);';
	Blockly.Arduino.setups_['ServoOriginZW_B2'] = 'Self_servoZW_B2.attach(ZW_B2);\n  angZW_B2 = 0;\n  Self_servoZW_B2.write(angZW_B2);';
	
//	Blockly.Arduino.setups_['dance'] = '  b1ServoPos = initTailPos;\n'+'  B1_servo.attach(B1_SERVO);\n'+'  B1_servo.write(b1ServoPos);\n'+'  b2ServoPos = initTailPos;\n'+'  B2_servo.attach(B2_SERVO);\n'+'  B2_servo.write(b2ServoPos);\n'; 

	
	
	var code0 = 'danceflag = 1;\n';
	var code1 = '\nif(danceflag == 1){\n  dance(Self_servoZW_B1,&angZW_B1,Self_servoZW_B2,&angZW_B2);\n}else if(danceflag == 2){\n  danceStop();\ndanceflag = 0;\n}';
	sessionStorage.setItem('dance_code1',code1);
	
	if(isNeedStrengthen('controls_if_new', 'dance')) { 
		var code = code0;
		sessionStorage.setItem('dance', code1);

	} else {
		var code = code0 + code1;

	}
	return code;
}

Blockly.Arduino.danceStop = function () {
	
	
	
	var code0 = 'danceflag = 2;';
	var code1 = '\nif(danceflag == 1){\n  dance(Self_servoZW_B1,&angZW_B1,Self_servoZW_B2,&angZW_B2);\n}else if(danceflag == 2){\n  danceStop();\ndanceflag = 0;\n}';
	sessionStorage.setItem('dance_code1',code1);
	
	if(isNeedStrengthen('controls_if_new', 'dance')) { 
		var code = code0;
		sessionStorage.setItem('dance', code1);

	} else {
		var code = code0 + code1;

	}
	return code;
}

Blockly.Arduino.pause = function () {
	var pauseNumber = this.getFieldValue('adress');
	Blockly.Arduino.definitions_['intoFlag']  =  '\nint intoFlag = 1;\n'; 
	var code = '\nif(number == '+pauseNumber+' ){\n  myPlayer.pause();\n  delay(100);\n \nintoFlag = 1;\nvolumeflag = 0;\nnumber = 0;}\n';
	return code;
}

Blockly.Arduino.playFileInFolder = function () {
	var pauseNumber = this.getFieldValue('adress');
	
	var code = '\ndummy\n';
	return code;
}


Blockly.Arduino.volume = function () {
	Blockly.Arduino.setups_['volume'] = 'mySoftwareSerial.begin(9600);\n  if (!myPlayer.begin(mySoftwareSerial)) {\n       while(true){ delay(0); } \n  }\n  myPlayer.pause();\n';
	Blockly.Arduino.definitions_['volume'] = '#include   ' + '\<' + 'Arduino.h' + '\>'+'\n'+'#include   ' + '\<' + 'SoftwareSerial.h' + '\>'+'\n'+'#include   ' + '\<' + 'PlayerMini.h' + '\>'+'\nSoftwareSerial mySoftwareSerial(ZW_A1, ZW_A2); \nPlayerMini myPlayer;\nint volumeflag;\nlong timer = 0;\n';
	Blockly.Arduino.definitions_['intoFlag']  =  '\nint intoFlag = 1;\n'; 
	Blockly.Arduino.definitions_['number']  =  '\nint number = 0;\n';
	var numberflag = this.getFieldValue('adress');//myPlayer.play(1);
	var code0 = ' if (millis() - timer > 1000){\n   volumeflag = '+numberflag+';\n   timer = millis();\n};\n'+'\nif(volumeflag != 0 && intoFlag == 1){\n  number = volumeflag;\n  intoFlag=0;\n  myPlayer.loop(volumeflag);\n  volumeflag = 0;\n  delay(200);\n  Rx_Buffer[2]=0;\n  Rx_Buffer[2]=0;\n}\n';
	var code1 = '';
	sessionStorage.setItem('volume_code1',code1);
	
	if(isNeedStrengthen('controls_if_new', 'volume')) { 
		var code = code0;
		sessionStorage.setItem('volume', code1);

	} else {
		var code = code0 + code1;

	}
	return code;
}

Blockly.Arduino.volumeOnlyOnce = function () {
	Blockly.Arduino.setups_['volume'] = 'mySoftwareSerial.begin(9600);\n  if (!myPlayer.begin(mySoftwareSerial)) {\n       while(true){ delay(0); } \n  }\n  myPlayer.pause();\n';
	Blockly.Arduino.definitions_['volume'] = '#include   ' + '\<' + 'Arduino.h' + '\>'+'\n'+'#include   ' + '\<' + 'SoftwareSerial.h' + '\>'+'\n'+'#include   ' + '\<' + 'PlayerMini.h' + '\>'+'\nSoftwareSerial mySoftwareSerial(ZW_A1, ZW_A2); \nPlayerMini myPlayer;\nint volumeflag;\nlong timer = 0;\n';
	var numberflag = this.getFieldValue('adress');//myPlayer.play(1);
	var code = ' if (millis() - timer > 1000){\n   volumeflag = '+numberflag+';\n   timer = millis();\n};\n'+'\nif(volumeflag != 0){\n  myPlayer.play(volumeflag);\n  volumeflag = 0;\n  delay(200);\n  Rx_Buffer[2]=0;\n  Rx_Buffer[2]=0;\n}\n';
	return code;
}

Blockly.Arduino.playFileInFolder = function () {
	Blockly.Arduino.setups_['t5_voice'] = 'mySoftwareSerial.begin(9600);\n  if (!myPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.\n' +
	                                       '    Serial.println(F("Unable to begin:"));\n' + 
	                                       '    Serial.println(F("1.Please recheck the connection!"));\n' + 
	                                       '    Serial.println(F("2.Please insert the SD card!"));\n' + 
	                                       '    while(true){\n' + 
	                                       '      delay(0); // Code to compatible with ESP8266 watch dog.\n' + 
	                                       '    }\n' + 
	                                       '  }\n';
	Blockly.Arduino.definitions_['t5_voice'] = '#include   ' + '\<' + 'Arduino.h' + '\>'+'\n'+'#include   ' + '\<' + 'SoftwareSerial.h' + '\>'+'\n'+'#include   ' + '\<' + 'PlayerMini.h' + '\>'+'\nSoftwareSerial mySoftwareSerial(ZW_A3, ZW_A4); \nPlayerMini myPlayer;\n';
	
	var foldername = Blockly.Arduino.valueToCode(this, 'folderName', Blockly.Arduino.ORDER_ATOMIC);
	var filename   = Blockly.Arduino.valueToCode(this, 'fileName', Blockly.Arduino.ORDER_ATOMIC);
	var code = 'myPlayer.playFolder(' + foldername + ', ' + filename + ');\n';
	return code;
}

Blockly.Arduino.playWeight = function () {
		Blockly.Arduino.setups_['t5_voice'] = 'mySoftwareSerial.begin(9600);\n  if (!myPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.\n' +
	                                       '    Serial.println(F("Unable to begin:"));\n' + 
	                                       '    Serial.println(F("1.Please recheck the connection!"));\n' + 
	                                       '    Serial.println(F("2.Please insert the SD card!"));\n' + 
	                                       '    while(true){\n' + 
	                                       '      delay(0); // Code to compatible with ESP8266 watch dog.\n' + 
	                                       '    }\n' + 
	                                       '  }\n';
	Blockly.Arduino.definitions_['t5_voice'] = '#include   ' + '\<' + 'Arduino.h' + '\>'+'\n'+'#include   ' + '\<' + 'SoftwareSerial.h' + '\>'+'\n'+'#include   ' + '\<' + 'PlayerMini.h' + '\>'+'\nSoftwareSerial mySoftwareSerial(ZW_A3, ZW_A4); \nPlayerMini myPlayer;\n';
	
	var weight = Blockly.Arduino.valueToCode(this, 'WeightVar', Blockly.Arduino.ORDER_ATOMIC);
	var code =  'myPlayer.VoiceWeight(' + weight + ');\n';
	return code;
}

Blockly.Arduino.setVolume = function () {
		Blockly.Arduino.setups_['t5_voice'] = 'mySoftwareSerial.begin(9600);\n  if (!myPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.\n' +
	                                       '    Serial.println(F("Unable to begin:"));\n' + 
	                                       '    Serial.println(F("1.Please recheck the connection!"));\n' + 
	                                       '    Serial.println(F("2.Please insert the SD card!"));\n' + 
	                                       '    while(true){\n' + 
	                                       '      delay(0); // Code to compatible with ESP8266 watch dog.\n' + 
	                                       '    }\n' + 
	                                       '  }\n';
	
	var volVar = Blockly.Arduino.valueToCode(this, 'volumeVar', Blockly.Arduino.ORDER_ATOMIC);
	Blockly.Arduino.setups_['t5_setvolume'] = 'myPlayer.volume(' + volVar + ');  //Set volume value. From 0 to 30\n';
	Blockly.Arduino.definitions_['t5_voice'] = '#include   ' + '\<' + 'Arduino.h' + '\>'+'\n'+'#include   ' + '\<' + 'SoftwareSerial.h' + '\>'+'\n'+'#include   ' + '\<' + 'PlayerMini.h' + '\>'+'\nSoftwareSerial mySoftwareSerial(ZW_A3, ZW_A4); \nPlayerMini myPlayer;\n';
	
	var code = ' ';
	return code;
}



Blockly.Arduino.infrared_sensor = function() {//红外线
	//获取第一个if的value
//	var dropdown_IR = this.getFieldValue('infraredPin');
//	console.log(dropdown_IR);
	Blockly.Arduino.setups_['infrared_sensor'] = 'pinMode(ZW_A3,INPUT);\n  pinMode(ZW_A4,INPUT);';

	var min = this.getFieldValue('infrared_min');
	var max = this.getFieldValue('infrared_max');
	var relation = this.getFieldValue('relation');
	

	var code = 'readInfraredDistance('+min+','+max+','+relation+')';

	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
};



Blockly.Arduino.temperature = function () {
	var setupCode = '';
	setupCode += 'Serial.begin(9600);\n';
	setupCode += ' if (sensors.isParasitePowerMode()) Serial.println("ON");\n';
	setupCode += ' else Serial.println("OFF");\n';
	setupCode += ' if (!sensors.getAddress(insideThermometer, 0)) Serial.println("Unable to find address for Device 0"); \n';
	setupCode += ' sensors.setResolution(insideThermometer, 9);\n\n';
	setupCode += 'if (sensors_2.isParasitePowerMode()) Serial.println("ON");\n';
	setupCode += '  else Serial.println("OFF");\n';
	setupCode += ' if (!sensors_2.getAddress(insideThermometer_2, 0)) Serial.println("Unable to find address for Device 0"); \n';
	setupCode += ' sensors_2.setResolution(insideThermometer_2, 9);\n';
	Blockly.Arduino.setups_['temperature'] = setupCode;
	
	var definitionsCode = '';
	definitionsCode += '#include <OneWire.h>\n';
	definitionsCode += '#include <DallasTemperature.h>\n';
	definitionsCode += 'OneWire oneWire(ZW_A1);\n';
	definitionsCode += 'DallasTemperature sensors(&oneWire);\n';
	definitionsCode += 'OneWire oneWire_2(ZW_A2);\n';
	definitionsCode += 'DallasTemperature sensors_2(&oneWire_2);\n';
	definitionsCode += 'DeviceAddress insideThermometer;\n';
	definitionsCode += 'DeviceAddress insideThermometer_2;\n';
	Blockly.Arduino.definitions_['temperature'] = definitionsCode;
	
	
	
	var min = this.getFieldValue('min');
	var max = this.getFieldValue('max');
	var relation = this.getFieldValue('relation');
	var code = 'getTemperature('+min+','+max+','+relation+')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
}




Blockly.Arduino.custom_lamp = function () {
	var  lampNumber = this.getFieldValue('lampNumber');
	var  lampColor = this.getFieldValue('lampColor');
	var  lampPinNumber = this.getFieldValue('lampPin');
	var  lampPin='';
	if(lampPinNumber == '1'){
		lampPin = 'ZW_B1';
	}else if(lampPinNumber == '2'){
		lampPin = 'ZW_B2';
	}else if(lampPinNumber == '3'){
		lampPin = 'ZW_B3';
	}else if(lampPinNumber == '4'){
		lampPin = 'ZW_B4';
	}
	Blockly.Arduino.setups_['custom_lamp'+lampPin] = 'lampRGB_'+lampPin+'.begin();\n  ' + 'lampRGB_'+lampPin+'.show();\n\n';
	Blockly.Arduino.definitions_['custom_lamp'] = '#include    ' + '\<' + 'Adafruit_NeoPixel.h' + '\>' + '\n' ;
	Blockly.Arduino.definitions_['custom_lamp'+lampPin] = '\n' +'extern Adafruit_NeoPixel lampRGB_'+lampPin+';\n\n'+'Adafruit_NeoPixel lampRGB_'+lampPin+' = Adafruit_NeoPixel('+lampNumber+', '+lampPin+', NEO_RGB + NEO_KHZ800);';
		
	
	var code = 'custom_lamp('+lampNumber+','+lampColor+','+lampPinNumber+');\n';
	return code;
}

Blockly.Arduino.ultrasonic_sensor = function () {
	Blockly.Arduino.setups_['ultrasonic_sensor'] = 'pinAsInput(ZW_A3);\n ';
	var min = this.getFieldValue('min');
	var max = this.getFieldValue('max');
	
	var code = 'getUltrasonic('+min+','+max+')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.wagTheTail = function () {
	
	Blockly.Arduino.setups_['wagTheTail'] ='tailPos = initTailPos;\n'+ '  B1_servo.attach(B1_SERVO);\n  B1_servo.write(tailPos);\n'; 

	Blockly.Arduino.definitions_['wagTheTail'] = '#include' + '\<' + 'Servo.h' + '\>' + '\n' + 'Servo B1_servo;\n\n' + '\n' + 'double tailPos ;\n' ;
	
	var code = 'wagTheTail(B1_servo,&tailPos);\n';
	return code;
}
    
    

Blockly.Arduino.RemoteControlButton = function () {
	
	Blockly.Arduino.setups_['RemoteControlButton'] ='Serial.begin(115200);\n'; 

	Blockly.Arduino.definitions_['RemoteControlButton'] = 'int PS2_Button_Read[6];\n' ;
	
	 var argument0 = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
	
	var buttonID = this.getFieldValue('buttonID');
	var relation = this.getFieldValue('relation');
	var bt = "";
	var re = "";
	switch (buttonID) {
	    	case "1":
			bt = "_ButtonUp";break;
			case "2":
			bt = "_ButtonDown";break;
			case "3":
			bt = "_ButtonLeft";break;
			case "4":
			bt = "_ButtonRight";break;
			case "5":
			bt = "_ButtonTriangle";break;
			case "6":
			bt = "_ButtonCross";break;
			case "7":
			bt = "_ButtonSquare";break;
			case "8":
			bt = "_ButtonCircle";break;
			case "9":
			bt = "_ButtonL1";break;
			case "10":
			bt = "_ButtonL2";break;
			case "11":
			bt = "_ButtonR1";break;
			case "12":
			bt = "_ButtonR2";break;
			case "13":
			bt = "_ButtonStart";break;
			case "14":
			bt = "_ButtonSelect";break;
	}
	switch (relation){
		case "1":
		re = "||";break;
		case "2":
		re = "&&";break;
	}
	var code = bt+re+argument0;
	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
}
    
Blockly.Arduino.RemoteControlButton_t5 = function () {
	
	Blockly.Arduino.setups_['RemoteControlButton'] ='Serial.begin(115200);\n'; 

	Blockly.Arduino.definitions_['RemoteControlButton'] = 'int PS2_Button_Read[6];\n' ;
	
	 var argument0 = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
	
	var buttonID = this.getFieldValue('buttonID');
	var relation = this.getFieldValue('relation');
	var bt = "";
	var re = "";
	switch (buttonID) {
	    	case "1":
			bt = "_ButtonUp";break;
			case "2":
			bt = "_ButtonDown";break;
			case "3":
			bt = "_ButtonLeft";break;
			case "4":
			bt = "_ButtonRight";break;
			case "5":
			bt = "_ButtonTriangle";break;
			case "6":
			bt = "_ButtonCross";break;
			case "7":
			bt = "_ButtonSquare";break;
			case "8":
			bt = "_ButtonCircle";break;
			case "9":
			bt = "_ButtonL1";break;
			case "10":
			bt = "_ButtonL2";break;
			case "11":
			bt = "_ButtonR1";break;
			case "12":
			bt = "_ButtonR2";break;
			case "13":
			bt = "_ButtonStart";break;
			case "14":
			bt = "_ButtonSelect";break;
	}
	switch (relation){
		case "1":
		re = "||";break;
		case "2":
		re = "&&";break;
	}
	var code = bt+re+argument0;
	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
}
    
Blockly.Arduino.RemoteControlButtonLast = function () {
	
	Blockly.Arduino.setups_['RemoteControlButton'] ='Serial.begin(115200);\n'; 

	Blockly.Arduino.definitions_['RemoteControlButton'] = 'int PS2_Button_Read[6];\n' ;
	
	var buttonID = this.getFieldValue('buttonID');
	var bt = "";
	switch (buttonID) {
	    	case "1":
			bt = "_ButtonUp";break;
			case "2":
			bt = "_ButtonDown";break;
			case "3":
			bt = "_ButtonLeft";break;
			case "4":
			bt = "_ButtonRight";break;
			case "5":
			bt = "_ButtonTriangle";break;
			case "6":
			bt = "_ButtonCross";break;
			case "7":
			bt = "_ButtonSquare";break;
			case "8":
			bt = "_ButtonCircle";break;
			case "9":
			bt = "_ButtonL1";break;
			case "10":
			bt = "_ButtonL2";break;
			case "11":
			bt = "_ButtonR1";break;
			case "12":
			bt = "_ButtonR2";break;
			case "13":
			bt = "_ButtonStart";break;
			case "14":
			bt = "_ButtonSelect";break;
			
	}
	var code = bt;
	return [bt, Blockly.Arduino.ORDER_ATOMIC];
	
}    

Blockly.Arduino.RemoteControlButtonLast_t5 = function () {
	
	Blockly.Arduino.setups_['RemoteControlButton'] ='Serial.begin(115200);\n'; 

	Blockly.Arduino.definitions_['RemoteControlButton'] = 'int PS2_Button_Read[6];\n' ;
	
	var buttonID = this.getFieldValue('buttonID');
	var bt = "";
	switch (buttonID) {
	    	case "1":
			bt = "_ButtonUp";break;
			case "2":
			bt = "_ButtonDown";break;
			case "3":
			bt = "_ButtonLeft";break;
			case "4":
			bt = "_ButtonRight";break;
			case "5":
			bt = "_ButtonTriangle";break;
			case "6":
			bt = "_ButtonCross";break;
			case "7":
			bt = "_ButtonSquare";break;
			case "8":
			bt = "_ButtonCircle";break;
			case "9":
			bt = "_ButtonL1";break;
			case "10":
			bt = "_ButtonL2";break;
			case "11":
			bt = "_ButtonR1";break;
			case "12":
			bt = "_ButtonR2";break;
			case "13":
			bt = "_ButtonStart";break;
			case "14":
			bt = "_ButtonSelect";break;
			
	}
	var code = bt;
	return [bt, Blockly.Arduino.ORDER_ATOMIC];
	
}    




Blockly.Arduino.followLine = function () {
	
//var followLineSetups='';
//followLineSetups +="  toneMelody();\n";
//followLineSetups +="  Wire.begin();\n";
//followLineSetups +="  Serial.begin(115200);\n";
//followLineSetups +="  setMaxVal(0x9,2000);\n";
//followLineSetups +="  button.waitForButton();  \n";
//followLineSetups +="  delay(1000);\n";
//followLineSetups +="  if(enable_cal)\n";
//followLineSetups +="  {\n";
//followLineSetups +='     Serial.println("Calibration");\n';
//followLineSetups +="  for(int i = 0; i < 160; i++)\n";
//followLineSetups +="  {\n";
//followLineSetups +="    if ((i > 20 && i <= 60) || (i > 100 && i <= 140))\n";
//followLineSetups +="      motors.setSpeeds(-200, 200);\n";
//followLineSetups +="    else\n";
//followLineSetups +="      motors.setSpeeds(200, -200);   \n";
//followLineSetups +="      calibration();\n";
//followLineSetups +="    delay(8);\n";
//followLineSetups +="  }\n";
//followLineSetups +="  motors.setSpeeds(0,0);\n";
//followLineSetups +='  Serial.println("Calibration result:");\n';
//followLineSetups +="  for(int i = 0; i<2; i++)\n";
//followLineSetups +="  {\n";
//followLineSetups +="    for(int j = 0; j<8; j++)\n";
//followLineSetups +="    {\n";
//followLineSetups +="      setCalData(0x9,j+1,_CAL_MAX_[j],_CAL_MIN_[j]);\n";
//followLineSetups +="      if(i == 0)\n";
//followLineSetups +="      {\n";
//followLineSetups +='      Serial.print("j = ");Serial.print(j);Serial.print(" :");Serial.print(_CAL_MAX_[j]);Serial.print("  :");\n';
//followLineSetups +="      Serial.print(_CAL_MIN_[j]);Serial.println();\n";
//followLineSetups +="      }\n";
//followLineSetups +="    }\n";
//followLineSetups +="}\n";
//followLineSetups +="  }\n";
//followLineSetups +="  else\n";
//followLineSetups +="  {\n";
//followLineSetups +="    for(int i = 0; i<8; i++)\n";
//followLineSetups +="    {\n";
//followLineSetups +="      getCalData(0x09,i+1,&_CAL_MAX_[i],&_CAL_MIN_[i]);\n";
//followLineSetups +="    }\n";
//followLineSetups +="  }\n";
//followLineSetups +=" toneMelody();\n";
//followLineSetups +=" button.waitForButton();  \n";
//followLineSetups +=" toneMelody();\n";
//Blockly.Arduino.setups_['followLine'] =followLineSetups; 



//var followLineDefinitions = '';
//followLineDefinitions +='#include <Wire.h>\n';
//followLineDefinitions +='#include <SoftwareSerial.h>\n';
//followLineDefinitions +='#include "ZeroMotors.h"\n';
//followLineDefinitions +='#include "Pushbutton.h"\n';
//followLineDefinitions +='//#include "ZeroBuzzer.h"\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='//ZeroBuzzer buzzer;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define PWM_L  5     //M2\n';
//followLineDefinitions +='#define PWM_R  6     //M4\n';
//followLineDefinitions +='#define DIR_L  12\n';
//followLineDefinitions +='#define DIR_R  9 \n';
//followLineDefinitions +='/*\n';
//followLineDefinitions +='#define PWM_L  6\n';
//followLineDefinitions +='#define PWM_R  5\n';
//followLineDefinitions +='#define DIR_L  12\n';
//followLineDefinitions +='#define DIR_R  13\n';
//followLineDefinitions +='*/\n';
//followLineDefinitions +='ZeroMotors motors(PWM_L,DIR_L,PWM_R,DIR_R);\n';
//followLineDefinitions +='//ZeroMotors motors();\n';
//followLineDefinitions +='Pushbutton button(ZERO_BUTTON);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define SENSOR_THRESHOLD  200\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define ABOVE_LINE(sensor)   ((sensor) >SENSOR_THRESHOLD)\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define TURN_SPEED  200\n';
//
//followLineDefinitions +='#define _OVERSHOOOT_     (50000/SPEED) \n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// path[] keeps a log of all the turns made\n';
//followLineDefinitions +='// since starting the maze\n';
//followLineDefinitions +='char path[100] = "";\n';
//followLineDefinitions +='unsigned char path_length = 0; // the length of the path\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='const int enable_cal = 1;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// move state and function\n';
//followLineDefinitions +='#define CMD_RESET         0x00\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define CMD_SET_CAL_DATA  0x14\n';
//followLineDefinitions +='#define CMD_SET_EMITTER   0x15\n';
//followLineDefinitions +='#define CMD_SET_MAX_VAL   0x16\n';
//followLineDefinitions +='#define CMD_SET_DEVID     0x17\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define CMD_GET_CAL_DATA        0x24\n';
//followLineDefinitions +='#define CMD_GET_POSITION_DATA        0x26\n';
//followLineDefinitions +='#define CMD_GET_FINAL_DATA      0x27\n';
//followLineDefinitions +='#define CMD_GET_RAW_DATA        0x28\n';
//followLineDefinitions +='#define I2C_DEFAULT_ADDR        0x9\n';
//followLineDefinitions +='#define _slot                   0x0\n';
//followLineDefinitions +='char cmdBuf[18];\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='long _CAL_MAX_[8]={0,0,0,0,0,0,0,0};\n';
//followLineDefinitions +='long _CAL_MIN_[8]={5000,5000,5000,5000,5000,5000,5000,5000};\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='/*************************************************\n';
//followLineDefinitions +=' * Public Constants\n';
//followLineDefinitions +=' *************************************************/\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='#define NOTE_B0  31\n';
//followLineDefinitions +='#define NOTE_C1  33\n';
//followLineDefinitions +='#define NOTE_CS1 35\n';
//followLineDefinitions +='#define NOTE_D1  37\n';
//followLineDefinitions +='#define NOTE_DS1 39\n';
//followLineDefinitions +='#define NOTE_E1  41\n';
//followLineDefinitions +='#define NOTE_F1  44\n';
//followLineDefinitions +='#define NOTE_FS1 46\n';
//followLineDefinitions +='#define NOTE_G1  49\n';
//followLineDefinitions +='#define NOTE_GS1 52\n';
//followLineDefinitions +='#define NOTE_A1  55\n';
//followLineDefinitions +='#define NOTE_AS1 58\n';
//followLineDefinitions +='#define NOTE_B1  62\n';
//followLineDefinitions +='#define NOTE_C2  65\n';
//followLineDefinitions +='#define NOTE_CS2 69\n';
//followLineDefinitions +='#define NOTE_D2  73\n';
//followLineDefinitions +='#define NOTE_DS2 78\n';
//followLineDefinitions +='#define NOTE_E2  82\n';
//followLineDefinitions +='#define NOTE_F2  87\n';
//followLineDefinitions +='#define NOTE_FS2 93\n';
//followLineDefinitions +='#define NOTE_G2  98\n';
//followLineDefinitions +='#define NOTE_GS2 104\n';
//followLineDefinitions +='#define NOTE_A2  110\n';
//followLineDefinitions +='#define NOTE_AS2 117\n';
//followLineDefinitions +='#define NOTE_B2  123\n';
//followLineDefinitions +='#define NOTE_C3  131\n';
//followLineDefinitions +='#define NOTE_CS3 139\n';
//followLineDefinitions +='#define NOTE_D3  147\n';
//followLineDefinitions +='#define NOTE_DS3 156\n';
//followLineDefinitions +='#define NOTE_E3  165\n';
//followLineDefinitions +='#define NOTE_F3  175\n';
//followLineDefinitions +='#define NOTE_FS3 185\n';
//followLineDefinitions +='#define NOTE_G3  196\n';
//followLineDefinitions +='#define NOTE_GS3 208\n';
//followLineDefinitions +='#define NOTE_A3  220\n';
//followLineDefinitions +='#define NOTE_AS3 233\n';
//followLineDefinitions +='#define NOTE_B3  247\n';
//followLineDefinitions +='#define NOTE_C4  262\n';
//followLineDefinitions +='#define NOTE_CS4 277\n';
//followLineDefinitions +='#define NOTE_D4  294\n';
//followLineDefinitions +='#define NOTE_DS4 311\n';
//followLineDefinitions +='#define NOTE_E4  330\n';
//followLineDefinitions +='#define NOTE_F4  349\n';
//followLineDefinitions +='#define NOTE_FS4 370\n';
//followLineDefinitions +='#define NOTE_G4  392\n';
//followLineDefinitions +='#define NOTE_GS4 415\n';
//followLineDefinitions +='#define NOTE_A4  440\n';
//followLineDefinitions +='#define NOTE_AS4 466\n';
//followLineDefinitions +='#define NOTE_B4  494\n';
//followLineDefinitions +='#define NOTE_C5  523\n';
//followLineDefinitions +='#define NOTE_CS5 554\n';
//followLineDefinitions +='#define NOTE_D5  587\n';
//followLineDefinitions +='#define NOTE_DS5 622\n';
//followLineDefinitions +='#define NOTE_E5  659\n';
//followLineDefinitions +='#define NOTE_F5  698\n';
//followLineDefinitions +='#define NOTE_FS5 740\n';
//followLineDefinitions +='#define NOTE_G5  784\n';
//followLineDefinitions +='#define NOTE_GS5 831\n';
//followLineDefinitions +='#define NOTE_A5  880\n';
//followLineDefinitions +='#define NOTE_AS5 932\n';
//followLineDefinitions +='#define NOTE_B5  988\n';
//followLineDefinitions +='#define NOTE_C6  1047\n';
//followLineDefinitions +='#define NOTE_CS6 1109\n';
//followLineDefinitions +='#define NOTE_D6  1175\n';
//followLineDefinitions +='#define NOTE_DS6 1245\n';
//followLineDefinitions +='#define NOTE_E6  1319\n';
//followLineDefinitions +='#define NOTE_F6  1397\n';
//followLineDefinitions +='#define NOTE_FS6 1480\n';
//followLineDefinitions +='#define NOTE_G6  1568\n';
//followLineDefinitions +='#define NOTE_GS6 1661\n';
//followLineDefinitions +='#define NOTE_A6  1760\n';
//followLineDefinitions +='#define NOTE_AS6 1865\n';
//followLineDefinitions +='#define NOTE_B6  1976\n';
//followLineDefinitions +='#define NOTE_C7  2093\n';
//followLineDefinitions +='#define NOTE_CS7 2217\n';
//followLineDefinitions +='#define NOTE_D7  2349\n';
//followLineDefinitions +='#define NOTE_DS7 2489\n';
//followLineDefinitions +='#define NOTE_E7  2637\n';
//followLineDefinitions +='#define NOTE_F7  2794\n';
//followLineDefinitions +='#define NOTE_FS7 2960\n';
//followLineDefinitions +='#define NOTE_G7  3136\n';
//followLineDefinitions +='#define NOTE_GS7 3322\n';
//followLineDefinitions +='#define NOTE_A7  3520\n';
//followLineDefinitions +='#define NOTE_AS7 3729\n';
//followLineDefinitions +='#define NOTE_B7  3951\n';
//followLineDefinitions +='#define NOTE_C8  4186\n';
//followLineDefinitions +='#define NOTE_CS8 4435\n';
//followLineDefinitions +='#define NOTE_D8  4699\n';
//followLineDefinitions +='#define NOTE_DS8 4978\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// notes in the melody:\n';
//followLineDefinitions +='int melody[] = {\n';
//followLineDefinitions +='  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4\n';
//followLineDefinitions +='};\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// note durations: 4 = quarter note, 8 = eighth note, etc.:\n';
//followLineDefinitions +='int noteDurations[] = {\n';
//followLineDefinitions +='  4, 8, 8, 4, 4, 4, 4, 4\n';
//followLineDefinitions +='};\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void toneMelody();\n';
//followLineDefinitions +='void goToFinishLine();\n';
//followLineDefinitions +='void simplifyPath();\n';
//followLineDefinitions +='void solveMaze();\n';
//followLineDefinitions +='void followSegment();\n';
//followLineDefinitions +='char selectTurn(unsigned char found_left, unsigned char found_straight,\n';
//followLineDefinitions +='  unsigned char found_right);\n';
//followLineDefinitions +='  void turn(char dir);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='/**\n';
//followLineDefinitions +=' * \par Function\n';
//followLineDefinitions +=' *    sendCmd\n';
//followLineDefinitions +=' * \par Description\n';
//followLineDefinitions +=' *    Send command to Motor.\n';
//followLineDefinitions +=' * \param[in]\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Output\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Return\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Others\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' */\n';
//followLineDefinitions +='void sendCmd(uint8_t address)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  for(int i=0;i<18;i++)\n';
//followLineDefinitions +='    Wire.write(cmdBuf[i]);\n';
//followLineDefinitions +='  Wire.endTransmission();\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='/**\n';
//followLineDefinitions +=' * \par Function\n';
//followLineDefinitions +=' *    reset\n';
//followLineDefinitions +=' * \par Description\n';
//followLineDefinitions +=' *    Reset the parameter of Motor.\n';
//followLineDefinitions +=' * \par Output\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Return\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Others\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' */\n';
//followLineDefinitions +='void reset(uint8_t address)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = _slot;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_RESET;\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='  delay(2);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='/**\n';
//followLineDefinitions +=' * \par Function\n';
//followLineDefinitions +=' *    setDevid\n';
//followLineDefinitions +=' * \par Description\n';
//followLineDefinitions +=' *    Set the devid to Motor.\n';
//followLineDefinitions +=' * \param[in]\n';
//followLineDefinitions +=' *    devid - the I2C adress\n';
//followLineDefinitions +=' * \par Output\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Return\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' * \par Others\n';
//followLineDefinitions +=' *    None\n';
//followLineDefinitions +=' */\n';
//followLineDefinitions +='void setDevid(uint8_t address,uint8_t devid)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = _slot;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_SET_DEVID;\n';
//followLineDefinitions +='  cmdBuf[2] = devid;\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void setEmitterOn(uint8_t address)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = _slot;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_SET_EMITTER;\n';
//followLineDefinitions +='  cmdBuf[2] = 0x1;\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void setEmitterOff(uint8_t address)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = _slot;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_SET_EMITTER;\n';
//followLineDefinitions +='  cmdBuf[2] = 0x1;\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='  \n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void setMaxVal(uint8_t address,long max_val)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = _slot;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_SET_MAX_VAL;\n';
//followLineDefinitions +='  memcpy(cmdBuf+2,&max_val,4);\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='  \n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void setCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  cmdBuf[0] = sensor_id;\n';
//followLineDefinitions +='  cmdBuf[1] = CMD_SET_CAL_DATA;\n';
//followLineDefinitions +='  memcpy(cmdBuf+2,&max_val,4);\n';
//followLineDefinitions +='  memcpy(cmdBuf+6,&min_val,4);\n';
//followLineDefinitions +='  sendCmd(address);\n';
//followLineDefinitions +='  delay(10);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='   char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(sensor_id);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_CAL_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)8);\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *max_val = *(long*)buf;\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *min_val = *(long*)buf;\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getRawData(uint8_t address,long *d)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(_slot);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  for(int j = 0;j<8;j++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *(d+j) = *(long*)buf;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='   Serial.print( *(d+j));\n';
//followLineDefinitions +='    Serial.print(" ");\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  Serial.println();\n';
//followLineDefinitions +=' // delayMicroseconds(1000);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getFinalData(uint8_t address,long *d)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(_slot);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_FINAL_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  for(int j = 0;j<8;j++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *(d+j) = *(long*)buf;\n';
//followLineDefinitions +='   Serial.print( *(d+j));\n';
//followLineDefinitions +='    Serial.print(" ");\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  Serial.println();\n';
//followLineDefinitions +='  //delayMicroseconds(1500);\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getPosition(uint8_t address,long *data)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(_slot);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_POSITION_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *data = *(long*)buf;\n';
//followLineDefinitions +='  \n';
//followLineDefinitions +='}\n';
//followLineDefinitions +=' \n';
//followLineDefinitions +='/*\n';
//followLineDefinitions +='void getRawData(uint8_t address,long * d1, long * d2, long * d3 , long *d4, long *d5,long *d6, long *d7, long *d8)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(_slot);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d1 = *(long*)buf;\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d2 = *(long*)buf;\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d3 = *(long*)buf;\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d4 = *(long*)buf;\n';
//followLineDefinitions +='    for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d5 = *(long*)buf;\n';
//followLineDefinitions +='    for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d6 = *(long*)buf;\n';
//followLineDefinitions +='   for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d7 = *(long*)buf;\n';
//followLineDefinitions +='    for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *d8 = *(long*)buf;\n';
//followLineDefinitions +='  \n';
//followLineDefinitions +=' // return raw_value;\n';
//followLineDefinitions +='}*/\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getRawData(uint8_t address,uint8_t sensor_id,long * dValue)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(sensor_id);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *dValue = *(long*)buf;\n';
//followLineDefinitions +='    \n';
//followLineDefinitions +=' // return raw_value;\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void getFinalData(uint8_t address,uint8_t sensor_id,long * dValue)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long raw_value;\n';
//followLineDefinitions +='  char buf[8];\n';
//followLineDefinitions +='  Wire.beginTransmission(address);\n';
//followLineDefinitions +='  Wire.write(sensor_id);\n';
//followLineDefinitions +='  Wire.write(CMD_GET_FINAL_DATA);\n';
//followLineDefinitions +='  Wire.endTransmission(0);\n';
//followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
//followLineDefinitions +='  for(int i=0;i<4;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    buf[i] = Wire.read();\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='  *dValue = *(long*)buf;\n';
//followLineDefinitions +='    \n';
//followLineDefinitions +=' // return raw_value;\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void calibration()\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='     long sensor_raw_data[8];  \n';
//followLineDefinitions +='     getRawData(0x9,sensor_raw_data);\n';
//followLineDefinitions +='     for(int i = 0; i<8; i++)\n';
//followLineDefinitions +='     {\n';
//followLineDefinitions +='        if(_CAL_MAX_[i]< sensor_raw_data[i]) _CAL_MAX_[i] = sensor_raw_data[i];\n';
//followLineDefinitions +='        if(_CAL_MIN_[i]> sensor_raw_data[i]) _CAL_MIN_[i] = sensor_raw_data[i];\n';
//followLineDefinitions +='        \n';
//followLineDefinitions +='   \n';
//followLineDefinitions +='      }\n';
//followLineDefinitions +='    //  Serial.println();\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void turn(char dir)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  unsigned short count = 0;\n';
//followLineDefinitions +='  unsigned short last_status = 0;\n';
//followLineDefinitions +='  long  sensors[8];\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  switch(dir)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +="    case 'L':\n";
//followLineDefinitions +="    case 'B':\n";
//followLineDefinitions +='      motors.setSpeeds(-TURN_SPEED,TURN_SPEED);\n';
//followLineDefinitions +='      while(count<2)\n';
//followLineDefinitions +='      {\n';
//followLineDefinitions +='        getFinalData(0x9,sensors);\n';
//followLineDefinitions +='        count += ABOVE_LINE(sensors[2])^last_status;\n';
//followLineDefinitions +='        last_status = ABOVE_LINE(sensors[2]);\n';
//followLineDefinitions +='        \n';
//followLineDefinitions +='      }  \n';
//followLineDefinitions +='    break;\n';
//followLineDefinitions +="    case 'R':\n";
//followLineDefinitions +='      motors.setSpeeds(TURN_SPEED,-TURN_SPEED);\n';
//followLineDefinitions +='      while(count<2)\n';
//followLineDefinitions +='      {\n';
//followLineDefinitions +='        getFinalData(0x9,sensors);\n';
//followLineDefinitions +='        count += ABOVE_LINE(sensors[6])^last_status;\n';
//followLineDefinitions +='        last_status = ABOVE_LINE(sensors[6]);\n';
//followLineDefinitions +='       }\n';
//followLineDefinitions +='       break;\n';
//followLineDefinitions +="    case 'S':\n";
//followLineDefinitions +='      break; \n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='char selectTurn(unsigned char found_left,unsigned char found_straight,unsigned char found_right)\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='   if(found_left)\n';
//followLineDefinitions +="   return 'L';\n";
//followLineDefinitions +='   else if(found_straight)\n';
//followLineDefinitions +="   return 'S'; \n";
//followLineDefinitions +='   else if(found_right)\n';
//followLineDefinitions +="   return 'R';\n";
//followLineDefinitions +='   else\n';
//followLineDefinitions +="   return 'B';\n";
//followLineDefinitions +=' }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +=' void followSegment()\n';
//followLineDefinitions +=' {\n';
//followLineDefinitions +='    unsigned long position;\n';
//followLineDefinitions +='    long sensors[8];\n';
//followLineDefinitions +='    int offset_from_center;\n';
//followLineDefinitions +='    int power_difference; \n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    while(1)\n';
//followLineDefinitions +='    {\n';
//followLineDefinitions +='       \n';
//followLineDefinitions +='        getFinalData(0x9,sensors);\n';
//followLineDefinitions +='        getPosition(0x9,&position);\n';
//followLineDefinitions +='        offset_from_center = ((int)position) - 3500;\n';
//followLineDefinitions +='        power_difference = offset_from_center/2;\n';
//followLineDefinitions +='        if(power_difference > SPEED)\n';
//followLineDefinitions +='          power_difference = SPEED;\n';
//followLineDefinitions +='        if(power_difference < -SPEED)\n';
//followLineDefinitions +='          power_difference = -SPEED;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        if(power_difference < 0)\n';
//followLineDefinitions +='            motors.setSpeeds(SPEED + power_difference, SPEED);\n';
//followLineDefinitions +='        else\n';
//followLineDefinitions +='            motors.setSpeeds(SPEED, SPEED - power_difference);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5])&& !ABOVE_LINE(sensors[6])&& !ABOVE_LINE(sensors[7]))\n';
//followLineDefinitions +='        {\n';
//followLineDefinitions +='      // intersection.  Must be a dead end.\n';
//followLineDefinitions +='            return;\n';
//followLineDefinitions +='        }\n';
//followLineDefinitions +='         else if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[7]))\n';
//followLineDefinitions +='        {\n';
//followLineDefinitions +='          // Found an intersection.\n';
//followLineDefinitions +='          return;\n';
//followLineDefinitions +='        }\n';
//followLineDefinitions +='     }\n';
//followLineDefinitions +=' \n';
//followLineDefinitions +=' }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void solveMaze()\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  while(1)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    followSegment();\n';
//followLineDefinitions +='    unsigned char found_left = 0;\n';
//followLineDefinitions +='    unsigned char found_straight = 0;\n';
//followLineDefinitions +='    unsigned char found_right = 0;\n';
//followLineDefinitions +='    long sensors[8];\n';
//followLineDefinitions +='    \n';
//followLineDefinitions +='    getFinalData(0x9,sensors);\n';
//followLineDefinitions +='    \n';
//followLineDefinitions +=' // if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[1]) )\n';
//followLineDefinitions +='  if(ABOVE_LINE(sensors[0]) )\n';
//followLineDefinitions +='    found_left = 1;\n';
//followLineDefinitions +='    //if(ABOVE_LINE(sensors[6]) ||ABOVE_LINE(sensors[7]))\n';
//followLineDefinitions +='     if(ABOVE_LINE(sensors[7]))\n';
//followLineDefinitions +='    found_right = 1;\n';
//followLineDefinitions +='    motors.setSpeeds(SPEED,SPEED);\n';
//followLineDefinitions +='    delay(_OVERSHOOOT_);\n';
//followLineDefinitions +='    getFinalData(0x9,sensors);\n';
//followLineDefinitions +='    if(ABOVE_LINE(sensors[0])  )\n';
//followLineDefinitions +='    found_left = 1;\n';
//followLineDefinitions +='    if(ABOVE_LINE(sensors[6]) )\n';
//followLineDefinitions +='    found_right = 1;\n';
//followLineDefinitions +='   \n';
//followLineDefinitions +='   delay(_OVERSHOOOT_);\n';
//followLineDefinitions +='   getFinalData(0x9,sensors);\n';
//followLineDefinitions +='     if(ABOVE_LINE(sensors[0]) )\n';
//followLineDefinitions +='    found_left = 1;\n';
//followLineDefinitions +='    if(ABOVE_LINE(sensors[6]))\n';
//followLineDefinitions +='    found_right = 1;\n';
//followLineDefinitions +='   \n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) || ABOVE_LINE(sensors[3]) || ABOVE_LINE(sensors[4]) || ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))\n';
//followLineDefinitions +='            found_straight = 1;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) && ABOVE_LINE(sensors[3]) && ABOVE_LINE(sensors[4]) && ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))\n';
//followLineDefinitions +='        {\n';
//followLineDefinitions +='          motors.setSpeeds(0,0);\n';
//followLineDefinitions +='          break;\n';
//followLineDefinitions +='        }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        // Intersection identification is complete.\n';
//followLineDefinitions +='        unsigned char dir = selectTurn(found_left, found_straight, found_right);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        // Make the turn indicated by the path.\n';
//followLineDefinitions +='    turn(dir);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        // Store the intersection in the path variable.\n';
//followLineDefinitions +='        path[path_length] = dir;\n';
//followLineDefinitions +='        //Terminal.print(path_length);Terminal.print(" ");\n';
//followLineDefinitions +='        //Terminal.println(dir);\n';
//followLineDefinitions +='        path_length++;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        // You should check to make sure that the path_length does not\n';
//followLineDefinitions +='        // example.\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='        // Simplify the learned path.\n';
//followLineDefinitions +='        simplifyPath();\n';
//followLineDefinitions +='     }\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// Now enter an infinite loop - we can re-run the maze as many\n';
//followLineDefinitions +='// times as we want to.\n';
//followLineDefinitions +='void goToFinishLine()\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  long sensors[8];\n';
//followLineDefinitions +='  int i = 0;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // Turn around if the Zumo is facing the wrong direction.\n';
//followLineDefinitions +="  if(path[0] == 'B')\n";
//followLineDefinitions +='  {\n';
//followLineDefinitions +="    turn('B');\n";
//followLineDefinitions +='    i++;\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  for(;i<path_length;i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    followSegment();\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    // Drive through the intersection.\n';
//followLineDefinitions +='    motors.setSpeeds(SPEED, SPEED);\n';
//followLineDefinitions +='    delay(_OVERSHOOOT_);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    // Make a turn according to the instruction stored in\n';
//followLineDefinitions +='    // path[i].\n';
//followLineDefinitions +='    turn(path[i]);\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // Follow the last segment up to the finish.\n';
//followLineDefinitions +='  followSegment();\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // The finish line has been reached.\n';
//followLineDefinitions +='  // Return and wait for another button push to\n';
//followLineDefinitions +='  // restart the maze.\n';
//followLineDefinitions +='    \n';
//followLineDefinitions +='  getFinalData(0x9,sensors);\n';
//followLineDefinitions +='  motors.setSpeeds(0,0);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  return;\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='// simplifyPath analyzes the path[] array and reduces all the\n';
//followLineDefinitions +='// turns. For example: Right turn + Right turn = (1) Back turn.\n';
//followLineDefinitions +='void simplifyPath()\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='\n';
//followLineDefinitions +="  // only simplify the path if the second-to-last turn was a 'B'\n";
//followLineDefinitions +="  if(path_length < 3 || path[path_length - 2] != 'B')\n";
//followLineDefinitions +='  return;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  int total_angle = 0;\n';
//followLineDefinitions +='  int i;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  for(i = 1; i <= 3; i++)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    switch(path[path_length - i])\n';
//followLineDefinitions +='    {\n';
//followLineDefinitions +="      case 'R':\n";
//followLineDefinitions +='        total_angle += 90;\n';
//followLineDefinitions +='        break;\n';
//followLineDefinitions +="      case 'L':\n";
//followLineDefinitions +='        total_angle += 270;\n';
//followLineDefinitions +='        break;\n';
//followLineDefinitions +="      case 'B':\n";
//followLineDefinitions +='        total_angle += 180;\n';
//followLineDefinitions +='        break;\n';
//followLineDefinitions +='    }\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // Get the angle as a number between 0 and 360 degrees.\n';
//followLineDefinitions +='  total_angle = total_angle % 360;\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // Replace all of those turns with a single one.\n';
//followLineDefinitions +='  switch(total_angle)\n';
//followLineDefinitions +='  {\n';
//followLineDefinitions +='    case 0:\n';
//followLineDefinitions +="      path[path_length - 3] = 'S';\n";
//followLineDefinitions +='      break;\n';
//followLineDefinitions +='    case 90:\n';
//followLineDefinitions +="      path[path_length - 3] = 'R';\n";
//followLineDefinitions +='      break;\n';
//followLineDefinitions +='    case 180:\n';
//followLineDefinitions +="      path[path_length - 3] = 'B';\n";
//followLineDefinitions +='      break;\n';
//followLineDefinitions +='    case 270:\n';
//followLineDefinitions +="      path[path_length - 3] = 'L';\n";
//followLineDefinitions +='      break;\n';
//followLineDefinitions +='  }\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='  // The path is now two steps shorter.\n';
//followLineDefinitions +='  path_length -= 2;\n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='void toneMelody()\n';
//followLineDefinitions +='{\n';
//followLineDefinitions +='  for (int thisNote = 0; thisNote < 8; thisNote++) {\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    // to calculate the note duration, take one second divided by the note type.\n';
//followLineDefinitions +='    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.\n';
//followLineDefinitions +='    int noteDuration = 1000 / noteDurations[thisNote];\n';
//followLineDefinitions +='    tone(8, melody[thisNote], noteDuration);\n';
//followLineDefinitions +='\n';
//followLineDefinitions +='    // to distinguish the notes, set a minimum time between them.\n';
//followLineDefinitions +='    int pauseBetweenNotes = noteDuration * 1.30;\n';
//followLineDefinitions +='    delay(pauseBetweenNotes);\n';
//followLineDefinitions +='    // stop the tone playing:\n';
//followLineDefinitions +='    noTone(8);\n';
//followLineDefinitions +='  }  \n';
//followLineDefinitions +='}\n';
//followLineDefinitions +='\n';
//
//Blockly.Arduino.definitions_['followLine'] = followLineDefinitions ;
	
	var code = '';
	return code;
}
    

Blockly.Arduino.control_condition = function () {
	var code = '1';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
}

Blockly.Arduino.followLine_speed = function () {
	
	var speed = this.getFieldValue("speed");
	
	
	var followLineDefinitions = '';
followLineDefinitions +='#include <Wire.h>\n';
followLineDefinitions +='#include <SoftwareSerial.h>\n';
followLineDefinitions +='#include "ZeroMotors.h"\n';
followLineDefinitions +='#include "Pushbutton.h"\n';
followLineDefinitions +='//#include "ZeroBuzzer.h"\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='//ZeroBuzzer buzzer;\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define PWM_L  5     //M2\n';
followLineDefinitions +='#define PWM_R  6     //M4\n';
followLineDefinitions +='#define DIR_L  12\n';
followLineDefinitions +='#define DIR_R  9 \n';
followLineDefinitions +='/*\n';
followLineDefinitions +='#define PWM_L  6\n';
followLineDefinitions +='#define PWM_R  5\n';
followLineDefinitions +='#define DIR_L  12\n';
followLineDefinitions +='#define DIR_R  13\n';
followLineDefinitions +='*/\n';
followLineDefinitions +='ZeroMotors motors(PWM_L,DIR_L,PWM_R,DIR_R);\n';
followLineDefinitions +='//ZeroMotors motors();\n';
followLineDefinitions +='Pushbutton button(ZERO_BUTTON);\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define SENSOR_THRESHOLD  200\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define ABOVE_LINE(sensor)   ((sensor) >SENSOR_THRESHOLD)\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define TURN_SPEED  200\n';
followLineDefinitions +='#define SPEED       '+speed+'\n';
followLineDefinitions +='#define _OVERSHOOOT_     100 //(50000/SPEED) \n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='// path[] keeps a log of all the turns made\n';
followLineDefinitions +='// since starting the maze\n';
followLineDefinitions +='char path[100] = "";\n';
followLineDefinitions +='unsigned char path_length = 0; // the length of the path\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='const int enable_cal = 1;\n';
followLineDefinitions +='\n';
followLineDefinitions +='// move state and function\n';
followLineDefinitions +='#define CMD_RESET         0x00\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define CMD_SET_CAL_DATA  0x14\n';
followLineDefinitions +='#define CMD_SET_EMITTER   0x15\n';
followLineDefinitions +='#define CMD_SET_MAX_VAL   0x16\n';
followLineDefinitions +='#define CMD_SET_DEVID     0x17\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define CMD_GET_CAL_DATA        0x24\n';
followLineDefinitions +='#define CMD_GET_POSITION_DATA        0x26\n';
followLineDefinitions +='#define CMD_GET_FINAL_DATA      0x27\n';
followLineDefinitions +='#define CMD_GET_RAW_DATA        0x28\n';
followLineDefinitions +='#define I2C_DEFAULT_ADDR        0x9\n';
followLineDefinitions +='#define _slot                   0x0\n';
followLineDefinitions +='char cmdBuf[18];\n';
followLineDefinitions +='\n';
followLineDefinitions +='long _CAL_MAX_[8]={0,0,0,0,0,0,0,0};\n';
followLineDefinitions +='long _CAL_MIN_[8]={5000,5000,5000,5000,5000,5000,5000,5000};\n';
followLineDefinitions +='\n';
followLineDefinitions +='/*************************************************\n';
followLineDefinitions +=' * Public Constants\n';
followLineDefinitions +=' *************************************************/\n';
followLineDefinitions +='\n';
followLineDefinitions +='#define NOTE_B0  31\n';
followLineDefinitions +='#define NOTE_C1  33\n';
followLineDefinitions +='#define NOTE_CS1 35\n';
followLineDefinitions +='#define NOTE_D1  37\n';
followLineDefinitions +='#define NOTE_DS1 39\n';
followLineDefinitions +='#define NOTE_E1  41\n';
followLineDefinitions +='#define NOTE_F1  44\n';
followLineDefinitions +='#define NOTE_FS1 46\n';
followLineDefinitions +='#define NOTE_G1  49\n';
followLineDefinitions +='#define NOTE_GS1 52\n';
followLineDefinitions +='#define NOTE_A1  55\n';
followLineDefinitions +='#define NOTE_AS1 58\n';
followLineDefinitions +='#define NOTE_B1  62\n';
followLineDefinitions +='#define NOTE_C2  65\n';
followLineDefinitions +='#define NOTE_CS2 69\n';
followLineDefinitions +='#define NOTE_D2  73\n';
followLineDefinitions +='#define NOTE_DS2 78\n';
followLineDefinitions +='#define NOTE_E2  82\n';
followLineDefinitions +='#define NOTE_F2  87\n';
followLineDefinitions +='#define NOTE_FS2 93\n';
followLineDefinitions +='#define NOTE_G2  98\n';
followLineDefinitions +='#define NOTE_GS2 104\n';
followLineDefinitions +='#define NOTE_A2  110\n';
followLineDefinitions +='#define NOTE_AS2 117\n';
followLineDefinitions +='#define NOTE_B2  123\n';
followLineDefinitions +='#define NOTE_C3  131\n';
followLineDefinitions +='#define NOTE_CS3 139\n';
followLineDefinitions +='#define NOTE_D3  147\n';
followLineDefinitions +='#define NOTE_DS3 156\n';
followLineDefinitions +='#define NOTE_E3  165\n';
followLineDefinitions +='#define NOTE_F3  175\n';
followLineDefinitions +='#define NOTE_FS3 185\n';
followLineDefinitions +='#define NOTE_G3  196\n';
followLineDefinitions +='#define NOTE_GS3 208\n';
followLineDefinitions +='#define NOTE_A3  220\n';
followLineDefinitions +='#define NOTE_AS3 233\n';
followLineDefinitions +='#define NOTE_B3  247\n';
followLineDefinitions +='#define NOTE_C4  262\n';
followLineDefinitions +='#define NOTE_CS4 277\n';
followLineDefinitions +='#define NOTE_D4  294\n';
followLineDefinitions +='#define NOTE_DS4 311\n';
followLineDefinitions +='#define NOTE_E4  330\n';
followLineDefinitions +='#define NOTE_F4  349\n';
followLineDefinitions +='#define NOTE_FS4 370\n';
followLineDefinitions +='#define NOTE_G4  392\n';
followLineDefinitions +='#define NOTE_GS4 415\n';
followLineDefinitions +='#define NOTE_A4  440\n';
followLineDefinitions +='#define NOTE_AS4 466\n';
followLineDefinitions +='#define NOTE_B4  494\n';
followLineDefinitions +='#define NOTE_C5  523\n';
followLineDefinitions +='#define NOTE_CS5 554\n';
followLineDefinitions +='#define NOTE_D5  587\n';
followLineDefinitions +='#define NOTE_DS5 622\n';
followLineDefinitions +='#define NOTE_E5  659\n';
followLineDefinitions +='#define NOTE_F5  698\n';
followLineDefinitions +='#define NOTE_FS5 740\n';
followLineDefinitions +='#define NOTE_G5  784\n';
followLineDefinitions +='#define NOTE_GS5 831\n';
followLineDefinitions +='#define NOTE_A5  880\n';
followLineDefinitions +='#define NOTE_AS5 932\n';
followLineDefinitions +='#define NOTE_B5  988\n';
followLineDefinitions +='#define NOTE_C6  1047\n';
followLineDefinitions +='#define NOTE_CS6 1109\n';
followLineDefinitions +='#define NOTE_D6  1175\n';
followLineDefinitions +='#define NOTE_DS6 1245\n';
followLineDefinitions +='#define NOTE_E6  1319\n';
followLineDefinitions +='#define NOTE_F6  1397\n';
followLineDefinitions +='#define NOTE_FS6 1480\n';
followLineDefinitions +='#define NOTE_G6  1568\n';
followLineDefinitions +='#define NOTE_GS6 1661\n';
followLineDefinitions +='#define NOTE_A6  1760\n';
followLineDefinitions +='#define NOTE_AS6 1865\n';
followLineDefinitions +='#define NOTE_B6  1976\n';
followLineDefinitions +='#define NOTE_C7  2093\n';
followLineDefinitions +='#define NOTE_CS7 2217\n';
followLineDefinitions +='#define NOTE_D7  2349\n';
followLineDefinitions +='#define NOTE_DS7 2489\n';
followLineDefinitions +='#define NOTE_E7  2637\n';
followLineDefinitions +='#define NOTE_F7  2794\n';
followLineDefinitions +='#define NOTE_FS7 2960\n';
followLineDefinitions +='#define NOTE_G7  3136\n';
followLineDefinitions +='#define NOTE_GS7 3322\n';
followLineDefinitions +='#define NOTE_A7  3520\n';
followLineDefinitions +='#define NOTE_AS7 3729\n';
followLineDefinitions +='#define NOTE_B7  3951\n';
followLineDefinitions +='#define NOTE_C8  4186\n';
followLineDefinitions +='#define NOTE_CS8 4435\n';
followLineDefinitions +='#define NOTE_D8  4699\n';
followLineDefinitions +='#define NOTE_DS8 4978\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='// notes in the melody:\n';
followLineDefinitions +='int melody[] = {\n';
followLineDefinitions +='  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4\n';
followLineDefinitions +='};\n';
followLineDefinitions +='\n';
followLineDefinitions +='// note durations: 4 = quarter note, 8 = eighth note, etc.:\n';
followLineDefinitions +='int noteDurations[] = {\n';
followLineDefinitions +='  4, 8, 8, 4, 4, 4, 4, 4\n';
followLineDefinitions +='};\n';
followLineDefinitions +='\n';
followLineDefinitions +='void toneMelody();\n';
followLineDefinitions +='void goToFinishLine();\n';
followLineDefinitions +='void simplifyPath();\n';
followLineDefinitions +='void solveMaze();\n';
followLineDefinitions +='void followSegment();\n';
followLineDefinitions +='char selectTurn(unsigned char found_left, unsigned char found_straight,\n';
followLineDefinitions +='  unsigned char found_right);\n';
followLineDefinitions +='  void turn(char dir);\n';
followLineDefinitions +='\n';
followLineDefinitions +='/**\n';
followLineDefinitions +=' * \par Function\n';
followLineDefinitions +=' *    sendCmd\n';
followLineDefinitions +=' * \par Description\n';
followLineDefinitions +=' *    Send command to Motor.\n';
followLineDefinitions +=' * \param[in]\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Output\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Return\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Others\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' */\n';
followLineDefinitions +='void sendCmd(uint8_t address)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  for(int i=0;i<18;i++)\n';
followLineDefinitions +='    Wire.write(cmdBuf[i]);\n';
followLineDefinitions +='  Wire.endTransmission();\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='/**\n';
followLineDefinitions +=' * \par Function\n';
followLineDefinitions +=' *    reset\n';
followLineDefinitions +=' * \par Description\n';
followLineDefinitions +=' *    Reset the parameter of Motor.\n';
followLineDefinitions +=' * \par Output\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Return\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Others\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' */\n';
followLineDefinitions +='void reset(uint8_t address)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = _slot;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_RESET;\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='  delay(2);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='/**\n';
followLineDefinitions +=' * \par Function\n';
followLineDefinitions +=' *    setDevid\n';
followLineDefinitions +=' * \par Description\n';
followLineDefinitions +=' *    Set the devid to Motor.\n';
followLineDefinitions +=' * \param[in]\n';
followLineDefinitions +=' *    devid - the I2C adress\n';
followLineDefinitions +=' * \par Output\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Return\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' * \par Others\n';
followLineDefinitions +=' *    None\n';
followLineDefinitions +=' */\n';
followLineDefinitions +='void setDevid(uint8_t address,uint8_t devid)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = _slot;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_SET_DEVID;\n';
followLineDefinitions +='  cmdBuf[2] = devid;\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void setEmitterOn(uint8_t address)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = _slot;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_SET_EMITTER;\n';
followLineDefinitions +='  cmdBuf[2] = 0x1;\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void setEmitterOff(uint8_t address)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = _slot;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_SET_EMITTER;\n';
followLineDefinitions +='  cmdBuf[2] = 0x1;\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='  \n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='void setMaxVal(uint8_t address,long max_val)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = _slot;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_SET_MAX_VAL;\n';
followLineDefinitions +='  memcpy(cmdBuf+2,&max_val,4);\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='  \n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void setCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  cmdBuf[0] = sensor_id;\n';
followLineDefinitions +='  cmdBuf[1] = CMD_SET_CAL_DATA;\n';
followLineDefinitions +='  memcpy(cmdBuf+2,&max_val,4);\n';
followLineDefinitions +='  memcpy(cmdBuf+6,&min_val,4);\n';
followLineDefinitions +='  sendCmd(address);\n';
followLineDefinitions +='  delay(10);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getCalData(uint8_t address, uint8_t sensor_id, long * max_val, long * min_val)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='   char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(sensor_id);\n';
followLineDefinitions +='  Wire.write(CMD_GET_CAL_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)8);\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *max_val = *(long*)buf;\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *min_val = *(long*)buf;\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getRawData(uint8_t address,long *d)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(_slot);\n';
followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
followLineDefinitions +='\n';
followLineDefinitions +='  for(int j = 0;j<8;j++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *(d+j) = *(long*)buf;\n';
followLineDefinitions +='\n';
followLineDefinitions +='   Serial.print( *(d+j));\n';
followLineDefinitions +='    Serial.print(" ");\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  Serial.println();\n';
followLineDefinitions +=' // delayMicroseconds(1000);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getFinalData(uint8_t address,long *d)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(_slot);\n';
followLineDefinitions +='  Wire.write(CMD_GET_FINAL_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
followLineDefinitions +='\n';
followLineDefinitions +='  for(int j = 0;j<8;j++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *(d+j) = *(long*)buf;\n';
followLineDefinitions +='   Serial.print( *(d+j));\n';
followLineDefinitions +='    Serial.print(" ");\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  Serial.println();\n';
followLineDefinitions +='  //delayMicroseconds(1500);\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getPosition(uint8_t address,long *data)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(_slot);\n';
followLineDefinitions +='  Wire.write(CMD_GET_POSITION_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
followLineDefinitions +='\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *data = *(long*)buf;\n';
followLineDefinitions +='  \n';
followLineDefinitions +='}\n';
followLineDefinitions +=' \n';
followLineDefinitions +='/*\n';
followLineDefinitions +='void getRawData(uint8_t address,long * d1, long * d2, long * d3 , long *d4, long *d5,long *d6, long *d7, long *d8)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(_slot);\n';
followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)32);\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d1 = *(long*)buf;\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d2 = *(long*)buf;\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d3 = *(long*)buf;\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d4 = *(long*)buf;\n';
followLineDefinitions +='    for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d5 = *(long*)buf;\n';
followLineDefinitions +='    for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d6 = *(long*)buf;\n';
followLineDefinitions +='   for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d7 = *(long*)buf;\n';
followLineDefinitions +='    for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *d8 = *(long*)buf;\n';
followLineDefinitions +='  \n';
followLineDefinitions +=' // return raw_value;\n';
followLineDefinitions +='}*/\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getRawData(uint8_t address,uint8_t sensor_id,long * dValue)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(sensor_id);\n';
followLineDefinitions +='  Wire.write(CMD_GET_RAW_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *dValue = *(long*)buf;\n';
followLineDefinitions +='    \n';
followLineDefinitions +=' // return raw_value;\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='void getFinalData(uint8_t address,uint8_t sensor_id,long * dValue)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long raw_value;\n';
followLineDefinitions +='  char buf[8];\n';
followLineDefinitions +='  Wire.beginTransmission(address);\n';
followLineDefinitions +='  Wire.write(sensor_id);\n';
followLineDefinitions +='  Wire.write(CMD_GET_FINAL_DATA);\n';
followLineDefinitions +='  Wire.endTransmission(0);\n';
followLineDefinitions +='  Wire.requestFrom(address,(uint8_t)4);\n';
followLineDefinitions +='  for(int i=0;i<4;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    buf[i] = Wire.read();\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='  *dValue = *(long*)buf;\n';
followLineDefinitions +='    \n';
followLineDefinitions +=' // return raw_value;\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void calibration()\n';
followLineDefinitions +='{\n';
followLineDefinitions +='     long sensor_raw_data[8];  \n';
followLineDefinitions +='     getRawData(0x9,sensor_raw_data);\n';
followLineDefinitions +='     for(int i = 0; i<8; i++)\n';
followLineDefinitions +='     {\n';
followLineDefinitions +='        if(_CAL_MAX_[i]< sensor_raw_data[i]) _CAL_MAX_[i] = sensor_raw_data[i];\n';
followLineDefinitions +='        if(_CAL_MIN_[i]> sensor_raw_data[i]) _CAL_MIN_[i] = sensor_raw_data[i];\n';
followLineDefinitions +='        \n';
followLineDefinitions +='   \n';
followLineDefinitions +='      }\n';
followLineDefinitions +='    //  Serial.println();\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='void turn(char dir)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  unsigned short count = 0;\n';
followLineDefinitions +='  unsigned short last_status = 0;\n';
followLineDefinitions +='  long  sensors[8];\n';
followLineDefinitions +='  delay(200);\n';
followLineDefinitions +='\n';
followLineDefinitions +='  switch(dir)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +="    case 'L':\n";
followLineDefinitions +="    case 'B':\n";
followLineDefinitions +='      motors.setSpeeds(-TURN_SPEED,TURN_SPEED);\n';
followLineDefinitions +='      while(count<2)\n';
followLineDefinitions +='      {\n';
followLineDefinitions +='        getFinalData(0x9,sensors);\n';
followLineDefinitions +='        count += ABOVE_LINE(sensors[2])^last_status;\n';
followLineDefinitions +='        last_status = ABOVE_LINE(sensors[2]);\n';
followLineDefinitions +='        \n';
followLineDefinitions +='      }  \n';
followLineDefinitions +='    break;\n';
followLineDefinitions +="    case 'R':\n";
followLineDefinitions +='      motors.setSpeeds(TURN_SPEED,-TURN_SPEED);\n';
followLineDefinitions +='      while(count<2)\n';
followLineDefinitions +='      {\n';
followLineDefinitions +='        getFinalData(0x9,sensors);\n';
followLineDefinitions +='        count += ABOVE_LINE(sensors[6])^last_status;\n';
followLineDefinitions +='        last_status = ABOVE_LINE(sensors[6]);\n';
followLineDefinitions +='       }\n';
followLineDefinitions +='       break;\n';
followLineDefinitions +="    case 'S':\n";
followLineDefinitions +='      break; \n';
followLineDefinitions +='  }\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='char selectTurn(unsigned char found_left,unsigned char found_straight,unsigned char found_right)\n';
followLineDefinitions +='{\n';
followLineDefinitions +='   if(found_left)\n';
followLineDefinitions +="   return 'L';\n";
followLineDefinitions +='   else if(found_straight)\n';
followLineDefinitions +="   return 'S'; \n";
followLineDefinitions +='   else if(found_right)\n';
followLineDefinitions +="   return 'R';\n";
followLineDefinitions +='   else\n';
followLineDefinitions +="   return 'B';\n";
followLineDefinitions +=' }\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +=' void followSegment()\n';
followLineDefinitions +=' {\n';
followLineDefinitions +='    unsigned long position;\n';
followLineDefinitions +='    long sensors[8];\n';
followLineDefinitions +='    int offset_from_center;\n';
followLineDefinitions +='    int power_difference; \n';
followLineDefinitions +='\n';
followLineDefinitions +='    while(1)\n';
followLineDefinitions +='    {\n';
followLineDefinitions +='       \n';
followLineDefinitions +='        getFinalData(0x9,sensors);\n';
followLineDefinitions +='        getPosition(0x9,&position);\n';
followLineDefinitions +='        offset_from_center = ((int)position) - 3500;\n';
followLineDefinitions +='        power_difference = offset_from_center/2;\n';
followLineDefinitions +='        if(power_difference > SPEED)\n';
followLineDefinitions +='          power_difference = SPEED;\n';
followLineDefinitions +='        if(power_difference < -SPEED)\n';
followLineDefinitions +='          power_difference = -SPEED;\n';
followLineDefinitions +='\n';
followLineDefinitions +='        if(power_difference < 0)\n';
followLineDefinitions +='            motors.setSpeeds(SPEED + power_difference, SPEED);\n';
followLineDefinitions +='        else\n';
followLineDefinitions +='            motors.setSpeeds(SPEED, SPEED - power_difference);\n';
followLineDefinitions +='\n';
followLineDefinitions +='        if(!ABOVE_LINE(sensors[0]) && !ABOVE_LINE(sensors[1]) && !ABOVE_LINE(sensors[2]) && !ABOVE_LINE(sensors[3]) && !ABOVE_LINE(sensors[4]) && !ABOVE_LINE(sensors[5])&& !ABOVE_LINE(sensors[6])&& !ABOVE_LINE(sensors[7]))\n';
followLineDefinitions +='        {\n';
followLineDefinitions +='      // intersection.  Must be a dead end.\n';
followLineDefinitions +='            return;\n';
followLineDefinitions +='        }\n';
followLineDefinitions +='         else if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[7]))\n';
followLineDefinitions +='        {\n';
followLineDefinitions +='          // Found an intersection.\n';
followLineDefinitions +='          return;\n';
followLineDefinitions +='        }\n';
followLineDefinitions +='     }\n';
followLineDefinitions +=' \n';
followLineDefinitions +=' }\n';
followLineDefinitions +='\n';
followLineDefinitions +='void solveMaze()\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  while(1)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    followSegment();\n';
followLineDefinitions +='    unsigned char found_left = 0;\n';
followLineDefinitions +='    unsigned char found_straight = 0;\n';
followLineDefinitions +='    unsigned char found_right = 0;\n';
followLineDefinitions +='    long sensors[8];\n';
followLineDefinitions +='    \n';
followLineDefinitions +='    getFinalData(0x9,sensors);\n';
followLineDefinitions +='    \n';
followLineDefinitions +=' // if(ABOVE_LINE(sensors[0]) || ABOVE_LINE(sensors[1]) )\n';
followLineDefinitions +='  if(ABOVE_LINE(sensors[0]) )\n';
followLineDefinitions +='    found_left = 1;\n';
followLineDefinitions +='    //if(ABOVE_LINE(sensors[6]) ||ABOVE_LINE(sensors[7]))\n';
followLineDefinitions +='     if(ABOVE_LINE(sensors[7]))\n';
followLineDefinitions +='    found_right = 1;\n';
followLineDefinitions +='    motors.setSpeeds(SPEED,SPEED);\n';
followLineDefinitions +='    delay(_OVERSHOOOT_);\n';
followLineDefinitions +='    getFinalData(0x9,sensors);\n';
followLineDefinitions +='    if(ABOVE_LINE(sensors[0])  )\n';
followLineDefinitions +='    found_left = 1;\n';
followLineDefinitions +='    if(ABOVE_LINE(sensors[6]) )\n';
followLineDefinitions +='    found_right = 1;\n';
followLineDefinitions +='   \n';
followLineDefinitions +='   delay(_OVERSHOOOT_);\n';
followLineDefinitions +='   getFinalData(0x9,sensors);\n';
followLineDefinitions +='     if(ABOVE_LINE(sensors[0]) )\n';
followLineDefinitions +='    found_left = 1;\n';
followLineDefinitions +='    if(ABOVE_LINE(sensors[6]))\n';
followLineDefinitions +='    found_right = 1;\n';
followLineDefinitions +='   \n';
followLineDefinitions +='\n';
followLineDefinitions +='    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) || ABOVE_LINE(sensors[3]) || ABOVE_LINE(sensors[4]) || ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))\n';
followLineDefinitions +='            found_straight = 1;\n';
followLineDefinitions +='\n';
followLineDefinitions +='    if(ABOVE_LINE(sensors[1]) ||ABOVE_LINE(sensors[2]) && ABOVE_LINE(sensors[3]) && ABOVE_LINE(sensors[4]) && ABOVE_LINE(sensors[5])|| ABOVE_LINE(sensors[6]))\n';
followLineDefinitions +='        {\n';
followLineDefinitions +='          motors.setSpeeds(0,0);\n';
followLineDefinitions +='          break;\n';
followLineDefinitions +='        }\n';
followLineDefinitions +='\n';
followLineDefinitions +='        // Intersection identification is complete.\n';
followLineDefinitions +='        unsigned char dir = selectTurn(found_left, found_straight, found_right);\n';
followLineDefinitions +='\n';
followLineDefinitions +='        // Make the turn indicated by the path.\n';
followLineDefinitions +='    turn(dir);\n';
followLineDefinitions +='\n';
followLineDefinitions +='        // Store the intersection in the path variable.\n';
followLineDefinitions +='        path[path_length] = dir;\n';
followLineDefinitions +='        //Terminal.print(path_length);Terminal.print(" ");\n';
followLineDefinitions +='        //Terminal.println(dir);\n';
followLineDefinitions +='        path_length++;\n';
followLineDefinitions +='\n';
followLineDefinitions +='        // You should check to make sure that the path_length does not\n';
followLineDefinitions +='        // example.\n';
followLineDefinitions +='\n';
followLineDefinitions +='        // Simplify the learned path.\n';
followLineDefinitions +='        simplifyPath();\n';
followLineDefinitions +='     }\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='// Now enter an infinite loop - we can re-run the maze as many\n';
followLineDefinitions +='// times as we want to.\n';
followLineDefinitions +='void goToFinishLine()\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  long sensors[8];\n';
followLineDefinitions +='  int i = 0;\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // Turn around if the Zumo is facing the wrong direction.\n';
followLineDefinitions +="  if(path[0] == 'B')\n";
followLineDefinitions +='  {\n';
followLineDefinitions +="    turn('B');\n";
followLineDefinitions +='    i++;\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='\n';
followLineDefinitions +='  for(;i<path_length;i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='\n';
followLineDefinitions +='    followSegment();\n';
followLineDefinitions +='\n';
followLineDefinitions +='    // Drive through the intersection.\n';
followLineDefinitions +='    motors.setSpeeds(SPEED, SPEED);\n';
followLineDefinitions +='    delay(_OVERSHOOOT_);\n';
followLineDefinitions +='\n';
followLineDefinitions +='    // Make a turn according to the instruction stored in\n';
followLineDefinitions +='    // path[i].\n';
followLineDefinitions +='    turn(path[i]);\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // Follow the last segment up to the finish.\n';
followLineDefinitions +='  followSegment();\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // The finish line has been reached.\n';
followLineDefinitions +='  // Return and wait for another button push to\n';
followLineDefinitions +='  // restart the maze.\n';
followLineDefinitions +='    \n';
followLineDefinitions +='  getFinalData(0x9,sensors);\n';
followLineDefinitions +='  motors.setSpeeds(0,0);\n';
followLineDefinitions +='\n';
followLineDefinitions +='  return;\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='\n';
followLineDefinitions +='// simplifyPath analyzes the path[] array and reduces all the\n';
followLineDefinitions +='// turns. For example: Right turn + Right turn = (1) Back turn.\n';
followLineDefinitions +='void simplifyPath()\n';
followLineDefinitions +='{\n';
followLineDefinitions +='\n';
followLineDefinitions +="  // only simplify the path if the second-to-last turn was a 'B'\n";
followLineDefinitions +="  if(path_length < 3 || path[path_length - 2] != 'B')\n";
followLineDefinitions +='  return;\n';
followLineDefinitions +='\n';
followLineDefinitions +='  int total_angle = 0;\n';
followLineDefinitions +='  int i;\n';
followLineDefinitions +='\n';
followLineDefinitions +='  for(i = 1; i <= 3; i++)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    switch(path[path_length - i])\n';
followLineDefinitions +='    {\n';
followLineDefinitions +="      case 'R':\n";
followLineDefinitions +='        total_angle += 90;\n';
followLineDefinitions +='        break;\n';
followLineDefinitions +="      case 'L':\n";
followLineDefinitions +='        total_angle += 270;\n';
followLineDefinitions +='        break;\n';
followLineDefinitions +="      case 'B':\n";
followLineDefinitions +='        total_angle += 180;\n';
followLineDefinitions +='        break;\n';
followLineDefinitions +='    }\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // Get the angle as a number between 0 and 360 degrees.\n';
followLineDefinitions +='  total_angle = total_angle % 360;\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // Replace all of those turns with a single one.\n';
followLineDefinitions +='  switch(total_angle)\n';
followLineDefinitions +='  {\n';
followLineDefinitions +='    case 0:\n';
followLineDefinitions +="      path[path_length - 3] = 'S';\n";
followLineDefinitions +='      break;\n';
followLineDefinitions +='    case 90:\n';
followLineDefinitions +="      path[path_length - 3] = 'R';\n";
followLineDefinitions +='      break;\n';
followLineDefinitions +='    case 180:\n';
followLineDefinitions +="      path[path_length - 3] = 'B';\n";
followLineDefinitions +='      break;\n';
followLineDefinitions +='    case 270:\n';
followLineDefinitions +="      path[path_length - 3] = 'L';\n";
followLineDefinitions +='      break;\n';
followLineDefinitions +='  }\n';
followLineDefinitions +='\n';
followLineDefinitions +='  // The path is now two steps shorter.\n';
followLineDefinitions +='  path_length -= 2;\n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';
followLineDefinitions +='void toneMelody()\n';
followLineDefinitions +='{\n';
followLineDefinitions +='  for (int thisNote = 0; thisNote < 8; thisNote++) {\n';
followLineDefinitions +='\n';
followLineDefinitions +='    // to calculate the note duration, take one second divided by the note type.\n';
followLineDefinitions +='    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.\n';
followLineDefinitions +='    int noteDuration = 1000 / noteDurations[thisNote];\n';
followLineDefinitions +='    tone(8, melody[thisNote], noteDuration);\n';
followLineDefinitions +='\n';
followLineDefinitions +='    // to distinguish the notes, set a minimum time between them.\n';
followLineDefinitions +='    int pauseBetweenNotes = noteDuration * 1.30;\n';
followLineDefinitions +='    delay(pauseBetweenNotes);\n';
followLineDefinitions +='    // stop the tone playing:\n';
followLineDefinitions +='    noTone(8);\n';
followLineDefinitions +='  }  \n';
followLineDefinitions +='}\n';
followLineDefinitions +='\n';

Blockly.Arduino.definitions_['followLine'] = followLineDefinitions ;
	
	return '';
	
}

Blockly.Arduino.followLine_verification = function () {
	
var followLineSetups='';
followLineSetups +="  toneMelody();\n";
followLineSetups +="  Wire.begin();\n";
followLineSetups +="  Serial.begin(115200);\n";
followLineSetups +="  setMaxVal(0x9,2000);\n";
followLineSetups +="  motors.flipM2Motor(1);\n";
followLineSetups +="  button.waitForButton();  \n";
followLineSetups +="  delay(1000);\n";
followLineSetups +="  if(enable_cal)\n";
followLineSetups +="  {\n";
followLineSetups +='     Serial.println("Calibration");\n';
followLineSetups +="  for(int i = 0; i < 160; i++)\n";
followLineSetups +="  {\n";
followLineSetups +="    if ((i > 20 && i <= 60) || (i > 100 && i <= 140))\n";
followLineSetups +="      motors.setSpeeds(-200, 200);\n";
followLineSetups +="    else\n";
followLineSetups +="      motors.setSpeeds(200, -200);   \n";
followLineSetups +="      calibration();\n";
followLineSetups +="    delay(8);\n";
followLineSetups +="  }\n";
followLineSetups +="  motors.setSpeeds(0,0);\n";
followLineSetups +='  Serial.println("Calibration result:");\n';
followLineSetups +="  for(int i = 0; i<2; i++)\n";
followLineSetups +="  {\n";
followLineSetups +="    for(int j = 0; j<8; j++)\n";
followLineSetups +="    {\n";
followLineSetups +="      setCalData(0x9,j+1,_CAL_MAX_[j],_CAL_MIN_[j]);\n";
followLineSetups +="      if(i == 0)\n";
followLineSetups +="      {\n";
followLineSetups +='      Serial.print("j = ");Serial.print(j);Serial.print(" :");Serial.print(_CAL_MAX_[j]);Serial.print("  :");\n';
followLineSetups +="      Serial.print(_CAL_MIN_[j]);Serial.println();\n";
followLineSetups +="      }\n";
followLineSetups +="    }\n";
followLineSetups +="}\n";
followLineSetups +="  }\n";
followLineSetups +="  else\n";
followLineSetups +="  {\n";
followLineSetups +="    for(int i = 0; i<8; i++)\n";
followLineSetups +="    {\n";
followLineSetups +="      getCalData(0x09,i+1,&_CAL_MAX_[i],&_CAL_MIN_[i]);\n";
followLineSetups +="    }\n";
followLineSetups +="  }\n";
followLineSetups +=" toneMelody();\n";
followLineSetups +=" button.waitForButton();  \n";
followLineSetups +=" toneMelody();\n";
Blockly.Arduino.setups_['followLine_verification'] =followLineSetups; 

	
	return '';
	
}

Blockly.Arduino.followLine_traversal = function () {
	var code = 'solveMaze();';
	return code;
	
}

Blockly.Arduino.followLine_finishLine = function () {
	var code = 'button.waitForButton(); goToFinishLine();  toneMelody();';
	return code;
	
}

Blockly.Arduino.infrared_sensor_single = function() {//红外线
	var dropdown_IR = this.getFieldValue('infraredPin');
	Blockly.Arduino.setups_['infrared_sensor_'+dropdown_IR+''] = 'pinMode(' + dropdown_IR + ',INPUT);';

	var code = 'readInfraredDistance_single('+dropdown_IR+')';

	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
};

Blockly.Arduino.delay_t5 = function() {
  var time = this.getFieldValue('delay');
  var unit = this.getFieldValue('unit');
  if(unit == 'm'){
  	time = time*1000;
  }
  var code = 'delay(' + time + ');\n';
  return code;
};

Blockly.Arduino.pressureTransducer = function() {
	
	Blockly.Arduino.setups_['pressureTransducer'] ='Init_Hx711();\n  Serial.begin(9600);\n  delay(3000);\n  Get_Maopi();'; 

	//Blockly.Arduino.definitions_['pressureTransducer'] = '#include "HX711.h" \n' ;
	
	
	var code = 'pressureTransducer()';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
	

	
}

Blockly.Arduino.MotorControlTime = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var dropdown_MotorName = this.getFieldValue('MotorName');
	var MotorStatus = this.getFieldValue('RunningStatus');
	var speedValue = this.getFieldValue('speedValue');
	var timeValue = this.getFieldValue('timeValue');
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'MotorControlTime(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ', ' + timeValue + ');\n';
	return code;
};
Blockly.Arduino.motor_speed_fillings = function() {
	var dropdown_MotorName = this.getFieldValue('MotorName');
	var MotorStatus = this.getFieldValue('RunningStatus');
	var speedValue = Blockly.Arduino.valueToCode(this, 'speed',Blockly.Arduino.ORDER_ATOMIC);
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	Blockly.Arduino.definitions_['motor_changeSpeed'+dropdown_MotorName] =  'double motor'+dropdown_MotorName+';';
	
	if(speedValue < 0) {
		speedValue = 0;
	}
	if(speedValue > 255) {
		speedValue = 255;
	}

	var code = 'motor_speed_fillings(' + dropdown_MotorName + ', ' + MotorStatus + ', ' + speedValue + ');\n';
	return code;
};

Blockly.Arduino.voiceNumber = function() {
	
  var argument0 = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
  var argument1 = this.getFieldValue("pinOne");//busy
  var argument2 = this.getFieldValue("pinSec");//sda
  var busy,sda;
  	if( argument1 == 1 ) {
		busy = 'ZW_A1';
	}else if( argument1 == 2 ){
		busy = 'ZW_A2';
	}else if( argument1 == 3 ){
		busy = 'ZW_A3';
	}else if( argument1 == 4 ){
		busy = 'ZW_A4';
	}
	
	if( argument2 == 1 ) {
		sda = 'ZW_A1';
	}else if( argument2 == 2 ){
		sda = 'ZW_A2';
	}else if( argument2 == 3 ){
		sda = 'ZW_A3';
	}else if( argument2 == 4 ){
		sda = 'ZW_A4';
	}
  
  Blockly.Arduino.setups_['TseriesClass_6'] = 'pinMode('+sda+',OUTPUT);\n  pinMode('+busy+',INPUT);\n  digitalWrite('+sda+',HIGH);';
  return 'VoiceNum(' + argument0 +','+ argument1 + ','+argument2+');\n';
};


Blockly.Arduino.voiceWord = function() {
	
  var argument0 = Blockly.Arduino.valueToCode(this, 'VALUE',
      Blockly.Arduino.ORDER_ASSIGNMENT) || '0';
  var argument1 = this.getFieldValue("pinOne");
  var argument2 = this.getFieldValue("pinSec");
  var busy,sda;
  	if( argument1 == 1 ) {
		busy = 'A0';
	}else if( argument1 == 2 ){
		busy = 'A1';
	}else if( argument1 == 3 ){
		busy = 'A2';
	}else if( argument1 == 4 ){
		busy = 'A3';
	}
	
	if( argument2 == 1 ) {
		sda = 'A0';
	}else if( argument2 == 2 ){
		sda = 'A1';
	}else if( argument2 == 3 ){
		sda = 'A2';
	}else if( argument2 == 4 ){
		sda = 'A3';
	}
  
  Blockly.Arduino.setups_['TseriesClass_6'] = 'pinMode('+sda+',OUTPUT);\n  pinMode('+busy+',INPUT);\n  digitalWrite('+sda+',HIGH);';
  
  return 'VoiceWord(' + argument0 +','+ argument1 + ','+argument2+');\n';
};

Blockly.Arduino.MultipleMotorSet = function() {
	// TODO: Assemble JavaScript into code variable.
	Blockly.Arduino.setups_['movement'] = 'pinMode(MOTOR1P,OUTPUT);\n  pinMode(MOTOR1M,OUTPUT);\n  pinMode(MOTOR2P,OUTPUT);\n  pinMode(MOTOR2M,OUTPUT);\n  pinMode(MOTOR3P,OUTPUT);\n  pinMode(MOTOR3M,OUTPUT);\n  pinMode(MOTOR4P,OUTPUT);\n  pinMode(MOTOR4M,OUTPUT);\n';
	//Blockly.Arduino.definitions_['init_incudes_header'] = 'int PS2_Button_Read[6];';
	var m1Speed = this.getFieldValue('m1Speed');
	var m2Speed = this.getFieldValue('m2Speed');
	var m3Speed = this.getFieldValue('m3Speed');
	var m4Speed = this.getFieldValue('m4Speed');
	var time    = this.getFieldValue('timeValue');
	if(m1Speed < -255) {
		m1Speed = -255;
	}
	if(m1Speed > 255) {
		m1Speed = 255;
	}
	if(m2Speed < -255) {
		m2Speed = -255;
	}
	if(m2Speed > 255) {
		m2Speed = 255;
	}
	if(m3Speed < -255) {
		m3Speed = -255;
	}
	if(m3Speed > 255) {
		m3Speed = 255;
	}
	if(m4Speed < -255) {
		m4Speed = -255;
	}
	if(m4Speed > 255) {
		m4Speed = 255;
	}
	var code = 'MultipleMotorSet(' + m1Speed + ', ' + m2Speed + ', ' + m3Speed + ', ' + m4Speed + ', ' + time + ');\n';
	return code;
};


Blockly.Arduino.MultipleServoSet = function() {
	var b1s = this.getFieldValue('b1s'); 
	if(b1s < 0){
		b1s = 0;
	}
	if(b1s > 10){
		b1s = 10;
	}
	var b1r = this.getFieldValue('b1r');
	if(b1r < 0){
		b1r = 0;
	}
	if(b1r > 180){
		b1r = 180;
	}
	var b2s = this.getFieldValue('b2s'); 
	if(b2s < 0){
		b2s = 0;
	}
	if(b2s > 10){
		b2s = 10;
	}
	var b2r = this.getFieldValue('b2r'); 
	if(b2r < 0){
		b2r = 0;
	}
	if(b2r > 180){
		b2r = 180;
	}
	var b3s = this.getFieldValue('b3s'); 
	if(b3s < 0){
		b3s = 0;
	}
	if(b3s > 10){
		b3s = 10;
	}
	var b3r = this.getFieldValue('b3r'); 
	if(b3r < 0){
		b3r = 0;
	}
	if(b3r > 180){
		b3r = 180;
	}
	var b4s = this.getFieldValue('b4s'); 
	if(b4s < 0){
		b4s = 0;
	}
	if(b4s > 10){
		b4s = 10;
	}
	var b4r = this.getFieldValue('b4r'); 
	if(b4r < 0){
		b4r = 0;
	}
	if(b4r > 180){
		b4r = 180;
	}
	var a1s = this.getFieldValue('a1s'); 
	if(a1s < 0){
		a1s = 0;
	}
	if(a1s > 180){
		a1s = 180;
	}
	var a1r = this.getFieldValue('a1r'); 
	if(a1r < 0){
		a1r = 0;
	}
	if(a1r > 180){
		a1r = 180;
	}
	var a2s = this.getFieldValue('a2s'); 
	if(a2s < 0){
		a2s = 0;
	}
	if(a2s > 180){
		a2s = 180;
	}
	var a2r = this.getFieldValue('a2r'); 
	if(a2r < 0){
		a2r = 0;
	}
	if(a2r > 180){
		a2r = 180;
	}
	var a3s = this.getFieldValue('a3s'); 
	if(a3s < 0){
		a3s = 0;
	}
	if(a3s > 180){
		a3s = 180;
	}
	var a3r = this.getFieldValue('a3r'); 
	if(a3r < 0){
		a3r = 0;
	}
	if(a3r > 180){
		a3r = 180;
	}
	var a4s = this.getFieldValue('a4s'); 
	if(a4s < 0){
		a4s = 0;
	}
	if(a4s > 180){
		a4s = 180;
	}
	var a4r = this.getFieldValue('a4r'); 
	if(a4r < 0){
		a4r = 0;
	}
	if(a4r > 180){
		a4r = 180;
	}
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
		Blockly.Arduino.setups_['ServoOriginZW_B1'] = 'Self_servoZW_B1.attach(ZW_B1); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B1'] = 'Servo Self_servoZW_B1;' + '\n' + 'double angZW_B1;';
		Blockly.Arduino.setups_['ServoOriginZW_B2'] = 'Self_servoZW_B2.attach(ZW_B2); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B2'] = 'Servo Self_servoZW_B2;' + '\n' + 'double angZW_B2;';
		Blockly.Arduino.setups_['ServoOriginZW_B3'] = 'Self_servoZW_B3.attach(ZW_B3); ';
		Blockly.Arduino.definitions_['ServoOriginZW_B3'] = 'Servo Self_servoZW_B3;' + '\n' + 'double angZW_B3;';
		Blockly.Arduino.setups_['ServoOriginZW_B4'] = 'Self_servoZW_B4.attach(ZW_B4); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B4'] = 'Servo Self_servoZW_B4;' + '\n' + 'double angZW_B4;';
		Blockly.Arduino.setups_['ServoOriginZW_A1'] = 'Self_servoZW_A1.attach(ZW_A1); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A1'] = 'Servo Self_servoZW_A1;' + '\n' + 'double angZW_A1;';
		Blockly.Arduino.setups_['ServoOriginZW_A2'] = 'Self_servoZW_A2.attach(ZW_A2); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A2'] = 'Servo Self_servoZW_A2;' + '\n' + 'double angZW_A2;';
		Blockly.Arduino.setups_['ServoOriginZW_A3'] = 'Self_servoZW_A3.attach(ZW_A3); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A3'] = 'Servo Self_servoZW_A3;' + '\n' + 'double angZW_A3;';
		Blockly.Arduino.setups_['ServoOriginZW_A4'] = 'Self_servoZW_A4.attach(ZW_A4); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A4'] = 'Servo Self_servoZW_A4;' + '\n' + 'double angZW_A4;';
	
	var code = 'MultipleServoSet('+b1s+','+b1r+','+b2s+','+b2r+','+b3s+','+b3r+','+b4s+','+b4r+','+a1s+','+a1r+','+a2s+','+a2r+','+a3s+','+a3r+','+a4s+','+a4r+',&angZW_B1,&angZW_B2,&angZW_B3,&angZW_B4,&angZW_A1,&angZW_A2,&angZW_A3,&angZW_A4,Self_servoZW_B1,Self_servoZW_B2,Self_servoZW_B3,Self_servoZW_B4,Self_servoZW_A1,Self_servoZW_A2,Self_servoZW_A3,Self_servoZW_A4);';
	return code;
	
};



Blockly.Arduino.MultipleServoSetPD = function() {
	var b1s = this.getFieldValue('b1s'); 
	if(b1s < 0){
		b1s = 0;
	}
	if(b1s > 10){
		b1s = 10;
	}
	var b1r = this.getFieldValue('b1r');
	if(b1r < 0){
		b1r = 0;
	}
	if(b1r > 180){
		b1r = 180;
	}
	var b2s = this.getFieldValue('b2s'); 
	if(b2s < 0){
		b2s = 0;
	}
	if(b2s > 10){
		b2s = 10;
	}
	var b2r = this.getFieldValue('b2r'); 
	if(b2r < 0){
		b2r = 0;
	}
	if(b2r > 180){
		b2r = 180;
	}
	var b3s = this.getFieldValue('b3s'); 
	if(b3s < 0){
		b3s = 0;
	}
	if(b3s > 10){
		b3s = 10;
	}
	var b3r = this.getFieldValue('b3r'); 
	if(b3r < 0){
		b3r = 0;
	}
	if(b3r > 180){
		b3r = 180;
	}
	var b4s = this.getFieldValue('b4s'); 
	if(b4s < 0){
		b4s = 0;
	}
	if(b4s > 10){
		b4s = 10;
	}
	var b4r = this.getFieldValue('b4r'); 
	if(b4r < 0){
		b4r = 0;
	}
	if(b4r > 180){
		b4r = 180;
	}
	var a1s = this.getFieldValue('a1s'); 
	if(a1s < 0){
		a1s = 0;
	}
	if(a1s > 180){
		a1s = 180;
	}
	var a1r = this.getFieldValue('a1r'); 
	if(a1r < 0){
		a1r = 0;
	}
	if(a1r > 180){
		a1r = 180;
	}
	var a2s = this.getFieldValue('a2s'); 
	if(a2s < 0){
		a2s = 0;
	}
	if(a2s > 180){
		a2s = 180;
	}
	var a2r = this.getFieldValue('a2r'); 
	if(a2r < 0){
		a2r = 0;
	}
	if(a2r > 180){
		a2r = 180;
	}
	var a3s = this.getFieldValue('a3s'); 
	if(a3s < 0){
		a3s = 0;
	}
	if(a3s > 180){
		a3s = 180;
	}
	var a3r = this.getFieldValue('a3r'); 
	if(a3r < 0){
		a3r = 0;
	}
	if(a3r > 180){
		a3r = 180;
	}
	var a4s = this.getFieldValue('a4s'); 
	if(a4s < 0){
		a4s = 0;
	}
	if(a4s > 180){
		a4s = 180;
	}
	var a4r = this.getFieldValue('a4r'); 
	if(a4r < 0){
		a4r = 0;
	}
	if(a4r > 180){
		a4r = 180;
	}
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
		Blockly.Arduino.setups_['ServoOriginZW_B1'] = 'Self_servoZW_B1.attach(ZW_B1); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B1'] = 'Servo Self_servoZW_B1;' + '\n' + 'double angZW_B1;';
		Blockly.Arduino.setups_['ServoOriginZW_B2'] = 'Self_servoZW_B2.attach(ZW_B2); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B2'] = 'Servo Self_servoZW_B2;' + '\n' + 'double angZW_B2;';
		Blockly.Arduino.setups_['ServoOriginZW_B3'] = 'Self_servoZW_B3.attach(ZW_B3); ';
		Blockly.Arduino.definitions_['ServoOriginZW_B3'] = 'Servo Self_servoZW_B3;' + '\n' + 'double angZW_B3;';
		Blockly.Arduino.setups_['ServoOriginZW_B4'] = 'Self_servoZW_B4.attach(ZW_B4); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_B4'] = 'Servo Self_servoZW_B4;' + '\n' + 'double angZW_B4;';
		Blockly.Arduino.setups_['ServoOriginZW_A1'] = 'Self_servoZW_A1.attach(ZW_A1); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A1'] = 'Servo Self_servoZW_A1;' + '\n' + 'double angZW_A1;';
		Blockly.Arduino.setups_['ServoOriginZW_A2'] = 'Self_servoZW_A2.attach(ZW_A2); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A2'] = 'Servo Self_servoZW_A2;' + '\n' + 'double angZW_A2;';
		Blockly.Arduino.setups_['ServoOriginZW_A3'] = 'Self_servoZW_A3.attach(ZW_A3); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A3'] = 'Servo Self_servoZW_A3;' + '\n' + 'double angZW_A3;';
		Blockly.Arduino.setups_['ServoOriginZW_A4'] = 'Self_servoZW_A4.attach(ZW_A4); ';	
		Blockly.Arduino.definitions_['ServoOriginZW_A4'] = 'Servo Self_servoZW_A4;' + '\n' + 'double angZW_A4;';
	
	var code = 'MultipleServoSetPD('+b1s+','+b1r+','+b2s+','+b2r+','+b3s+','+b3r+','+b4s+','+b4r+','+a1s+','+a1r+','+a2s+','+a2r+','+a3s+','+a3r+','+a4s+','+a4r+',&angZW_B1,&angZW_B2,&angZW_B3,&angZW_B4,&angZW_A1,&angZW_A2,&angZW_A3,&angZW_A4,Self_servoZW_B1,Self_servoZW_B2,Self_servoZW_B3,Self_servoZW_B4,Self_servoZW_A1,Self_servoZW_A2,Self_servoZW_A3,Self_servoZW_A4);';
	return code;
	
};

Blockly.Arduino.ultrasonic_sensor_sbt = function () {
	var pin = this.getFieldValue('pin');
	Blockly.Arduino.setups_['ultrasonic_sensor'] = 'pinAsInput('+pin+');\n ';
	if(pin == 'ZW_A1'){
		pin = 1; 
	}else if(pin == 'ZW_A2'){
		pin = 2; 
	}else if(pin == 'ZW_A3'){
		pin = 3; 
	}else if(pin == 'ZW_A4'){
		pin = 4; 
	}
	
	var min = this.getFieldValue('min');
	var max = this.getFieldValue('max');
	
	var code = 'getUltrasonicSBT('+pin+','+min+','+max+')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.ultrasonic_sensor_value_sbt = function () {
	var pin = this.getFieldValue('pin');
	
	Blockly.Arduino.setups_['ultrasonic_sensor'] = 'pinAsInput('+pin+');\n ';
	if(pin == 'ZW_A1'){
		pin = 1; 
	}else if(pin == 'ZW_A2'){
		pin = 2; 
	}else if(pin == 'ZW_A3'){
		pin = 3; 
	}else if(pin == 'ZW_A4'){
		pin = 4; 
	}
	var code = 'returnUltrasonicValueSBT('+pin+')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.infrared_sensor_sbt = function() {//红外线
	//获取第一个if的value
	var dropdown_IR = this.getFieldValue('infraredPin');
	Blockly.Arduino.setups_['infrared_sensor'] = 'pinMode(' + dropdown_IR + ',INPUT);';

	var min = this.getFieldValue('infrared_min');
	var max = this.getFieldValue('infrared_max');
	

	var code = 'readInfraredDistanceSBT('+dropdown_IR+','+min+','+max+')';

	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
};

Blockly.Arduino.infrared_sensor_value_sbt = function() {//红外线
	//获取第一个if的value
	var dropdown_IR = this.getFieldValue('infraredPin');
	var pin='';
	if(dropdown_IR == 1){
		pin = 'ZW_A1';
	}else if(dropdown_IR == 2){
		pin = 'ZW_A2';
	}else if(dropdown_IR == 3){
		pin = 'ZW_A3';
	}else if(dropdown_IR == 4){
		pin = 'ZW_A4';
	}
	Blockly.Arduino.setups_['infrared_sensor'] = 'pinMode(' + pin + ',INPUT);';

	

	var code = 'readInfraredDistanceValueSBT('+dropdown_IR+')';

	return [code, Blockly.Arduino.ORDER_ATOMIC];
	
};

Blockly.Arduino.temperature_sbt = function () {
	var Pin = this.getFieldValue('Pin');
	Blockly.Arduino.definitions_['temperature'] = '#include   ' + '\<' + 'OneWire.h' + '\>'+'\nOneWire  ds('+Pin+');';
	var min = this.getFieldValue('min');
	var max = this.getFieldValue('max');
	
	var code = 'getTemperatureSBT('+min+','+max+')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.temperature_value_sbt = function () {
	var Pin = this.getFieldValue('Pin');
	Blockly.Arduino.definitions_['temperature'] = '#include   ' + '\<' + 'OneWire.h' + '\>'+'\n';
	Blockly.Arduino.definitions_['temperature' + Pin] = 'OneWire  ds_' + Pin + '('+Pin+');';
	
	var code = 'getTemperatureValueSBT(ds_' + Pin +')';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}


Blockly.Arduino.TongChuangAuto = function () {
	var armLowerServo_initPos = this.getFieldValue('armLowerServoInitPos');
	var armLowerServo_catchPos = this.getFieldValue('armLowerServoCatchPos');
	var armHigherServo_initPos = this.getFieldValue('armHigherServoInitPos');
	var armHigherServo_catchPos = this.getFieldValue('armHigherServoCatchPos');
	var handServo_openPos = this.getFieldValue('handServoOpenPos');
	var handServo_closePos = this.getFieldValue('handServoClosePos');
	var headServo_midPos = this.getFieldValue('headServoMidPos');
	var headServo_Range = this.getFieldValue('headServoRange');
	
	var armLowerServo = this.getFieldValue('armLowerServo');
	var armHigherServo = this.getFieldValue('armHigherServo');
	var handServo = this.getFieldValue('handServo');
	var headServo = this.getFieldValue('headServo');
	
	var userDefined_grabTime = this.getFieldValue('userDefined_grabTime');
	
	Blockly.Arduino.definitions_['TongChuangAutoInclude'] = '#include   "automode.h"\n';
	
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['ServoOrigin'+armLowerServo] = 'Servo  Self_servo'+armLowerServo+';' + '\n' + 'double ang'+armLowerServo+';';
	Blockly.Arduino.definitions_['ServoOrigin'+armHigherServo] = 'Servo  Self_servo'+armHigherServo+';' + '\n' + 'double ang'+armHigherServo+';';
	Blockly.Arduino.definitions_['ServoOrigin'+handServo] = 'Servo  Self_servo'+handServo+';' + '\n' + 'double ang'+handServo+';';
	Blockly.Arduino.definitions_['ServoOrigin'+headServo] = 'Servo  Self_servo'+headServo+';' + '\n' + 'double ang'+headServo+';';
	
	Blockly.Arduino.setups_['ServoOrigin'+armLowerServo] = 'Self_servo'+armLowerServo+'.attach(' + armLowerServo + '); ';
	Blockly.Arduino.setups_['ServoOrigin'+armHigherServo] = 'Self_servo'+armHigherServo+'.attach(' + armHigherServo + '); ';
	Blockly.Arduino.setups_['ServoOrigin'+handServo] = 'Self_servo'+handServo+'.attach(' + handServo + '); ';
	Blockly.Arduino.setups_['ServoOrigin'+headServo] = 'Self_servo'+headServo+'.attach(' + headServo + '); ';
	
	Blockly.Arduino.definitions_['TongChuangAutoVar'] = 'int headSweepDirection;\n' + 
	                                                     'extern double  SERVO1_CATCH_POS;\n' + 
	                                                     'extern double  SERVO2_CATCH_POS;\n' +
	                                                     'extern double  SERVO1_INIT_POS;\n' +
	                                                     'extern double  SERVO2_INIT_POS;\n' +
	                                                     'extern double  HANDOPEN_ANG;\n' +
	                                                     'extern double  HANDCLOSE_ANG;\n' +
	                                                     'extern double  HEADSENSOR_MIDDLE_POS;\n' +
	                                                     'extern double  HEADSERVO_RANGE;\n' +
	                                                     'extern double  AUTOGRAB_TIME;\n' +
	                                                     'extern double  AutoModeStartTime;\n';
	
	Blockly.Arduino.setups_['TongChuangAuto'] = 'if (ProgramSelected == 3) {' + '\n' + 
	                                             '   parameterDefinition(' + armLowerServo_initPos  + ',' + armLowerServo_catchPos  + ','
	                                                                       + armHigherServo_initPos + ',' + armHigherServo_catchPos + ','
	                                                                       + handServo_openPos      + ',' + handServo_closePos + ','
	                                                                       + headServo_midPos       + ',' + headServo_Range  + ','
	                                                                       + userDefined_grabTime + ');\n' + 
	                                             '   // Head Servo is:' + headServo + ',  Arm lower Servo is: ' + armLowerServo + ',  Arm higher Servo is: ' + armHigherServo + ',  Hand Servo is: ' + handServo + '\n' +
	                                             '   AutoModeSetup(Self_servo' + headServo + ', Self_servo' + armLowerServo + ', Self_servo' + armHigherServo + ', Self_servo' + handServo + ', &ang' + headServo + ', &ang' + armLowerServo + ', &ang' + armHigherServo + ', &headSweepDirection);\n' + 
	                                             '   AutoModeStartTime = millis();  // record the program start time \n' +
	                                             '  }';
	                                            
	
	var code = 'if (ProgramSelected == 3) {\n' + 
                  'while (1)\n' + 
                  '    autoModeRun(Self_servo' + headServo + ', Self_servo' + armLowerServo + ', Self_servo' + armHigherServo + ', Self_servo' + handServo + ', &ang' + headServo + ', &ang' + armLowerServo + ', &ang' + armHigherServo + ', &headSweepDirection);\n' + 
                  '}\n';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}


Blockly.Arduino.TongChuangAutoMotorClaw = function () {
	var armLowerServo_initPos = this.getFieldValue('armLowerServoInitPos');
	var armLowerServo_catchPos = this.getFieldValue('armLowerServoCatchPos');
	var armHigherServo_initPos = this.getFieldValue('armHigherServoInitPos');
	var armHigherServo_catchPos = this.getFieldValue('armHigherServoCatchPos');
	var headServo_midPos = this.getFieldValue('headServoMidPos');
	var headServo_Range = this.getFieldValue('headServoRange');
	
	var armLowerServo = this.getFieldValue('armLowerServo');
	var armHigherServo = this.getFieldValue('armHigherServo');
	var headServo = this.getFieldValue('headServo');
	
	var userDefined_grabTime = this.getFieldValue('userDefined_grabTime');
	
	Blockly.Arduino.definitions_['TongChuangAutoInclude'] = '#include   "automode.h"\n';
	
	Blockly.Arduino.definitions_['ServoControl'] = '#include   ' + '\<' + 'Servo.h' + '\>';
	Blockly.Arduino.definitions_['ServoOrigin'+armLowerServo] = 'Servo  Self_servo'+armLowerServo+';' + '\n' + 'double ang'+armLowerServo+';';
	Blockly.Arduino.definitions_['ServoOrigin'+armHigherServo] = 'Servo  Self_servo'+armHigherServo+';' + '\n' + 'double ang'+armHigherServo+';';
	Blockly.Arduino.definitions_['ServoOrigin'+headServo] = 'Servo  Self_servo'+headServo+';' + '\n' + 'double ang'+headServo+';';
	
	Blockly.Arduino.setups_['ServoOrigin'+armLowerServo] = 'Self_servo'+armLowerServo+'.attach(' + armLowerServo + '); ';
	Blockly.Arduino.setups_['ServoOrigin'+armHigherServo] = 'Self_servo'+armHigherServo+'.attach(' + armHigherServo + '); ';
	Blockly.Arduino.setups_['ServoOrigin'+headServo] = 'Self_servo'+headServo+'.attach(' + headServo + '); ';
	
	Blockly.Arduino.definitions_['TongChuangAutoMotorClawVar'] = 'int headSweepDirection;\n' + 
	                                                             'extern double  SERVO1_CATCH_POS;\n' + 
	                                                             'extern double  SERVO2_CATCH_POS;\n' +
	                                                             'extern double  SERVO1_INIT_POS;\n' +
	                                                             'extern double  SERVO2_INIT_POS;\n' +
	                                                             'extern double  HEADSENSOR_MIDDLE_POS;\n' +
	                                                             'extern double  HEADSERVO_RANGE;\n' +
	                                                             'extern int     handStatus;\n' +
	                                                             'extern double  AUTOGRAB_TIME;\n' +
	                                                             'extern double  AutoModeStartTime;\n';
	
	Blockly.Arduino.setups_['TongChuangAutoMotorClaw'] = 'if (ProgramSelected == 3) {' + '\n' + 
	                                                     '   parameterDefinition(' + armLowerServo_initPos  + ',' + armLowerServo_catchPos  + ','
	                                                                               + armHigherServo_initPos + ',' + armHigherServo_catchPos + ','
	                                                                               + headServo_midPos       + ',' + headServo_Range  + ','
	                                                                               + userDefined_grabTime + ');\n' + 
	                                                     '   // Head Servo is:' + headServo + ',  Arm lower Servo is: ' + armLowerServo + ',  Arm higher Servo is: ' + armHigherServo + '\n' +
	                                                     '   AutoModeSetup(Self_servo' + headServo + ', Self_servo' + armLowerServo + ', Self_servo' + armHigherServo + ', &ang' + headServo + ', &ang' + armLowerServo + ', &ang' + armHigherServo + ', &headSweepDirection);\n' + 
	                                                     '   AutoModeStartTime = millis();  // record the program start time \n' +
	                                                     '  }';
	                                            
	
	var code = 'if (ProgramSelected == 3) {\n' + 
                  'while (1)\n' + 
                  '    autoModeRun(Self_servo' + headServo + ', Self_servo' + armLowerServo + ', Self_servo' + armHigherServo + ', &ang' + headServo + ', &ang' + armLowerServo + ', &ang' + armHigherServo + ', &headSweepDirection);\n' + 
                  '}\n';
	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.readColorSensor = function () {
	
	Blockly.Arduino.definitions_['colorSensorRead'] = '#include <Wire.h>\n#include "Adafruit_TCS34725.h"\n' + 'uint16_t RGB_r, RGB_g, RGB_b, RGB_c, RGB_colorTemp, RGB_lux;\n' + 'Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);\n' + 'byte gammatable[256];\n';
  Blockly.Arduino.definitions_['include_Adafruit_NeoPixel_Bright'] = 'uint8_t LEDBrightness = 255; //default LEDBrightness is set to 255;\n';
  Blockly.Arduino.setups_['colorSensorRead'] = 'if (tcs.begin()) {\n' +
                                               '    Serial.println("Found sensor");\n' + 
                                               '  } else {\n' +
                                               '    Serial.println("No TCS34725 found ... check your connections");\n' +
                                               '  }\n' +
                                               '  for (int i=0; i<256; i++) {\n' + 
                                               '    float x = i;\n' +
                                               '    x /= 255;\n' +
                                               '    x = pow(x, 2.5);\n' + 
                                               '    x *= 255;\n\n' + 
                                               '    gammatable[i] = x;\n  }\n';
	
	var code = '';
	    code += 'tcs.getRawData(&RGB_r, &RGB_g, &RGB_b, &RGB_c);\n';
	    code += 'RGB_colorTemp = tcs.calculateColorTemperature(RGB_r, RGB_g, RGB_b);\n';
	    code += 'RGB_lux = tcs.calculateLux(RGB_r, RGB_g, RGB_b);\n';
	    code += 'uint32_t sum = RGB_r;\n';
	    code += 'sum += RGB_g;\n';
	    code += 'sum += RGB_b;\n\n';
	    code += 'float r, g, b;\n';
	    code += 'r = RGB_r; r /= sum;\n';
	    code += 'g = RGB_g; g /= sum;\n';
	    code += 'b = RGB_b; b /= sum;\n';
	    code += 'r *= 256; g *= 256; b *= 256;\n';
	    
	    code += 'int RGB_red; int RGB_green; int RGB_blue;\n';
	    code += 'RGB_red   = gammatable[(int)r];\n';
	    code += 'RGB_green = gammatable[(int)g];\n';
	    code += 'RGB_blue  = gammatable[(int)b];\n';
	    code += 'int BrightScale = LEDBrightness / max(max(RGB_red, RGB_green), RGB_blue);\n';
	    code += 'RGB_red   = RGB_red * BrightScale;\n';
	    code += 'RGB_green = RGB_green * BrightScale;\n';
	    code += 'RGB_blue  = RGB_blue * BrightScale;\n';

	    
	    
	return code;
}  

Blockly.Arduino.readColorSensorValue = function () {
 var rgb = this.getFieldValue('RGB_Value');
	var code  = rgb;

	return [code, Blockly.Arduino.ORDER_ATOMIC];
}

Blockly.Arduino.RGB_color_seclet = function () {
  var colour = this.getFieldValue('COLOR');
  return [colour, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino.RGB_color_rgb = function () {
  var R = Blockly.Arduino.valueToCode(this, 'R', Blockly.Arduino.ORDER_ATOMIC);
  var G = Blockly.Arduino.valueToCode(this, 'G', Blockly.Arduino.ORDER_ATOMIC);
  var B = Blockly.Arduino.valueToCode(this, 'B', Blockly.Arduino.ORDER_ATOMIC);
  var colour = R + "*65536" + "+" + G + "*256" + "+" + B;
  return [colour, Blockly.Arduino.ORDER_NONE];
};

Blockly.Arduino.display_rgb_init = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var value_ledcount = Blockly.Arduino.valueToCode(this, 'LEDCOUNT', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.definitions_['include_Adafruit_NeoPixel'] = '#include <Adafruit_NeoPixel.h>\n';
  Blockly.Arduino.definitions_['include_Adafruit_NeoPixel_Bright'] = 'uint8_t LEDBrightness = 255; //default LEDBrightness is set to 255;\n';
  Blockly.Arduino.definitions_['var_declare_rgb_display' + dropdown_rgbpin] = 'Adafruit_NeoPixel  rgb_display_' + dropdown_rgbpin + '= Adafruit_NeoPixel(' + value_ledcount + ',' + dropdown_rgbpin + ',NEO_RGB + NEO_KHZ800);';
  Blockly.Arduino.setups_['setup_rgb_display_begin_' + dropdown_rgbpin] = 'rgb_display_' + dropdown_rgbpin + '.begin();';
  return '';
};

Blockly.Arduino.display_rgb_Brightness = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var Brightness = Blockly.Arduino.valueToCode(this, 'Brightness', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.definitions_['include_Adafruit_NeoPixel'] = '#include <Adafruit_NeoPixel.h>\n';
  Blockly.Arduino.definitions_['include_Adafruit_NeoPixel_Bright'] = 'uint8_t LEDBrightness = 255; //default LEDBrightness is set to 255;\n';
  Blockly.Arduino.setups_['setup_rgb_display_begin_' + dropdown_rgbpin] = 'rgb_display_' + dropdown_rgbpin + '.begin();';
  if (Brightness > 255) Brightness = 255;
  else if (Brightness < 0) Brightness = 0;
  
  var code  = 'rgb_display_' + dropdown_rgbpin + '.setBrightness(' + Brightness + ');\n';
      code += 'LEDBrightness = ' + Brightness + ';\n';
  return code;
};

Blockly.Arduino.display_rgb = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var value_led = Blockly.Arduino.valueToCode(this, '_LED_', Blockly.Arduino.ORDER_ATOMIC);
  var Brightness = Blockly.Arduino.valueToCode(this, 'Brightness', Blockly.Arduino.ORDER_ATOMIC);
  var COLOR = Blockly.Arduino.valueToCode(this, 'COLOR');
  COLOR = COLOR.replace(/#/g, "0x");
  var code = 'rgb_display_' + dropdown_rgbpin + '.setPixelColor((' + value_led + ')-1, ' + COLOR + ');\n';
  return code;
};

Blockly.Arduino.display_rgb_show = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var code = 'rgb_display_' + dropdown_rgbpin + '.show();\n';
  return code;
};

Blockly.Arduino.display_rgb_rainbow1 = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.setups_['setup_rgb_display_begin_' + dropdown_rgbpin] = 'rgb_display_' + dropdown_rgbpin + '.begin();\n';
  var funcName2 = 'Wheel';
  var code2 = 'uint32_t Wheel(byte WheelPos) {\n';
  code2 += 'if(WheelPos < 85) \n{\nreturn rgb_display_' + dropdown_rgbpin + '.Color(WheelPos * 3, 255 - WheelPos * 3, 0);\n} \n';
  code2 += 'else if(WheelPos < 170) \n{\nWheelPos -= 85; \nreturn rgb_display_' + dropdown_rgbpin + '.Color(255 - WheelPos * 3, 0, WheelPos * 3);\n}\n ';
  code2 += 'else\n {\nWheelPos -= 170;\nreturn rgb_display_' + dropdown_rgbpin + '.Color(0, WheelPos * 3, 255 - WheelPos * 3);\n}\n';
  code2 += '}\n';
  Blockly.Arduino.definitions_[funcName2] = code2;
  var funcName3 = 'rainbow';
  var code3 = 'void rainbow(uint8_t wait) {\n uint16_t i, j;\n';
  code3 += 'for(j=0; j<256; j++) {\n';
  code3 += 'for(i=0; i<rgb_display_' + dropdown_rgbpin + '.numPixels(); i++)\n {\n';
  code3 += 'rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, Wheel((i+j) & 255));\n}\n';
  code3 += 'rgb_display_' + dropdown_rgbpin + '.show();\n';
  code3 += 'delay(wait);\n}\n}\n';
  Blockly.Arduino.definitions_[funcName3] = code3;
  var code = 'rainbow(' + wait_time + ');\n'
  return code;
};

Blockly.Arduino.display_rgb_rainbow2 = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  var funcName2 = 'Wheel';
  var code2 = 'uint32_t Wheel(byte WheelPos) {\n';
  code2 += 'if(WheelPos < 85)\n {\nreturn rgb_display_' + dropdown_rgbpin + '.Color(WheelPos * 3, 255 - WheelPos * 3, 0);} \n';
  code2 += 'else if(WheelPos < 170)\n {\nWheelPos -= 85; return rgb_display_' + dropdown_rgbpin + '.Color(255 - WheelPos * 3, 0, WheelPos * 3);}\n ';
  code2 += 'else {\nWheelPos -= 170;return rgb_display_' + dropdown_rgbpin + '.Color(0, WheelPos * 3, 255 - WheelPos * 3);}\n';
  code2 += '}\n';
  Blockly.Arduino.definitions_[funcName2] = code2;
  var funcName3 = 'rainbow';
  var code3 = 'void rainbow(uint8_t wait) { uint16_t i, j;\n';
  code3 += 'for(j=0; j<256; j++) {               \n';
  code3 += 'for(i=0; i<rgb_display_' + dropdown_rgbpin + '.numPixels(); i++)\n{\n';
  code3 += 'rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, Wheel((i+j) & 255));\n}\n';
  code3 += 'rgb_display_' + dropdown_rgbpin + '.show();\n';
  code3 += 'delay(wait);\n}\n}\n';
  Blockly.Arduino.definitions_[funcName3] = code3;
  var funcName4 = 'rainbowCycle';
  var code4 = 'void rainbowCycle(uint8_t wait) \n{\nuint16_t i, j;\n';
  code4 += 'for(j=0; j<256*5; j++) {\n';
  code4 += 'for(i=0; i< rgb_display_' + dropdown_rgbpin + '.numPixels(); i++) \n{\n';
  code4 += 'rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, Wheel(((i * 256 / rgb_display_' + dropdown_rgbpin + '.numPixels()) + j) & 255));}\n';
  code4 += 'rgb_display_' + dropdown_rgbpin + '.show();\n';
  code4 += 'delay(wait);\n}\n}\n';
  Blockly.Arduino.definitions_[funcName4] = code4;
  var code = 'rainbowCycle(' + wait_time + ');\n'
  return code;
};
Blockly.Arduino.display_rgb_rainbow3 = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var rainbow_color = Blockly.Arduino.valueToCode(this, 'rainbow_color', Blockly.Arduino.ORDER_ATOMIC);
  var type = this.getFieldValue('TYPE');
  var funcName2 = 'Wheel';
  var code2 = 'uint32_t Wheel(byte WheelPos) {\n';
  code2 += 'if(WheelPos < 85)\n {\nreturn rgb_display_' + dropdown_rgbpin + '.Color(WheelPos * 3, 255 - WheelPos * 3, 0);} \n';
  code2 += 'else if(WheelPos < 170)\n {\nWheelPos -= 85; return rgb_display_' + dropdown_rgbpin + '.Color(255 - WheelPos * 3, 0, WheelPos * 3);}\n ';
  code2 += 'else {\nWheelPos -= 170;return rgb_display_' + dropdown_rgbpin + '.Color(0, WheelPos * 3, 255 - WheelPos * 3);}\n';
  code2 += '}\n';
  Blockly.Arduino.definitions_[funcName2] = code2;
  if (type == "normal")
    var code3 = 'for (int i = 0; i < rgb_display_' + dropdown_rgbpin + '.numPixels(); i++)\n{rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, Wheel(' + rainbow_color + ' & 255));\n}\nrgb_display_' + dropdown_rgbpin + '.show();\n';
  else
    var code3 = 'for (int i = 0; i < rgb_display_' + dropdown_rgbpin + '.numPixels(); i++)\n {rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, Wheel(((i * 256 / rgb_display_' + dropdown_rgbpin + '.numPixels()) + ' + rainbow_color + ') & 255));\n}\nrgb_display_' + dropdown_rgbpin + '.show();\n';
  return code3;
};

Blockly.Arduino.display_rainbow_stream = function () {

  var dropdown_rgbpin = this.getFieldValue('PIN');
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.setups_['setup_rgb_display_begin_' + dropdown_rgbpin] = 'rgb_display_' + dropdown_rgbpin + '.begin();\n';
  var funcName2 = 'rainbow_stream_def';
  var code2 = 'double FStartT = 0;\n';
  code2 += 'long firstPixelHue = 0;\n';
  
  Blockly.Arduino.definitions_[funcName2] = code2;
  var funcName3 = 'rainbow_stream';
  var code3 = 'void rainbow_stream(uint8_t wait, long *firstPixHue) {\n';

  
  code3 += '  for (int i = 0; i < rgb_display_' + dropdown_rgbpin + '.numPixels(); i++) {\n';
  code3 += '    int pixelHue = *firstPixHue + (i * 65536L / rgb_display_' + dropdown_rgbpin + '.numPixels());\n';
  code3 += '    rgb_display_' + dropdown_rgbpin + '.setPixelColor(i, ' + 'rgb_display_' + dropdown_rgbpin + '.gamma32(rgb_display_' + dropdown_rgbpin + '.ColorHSV(pixelHue)));\n  }\n';
  code3 += '  if (millis() - FStartT > wait) {\n';
  code3 += '    rgb_display_' + dropdown_rgbpin + '.show(); // Update strip with new contents\n';
  code3 += '    FStartT = millis();\n';
  code3 += '     *firstPixHue += 256;\n';
  code3 += '    if (*firstPixHue > 3 * 65536)\n';
  code3 += '      *firstPixHue = 0;\n  }\n}';
  Blockly.Arduino.definitions_[funcName3] = code3;
  var code = 'rainbow_stream(' + wait_time + ', &firstPixelHue);\n'
  return code;
};

Blockly.Arduino.display_theaterChase_rainbow_stream = function () {

  var dropdown_rgbpin = this.getFieldValue('PIN');
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.setups_['setup_rgb_display_begin_' + dropdown_rgbpin] = 'rgb_display_' + dropdown_rgbpin + '.begin();\n';
  var funcName2 = 'theaterChase_rainbow_stream_def';
  var code2 = 'double FStartT = 0;\n';
  code2 += 'long firstPixelHue = 0;\n';
  code2 += 'int firstloop = 0;\n';
  code2 += 'int secondloop = 0;\n'

  
  Blockly.Arduino.definitions_[funcName2] = code2;
  var funcName3 = 'theaterChase_rainbow_stream';
  var code3 = 'void theaterChaseRainbow(int wait, long *firstPixHue, int *outerloop, int *innerloop) {\n';

  
  code3 += '  for (int c = *innerloop; c < rgb_display_' + dropdown_rgbpin + '.numPixels(); c += 3) {\n';
  code3 += '    int hue = *firstPixHue + c * 65536L / rgb_display_' + dropdown_rgbpin + '.numPixels();\n';
  code3 += '    uint32_t color = rgb_display_' + dropdown_rgbpin + '.gamma32(rgb_display_' + dropdown_rgbpin + '.ColorHSV(hue)); // hue -> RGB\n';
  code3 += '    rgb_display_' + dropdown_rgbpin + '.setPixelColor(c, color); \n  }\n';   
  code3 += '  if (millis() - FStartT <= wait) {\n';
  code3 += '    rgb_display_' + dropdown_rgbpin + '.show(); \n  }\n';
  code3 += '  else {\n';
  code3 += '    rgb_display_' + dropdown_rgbpin + '.clear();\n';
  code3 += '    FStartT = millis();\n';
  code3 += '    *firstPixHue += 65536 / 90;\n'; 
  code3 += '    *innerloop += 1;\n\n';
  code3 += '    if (*innerloop >= 3) {\n';
  code3 += '      *innerloop = 0;\n';
  code3 += '      *outerloop += 1;\n    }\n';
  code3 += '    if (*outerloop >= 30) {\n';
  code3 += '      *outerloop = 0;\n';
  code3 += '      *firstPixHue = 0;\n    }\n  }\n}\n\n';

  
  
  Blockly.Arduino.definitions_[funcName3] = code3;
  var code = 'theaterChaseRainbow(' + wait_time + ', &firstPixelHue, &firstloop, &secondloop);\n'
  return code;
};

Blockly.Arduino.password = function () {
  var value = Blockly.Arduino.valueToCode(this, 'VALUE', Blockly.Arduino.ORDER_ATOMIC);
  
  Blockly.Arduino.definitions_['include_password'] = '#include <Password.h>\n';
  
  //Blockly.Arduino.definitions_['password_def_macro'] = '#define ButtonA1 digitalRead(ZW_A1)\n;' + '#define ButtonA2 digitalRead(ZW_A2)\n;' + '#define ButtonA3 digitalRead(ZW_A3)\n;' + '#define ButtonA4 digitalRead(ZW_A4)\n;';
  //Blockly.Arduino.definitions_['password_def_var'] = 'long ButtonA1;\n' + 'long ButtonA2;\n' + 'long ButtonA3;\n' + 'long ButtonA4;\n' + 'long Counter;\n'; 
  
  
  
  var code = 'password.append(' + value + ');\n'
  return code;
};

Blockly.Arduino.setpassword = function () {

  var password = this.getFieldValue('passwd');
  
 
  
  Blockly.Arduino.definitions_['include_password'] = '#include <Password.h> \n';
  Blockly.Arduino.definitions_['password_def'] =  'Password password = Password("' + password + '");\n'
  //Blockly.Arduino.definitions_['password_def_var'] = 'long ButtonA1;\n' + 'long ButtonA2;\n' + 'long ButtonA3;\n' + 'long ButtonA4;\n' + 'long Counter;\n'; 
 
  

  return;
};

Blockly.Arduino.checkpassword = function () {
  
  var code = 'password.evaluate();\n';

  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.resetpasswordinput = function () {
  var dropdown_rgbpin = this.getFieldValue('PIN');
  var code = 'password.reset();\n';
  return code;
};

Blockly.Arduino.ZWinout_analog_write = function() {
  var value_num = Blockly.Arduino.valueToCode(this, 'VALUE',Blockly.Arduino.ORDER_ATOMIC);
  var dropdown_pin = this.getFieldValue('PIN');
  //var dropdown_stat = this.getFieldValue('STAT');
  //var value_num = Blockly.Arduino.valueToCode(this, 'NUM', Blockly.Arduino.ORDER_ATOMIC);
  //var value_num = this.getFieldValue('analogValue');
  Blockly.Arduino.setups_['setup_output'+dropdown_pin] = 'pinMode('+dropdown_pin+', OUTPUT);';
  var code = 'analogWrite('+dropdown_pin+','+value_num+');\n';
  return code;
};
