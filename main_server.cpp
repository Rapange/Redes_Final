#include "server.h"
#include <iostream>

int main(){
  int n_port, l_port, q_port, p_port, c_port, s_port, keepAlive_port;
  cin>>n_port>>l_port>>q_port>>p_port>>c_port>>s_port>>keepAlive_port;
  Server server(n_port,l_port,q_port,p_port,c_port,s_port,keepAlive_port);

  server.iniServerBot();
  cout<<"Se inicio servidor."<<endl;
  server.iniClientBot();
  return 0;
}
