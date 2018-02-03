#ifndef COMMON_H
#define COMMON_H
#include  <queue>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include "mempoolstr/ncx_slab.h"

extern int g_count;
extern int g_countsend;

#define ALLOC(size)     ncx_slab_alloc(g_mempool, size);\
//                        g_count++;                                  \
//                        printf("g_count= %d\n",g_count);\

#define FREE(p)        ncx_slab_free(g_mempool, p);\
//                       g_count--;\
//                       printf("g_count= %d\n",g_count);\
//                       p=NULL;

//#define ALLOC(size)   malloc(size)
//#define FREE(p)       free(p);

using namespace std;

struct waitDealWithNode
{
    int socket;
    char *buff;
    int buffSize;
};
struct waitReturnNode
{
    int socket;
    char * buff;
    int buffSize;
};

extern  queue<waitDealWithNode> g_queueWaitDealWith;
extern queue<waitReturnNode> g_queueWaitReturn;
extern sem_t g_semWaitDealWith;
extern sem_t g_semWaitReturn;
extern ncx_slab_pool_t *g_mempool;



#endif // COMMON_H
