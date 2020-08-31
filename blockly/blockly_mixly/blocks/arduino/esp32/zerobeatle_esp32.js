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


Blockly.Blocks.beatleAIRequest = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequesting)
    		.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequest, "request"],
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	[Blockly.beatleAIrequesLearned, "requestLearned"],
			  	[Blockly.beatleAIrequesBlocksLearned, "requestBlocksLearned"],
			  	[Blockly.beatleAIrequesArrowsLearned, "requestArrowsLearned"],
		  	]), "AICamRequest");
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, Boolean);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIRequestID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestingID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(Blockly.beatleAIrequestingDe)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequest, "request"],
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	[Blockly.beatleAIrequesLearned, "requestLearned"],
			  	[Blockly.beatleAIrequesBlocksLearned, "requestBlocksLearned"],
			  	[Blockly.beatleAIrequesArrowsLearned, "requestArrowsLearned"],
		  	]), "AICamRequest");
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, Boolean);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIRequestLearnedIDCount = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestAllLearnedIDCount);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIRequestCount = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")
		  	.appendField(Blockly.beatleAIrequestCountNumber);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAICheckBlocksArrows = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")
		  	.appendField(Blockly.beatleAIrequestInCam);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, Boolean);
		this.setTooltip('');
	}
};


Blockly.Blocks.beatleAIgetBlockParam = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCenter)
		  	.appendField(Blockly.beatleAIrequestBlocks)
		  	/*.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")*/
			  .appendField(Blockly.beatleAIrequestingDe)	
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXcenter, "xCenter"],
			  	[Blockly.beatleAIrequestParamYcenter, "yCenter"],
			  	[Blockly.beatleAIrequestParamWidth, "width"],
			  	[Blockly.beatleAIrequestParamHeight, "height"],
			  	]), "AIResultPara")
		  	.appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetArrowParam = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCenter)
		  	.appendField(Blockly.beatleAIrequesArrows)
		  	/*.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")*/
			  .appendField(Blockly.beatleAIrequestingDe)	
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXStart, "xOrigin"],
			  	[Blockly.beatleAIrequestParamYStart, "yOrigin"],
			  	[Blockly.beatleAIrequestParamXEnd, "xTarget"],
			  	[Blockly.beatleAIrequestParamYEnd, "yTarget"],
			  	]), "AIResultPara")
		  	.appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIisLearned = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
			  .appendField(Blockly.beatleAIrequestisLearned);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, Boolean);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIisInCam = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")
			  .appendField(Blockly.beatleAIrequestInCam);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, Boolean);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetBlockInfowithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(Blockly.beatleAIrequestBlocks)
		  	.appendField(Blockly.beatleAIrequestiParam)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXcenter, "xCenter"],
			  	[Blockly.beatleAIrequestParamYcenter, "yCenter"],
			  	[Blockly.beatleAIrequestParamWidth, "width"],
			  	[Blockly.beatleAIrequestParamHeight, "height"],
			  	]), "AIResultPara");
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetArrowInfowithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(Blockly.beatleAIrequesArrows)
		  	.appendField(Blockly.beatleAIrequestiParam)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXStart, "xOrigin"],
			  	[Blockly.beatleAIrequestParamYStart, "yOrigin"],
			  	[Blockly.beatleAIrequestParamXEnd, "xTarget"],
			  	[Blockly.beatleAIrequestParamYEnd, "yTarget"],
			  	]), "AIResultPara");
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetBlockArrowCount = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")
			  .appendField(Blockly.beatleAIrequestTotal);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetBlockCountwithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestNum)
		  	.appendField(new Blockly.FieldTextInput('1'),'Num')
		  	.appendField(Blockly.beatleAIrequestGe)
		  	.appendField(Blockly.beatleAIrequestBlocks)
		  	.appendField(Blockly.beatleAIrequestingDe)
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXcenter, "xCenter"],
			  	[Blockly.beatleAIrequestParamYcenter, "yCenter"],
			  	[Blockly.beatleAIrequestParamWidth, "width"],
			  	[Blockly.beatleAIrequestParamHeight, "height"],
			  	]), "AIResultPara")
			  	.appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetArrowCountwithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestNum)
		  	.appendField(new Blockly.FieldTextInput('1'),'Num')
		  	.appendField(Blockly.beatleAIrequestGe)
		  	.appendField(Blockly.beatleAIrequesArrows)
		  	.appendField(Blockly.beatleAIrequestingDe)
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXStart, "xOrigin"],
			  	[Blockly.beatleAIrequestParamYStart, "yOrigin"],
			  	[Blockly.beatleAIrequestParamXEnd, "xTarget"],
			  	[Blockly.beatleAIrequestParamYEnd, "yTarget"],
			  	]), "AIResultPara")
			  	.appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetBlockArrowCountwitID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestBlocks, "requestBlocks"],
			  	[Blockly.beatleAIrequesArrows, "requestArrows"],
			  	]), "AICamRequest")
			  .appendField(Blockly.beatleAIrequestTotal);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetBlockNumCountwithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(Blockly.beatleAIrequestNum)
		  	.appendField(new Blockly.FieldTextInput('1'),'Num')
		  	.appendField(Blockly.beatleAIrequestGe)
		  	.appendField(Blockly.beatleAIrequestBlocks)
		  	.appendField(Blockly.beatleAIrequestingDe)
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXcenter, "xCenter"],
			  	[Blockly.beatleAIrequestParamYcenter, "yCenter"],
			  	[Blockly.beatleAIrequestParamWidth, "width"],
			  	[Blockly.beatleAIrequestParamHeight, "height"],
			  	]), "AIResultPara")
			  	.appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAIgetArrowNumCountwithID = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIrequestCount)
		  	.appendField(Blockly.beatleAIrequestParamID)
		  	.appendField(new Blockly.FieldTextInput('1'),'ID')
		  	.appendField(Blockly.beatleAIrequestNum)
		  	.appendField(new Blockly.FieldTextInput('1'),'Num')
		  	.appendField(Blockly.beatleAIrequestGe)
		  	.appendField(Blockly.beatleAIrequesArrows)
		  	.appendField(Blockly.beatleAIrequestingDe)
			  .appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIrequestParamXStart, "xOrigin"],
			  	[Blockly.beatleAIrequestParamYStart, "yOrigin"],
			  	[Blockly.beatleAIrequestParamXEnd, "xTarget"],
			  	[Blockly.beatleAIrequestParamYEnd, "yTarget"],
			  	]), "AIResultPara")
			  .appendField(Blockly.beatleAIrequestiParam1);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setOutput(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleAISwitchAlrorithm = {
  init: function() {
		//this.appendDummyInput().appendField('  ' + Blockly.beatleAIReuest);
		
    this.appendDummyInput()
		  	.appendField(Blockly.beatleAIswitchAlorithm)
    		.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleAIfaceRecog, "faceRecog"],
			  	[Blockly.beatleAIobjTracking, "objTracking"],
			  	[Blockly.beatleAIobjRecog, "objRecog"],
			  	[Blockly.beatleAIlineTracking, "lineTracking"],
			  	[Blockly.beatleAIcolorRecog, "colorRecog"],
			  	[Blockly.beatleAItagRecog, "tagRecog"],
		  	]), "AIAlgorithm");
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#3366CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};