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
