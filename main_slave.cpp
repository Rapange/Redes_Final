#include "slave.h"
#include <iostream>

int main(){
  int n_port, l_port, q_port, p_port, c_port, s_port, keepAlive_port;
  cin>>n_port>>l_port>>q_port>>p_port>>c_port>>s_port>>keepAlive_port;
  Slave slave(n_port,l_port,q_port,p_port,c_port,s_port,keepAlive_port);

  slave.iniServerBot();
  cout<<"Se inicio servidor."<<endl;
  slave.iniClientBot();
  return 0;
}
