#include "client.h"

Client::Client(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port)
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

void Client::iniClientBot(char action, vector<string> &arguments)
{
  int port;
  string Ip;
  string word_1, word_2;
  string attr, result, ip_list;
  int query_N, depth, redundance;
  char is_successful, get_attributes, use;
  ifstream file;
  file.open("IPs_client.txt");
  if(file.is_open()){
    file >> Ip;
    file >> m_n_port;
  }
  
  
  query_N = createClientSocket(m_n_port,Ip);
  if(action == ACT_SND_N){
    word_1 = arguments[0];
    for(unsigned int i = 1; i < arguments.size(); i+=3){
      attr += arguments[i+2] + ",";
    }
    is_successful = opN(query_N,word_1,attr);
    if(is_successful == '1') cout<<"Operacion exitosa"<<endl;
    else cout<<"ERROR"<<endl;
  }
  else if(action == ACT_SND_L){
    cout<<"ES L"<<endl;
    word_1 = arguments[0];
    word_2 = arguments[1];
    is_successful = opL(query_N,word_1,word_2);
    if(is_successful == '1') cout<<"Operacion exitosa"<<endl;
    else cout<<"ERROR"<<endl;
  }

  else if(action == ACT_SND_Q){
    cout<<"ES Q"<<endl;
    word_1 = arguments[0];
    depth = 1;
    get_attributes = '0';
    if(arguments.size() > 1) depth = stoi(arguments[1]);
    if(arguments.size() > 2) get_attributes = '1';
    //cout<<"Se envian: "<<get_attributes<<endl;
    opWriteQ(query_N, word_1, depth, get_attributes);
    while(true){
      result = opReadQ(query_N);
      cout<<result<<endl;
    }
  }
  else if(action == ACT_SND_C){
    cout<<"Es C"<<endl;
    word_1 = arguments[0];
    opWriteC(query_N, word_1);
    opReadC(query_N, ip_list, redundance, use);
    cout<<ip_list<<endl<<redundance<<endl<<use<<endl;
    
  }
  else if(action == ACT_SND_S){
    cout<<"Es S"<<endl;
    opWriteS(query_N);
    cout<<"Waiting..."<<endl;
    opReadS(query_N, result);
    cout<<result<<endl;
  }
  
}

char Client::opReadN(int clientSD)
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
  buffer = NULL;

  cout<<is_successful<<endl;

  return is_successful;
}

void Client::opWriteS(int clientSD){
  string protocol;
  char* buffer;
  protocol = ACT_SND_S;

  buffer = new char[protocol.size()];
  protocol.copy(buffer, protocol.size(),0);

  write(clientSD, buffer, protocol.size());

  delete[] buffer;
  buffer = NULL;
}
void Client::opReadS(int clientSD, string &result){
  char* buffer;
  int size_of_response;
  
  buffer= new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer =  new char[RESPONSE_SIZE+1];
  read(clientSD, buffer, RESPONSE_SIZE);
  buffer[RESPONSE_SIZE] = '\0';
  size_of_response = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_response+1];
  read(clientSD, buffer, size_of_response);
  buffer[size_of_response] = '\0';
  result = buffer;
  delete[] buffer;

  return;
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
  protocol.copy(buffer,protocol.size(),0);
  write(clientSD, buffer, protocol.size());

  delete[] buffer;
  buffer = NULL;
}

char Client::opN(int clientSD, string word, string attributes)
{
  char is_successful;
  opWriteN(clientSD, word, attributes);
  return opReadN(clientSD);
}

char Client::opReadL(int clientSD)
{
  char* buffer;
  char is_successful;
  buffer = new char[ACTION_SIZE+1];
  read(clientSD,buffer,ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;

  buffer = new char[SUCCESS_SIZE+1];
  read(clientSD,buffer,SUCCESS_SIZE);
  buffer[SUCCESS_SIZE] = '\0';
  is_successful = buffer[0];
  delete[] buffer;

  return is_successful;
}

void Client::opWriteL(int clientSD, string word, string word2)
{
  string protocol;
  char* buffer;
  protocol += ACT_SND_L;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;
  protocol += intToStr(word2.size(),DATA_SIZE);
  protocol += word2;

  buffer = new char[protocol.size()];
  protocol.copy(buffer,protocol.size(),0);
  write(clientSD,buffer,protocol.size());

  delete[] buffer;
  buffer = NULL;
}

char Client::opL(int clientSD, string word, string word2)
{
  opWriteL(clientSD, word, word2);
  return opReadL(clientSD);
}

string Client::opReadQ(int clientSD)
{
  char* buffer;
  int size_of_response;
  string response;

  buffer = new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;
  
  buffer = new char[RESPONSE_SIZE+1];
  read(clientSD, buffer, RESPONSE_SIZE);
  buffer[RESPONSE_SIZE] = '\0';
  size_of_response = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_response+1];
  read(clientSD, buffer, size_of_response);
  buffer[size_of_response] = '\0';
  response = buffer;
  delete[] buffer;

  return response;
  
}

void Client::opWriteQ(int clientSD, string word, int depth, char attributes)
{
  string protocol;
  char* buffer;
  protocol = ACT_SND_Q;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;
  protocol += intToStr(depth, DEPTH_SIZE);
  protocol += attributes;

  buffer = new char[protocol.size()];
  protocol.copy(buffer, protocol.size(), 0);
  cout<<"enviando protocolo: "<<protocol<<endl;
  write(clientSD, buffer, protocol.size());

  delete[] buffer;
  buffer = NULL;
}

string Client::opQ(int clientSD, string word, int depth, char attributes)
{
  opWriteQ(clientSD, word, depth, attributes);
  return opReadQ(clientSD);
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

void Client::opReadC(int clientSD, string &ip_list, int &redundance, char &use){
  char* buffer;
  int size_of_ip_list = 0;
  
  buffer = new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  delete[] buffer;
  
  buffer = new char[IP_LIST_SIZE+1];
  read(clientSD, buffer, IP_LIST_SIZE);
  buffer[IP_LIST_SIZE] = '\0';
  size_of_ip_list = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_ip_list+1];
  read(clientSD, buffer, size_of_ip_list);
  buffer[size_of_ip_list] = '\0';
  ip_list = buffer;
  delete[] buffer;

  buffer = new char[REDUNDANCE_SIZE+1];
  read(clientSD, buffer, REDUNDANCE_SIZE);
  buffer[REDUNDANCE_SIZE] = '\0';
  redundance = stoi(buffer);
  delete[] buffer;

  buffer = new char[USE_SIZE+1];
  read(clientSD, buffer, USE_SIZE);
  buffer[USE_SIZE] = '\0';
  use = buffer[0];
  delete[] buffer;
  
  buffer = NULL;
}

void Client::opWriteC(int clientSD, string word){
  char* buffer;
  string protocol;
  protocol = ACT_SND_C;
  protocol += intToStr(word.size(),DATA_SIZE);
  protocol += word;

  buffer = new char[protocol.size()];
  protocol.copy(buffer, protocol.size(), 0);
  write(clientSD,buffer,protocol.size());
  delete[] buffer;
  buffer = NULL;
  
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
