'use strict';

goog.provide('Blockly.Blocks.beatle');
goog.require('Blockly.Blocks');
Blockly.Blocks.beatle.HUE = "#09B9DF";

Blockly.Blocks.allfunc = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleAll);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatle.png',200,200));
		this.setColour(Blockly.Blocks.beatle.HUE);
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

/*************************************************************************************************************/
/*************************************************************************************************************/
Blockly.Blocks.beatleCruise = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleCruise);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlewandering.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleFollowline = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleFollowline);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlefollowline.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleMaze = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.BeatleMaze);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlemaze.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleEdgedetect = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleEdgedetect);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatleborder.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};



Blockly.Blocks.beatleAvoid = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleAvoid);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/pawDown.png',100,65));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleSumo = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleSumo);
		this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/beatlesumo.gif',150,150));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleControl = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleControl);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/pawDown.png',100,65));
		this.setColour('#CC66CC');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};
/*************************************************************************************************************/
/*************************************************************************************************************/
Blockly.Blocks.beatleLRWheels = {
  	init: function() {
		this.appendDummyInput()
		  	.appendField(Blockly.beatleLWheel)
    		.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleWheelForward, "FORWARD"],
			  	[Blockly.beatleWheelBackward, "BACKWARD"],
			  	[Blockly.beatleWheelStop, "STOP"]
		  	]), "LRunningStatus");
		  	
		this.appendValueInput('LspeedValue').appendField(Blockly.beatleWheelSpeed);
		this.appendDummyInput()
		  	.appendField(Blockly.beatleRWheel)
    		.appendField(new Blockly.FieldDropdown([
			  	[Blockly.beatleWheelForward, "FORWARD"],
			  	[Blockly.beatleWheelBackward, "BACKWARD"],
			  	[Blockly.beatleWheelStop, "STOP"]
		  	]), "RRunningStatus");
			 this.appendValueInput('RspeedValue').appendField(Blockly.beatleWheelSpeed);

		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour('#ff9900');
		this.setTooltip('');
		this.setInputsInline(false);
	}
};


Blockly.Blocks.beatleWheel = {
  	init: function() {
		this.appendDummyInput()
		  //.appendField(Blockly.beatleWheel)

			.appendField(new Blockly.FieldDropdown([
				[Blockly.beatleWheelLeft, "M1"],
				[Blockly.beatleWheelRight, "M2"]
			]), "MotorName")
			.appendField(Blockly.beatleWheel)

			.appendField(new Blockly.FieldDropdown([
				[Blockly.beatleWheelForward, "FORWARD"],
				[Blockly.beatleWheelBackward, "BACKWARD"],
				[Blockly.beatleWheelStop, "STOP"]
			]), "RunningStatus");
			
			this.appendValueInput('speedValue')
			    .appendField(Blockly.beatleWheelSpeed);
			

		//.appendField(new Blockly.FieldImage("../../media/ZeroWorkshop/catch.png", 150, 80, ""));
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour('#ff9900');
		this.setTooltip('');
	}
};

Blockly.Blocks['beatle_lists_create_melody'] = {
  /**
   * Block for creating a list with any number of elements of any type.
   * @this Blockly.Block
   */
   init: function() {
    this.setColour('#ff9900');
    this.appendDummyInput("")
    .appendField(Blockly.beatleMyMelodylist)
    .appendField(new Blockly.FieldTextInput('myMelody'), 'MYLIST');
    //.appendField('[')
        //.appendField(new Blockly.FieldTextInput('3',Blockly.FieldTextInput.math_number_validator), 'SIZE')
    //    .appendField(']');
    this.itemCount_ = 9;    //Define the default list number
    this.updateShape_();
    this.setPreviousStatement(true);
    this.setNextStatement(true);
    this.setMutator(new Blockly.Mutator(['lists_create_with_item']));
    this.setTooltip(Blockly.beatleMyMelodylist_TOOLTIP);
      },
  /**
   * Create XML to represent list inputs.
   * @return {Element} XML storage element.
   * @this Blockly.Block
   */
   mutationToDom: function() {
    var container = document.createElement('mutation');
    container.setAttribute('items', this.itemCount_);
    return container;
  },
  /**
   * Parse XML to restore the list inputs.
   * @param {!Element} xmlElement XML storage element.
   * @this Blockly.Block
   */
   domToMutation: function(xmlElement) {
    this.itemCount_ = parseInt(xmlElement.getAttribute('items'), 10);
    this.updateShape_();
  },
  /**
   * Populate the mutator's dialog with this block's components.
   * @param {!Blockly.Workspace} workspace Mutator's workspace.
   * @return {!Blockly.Block} Root block in mutator.
   * @this Blockly.Block
   */
   decompose: function(workspace) {
    var containerBlock =
    Blockly.Block.obtain(workspace, 'lists_create_with_container');
    containerBlock.initSvg();
    var connection = containerBlock.getInput('STACK').connection;
    for (var i = 0; i < this.itemCount_; i++) {
      var itemBlock = Blockly.Block.obtain(workspace, 'lists_create_with_item');
      itemBlock.initSvg();
      connection.connect(itemBlock.previousConnection);
      connection = itemBlock.nextConnection;
    }
    return containerBlock;
  },
  /**
   * Reconfigure this block based on the mutator dialog's components.
   * @param {!Blockly.Block} containerBlock Root block in mutator.
   * @this Blockly.Block
   */
   compose: function(containerBlock) {
    var itemBlock = containerBlock.getInputTargetBlock('STACK');
    // Count number of inputs.
    var connections = [];
    var i = 0;
    while (itemBlock) {
      connections[i] = itemBlock.valueConnection_;
      itemBlock = itemBlock.nextConnection &&
      itemBlock.nextConnection.targetBlock();
      i++;
    }
    this.itemCount_ = i;
    this.updateShape_();
    // Reconnect any child blocks.
    for (var i = 0; i < this.itemCount_; i++) {
      if (connections[i]) {
        this.getInput('ADD' + i).connection.connect(connections[i]);
      }
    }
  },
  /**
   * Store pointers to any connected child blocks.
   * @param {!Blockly.Block} containerBlock Root block in mutator.
   * @this Blockly.Block
   */
   saveConnections: function(containerBlock) {
    var itemBlock = containerBlock.getInputTargetBlock('STACK');
    var i = 0;
    while (itemBlock) {
      var input = this.getInput('ADD' + i);
      itemBlock.valueConnection_ = input && input.connection.targetConnection;
      i++;
      itemBlock = itemBlock.nextConnection &&
      itemBlock.nextConnection.targetBlock();
    }
  },
  /**
   * Modify this block to have the correct number of inputs.
   * @private
   * @this Blockly.Block
   */
   updateShape_: function() {
    // Delete everything.
    if (this.getInput('EMPTY')) {
      this.removeInput('EMPTY');
    } else {
      var i = 0;
      while (this.getInput('ADD' + i)) {
        this.removeInput('ADD' + i);
        i++;
      }
    }
    // Rebuild block.
    if (this.itemCount_ == 0) {
      this.appendDummyInput('EMPTY')
      .appendField(Blockly.Msg.LISTS_CREATE_EMPTY_TITLE);
    } else {
      for (var i = 0; i < this.itemCount_; i++) {
        var input = this.appendValueInput('ADD' + i);
        if (i == 0) {
          //input.appendField(Blockly.Msg.LISTS_CREATE_WITH_INPUT_WITH);
        }
      }
    }
  }
};

Blockly.Blocks.beatleBuzzerPlaynote = {
  init: function() {
	
	this.setColour('#ff9900');
    this.appendDummyInput()
      .appendField(Blockly.beatlePlaynote)
      .appendField(new Blockly.FieldDropdown([
				[Blockly.beatleNoteC,  "C"],
				[Blockly.beatleNoteCSharp, "C#"],
				[Blockly.beatleNoteD,  "D"],
				[Blockly.beatleNoteDSharp, "D#"],
				[Blockly.beatleNoteE,  "E"],
				[Blockly.beatleNoteF,  "F"],
				[Blockly.beatleNoteFSharp, "F#"],
				[Blockly.beatleNoteG,  "G"],
				[Blockly.beatleNoteGSharp, "G#"],
				[Blockly.beatleNoteA,  "A"],
				[Blockly.beatleNoteASharp, "A#"],
				[Blockly.beatleNoteB, "B"],
				[Blockly.beatleNoteSilent, "SILENT"]
			]), "Note")
			.appendField(new Blockly.FieldDropdown([
				[Blockly.beatleoctave0, "0"],
				[Blockly.beatleoctave1, "1"],
				[Blockly.beatleoctave2, "2"],
				[Blockly.beatleoctave3, "3"],
				[Blockly.beatleoctave4, "4"],
				[Blockly.beatleoctave5, "5"],
				[Blockly.beatleoctave6, "6"],
				[Blockly.beatleoctave7, "7"],
				[Blockly.beatleoctave8, "8"]
			]), "Octave");
    
    this.appendDummyInput()
      .appendField(Blockly.beatleNoteduration)
    this.appendValueInput("VALUE")
        .setAlign(Blockly.ALIGN_RIGHT);
    
    this.appendDummyInput()
      .appendField(Blockly.beatleMS)
    
    this.appendDummyInput()
      .appendField(Blockly.beatleNotevolume)
    this.appendValueInput("VOL")
        .setAlign(Blockly.ALIGN_RIGHT);
    
    this.appendDummyInput()
      .appendField(Blockly.beatleVolumerange)
        
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_4digitdisplay_displayString);
  }
};

Blockly.Blocks.beatleBuzzer = {
  init: function() {
	
	this.setColour('#ff9900');
    this.appendDummyInput()
      .appendField(Blockly.beatlePlaysong)
    this.appendValueInput("VALUE")
      //            .setCheck(String)
      .setAlign(Blockly.ALIGN_RIGHT);
      //.appendField(Blockly.OLED_DRAWSTR);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_4digitdisplay_displayString);
  }
};

Blockly.Blocks.beatleBuzzerPlaylist = {
  init: function() {
	
	this.setColour('#ff9900');
    this.appendDummyInput()
      .appendField(Blockly.beatlePlaysong)
      //.appendField('my_melody [')
    this.appendValueInput("VALUE")
      .setAlign(Blockly.ALIGN_RIGHT);
      
    // this.appendDummyInput()
    //     .appendField(']');
      
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip(Blockly.MIXLY_TOOLTIP_4digitdisplay_displayString);
  }
};
Blockly.Blocks.beatleLED = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleLED);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/pawDown.png',100,65));
		this.setColour('#00AD69');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};


Blockly.Blocks.beatle_display_rgb_show = {
  init: function () {
    this.setColour('#ff9900');
    this.appendDummyInput("")
        .appendField(Blockly.beatleLEDpin);
    this.appendValueInput("PIN")
       .setAlign(Blockly.ALIGN_RIGHT); 
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB_SHOW)
    .setAlign(Blockly.ALIGN_RIGHT);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
  }
};

  Blockly.Blocks.beatle_RGB_color_rgb = {
    init: function () {
      this.setColour('#ff9900');
      this.appendValueInput("R")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_R);
      this.appendValueInput("G")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_G);
      this.appendValueInput("B")
      .setCheck(Number)
      .setAlign(Blockly.ALIGN_RIGHT)
      .appendField(Blockly.MIXLY_RGB_B);
      this.setInputsInline(true);
      this.setOutput(true);
      this.setTooltip('');
    }
  };
  
Blockly.Blocks.beatle_display_rgb = {
  init: function () {
    this.setColour('#ff9900');
    this.appendDummyInput("")
    .appendField(Blockly.beatleSetRGB)
    .setAlign(Blockly.ALIGN_RIGHT);
    this.appendDummyInput("")
        .appendField(Blockly.beatleLEDpin);
    this.appendValueInput("PIN")
       .setAlign(Blockly.ALIGN_RIGHT); 
    this.appendValueInput("_LED_")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.MIXLY_RGB_NUM);
    this.appendDummyInput("")
    .appendField(Blockly.Msg.HTML_COLOUR);
    this.appendValueInput("COLOR", Number)
    .setCheck(Number);
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setTooltip('');
    
  }
};


Blockly.Blocks.display_rainbow_stream = {
  init: function () {
  
    this.setColour('#CC66CC');
    this.appendDummyInput("")
    .appendField(Blockly.MIXLY_RGB)
    .appendField(Blockly.beatleLEDfunc)
    .appendField(new Blockly.FieldDropdown([
							[Blockly.beatleRainbow, "option_1"],
							[Blockly.beatleTheaterRainbow, "option_2"]
						]), 'OPTION')
    .setAlign(Blockly.ALIGN_RIGHT);
    
    this.appendValueInput("WAIT")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.beatleInterval);
    
    
    this.setInputsInline(true);
    this.appendDummyInput("")
    .appendField(Blockly.beatleMS);
    
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

  }
};


Blockly.Blocks.RGBLED_functions = {
  init: function () {
  
    this.setColour('#ff9900');
    this.appendDummyInput("")
        .appendField(Blockly.MIXLY_RGB);
       
    this.appendDummyInput("")
        .appendField(Blockly.beatleLEDpin);
    this.appendValueInput("PIN")
       .setAlign(Blockly.ALIGN_RIGHT); 

    this.appendDummyInput("")
        .appendField(Blockly.beatleLEDnumber);
    this.appendValueInput("LEDN")
       .setAlign(Blockly.ALIGN_RIGHT); 
       
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([
							[Blockly.beatleRainbow, "option_1"],
							[Blockly.beatleTheaterRainbow, "option_2"]
						]), 'OPTION')
    .setAlign(Blockly.ALIGN_RIGHT);
    
    this.appendValueInput("WAIT")
    .setCheck(Number)
    .setAlign(Blockly.ALIGN_RIGHT)
    .appendField(Blockly.beatleInterval);
    
    
    this.setInputsInline(true);
    this.appendDummyInput("")
    .appendField(Blockly.beatleMS);
    
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);

  }
};

Blockly.Blocks.RGBLED_policelight = {
	init: function() {
		
		this.appendDummyInput().appendField('有').appendField(new Blockly.FieldDropdown([
			["2", "2"],
			["4", "4"],
			["6", "6"],
			["8", "8"],
			["10", "10"],
			["12", "12"],
		]), 'number').appendField('个警灯');
		this.appendDummyInput()
			.appendField(new Blockly.FieldImage("../../media/ZeroWorkshop/police1.gif", 150, 100, "")).appendField(new Blockly.FieldLabel('', 'policeLight'));
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour('#CC66CC');
		this.setTooltip('');
	}
}

Blockly.Blocks.beatleIRsensor = {
  init: function() {
		this.appendDummyInput()
		  //.appendField(Blockly.beatleWheel)

			.appendField(new Blockly.FieldDropdown([
				[Blockly.beatleWheelLeft, "DSL"],
				[Blockly.beatleWheelRight, "DSR"]
			]), "SensorName")
			.appendField(Blockly.beatleIR)

			.appendField(new Blockly.FieldDropdown([
				[Blockly.beatleIRsensored, "IRsensored"],
				[Blockly.beatleIRunsensored, "unIRsensored"]
			]), "IRStatus");
			
		this.setOutput(true, Boolean);	
		//this.setPreviousStatement(true, null);
		//this.setNextStatement(true, null);
		this.setColour('#f4436d');
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleReadLineIRsensors = {
  init: function() {
		this.appendDummyInput().appendField('  ' + Blockly.beatleLineIRSensor);
		//this.appendDummyInput().appendField(new Blockly.FieldImage('../../media/ZeroWorkshop/pawDown.png',100,65));
		this.setColour('#F4436D');
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setTooltip('');
	}
};

Blockly.Blocks['readLineIRSensorValue'] = {
	init: function() {
		
		this.appendDummyInput()
		    .appendField(Blockly.beatleLineSensorValues)
		    .appendField(new Blockly.FieldDropdown([
				["0", "sensor_values[0]"],
				["1", "sensor_values[1]"],
				["2", "sensor_values[2]"],
				["3", "sensor_values[3]"],
				["4", "sensor_values[4]"],
				["5", "sensor_values[5]"],
				["6", "sensor_values[6]"]
			]), "Sensor_Value").appendField(Blockly.beatleValueread);
		this.setOutput(true,null);
		
		this.setColour("#F4436D");
		

	}
};

Blockly.Blocks.setCalibration4lineSensors = {
  	init: function() {
  	this.appendDummyInput()
		  	.appendField(Blockly.linesensorCalibration);
		  	
		  	
  	this.appendDummyInput()
		  	.appendField(Blockly.linesensors).appendField("  1          ")
		  	.appendField("2          ")
		  	.appendField("3           ")
		  	.appendField("4          ")
		  	.appendField("5           ")
		  	.appendField("6           ")
		  	.appendField("7          ");
		  	
		this.appendDummyInput()
		  	.appendField(Blockly.MaxValue)
		  	.appendField("     ")
		  	.appendField(new Blockly.FieldTextInput('2000'),'0max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'1max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'2max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'3max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'4max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'5max')
		  	.appendField(new Blockly.FieldTextInput('2000'),'6max');		 	
		  	
		
this.appendDummyInput()
		  	.appendField(Blockly.MinValue)
		  	.appendField(" ")
		  	.appendField("   ").appendField(new Blockly.FieldTextInput('200'),'0min')
		  	.appendField("  ").appendField(new Blockly.FieldTextInput('200'),'1min')
		  	.appendField("   ").appendField(new Blockly.FieldTextInput('200'),'2min')
		  	.appendField("  ").appendField(new Blockly.FieldTextInput('200'),'3min')
		  	.appendField("   ").appendField(new Blockly.FieldTextInput('200'),'4min')
		  	.appendField("  ").appendField(new Blockly.FieldTextInput('200'),'5min')
		  	.appendField("   ").appendField(new Blockly.FieldTextInput('200'),'6min');	
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour('#F4436D');
		this.setTooltip('');
	}
};

Blockly.Blocks.beatleReadLinePostion = {
  init: function() {
		
		
		this.appendDummyInput()
		    .appendField(Blockly.beatleLinePostion)
		    ;
		this.setOutput(true,null);
		
		this.setColour("#F4436D");
				
		this.setTooltip('');
	}

};


Blockly.Blocks.beatleLineSensorCalibration = {
  	init: function() {
		this.appendDummyInput()
		  .appendField(Blockly.LineSensorCalibration)
			.appendField(new Blockly.FieldDropdown([
				[Blockly.Yes, "true"],
				[Blockly.No, "false"]
			]), "AllowCal")
			.appendField(Blockly.wheelSpeed)
      .appendField(new Blockly.FieldTextInput('128'),'speed')
      .appendField(Blockly.turningTime)
      .appendField(new Blockly.FieldTextInput('20'),'time');
			
			
			

		//.appendField(new Blockly.FieldImage("../../media/ZeroWorkshop/catch.png", 150, 80, ""));
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);
		this.setColour('#F4436D');
		this.setTooltip('');
	}
};
Blockly.Blocks.beatlewaitforButton = {
  init: function() {
		
		
		this.appendDummyInput()
		    .appendField(Blockly.waitforButton);
		
		
		this.setColour("#F4436D");
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);		
		this.setTooltip('');
	}

};

Blockly.Blocks.PS2_button = {
  init: function() {
  	
  	var options = [
			[Blockly.BPS2_UP, '../../media/ZeroWorkshop/Bup.png'],
			[Blockly.BPS2_LEFT, '../../media/ZeroWorkshop/Bleft.png'],
			[Blockly.BPS2_DOWN, '../../media/ZeroWorkshop/Bdown.png'],
			[Blockly.BPS2_RIGHT, '../../media/ZeroWorkshop/Bright.png'],
			[Blockly.BPS2_TRIANGLE, '../../media/ZeroWorkshop/Btriangle.png'],
			[Blockly.BPS2_SQUARE, '../../media/ZeroWorkshop/Bsquare.png'],
			[Blockly.BPS2_CROSS, '../../media/ZeroWorkshop/Bcross.png'],
			[Blockly.BPS2_CIRCLE, '../../media/ZeroWorkshop/Bcircle.png'],
			[Blockly.BPS2_L1, '../../media/ZeroWorkshop/BL1.png'],
			[Blockly.BPS2_L2, '../../media/ZeroWorkshop/BL2.png'],
			[Blockly.BPS2_R1, '../../media/ZeroWorkshop/BR1.png'],
			[Blockly.BPS2_R2, '../../media/ZeroWorkshop/BR2.png'],
			[Blockly.BPS2_START, '../../media/ZeroWorkshop/Bstart.png'],
			[Blockly.BPS2_SELECT, '../../media/ZeroWorkshop/Bselect.png']
		];

		var dropdown0 = new Blockly.FieldDropdown(options,
			function(newOp) {
				this.sourceBlock_.getField('IMAGE_0').setValue(newOp);

			});

		
      
			this.appendDummyInput()
			.appendField(Blockly.pressPS2button)
			.appendField(dropdown0, 'BUTTON')
			.appendField(Blockly.ZEROWORKSHOP_PS2_BUTTON)
			.appendField(new Blockly.FieldImage('', 50, 50, '*'), 'IMAGE_0');
			
			this.setOutput(true, Boolean);	

		this.setColour('#f4436d');
		this.setTooltip('');
			
		
	}
};


Blockly.Blocks.beatleKeepDirection = {
  init: function() {
		
		
		this.appendDummyInput()
		    .appendField(Blockly.beatleKeepDirection);
		
		this.setColour("#CC66CC");
		this.setPreviousStatement(true, null);
		this.setNextStatement(true, null);		
		this.setTooltip('');
	}

};
