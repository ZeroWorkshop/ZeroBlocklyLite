function changeSize(z) {

	for(var i = 0; i < 10; i++) { //改变背景图片大小
		$('.' + z + 'cover' + i).prev().children().attr('width', '450px');
	}
	var blocklyPathDark = $('.' + z + 'cover0').prev().prev().prev().prev().prev().attr('d');
	if(blocklyPathDark != undefined) {
		blocklyPathDark = blocklyPathDark.split(' ');
		for(var i = 0; i < blocklyPathDark.length; i++) {
			if(parseInt(blocklyPathDark[i]) > 1000) {
				blocklyPathDark[i] = "530";
			}
		}
		blocklyPathDark = blocklyPathDark.join(' ');
		$('.' + z + 'cover0').prev().prev().prev().prev().prev().attr('d', blocklyPathDark);
		$('.' + z + 'cover0').prev().prev().prev().prev().attr('d', blocklyPathDark);
		$('.' + z + 'cover0').prev().prev().prev().attr('d', blocklyPathDark);
	}
}

function reSetBt(z) {

	//	$('.blocklyEditableText rect').css('fill-opacity', '0');
	$('.blocklyEditableText text').css('fill', '#000000');
	//shang下左右复选框
	$('.' + z + 'test0').next().css('transform', 'translate(121px,63px)');
	$('.' + z + 'test0').next().next().css('transform', 'translate(121px,124px)');
	$('.' + z + 'test0').next().next().next().css('transform', 'translate(86px,92px)');
	$('.' + z + 'test0').next().next().next().next().css('transform', 'translate(159px,92px)');
	

	$('.' + z + 'test0').next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test0').next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test0').next().next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test0').next().next().next().next().find('rect').css('fill-opacity', '0');

	//右边键
	$('.' + z + 'test00').next().css('transform', 'translate(380px,63px)');
	$('.' + z + 'test00').next().next().css('transform', 'translate(380px,122px)');
	$('.' + z + 'test00').next().next().next().css('transform', 'translate(346px,92px)');
	$('.' + z + 'test00').next().next().next().next().css('transform', 'translate(414px,92px)');

	$('.' + z + 'test00').next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test00').next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test00').next().next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test00').next().next().next().next().find('rect').css('fill-opacity', '0');
	//上方键
	$('.' + z + 'test000').next().css('transform', 'translate(49px,17px)');
	$('.' + z + 'test000').next().next().css('transform', 'translate(194px,15px)');
	$('.' + z + 'test000').next().next().next().css('transform', 'translate(287px,17px)');
	$('.' + z + 'test000').next().next().next().next().css('transform', 'translate(433px,16px)');

	$('.' + z + 'test000').next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test000').next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test000').next().next().next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test000').next().next().next().next().find('rect').css('fill-opacity', '0');
	//中间2个键
	$('.' + z + 'test0000').next().css('transform', 'translate(213px,101px)');
	$('.' + z + 'test0000').next().next().css('transform', 'translate(270px,103px)');

	$('.' + z + 'test0000').next().find('rect').css('fill-opacity', '0');
	$('.' + z + 'test0000').next().next().find('rect').css('fill-opacity', '0');
	
	$('.' + z + 'test0000').next().next().next().css('transform', 'translate(200px,273px)');
	$('.' + z + 'test0000').next().next().next().find('rect').css('fill', '#ffff');
	
}

function reSetBtRest(z) {
	for(var i = 1; i < 10; i++) {
		if($('.' + z + 'cover' + i).attr('class') != undefined) {
			var addDis = getDistance(i, z);

			//shang下左右复选框
			$('.' + z + 'test' + i).next().css('transform', 'translate(93px,' + eval(parseInt(400) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i).next().next().css('transform', 'translate(93px,' + eval(parseInt(456) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i).next().next().next().css('transform', 'translate(59px,' + eval(parseInt(426) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i).next().next().next().next().css('transform', 'translate(128px,' + eval(parseInt(426) + parseInt(addDis)) + 'px)');

			$('.' + z + 'test' + i).next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i).next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i).next().next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i).next().next().next().next().find('rect').css('fill-opacity', '0');
			//右边键
			$('.' + z + 'test' + i + i).next().css('transform', 'translate(352px, ' + eval(parseInt(398) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i).next().next().css('transform', 'translate(352px, ' + eval(parseInt(463) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i).next().next().next().css('transform', 'translate(318px,' + eval(parseInt(426) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i).next().next().next().next().css('transform', 'translate(387px,' + eval(parseInt(426) + parseInt(addDis)) + 'px)');

			$('.' + z + 'test' + i + i).next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i).next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i).next().next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i).next().next().next().next().find('rect').css('fill-opacity', '0');
			//上方键
			$('.' + z + 'test' + i + i + i).next().css('transform', 'translate(22px,' + eval(parseInt(353) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i + i).next().next().css('transform', 'translate(167px,' + eval(parseInt(353) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i + i).next().next().next().css('transform', 'translate(260px,' + eval(parseInt(353) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i + i).next().next().next().next().css('transform', 'translate(406px,' + eval(parseInt(353) + parseInt(addDis)) + 'px)');

			$('.' + z + 'test' + i + i + i).next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i + i).next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i + i).next().next().next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i + i).next().next().next().next().find('rect').css('fill-opacity', '0');
			//中间2个键
			$('.' + z + 'test' + i + i + i + i).next().css('transform', 'translate(186px,' + eval(parseInt(435) + parseInt(addDis)) + 'px)');
			$('.' + z + 'test' + i + i + i + i).next().next().css('transform', 'translate(245px,' + eval(parseInt(433) + parseInt(addDis)) + 'px)');
			
			$('.' + z + 'test' + i + i + i + i).next().next().next().css('transform', 'translate(252px,' + eval(parseInt(605) + parseInt(addDis)) + 'px)');

			$('.' + z + 'test' + i + i + i + i).next().find('rect').css('fill-opacity', '0');
			$('.' + z + 'test' + i + i + i + i).next().next().find('rect').css('fill-opacity', '0');
			
			
			$('.' + z + 'test' + i + i + i + i).next().next().next().find('rect').css('fill', '#4D4B4C');
		}
	}

}

function reSetButtonPic(z) {
	//上下左右原始图片
	$('.' + z + 'cover0').next().css('transform', 'translate(103px,50px)');
	$('.' + z + 'cover0').next().next().css('transform', 'translate(103px,105px)');
	$('.' + z + 'cover0').next().next().next().css('transform', 'translate(73px,75px)');
	$('.' + z + 'cover0').next().next().next().next().css('transform', 'translate(135px,75px)');
	//右边方向控制键
	$('.' + z + 'cover00').next().css('transform', 'translate(367px,52px)');
	$('.' + z + 'cover00').next().next().css('transform', 'translate(367px,116px)');
	$('.' + z + 'cover00').next().next().next().css('transform', 'translate(333px,81px)');
	$('.' + z + 'cover00').next().next().next().next().css('transform', 'translate(401px,81px)');
	//上面的键
	$('.' + z + 'cover000').next().css('transform', 'translate(44px,3px)');
	$('.' + z + 'cover000').next().next().css('transform', 'translate(188px,4px)');
	$('.' + z + 'cover000').next().next().next().css('transform', 'translate(281px,4px)');
	$('.' + z + 'cover000').next().next().next().next().css('transform', 'translate(427px,3px)');
	//中间2个键
	$('.' + z + 'cover0000').next().css('transform', 'translate(224px,98px)');
	$('.' + z + 'cover0000').next().next().css('transform', 'translate(277px,98px)');
}

function reSetButtonPicRest(z) {

	for(var i = 1; i < 10; i++) {
		if($('.' + z + 'cover' + i).attr('class') != undefined) {

			var addDis = getDistance(i, z);

			//上下左右原始图片
			$('.' + z + 'cover' + i).next().css('transform', 'translate(76px,' + eval(parseInt(385) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i).next().next().css('transform', 'translate(76px,' + eval(parseInt(441) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i).next().next().next().css('transform', 'translate(45px,' + eval(parseInt(411) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i).next().next().next().next().css('transform', 'translate(108px,' + eval(parseInt(411) + parseInt(addDis)) + 'px)');
			//右边方向控制键
			$('.' + z + 'cover' + i + i).next().css('transform', 'translate(340px,' + eval(parseInt(388) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i).next().next().css('transform', 'translate(341px,' + eval(parseInt(453) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i).next().next().next().css('transform', 'translate(305px,' + eval(parseInt(416) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i).next().next().next().next().css('transform', 'translate(374px,' + eval(parseInt(416) + parseInt(addDis)) + 'px)');
			//上面的键
			$('.' + z + 'cover' + i + i + i).next().css('transform', 'translate(16px,' + eval(parseInt(339) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i + i).next().next().css('transform', 'translate(161px,' + eval(parseInt(339) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i + i).next().next().next().css('transform', 'translate(254px,' + eval(parseInt(339) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i + i).next().next().next().next().css('transform', 'translate(400px,' + eval(parseInt(339) + parseInt(addDis)) + 'px)');
			//中间2个键
			$('.' + z + 'cover' + i + i + i + i).next().css('transform', 'translate(197px,' + eval(parseInt(433) + parseInt(addDis)) + 'px)');
			$('.' + z + 'cover' + i + i + i + i).next().next().css('transform', 'translate(249px,' + eval(parseInt(433) + parseInt(addDis)) + 'px)');
		}
	}

}

function resetSize(x) {
	for(var i = 0, len = x.length; i < len; i++) {
		x[i].find('text:last').html('');
		x[i].find('rect').css('stroke-opacity', '0');
		x[i].find('rect').attr('height', '30');
		x[i].find('rect').css('width', '35');
	}

}

function resetSize1(x) {
	for(var i = 0, len = x.length; i < len; i++) {
		x[i].find('text:last').html('');
		x[i].find('rect').css('stroke-opacity', '0');
		x[i].find('rect').attr('height', '26');
		x[i].find('rect').css('width', '54');
	}

}

function resetSize1_rest(z) {
	for(var i = 1; i < 10; i++) {
		if($('' + z + 'test' + i + i + i)) {
			var arr1_rest = [
				$('.' + z + 'test' + i + i + i).next(),
				$('.' + z + 'test' + i + i + i).next().next(),
				$('.' + z + 'test' + i + i + i).next().next().next(),
				$('.' + z + 'test' + i + i + i).next().next().next().next(),
				$('.' + z + 'test' + i + i + i + i).next(),
				$('.' + z + 'test' + i + i + i + i).next().next()
			];
			var arr_rest = [$('.' + z + 'test' + i).next(),
				$('.' + z + 'test' + i).next().next(),
				$('.' + z + 'test' + i).next().next().next(),
				$('.' + z + 'test' + i).next().next().next().next(),
				$('.' + z + 'test' + i + i).next(),
				$('.' + z + 'test' + i + i).next().next(),
				$('.' + z + 'test' + i + i).next().next().next(),
				$('.' + z + 'test' + i + i).next().next().next().next()
			];
			resetSize(arr_rest);
			resetSize1(arr1_rest);
		} else {
			return false;
		}
	}
}

function reSetBlocklyFlyoutBackgroundSize() {
	setTimeout(function() {
		var blocklyFlyoutBackground = $('.blocklyFlyoutBackground').attr('d');
		if(blocklyFlyoutBackground != undefined) {
			blocklyFlyoutBackground = blocklyFlyoutBackground.split(' ');
			for(var i = 0, len = blocklyFlyoutBackground.length; i < len; i++) {
				if(parseInt(blocklyFlyoutBackground[i]) > 1000) {
					blocklyFlyoutBackground[i] = "580";
				}
				if(parseInt(blocklyFlyoutBackground[i]) < -1000) {
					blocklyFlyoutBackground[i] = "-580";
				}
			}
			blocklyFlyoutBackground = blocklyFlyoutBackground.join(' ');
			$('.blocklyFlyoutBackground').attr('d', blocklyFlyoutBackground);

		}
	}, 17)
}
//获取添加块之后需要改变的距离
function getDistance(i, z) {
//	console.log(i,z);
	var distance = 0;
	var no1 = $('.' + z + 'cover0').prev().attr('transform').split(',')[1].split(')')[0];
	if(i == 1) {
		var no = $('.' + z + 'cover1').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no - 340;
	} else if(i == 2) {
		var no3 = $('.' + z + 'cover2').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no3 - 340;
	} else if(i == 3) {
		var no4 = $('.' + z + 'cover3').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no4 - 340;
	} else if(i == 4) {
		var no5 = $('.' + z + 'cover4').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no5 - 340;
	} else if(i == 5) {
		var no6 = $('.' + z + 'cover5').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no6 - 340;
	} else if(i == 6) {
		var no7 = $('.' + z + 'cover6').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no7 - 340;
	} else if(i == 7) {
		var no8 = $('.' + z + 'cover7').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no8 - 340;
	} else if(i == 8) {
		var no9 = $('.' + z + 'cover8').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no9 - 340;
	} else if(i == 9) {
		var no10 = $('.' + z + 'cover9').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no10 - 340;
	} else if(i == 10) {
		var no11 = $('.' + z + 'cover10').prev().attr('transform').split(',')[1].split(')')[0];
		distance = no11 - 340;
	}
	return distance;
}