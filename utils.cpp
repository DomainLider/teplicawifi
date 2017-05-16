#include "utils.h"

int D(int idx){
  static int GPIO[]={16,5,4,0,2,14,12,13,15,3,1,9,10};
  if (idx<=12)
    return GPIO[idx];
  return -1;
}

char* stringToChar(String s){
  char buffer[s.length()+1];
  s.toCharArray(buffer,s.length()+1);
  return buffer;
}
