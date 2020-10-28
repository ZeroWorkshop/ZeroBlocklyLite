'use strict';

goog.provide('Blockly.Arduino.beatle');
goog.require('Blockly.Arduino');


var beatleSingleFunc = "";
Blockly.Arduino.beatleColorFollower = function () {
	var speedP = 1500;
	var speedI = 0;
	var speedD = 0;
	var servoP = this.getFieldValue('servoP');
	var servoI = this.getFieldValue('servoI');
	var servoD = this.getFieldValue('servoD');
  Blockly.Arduino.definitions_['include_beatleColorFollower'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleColorFollower'] = 'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_COLOR_RECOGNITION);\n';
	
	
  beatleSingleFunc = 'follower(huskylens,ID1);\n';
                
  return beatleSingleFunc;
};

Blockly.Arduino.beatleObjectFollower = function () {
	var speedP = 1500;
	var speedI = 0;
	var speedD = 0;
	var servoP = this.getFieldValue('servoP');
	var servoI = this.getFieldValue('servoI');
	var servoD = this.getFieldValue('servoD');
  Blockly.Arduino.definitions_['include_beatleColorFollower'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleColorFollower'] = 'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_OBJECT_TRACKING);\n';
	
	
  beatleSingleFunc = 'follower(huskylens,ID1);\n';
                
  return beatleSingleFunc;
};

Blockly.Arduino.beatleObjectClassifierFollower = function () {
	var speedP = 1500;
	var speedI = 0;
	var speedD = 0;
	var servoP = this.getFieldValue('servoP');
	var servoI = this.getFieldValue('servoI');
	var servoD = this.getFieldValue('servoD');
  Blockly.Arduino.definitions_['include_beatleColorFollower'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleColorFollower'] = 'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_OBJECT_RECOGNITION);\n';
	
	
  beatleSingleFunc = 'follower(huskylens,ID1,true);\n';
                
  return beatleSingleFunc;
};
Blockly.Arduino.beatleLineTracking = function () {
	var speedP = this.getFieldValue('speedP');
	var speedI = this.getFieldValue('speedI');
	var speedD = this.getFieldValue('speedD');
  var servoP = 100;
	var servoI = 0;
	var servoD = 0;
  Blockly.Arduino.definitions_['include_beatleLineTracking'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleLineTracking'] =  'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_LINE_TRACKING);\n';
	
	
  beatleSingleFunc = 'lineTracking(huskylens,ID1);\n';
                
  return beatleSingleFunc;
};

Blockly.Arduino.beatleFaceTracking = function () {
	var speedP = 2000;
	var speedI = 0;
	var speedD = 0;
  var servoP = this.getFieldValue('servoP');
	var servoI = this.getFieldValue('servoI');
	var servoD = this.getFieldValue('servoD');
  Blockly.Arduino.definitions_['include_beatleLineTracking'] =  '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleLineTracking'] =  'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_FACE_RECOGNITION);\n';
	
	
  beatleSingleFunc = 'servoTrackingOnly(huskylens,ID1);\n';
                
  return beatleSingleFunc;
};

Blockly.Arduino.beatleQRcodeRecog = function () {
	var speedP = 2000;
	var speedI = 0;
	var speedD = 0;
  var servoP = this.getFieldValue('servoP');
	var servoI = this.getFieldValue('servoI');
	var servoD = this.getFieldValue('servoD');
  Blockly.Arduino.definitions_['include_beatleLineTracking'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleLineTracking'] = 'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'follower_setup(ALGORITHM_TAG_RECOGNITION );\n';
	
	
  beatleSingleFunc = 'servoTrackingOnly(huskylens,ID1,false);\n';
                
  return beatleSingleFunc;
};


Blockly.Arduino.beatleCombo = function () {
	var speedP = 2000;
	var speedI = 0;
	var speedD = 0;
  var servoP = 100;
	var servoI = 0;
	var servoD = 0;
  Blockly.Arduino.definitions_['include_beatleLineTracking'] = '#include "beatleESP32_functions.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleLineTracking'] = 'int ID1 = 1;' + '\n' + 
	                                                              'int32_t size = 400;' + '\n' + 
	                                                              'int32_t speedP = ' + speedP + ',\tspeedI = ' + speedI + ',\tspeedD =' + speedD + ';\n' +
	                                                              'int32_t servoP = ' + servoP + ',\tservoI = ' + servoI + ',\tservoD =' + servoD + ';\n';



	

	Blockly.Arduino.setups_['beatleESP32_basicSetup'] = 'combo_setup();\n';
	
	
  beatleSingleFunc = 'combo();\n';
                
  return beatleSingleFunc;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Blockly.Arduino.beatleAIRequest = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	if (requestType == "request")
	    code = "huskylens.request()";
	else if (requestType == "requestBlocks")
	    code = "huskylens.requestBlocks()";
	else if (requestType == "requestArrows")
	    code = "huskylens.requestArrows()";    
  else if (requestType == "requestLearned")
	    code = "huskylens.requestLearned()";
	else if (requestType == "requestBlocksLearned")
	    code = "huskylens.requestBlocksLearned()";  
	else if (requestType == "requestArrowsLearned")
	    code = "huskylens.requestArrowsLearned()";      
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIRequestID = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestID = this.getFieldValue('ID');
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	if (requestType == "request")
	    code = 'huskylens.request(' + requestID + ')';
	else if (requestType == "requestBlocks")
	    code = 'huskylens.requestBlocks(' + requestID + ')';
	else if (requestType == "requestArrows")
	    code = 'huskylens.requestArrows(' + requestID + ')';    
  else if (requestType == "requestLearned")
	    code = 'huskylens.requestLearned(' + requestID + ')';
	else if (requestType == "requestBlocksLearned")
	    code = 'huskylens.requestBlocksLearned(' + requestID + ')';  
	else if (requestType == "requestArrowsLearned")
	    code = 'huskylens.requestArrowsLearned(' + requestID + ')';      
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIRequestLearnedIDCount = function () {
	var requestType = this.getFieldValue('AICamRequest');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readLearnedIDCount()';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIRequestCount = function () {
	var requestType = this.getFieldValue('AICamRequest');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	if (requestType == "requestBlocks")
	    code = 'huskylens.countBlocks()';
	else if (requestType == "requestArrows")
	    code = 'huskylens.countArrows()';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAICheckBlocksArrows = function () {
	var requestType = this.getFieldValue('AICamRequest');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	if (requestType == "requestBlocks")
	    code = 'huskylens.isAppearDirect(HUSKYLENSResultBlock)';
	else if (requestType == "requestArrows")
	    code = 'huskylens.isAppearDirect(HUSKYLENSResultArrow)';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};



Blockly.Arduino.beatleAIgetBlockParam = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readBlockCenterParameterDirect().' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIgetArrowParam = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readArrowCenterParameterDirect().' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIisLearned = function () {
	var requestID = this.getFieldValue('ID');
		
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.isLearned(' + requestID + ')';
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIisInCam = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestID = this.getFieldValue('ID');
		
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.isAppear(' + requestID + ')';
	
  if (requestType == "requestBlocks")
	    code = 'huskylens.isAppear(' + requestID + ',HUSKYLENSResultBlock)';
	else if (requestType == "requestArrows")
	    code = 'huskylens.isAppear(' + requestID + ',HUSKYLENSResultArrow)';
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIgetBlockInfowithID = function () {
	var requestID = this.getFieldValue('ID');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readBlockParameter(' + requestID + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIgetArrowInfowithID = function () {
	var requestID = this.getFieldValue('ID');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readArrowParameter(' + requestID + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIgetBlockArrowCount = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestID = this.getFieldValue('ID');
		
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.isAppear(' + requestID + ')';
	
  if (requestType == "requestBlocks")
	    code = 'huskylens.readCount(HUSKYLENSResultBlock)';
	else if (requestType == "requestArrows")
	    code = 'huskylens.readCount(HUSKYLENSResultArrow)';
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIgetBlockCountwithID = function () {
	var requestNum = this.getFieldValue('Num');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readBlockParameterDirect(' + requestNum + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIgetArrowCountwithID = function () {
	var requestNum = this.getFieldValue('Num');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readArrowParameterDirect(' + requestNum + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIgetBlockArrowCountwitID = function () {
	var requestType = this.getFieldValue('AICamRequest');
	var requestID = this.getFieldValue('ID');
		
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.isAppear(' + requestID + ')';
	
  if (requestType == "requestBlocks")
	    code = 'huskylens.readCount(' + requestID + ',HUSKYLENSResultBlock)';
	else if (requestType == "requestArrows")
	    code = 'huskylens.readCount(' + requestID + ',HUSKYLENSResultArrow)';
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAIgetBlockNumCountwithID = function () {
	var requestNum = this.getFieldValue('Num');
	var requestID = this.getFieldValue('ID');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readBlockParameter(' + requestID + ',' + requestNum + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleAIgetArrowNumCountwithID = function () {
	var requestNum = this.getFieldValue('Num');
	var requestID = this.getFieldValue('ID');
	var requestParam = this.getFieldValue('AIResultPara');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'huskylens.readArrowParameter(' + requestID + ',' + requestNum + ').' + requestParam;
	
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleAISwitchAlrorithm = function () {
	var Algorithm = this.getFieldValue('AIAlgorithm');
	var code;
	
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



  if (Algorithm == "faceRecog")
	    code = "huskylens.writeAlgorithm(ALGORITHM_FACE_RECOGNITION);";
	else if (Algorithm == "objTracking")
	    code = "huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);";
	else if (Algorithm == "objRecog")
	    code = "huskylens.writeAlgorithm(ALGORITHM_OBJECT_RECOGNITION);";
  else if (Algorithm == "lineTracking")
	    code = "huskylens.writeAlgorithm(ALGORITHM_LINE_TRACKING);"; 
  else if (Algorithm == "colorRecog")
	    code = "huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);";
	else if (Algorithm == "tagRecog")
	    code = "huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);";
	

	Blockly.Arduino.setups_['beatleAISwitchAlgorithmSetup'] = code;
	
	
    
                
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
};

//////////////////////////////////////////////////////////////////////////////////////////
Blockly.Arduino.beatleESP32TempSensor = function () {
	var code;
  Blockly.Arduino.definitions_['include_beatleBMP280'] = '#include "Adafruit_BMP280.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleBMP280'] = 'Adafruit_BMP280 bmp;' + '\n';



	

	Blockly.Arduino.setups_['beatleBMP280Setup'] = 'bmp.begin();\n';
	
	
	code = 'bmp.readTemperature()';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32HumSensor = function () {
	var code;
  Blockly.Arduino.definitions_['include_beatleBMP280'] = '#include "Adafruit_BMP280.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleBMP280'] = 'Adafruit_BMP280 bmp;' + '\n';



	

	Blockly.Arduino.setups_['beatleBMP280Setup'] = 'bmp.begin();\n';
	
	
	code = 'bmp.readHumidity()';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32PressureSensor = function () {
	var code;
  Blockly.Arduino.definitions_['include_beatleBMP280'] = '#include "Adafruit_BMP280.h"\n' +
                                                         '#define ALTITUDE 216.0 // Altitude in Sparta, Greece';
  
  
	Blockly.Arduino.definitions_['declare_beatleBMP280'] = 'Adafruit_BMP280 bmp;' + '\n';



	

	Blockly.Arduino.setups_['beatleBMP280Setup'] = 'bmp.begin();\n';
	
	
	code = 'bmp.seaLevelForAltitude(ALTITUDE,bmp.readPressure()) / 100.0F';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleESP32GestureSensor = function () {
	var requestType = this.getFieldValue('AICamRequest');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleESP32GestureSensor'] ='#include "Adafruit_APDS9960.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32GestureSensor'] = 'Adafruit_APDS9960 apds;\n';



	

	Blockly.Arduino.setups_['setup_beatleESP32GestureSensor'] = 'Serial.begin(115200);\n' + 
	                                                             '  if(!apds.begin()){\n' +
	                                                             '    Serial.println("failed to initialize device! Please check your wiring.");\n' + 
	                                                             '  }\n' + 
	                                                             '  else Serial.println("Device initialized!");\n\n' + 
	                                                             '  apds.enableProximity(true);\n' + 
	                                                             '  apds.enableGesture(true);\n';
	
	
	code = 'uint8_t gesture = apds.readGesture();\n';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32GestureSensored = function () {
	var gesture = this.getFieldValue('gesture');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleESP32GestureSensor'] ='#include "Adafruit_APDS9960.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32GestureSensor'] = 'Adafruit_APDS9960 apds;\n';



	

	Blockly.Arduino.setups_['setup_beatleESP32GestureSensor'] = 'Serial.begin(115200);\n' + 
	                                                             '  if(!apds.begin()){\n' +
	                                                             '    Serial.println("failed to initialize device! Please check your wiring.");\n' + 
	                                                             '  }\n' + 
	                                                             '  else Serial.println("Device initialized!");\n\n' + 
	                                                             '  apds.enableProximity(true);\n' + 
	                                                             '  apds.enableGesture(true);\n';
	
	if (gesture == "UP") 
	   code = 'gesture == APDS9960_UP';
	else if (gesture == "DOWN") 
	   code = 'gesture == APDS9960_DOWN';
	else if (gesture == "LEFT") 
	   code = 'gesture == APDS9960_LEFT';
	else if (gesture == "RIGHT") 
	   code = 'gesture == APDS9960_RIGHT';   


  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleESP32IRRecorder = function () {
	Blockly.Arduino.definitions_['include_beatleESP32IRRecorder'] = '#include "beatleESP32_IRrecord.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32IRRecorder'] = '';



	

	Blockly.Arduino.setups_['beatleESP32_beatleESP32IRRecorder'] = 'IRrecordsetup();\n';
	
	
  beatleSingleFunc = 'IRrecordloop();\n';
                
  return beatleSingleFunc;
  
                
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
};


Blockly.Arduino.beatleESP32MPU9250 = function () {
	var IMUAxis = this.getFieldValue('IMUAccAxis');
	var code;
	
  Blockly.Arduino.definitions_['include_beatleESP32MPU9250'] = '#include <Wire.h>\n' + '#include <MPU6050.h>\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32MPU9250'] = 'MPU6050 mpu;\n' + 
	                                                             'unsigned long timer = 0;\n' + 
	                                                             'float timeStep = 0.01;\n' + 
	                                                             'float pitch = 0;\n' + 
	                                                             'float roll = 0;\n' +
	                                                             'float yaw = 0;\n';

  Blockly.Arduino.setups_['setup_beatleESP32MPU9250'] = 'Serial.begin(115200);\n' +
                                                           '  Serial.println("Initialize MPU6050");\n' + 
                                                           '  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))\n' + 
                                                           '  {\n' +
                                                           '      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");\n' +
                                                           '      delay(500);\n' +
                                                           '  }\n\n' +
                                                           '  mpu.calibrateGyro();\n' +
                                                           '  mpu.setThreshold(3);';
                                                           
  var code = 'timer = millis();\n' + 
             'Vector normAccel = mpu.readNormalizeAccel();\n' +
             'Vector norm = mpu.readNormalizeGyro();\n\n';
  
  

	
    return code;            
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32MPU9250Acc = function () {
	var IMUAxis = this.getFieldValue('IMUAccAxis');
	var code;
	
  Blockly.Arduino.definitions_['include_beatleESP32MPU9250'] = '#include <Wire.h>\n' + '#include <MPU6050.h>\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32MPU9250'] = 'MPU6050 mpu;\n' + 
	                                                             'unsigned long timer = 0;\n' + 
	                                                             'float timeStep = 0.01;\n' + 
	                                                             'float pitch = 0;\n' + 
	                                                             'float roll = 0;\n' +
	                                                             'float yaw = 0;\n';

  Blockly.Arduino.setups_['setup_beatleESP32MPU9250'] = 'Serial.begin(115200);\n' +
                                                           '  Serial.println("Initialize MPU6050");\n' + 
                                                           '  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))\n' + 
                                                           '  {\n' +
                                                           '      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");\n' +
                                                           '      delay(500);\n' +
                                                           '  }\n\n' +
                                                           '  mpu.calibrateGyro();\n' +
                                                           '  mpu.setThreshold(3);';
                                                           

  
  if (IMUAxis == "IMUAccX")
	    code = '-(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;\n';
	else if (IMUAxis == "IMUAccY")
	    code = '(atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;\n';



	
  //  return code;            
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32MPU9250Gyro = function () {
	var IMUAxis = this.getFieldValue('IMUGyroAxis');
	var code;
	
  Blockly.Arduino.definitions_['include_beatleESP32MPU9250'] = '#include <Wire.h>\n' + '#include <MPU6050.h>\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32MPU9250'] = 'MPU6050 mpu;\n' + 
	                                                             'unsigned long timer = 0;\n' + 
	                                                             'float timeStep = 0.01;\n' + 
	                                                             'float pitch = 0;\n' + 
	                                                             'float roll = 0;\n' +
	                                                             'float yaw = 0;\n';
	

  Blockly.Arduino.setups_['setup_beatleESP32MPU9250'] = 'Serial.begin(115200);\n' +
                                                           '  Serial.println("Initialize MPU6050");\n' + 
                                                           '  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))\n' + 
                                                           '  {\n' +
                                                           '      Serial.println("Could not find a valid MPU6050 sensor, check wiring!");\n' +
                                                           '      delay(500);\n' +
                                                           '  }\n\n' +
                                                           '  mpu.calibrateGyro();\n' +
                                                           '  mpu.setThreshold(3);\n';



  if (IMUAxis == "IMUGyroX")
	    code = "pitch = pitch + norm.YAxis * timeStep;\n";
	else if (IMUAxis == "IMUGyroY")
	    code = "roll = roll + norm.XAxis * timeStep;\n";
	else if (IMUAxis == "IMUGyroZ")
	    code = "yaw = yaw + norm.ZAxis * timeStep;\n";

	
  return code;              
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.beatleESP32KeepDirection = function () {
    Blockly.Arduino.definitions_['include_beatleESP32KeepDirection'] = '#include "beatleESP32_MPU9250.h"';
	  
    
    
    Blockly.Arduino.setups_['setup_beatleESP32KeepDirection'] = 'MPU9250setup();\n';

    var code = 'MPU9250loop();\n';
    
    return code;
};

Blockly.Arduino.beatleESP32MicDB = function () {
	var requestType = this.getFieldValue('AICamRequest');
	
	var code;
  Blockly.Arduino.definitions_['include_beatleAICam'] = '#include "ZWHuskyLens.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleAICam'] = 'ZWHuskyLens huskylens;' + '\n';



	

	Blockly.Arduino.setups_['beatleAICamSetup'] = '//combo_setup();\n';
	
	
	code = 'IMU.readSensor();';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
};

/////////////////////////////////////////////////////////////////////////////////////////////////////
Blockly.Arduino.beatleESP32Weatherstation = function() {
  var SSID = Blockly.Arduino.valueToCode(this, 'SSID', Blockly.Arduino.ORDER_ATOMIC);
  var PWD = Blockly.Arduino.valueToCode(this, 'PWD', Blockly.Arduino.ORDER_ATOMIC);
  Blockly.Arduino.definitions_['include_beatleESP32Weatherstation'] ='#include "beatleESP32_weatherStation.h"\n';
  Blockly.Arduino.definitions_['declare_beatleESP32Weatherstation'] = 'const char* ssid = ' + SSID + ';\n' +
                                                                      'const char* password = ' + PWD + ';\n';
  Blockly.Arduino.setups_['setup_beatleESP32Weatherstation'] = 'weathersation_setup(ssid, password);\n'
  
  var code = 'weathersation_loop();\n';    
  
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];
 
};

Blockly.Arduino.beatlePS4padMAC = function() {
  var add0 = this.getFieldValue('add0');
	var add1 = this.getFieldValue('add1');
	var add2 = this.getFieldValue('add2');
	var add3 = this.getFieldValue('add3');
	var add4 = this.getFieldValue('add4');
	var add5 = this.getFieldValue('add5');
	
	
	Blockly.Arduino.definitions_['include_beatleESP32PS4pad'] = '#include <PS4Controller.h>\n';
	Blockly.Arduino.definitions_['declare_beatleESP32PS4pad'] = '';
  
  
  var setupcode = 'PS4.begin("' + add0 + ':' + add1 + ':' + add2 + ':' + add3 + ':' + add4 + ':' + add5 + '");\n' ;
	Blockly.Arduino.setups_['beatle_beatleESP32PS4pad'] = setupcode;
  

	

	var code = '';
	return code;

};
Blockly.Arduino.beatleESP32PS4pad = function () {
	var btn = this.getFieldValue('button');
	Blockly.Arduino.definitions_['include_beatleESP32PS4pad'] = '#include <PS4Controller.h>\n';
  
  
  var buttonkey='';
	if (btn == "UP")
	  buttonkey='up';
	else if (btn == "DOWN")
		buttonkey="down";
	else if (btn == "LEFT")
		buttonkey="left";	
	else if (btn == "RIGHT")
		buttonkey="right";	
	else if (btn == "TRIANGLE")
		buttonkey="triangle";	
	else if (btn == "CROSS")
		buttonkey="cross";
	else if (btn == "SQUARE")
		buttonkey="square";	
	else if (btn == "CIRCLE")
		buttonkey="circle";
  else if (btn == "L1")
		buttonkey="l1";
	else if (btn == "L2")
		buttonkey="l2";	
	else if (btn == "R1")
		buttonkey="r1";
	else if (btn == "R2")
		buttonkey="r2";	
	else if (btn == "L3")
		buttonkey="l3";	
	else if (btn == "R3")
		buttonkey="r3";		
	else if (btn == "UPLEFT")
	  buttonkey='upleft';	
	else if (btn == "UPRIGHT")
	  buttonkey='upright';	
	else if (btn == "DOWNLEFT")
	  buttonkey='downleft';	
	else if (btn == "DOWNRIGHT")
	  buttonkey='downright';	
	else if (btn == "SHARE")
		buttonkey="share";
	else if (btn == "OPTIONS")
		buttonkey="options";
	else if (btn == "PS")
		buttonkey="ps";	
	else if (btn == "TOUCHPAD")
		buttonkey="touchpad";	
				
  var code = 'PS4.data.button.'+ buttonkey;
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];

}

Blockly.Arduino.beatleESP32LRWheels = function() {


	Blockly.Arduino.definitions_['include_beatleSlave'] = '#include <BeatleSerial.h>';
	Blockly.Arduino.definitions_['declare_beatleSlave'] = 'BeatleSerial bSerial;\n';

	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_beatleSlave'] = 'bSerial.begin(Serial);\n';
  

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

	var code = 'bSerial.setSpeeds(' + LspeedValue + ', ' + RspeedValue + ');\n';
	return code;

};

Blockly.Arduino.beatleESP32Wheel = function() {
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

Blockly.Arduino.beatleESP32PlayMP3 = function () {
	var mp3file = this.getFieldValue('mp3file');
	

	
	
  beatleSingleFunc = 'lineTracking(huskylens,ID1);\n';
                
  return beatleSingleFunc;
};

Blockly.Arduino.beatleESP32Servo = function() {

	var code = '\n';
	return code;
};

Blockly.Arduino.beatleESP32IRSend = function () {
	var code = '';
	
	var encodingType = this.getFieldValue('encodingType');
	var keyValue = Blockly.Arduino.valueToCode(this, 'keyValue', Blockly.Arduino.ORDER_ATOMIC);
	Blockly.Arduino.definitions_['include_beatleESP32IRsend'] = '#include <IRremoteESP8266.h>\n' + '#include <IRsend.h>\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32IRsend'] = 'const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).\n' + 'IRsend irsend(kIrLed);\n';



	

	Blockly.Arduino.setups_['beatleESP32_beatleESP32IRsend'] = 'irsend.begin();\n';
	
	if (encodingType == "NEC")
	   code = 'irsend.sendNEC(' + keyValue + ',32);';
	else if (encodingType == "SONY")
	   code = 'irsend.sendSony(' + keyValue + ',32);';
  else if (encodingType == "RC5")
	   code = 'irsend.sendRC5(' + keyValue + ',32);';
  else if (encodingType == "RC6")
	   code = 'irsend.sendRC6(' + keyValue + ',32);';   
	else if (encodingType == "DISH")
	   code = 'irsend.sendDISH(' + keyValue + ',32);';           
  else if (encodingType == "SHARP")
	   code = 'irsend.sendSharpRaw(' + keyValue + ',32);';     
	else if (encodingType == "JVC")
	   code = 'irsend.sendJVC(' + keyValue + ',32,true);';  
  else if (encodingType == "SAMSUNG")
	   code = 'irsend.sendSAMSUNG(' + keyValue + ',32);';    
	else if (encodingType == "MITSUBISHI")
	   code = 'irsend.sendMitsubishi(' + keyValue + ',32);';  
	else if (encodingType == "PANASONIC")
	   code = 'irsend.sendPanasonic(' + keyValue + ',32);';  
	else if (encodingType == "DENON")
	   code = 'irsend.sendDenon(' + keyValue + ',32);';    
	else if (encodingType == "BOSEWAVE")
	   code = 'irsend.sendBoseWave(' + keyValue + ',32);';            
  else if (encodingType == "LG")
	   code = 'irsend.sendLG(' + keyValue + ',32);';           
	           
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
  return code;
};

Blockly.Arduino.beatleESP32getIRbuttonKey = function () {
	Blockly.Arduino.definitions_['include_beatleESP32getIRbuttonKey'] = '#include "beatleESP32_IRreadButtonKey.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32getIRbuttonKey'] = 'String buttonKey;\n';



	

	Blockly.Arduino.setups_['beatleESP32_beatleESP32getIRbuttonKey'] = 'buttonKey = "";\n' +
	                                                                   '  Serial2.begin(115200);\n';
	
	
  var beatleSingleFunc = 'buttonKey = getButtontValue();\n';
                
  return beatleSingleFunc;

}

Blockly.Arduino.beatleESP32compareIRbuttonKey = function () {
	var keyvalue = Blockly.Arduino.valueToCode(this, 'A', Blockly.Arduino.ORDER_ATOMIC);
	Blockly.Arduino.definitions_['include_beatleESP32getIRbuttonKey'] = '#include "beatleESP32_IRreadButtonKey.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_beatleESP32getIRbuttonKey'] = 'String buttonKey;\n';



	

	Blockly.Arduino.setups_['beatleESP32_beatleESP32getIRbuttonKey'] = 'buttonKey = "";\n' +
	                                                                   '  Serial2.begin(115200);\n';
	
	
  var code = '!buttonKey.compareTo('+ keyvalue + ')';
                
  return [code, Blockly.Arduino.ORDER_ATOMIC];

}

Blockly.Arduino.BeatleESP32PlayMP3fromSD = function () {
	Blockly.Arduino.definitions_['include_BeatleESP32PlayMP3fromSD'] = '#include "beatleESP32_onScreenMP3selector.h"\n';
  
  
	Blockly.Arduino.definitions_['declare_BeatleESP32PlayMP3fromSD'] = '';



	

	Blockly.Arduino.setups_['beatleESP32_BeatleESP32PlayMP3fromSD'] = 'MP3Selsetup();\n';
	
	
  beatleSingleFunc = 'MP3Selloop();\n';
                
  return beatleSingleFunc;
  
                
  //return [code, Blockly.Arduino.ORDER_ATOMIC];
};

Blockly.Arduino.RGBLED_functions = function () {

  var dropdown_rgbpin = '13';
  var wait_time = Blockly.Arduino.valueToCode(this, 'WAIT', Blockly.Arduino.ORDER_ATOMIC);
  var lednum = Blockly.Arduino.valueToCode(this, 'LEDN', Blockly.Arduino.ORDER_ATOMIC);

  var code0 = "\n";
  var code1 = "\n";

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;
  code0 = 'Adafruit_NeoPixel  ' + stripName + ' = Adafruit_NeoPixel(' + lednum + ',' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);\n';
  code1 = 'ZeroRGBLED_ESP32 ' + LEDstrip + '(' + dropdown_rgbpin + ',' + lednum + ');\n';
  //Blockly.Arduino.definitions_["RGBLED_function_include"] = '#include "ZeroRGBLED.h"\n';

  Blockly.Arduino.definitions_['include_beatleESP32LED'] = '#include "ZeroRGBLED_ESP32.h"\n';

  Blockly.Arduino.setups_['setup_beatleESP32LED'] = 'Serial.begin(115200);\n  ' +
                                                    LEDstrip + '.init();\n';


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
  var dropdown_rgbpin = '13';
  var value_led = Blockly.Arduino.valueToCode(this, '_LED_', Blockly.Arduino.ORDER_ATOMIC);
  var Brightness = Blockly.Arduino.valueToCode(this, 'Brightness', Blockly.Arduino.ORDER_ATOMIC);
  var COLOR = Blockly.Arduino.valueToCode(this, 'COLOR');

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;

  //Blockly.Arduino.definitions_['include_ZumoShield'] = '#include <Beatle.h>';

  var code1 = 'ZeroRGBLED_ESP32 ' + LEDstrip + '(' + dropdown_rgbpin + ',12);\n';

  Blockly.Arduino.definitions_['include_beatleESP32LED'] = '#include "ZeroRGBLED_ESP32.h"\n';

  Blockly.Arduino.setups_['setup_beatleESP32LED'] = 'Serial.begin(115200);\n  ' +
                                                    LEDstrip + '.init();\n';

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
Blockly.Arduino.beatle_display_rgb_show = function () {

  var dropdown_rgbpin = '13';

 

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;

  var code1 = 'ZeroRGBLED_ESP32 ' + LEDstrip + '(' + dropdown_rgbpin + ',12);\n';

  Blockly.Arduino.definitions_["RGBLED_function_def2" + LEDstrip] = code1;


  Blockly.Arduino.definitions_['include_beatleESP32LED'] = '#include "ZeroRGBLED_ESP32.h"\n';

  Blockly.Arduino.setups_['setup_beatleESP32LED'] = 'Serial.begin(115200);\n  ' +
                                                    LEDstrip + '.init();\n';
  var code = LEDstrip + '.strip.show();\n';
  return code;
};

Blockly.Arduino.RGBLED_policelight = function() {

  var dropdown_rgbpin = "13";

  var lednum = 12;

  var code0 = "\n";
  var code1 = "\n";
  var code2 = "\n";

  var stripName = 'RGBStrip_' + dropdown_rgbpin;
  var LEDstrip = 'LEDStrip_' + dropdown_rgbpin;
  code0 = 'Adafruit_NeoPixel  ' + stripName + ' = Adafruit_NeoPixel(' + lednum + ',' + dropdown_rgbpin + ',NEO_GRB + NEO_KHZ800);\n';
  //code1 = 'ZeroRGBLED ' + LEDstrip + '(' + stripName + ');\n';
  code1 = 'ZeroRGBLED_ESP32 ' + LEDstrip + '(' + dropdown_rgbpin + ',' + lednum + ');\n';
  code2 = 'int pix;'

  Blockly.Arduino.definitions_['include_beatleESP32LED'] = '#include "ZeroRGBLED_ESP32.h"\n';

  Blockly.Arduino.setups_['setup_beatleESP32LED'] = 'Serial.begin(115200);\n  ' +
                                                    LEDstrip + '.init();\n';

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

 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Blockly.Arduino.beatleESP32CleanScreen = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50]\n;' +
                                                              'char str2[50];\n';

	Blockly.Arduino.setups_['beatle_serial'] = 'Serial.begin(115200);\n';

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';

	var color = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

  var code = 'cmd = "cls ' + color + '";\n' +
              'myNextion.sendCommand(cmd);\n';
      
      
	
	return code;

};

Blockly.Arduino.beatleESP32ShowString = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var w = Blockly.Arduino.valueToCode(this, 'W', Blockly.Arduino.ORDER_ATOMIC);
  var h = Blockly.Arduino.valueToCode(this, 'H', Blockly.Arduino.ORDER_ATOMIC);
  var fontid = Blockly.Arduino.valueToCode(this, 'ID', Blockly.Arduino.ORDER_ATOMIC);
  var pointcolor = Blockly.Arduino.valueToCode(this, 'fontcolor', Blockly.Arduino.ORDER_ATOMIC);
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
  var XAlignStatus = this.getFieldValue('XAlignStatus');
  var YAlignStatus = this.getFieldValue('YAlignStatus');
  var backstatus = this.getFieldValue('backstatus');
  var xcenter = 0;
  var ycenter = 0;
  var sta = 0;
  if (XAlignStatus == "LeftAlign") 
    xcenter = 0;
  else if (XAlignStatus == "RightAlign") 
  	xcenter = 2;
  else if (XAlignStatus == "MiddleAlign") 	
  	xcenter = 1;
  	
  if (YAlignStatus == "Uplign") 
    ycenter = 0;
  else if (YAlignStatus == "DownAlign") 
  	ycenter = 2;
  else if (YAlignStatus == "MiddleAlign") 	
  	ycenter = 1;


  if (backstatus == "backstatus0")
    sta = 0;
  else if (backstatus == "backstatus1")
    sta = 1;  
  else if (backstatus == "backstatus2")
    sta = 2;
  else if (backstatus == "backstatus3")
    sta = 3;  
  
  var string = this.getFieldValue('str');
 
  var code = 'cmd = "xstr ' + x + ',' + y + ',' + w + ',' + h + ',' + fontid + ',' + pointcolor + ',' + backcolor + ',' + xcenter + ',' + ycenter + ',' + sta + ',\\"' + string + '\\"";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};

Blockly.Arduino.beatleESP32Fill = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var w = Blockly.Arduino.valueToCode(this, 'W', Blockly.Arduino.ORDER_ATOMIC);
  var h = Blockly.Arduino.valueToCode(this, 'H', Blockly.Arduino.ORDER_ATOMIC);
  
  
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
 
 
  var code = 'cmd = "fill ' + x + ',' + y + ',' + w + ',' + h + ',' + backcolor+ '";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};

Blockly.Arduino.beatleESP32Line = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var x2 = Blockly.Arduino.valueToCode(this, 'X2', Blockly.Arduino.ORDER_ATOMIC);
  var y2 = Blockly.Arduino.valueToCode(this, 'Y2', Blockly.Arduino.ORDER_ATOMIC);
  
  
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
 
 
  var code = 'cmd = "line ' + x + ',' + y + ',' + x2 + ',' + y2 + ',' + backcolor+ '";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};

Blockly.Arduino.beatleESP32Rectangle = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var x2 = Blockly.Arduino.valueToCode(this, 'X2', Blockly.Arduino.ORDER_ATOMIC);
  var y2 = Blockly.Arduino.valueToCode(this, 'Y2', Blockly.Arduino.ORDER_ATOMIC);
  
  
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
 
 
  var code = 'cmd = "draw ' + x + ',' + y + ',' + x2 + ',' + y2 + ',' + backcolor+ '";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};

Blockly.Arduino.beatleESP32Circle = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var r = Blockly.Arduino.valueToCode(this, 'R', Blockly.Arduino.ORDER_ATOMIC);
  
  
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
 
 
  var code = 'cmd = "cir ' + x + ',' + y + ',' + r + ',' + backcolor+ '";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};

Blockly.Arduino.beatleESP32Circle2 = function() {


	Blockly.Arduino.definitions_['include_beatleESP32Screen'] = '#include "NextionSimple.h"';
	Blockly.Arduino.definitions_['declare_beatleESP32Screen'] = '#define nextion Serial2\n' + 
                                                              'NextionSimple myNextion(nextion, 115200);\n' +
                                                              'String message;\n' + 
                                                              'char* cmd;\n' + 
                                                              'char str1[50];\n' +
                                                              'char str2[50];\n';

	

	Blockly.Arduino.setups_['beatle_beatleESP32Screen'] = 'myNextion.init(); ;\n';
  
  var x = Blockly.Arduino.valueToCode(this, 'X', Blockly.Arduino.ORDER_ATOMIC);
  var y = Blockly.Arduino.valueToCode(this, 'Y', Blockly.Arduino.ORDER_ATOMIC);
  var r = Blockly.Arduino.valueToCode(this, 'R', Blockly.Arduino.ORDER_ATOMIC);
  
  
  var backcolor = Blockly.Arduino.valueToCode(this, 'color', Blockly.Arduino.ORDER_ATOMIC);

	
 
 
  var code = 'cmd = "cirs ' + x + ',' + y + ',' + r + ',' + backcolor+ '";\n' +
              'myNextion.sendCommand(cmd);\n';
     
	
	return code;

};