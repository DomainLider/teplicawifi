#include "webserver.h"
#include <FS.h>

ESP8266WebServer server(80);
SPFS _fs;
#include "jsonhandler.h"

WebServer::WebServer(State* state){
  //server.on("/",HTTP_GET,[](){ server.send(200,"text/html",fs.dir());}); 
  server.addHandler(new JsonHandler(state));
  server.on("/", HTTP_GET, [](){    
    server.send(200, "text/html", _fs.dir());
  });
  server.on("/index.html", HTTP_GET, [](){    
    server.send(200, "text/html", _fs.getFile(String("/index.html")));
  });
  server.serveStatic("/", SPIFFS, "/", "max-age=86400");
  server.begin();
}
void WebServer::handleRequest(){
  server.handleClient();
}


