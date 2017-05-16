#include "state.h"

State::State(Setup* setup_){
  this->setup_=setup_;
}
void State::setParameters(Parameters newparameters){
  this->oldparameters=this->parameters;
  this->parameters=newparameters;
  //this->parameters.count=++count;
}
String State::getJsonParameters(){
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root=jsonBuffer.createObject();  
//  Serial.println(parameters.tInt);
//  Serial.println(parameters.tExt);
  root["tInt"]=parameters.tInt;
  root["tExt"]=parameters.tExt;
  root["count"]=parameters.count;
  root["wk"]=parameters.wk;
  root["mr"]=parameters.mr;
  root["b1"]=parameters.b1;
  root["b2"]=parameters.b2;
  root["heap"]=ESP.getFreeHeap();
  String json;
  root.prettyPrintTo(json);
  return json;
}
String State::getJsonSettings(){
  StaticJsonBuffer<200> jsonBuffer;
  Settings s=setup_->readSettings();
  JsonObject& root=jsonBuffer.createObject();
  root["wifiPass"]=String("bgt61Yhn");//s.wifiPass;
  Serial.println(s.wifiPass);
  Serial.println(s.wifiPass.length());
  root["wifiSid"]=s.wifiSid; 
  root["accesskey"]=s.accesskey;
  root["tGood"]=s.tGood;
  root["tLazy"]=s.tLazy;
  root["motorPos"]=s.motorPos;
  root["minMotorPos"]=s.minMotorPos;
  root["maxMotorPos"]=s.maxMotorPos;
  String json;
  root.printTo(json);
  return json;
}
void State::setJsonSettings(String jsonSettings){
  
}
void State::setJsonParameters(String jsonParameters){
  
}

