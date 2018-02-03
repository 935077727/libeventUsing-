#include "common.h"


queue<waitDealWithNode> g_queueWaitDealWith;
queue<waitReturnNode> g_queueWaitReturn;
sem_t g_semWaitDealWith;
sem_t g_semWaitReturn;
ncx_slab_pool_t *g_mempool;
int g_count=0;
int g_countsend=0;
