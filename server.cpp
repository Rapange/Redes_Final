#include "server.h"

Server::Server(int n_port, int l_port, int q_port, int p_port, int c_port, int keepAlive_port)
{
  m_n_port = n_port;
  m_l_port = l_port;
  m_q_port = q_port;
  m_c_port = c_port;
  m_p_port = p_port;
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

void Server::iniServerBot()
{
  
  
  
}

void Server::listenForClients(int serverSD, char action)
{
  
}

void Server::iniClientBot()
{
  int port;
  string Ip;
  string command;
  int query_N;
  cout<<"Ingrese direccion IP del maestro: ";
  cin>>Ip;
  cout<<"Ingrese puerto del maestro; ";
  cin>>port;
  query_N = createClientSocket(port,Ip);
  while(true){
    cin>>command;
    if(command[0] == 'N') opN(query_N,"test","");
  }
}

char Server::opReadN(int clientSD)
{
  /*char* buffer;
  int size_of_data;
  string data;
  buffer = new char[ACTION_SIZE+1]; //n
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  delete[] buffer;*/
  char* buffer;
  char is_successful;
  buffer = new char[ACTION_SIZE+1];
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[SUCCESS_SIZE+1];
  buffer[SUCCESS_SIZE] = '\0';
  is_successful = buffer[0];
  delete[] buffer;
  buffer = NULL;

  return is_successful;
}

void Server::opWriteN(int clientSD, string word, string attributes)
{
  string protocol;
  char* buffer;
  protocol += ACT_SND_N;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;
  protocol += intToStr(attributes.size(),ATTRIBUTE_LIST_SIZE);
  protocol += attributes;
  //Colocar redundancia?

  buffer = new char[protocol.size()];
  write(clientSD, buffer, protocol.size());

  delete[] buffer;
  buffer = NULL;
}

char Server::opN(int clientSD, string word, string attributes)
{
  char is_successful;
  opWriteN(clientSD, word, attributes);
  return opReadN(clientSD);
}

char Server::opReadL(int clientSD)
{
  char* buffer;
  buffer = new char[ACTION_SIZE+1];
  read(clientSD,buffer,ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[SUCCESS_SIZE+1];
  read(clientSD,buffer,SUCCESS_SIZE);
  buffer[SUCCESS_SIZE] = '\0';
  delete[] buffer;

  return buffer[0];
}

void Server::opWriteL(int clientSD, string word, string word2)
{
  string protocol;
  char* buffer;
  protocol += ACT_SND_L;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;
  protocol += intToStr(word2.size(),DATA_SIZE);
  protocol += word2;

  buffer = new char[protocol.size()];
  write(clientSD,buffer,protocol.size());

  delete[] buffer;
  buffer = NULL;
}

char Server::opL(int clientSD, string word, string word2)
{
  opWriteL(clientSD, word, word2);
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
  opWriteQ(clientSD, word, depth, attributes);
  opReadQ(clientSD, word, depth, attributes);
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
  char* buffer;
  string protocol;
  protocol += ACT_SND_C;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;

  buffer = new char[protocol.size()];

  write(clientSD,buffer,protocol.size());
  delete[] buffer;
  
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
  opReadNS(clientSD);
  //insert word
  opWriteNS(clientSD, is_successful);
}

string Server::opReadNS(int clientSD){
  char* buffer;
  int size_of_data, size_of_attributes;
  string data, attributes;
  buffer = new char[ACTION_SIZE+1]; //n
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  data = buffer;
  delete[] buffer;

  buffer = new char[ATTRIBUTE_LIST_SIZE+1];
  read(clientSD, buffer, ATTRIBUTE_LIST_SIZE);
  buffer[ATTRIBUTE_LIST_SIZE] = '\0';
  size_of_attributes = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_attributes+1];
  read(clientSD,buffer, size_of_attributes);
  buffer[size_of_attributes] = '\0';
  attributes = buffer;
  delete[] buffer;
  buffer = NULL;
  
  return attributes;
}

void Server::opWriteNS(int clientSD, char is_successful){
  string protocol;
  char* buffer;
  protocol = ACT_RCV_N;
  protocol += is_successful;
  buffer = new char[protocol.size()];
  protocol.copy(buffer,protocol.size(),0);
  write(clientSD,buffer,protocol.size());

  delete[] buffer;
  buffer = NULL;
}

void Server::opLS(int clientSD, string word, string word2, string attributes)
{
  
}

void Server::opReadLS(int clientSD, string word, string word2, string attributes){
  
}

void Server::opWriteLS(int clientSD, string word, string word2, string attributes){
  
}

void Server::opQS(int clientSD, string word, int depth, bool attributes)
{
  
}

void Server::opReadQS(int clientSD, string word, int depth, bool attributes){
  
}

void Server::opWriteQS(int clientSD, string word, int depth, bool attributes){
  
}


void Server::opPS(int clientSD, string words, int depth, string attribute_name)
{
  
}

void Server::opReadPS(int clientSD, string words, int depth, string attribute_name){
  
}

void Server::opWritePS(int clientSD, string words, int depth, string attribute_name){
  
}

void Server::opCS(int clientSD, string word)
{
  
}

void Server::opReadCS(int clientSD, string word){
  
}

void Server::opWriteCS(int clientSD, string word){
  
}

Server::~Server()
{
    //dtor
}
