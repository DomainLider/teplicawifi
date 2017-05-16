#include "spfs.h"
#include <FS.h>

void SPFS::toSerial(){
   if (SPIFFS.begin()){
    Serial.println("FS Mounted");
    Dir dir=SPIFFS.openDir("/");
    while (dir.next()){
      Serial.print(dir.fileName());
      File f=dir.openFile("r");
      Serial.println(f.size());
    }
    SPIFFS.end();
  }
}

String SPFS::dir(){
   if (SPIFFS.begin()){
    String filebody="<html><body>";
    Serial.println("FS Mounted");
    Dir dir=SPIFFS.openDir("/");
    while (dir.next()){
      File f=dir.openFile("r");
      filebody=filebody+"<br/><a href="+dir.fileName()+">"+dir.fileName()+"<p>"+String(f.size());
      Serial.println(dir.fileName()+" "+String(f.size()));
    }
    filebody=filebody+"</body></html>";
    SPIFFS.end();
    return filebody;
  }
  return HTTP500;
  
}

String SPFS::getFile(String filename){
  if (SPIFFS.begin()){
    File f=SPIFFS.open(filename,"r");
    if (!f){
      Serial.println("FSERR: File not found "+filename);  
      return HTTP404;
    }
    String filebody=String("");
    while (f.available()){
      filebody=filebody+f.readStringUntil('\n');
    }
    f.close();
    SPIFFS.end();
    return filebody;
  }
}

