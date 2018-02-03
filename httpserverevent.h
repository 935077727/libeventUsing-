#ifndef HTTPSERVEREVENT_H
#define HTTPSERVEREVENT_H


class HttpServerEvent
{
public:
    HttpServerEvent();
    static int startHeepServer(char * host,int port,int timeOut);
private:
    static void  httpHandlerCb(struct evhttp_request *req, void *arg);

};

#endif // HTTPSERVEREVENT_H
