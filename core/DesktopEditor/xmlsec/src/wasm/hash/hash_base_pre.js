(function(window, undefined) {

	window.messageData = null;
	window.messagePort = null;
	function onMessageEvent(data, port)
	{
	    if (data.type == "hash")
	    {
	        window.messageData = data.value;
	        window.messagePort = port;
	        if (!window.engineInit)
	        	return;
	        checkMessage();
	    }
	}

	window.onconnect = function(e)
	{
	    var port = e.ports[0];
	    port.onmessage = function(e) {
	        onMessageEvent(e.data, port);
	    }    
	};
	window.onmessage = function(e)
	{
	    onMessageEvent(e.data);
	};
	window.engineInit = false;
	window.onEngineInit = function()
	{
		window.engineInit = true;
		if (window.messageData)
			checkMessage();
	};

	function checkMessage()
	{
		var data = window.messageData;
		var res = [];

		for (var i = 0, len = data.length; i < len; i++)
        {
            res.push(AscCommon.Hash.hashOffice(data[i].password, data[i].salt, data[i].spinCount, data[i].alg).base64());
        }

		var sender = window.messagePort || window;
		sender.postMessage({ hashValue : res });
	}