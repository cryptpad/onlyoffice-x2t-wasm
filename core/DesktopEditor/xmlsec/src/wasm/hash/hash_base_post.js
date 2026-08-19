    
    var HashAlgs = {
        MD2       : 0,
        MD4       : 1,
        MD5       : 2,
        RMD160    : 3,
        SHA1      : 4,
        SHA256    : 5,
        SHA384    : 6,
        SHA512    : 7,
        WHIRLPOOL : 8
    };

    var HashSizes = [
        16,
        16,
        16,
        20,
        20,
        32,
        48,
        64,
        64
    ];

	window["AscCommon"] = window.AscCommon = (window["AscCommon"] || {});
	window.AscCommon["Hash"] = window.AscCommon.Hash = {};
	window.AscCommon.Hash["HashAlgs"] = window.AscCommon.Hash.HashAlgs = HashAlgs;
	window.AscCommon.Hash["HashSizes"] = window.AscCommon.Hash.HashSizes = HashSizes;
	
	function HashObj() { this.buf; }
	HashObj.prototype["buffer"] = HashObj.prototype.buffer = function()	{ return this.buf; };
	HashObj.prototype["base64"] = HashObj.prototype.base64 = function() { return window.AscCommon.Base64.encode(this.buf); };
	HashObj.prototype["hex"] = HashObj.prototype.hex = function() { return window.AscCommon.Hex.encode(this.buf); };
	
	window.AscCommon.Hash["hash"] = window.AscCommon.Hash.hash = function(data, alg)
	{
		if (typeof alg === "string")
		{
			switch (alg)
			{
				case "md2" : alg = HashAlgs.MD2; break;
				case "md4" : alg = HashAlgs.MD4; break;
				case "md5" : alg = HashAlgs.MD5; break;
				case "rmd160" : alg = HashAlgs.RMD160; break;
				case "sha1" : alg = HashAlgs.SHA1; break;
				case "sha256" : alg = HashAlgs.SHA256; break;
				case "sha384" : alg = HashAlgs.SHA384; break;
				case "sha512" : alg = HashAlgs.SHA512; break;
				case "whirlpool" : alg = HashAlgs.WHIRLPOOL; break;
				default:
					alg = HashAlgs.SHA256;
			}
		}
		
		var arrayData = null;
		if (typeof data === "string")
			arrayData = data.toUtf8(true);
		else
			arrayData = data;
		
        var dataPointer = Module["_malloc"](arrayData.length);
        Module["HEAPU8"].set(arrayData, dataPointer);		
		var resultPointer = Module["_hash"](dataPointer, arrayData.length, alg);
		Module["_free"](dataPointer);
		
		var result = new HashObj();
		if (0 != resultPointer)
		{
			var tmp = new Uint8Array(Module["HEAPU8"].buffer, resultPointer, HashSizes[alg]);
			result.buf = new Uint8Array(tmp.length);
			result.buf.set(tmp, 0);
			Module["_free"](resultPointer);
		}
		else
		{
			result.buf = [];
		}
		
		return result;
	};
	
	window.AscCommon.Hash["hashOffice"] = window.AscCommon.Hash.hash = function(password, salt, spinCount, alg)
	{
		if (typeof alg === "string")
		{
			switch (alg)
			{
				case "md2" : alg = HashAlgs.MD2; break;
				case "md4" : alg = HashAlgs.MD4; break;
				case "md5" : alg = HashAlgs.MD5; break;
				case "rmd160" : alg = HashAlgs.RMD160; break;
				case "sha1" : alg = HashAlgs.SHA1; break;
				case "sha256" : alg = HashAlgs.SHA256; break;
				case "sha384" : alg = HashAlgs.SHA384; break;
				case "sha512" : alg = HashAlgs.SHA512; break;
				case "whirlpool" : alg = HashAlgs.WHIRLPOOL; break;
				default:
					alg = HashAlgs.SHA256;
			}
		}

		var passwordData = password.toUtf8();
		var passwordPointer = Module["_malloc"](passwordData.length);
		Module["HEAPU8"].set(passwordData, passwordPointer);

		var saltData = salt.toUtf8();
		var saltPointer = Module["_malloc"](saltData.length);
		Module["HEAPU8"].set(saltData, saltPointer);

		var resultPointer = Module["_hash2"](passwordPointer, saltPointer, spinCount, alg);

		Module["_free"](passwordPointer);
		Module["_free"](saltPointer);

		var result = new HashObj();
		if (0 != resultPointer)
		{
			var tmp = new Uint8Array(Module["HEAPU8"].buffer, resultPointer, HashSizes[alg]);
			result.buf = new Uint8Array(tmp.length);
			result.buf.set(tmp, 0);
			Module["_free"](resultPointer);
		}
		else
		{
			result.buf = [];
		}

		return result;
	};

    Module.onRuntimeInitialized = function () {
        self.onEngineInit();
    };

})(self, undefined);
