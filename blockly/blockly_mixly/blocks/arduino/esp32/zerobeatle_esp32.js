'use strict';

goog.provide('Blockly.Blocks.beatle');
goog.require('Blockly.Blocks');
Blockly.Blocks.beatle.HUE = "#09B9DF";


/*************************************************************************************************************/
/*************************************************************************************************************/
Blockly.Blocks.beatleColorFollower = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleColorFollower);
		/*
		this.appendDummyInput()
		    .appendField(Blockly.BeatleSpeedPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('1500'),'speedP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedD');
		*/
		this.appendDummyInput()
		    .appendField(Blockly.BeatleServoPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('100'),'servoP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoD');
		  	

		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlewandering.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleObjectFollower = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleObjectFollower);
		/*
		this.appendDummyInput()
		    .appendField(Blockly.BeatleSpeedPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('1500'),'speedP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedD');
		*/
		this.appendDummyInput()
		    .appendField(Blockly.BeatleServoPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('50'),'servoP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('50'),'servoD');
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlewandering.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleObjectClassifierFollower = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleObjectClassifierFollower);
		/*
		this.appendDummyInput()
		    .appendField(Blockly.BeatleSpeedPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('1500'),'speedP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedD');
		*/
		this.appendDummyInput()
		    .appendField(Blockly.BeatleServoPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('50'),'servoP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('50'),'servoD');
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlewandering.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleLineTracking = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleCamFollowline);
		
		this.appendDummyInput()
		    .appendField(Blockly.BeatleSpeedPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('2000'),'speedP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'speedD');
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleFaceTracking = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleFaceTracking);
		
    this.appendDummyInput()
		    .appendField(Blockly.BeatleServoPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('200'),'servoP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoD');
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleQRcodeRecog = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleQRcodeRecog);
		
    this.appendDummyInput()
		    .appendField(Blockly.BeatleServoPID)
		  	.appendField(Blockly.linesensors).appendField("P: ")
		  	.appendField(new Blockly.FieldTextInput('150'),'servoP')
		  	.appendField(Blockly.linesensors).appendField("I: ")
		  	.appendField(new Blockly.FieldTextInput('0'),'servoI')
		  	.appendField(Blockly.linesensors).appendField("D: ")
		  	.appendField(new Blockly.FieldTextInput('50'),'servoD');
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};


Blockly.Blocks.beatleCombo = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleCombo);
		
    
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};
