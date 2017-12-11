#ifndef CLIENT_H
#define CLIENT_H

#include "red.h"

class Client
{
    public:

  int m_n_port, m_l_port, m_q_port, m_p_port, m_c_port, m_s_port, m_keepAlive_port;
  
       int state;
	int id;

        std::vector< int > m_sockets;
        
        Client(int n_port, int l_port, int q_port, int p_port, int c_port, int s_port, int keepAlive_port);
        virtual ~Client();

        std::string intToStr(int num, int size);

        

        void iniServerBot();
	void listenForClients(int serverSD, char action);
	
        void iniClientBot(char action, vector<string>& arguments);
        int createClientSocket(int portNumber, string serverIP);
        int createServerSocket(int portNumber);
        bool isNum(string word);
	//Client side
	
        char opReadN(int clientSD);
        void opWriteN(int clientSD, string word, string attributes);
	char opN(int clientSD, string word, string attributes);

	char opReadL(int clientSD);
        void opWriteL(int clientSD, string word, string word2);
        char opL(int clientSD, string word, string word2);

	string opReadQ(int clientSD, char &is_hoja);
        void opWriteQ(int clientSD, string word, int depth, char attributes);
	string opQ(int clientSD, string word, int depth, char attributes);

        string opReadP(int clientSD);
        void opWriteP(int clientSD, vector<string> &p_words);
	void opP(int clientSD, string words, int depth, string attribute_name);

	void opReadC(int clientSD, string &ip_list, int &redundance, char& use);
        void opWriteC(int clientSD, string word);
	void opC(int clientSD, string word);

	void opReadS(int clientSD, string &result);
	void opWriteS(int clientSD);
	void opS(int clientSD);
	
	void opReadKeep(int clientSD); //Keep Alive operation
        void opWriteKeep(int clientSD);
	void opKeep(int clientSD);

	//Server side

	void opNS(int clientSD, string word, string attributes);
	void opReadNS(int clientSD, string word, string attributes);
	void opWriteNS(int clientSD, string word, string attributes);

	void opLS(int clientSD, string word, string word2, string attributes);
	void opReadLS(int clientSD, string word, string word2, string attributes);
	void opWriteLS(int clientSD, string word, string word2, string attributes);

	void opQS(int clientSD, string word, int depth, bool attributes);
	void opReadQS(int clientSD, string word, int depth, bool attributes);
	void opWriteQS(int clientSD, string word, int depth, bool attributes);

	void opPS(int clientSD, string words, int depth, string attribute_name);
	void opReadPS(int clientSD, string words, int depth, string attribute_name);
	void opWritePS(int clientSD, string words, int depth, string attribute_name);

	void opCS(int clientSD, string word);
	void opReadCS(int clientSD, string word);
	void opWriteCS(int clientSD, string word);
	
        

	
};

#endif // CPEER_H
