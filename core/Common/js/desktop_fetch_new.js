var _scriptSrc = (typeof document !== 'undefined' && document.currentScript && document.currentScript.src)
    || (typeof self !== 'undefined' && self.location && self.location.href)
    || '';

Module['instantiateWasm'] = function(imports, successCallback) {

    function internal_isLocal() {
        // Resolve globals safely
        var _win = (typeof window !== 'undefined') ? window
                 : (typeof self  !== 'undefined') ? self
                 : null;
        if (!_win) return false;

        var _doc = (typeof document !== 'undefined') ? document
                 : (_win.document || null);

        // Desktop signal: either UA string (case 1) or AscDesktopEditor object (case 2)
        var ua = (_win.navigator && _win.navigator.userAgent)
               ? _win.navigator.userAgent.toLowerCase() : '';
        var isDesktop = ua.indexOf('ascdesktopeditor') >= 0 || !!_win.AscDesktopEditor;

        if (!isDesktop) return false;

        // Locality checks (same in both cases)
        if (_win.location && _win.location.protocol === 'file:') return true;
        if (_doc && _doc.currentScript && _doc.currentScript.src.indexOf('file:///') === 0) return true;

        return false;
    }

    //console.log("RESULT OF LOCAL TEST:" + internal_isLocal())
    if (internal_isLocal()) {

        var wasmAbsPath = _scriptSrc.replace(/\.js(\?.*)?$/, '.wasm').substr(7);

        //console.log("Loading WASM from:", wasmAbsPath);

        if (!wasmAbsPath) {
            console.error("Could not determine wasm absolute path; falling back to Emscripten default.");
        } else {

            // Use the custom desktop protocol path
            var wasmPath = "ascdesktop://fonts/" + wasmAbsPath;

            var xhr = new XMLHttpRequest();
            xhr.open('GET', wasmPath, true);
            xhr.responseType = 'arraybuffer';

            // Keep the original MIME/Charset overrides
            if (xhr.overrideMimeType)
                xhr.overrideMimeType('text/plain; charset=x-user-defined');
            else
                xhr.setRequestHeader('Accept-Charset', 'x-user-defined');

            xhr.onload = function() {
                //console.log("XHR onload — status:", xhr.status, "byteLength:", xhr.response && xhr.response.byteLength);
                
                if (xhr.status === 200 || (xhr.status === 0 && xhr.response && xhr.response.byteLength > 0)) {
                    //console.log("Calling WebAssembly.instantiate...");
                    WebAssembly.instantiate(xhr.response, imports)
                        .then(function(result) {
                            //console.log("WASM instantiated successfully, calling successCallback");
                            successCallback(result.instance, result.module);
                        })
                        .catch(function(e) {
                            console.error("WASM instantiation failed:", e);
                        });
                } else {
                    console.error("XHR status check failed — status:", xhr.status, "response:", xhr.response);
                }
            };

            xhr.onerror = function() {
                console.error("XHR onerror fired for:", wasmPath);
            };

            xhr.ontimeout = function() {
                console.error("XHR timed out for:", wasmPath);
            };

            /*xhr.onreadystatechange = function() {
                console.log("XHR readyState:", xhr.readyState, "status:", xhr.status);
            };*/
            
            xhr.send(null);
            return {}; // Tell Emscripten instantiation is happening asynchronously
        }
    }

    // --- Web: replicate Emscripten's default streaming path ---
    var wasmUrl = _scriptSrc.replace(/\.js(\?.*)?$/, '.wasm');
    if (typeof WebAssembly.instantiateStreaming === 'function') {
        WebAssembly.instantiateStreaming(fetch(wasmUrl), imports)
            .then(function(result) {
                successCallback(result.instance, result.module);
            })
            .catch(function(e) {
                // Streaming failed (e.g. wrong MIME type), fall back to arraybuffer
                console.warn("Streaming instantiation failed, retrying with ArrayBuffer:", e);
                fetch(wasmUrl)
                    .then(function(r) { return r.arrayBuffer(); })
                    .then(function(buf) { return WebAssembly.instantiate(buf, imports); })
                    .then(function(result) {
                        successCallback(result.instance, result.module);
                    })
                    .catch(function(e2) {
                        console.error("ArrayBuffer instantiation also failed:", e2);
                    });
            });
    } else {
        fetch(wasmUrl)
            .then(function(r) { return r.arrayBuffer(); })
            .then(function(buf) { return WebAssembly.instantiate(buf, imports); })
            .then(function(result) {
                successCallback(result.instance, result.module);
            })
            .catch(function(e) {
                console.error("WASM instantiation failed:", e);
            });
    }
    return {};
};

