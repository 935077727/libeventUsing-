#ifndef LIBEVENTOR_H
#define LIBEVENTOR_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/tcp.h>
#include <sys/queue.h>
#include "libeventstr/event.h"
#include "libeventstr/evhttp.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "LightLoger.h"
#include <list>
#include <pthread.h>
#include "common.h"
#include "univiewanalyze.h"



using namespace std;

#define BUFF_RECV_MAX_SIZE  1024*700

typedef void( *pServerAccept)(int fd, short ev, void *arg);
typedef void( *pServerWrite)(int fd, short ev, void *arg);
typedef void( *pServerRead)(int fd, short ev, void *arg);

struct sock_ev {
    struct event* read_ev;
    struct event* write_ev;
};

struct st_recvNode
{
    int socket;
    int isDone;
    int sendDone;
    char *buff;
    size_t buffSize;
    int offset;
    int waitRecvSize;
    struct event* read_ev;
    struct event* write_ev;
    time_t lastInTime;
};

struct st_package
{
    waitReturnNode * node;
    struct event *write;
};

struct st_sendInfo
{
    int size;
    char *buf;

};

class libeventor
{
public:
    libeventor();
    int serverInit(int port);
    int serverInit(int port,char *httpHost,int httpPort,int httpTomeOut);
    int serverInit(char *httpHost,int httpPort,int httpTomeOut);
    static int SetNonblock(int fd);
    int dispatch();
private:
    static list <st_recvNode> m_clientLsit;
    int  m_listerPort;
    long m_listenAddr;
    int  m_maxConnections;
    int  m_serverSocket;
    pthread_t m_sendHandleThread;
    static struct event m_timer_ev;
    static pServerAccept  m_ServerAccept;
    static pServerWrite m_ServerWrite;
    static pServerRead m_ServerRead;
    static struct event m_listen_ev;
    static struct event_base* m_eventbase;
    static void ServerAccept(int sock, short even, void *arg);
    static void ServerWrite(int sock, short ev, void *arg);
    static void ServerRead(int sock, short ev, void *arg);
    static int checkSocket(int net);
    static int freeEvent(list<st_recvNode>::iterator &it);
    static int deleteFromList(list<st_recvNode>::iterator &it);
    static void *sendHandle(void * argu);
    static void lostConnect_cb(int sock, short event , void *arg);
    static void  httpHandlerCb(struct evhttp_request *req, void *arg);
    static int addWriteEvent(int socket, char * buf, int size);


};

#endif // LIBEVENTOR_H
