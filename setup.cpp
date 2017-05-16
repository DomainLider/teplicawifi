#include "setup.h"

Setup::Setup(){
  
}

Settings Setup::readSettings(){
  Settings _settings;
  current=0;
  EEPROM.begin(512);
  _settings.tGood=readFloat(current);
  _settings.tLazy=readFloat(current);
  _settings.motorPos=readInt(current);
  _settings.minMotorPos=readInt(current);
  _settings.maxMotorPos=readInt(current);
  _settings.wifiSid=readString(current);  
  _settings.accesskey=readString(current);
  _settings.wifiPass=readString(current);
  EEPROM.end();
  return _settings;
}

void Setup::writeSettings(Settings settings){
  current=0;
  EEPROM.begin(512);
  writeFloat(current,settings.tGood);
  writeFloat(current,settings.tLazy);
  writeInt(current,settings.motorPos);
  writeInt(current,settings.minMotorPos);
  writeInt(current,settings.maxMotorPos);
  writeString(current,settings.wifiSid);  
  writeString(current,settings.accesskey);
  writeString(current,settings.wifiPass);
  EEPROM.end();
}

Settings Setup::resetSettings(){
  Settings settings;
  writeSettings(settings);
  return settings;
}
float Setup::readFloat(int addr){
  void* buffer=readBuffer(addr,sizeof(float));
  float* link=(float*)buffer;
  return *link;
}

void Setup::writeFloat(int addr,float val){
  writeBuffer(addr,sizeof(float),&val);
}

void* Setup::readBuffer(int addr,byte _size){
  byte x[_size];
  for (byte i=0;i<_size;i++) {
    x[i]=EEPROM.read(i+addr);
//    Serial.println("R>"+String(i+addr)+":"+String(x[i]));
  }
  current=addr+_size;
  return x;
}

void Setup::writeBuffer(int addr,byte _size,void* buffer){
  byte* x=(byte*)buffer;
  for (byte i=0;i<_size;i++) {
    EEPROM.write(i+addr,x[i]);
//    Serial.println("W>"+String(i+addr)+":"+String(x[i]));
  }
  current=addr+_size;
}
int Setup::readInt(int addr){
  void* buffer=readBuffer(addr,sizeof(int));
  int* link=(int*)buffer;
  return *link;
}
void Setup::writeInt(int addr,int val){
  writeBuffer(addr,sizeof(int),&val);
}

String Setup::readString(int addr){
  int valLength=readInt(addr);
//  Serial.println("RL="+String(valLength));
  void* buffer=readBuffer(addr+sizeof(int),valLength);
  char* link=(char*)buffer;
//  Serial.println(link);
  return String(link);
}
void Setup::writeString(int addr,String val){
  int valLength=(int)val.length()+1;
//  Serial.println("WL="+String(valLength));
  writeInt(addr,valLength);
  char str[valLength];
  val.toCharArray(str,valLength);
//  Serial.println(str);
  writeBuffer(addr+sizeof(int),valLength,str);
}

void Setup::toSerial(Settings _settings){
  Serial.println("Wifi SID: "+_settings.wifiSid);
  Serial.println("Wifi Pass: "+_settings.wifiPass);
  Serial.println("Temp Good: "+String(_settings.tGood));
  Serial.println("Temp Lazy: "+String(_settings.tLazy));
  Serial.println("Motor Position: "+String(_settings.motorPos));
  Serial.println("Min Motor Position: "+String(_settings.minMotorPos));
  Serial.println("Max Motor Position: "+String(_settings.maxMotorPos));
}

