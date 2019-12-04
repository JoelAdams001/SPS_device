/*
  WiFi Web Server
 A simple web server that shows the value of the analog input pins.
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 Circuit:
 * Analog inputs attached to pins A0 through A5 (optional)
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */

#include <SPI.h>
#include <WiFiNINA.h>

  int num = 0;
  int num2 = 0;

const char page[] = R"=====(
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1">
    <title>Input Range</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
      input[type=range] {
  -webkit-appearance: none;
  margin: 12.5px 0;
  width: 100%;
}
input[type=range]:focus {
  outline: none;
}
input[type=range]::-webkit-slider-runnable-track {
  width: 100%;
  height: 5rem;
  cursor: pointer;
  transition: all 0.2s ease;
  background: linear-gradient(90deg, rgba(41,56,145,1) 12%, rgba(205,220,40,1) 35%, rgba(127,194,65,1) 68%, rgba(230,57,36,1) 88%);
}
input[type=range]::-webkit-slider-thumb {
  position: relative;
  height: 2rem;
  width: 2rem;
  clip-path: polygon(50% 0%, 0% 100%, 100% 100%);
   background-color: #be1450;
  cursor: pointer;
  z-index: 1;
  -webkit-appearance: none;
  margin-top: 6%;
}
input[type=range]:focus::-webkit-slider-runnable-track {
  background: linear-gradient(90deg, rgba(41,56,145,1) 12%, rgba(205,220,40,1) 35%, rgba(127,194,65,1) 68%, rgba(230,57,36,1) 88%);
}
input[type=range]::-moz-range-track {
  width: 100%;
  height: 5px;
  cursor: pointer;
  transition: all 0.2s ease;
  background: #cecece;
  border: 0px solid #000;
  border-radius: 0px;
}
input[type=range]::-moz-range-thumb {
  position: relative;
  border: 5px solid rgba(255, 255, 255, 0.5);
  height: 25px;
  width: 25px;
  border-radius: 100%;
  background: #01c9ca;
  cursor: pointer;
  z-index: 1;
}
input[type=range]::-ms-track {
  width: 100%;
  height: 5px;
  cursor: pointer;
  transition: all 0.2s ease;
  background: transparent;
  border-color: transparent;
  border-width: 25px 0;
  color: transparent;
}
input[type=range]::-ms-fill-lower {
  background: #cecece;
  border: 0px solid #000;
  border-radius: 0px;
}
input[type=range]::-ms-fill-upper {
  background: #cecece;
  border: 0px solid #000;
  border-radius: 0px;
}
input[type=range]::-ms-thumb {
  position: relative;
  border: 5px solid rgba(255, 255, 255, 0.5);
  height: 25px;
  width: 25px;
  border-radius: 100%;
  background: #01c9ca;
  cursor: pointer;
  z-index: 1;
}
input[type=range]:focus::-ms-fill-lower {
  background: #cecece;
}
input[type=range]:focus::-ms-fill-upper {
  background: #cecece;
}

/* Custom by @mmt-zinee */
.range {
  box-sizing: border-box;
  position: relative;
  padding: 0 50px;
  width: 100%;
}
.range[data-value='0'] .label {
  left: 0%;
}

.range[data-value='25'] .label {
  left: 25%;
}

.range[data-value='50'] .label {
  left: 50%;
}

.range[data-value='75'] .label {
  left: 75%;
}
.range[data-value='100'] .label {
  left: 100%;
}

.label {
  position: relative;
  top: 182px;
  margin-left: -40px;
  margin-bottom: 20px;
  width: 80px;
}
.label .value,.label .value2 {
  position: absolute;
  top: 26px;
  left: 0;
  right: 0;
  margin: 0 auto;
  text-align: center;
  font-size: 20px;
  font-weight: 700;
  color: black;
  z-index: 1;
}
.label .drop {
  box-sizing: content-box;
  width: 80px;
  height: 80px;
  border-radius: 80% 0 55% 50%/55% 0 80% 50%;
  background: transparent;
  -webkit-transform: rotateZ(135deg);
  transform: rotateZ(135deg);
}

.input-box {
  position: relative;
  margin: 0 -12.5px;
  height: 60px;
}
.input-box input[type="range"] {
  display: block;
  padding: 0;
  margin: 0;
  width: 100%;
  height: 60px;
}
.input-box .bar {
  position: absolute;
  bottom: 50%;
  left: 0;
  margin: 0 0 -2.5px;
  height: 5px;
  background: #01c9ca;
  z-index: 0;
}
.input-box[data-value='0'] .bar {
  margin-right: 25px;
  width: calc(0% - 25px / (100/0));
}
.input-box[data-value='25'] .bar {
  margin-right: 25px;
  width: calc(25% - 25px / (100/25));
}
.input-box[data-value='50'] .bar {
  margin-right: 25px;
  width: calc(50% - 25px / (100/50));
}
.input-box[data-value='75'] .bar {
  margin-right: 25px;
  width: calc(75% - 25px / (100/75));
}
.input-box[data-value='100'] .bar {
  margin-right: 25px;
  width: calc(100% - 25px / (100/100));
}
.low{

  position: absolute;
  top: 75px;
  left: 0px;
}
.high{

  position: absolute;
  top: 75px;
  right:0px;
}
)=====";

const char page2_1[] = R"=====(
.low .triangle,.high .triangle{
  width: 2rem;
  height: 2rem;
  background-color: #000;
  clip-path: polygon(50% 0%, 0% 100%, 100% 100%);
}
.low p{margin-top: 1px;margin-left: -7px;text-align: center;font-size: 20px;font-weight: 700;color: black;}
.high p{margin-top: 1px;margin-left: 0px;text-align: center;font-size: 20px;font-weight: 700;color: black;}

    </style>
</head>
<body>

<h1 style="text-align: center;margin: 0;">TEMPERATURE (K)</h1>
)=====";

const String page2 = R"=====(
<div class="range range1" data-value=")=====";

const String page3 = R"=====(">
  <div class="label">
    <div class="value">)=====";

const String page4 = R"=====(</div>
    <div class="drop"></div>    
  </div>
  <div class="input-box">
    <input id="input-range" type="range" min="0" max="100" value=")=====";

const String page5 = R"=====("/>
    <div class="bar"></div>
    <div class="low"><div class="triangle"></div><p>0</p></div>
    <div class="high"><div class="triangle"></div><p>100</p></div>
  </div>
</div>
<br><br><br>
<br><br><br>
<br><br><br>
<h1 style="text-align: center;margin: 0;">PRESSURE (MPa)</h1>
<div class="range range2" data-value=")=====";

const String page6 = R"=====(">
  <div class="label">
    <div class="value2">)=====";

const String page7 = R"=====(</div>
    <div class="drop"></div>    
  </div>
  <div class="input-box">
    <input id="input-range2" type="range" min="0" max="100" value=")=====";

const String page8 = R"=====("/>
    <div class="bar"></div>
    <div class="low"><div class="triangle"></div><p>0</p></div>
    <div class="high"><div class="triangle"></div><p>100</p></div>
  </div>
</div>
</body>)=====";

char ssid[] = "Note9_9132";        // your network SSID (name)
char pass[] = "exgv3061";    // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;

WiFiServer server(80);


void setup() {
  //Initialize serial and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // check for the WiFi module:
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Communication with WiFi module failed!");
    // don't continue
    while (true);
  }

  String fv = WiFi.firmwareVersion();
  if (fv < WIFI_FIRMWARE_LATEST_VERSION) {
    Serial.println("Please upgrade the firmware");
  }

  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);

    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();
  // you're connected now, so print out the status:
}


void loop() {
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          String temp = String(num);
          String pres = String(num2);
          String full = page2 + temp + page3 + temp + page4 + temp + page5 + pres + page6 + pres + page7 + pres + page8;
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 2");  // refresh the page automatically every 5 sec
          client.println();
          client.print("<!DOCTYPE HTML>");
          client.print(page);
          client.print(page2_1);
          client.println(full);
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(2000);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
          if (num < 100){
            num+= 25;
            num2+= 25;
          }
          else{
            num = 0;
            num2 = 0;
          }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
