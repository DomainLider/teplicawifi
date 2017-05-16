#ifndef SPFS_H
#define SPFS_H
#include <Arduino.h>

class SPFS {
  private: const String HTTP404=String("File not found");
  private: const String HTTP500=String("Internal server error (FS not ready)");
  public: void toSerial();
  public: String getFile(String filename);
  public: String dir();
};
#endif
