#include "server.h"
#include <iostream>

int main(){
  int mainPortNumber,CheckPortNumber;
  cout<<"Ingrese puerto check";
  cin>>CheckPortNumber;

  //Server slaveserver(40010,CheckPortNumber);
  //slaveserver.iniSlaveCheckBot();

  Server mainserver(40012,CheckPortNumber);
  mainserver.iniMasterCheckBot();

  return 0;
}
