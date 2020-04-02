'use strict';
goog.provide('Blockly.Blocks.pins');
goog.require('Blockly.Blocks');
Blockly.Blocks.pins.HUE = 230;

Blockly.Blocks['pins_digital'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.default.digital), 'PIN');
    this.setOutput(true, Number);
  }
};
Blockly.Blocks['pins_analog'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.default.analog), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['pins_pwm'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.default.pwm), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['pins_interrupt'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.default.interrupt), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['ZWpins_digital'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([
							["ZW_A1", "ZW_A1"],
							["ZW_A2", "ZW_A2"],
							["ZW_A3", "ZW_A3"],
							["ZW_A4", "ZW_A4"],
							["ZW_B1", "ZW_B1"],
							["ZW_B2", "ZW_B2"],
							["ZW_B3", "ZW_B3"],
							["ZW_B4", "ZW_B4"]
						]), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['ZWpins_analog'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([
							["R1", "R1"],
							["R2", "R2"],
							["R3", "R3"],
							["R4", "R4"]
						]), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['ZWpins_interrupt'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([
							["L1", "L1"],
							["L2", "L2"]
						]), 'PIN');
    this.setOutput(true, Number);
  }
};

Blockly.Blocks['ZWpins_servo'] = {
   init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown([
							["ZW_B1", "ZW_B1"],
							["ZW_B2", "ZW_B2"],
							["ZW_B3", "ZW_B3"],
							["ZW_B4", "ZW_B4"]
						]), 'PIN');
    this.setOutput(true, Number);
  }
};