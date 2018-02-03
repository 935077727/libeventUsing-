#include "common.h"
#include "libeventor.h"
#include "LightLoger.h"
#include "univiewanalyze.h"
#include <pthread.h>
#include "httpserverevent.h"
int main()
{
    size_t 	pool_size=20*1024*1024;
    char * space=(char*)malloc(pool_size);
    g_mempool = (ncx_slab_pool_t*) space;
    g_mempool->addr = space;
    g_mempool->min_shift = 3;
    g_mempool->end = ( unsigned char*)(space + pool_size);

    ncx_slab_init(g_mempool);

    pthread_mutex_init(&(g_mempool->mutex.spin),NULL);


    libeventor *eventor =new libeventor();
    univiewAnalyze *analyzer =new univiewAnalyze();
    analyzer->init();
   // eventor->serverInit(5196,"172.32.4.230",80,20);
     eventor->serverInit("172.32.4.230",80,20);
   // HttpServerEvent::startHeepServer("172.32.4.230",8080,20);

    eventor->dispatch();
}
