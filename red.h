#ifndef RED_H_INCLUDED
#define RED_H_INCLUDED

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <sstream>
#include <thread>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <chrono>
#include <unordered_map>
#include <fstream>
#include <functional>
#include <mutex>

#define ACTION_SIZE 1
#define DATA_SIZE 3
#define ATTRIBUTE_LIST_SIZE 4
#define DATA_LIST_SIZE 4
#define RESPONSE_SIZE 4
#define ATTRIBUTE_SIZE 2
#define REDUNDANCE_SIZE 2
#define USE_SIZE 1
#define SUCCESS_SIZE 1
#define DEPTH_SIZE 1

#define ACT_SND_N 'N'
#define ACT_RCV_N 'n'
#define ACT_SND_L 'L'
#define ACT_RCV_L 'l'
#define ACT_SND_Q 'Q' //Receive query Action
#define ACT_RCV_Q 'q' //Send query Action
#define ACT_SND_P 'P'
#define ACT_RCV_P 'p'
#define ACT_SND_C 'C'
#define ACT_RCV_C 'c'
#define ACT_SND_S 'S'
#define ACT_RCV_S 's'

using namespace std;
#endif // RED_H_INCLUDED
