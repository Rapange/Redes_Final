#include "server.h"

Server::Server(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port)
{
  m_n_port = n_port;
  m_l_port = l_port;
  m_q_port = q_port;
  m_c_port = c_port;
  m_p_port = p_port;
  m_s_port = s_port;
  m_keepAlive_port = keepAlive_port;
    //ctor
}

//Transforms an int to a sized string e.g., intToStr(21,4) => 0021, intToStr(9,3) => 009
std::string Server::intToStr(int num, int size){
    std::string result;
    for(int i= 0; i < size; i++)
      result+='0';
    for(int i = size - 1; i >= 0; --i){
      result[i] = std::to_string(num%10)[0];
      num = num/10;
    }
    return result;
}





int Server::createServerSocket(int portNumber)
{
    vector<unsigned int> holder;
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int ConnectFD = 0;

    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }

    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));

    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(portNumber);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;

    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    if(-1 == listen(SocketFD, 10))
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }

    return SocketFD;

    /*while(true)
    {
      ConnectFD = accept(SocketFD, NULL, NULL);

      if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
    }

    close(SocketFD);
    return 0;*/
}

int Server::createClientSocket(int portNumber,std::string serverIP)
{
  struct sockaddr_in stSockAddr;
  int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  int n, Res;

  if (-1 == SocketFD)
  {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }

  memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
  stSockAddr.sin_family = AF_INET;
  stSockAddr.sin_port = htons(portNumber);

  Res = inet_pton(AF_INET, serverIP.data(), &stSockAddr.sin_addr);

  if (0 > Res)
  {
    perror("error: first parameter is not a valid address family");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  else if (0 == Res)
  {
    perror("char string (second parameter does not contain valid ipaddress");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }

  if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
  {
    perror("connect failed");
    close(SocketFD);
    exit(EXIT_FAILURE);
  }
  return SocketFD;
}

void Server::readAll(){
  ifstream file;
  string ip;
  int port;
  vector<pair<string,int> > machine;
  file.open("IPs.txt");
  if(file.is_open()){
    while(file >> ip){
      if(ip == "-1"){
	m_ip_port.push_back(machine);
	machine.clear();
	//cout<<"PUSH ALL"<<endl;
	continue;
      }

      file >> port;
      cout<<ip<<" "<<port<<endl;
      machine.push_back(make_pair(ip,port));
      
    }
     
  }
}

void Server::connectAll(){
  readAll();
  vector<int> sockets;
  int my_socket;
  for(unsigned int i = 0; i < m_ip_port.size(); i++){
    //cout<<"line begin"<<endl;
    for(unsigned int j = 0; j < m_ip_port[i].size(); j++){
      my_socket =createClientSocket(m_ip_port[i][j].second, m_ip_port[i][j].first);
      sockets.push_back(my_socket);
      //cout<<m_ip_port[i][j].first<<" CONECTADO"<<endl;
    }
    m_sockets.push_back(sockets);
    sockets.clear();
  }
  
  return;
}

void Server::iniServerBot()
{
  
  int NSD = createServerSocket(m_n_port);
  int LSD = createServerSocket(m_l_port);
  int QSD = createServerSocket(m_q_port);
  int PSD = createServerSocket(m_p_port);
  int CSD = createServerSocket(m_c_port);
  int SSD = createServerSocket(m_s_port);

  std::thread(&Server::listenForClients,this,NSD,ACT_RCV_N).detach();
  std::thread(&Server::listenForClients,this,LSD,ACT_RCV_L).detach();
  std::thread(&Server::listenForClients,this,QSD,ACT_RCV_Q).detach();
  std::thread(&Server::listenForClients,this,PSD,ACT_RCV_P).detach();
  std::thread(&Server::listenForClients,this,CSD,ACT_RCV_C).detach();
  std::thread(&Server::listenForClients,this,SSD,ACT_RCV_S).detach();
  
}

void Server::listenForClients(int serverSD, char action)
{
  int ConnectFD = 0;
  while(true)
  {
    ConnectFD = accept(serverSD, NULL, NULL);

    if(0 > ConnectFD)
    {
       perror("error accept failed");
       close(serverSD);
       exit(EXIT_FAILURE);
    }
    if(action == ACT_RCV_N)
      std::thread(&Server::opNS,this,ConnectFD).detach();
    else if(action == ACT_RCV_L)
      std::thread(&Server::opLS,this,ConnectFD).detach();
    /*else if(action == ACT_RCV_Q)
      std::thread(&Server::opQS,this,ConnectFD).detach();
    else if(action == ACT_RCV_P)
      std::thread(&Server::opPS,this,ConnectFD).detach();
    else if(action == ACT_RCV_C)
      std::thread(&Server::opCS,this,ConnectFD).detach();
    else if(action == ACT_RCV_S)
      std::thread(&Server::opSS,this,ConnectFD).detach();*/
    
 }
}

void Server::iniClientBot()
{
  connectAll();
  while(true);
}

char Server::opReadN(int clientSD)
{
  char* buffer;
  char is_successful;
    
  buffer = new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[SUCCESS_SIZE+1];
  read(clientSD, buffer, SUCCESS_SIZE);
  buffer[SUCCESS_SIZE] = '\0';
  is_successful = buffer[0];
  delete[] buffer;

  return is_successful;
}

void Server::opWriteN(int clientSD, string n_protocol)
{
  char buffer[n_protocol.size()];
  n_protocol.copy(buffer,n_protocol.size(),0);
  write(clientSD,buffer,n_protocol.size());

}

char Server::opN(int clientSD, string n_protocol)
{
  char is_successful;

  cout<<"Se escribe"<<endl;
  opWriteN(clientSD, n_protocol);
  cout<<"Se recibe"<<endl;
  is_successful = opReadN(clientSD);
  return is_successful;
}

//Es el mismo codigo que opReadN...
char Server::opReadL(int clientSD)
{
  char* buffer;
  char is_successful;
    
  buffer = new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[SUCCESS_SIZE+1];
  read(clientSD, buffer, SUCCESS_SIZE);
  buffer[SUCCESS_SIZE] = '\0';
  is_successful = buffer[0];
  delete[] buffer;

  return is_successful;
}

void Server::opWriteL(int clientSD, string l_protocol)
{
  char buffer[l_protocol.size()];
  l_protocol.copy(buffer,l_protocol.size(),0);
  //cout<<"SE envia: "<<buffer<<endl;
  write(clientSD,buffer,l_protocol.size());
}

char Server::opL(int clientSD, string l_protocol, char reverse)
{
  l_protocol += reverse;
  cout<<"l protocolo "<<l_protocol<<endl;
  opWriteL(clientSD,l_protocol);
  return opReadL(clientSD);
}

void Server::opReadQ(int clientSD, string word, int depth, bool attributes)
{
 
}

void Server::opWriteQ(int clientSD, string word, int depth, bool attributes)
{
  
}

void Server::opQ(int clientSD, string word, int depth, bool attributes)
{
  
}

void Server::opReadP(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opWriteP(int clientSD, string words, int depth, string attribute_name)
{

}

void Server::opP(int clientSD, string words, int depth, string attribute_name)
{
  
}

void Server::opReadC(int clientSD, string word){
}

void Server::opWriteC(int clientSD, string word){
  
  
}

void Server::opC(int clientSD, string word){
}

void Server::opReadKeep(int clientSD)
{

}

void Server::opWriteKeep(int clientSD)
{

}

void Server::opKeep(int clientSD){
}

//Server side

void Server::opNS(int clientSD)
{
  char is_successful;
  string n_protocol;
  char buffer[ACTION_SIZE+1];
  int pos, pos_2, current_socket;

  read(clientSD,buffer,ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  n_protocol = buffer;
  cout<<"protocolo a usar: "<<buffer<<endl;
  
  if(buffer[0] == ACT_SND_S || buffer[0] == ACT_SND_C){
  }
  else{
    if(buffer[0] == ACT_SND_N){
      cout<<"ES N"<<endl;
      opReadNS(clientSD, n_protocol, pos);
      for(unsigned int i = 0; i < m_sockets[pos].size(); i++){
	cout<<"Sending request N to: "<< m_ip_port[pos][i].second <<endl;
	current_socket = m_sockets[pos][i];
	is_successful = opN(current_socket, n_protocol);
      }
      opWriteNS(clientSD, is_successful);
    }
    if(buffer[0] == ACT_SND_L){
      cout<<"ES L"<<endl;
      opReadLS(clientSD, n_protocol, pos, pos_2);
      for(unsigned int i = 0; i < m_sockets[pos].size(); i++){
	cout<<"Sending request L1 to: "<< m_ip_port[pos][i].second << endl;
	current_socket = m_sockets[pos][i];
	is_successful = opL(current_socket, n_protocol, '0');
      }

      if(is_successful == '1'){
	for(unsigned int i = 0; i < m_sockets[pos_2].size(); i++){
	  cout<<"Sending request L2 to: "<< m_ip_port[pos_2][i].second << endl;
	  current_socket = m_sockets[pos_2][i];
	  is_successful = opL(current_socket, n_protocol, '1');
	}
      }
      opWriteLS(clientSD, is_successful);
    }
  }
  
  //insert word

  //Debe ser otro clientSD
  
  
  
  
}

string Server::opReadNS(int clientSD, std::string& protocol, int &pos){
  char* buffer;
  int size_of_data, size_of_attributes;
  string data, attributes;
  

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  protocol += buffer;
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  data = buffer;

  size_t str_hash = (hash<string>{}(data) % (m_sockets.size()-1)) + 1;
  cout<<str_hash<<endl;
  pos = str_hash;
  protocol += buffer;
  delete[] buffer;

  buffer = new char[ATTRIBUTE_LIST_SIZE+1];
  read(clientSD, buffer, ATTRIBUTE_LIST_SIZE);
  buffer[ATTRIBUTE_LIST_SIZE] = '\0';
  size_of_attributes = stoi(buffer);
  protocol += buffer;
  delete[] buffer;

  buffer = new char[size_of_attributes+1];
  read(clientSD,buffer, size_of_attributes);
  buffer[size_of_attributes] = '\0';
  attributes = buffer;
  protocol += buffer;
  delete[] buffer;
  buffer = NULL;

  cout<<data<<endl;
  
  return protocol;
}

void Server::opWriteNS(int clientSD, char is_successful){
  string protocol;
  char* buffer;
  protocol = ACT_RCV_N;
  protocol += is_successful;
  buffer = new char[protocol.size()];
  protocol.copy(buffer,protocol.size(),0);

  cout<<protocol<<endl;
  write(clientSD,buffer,protocol.size());

  delete[] buffer;
  buffer = NULL;
}

void Server::opLS(int clientSD)
{
  /*std::string l_protocol;
  char is_successful;
  opReadLS(clientSD,l_protocol);

  //clientSD debe ser otro.
  is_successful = opL(clientSD,l_protocol);
  opWriteLS(clientSD, is_successful);*/
}

void Server::opReadLS(int clientSD, std::string& l_protocol, int &pos, int &pos_2){
  char* buffer;
  int size_of_data;
  string data_1, data_2;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  l_protocol += buffer;
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  data_1 = buffer;
  l_protocol += buffer;
  delete[] buffer;

  buffer = new char[DATA_SIZE+1];
  read(clientSD,buffer,DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  l_protocol += buffer;
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD,buffer,size_of_data);
  buffer[size_of_data] = '\0';
  data_2 = buffer;
  l_protocol += buffer;
  delete[] buffer;
  
  buffer = NULL;

  pos = (hash<string>{}(data_1) % (m_sockets.size()-1)) + 1;
  pos_2 = (hash<string>{}(data_2) % (m_sockets.size()-1)) + 1;
}

void Server::opWriteLS(int clientSD, char is_successful){
  string protocol;
  char* buffer;
  
  protocol = ACT_RCV_L;
  protocol += is_successful;
  cout<<"Enviando protocolo resultado: "<<protocol<<endl;

  buffer = new char[protocol.size()];
  protocol.copy(buffer,protocol.size(),0);

  write(clientSD,buffer,protocol.size());
}

void Server::opQS(int clientSD)
{
  
}

void Server::opReadQS(int clientSD, string word, int depth, bool attributes){
  
}

void Server::opWriteQS(int clientSD, string word, int depth, bool attributes){
  
}


void Server::opPS(int clientSD)
{
  
}

void Server::opReadPS(int clientSD, string words, int depth, string attribute_name){
  
}

void Server::opWritePS(int clientSD, string words, int depth, string attribute_name){
  
}

void Server::opCS(int clientSD)
{
  
}

void Server::opReadCS(int clientSD, string word){
  
}

void Server::opWriteCS(int clientSD, string word){
  
}

void Server::opSS(int clientSD){
}

void Server::opReadSS(int clientSD){
}

void Server::opWriteSS(int clientSD){
}

Server::~Server()
{
    //dtor
}
