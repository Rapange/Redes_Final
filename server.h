#ifndef SERVER_H
#define SERVER_H

#include "red.h"


class Server
{
    public:

  int m_n_port, m_l_port, m_q_port, m_p_port, m_c_port, m_s_port, m_keepAlive_port;
  
       int state;
	int id;
	std::vector< std::vector< std::pair < std::string, int > > > m_ip_port;
        std::vector< std::vector< int > > m_sockets;
        
        Server(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port);
        virtual ~Server();

        std::string intToStr(int num, int size);

        void readAll();
	void connectAll();
	
        void iniServerBot();
	void listenForClients(int serverSD, char action);
	
        void iniClientBot();
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

	void opReadP(int clientSD, string words, int depth, string attribute_name);
        void opWriteP(int clientSD, string words, int depth, string attribute_name);
	void opP(int clientSD, string words, int depth, string attribute_name);

	void opReadC(int clientSD, string word);
        void opWriteC(int clientSD, string word);
	void opC(int clientSD, string word);
	
	void opReadKeep(int clientSD); //Keep Alive operation
        void opWriteKeep(int clientSD);
	void opKeep(int clientSD);

	//Server side

	void opNS(int clientSD);
	string opReadNS(int clientSD, std::string& n_protocol, int& pos);
	void opWriteNS(int clientSD, char is_successful);

	void opLS(int clientSD);
	void opReadLS(int clientSD, std::string& l_protocol, int& pos, int& pos_2);
	void opWriteLS(int clientSD, char is_successful);

	void opQS(int clientSD);
	void opReadQS(int clientSD, string &q_protocol, int &pos);
	void opWriteQS(int clientSD, string result);

	void opPS(int clientSD);
	void opReadPS(int clientSD, string words, int depth, string attribute_name);
	void opWritePS(int clientSD, string words, int depth, string attribute_name);

	void opCS(int clientSD);
	void opReadCS(int clientSD, string word);
	void opWriteCS(int clientSD, string word);
	
        void opSS(int clientSD);
	void opReadSS(int clientSD);
	void opWriteSS(int clientSD);

	
};

#endif // CPEER_H
