#ifndef UNIVIEWANALYZE_H
#define UNIVIEWANALYZE_H
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "LightLoger.h"
#include "libeventor.h"

#define CMD_HEAD             0x77aa77aa
#define CMD_END              0x77ab77ab

#define CMD_REGISTER         100
#define CMD_CONNECT_SIGNAL   101
#define CMD_STATE            103
#define CMD_PARKINGLOT_STATE 104
#define CMD_REPLY_CTRL       105

#define CMD_TEST              111

#define CMD_REAL_TIME_INFO_ONE  115
#define CMD_HISTORY_INFO_ONE    116

#define CMD_REAL_TIME_INFO_TWO  118
#define CMD_HISTORY_INFO_TWO    119

#define CMD_UPDATA_INFO         151

#define CMD_REPLY_REGISTER       500
#define CMD_REPLY_CONNECT_SIGNAL 501
#define CMD_REPLY_PROOF_TIME     502
#define CMD_REPLY_CTRL           505
#define CMD_REPLY_INFO           511
#define CMD_REPLY_ACK_RECV       512
#define CMD_REPLY_UPDATA         581

#define BUFF_IMAGE_MAX_SIZE      1024*200
#define BUFF_XML_MAX_SIZE        1024*10

class univiewAnalyze
{
public:
    univiewAnalyze();
    int init();
    static int analyzeMakeReply(char * inbuf, int insize, char *&outbuf, int &outsize);
private:
    static int checkComplate(char*pbuf,int size);
    static void *recvHandleThread(void *arg);
    static  int getCmdId(char *buf);
    static int getDataSize(char *buf);
    static int getVersion(char *buf);
    static int getXmlSize(char *buf);
    static int getXml(char *buf);
    static int getImageCount(char *buf);
    static int getImageSize1(char *buf);
    static int getImage1(char *buf);
    static int getImageSize2(char *buf);
    static int getImage2(char *buf);
    static int getImageSize3(char *buf);
    static int getImage3(char *buf);
    static int getImageSize4(char *buf);
    static int getImage4(char *buf);
    static int getImageSize5(char *buf);
    static int getImage5(char *buf);
    static int getDeviceId(char *buf);
    static int analyze(char *buf);

    static int makeConnectReply(int cmdId, char *inBuf, int inSize, char*outBuf, int &outSize);
    static int makeCommonReply(int cmdId, char *inxml, char*outBuf, int &outSize, int result);

public:
    static  int m_dataSize;
    static int  m_cmdId;
    static int  m_version;
    static int m_xmlLen;
    static  char m_xml[BUFF_XML_MAX_SIZE];
    static int m_imageCount;
    static int m_nImageSize1;
    static  char *m_pIamge1;
    static int m_nImageSize2;
    static char *m_pIamge2;
    static int m_nImageSize3;
    static  char *m_pIamge3;
    static int m_nImageSize4;
    static  char *m_pIamge4;
    static  int m_nImageSize5;
    static char *m_pIamge5;
    static  char m_deviceId[32];

};

#endif // UNIVIEWANALYZE_H
