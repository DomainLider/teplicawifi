#ifndef WEBSERVER_H
#define WEBSERVER_H

#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "spfs.h"
#include "state.h"

class WebServer {   
  public: WebServer(State* state);
  public: void handleRequest();
};

#endif
