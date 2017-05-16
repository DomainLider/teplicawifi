#ifndef TEMP_H
#define TEMP_H

#include <OneWire.h>
#include <DallasTemperature.h>

#include "utils.h"
//OneWire ds(D(7)); //PIN7! на пине 10 (нужен резистор 4.7 КОм)
OneWire ds(D(4)); //PIN7! на пине 10 (нужен резистор 4.7 КОм)
DallasTemperature sensors(&ds);

float t1;
float t2;
int MAX_HISTORY=128;
int curt=0;
float* ht1=new float[MAX_HISTORY];
float* ht2=new float[MAX_HISTORY];
float* hd=new float[MAX_HISTORY];

void tempSetup(){
  sensors.begin();
  for (int i=0;i<MAX_HISTORY;i++){
    ht1[i]=ht2[i]=hd[i]=0;
  }
}


void addTemp(){
  if (curt!=MAX_HISTORY-1){
    curt++;
  }else{
    for (int i=1;i<=curt;i++){
      ht1[i-1]=ht1[i];ht2[i-1]=ht2[i];hd[i-1]=hd[i];
    }
  }
  ht1[curt]=t1;
  ht2[curt]=t2;
  hd[curt]=t1-t2;
}
String st1="";
String st2="";
void getTemp(){
  sensors.requestTemperatures();
  t1=sensors.getTempCByIndex(0);
  delay(500);
  t2=sensors.getTempCByIndex(1);
  Serial.println(t2);
  addTemp();
  st1=String(t1);
  st2=String(t2);
}

void tempPrint(){
  getTemp();
  Serial.print("t0=");
  Serial.println(t1);
  Serial.print("t1=");
  Serial.println(t2);
}

#endif TEMP_H
