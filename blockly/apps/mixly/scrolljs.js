var iscroll = new IScroll('.explain-component', {
	mouseWheel: true,
	scrollbars: true,
});
function linkage() {
	setTimeout(function() {
		$('.blocklyDraggable').on('mousedown', function() {
			clearTimeout(timeout);
			var timeout;
			$('li').children().css('background-color', '#eeeeee')
			if(this.className.animVal.indexOf('blocklySelected') > 0) {
				for(var i = 0,length =  this.childNodes.length; i < length; i++) {
					if(this.childNodes[i].className.baseVal.indexOf('cover') > 0) {
						scrollTo('yaokq');
					} else if(this.childNodes[i].className.baseVal.indexOf('left_turn') > 0) {
						scrollTo('turnleft');
					} else if(this.childNodes[i].className.baseVal.indexOf('right_turn') > 0) {
						scrollTo('turnright');
					} else if(this.childNodes[i].className.baseVal.indexOf('go_forward') > 0) {
						scrollTo('goahead');
					} else if(this.childNodes[i].className.baseVal.indexOf('go_reverse') > 0) {
						scrollTo('goback');
					} else if(this.childNodes[i].className.baseVal.indexOf('stop') > 0) {
						scrollTo('stop');
					} else if(this.childNodes[i].className.baseVal.indexOf('catHandle') > 0) {
						scrollTo('catwave');
					} else if(this.childNodes[i].className.baseVal.indexOf('catSound') > 0) {
						scrollTo('catSound ');
					}  else if(this.childNodes[i].className.baseVal.indexOf('firstBtn') > 0) {
						scrollTo('firstBtn '); 
					}else if(this.childNodes[i].className.baseVal.indexOf('secondBtn') > 0) {
						scrollTo('secondBtn ');
					}else if(this.childNodes[i].className.baseVal.indexOf('backBtn') > 0) {
						scrollTo('backBtn ');
					}else if(this.childNodes[i].className.baseVal.indexOf('hammerKnock') > 0) {
						scrollTo('hammerKnock ');
					}else if(this.childNodes[i].className.baseVal.indexOf('numberLives') > 0) {
						scrollTo('numberLives ');
					}else if(this.childNodes[i].className.baseVal.indexOf('scanningGoForward') > 0) {
						scrollTo('scanningGoForward');
					}else if(this.childNodes[i].className.baseVal.indexOf('obstacleGoBack') > 0) {
						scrollTo('obstacleGoBack ');
					}else if(this.childNodes[i].className.baseVal.indexOf('presShake') > 0) {
						scrollTo('presShake');
					}else if(this.childNodes[i].className.baseVal.indexOf('pursuit') > 0) {
						scrollTo('pursuit1');
					}else if(this.childNodes[i].className.baseVal.indexOf('Score') > 0) {
						scrollTo('Score');
					}else if(this.childNodes[i].className.baseVal.indexOf('basketSpeed') > 0) {
						scrollTo('basketSpeed');
					}else if(this.childNodes[i].className.baseVal.indexOf('control_Button_if') > 0) {
						scrollTo('control_Button_if');
					}else if(this.childNodes[i].className.baseVal.indexOf('control_IRsensor_if') > 0) {
						scrollTo('control_IRsensor_if');
					}else if(this.childNodes[i].className.baseVal.indexOf('play_note') > 0) {
						scrollTo('play_note');
					}else if(this.childNodes[i].className.baseVal.indexOf('play_song') > 0) {
						scrollTo('play_song');
					}else if(this.childNodes[i].className.baseVal.indexOf('policeLight') > 0) {
						scrollTo('policeLight');
					}else if(this.childNodes[i].className.baseVal.indexOf('greenLED') > 0) {
						scrollTo('greenLED');
					}else if(this.childNodes[i].className.baseVal.indexOf('redLED') > 0) {
						scrollTo('redLED');
					}else if(this.childNodes[i].className.baseVal.indexOf('blueLED') > 0) {
						scrollTo('blueLED');
					}else if(this.childNodes[i].className.baseVal.indexOf('yellowLED') > 0) {
						scrollTo('yellowLED');
					}else if(this.childNodes[i].className.baseVal.indexOf('offLED') > 0) {
						scrollTo('offLED');
					}else if(this.childNodes[i].className.baseVal.indexOf('leftturn_light_flash') > 0) {
						scrollTo('leftturn_light_flash');
					}else if(this.childNodes[i].className.baseVal.indexOf('leftturn_light_off') > 0) {
						scrollTo('leftturn_light_off');
					}else if(this.childNodes[i].className.baseVal.indexOf('leftturn_light_on') > 0) {
						scrollTo('leftturn_light_on');
					}else if(this.childNodes[i].className.baseVal.indexOf('rightturn_light_flash') > 0) {
						scrollTo('rightturn_light_flash');
					}else if(this.childNodes[i].className.baseVal.indexOf('rightturn_light_off') > 0) {
						scrollTo('rightturn_light_off');
					}else if(this.childNodes[i].className.baseVal.indexOf('rightturn_light_on') > 0) {
						scrollTo('rightturn_light_on');
					}else if(this.childNodes[i].className.baseVal.indexOf('rear_light_on') > 0) {
						scrollTo('rear_light_on');
					}else if(this.childNodes[i].className.baseVal.indexOf('rear_light_off') > 0) {
						scrollTo('rear_light_off');
					}
					
					

				}
			}
		})
	}, 500);
}
function scrollTo(a) {
	iscroll.scrollToElement('.' + a, 500, null, -50, IScroll.utils.ease.bounce);
	timeout = setTimeout(function() {
		$('.' + a).css('background-color', '#ffffff');
		$('.' + a + ' ul li').children().css('background-color', '#fff')
	}, 200);

	return false;

}



//setInterval(function (){
//	$('.blocklyText').each(function(){
//			if($(this).html() == '如果'||$(this).html() == '执行'||$(this).html() == '否则'||$(this).html() == '否则如果'||$(this).html() == '重复'){
//		$(this).css('fill','#514F50')
//	}
//	});
//},17)