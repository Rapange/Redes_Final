#include "server.h"
#include <iostream>

int main(){
  int mainPortNumber,checkPortNumber;

  cout<<"Ingrese puerto main";
  cin>>mainPortNumber;

  cout<<"Ingrese puerto check";
  cin>>checkPortNumber;

  //Server slaveserver(mainPortNumber,checkPortNumber);
  //slaveserver.iniSlaveCheckBot();

  Server mainserver(mainPortNumber,checkPortNumber);
  mainserver.iniMasterCheckBot();

  return 0;
}
