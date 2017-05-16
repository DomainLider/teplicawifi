#ifndef JSONHANDLER_H
#define JSONHANDLER_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "state.h"

class JsonHandler:public RequestHandler {
  private: State* state;
  public:   
   JsonHandler(State* state){
    this->state=state;
   }
    bool canHandle(HTTPMethod method,String uri) override{
      if (method==HTTP_GET){
//        Serial.println("Check handle for "+uri);
        return uri=="/status"||uri=="/config";
      }
      return false;
    }
    bool handle(ESP8266WebServer& server,HTTPMethod requestMethod,String uri) override {
//      Serial.println("Handler for :"+uri);
      if (!canHandle(requestMethod,uri)) return false; 
      if (uri=="/status"){
          server.send(200, "text/json", state->getJsonParameters());
          return true;
      }
      if (uri=="/config"){
        server.send(200, "text/json", state->getJsonSettings());
        return true;
      }
      return false;
    }
    
};
#endif
