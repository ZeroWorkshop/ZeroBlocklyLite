'use strict';
goog.provide('Blockly.Blocks.pins');
goog.require('Blockly.Blocks');
Blockly.Blocks.pins.HUE = 230;
profile["default"] = profile["arduino_esp32"];
//The original statement ".appendField(new Blockly.FieldDropdown(profile.default.dac), 'PIN');" seems not work properly.
//To make it work, replace the profile.default by profile.arduino_esp32
Blockly.Blocks['pins_dac'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.dac), 'PIN');
    this.setOutput(true);
}
};

Blockly.Blocks['pins_button'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.button), 'PIN');
    this.setOutput(true, Number);
}
};
Blockly.Blocks['pins_sda'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.SDA), 'PIN');
    this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_tx'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.tx), 'PIN');
    this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_scl'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.SCL), 'PIN');
    this.setOutput(true, Number);
}
};

Blockly.Blocks['pins_touch'] = {
 init: function() {
    this.setColour(Blockly.Blocks.pins.HUE);
    this.appendDummyInput("")
    .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.touch), 'PIN');
    this.setOutput(true);
}
};

Blockly.Blocks['pins_serial'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.serial_pin), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_playlist'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.playlist), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['pins_exlcdh'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.exlcdh), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_exlcdv'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.exlcdv), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_axis'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.axis), 'PIN');
        this.setOutput(true, Number);
    }
};
Blockly.Blocks['pins_brightness'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.brightness), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_tone_notes'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.tone_notes), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_radio_power'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.radio_power), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_radio_datarate'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.radio_datarate), 'PIN');
        this.setOutput(true, Number);
    }
};

Blockly.Blocks['pins_one_more'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.one_more), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['serial_select'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.serial_select), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['brightness'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.brightness), 'PIN');
        this.setOutput(true);
    }
};


Blockly.Blocks['CHANNEL'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.CHANNEL), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['PWM_RESOLUTION'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.PWM_RESOLUTION), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['OCTAVE'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.OCTAVE), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['TONE_NOTE'] = {
    init: function() {
        this.setColour(Blockly.Blocks.pins.HUE);
        this.appendDummyInput("")
        .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.TONE_NOTE), 'PIN');
        this.setOutput(true);
    }
};

Blockly.Blocks['pins_digitalWrite'] = {
 init: function() {
  this.setColour(Blockly.Blocks.pins.HUE);
  this.appendDummyInput("")
  .appendField(new Blockly.FieldDropdown(profile.arduino_esp32.digitalWrite), 'PIN');
  this.setOutput(true, Number);
}
};
