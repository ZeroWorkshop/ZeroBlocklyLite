var xmlInfo = document.getElementById('content_xml');
var body = document.getElementsByTagName('body');
body[0].addEventListener('mouseup', function() {
	spliceST();
});
function spliceST() {
	
	var xmlTextarea = document.getElementById('content_xml');
	var xmlText = xmlTextarea.value;
	var xmlDom = null;
	try {
		xmlDom = Blockly.Xml.textToDom(xmlText);
	} catch(e) {
		var q = window.confirm('Error parsing XML:\n' + e + '\n\nAbandon changes?');
		if(!q) {
			return;
		}
	}
	selected = 'xml';
	var content = document.getElementById('content_' + selected);
	var xmlTextarea = document.getElementById('content_xml');
	var xmlDom = Blockly.Xml.workspaceToDom(Blockly.mainWorkspace);
	var xmlText = Blockly.Xml.domToPrettyText(xmlDom);
	xmlTextarea.value = xmlText;
	xmlTextarea.focus();
	var pattern_char = /block/g;
	if(xmlText.match(pattern_char) != null) {
		var blockNumber = xmlText.match(pattern_char).length;
		if(xmlText.indexOf('level_s') > -1&&blockNumber>2) {
			if(xmlDom) {
				xmlDom = Blockly.Xml.textToDom('<xml xmlns="http://www.w3.org/1999/xhtml"><block type="level_s" id="VHp/XK:t/=TZ[`v:X_?s" x="128" y="41"></block></xml>');
				Blockly.mainWorkspace.clear();
				Blockly.Xml.domToWorkspace(xmlDom, Blockly.mainWorkspace);
			}
		} else {

		}
	}


}
