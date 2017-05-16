
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "setup.h"
#include "webserver.h"
#include "state.h"
#include "utils.h"
#include "temp.h"

Setup _setup;
WebServer* _ws;
State* state=new State(&_setup);
Parameters work;
Settings stSettings;
void setup() {
    //Buttons setup
  pinMode(D(5),INPUT);
  pinMode(D(6),INPUT);
  
  Serial.begin(9600);
  //stSettings=_setup.readSettings();
  work.mode=digitalRead(D(5));
  if (digitalRead(D(6))==1){
    //Reset settings to default
    Serial.println("Reset settings to default");
    stSettings=_setup.resetSettings();
  }
  //Settings stSettings=_setup.resetSettings();
//  _setup.writeSettings(stSettings);

    Serial.println("SID:"+stSettings.wifiSid);
    Serial.println("PASS:"+stSettings.wifiPass);
    //WiFi.begin(stringToChar(stSettings.wifiSid),stringToChar(stSettings.wifiPass));
    //WiFi.begin("DL","bgt61Yhn");
    WiFi.begin("dl2","bgt61Yhn");
    while (WiFi.status()!=WL_CONNECTED){
      delay(500);
      Serial.print(".");
    }
    Serial.println(WiFi.localIP());

  if (work.mode==0){
    Serial.println("Mode Web client");
    Serial.println("Www host:"+stSettings.www);
    Serial.println("Www port:"+String(stSettings.port));
    _ws=new WebServer(state);
  }else{
    Serial.println("Mode Web server");
    _ws=new WebServer(state);
  }
}

void loop() {
  //_fs.dir();
  //Settings _settings=_setup.readSettings();
  //_setup.toSerial(_settings);
  //delay(125000);
//  getTemp();
  if (work.count%5==0){    
      getTemp();
      work.tInt=t1;
      work.tExt=t2;
      work.b1=digitalRead(D(5));
      work.b2=digitalRead(D(6));
      state->setParameters(work);
  }  
  if (work.mode==0){
    if (work.count%5==0){
      Serial.print("+");
      HTTPClient http;
      http.begin("http://www.samogon-on.ru/indexpstj.php");
      http.addHeader("Content-Type", "application/json");
      int code=http.POST(state->getJsonParameters());
      //http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      //int code=http.POST(String("ws1=0&ts1="+String(work.tInt)+"&ts2="+String(work.tExt)+"&genid=UID-TPL001"));      
      Serial.println(String(work.count)+" "+String(code));
      //http.writeToStream(&Serial);
      http.end();    
   //   delay(60000);
    }else{
      for (int i=0;i<60;i++){
        _ws->handleRequest();
        delay(100);
      }
      
      //delay(6000);
    }
  }else{
    _ws->handleRequest();
    delay(100);
  }
  work.count++;
}
