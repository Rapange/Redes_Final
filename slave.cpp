#include "slave.h"
#include "node.h"

Slave::Slave(int n_port, int l_port, int q_port, int c_port, int p_port, int s_port, int keepAlive_port)
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
std::string Slave::intToStr(int num, int size){
    std::string result;
    for(int i= 0; i < size; i++)
      result+='0';
    for(int i = size - 1; i >= 0; --i){
      result[i] = std::to_string(num%10)[0];
      num = num/10;
    }
    return result;
}


void Slave::readAll(){
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

void Slave::connectAll(){
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


int Slave::createServerSocket(int portNumber)
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

int Slave::createClientSocket(int portNumber,std::string serverIP)
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

void Slave::iniServerBot()
{

  int NSD = createServerSocket(m_n_port);
  int LSD = createServerSocket(m_l_port);
  int QSD = createServerSocket(m_q_port);
  int PSD = createServerSocket(m_p_port);
  int CSD = createServerSocket(m_c_port);
  int SSD = createServerSocket(m_s_port);

  std::thread(&Slave::listenForClients,this,NSD,ACT_RCV_N).detach();
  std::thread(&Slave::listenForClients,this,LSD,ACT_RCV_L).detach();
  std::thread(&Slave::listenForClients,this,QSD,ACT_RCV_Q).detach();
  std::thread(&Slave::listenForClients,this,PSD,ACT_RCV_P).detach();
  std::thread(&Slave::listenForClients,this,CSD,ACT_RCV_C).detach();
}

void Slave::iniSlaveCheckBot()
{
  int checkSD = createServerSocket(m_keepAlive_port);
  int ConnectFD = 0;
  while(true)
  {
    ConnectFD = accept(checkSD, NULL, NULL);
    if(0 > ConnectFD)
    {
      perror("error accept failed");
      close(checkSD);
      exit(EXIT_FAILURE);
    }
    std::thread(&Slave::opReadKeep,this,ConnectFD).detach();
  }
}

void Slave::listenForClients(int serverSD, char action)
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
      std::thread(&Slave::opNS,this,ConnectFD).detach();
    else if(action == ACT_RCV_L)
      std::thread(&Slave::opLS,this,ConnectFD).detach();
    /*else if(action == ACT_RCV_Q)
      std::thread(&Slave::opQS,this,ConnectFD).detach();
    else if(action == ACT_RCV_P)
      std::thread(&Slave::opPS,this,ConnectFD).detach();
    else if(action == ACT_RCV_C)
      std::thread(&Slave::opCS,this,ConnectFD).detach();
    else if(action == ACT_RCV_S)
      std::thread(&Slave::opSS,this,ConnectFD).detach();*/
 }
}

//str1,str2,str3
void Slave::strToVec(std::vector<std::string>& formatted_string, std::string& normal_string){
  std::string holder_string;
  cout<<"mis atributos: "<<normal_string<<endl;
  for(unsigned int i = 0; i < normal_string.size(); i++){
    if(normal_string[i] != ','){
      holder_string += normal_string[i];
    }
    else{
      formatted_string.push_back(holder_string);
      holder_string = "";
    }
  }
  if(holder_string != ""){
    formatted_string.push_back(holder_string);
  }
  return;
}

char Slave::addWord(std::string data, std::vector<std::string>& attributes){
  if(m_words[data]) return '0';
  cout<<"Attributes: "<<endl;
  for(unsigned int i = 0; i < attributes.size(); i++){
    cout<<attributes[i]<<" ";
  }
  cout<<endl;
  m_words[data] = new Node(data,attributes);
  /*Aqui se escribe en el archivo*/
  return '1';
}

char Slave::addRelation(std::string data_from, std::string data_to){
  if(!m_words[data_from]) return '0';
  if(m_words[data_from]->addRelation(data_to)) return '1';
  return '0';
}

void Slave::iniClientBot()
{
  connectAll();
  iniSlaveCheckBot();
  while(true);
}

char Slave::opReadN(int clientSD)
{

}

void Slave::opWriteN(int clientSD, string n_protocol)
{


}

char Slave::opN(int clientSD, string n_protocol)
{

}

char Slave::opReadL(int clientSD)
{

}

void Slave::opWriteL(int clientSD, string word, string word2)
{

}

char Slave::opL(int clientSD, string word, string word2)
{

}

string Slave::opReadQ(int clientSD)
{
  char* buffer;
  int size_of_response;
  string result;

  //mtx.lock();

  buffer = new char[ACTION_SIZE+1];
  read(clientSD, buffer, ACTION_SIZE);
  buffer[ACTION_SIZE] = '\0';
  cout<<buffer<<endl;
  delete[] buffer;

  buffer = new char[RESPONSE_SIZE+1];
  read(clientSD, buffer, RESPONSE_SIZE);
  buffer[RESPONSE_SIZE] = '\0';
  cout<<buffer<<endl;
  size_of_response = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_response+1];
  read(clientSD, buffer, size_of_response);
  buffer[size_of_response] = '\0';
  cout<<buffer<<endl;
  result = buffer;

  delete[] buffer;
  buffer= NULL;

  //mtx.unlock();

  return result;
}

void Slave::opWriteQ(int clientSD, string word, int depth, char attributes)
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

  //mtx.lock();
  write(clientSD, buffer, protocol.size());
  //mtx.unlock();
}

void Slave::opQ(int clientSD, string word, int depth, bool attributes)
{

}

void Slave::opReadP(int clientSD, string words, int depth, string attribute_name)
{

}

void Slave::opWriteP(int clientSD, string words, int depth, string attribute_name)
{

}

void Slave::opP(int clientSD, string words, int depth, string attribute_name)
{

}

void Slave::opReadC(int clientSD, string word){
}

void Slave::opWriteC(int clientSD, string word){


}

void Slave::opC(int clientSD, string word){
}

void Slave::opReadKeep(int clientSD)
{
  int n;
  char* message;
  message = new char[ACTION_SIZE+1];
  while(true){
    n = read(clientSD, message, ACTION_SIZE + 1);
    if (n < 0) perror("ERROR writing to socket");
    cout<<"Received Keep --"<<message<<"--"<<endl;
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }

    string confirm = "kR";
    n = write(clientSD,confirm.data(),confirm.size());
    if (n <= 0) {
      cout<<"fail"<<endl;
      break;
    }//perror("ERROR writing to socket");
  }
  shutdown(clientSD,SHUT_RDWR);
  close(clientSD);

}

void Slave::opWriteKeep(int clientSD)
{

}

void Slave::opKeep(int clientSD){
}

//Slave side

string Slave::formatResult(string word, char get_attributes){
  string result;
  if(!m_words[word]) return "";
  result = word;
  if(get_attributes == '1'){
    for(unsigned int i = 0; i < m_words[word]->m_attributes.size(); i++){
      result += ",";
      result += m_words[word]->m_attributes[i] ;
    }
  }
  result += ";";
  return result;
}

void Slave::doAllQuery(int clientSD, string word, int depth, char get_attributes){
  string result, current_word;
  int pos, current_socket;
  result = formatResult(word, get_attributes);
  cout<<"primer results. "<<result<<endl;
  if(depth == 0){
    cout<<"my result: "<<result << endl;
  }
  else{
    mtx.lock();
    for(unsigned int i = 0; i < m_words[word]->m_relations.size(); i++){
      current_word = m_words[word]->m_relations[i];
      pos = (hash<string>{}(current_word) % (m_sockets.size() - 1)) + 1;
      current_socket = m_sockets[pos][0];

      //mtx.lock();
      opWriteQ(current_socket, current_word, depth - 1, get_attributes);
      //mtx.unlock();
    }
    mtx.unlock();

    /*
    //mtx.lock();
    for(unsigned int i = 0; i < m_words[word]->m_relations.size(); i++){
      current_word = m_words[word]->m_relations[i];
      pos = (hash<string>{}(current_word) % (m_sockets.size() - 1)) + 1;
      current_socket = m_sockets[pos][0];

      //mtx.lock();
      result += opReadQ(current_socket);
      //mtx.unlock();
    }
    //mtx.unlock();
    */
  }
  //mtx.lock();
  cout<<"Escfibo a master"<<endl;
  opWriteQS(m_sockets[0][0], result);
  //mtx.unlock();
}

void Slave::opNS(int clientSD)
{
  while(true){
    char is_successful, get_attributes;
    char buffer[ACTION_SIZE+1];
    int depth;
    string protocol;
    std::string data, data_2, attributes;
    std::vector<std::string> formatted_attr;

    cout<<"Inicializacion"<<endl;
    //mtx.lock();
    read(clientSD,buffer,ACTION_SIZE);
    //mtx.unlock();
    buffer[ACTION_SIZE+1] = '\0';


    protocol = buffer;
    cout<<"Termino inicializacion"<<endl;

    if(buffer[0] == ACT_SND_N){
      cout<<"Se agrega N"<<endl;
      opReadNS(clientSD,data,attributes);

      strToVec(formatted_attr,attributes);
      //insert word
      is_successful = addWord(data,formatted_attr);
      cout<<"Se agrego: "<<data<<" "<<is_successful<<endl;
      opWriteNS(clientSD, is_successful);
    }
    else if(buffer[0] == ACT_SND_L){
      cout<<"Se agrega L"<<endl;
      opReadLS(clientSD,data,data_2);

      is_successful = addRelation(data,data_2);
      cout<<"Se agrego enlace: "<<data<<" "<<data_2<<" "<<is_successful<<endl;
      opWriteLS(clientSD, is_successful);
    }

    else if(buffer[0] == ACT_SND_Q){
      cout<<"Se lee Q"<<endl;
      //mtx.lock();
      opReadQS(clientSD, data, depth, get_attributes);
      //mtx.unlock();
      cout<<"se busca palabra, profundidad, attributes: "<<data<<" "<<depth<<" "<<get_attributes<<endl;
      thread(&Slave::doAllQuery,this,clientSD, data, depth,get_attributes).detach();
      //doAllQuery(clientSD,data,depth,get_attributes);
    }
    else if(buffer[0] == ACT_SND_C){
      cout<<"Se lee C"<<endl;

      opReadCS(clientSD, data);
      if(!m_words[data]) opWriteCS(clientSD, '0');
      else opWriteCS(clientSD, '1');

    }
  }


}

void Slave::opReadNS(int clientSD, string& data, string& attributes){
  char* buffer;
  int size_of_data, size_of_attributes;


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

}

void Slave::opWriteNS(int clientSD, char is_successful){
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

void Slave::opLS(int clientSD)
{
  string word,word2;
  char is_successful;
  opReadLS(clientSD,word,word2);
  is_successful = addRelation(word,word2);
  opWriteLS(clientSD,is_successful);
}

void Slave::opReadLS(int clientSD, string& word, string &word2){
  char* buffer;
  int size_of_data;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  word = buffer;
  delete[] buffer;

  buffer = new char[DATA_SIZE+1];
  read(clientSD,buffer,DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD,buffer,size_of_data);
  buffer[size_of_data] = '\0';
  word2 = buffer;
  delete[] buffer;

  cout<<"Se lee reverse"<<endl;

  buffer = new char[2];
  read(clientSD,buffer,1);
  buffer[1] = '\0';
  cout<<"Reverse: "<<buffer<<endl;
  if(buffer[0] == '1'){
    swap(word,word2);
  }
  delete[] buffer;

  buffer = NULL;
}

void Slave::opWriteLS(int clientSD, char is_successful){
  string protocol;
  char* buffer;

  protocol = ACT_RCV_L;
  protocol += is_successful;

  buffer = new char[protocol.size()];
  protocol.copy(buffer,protocol.size(),0);

  write(clientSD,buffer,protocol.size());
}

void Slave::opQS(int clientSD)
{

}

void Slave::opReadQS(int clientSD, string &word, int &depth, char &get_attributes){
  char* buffer;
  int size_of_data;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  word = buffer;
  delete[] buffer;

  buffer = new char[DEPTH_SIZE+1];
  read(clientSD, buffer, DEPTH_SIZE);
  buffer[DEPTH_SIZE] = '\0';
  depth = stoi(buffer);
  delete[] buffer;

  buffer = new char[1+1];
  read(clientSD, buffer, 1);
  buffer[1] = '\0';
  get_attributes = buffer[0];
  delete[] buffer;

  buffer = NULL;
}

void Slave::opWriteQS(int clientSD, string result){
  string protocol;
  char* buffer;
  protocol = ACT_RCV_Q;
  protocol += intToStr(result.size(), RESPONSE_SIZE);
  protocol += result;

  buffer = new char[protocol.size()];
  protocol.copy(buffer, protocol.size(), 0);
  //mtx.lock();
  write(clientSD, buffer, protocol.size());
  //mtx.unlock();

  delete[] buffer;
  buffer = NULL;
}


void Slave::opPS(int clientSD)
{

}

void Slave::opReadPS(int clientSD, string words, int depth, string attribute_name){

}

void Slave::opWritePS(int clientSD, string words, int depth, string attribute_name){

}

void Slave::opCS(int clientSD)
{

}

void Slave::opReadCS(int clientSD, string& word){
  char* buffer;
  int size_of_data;

  buffer = new char[DATA_SIZE+1];
  read(clientSD, buffer, DATA_SIZE);
  buffer[DATA_SIZE] = '\0';
  cout<<buffer<<endl;
  size_of_data = stoi(buffer);
  delete[] buffer;

  buffer = new char[size_of_data+1];
  read(clientSD, buffer, size_of_data);
  buffer[size_of_data] = '\0';
  word = buffer;
  cout<<word<<endl;
  delete[] buffer;
  buffer = NULL;
}

void Slave::opWriteCS(int clientSD, char found){
  string protocol;
  char* buffer;
  protocol = ACT_RCV_C;
  protocol += found;

  buffer = new char[protocol.size()];

  protocol.copy(buffer, protocol.size(), 0);
  write(clientSD, buffer, protocol.size());

  delete[] buffer;
  buffer = NULL;
}

void Slave::opSS(int clientSD){
}

void Slave::opReadSS(int clientSD){
}

void Slave::opWriteSS(int clientSD){
}

Slave::~Slave()
{
    //dtor
}
