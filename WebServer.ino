ESP8266WebServer esp8266_server(80); // 建立ESP8266WebServer对象，对象名称为esp8266_server 网络服务器标准http端口号为80，因此这里使用80为端口号
WebSocketsServer webSocket = WebSocketsServer(81);

/*******************************************************
 * 函数名：WebServer_init
 * 描述  ：服务器初始化
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void WebServer_init()
{
    esp8266_server.begin();
    esp8266_server.on("/", handleRoot);  //开启各网页服务
    esp8266_server.on("/pic", handlePic);
    esp8266_server.on("/time", handleTime);
    esp8266_server.on("/words", handleWords);
    esp8266_server.on("/wordsetting", handleWordsetting);
    esp8266_server.on("/animation", handleAnimation);
    esp8266_server.on("/setting", handleSetting);
    esp8266_server.onNotFound(handleNotFound);
    Serial.println("HTTP esp8266_server started");
    Serial.print("Config Web Server at ");
    Serial.println(WiFi.localIP());
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    if (MDNS.begin("esp8266"))
    {
        Serial.println("MDNS responder started");
    }
    MDNS.addService("http", "tcp", 80);
    MDNS.addService("ws", "tcp", 81);
}

/*******************************************************
 * 函数名：WebServer_run
 * 描述  ：服务运行函数
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void WebServer_run()
{
    webSocket.loop();
    esp8266_server.handleClient();
}

/*******************************************************
 * 函数名：handleRoot/handlePic/handleTime/handleWords/handleWordsetting/handleAnimation/handleSetting/handleNotFound
 * 描述  ：各网页下的处理函数
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void handleRoot()
{
    Serial.println("enter Root");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale'/><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body{height:100%;margin:0;padding:0;}body{background: rgb(255, 255, 255) url(img/index.jpg) center center;background-size: cover;position: relative;/* 相对位置 */}.container{position: absolute;/* 绝对位置 */top: 50%;text-align: center;width: 100%;transform: translateY(-50%);/* 将div元素上移至自身高度的50% */}h1{line-height: 90px;color: royalblue;font-size: 50px;}p{line-height: 80px;color: royalblue;font-size: 22px;}.btn{width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;/* 设置其上下边距：30px 左右边距：自动 */border-radius: 10px;/* 给按钮增加圆角样式 */transition: 1s;}.btn:hover{background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 50px auto;}</style></head><body><div class='container'><h1>欢迎使用像素灯</h1><p>请选择要显示的内容</p><form  action='/pic' method='POST'><input class='btn' type='submit' value='图片'></form><form  action='/time' method='POST'><input class='btn' type='submit' value='时钟'></form><form  action='/words' method='POST'><input class='btn' type='submit' value='文字'></form><form  action='/animation' method='POST'><input class='btn' type='submit' value='动画'></form><form  action='/setting' method='POST'><input class='btn' type='submit' value='配置'></form></div></body></html>"));
}

void handlePic()
{ //处理网站根目录“/pic”的访问请求
    Serial.println("enter Pic");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) url(img/index.jpg) center center;background-size: cover;position: relative;}.container {position: absolute;top: 50%;text-align: center;width: 100%;transform: translateY(-50%);}div {margin: 10px}h1 {line-height: 150px;color: royalblue;font-size: 50px;}p {line-height: 80px;color: royalblue;font-size: 22px;margin: 40px 0px 0px 0px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 30px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style>"
                                            "</head><body><div class='container'><h1>选择一个图案</h1><img style='transform:scale(2)' id='emojis' onclick='clickEmoji(event);'src='data:image/png;base64,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'>"
                                            "<p id='out'></p> <canvas style='transform:scale(4)' id='emoji' width='8' height='8'></canvas><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};function clickEmoji(e) {var xo = 3;var yo = 3;var xs = 13;var ys = 12;var x = e.offsetX;var y = e.offsetY;var c = Math.round((x - xo - 4) / xs);var r = Math.round((y - yo - 4) / ys);document.getElementById('out').innerText = 'Selected [' + (c + 1) + ', ' + (r + 1) + ']';var img = document.getElementById('emojis');var ce = document.getElementById('emoji');var ctx = ce.getContext('2d');ctx.drawImage(img, -(xo + (xs * c)), -(yo + (ys * r)), 131, 122);var index = 'p' + c + '' + r;console.log('index: ' + index);connection.send(index);}</script><form action='/' method='POST'><input class='btn' type='submit' value='返回主页'></form></div></body></html>"));
}

void handleTime()
{ //处理网站根目录“/time”的访问请求
    Serial.println("enter Time");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) center center;background-size: cover;position: relative;}.container {position: absolute;top: 50%;text-align: center;width: 100%;transform: translateY(-50%);}h1 {line-height: 150px;color: royalblue;font-size: 50px;margin: 0px;}p {line-height: 50px;color: royalblue;font-size: 22px;margin: 20px 0px 30px 0px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style></head><body><div class='container'><h1>选择时钟风格</h1><form action='/' method='POST'><img style='transform:scale(8)'src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABEAAAAICAIAAACQ1oP+AAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAEnQAABJ0Ad5mH3gAAAB5SURBVChTfZDdDYAwCITBKXx2HqMbOJwbGF1Hn92iHr1KaPz5kpKjcIEgX6SUinqgeN3SIx7jln8shYZH1aoynzK1Fh0aXCBSlDlojd3gx2welr3p9jdM0ee7VUQbNvQlfQKpdgPRloVGA0Z5ug9rdQMKQP3K561FLvvDRmbEzBKCAAAAAElFTkSuQmCC'><p><input type='radio' name='style' value='1' onclick='clickRad();' checked />闪烁风格</p><img style='transform:scale(8)' src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAICAIAAAB/FOjAAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAEnQAABJ0Ad5mH3gAAABOSURBVChTtY3BCQAgDAM7i/M4pRu4lWOYchL16cMjhBQTjGdKr8gnIWnjcgT0vEz3s0tCmRI94ZCw8QxdjeOr1RMOggHSeeYNAzn6TMQEDQs5aFY3rzoAAAAASUVORK5CYII='><p><input type='radio' name='style' value='2' onclick='clickRad();' /> 摇摆风格</p><img style='transform:scale(4)'src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAEnQAABJ0Ad5mH3gAAAB+SURBVDhPY1Ta6POfAQnc898CZaECoDowjS7PBKXJBoxAjOICdJtgfBignQtw+REGaBcGQJNRwgAGcIUBDMDkqRgLi16AKTiIk4DQuMShgAouWPQC4gJ0G9FswuUSil2AMABkA7otyABkI7qrgICKsQAD6GGAw+8wQKELGBgAM/ExE0OFvNIAAAAASUVORK5CYII='><p><input type='radio' name='style' value='3' onclick='clickRad();' /> 静态风格</p><img style='transform:scale(4)'src='data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAJcEhZcwAAEnQAABJ0Ad5mH3gAAAB2SURBVDhPY2RgYPgPxAz//4MpogEjI0grAwMTmKQAMAJtBlsNM5FYAHMxDVyw6AWExgXiJMAU9VygtNEHbNS9j3PAAjAb4C7BwaehC9ABzAUwAHXJ/1hxME3DdIArNqgeBjhdQABQzwVADDYKZiKxgEq5kYEBAFguO/9DoL8kAAAAAElFTkSuQmCC'><p><input type='radio' name='style' value='4' onclick='clickRad();' /> 表盘风格</p></form></p><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};var oBtn = document.getElementById('btn');var oStyle = document.getElementsByName('style');function clickRad() {for (var i = 0; i < oStyle.length; i++) { if (oStyle[i].checked) {    var styleNum = 't' + parseInt(oStyle[i].value).toString(16);    console.log('Style: ' + styleNum);    connection.send(styleNum);  }}}</script><form action='/' method='POST'><input class='btn' type='submit' value='返回主页'></form></div></body></html>"));
}

void handleWords()
{ //处理网站根目录“/words”的访问请求
    Serial.println("enter Words");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) center center;background-size: cover;position: relative;}.container {position: absolute;top: 50%;text-align: center;width: 100%;transform: translateY(-50%);}h1 {line-height: 150px;color: royalblue;font-size: 50px;margin: 0px;}p {line-height: 50px;color: royalblue;font-size: 22px;margin: 5px;}textarea {line-height: 30px;width: 300px;height: 200px;color: royalblue;font-size: 22px;border-radius: 10px;margin: 5px;}select {line-height: 30px;width: 190px;height: 40px;font-size: 20px;margin: 10px auto;border-radius: 5px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style></head><body><div class='container'><h1>像素屏文本显示</h1><textarea id='text' placeholder='请输入显示内容'></textarea><p>选择字体：<select><option name='font' value='0'>Apple4x6(字符全)</option><option name='font' value='1'>Apple5x7(字符全)</option><option name='font' value='2'>Apple6x10(字符全，偏大)</option><option name='font' value='3'>Pix5x7(0~9 A~Z a~z)</option><option name='font' value='4'>Atari8x8(0~9 A~Z)</option><option name='font' value='5'>Undertale8x8(字符全)</option><option name='font' value='6'>Blodnum8x8(字符全)</option><option name='font' value='7' selected>Cnfont8x8(中英文,含中文必选)</option></select></p><p>颜色模式：<select><option name='color' value='0' selected>纯色</option><option name='color' value='1'>彩虹色</option><option name='color' value='2'>渐变色</option><option name='color' value='3'>调色板</option></select></p><p>显示方式：<select><option name='showmode' value='0' selected>滚动播放</option><option name='showmode' value='1'>快闪模式</option></select><br/><a href='/wordsetting'>高级设置</a></p><input id='btn' class='btn' type='submit' value='确认' onclick='clickOk();'><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};var oBtn = document.getElementById('btn');var oFont = document.getElementsByName('font');var oColor = document.getElementsByName('color');var oShowmode = document.getElementsByName('showmode');var oText = document.getElementById('text');var oMessage;function clickOk() {for (var i = 0; i < oFont.length; i++) {if (oFont[i].selected) { oMessage = 'w' + parseInt(oFont[i].value).toString(16);}}for (var i = 0; i < oColor.length; i++) {if (oColor[i].selected) { oMessage = oMessage + parseInt(oColor[i].value).toString(16);}}for (var i = 0; i < oShowmode.length; i++) {if (oShowmode[i].selected) { oMessage = oMessage + parseInt(oShowmode[i].value).toString(16);}}oMessage = oMessage + oText.value;console.log('oMessage: ' + oMessage);connection.send(oMessage);}</script><form action='/' method='POST'><input class='btn' type='submit' value='返回主页'></form></div></body></html>"));
}

void handleWordsetting()
{
    Serial.println("enter Wordsetting");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) center center;background-size: cover;position: relative;}.container {position: absolute;text-align: center;width: 100%;}h1 {line-height: 80px;color: royalblue;font-size: 50px;margin: 0px;}h2 {line-height: 40px;color: royalblue;font-size: 30px;margin: 0px;}p {line-height: 50px;color: royalblue;font-size: 22px;margin: 5px;}textarea {line-height: 30px;width: 300px;height: 200px;color: royalblue;font-size: 22px;border-radius: 10px;margin: 5px;}input{line-height: 30px;width: 50px;height: 30px;font-size: 18px;border-radius: 5px;margin: 5px;}select {line-height: 30px;width: 120px;height: 30px;font-size: 18px;margin: 10px auto;border-radius: 5px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style></head><body><div class='container'><h1>文本显示配置</h1><form><p>设置类型：<select><option name='settype' value='0' selected>滑动背景</option><option name='settype' value='1'>滑动字体</option><option name='settype' value='2'>闪烁背景</option><option name='settype' value='3'>闪烁字体</option></select></p><p>颜色类型：<select><option name='color' value='0' selected>纯色</option><option name='color' value='1'>彩虹色</option><option name='color' value='2'>渐变色</option><option name='color' value='3'>调色板</option></select></p><p>纯色 R<input id='solid_R' type='text' placeholder='0~255'/> G<input id='solid_G' type='text' placeholder='0~255'/> B<input id='solid_B' type='text' placeholder='0~255'/></p><p>彩虹色 色调值<input id='rainbow_initialhue' type='text' placeholder='0~255'/> 色调差<input id='rainbow_deltahue' type='text' placeholder='0~255'/></p><p>渐变色 开始RGB<input id='gradient_startcolor_R' type='text' placeholder='0~255'/> <input id='gradient_startcolor_G' type='text' placeholder='0~255'/> <input id='gradient_startcolor_B' type='text' placeholder='0~255'/></p><p>渐变色 结束RGB<input id='gradient_endcolor_R' type='text' placeholder='0~255'/> <input id='gradient_endcolor_G' type='text' placeholder='0~255'/> <input id='gradient_endcolor_B' type='text' placeholder='0~255'/></p><p>色盘风格 <select><option name='palette_pal' value='0' selected>云朵渐变</option><option name='palette_pal' value='1'>火山渐变</option><option name='palette_pal' value='2'>海洋渐变</option><option name='palette_pal' value='3'>树林渐变</option><option name='palette_pal' value='4'>彩虹渐变</option><option name='palette_pal' value='5'>彩带渐变</option><option name='palette_pal' value='6'>派对渐变</option><option name='palette_pal' value='6'>热浪渐变</option></select>首色序号<input id='palette_startindex' type='text' placeholder='0'/></p><p>色盘色彩差<input id='palette_incindex' type='text' placeholder='0~255'/> 线性过渡效果 <select style='width:50px'><option name='palette_linearblend' value='0' selected>是</option><option name='palette_linearblend' value='1'>否</option></select></p><h2>滑动显示配置</h2><p>滑动速度（ms/像素）：<input id='slipshow_strspeed' type='text' placeholder='80'/></p><p>字符间隔（像素）：<input id='slipshow_cspace' type='text' placeholder='8'/></p><h2>闪烁显示配置</h2><p>闪烁速度（ms/次）：<input id='twinkleshow_twkspeed' type='text' placeholder='80'/></p></form><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};				function clickOk() {var oSettype = document.getElementsByName('settype');for (var i = 0; i < oSettype.length; i++) {if (oSettype[i].selected) {	oMessage = '{\"settype\":' + parseInt(oSettype[i].value).toString(16);}}var oColor = document.getElementsByName('color');for (var i = 0; i < oColor.length; i++) {if (oColor[i].selected) {	oMessage = oMessage + ',\"colortype\":' + parseInt(oColor[i].value).toString(16);}}var S_R = document.getElementById('solid_R').value;var S_G = document.getElementById('solid_G').value;var S_B = document.getElementById('solid_B').value;oMessage = oMessage + ',\"solid\":[' + parseInt(S_R? S_R : 999);oMessage = oMessage + ',' + parseInt(S_G? S_G : 999);oMessage = oMessage + ',' + parseInt(S_B? S_B : 999);var R_I = document.getElementById('rainbow_initialhue').value;var R_D = document.getElementById('rainbow_deltahue').value;oMessage = oMessage + '],\"rainbow\":{\"initialhue\":' + parseInt(R_I? R_I : 999);oMessage = oMessage + ',\"deltahue\":' + parseInt(R_D? R_D : 999);var GS_R = document.getElementById('gradient_startcolor_R').value;var GS_G = document.getElementById('gradient_startcolor_G').value;	var GS_B = document.getElementById('gradient_startcolor_B').value;	oMessage = oMessage + '},\"gradient\":{\"startcolor\":[' + parseInt(GS_R? GS_R : 999);oMessage = oMessage + ',' + parseInt(GS_G? GS_G : 999);oMessage = oMessage + ',' + parseInt(GS_B? GS_B : 999);var GE_R = document.getElementById('gradient_endcolor_R').value;var GE_G = document.getElementById('gradient_endcolor_G').value;	var GE_B = document.getElementById('gradient_endcolor_B').value;oMessage = oMessage + '],\"endcolor\":[' + parseInt(GE_R? GE_R : 999);oMessage = oMessage + ',' + parseInt(GE_G? GE_G : 999);oMessage = oMessage + ',' + parseInt(GE_B? GE_B : 999);var oPal = document.getElementsByName('palette_pal');for (var i = 0; i < oPal.length; i++) {if (oPal[i].selected) {	oMessage = oMessage + ']},\"palette\":{\"pal\":' + parseInt(oPal[i].value).toString(16);}}var P_S = document.getElementById('palette_startindex').value;var P_I = document.getElementById('palette_incindex').value;oMessage = oMessage + ',\"startindex\":' + parseInt(P_S? P_S : 999);oMessage = oMessage + ',\"incindex\":' + parseInt(P_I? P_I : 999);var oLine = document.getElementsByName('palette_linearblend');for (var i = 0; i < oLine.length; i++) {if (oLine[i].selected) {	oMessage = oMessage + ',\"linearblend\":' + parseInt(oLine[i].value).toString(16);}}					var S_S = document.getElementById('slipshow_strspeed').value;var S_C = document.getElementById('slipshow_cspace').value;var T_T = document.getElementById('twinkleshow_twkspeed').value;oMessage = oMessage + '},\"slipshow\":{\"strspeed\":' + parseInt(S_S? S_S : 999);oMessage = oMessage + ',\"cspace\":' + parseInt(S_C? S_C : 999);oMessage = oMessage + '},\"twinkleshow\":{\"twkspeed\":' + parseInt(T_T? T_T : 999);oMessage = oMessage + '}}';console.log('oMessage: ' + oMessage);connection.send(oMessage);}</script><input class='btn' type='submit' value='配置' onclick='clickOk();'><form action='/words' method='POST'><input class='btn' type='submit' value='返回文字'></form></div></body></html>"));
}

void handleAnimation()
{ //处理网站根目录“/animation”的访问请求
    Serial.println("enter Animation");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) center center;background-size: cover;position: relative;}.container {position: absolute;top: 50%;text-align: center;width: 100%;transform: translateY(-50%);}h1 {line-height: 150px;color: royalblue;font-size: 50px;margin: 0px;}p {line-height: 50px;color: royalblue;font-size: 22px;margin: 20px 0px 30px 0px;}select {line-height: 30px;width: 190px;height: 40px;font-size: 20px;margin: 10px auto;border-radius: 5px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style></head><body><div class='container'><h1>动态画面</h1><p>动态类型：<select><option name='anim' value='00' selected>RainbowColors_p(L)</option><option name='anim' value='01' >RainbowStripeColors_p(N)</option><option name='anim' value='02' >RainbowStripeColors_p(L)</option><option name='anim' value='03' >PurpleAndGreenPalette(L)</option><option name='anim' value='04' >TallyRandomPalette(L)</option><option name='anim' value='05' >BlackAndWhiteStripedPalette(N)</option><option name='anim' value='06' >BlackAndWhiteStripedPalette(L)</option><option name='anim' value='07' >CloudColors_p(L)</option><option name='anim' value='08' >PartyColors_p(L)</option><option name='anim' value='09' >RedWhiteBluePalette_p(N)</option><option name='anim' value='10' >RedWhiteBluePalette_p(L)</option></select></p><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};function clickOk() {var oAnim = document.getElementsByName('anim');for (var i = 0; i < oAnim.length; i++) {if (oAnim[i].selected) { var oMessage = 'a' + oAnim[i].value;}}console.log('oMessage: ' + oMessage);connection.send(oMessage);}</script><input class='btn' type='submit' value='设置' onclick='clickOk();'><form action='/' method='POST'><input class='btn' type='submit' value='返回主页'></form></div></body></html>"));
}

void handleSetting()
{ //处理网站根目录“/setting”的访问请求
    Serial.println("enter Setting");
    esp8266_server.send(200, "text/html", F("<!DOCTYPE html><html lang='cn'><head><meta name='viewport' content='width=device-width,initial-scale=1 .0 user-scale' /><meta charset='utf-8' /><title>像素灯网页配置</title><style>html,body {height: 100%;margin: 0;padding: 0;}body {background: rgb(255, 255, 255) center center;background-size: cover;position: relative;}.container {position: absolute;top: 50%;text-align: center;width: 100%;transform: translateY(-50%);}h1 {line-height: 150px;color: royalblue;font-size: 50px;margin: 0px;}p {line-height: 50px;color: royalblue;font-size: 22px;margin: 20px 0px 30px 0px;}input {line-height: 30px;width: 150px;height: 15px;border-radius: 5px;margin: 2px;}.btn {width: 150px;height: 60px;background-color: #7cacae;color: #fff;font-size: 24px;line-height: 60px;margin: 10px auto;border-radius: 10px;transition: 1s;}.btn:hover {background-color: royalblue;width: 300px;height: 100px;line-height: 100px;font-size: 36px;margin: 100px auto;}</style></head><body><div class='container'><h1>配置</h1> <p>亮度：<input id='bt' type='range' min='0' max='255' step='1' oninput='sendBrightness();'/> </p><script>var connection = new WebSocket('ws://' + location.hostname + ':81/', ['arduino']);connection.onopen = function() {connection.send('Connect ' + new Date());};connection.onerror = function(error) {console.log('WebSocket Error ', error);};connection.onmessage = function(e) {console.log('Server: ', e.data);};function sendBrightness() {var Obrightness = document.getElementById('bt').value;var oMessage = 's';if (Obrightness.length == 1) { oMessage = oMessage + '00';} else if (Obrightness.length == 2) {  oMessage = oMessage + '0';}oMessage = oMessage + parseInt(Obrightness ? Obrightness : 999);console.log('oMessage: ' + oMessage);connection.send(oMessage);}</script><form action='/' method='POST'><input class='btn' type='submit' value='返回主页'></form></div></body></html>"));
}

void handleNotFound()
{                                                             // 当浏览器请求的网络资源无法在服务器找到时，
    esp8266_server.send(404, "text/plain", "404: Not found"); // NodeMCU将调用此函数。
}

/*******************************************************
 * 函数名：webSocketEvent
 * 描述  ：处理网页webSocket数据，事件回调函数
 * 参数  ：
 *         @num
 *         @type
 *         @payload
 *         @length
 * 返回值：无
 **********************************************************/
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    switch (type)
    {
    case WStype_DISCONNECTED:
        Serial.printf("[%u] Disconnected!\n", num);
        break;
    case WStype_CONNECTED:
    {
        IPAddress ip = webSocket.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
        webSocket.sendTXT(num, "Connected"); // send message to client
    }
    break;
    case WStype_TEXT:
    {
        Serial.printf("[%u] get Text: %s\n", num, payload);
        if(((char *)payload)[0] == '{'||((char *)payload)[0] == 's') 
        {
          strcpy(settingMessage,(char *)payload);
          if (settingMessage[0] == 's')
          {
             int bt= ((int)settingMessage[1]-48)*100+((int)settingMessage[2]-48)*10+(int)settingMessage[3]-48;
             if(bt>=0&&bt<=255) Brightness =bt;
             FastLED.setBrightness(Brightness);
             FastLED.show();
          }
          else if(settingMessage[0] == '{')
          {
             handleSettingMessage();
          }
        }
        else if (((char *)payload)[0] != 'C') 
        {
          strcpy(socketMessage, (char *)payload);
          if (socketMessage[0] == 'p')
          {
              wordShowkMode = 0;
              clockMode = 0;
              aniMode = 0;
              FastLED.setBrightness(Brightness);
              SetEmoji(((int)socketMessage[2]) - 47, ((int)socketMessage[1]) - 47);
              FastLED.show();
          }
          else if (socketMessage[0] == 't')
          {
              wordShowkMode = 0;
              aniMode = 0;
              FastLED.setBrightness(Brightness);
              clockMode = ((int)socketMessage[1]) - 48 ;
              //if(socketMessage[1] != '1') FastLED.setBrightness(Brightness);
          }
          else if (socketMessage[0] == 'w')
          {
              clockMode = 0;
              aniMode = 0;
              FastLED.setBrightness(Brightness);
              wordShowkMode = ((int)socketMessage[3]) - 47 ;
              message_str = (char *)socketMessage + 4;
              if(wordShowkMode == 2) //2 闪烁模式
              {
                  strstwinkleconfig.cfont = ((int)socketMessage[1]) - 48;
                  strstwinkleconfig.font_color_func = ((int)socketMessage[2]) - 48;
                  setTwinkleStrLen(message_str,strlen(message_str));
              }
              else if(wordShowkMode == 1)  //滚动模式
              {   
                  strslipconfig.cfont = ((int)socketMessage[1]) - 48;
                  strslipconfig.font_color_func = ((int)socketMessage[2]) - 48;
                  strslipconfig.cspace = fontattribute[strslipconfig.cfont].font_test_space;
                  setSlipStrLen(message_str,strlen(message_str)); 
              }
          }
          else if(socketMessage[0] == 'a')
          {
              anm_style = ((int)socketMessage[1]-48)*10+(int)socketMessage[2]-48;
              wordShowkMode = 0;
              clockMode = 0;
              FastLED.setBrightness(Brightness);
              anm_colorIndex = 0;
              aniMode = 1;
              if( anm_style == 0)  { anm_currentPalette = RainbowColors_p;         anm_currentBlending = LINEARBLEND; }
              if( anm_style == 1)  { anm_currentPalette = RainbowStripeColors_p;   anm_currentBlending = NOBLEND;  }
              if( anm_style == 2)  { anm_currentPalette = RainbowStripeColors_p;   anm_currentBlending = LINEARBLEND; }
              if( anm_style == 3)  { SetupPurpleAndGreenPalette();             anm_currentBlending = LINEARBLEND; }
              if( anm_style == 4)  { SetupTotallyRandomPalette();              anm_currentBlending = LINEARBLEND; }
              if( anm_style == 5)  { SetupBlackAndWhiteStripedPalette();       anm_currentBlending = NOBLEND; }
              if( anm_style == 6)  { SetupBlackAndWhiteStripedPalette();       anm_currentBlending = LINEARBLEND; }
              if( anm_style == 7)  { anm_currentPalette = CloudColors_p;           anm_currentBlending = LINEARBLEND; }
              if( anm_style == 8)  { anm_currentPalette = PartyColors_p;           anm_currentBlending = LINEARBLEND; }
              if( anm_style == 9)  { anm_currentPalette = myRedWhiteBluePalette_p; anm_currentBlending = NOBLEND;  }
              if( anm_style == 10)  { anm_currentPalette = myRedWhiteBluePalette_p; anm_currentBlending = LINEARBLEND; }
          }
          count = 0;
        }
    }
    break;
    }
}

/*******************************************************
 * 函数名：handleSettingMessage
 * 描述  ：文字配置信息处理，在网页采用json格式发送配置信息，因此用json库进行处理
 * 参数  ：无
 * 返回值：无
 **********************************************************/
void handleSettingMessage()
{
    // size_t inputLength; (optional)

    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, settingMessage);

    if (error) {
    Serial.print(F("deserializeJson() failed: "));
    Serial.println(error.f_str());
    return;
    }

    int settype = doc["settype"]; // 0
    int colortype = doc["colortype"]; // 0

    JsonArray solid = doc["solid"];
    int solid_R = solid[0]; // 255
    int solid_G = solid[1]; // 255
    int solid_B = solid[2]; // 255

    int rainbow_initialhue = doc["rainbow"]["initialhue"]; // 255
    int rainbow_deltahue = doc["rainbow"]["deltahue"]; // 255

    JsonArray gradient_startcolor = doc["gradient"]["startcolor"];
    int gradient_startcolor_R = gradient_startcolor[0]; // 255
    int gradient_startcolor_G = gradient_startcolor[1]; // 255
    int gradient_startcolor_B = gradient_startcolor[2]; // 255

    JsonArray gradient_endcolor = doc["gradient"]["endcolor"];
    int gradient_endcolor_R = gradient_endcolor[0]; // 255
    int gradient_endcolor_G = gradient_endcolor[1]; // 255
    int gradient_endcolor_B = gradient_endcolor[2]; // 255

    JsonObject palette = doc["palette"];
    int palette_pal = palette["pal"]; // 0
    int palette_startindex = palette["startindex"]; // 0
    int palette_incindex = palette["incindex"]; // 0
    int palette_linearblend = palette["linearblend"]; // 0

    int slipshow_strspeed = doc["slipshow"]["strspeed"]; // 80
    int slipshow_cspace = doc["slipshow"]["cspace"]; // 8

    int twinkleshow_twkspeed = doc["twinkleshow"]["twkspeed"]; // 300

    if(settype == 0)
    {
        strslipconfig.bg_color_func = colortype;
        if(solid_R!=999&&solid_G!=999&&solid_B!=999)
            strslipconfig.bg_sc_var.color=CRGB(solid_R,solid_G,solid_B);
        rainbow_initialhue==999? :strslipconfig.bg_rc_var.initialhue=rainbow_initialhue;
        rainbow_deltahue==999? :strslipconfig.bg_rc_var.deltahue=rainbow_deltahue;
        if(gradient_startcolor_R!=999&&gradient_startcolor_G!=999&&gradient_startcolor_B!=999)
            strslipconfig.bg_gc_var.startcolor=CRGB(gradient_startcolor_R,gradient_startcolor_G,gradient_startcolor_B);
        if(gradient_endcolor_R!=999&&gradient_endcolor_G!=999&&gradient_endcolor_B!=999)
            strslipconfig.bg_gc_var.endcolor=CRGB(gradient_endcolor_R,gradient_endcolor_G,gradient_endcolor_B);
        switch (palette_pal)
        {
        case 0:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)CloudColors_p;
            break;
        case 1:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)LavaColors_p;
            break;
        case 2:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)OceanColors_p;
            break;
        case 3:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)ForestColors_p;
            break;
        case 4:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)RainbowColors_p;
            break;
        case 5:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)RainbowStripeColors_p;
            break;
        case 6:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)PartyColors_p;
            break;
        case 7:
            strslipconfig.bg_pc_var.pal=(CRGBPalette16)HeatColors_p;
            break;
        default:
            break;
        }
        palette_startindex==999? :strslipconfig.bg_pc_var.startIndex=palette_startindex;
        palette_incindex==999? :strslipconfig.bg_pc_var.incIndex=palette_incindex;
        if(palette_linearblend==0) strslipconfig.bg_pc_var.blendType=LINEARBLEND;
        else strslipconfig.bg_pc_var.blendType=NOBLEND;
    }
    else if(settype == 1)
    {
        strslipconfig.font_color_func = colortype;
        if(solid_R!=999&&solid_G!=999&&solid_B!=999)
            strslipconfig.font_sc_var.color=CRGB(solid_R,solid_G,solid_B);
        rainbow_initialhue==999? :strslipconfig.font_rc_var.initialhue=rainbow_initialhue;
        rainbow_deltahue==999? :strslipconfig.font_rc_var.deltahue=rainbow_deltahue;
        if(gradient_startcolor_R!=999&&gradient_startcolor_G!=999&&gradient_startcolor_B!=999)
            strslipconfig.font_gc_var.startcolor=CRGB(gradient_startcolor_R,gradient_startcolor_G,gradient_startcolor_B);
        if(gradient_endcolor_R!=999&&gradient_endcolor_G!=999&&gradient_endcolor_B!=999)
            strslipconfig.font_gc_var.endcolor=CRGB(gradient_endcolor_R,gradient_endcolor_G,gradient_endcolor_B);
        switch (palette_pal)
        {
        case 0:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)CloudColors_p;
            break;
        case 1:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)LavaColors_p;
            break;
        case 2:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)OceanColors_p;
            break;
        case 3:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)ForestColors_p;
            break;
        case 4:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)RainbowColors_p;
            break;
        case 5:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)RainbowStripeColors_p;
            break;
        case 6:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)PartyColors_p;
            break;
        case 7:
            strslipconfig.font_pc_var.pal=(CRGBPalette16)HeatColors_p;
            break;
        default:
            break;
        }
        palette_startindex==999? :strslipconfig.font_pc_var.startIndex=palette_startindex;
        palette_incindex==999? :strslipconfig.font_pc_var.incIndex=palette_incindex;
        if(palette_linearblend==0) strslipconfig.font_pc_var.blendType=LINEARBLEND;
        else strslipconfig.font_pc_var.blendType=NOBLEND;
    }
    else if(settype == 2)
    {
        strstwinkleconfig.bg_color_func = colortype;
        if(solid_R!=999&&solid_G!=999&&solid_B!=999)
            strstwinkleconfig.bg_sc_var.color=CRGB(solid_R,solid_G,solid_B);
        rainbow_initialhue==999? :strstwinkleconfig.bg_rc_var.initialhue=rainbow_initialhue;
        rainbow_deltahue==999? :strstwinkleconfig.bg_rc_var.deltahue=rainbow_deltahue;
        if(gradient_startcolor_R!=999&&gradient_startcolor_G!=999&&gradient_startcolor_B!=999)
            strstwinkleconfig.bg_gc_var.startcolor=CRGB(gradient_startcolor_R,gradient_startcolor_G,gradient_startcolor_B);
        if(gradient_endcolor_R!=999&&gradient_endcolor_G!=999&&gradient_endcolor_B!=999)
            strstwinkleconfig.bg_gc_var.endcolor=CRGB(gradient_endcolor_R,gradient_endcolor_G,gradient_endcolor_B);
        switch (palette_pal)
        {
        case 0:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)CloudColors_p;
            break;
        case 1:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)LavaColors_p;
            break;
        case 2:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)OceanColors_p;
            break;
        case 3:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)ForestColors_p;
            break;
        case 4:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)RainbowColors_p;
            break;
        case 5:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)RainbowStripeColors_p;
            break;
        case 6:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)PartyColors_p;
            break;
        case 7:
            strstwinkleconfig.bg_pc_var.pal=(CRGBPalette16)HeatColors_p;
            break;
        default:
            break;
        }
        palette_startindex==999? :strstwinkleconfig.bg_pc_var.startIndex=palette_startindex;
        palette_incindex==999? :strstwinkleconfig.bg_pc_var.incIndex=palette_incindex;
        if(palette_linearblend==0) strstwinkleconfig.bg_pc_var.blendType=LINEARBLEND;
        else strstwinkleconfig.bg_pc_var.blendType=NOBLEND;
    }
    else if(settype == 3)
    {
        strstwinkleconfig.font_color_func = colortype;
        if(solid_R!=999&&solid_G!=999&&solid_B!=999)
            strstwinkleconfig.font_sc_var.color=CRGB(solid_R,solid_G,solid_B);
        rainbow_initialhue==999? :strstwinkleconfig.font_rc_var.initialhue=rainbow_initialhue;
        rainbow_deltahue==999? :strstwinkleconfig.font_rc_var.deltahue=rainbow_deltahue;
        if(gradient_startcolor_R!=999&&gradient_startcolor_G!=999&&gradient_startcolor_B!=999)
            strstwinkleconfig.font_gc_var.startcolor=CRGB(gradient_startcolor_R,gradient_startcolor_G,gradient_startcolor_B);
        if(gradient_endcolor_R!=999&&gradient_endcolor_G!=999&&gradient_endcolor_B!=999)
            strstwinkleconfig.font_gc_var.endcolor=CRGB(gradient_endcolor_R,gradient_endcolor_G,gradient_endcolor_B);
        switch (palette_pal)
        {
        case 0:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)CloudColors_p;
            break;
        case 1:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)LavaColors_p;
            break;
        case 2:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)OceanColors_p;
            break;
        case 3:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)ForestColors_p;
            break;
        case 4:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)RainbowColors_p;
            break;
        case 5:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)RainbowStripeColors_p;
            break;
        case 6:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)PartyColors_p;
            break;
        case 7:
            strstwinkleconfig.font_pc_var.pal=(CRGBPalette16)HeatColors_p;
            break;
        default:
            break;
        }
        palette_startindex==999? :strstwinkleconfig.font_pc_var.startIndex=palette_startindex;
        palette_incindex==999? :strstwinkleconfig.font_pc_var.incIndex=palette_incindex;
        if(palette_linearblend==0) strstwinkleconfig.font_pc_var.blendType=LINEARBLEND;
        else strstwinkleconfig.font_pc_var.blendType=NOBLEND;
    }
    slipshow_strspeed==999? :strslipconfig.strspeed=slipshow_strspeed;
    slipshow_cspace==999? :strslipconfig.cspace=slipshow_cspace;

    twinkleshow_twkspeed==999? :strstwinkleconfig.twkspeed=twinkleshow_twkspeed;
}
