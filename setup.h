#ifndef SETUP_H
#define SETUP_H

#include <Arduino.h>
#include <EEPROM.h>

struct Settings{
  String accesskey="admin";
  String wifiSid="DL";
  String wifiPass="bgt61Yhn";
  float tGood=24.4;
  float tLazy=1.9;
  int motorPos=99;
  int minMotorPos=1;
  int maxMotorPos=244;
  String www="www.samogon-on.ru";
  int port=80;
};

class Setup
{
  private: const int MAX_IO_SIZE=10;//Limit size bytes per one IO operaion
  private: const int MAX_IO_BUFFER=100;//Limit size bytes IO transaction READ\WRITE
  private: int current=0;
  public: Setup();  
  public: Settings readSettings();
  public: void writeSettings(Settings settings);
  public: Settings resetSettings();//Write default
  public: float readFloat(int addr);
  public: void writeFloat(int addr,float val);
  private: void writeBuffer(int addr,byte _size,void* buffer);
  private: void* readBuffer(int addr,byte _size);
  public: int readInt(int addr);
  public: void writeInt(int addr,int val);
  public: String readString(int addr);
  public: void writeString(int addr,String val);
  public: void toSerial(Settings _settings);
  
};
#endif
