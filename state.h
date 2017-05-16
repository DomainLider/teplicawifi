#ifndef STATE_H
#define STATE_H

#include <ArduinoJson.h>
#include "setup.h"

struct Parameters {
  float tInt=0;
  float tExt=0;
  int count=0;
  byte wk=LOW;
  byte mr=LOW; 
  byte b1=LOW;
  byte b2=LOW;
  byte mode=0;//0-client,1-server
};

class State {
//  private: DynamicJsonBuffer jsonBuffer;
  
  private: Setup* setup_;
  private: Parameters parameters;
  private: Parameters oldparameters;
  private: int count=0;
  
  public: State(Setup* setup_);
  public: void setParameters(Parameters newparameters);
  public: String getJsonParameters();
  public: String getJsonSettings();
  public: void setJsonSettings(String jsonSettings);
  public: void setJsonParameters(String jsonParameters);
};

#endif
