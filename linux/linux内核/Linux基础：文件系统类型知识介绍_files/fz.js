document.body.oncopy = function () { 
	setTimeout( function () { 
		var text = clipboardData.getData("text");
		if (text) { 
			text = text + "\r\n���������й���վ��"+location.href; clipboardData.setData("text", text);
		} 
	}, 100 ) 
}
