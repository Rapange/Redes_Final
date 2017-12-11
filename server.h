#ifndef SERVER_H
#define SERVER_H

#include "red.h"


class Server
{
  public:

    int m_n_port, m_l_port, m_q_port, m_p_port, m_c_port, m_s_port, m_keepAlive_port;
    string result;
    mutex mtx;
    int state;
	  int id;
	  int m_seconds;
	  std::vector< std::vector< std::pair < std::string, int > > > m_ip_port;
    std::vector< std::vector< int > > m_sockets;
    std::vector< int > m_available;
	  vector<int> m_clients;

    Server(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port);
    virtual ~Server();

    std::string intToStr(int num, int size);
    void readAll();
    void connectAll();
    
    vector<string> strToVec(string words);
	  
    void iniServerBot();
  	void listenForClients(int serverSD, char action);

    void iniClientBot();
    void iniMasterCheckBot();
    int createClientSocket(int portNumber, string serverIP);
    int createServerSocket(int portNumber);

	  //Client side

    char opReadN(int clientSD);
    void opWriteN(int clientSD, string n_protocol);
	  char opN(int clientSD, string n_protocol);

  	char opReadL(int clientSD);
    void opWriteL(int clientSD, string l_protocol);
    char opL(int clientSD, string l_protocol, char reverse);

  	string opReadQ(int clientSD);
    void opWriteQ(int clientSD, string q_protocol);
  	string opQ(int clientSD, string q_protocol);

	  string opReadP(int clientSD);
	  void opWriteP(int clientSD, string word, int depth);
	  void opP(int clientSD, string words, int depth, string attribute_name);

	  char opReadC(int clientSD);
    void opWriteC(int clientSD, string c_protocol);
	  char opC(int clientSD, string c_protocol);

	  void opReadKeep(int clientSD); //Keep Alive operation
    void opWriteKeep(int clientSD,int c_port,string c_ip);
	  void opKeep(int clientSD);

	  //Server side

	  void opNS(int clientSD);
	  string opReadNS(int clientSD, std::string& n_protocol, int& pos);
  	void opWriteNS(int clientSD, char is_successful);

  	void opLS(int clientSD);
  	void opReadLS(int clientSD, std::string& l_protocol, int& pos, int& pos_2);
  	void opWriteLS(int clientSD, char is_successful);

  	string opReadQSSlave(int clientSD, char& is_hoja);
  	void opQS(int clientSD);
  	void opReadQS(int clientSD, string &q_protocol, int &pos);
  	void opWriteQS(int clientSD, string result, char is_hoja);

  	void opPS(int clientSD);
  	void opReadPS(int clientSD, string &word_list,int &depth);
  	void opWritePS(int clientSD, string words);

	  void opCS(int clientSD);
	  void opReadCS(int clientSD, string &c_protocol, int &pos);
	  void opWriteCS(int clientSD, string ip_list, int redundance, char use);

    void opSS(int clientSD);
	  void opReadSS(int clientSD);
	  void opWriteSS(int clientSD);
};

#endif // SERVER_H
