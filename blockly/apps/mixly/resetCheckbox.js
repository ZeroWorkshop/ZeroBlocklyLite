var time;
var arrNum = [];
var t ;
var o ;
var classNum=[];
var temporary=[];
var usefulNum=[];

setInterval(function (){
	reSetCheckbox();
},500);

function reSetCheckbox(u) {
	arrNum.push(u);
	if(time == undefined) {
		time = new Date().getTime();
	} else {
		 t = new Date().getTime();
		 o = t - time;
	}
	time = new Date().getTime();
	if(o < 150) {
		return false;
	}
	setKey();
	arrNum.sort();
	var res = [arrNum[0]];
	for(var i=0, len= arrNum.length;i<len;i++){
		if(arrNum[i]!=res[res.length-1]&&arrNum[i]!=undefined){
			res.push(arrNum[i]);
		}
	}
//		console.log('res is :'+res);
	for(var i = 0,len = res.length ; i < len; i++) {
		if(!isNaN(res[i])){
			reSetCheckbox1(res[i]);
		}
	}
}
 
function reSetCheckbox1(z) {

		
	setTimeout(function() {
		
		changeSize(z); 
		reSetBt(z); 
		reSetButtonPic(z); 
		resetSize1_rest(z); 
		reSetBtRest(z); 
		reSetButtonPicRest(z); 
		reSetBlocklyFlyoutBackgroundSize(z);

		var arr = [$('.' + z + 'test0').next(),
			$('.' + z + 'test0').next().next(),
			$('.' + z + 'test0').next().next().next(),
			$('.' + z + 'test0').next().next().next().next(),
			$('.' + z + 'test00').next(),
			$('.' + z + 'test00').next().next(),
			$('.' + z + 'test00').next().next().next(),
			$('.' + z + 'test00').next().next().next().next()
		];

		var arr1 = [
			$('.' + z + 'test000').next(),
			$('.' + z + 'test000').next().next(),
			$('.' + z + 'test000').next().next().next(),
			$('.' + z + 'test000').next().next().next().next(),
			$('.' + z + 'test0000').next(),
			$('.' + z + 'test0000').next().next()
		];

		var change = [$('.' + z + 'cover0').next(),
			$('.' + z + 'cover0').next().next(),
			$('.' + z + 'cover0').next().next().next(),
			$('.' + z + 'cover0').next().next().next().next(),
			$('.' + z + 'cover00').next(),
			$('.' + z + 'cover00').next().next(),
			$('.' + z + 'cover00').next().next().next(),
			$('.' + z + 'cover00').next().next().next().next(),
		];
		var change1 = [$('.' + z + 'cover000').next(),
			$('.' + z + 'cover000').next().next(),
			$('.' + z + 'cover000').next().next().next(),
			$('.' + z + 'cover000').next().next().next().next(),
			$('.' + z + 'cover0000').next(),
			$('.' + z + 'cover0000').next().next(),
		];
		if($('.' + z + 'test0').attr('class') == undefined) {
			return false;
		}

		loopFunction(z);
		resetSize1(arr1);
		resetSize(arr);
		repalceAbovePic(arr1, change1);
		repalcePic(arr, change); 
	}, 17);
}

function loopFunction(z) {
	for(var i = 1; i < 10; i++) {
		var arr_rest = [$('.' + z + 'test' + i).next(),
			$('.' + z + 'test' + i).next().next(),
			$('.' + z + 'test' + i).next().next().next(),
			$('.' + z + 'test' + i).next().next().next().next(),
			$('.' + z + 'test' + i + i).next(),
			$('.' + z + 'test' + i + i).next().next(),
			$('.' + z + 'test' + i + i).next().next().next(),
			$('.' + z + 'test' + i + i).next().next().next().next()
		];
		var change_rest = [$('.' + z + 'cover' + i).next(),
			$('.' + z + 'cover' + i).next().next(),
			$('.' + z + 'cover' + i).next().next().next(),
			$('.' + z + 'cover' + i).next().next().next().next(),
			$('.' + z + 'cover' + i + i).next(),
			$('.' + z + 'cover' + i + i).next().next(),
			$('.' + z + 'cover' + i + i).next().next().next(),
			$('.' + z + 'cover' + i + i).next().next().next().next(),
		];
		var arr1_rest = [
			$('.' + z + 'test' + i + i + i).next(),
			$('.' + z + 'test' + i + i + i).next().next(),
			$('.' + z + 'test' + i + i + i).next().next().next(),
			$('.' + z + 'test' + i + i + i).next().next().next().next(),
			$('.' + z + 'test' + i + i + i + i).next(),
			$('.' + z + 'test' + i + i + i + i).next().next()
		];
		var change1_rest = [$('.' + z + 'cover' + i + i + i).next(),
			$('.' + z + 'cover' + i + i + i).next().next(),
			$('.' + z + 'cover' + i + i + i).next().next().next(),
			$('.' + z + 'cover' + i + i + i).next().next().next().next(),
			$('.' + z + 'cover' + i + i + i + i).next(),
			$('.' + z + 'cover' + i + i + i + i).next().next(),
		];
		repalcePic(arr_rest, change_rest);
		repalceAbovePic(arr1_rest, change1_rest);

	}
}
function repalcePic(y, x) {
	for(var i = 0,len = y.length; i < len; i++) {
		if(y[i].find('text:last').css('display') == 'block') {
			if(i == 0) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/upLight.png');
			} else if(i == 1) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/downLight.png');
			} else if(i == 2) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/leftLight.png');
			} else if(i == 3) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/rightLight.png');
			} else if(i == 4) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/TriangleLight.png');
			} else if(i == 5) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/×Light.png');
			} else if(i == 6) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/SquareLight.png');
			} else if(i == 7) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/roundLight.png');
			}

		} else {
			if(i == 0) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/upDark.png');
			} else if(i == 1) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/downDark.png');
			} else if(i == 2) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/leftDark.png');
			} else if(i == 3) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/rightDark.png');
			} else if(i == 4) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/TriangleDark.png');
			} else if(i == 5) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/×Dark.png');
			} else if(i == 6) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/SquareDark.png');
			} else if(i == 7) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/roundDark.png');
			}

		}
	}
}

function repalceAbovePic(y, x) {
	for(var i = 0,len = y.length; i < len ; i++) {
		if(y[i].find('text:last').css('display') == 'block') {
			if(i == 0) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/L-L1.png');
			} else if(i == 1) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/L-L2.png');
			} else if(i == 2) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/L-R1.png');
			} else if(i == 3) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/L-R2.png');
			} else if(i == 4) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/selectLight.png');
			} else if(i == 5) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/startLight.png');
			}

		} else {
			if(i == 0) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/D-L1.png');
			} else if(i == 1) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/D-L2.png');
			} else if(i == 2) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/D-R1.png');
			} else if(i == 3) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/D-R2.png');
			} else if(i == 4) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/selectDark.png');
			} else if(i == 5) {
				x[i].children().attr('xlink:href', '../../media/ZeroWorkshop/startDark.png');
			}
		}
	}

}

function setKey() {
	$('.blocklyIconGroup').on('mouseover', function() {
		var classname = $(this).next().next().attr('class');
		localStorage.setItem('z', classname);

	})
}

function getKey() {
	var a = localStorage.getItem('z');
//	console.log(a)
	a = a.split(' ');
	a = a[1].split('c')[0];

	return a;
}

function hasClass(element, cls) {
    return (' ' + element.className + ' ').indexOf(' ' + cls + ' ') > -1;
}

//hasClass(document.querySelector("html"), 'no-js');