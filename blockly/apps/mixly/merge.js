var arrS = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60 ,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];


$('#model').change(function () {
	
	var model = document.getElementById('model').value;
	if(model == 1){
		var arr = [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
		document.getElementsByClassName('tablevel')[0].style.display='block';
	}else if(model == 2){
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60 ,61,62,63,64,65,66,67,68,69,70,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
		document.getElementsByClassName('tablevel')[0].style.display='none';
	}else if(model == 3){
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60 ,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,78,79,80,81,82,83,84,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
		document.getElementsByClassName('tablevel')[0].style.display='none';
	}
	

})

//var txt = '';
var s = 'Share',
	tou = 'Touch',
	e = 'Explore',
	app = 'Apply',
	m = 'Make';


$('#viewLevelS').on('click', function() {
}).hover(function() {
	document.getElementById('viewLevelS').textContent = s;
}, function() {
		document.getElementById('viewLevelS').textContent = 'S';
});
$('#viewLevelT').on(
	"click",
	function() {
		$('.t').show();
	}
).hover(function() {
	document.getElementById('viewLevelT').textContent = tou;
}, function() {
		document.getElementById('viewLevelT').textContent = 'T';

});
$('#viewLevelE').on('click', function() {
}).hover(function() {
	document.getElementById('viewLevelE').textContent = e;	
}, function() {
		document.getElementById('viewLevelE').textContent = 'E';

});
$('#viewLevelA').on('click', function() {
}).hover(function() {

	document.getElementById('viewLevelA').textContent = app;
}, function() {
		document.getElementById('viewLevelA').textContent = 'A';
});
$('#viewLevelM').on('click', function() {
}).hover(function() {

	document.getElementById('viewLevelM').textContent = m;
}, function() {
		document.getElementById('viewLevelM').textContent = 'M';
});
$('#viewLevelO').on('click', function() {
	
	$('.t').hide();
	var arr = [];
	var id = '#viewLevelO';
	hideSomething(arr, arrS, id);
}).hover(function() {

}, function() {

});
//$("div[aria-posinset=1]").attr('id');
function changeL0() {
	//.42.46.47.52.53.54.55.56.57.58.59
	var arr = [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
	var id = '#viewLevelT';
	hideSomething(arr, arrS, id);
}
setTimeout(function() {
	changePadding(arrS);
	$('.blocklyTreeRoot').click(function() {});
}, 10)

function changePadding(a) {
	a.forEach(function(item) {
		//		$("div[aria-posinset=" + item + "]").css('background-color', '#ffffff');
		$("div[aria-posinset=" + item + "]").css('padding-top', '10px');
	});

	$('.blocklyTreeRow').css('background-color', '#ddd');
}

function hideSomething(a, b, c) {
	
	$('.blocklyFlyout').css('display', 'none');

	document.getElementById('viewLevelS').textContent = 'S';
	document.getElementById('viewLevelT').textContent = 'T';
	document.getElementById('viewLevelE').textContent = 'E';
	document.getElementById('viewLevelA').textContent = 'A';
	document.getElementById('viewLevelM').textContent = 'M';
	for(var i = 0; i < b.length; i++) {
		$("div[aria-posinset=" + b[i] + "]").show();
	}
	for(var i = 0; i < a.length; i++) {
		$("div[aria-posinset=" + a[i] + "]").hide();
	}
}
var canClick = false;
$('.switch-ul').on('click', function() {
	if($('.bgul').css('display') == 'none') {
		$('.bgul').css('display', 'block');
		canClick = true;
	} else {
		canClick = false;
		$('.bgul').css('display', 'none')
	}
});
$('#backgroundSetting').parents().on('click', function() {
	if($(this).attr('class') == 'switch-ul') {
		return false;
	}
	if($('.bgul').css('display') == 'block' && canClick == true) {
		$('.bgul').css('display', 'none');
	}
});
$('.changeBg').on('click', function() {
	var classname = $(this).children().attr('class');
	if(classname == 'icon-bg') {
		sendurl('12345.jpg');
	} else if(classname == 'icon-bg1') {
		sendurl('211614.png');
	} else if(classname == 'icon-bg2') {
		sendurl('backgroundBlue.png');
	} else if(classname == 'icon-bg3') {
		sendurl('backgroundPurple.png');
	}
	$('.bgul').css('display', 'none');
});
setTimeout(function() {
	sendurl('12345.jpg');
	var str = '<div class="t" style="width:100%;height:30px;margin-bottom:3px"><div class="t1 thisT" style="width:49%;height:30px;text-align:center;line-height:30px">T1</div><div style="width:49%;float:right;height:30px;text-align:center;line-height:30px" class="t2">T2</div></div>';
//	$("div[aria-posinset=1]").before(str);
}, 500);

setTimeout(function() {
	$('.s_serial').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.s_serial').addClass('thisT');
		var arr = [1, 2, 3, 4, 5, 6, 7,8,9,10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelS';
		hideSomething(arr, arrS, id);
	});
	$('.t_1').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.t_1').addClass('thisT');
		var arr = [8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});
	$('.t_2').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.t_2').addClass('thisT');
		var arr = [1, 2, 3, 4, 5, 6, 7, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});
	$('.t_3').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.t_3').addClass('thisT');
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,43,41,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});
	$('.t_4').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.t_4').addClass('thisT');
		//40.42，46，47，48，49，50，51，
		
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,41,43,44,45,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});
	$('.t_5').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.t_5').addClass('thisT');
		//.42.46.47.52.53.54.55.56.57.58.59
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,43,44,45,46,48,49,50,51,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});
	$('.preE').on('click', function() {
		$('.thisT').removeClass('thisT');
		$('.preE').addClass('thisT');
		var arr = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103];
		var id = '#viewLevelT';
		hideSomething(arr, arrS, id);
	});

	
}, 1000)



function sendurl(a) {
	setTimeout(function() {
		document.getElementsByTagName('svg')[0].style.background = 'url(../../media/ZeroWorkshop/' + a + ') no-repeat';
		document.getElementsByTagName('svg')[0].style.backgroundSize = 'cover';
	}, 100);

}