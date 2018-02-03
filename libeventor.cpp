#include "libeventor.h"
#include "common.h"
#include <signal.h>
#include <time.h>
struct event libeventor::m_listen_ev;
struct event_base* libeventor::m_eventbase;
pServerAccept  libeventor::m_ServerAccept;
pServerWrite libeventor::m_ServerWrite;
pServerRead libeventor::m_ServerRead;
list <st_recvNode> libeventor::m_clientLsit;
struct event libeventor::m_timer_ev;

//#define ALLOC(size)   ncx_slab_alloc(g_mempool, size)
//#define FREE(p)       ncx_slab_free(g_mempool, p);

//#define ALLOC(size)   malloc(size)
//#define FREE(p)       free(p);

libeventor::libeventor()
{
    signal(SIGPIPE, SIG_IGN);
    m_ServerAccept=ServerAccept;
    m_ServerRead=ServerRead;
    m_ServerWrite =ServerWrite;

}

int libeventor::SetNonblock(int fd)
{
    int flags;

    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        return -1;
    }

    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        return -1;
    }
    return 0;
}


void libeventor:: ServerRead(int sock, short event, void *arg)
{

    int size;
    int bfindFlag=0;
//    char * p=(char*)ALLOC(1024*700);
//    int size=recv(sock,p,1024*700,0);
//    printf("recv size =%d \n",size);
//    FREE(p);
//    return ;


    list<st_recvNode>::iterator it=m_clientLsit.begin();

    for(;it!=m_clientLsit.end();it++)
    {
        if((*it).socket==sock)
        {
            bfindFlag=1;
            break;

        }

    }
    if(bfindFlag==0)
    {
        LightLoger::log_bint("can not find  this socket:%d",sock);
        return ;
    }
    if((*it).sendDone!=1)
    {
        LightLoger::log_b("last send is not finish yet ,wait.... ");
        return ;
    }
    (*it).lastInTime=time(0);
    if((*it).isDone==1)
    {
        (*it).buff=(char*)ALLOC(BUFF_RECV_MAX_SIZE);
        if((*it).buff==NULL)
        {
            ncx_slab_stat_t t;
            ncx_slab_stat(g_mempool,&t);
           // g_countsend--;
            LightLoger::log_b("do not have enouth mem");
            return ;
        }
        bzero((*it).buff,BUFF_RECV_MAX_SIZE);
        size = recv(sock, (*it).buff,8, 0);
        if(checkSocket(size)!=0)
        {

            freeEvent(it);
            close(sock);
            FREE((*it).buff);
            deleteFromList(it);
            return;
        }
        if(htonl(*(((uint32_t*)((*it).buff))))!=0x77aa77aa)
        {
            LightLoger::log_b("illegal head ,lose connect");
            freeEvent(it);
            close(sock);
            FREE((*it).buff);
            deleteFromList(it);
            return;
        }
        if(size!=8)
        {
            LightLoger::log_bint("recv lenth is  %d ，数据非法 重新接收",size);
            FREE((*it).buff);
            return;
        }
        (*it).waitRecvSize=htonl(*(((uint32_t*)((*it).buff+4))))+4;
        if((*it).waitRecvSize>BUFF_RECV_MAX_SIZE-1024||(*it).waitRecvSize<=0)
        {
            LightLoger::log_b(" recv wrong size,giveup this recv");
            FREE((*it).buff);
            return;
        }
        (*it).isDone=0;
        (*it).buffSize= (*it).waitRecvSize+8;
        (*it).offset=8;
        return ;

    }
    else if((*it).isDone==0)
    {
        size = recv(sock, (*it).buff+(*it).offset,(*it).waitRecvSize, 0);
        if(checkSocket(size)!=0)
        {
            freeEvent(it);
            close(sock);
            FREE((*it).buff);
            deleteFromList(it);
            return;
        }
        (*it).isDone=0;
        (*it).waitRecvSize=(*it).waitRecvSize-size;
        (*it).offset=(*it).offset+size;
        if((*it).waitRecvSize==0)
        {
            (*it).isDone=1;
            LightLoger::log_b(" recv scuess ,start to analyze!!");
            char * psendbuff;
            int sendsize;
//            g_countsend++;
//            LightLoger::log_bint("recv : g_countsend =%d ",g_countsend);
            int nRet= univiewAnalyze::analyzeMakeReply((*it).buff,(*it).offset,psendbuff,sendsize);
            if(nRet!=0)
            {
                FREE(psendbuff);
                FREE((*it).buff);
                LightLoger::log_b("failed: analyze failed");
                //exit(-1);
                return;
            }

            nRet=addWriteEvent(sock,psendbuff,sendsize);
            if(nRet!=0)
            {
                FREE(psendbuff);
                FREE((*it).buff);
                LightLoger::log_b("failed: add write event failed");
                //exit(-1);
                return;
            }
            (*it).sendDone=0;
            FREE((*it).buff);
            return ;
        }
        else if((*it).waitRecvSize<0)
        {
            LightLoger::log_bint("pack package failed ,give up this recv",(*it).waitRecvSize);
            (*it).isDone=1;
            FREE((*it).buff);
        }

    }
}


void libeventor::ServerWrite(int sock, short event, void *arg)
{
//    g_countsend--;
//    LightLoger::log_bint("send: g_countsend =%d ",g_countsend);

    int bfindFlag=0;

    list<st_recvNode>::iterator it=m_clientLsit.begin();

    for(;it!=m_clientLsit.end();it++)
    {
        if((*it).socket==sock)
        {
            bfindFlag=1;
            break;

        }

    }
    if(bfindFlag==0)
    {
        LightLoger::log_bint("can not find  this socket:%d",sock);
        return ;
    }

    st_sendInfo *info= (st_sendInfo *)arg;
    LightLoger::log_bint("need send size is %d",info->size);
    int nRet=send(sock, info->buf, info->size, MSG_NOSIGNAL);
    LightLoger::log_bint("already send is %d",nRet);
    FREE(info->buf);
    FREE(info);

    (*it).sendDone=1;

    return ;
}


void libeventor::ServerAccept(int sock, short even, void *arg)
{
    st_recvNode node;
    struct sockaddr_in cli_addr;
    int newfd, sin_size;

    sin_size = sizeof(struct sockaddr_in);
    newfd = accept(sock, (struct sockaddr*)&cli_addr, (socklen_t*)&sin_size);
    if(newfd<0)
    {
        LightLoger::log_b("accept error :",(char *)(strerror(errno)));
        return;
    }
    node.socket=newfd;
    node.buff=NULL;//=(char *)calloc(BUFF_RECV_MAX_SIZE,sizeof(char));
    node.buffSize=0;
    node.isDone=1;
    node.offset=0;
    node.waitRecvSize=0;
    node.write_ev=(struct event*)ALLOC(sizeof(struct event));
    node.read_ev=(struct event*)ALLOC(sizeof(struct event));
    node.lastInTime=time(NULL);
    node.sendDone=1;
    m_clientLsit.push_back(node);
    event_set(node.read_ev, newfd, EV_READ|EV_PERSIST, m_ServerRead, NULL);
    event_base_set(m_eventbase, node.read_ev);
    event_add(node.read_ev, NULL);

    LightLoger::log_b("Accepted connection from\n", (char *)inet_ntoa(cli_addr.sin_addr));
}

int libeventor::serverInit(int port)
{
    int nRet;
    struct sockaddr_in my_addr;

    m_serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (m_serverSocket == -1) {
        LightLoger::log_b("socket(): can not create server socket\n");
        return -1;
    }

    int yes = 1;
    setsockopt(m_serverSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int));
    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    nRet=bind(m_serverSocket, (struct sockaddr*)&my_addr, sizeof(struct sockaddr));
    if(nRet!=0)
    {
        close(m_serverSocket);
        LightLoger::log_b("bind(): can not bind server socket");
        return -1;
    }

    if (listen(m_serverSocket, 1000) == -1) {
        LightLoger::log_b("listen(): can not listen server socket");
        close(m_serverSocket);
        return -1;
    }

    nRet= SetNonblock(m_serverSocket);
    if(nRet!=0)
    {
        printf("setsockopt(): TCP_NODELAY\n", (char *)strerror(errno));
        close(m_serverSocket);
        return -1;
    }


    m_eventbase = event_init();
    event_set(&m_listen_ev, m_serverSocket, EV_READ|EV_PERSIST,m_ServerAccept, NULL);
    event_base_set(m_eventbase, &m_listen_ev);
    event_add(&m_listen_ev, NULL);

    evtimer_set(&m_timer_ev, lostConnect_cb, &m_timer_ev);
    event_base_set(m_eventbase, &m_timer_ev);
    struct timeval timer_v;
    timer_v.tv_sec = 30;
    timer_v.tv_usec = 0;
    evtimer_add(&m_timer_ev, &timer_v);


    LightLoger::log_b(" set listering event scuess ");
    LightLoger::log_b(" start send Thread scuess ");
    return 0;
}
int libeventor::dispatch()
{
    event_base_dispatch(m_eventbase);
}
int libeventor::checkSocket(int ret)
{
    if (ret == 0) {
        LightLoger::log_b(" disconnect info： ",(char *)(strerror(errno)));
        return -1;
    }
    else if((ret<0)&&((errno == EINTR || errno == EWOULDBLOCK || errno == EAGAIN)))
    {
        LightLoger::log_b("this recv is not complate ，continue");
        return 0;
    }
    else  if(ret<0)
    {
        LightLoger::log_b(" read error info :",(char *)(strerror(errno)));
        return -1;
    }
    else
    {
        return 0;
    }
}


int libeventor::freeEvent(list<st_recvNode>::iterator &it)
{
    event_del((*it).read_ev);
    event_del((*it).write_ev);
    FREE((*it).read_ev);
    FREE((*it).write_ev);
}
int libeventor::deleteFromList(list<st_recvNode>::iterator &it)
{
    it =m_clientLsit.erase(it);
    return 0;
}

int libeventor::addWriteEvent(int socket,char * buf,int size)
{
    st_sendInfo * pInfo=(st_sendInfo *)ALLOC(sizeof(st_sendInfo));
    int bfindFlag=0;
    list<st_recvNode>::iterator it=m_clientLsit.begin();

    for(;it!=m_clientLsit.end();it++)
    {
        if((*it).socket==socket)
        {
            bfindFlag=1;
            break;
        }

    }
    if(bfindFlag==0)
    {
        FREE(pInfo);
        LightLoger::log_bint("can not find this socket:%d",socket);
        return  -1;
    }

    pInfo->buf=buf;
    pInfo->size=size;
    event_set((*it).write_ev,socket, EV_WRITE,m_ServerWrite,(void*)pInfo);
    int nRet= event_base_set(m_eventbase, (*it).write_ev);
    if(nRet!=0)
    {
        FREE(pInfo);
        LightLoger::log_b("event_base_set failed");
        return -1;
    }
    if(event_add((*it).write_ev, NULL)!=0)
    {
        FREE(pInfo);
        LightLoger::log_b( "event_add failed ");
        return -1;
    }
    return 0;

}
void libeventor::lostConnect_cb(int sock, short event , void *arg)
{
    LightLoger::log_b("checking the outTime dev ..........");
    ncx_slab_stat_t t;
    ncx_slab_stat(g_mempool,&t);
    list<st_recvNode>::iterator it=m_clientLsit.begin();
    time_t currentTime=time(0);

    for(;it!=m_clientLsit.end();)
    {
        if(currentTime-(*it).lastInTime>60)
        {
            LightLoger::log_bint("this socket is outTime, Disconnect this connection %d",(*it).socket);

            freeEvent(it);
            close((*it).socket);
            if((*it).isDone==0)
            {
                FREE((*it).buff);
            }
            deleteFromList(it);
        }
        else
        {
            it++;
        }

    }

    evtimer_set(&m_timer_ev, lostConnect_cb, &m_timer_ev);
    event_base_set(m_eventbase, &m_timer_ev);
    struct timeval timer_v;
    timer_v.tv_sec = 30;
    timer_v.tv_usec = 0;
    evtimer_add(&m_timer_ev, &timer_v);
}

void  libeventor::httpHandlerCb(struct evhttp_request *req, void *arg)
{

    char output[2048] ={0};
    char tmp[1024]={0};

    //获取客户端请求的URI(使用evhttp_request_uri或直接req->uri)
    const char *uri;
    uri = evhttp_request_uri(req);
    sprintf(tmp, "uri=%s\n", uri);
    strcat(output, tmp);

    sprintf(tmp, "uri=%s\n", req->uri);
    strcat(output, tmp);
    //decoded uri
    char *decoded_uri;
    decoded_uri = evhttp_decode_uri(uri);
    sprintf(tmp, "decoded_uri=%s\n", decoded_uri);
    strcat(output, tmp);

    //解析URI的参数(即GET方法的参数)
    struct evkeyvalq params;
    evhttp_parse_query(decoded_uri, &params);
    sprintf(tmp, "q=%s\n", evhttp_find_header(&params, "q"));
    strcat(output, tmp);
    sprintf(tmp, "s=%s\n", evhttp_find_header(&params, "s"));
    strcat(output, tmp);
    free(decoded_uri);

    //获取POST方法的数据
    char *post_data = (char *) EVBUFFER_DATA(req->input_buffer);
    sprintf(tmp, "post_data=%s\n", post_data);
    strcat(output, tmp);

    /*
    具体的：可以根据GET/POST的参数执行相应操作，然后将结果输出
    ...
    */

    /* 输出到客户端 */

    //HTTP header
    evhttp_add_header(req->output_headers, "Server", "SOONG v1.00");
    evhttp_add_header(req->output_headers, "Content-Type", "text/plain; charset=UTF-8");
    evhttp_add_header(req->output_headers, "Connection", "close");
    //输出的内容
    struct evbuffer *buf;
    buf = evbuffer_new();
    evbuffer_add_printf(buf, "%s", output);
    evhttp_send_reply(req, HTTP_OK, "OK", buf);
    evbuffer_free(buf);
}


int libeventor::serverInit(int port,char *httpHost,int httpPort,int httpTomeOut)
{
    serverInit(port);
    char *httpd_option_listen = httpHost;
    int httpd_option_port = httpPort;
    int httpd_option_timeout = httpTomeOut; //in seconds


    struct evhttp *httpd;
    httpd = evhttp_start(httpd_option_listen, httpd_option_port);
    if(httpd==NULL)
    {
        LightLoger::log_b("statrt http server failed :httpd =NULL ");
        return -1;
    }
    evhttp_set_timeout(httpd, httpd_option_timeout);

    //指定generic callback
    evhttp_set_gencb(httpd,httpHandlerCb, NULL);
    return 0;
}
int libeventor::serverInit(char *httpHost,int httpPort,int httpTomeOut)
{
    //serverInit(port);
    m_eventbase= event_init();
    char *httpd_option_listen = httpHost;
    int httpd_option_port = httpPort;
    int httpd_option_timeout = httpTomeOut; //in seconds


    struct evhttp *httpd;
    httpd = evhttp_start(httpd_option_listen, httpd_option_port);
    if(httpd==NULL)
    {
        LightLoger::log_b("statrt http server failed :httpd =NULL ");
        return -1;
    }
    evhttp_set_timeout(httpd, httpd_option_timeout);

    //指定generic callback
    evhttp_set_gencb(httpd,httpHandlerCb, NULL);
    return 0;
}
