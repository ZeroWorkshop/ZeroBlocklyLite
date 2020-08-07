'use strict';
goog.provide('Blockly.Blocks.pins');
goog.require('Blockly.Blocks');
Blockly.Blocks.pins.HUE = 230;

//profile["default"] = profile["Arduino/Genuino Uno"] ;
profile["default"] = profile["arduino_esp32"] ;

Blockly.Blocks['pins_digital'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.digital), 'PIN');
  this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_analog'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.analog), 'PIN');
  this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_pwm'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.pwm), 'PIN');
  this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_interrupt'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.interrupt), 'PIN');
  this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_MOSI'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.MOSI), 'PIN');
  this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_MISO'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.MISO), 'PIN');
  this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_SCK'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.SCK), 'PIN');
  this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_SCL'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.SCL), 'PIN');
  this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_SDA'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.SDA), 'PIN');
  this.setOutput(true, Number);
}
};