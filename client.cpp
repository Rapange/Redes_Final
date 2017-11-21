#include "client.h"

Client::Client(int n_port, int l_port, int q_port, int p_port, int c_port, int keepAlive_port)
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
std::string Client::intToStr(int num, int size){
    std::string result;
    for(int i= 0; i < size; i++)
      result+='0';
    for(int i = size - 1; i >= 0; --i){
      result[i] = std::to_string(num%10)[0];
      num = num/10;
    }
    return result;
}





int Client::createServerSocket(int portNumber)
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

int Client::createClientSocket(int portNumber,std::string serverIP)
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

void Client::iniServerBot()
{
  
  
  
}

void Client::listenForClients(int serverSD, char action)
{
  
}

void Client::iniClientBot()
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

char Client::opReadN(int clientSD)
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

void Client::opWriteN(int clientSD, string word, string attributes)
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

void Client::opN(int clientSD, string word, string attributes)
{
  char is_successful;
  opWriteN(clientSD, word, attributes);
  is_successful = opReadN(clientSD);
  if(is_successful == '0') cout<<"Palabra insertada"<<endl;
  else cout<<"Palabra no insertada"<<endl;
}

void Client::opReadL(int clientSD, string word, string word2, string attributes)
{

}

void Client::opWriteL(int clientSD, string word, string word2, string attributes)
{

}

void Client::opL(int clientSD, string word, string word2, string attributes)
{

}

void Client::opReadQ(int clientSD, string word, int depth, bool attributes)
{
 
}

void Client::opWriteQ(int clientSD, string word, int depth, bool attributes)
{
  
}

void Client::opQ(int clientSD, string word, int depth, bool attributes)
{
  opWriteQ(clientSD, word, depth, attributes);
  opReadQ(clientSD, word, depth, attributes);
}

void Client::opReadP(int clientSD, string words, int depth, string attribute_name)
{

}

void Client::opWriteP(int clientSD, string words, int depth, string attribute_name)
{

}

void Client::opP(int clientSD, string words, int depth, string attribute_name)
{

}

void Client::opReadC(int clientSD, string word){
}

void Client::opWriteC(int clientSD, string word){
  char* buffer;
  string protocol;
  protocol += ACT_SND_C;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;

  buffer = new char[protocol.size()];

  write(clientSD,buffer,protocol.size());
  delete[] buffer;
  
}

void Client::opC(int clientSD, string word){
}

void Client::opReadKeep(int clientSD)
{

}

void Client::opWriteKeep(int clientSD)
{

}

void Client::opKeep(int clientSD){
}

//Server side

void Client::opNS(int clientSD, string word, string attributes)
{
  
}

void Client::opReadNS(int clientSD, string word, string attributes){
  
}

void Client::opWriteNS(int clientSD, string word, string attributes){
  
}

void Client::opLS(int clientSD, string word, string word2, string attributes)
{
  
}

void Client::opReadLS(int clientSD, string word, string word2, string attributes){
  
}

void Client::opWriteLS(int clientSD, string word, string word2, string attributes){
  
}

void Client::opQS(int clientSD, string word, int depth, bool attributes)
{
  
}

void Client::opReadQS(int clientSD, string word, int depth, bool attributes){
  
}

void Client::opWriteQS(int clientSD, string word, int depth, bool attributes){
  
}


void Client::opPS(int clientSD, string words, int depth, string attribute_name)
{
  
}

void Client::opReadPS(int clientSD, string words, int depth, string attribute_name){
  
}

void Client::opWritePS(int clientSD, string words, int depth, string attribute_name){
  
}

void Client::opCS(int clientSD, string word)
{
  
}

void Client::opReadCS(int clientSD, string word){
  
}

void Client::opWriteCS(int clientSD, string word){
  
}

Client::~Client()
{
    //dtor
}
