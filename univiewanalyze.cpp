#include "univiewanalyze.h"
#include "common.h"
#include "XmlOpertator.h"


int univiewAnalyze:: m_dataSize;
int univiewAnalyze:: m_cmdId;
int univiewAnalyze:: m_version;
int univiewAnalyze::m_xmlLen;
char  univiewAnalyze::m_xml[BUFF_XML_MAX_SIZE];
int univiewAnalyze::m_imageCount;
int univiewAnalyze::m_nImageSize1;
char  *univiewAnalyze::m_pIamge1;
int univiewAnalyze::m_nImageSize2;
char  *univiewAnalyze::m_pIamge2;
int univiewAnalyze::m_nImageSize3;
char  *univiewAnalyze::m_pIamge3;
int univiewAnalyze::m_nImageSize4;
char  * univiewAnalyze::m_pIamge4;
int univiewAnalyze::m_nImageSize5;
char  *univiewAnalyze::m_pIamge5;
char  univiewAnalyze::m_deviceId[32];


univiewAnalyze::univiewAnalyze()
{

}
int  univiewAnalyze::checkComplate(char*pbuf,int size)
{
    if(htonl(*(((uint32_t*)(pbuf))))!=0x77aa77aa)
    {
        return -1;
    }

    else if(htonl(*(((uint32_t*)(pbuf+size-4))))!=0x77ab77ab)
    {
        return -1;
    }
    return 0;
}
int univiewAnalyze::init()
{
    // int nRet=pthread_create(&m_recvHandleThread,NULL,recvHandleThread,this);
    //    m_pIamge1=(char *) ALLOC(BUFF_IMAGE_MAX_SIZE,sizeof(char));
    //    m_pIamge2=(char *) ALLOC(BUFF_IMAGE_MAX_SIZE,sizeof(char));
    //    m_pIamge3=(char *) ALLOC(BUFF_IMAGE_MAX_SIZE,sizeof(char));
    //    m_pIamge4=(char *) ALLOC(BUFF_IMAGE_MAX_SIZE,sizeof(char));
    //    m_pIamge5=(char *) ALLOC(BUFF_IMAGE_MAX_SIZE,sizeof(char));

}

int univiewAnalyze::getCmdId(char *buf)
{
    m_cmdId= htonl(*(((uint32_t*)(buf+12))));
    return 0;
}
int univiewAnalyze::getDataSize(char *buf)
{
    m_dataSize= htonl(*(((uint32_t*)(buf+4))));
    return 0;
}
int univiewAnalyze::getVersion(char *buf)
{
    m_version= htonl(*(((uint32_t*)(buf+8))));
    return 0;
}
int univiewAnalyze::getXmlSize(char *buf)
{
    m_xmlLen=htonl(*(((uint32_t*)(buf+16))));
    return 0;
}

int univiewAnalyze::getXml(char *buf)
{
    bzero(m_xml,BUFF_XML_MAX_SIZE);
    strcpy(m_xml,buf+20);
    return 0;
}
int univiewAnalyze::getImageCount(char *buf)
{
    m_imageCount=htonl(*(((uint32_t*)(buf+20+m_xmlLen))));
    if(m_imageCount>5)
    {
        return -1;
    }
    return 0;
}
int univiewAnalyze::getImageSize1(char *buf)
{
    m_nImageSize1=htonl(*(((uint32_t*)(buf+20+m_xmlLen+4))));
    return 0;
}
int univiewAnalyze::getImage1(char *buf)
{
    //memcpy(m_pIamge1,buf+20+m_xmlLen+8,m_nImageSize1);
    m_pIamge1=buf+20+m_xmlLen+8;
}
int univiewAnalyze::getImageSize2(char *buf)
{
    m_nImageSize2=htonl(*(((uint32_t*)(m_pIamge1+m_nImageSize1))));
    return 0;
}

int univiewAnalyze::getImage2(char *buf)
{
    //emcpy(m_pIamge2,buf+20+m_xmlLen+8+m_nImageSize1+4,m_nImageSize2);
    m_pIamge2=m_pIamge1+m_nImageSize1+4;
    return 0;
}
int univiewAnalyze::getImageSize3(char *buf)
{
    m_nImageSize3=htonl(*(((uint32_t*)(m_pIamge2+m_nImageSize2))));
    return 0;
}
int univiewAnalyze::getImage3(char *buf)
{
    m_pIamge3=m_pIamge2+m_nImageSize2+4;
    return 0;
    //memcpy(m_pIamge3,m_nImageSize1+4,m_nImageSize3);
    // m_pIamge3=m_pIamge1+m_nImageSize2+4;
    return 0;
}
int univiewAnalyze::getImageSize4(char *buf)
{

    m_nImageSize4=htonl(*(((uint32_t*)(m_pIamge3+m_nImageSize3))));
    return 0;

}
int univiewAnalyze::getImage4(char *buf)
{
    m_pIamge4=m_pIamge3+m_nImageSize3+4;
    return 0;
}
int univiewAnalyze::getImageSize5(char *buf)
{
    m_nImageSize5=htonl(*(((uint32_t*)(m_pIamge4+m_nImageSize4))));
    return 0;
}

int univiewAnalyze::getImage5(char *buf)
{
    m_pIamge5=m_pIamge4+m_nImageSize4+4;
    return 0;
}
int univiewAnalyze::analyze(char *buf)
{
    getCmdId(buf);
    getDataSize(buf);
    getVersion(buf);
    getXmlSize(buf);
    getXml(buf);
    getImageCount(buf);
    if(m_imageCount==-1)
    {
        return 0;
    }
    if(m_imageCount==1)
    {
        getImageSize1(buf);
        getImage1(buf);
    }
    if(m_imageCount==2)
    {
        getImageSize1(buf);
        getImage1(buf);
        getImageSize2(buf);
        getImage2(buf);
    }
    if(m_imageCount==3)
    {
        getImageSize1(buf);
        getImage1(buf);
        getImageSize2(buf);
        getImage2(buf);
        getImageSize3(buf);
        getImage3(buf);
    }
    if(m_imageCount==4)
    {
        getImageSize1(buf);
        getImage1(buf);
        getImageSize2(buf);
        getImage2(buf);
        getImageSize3(buf);
        getImage3(buf);
        getImageSize4(buf);
        getImage4(buf);
    }
    if(m_imageCount==5)
    {
        getImageSize1(buf);
        getImage1(buf);
        getImageSize2(buf);
        getImage2(buf);
        getImageSize3(buf);
        getImage3(buf);
        getImageSize4(buf);
        getImage4(buf);
        getImageSize5(buf);
        getImage5(buf);
    }
    return 0;
}
int univiewAnalyze::getDeviceId(char *buf)
{
    bzero(m_deviceId,32);
    strncpy(m_deviceId,buf+20,32);
    return 0;
}
int univiewAnalyze::makeConnectReply(int cmdId,char *inBuf,int inSize,char*outBuf,int &outSize)
{
    if(cmdId==CMD_CONNECT_SIGNAL)
    {
        memcpy(outBuf,inBuf,inSize);
        *(int *)(outBuf+12) = htonl(CMD_REPLY_CONNECT_SIGNAL);
        outSize=inSize;
        return 0;
    }
}

int univiewAnalyze::makeCommonReply(int cmdId,char*inxml,char*outBuf,int &outSize,int result)
{
    if(cmdId==CMD_TEST)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);
        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;

        outSize = DataTotallen + 12;

        return 0;
    }


    if(cmdId==CMD_PARKINGLOT_STATE)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);
        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;

        outSize = DataTotallen + 12;

        return 0;
    }
    if(cmdId==CMD_PARKINGLOT_STATE)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);
        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;

        outSize = DataTotallen + 12;

        return 0;
    }
    if(cmdId==CMD_REAL_TIME_INFO_ONE)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);
        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;

        outSize = DataTotallen + 12;

        return 0;
    }

    if(cmdId==CMD_REAL_TIME_INFO_TWO)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);

        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;

        outSize = DataTotallen + 12;

        return 0;
    }

    if(cmdId ==CMD_STATE)
    {
        char strCmdId[5]={0};
        char strResult[3]={0};

        sprintf(strCmdId,"%d",cmdId);
        sprintf(strResult,"%d",result);

        XmlOpertator::ReadXml(inxml);
        XmlOpertator::XMLACK(strResult,strCmdId);

        char *pxml=XmlOpertator::m_ACKBollXML;
        char *pcVehBufStart =  outBuf;
        char BeginFlag[5];
        char EndFlag[5];
        uint32_t Xmllen = strlen(pxml);
        uint32_t DataTotallen = 4 + 4 + 4 + Xmllen;
        memset(BeginFlag, 0, 5);
        memset(EndFlag, 0, 5);

        snprintf(BeginFlag, sizeof(BeginFlag), "%c%c%c%c", 0x77, 0xaa, 0x77, 0xaa);
        snprintf(EndFlag, sizeof(EndFlag), "%c%c%c%c", 0x77, 0xab, 0x77, 0xab);

        memcpy(pcVehBufStart, BeginFlag, 4);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(DataTotallen);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(2);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(CMD_REPLY_ACK_RECV);
        pcVehBufStart += 4;

        *(uint32_t *)pcVehBufStart = htonl(Xmllen);
        pcVehBufStart += 4;

        memcpy(pcVehBufStart, pxml, Xmllen);
        pcVehBufStart += Xmllen;

        memcpy(pcVehBufStart, EndFlag, 4);
        pcVehBufStart += 4;


        outSize = DataTotallen + 12;

        return 0;
    }
}

int  univiewAnalyze::analyzeMakeReply(char * inbuf, int insize, char *&outbuf, int &outsize)
{
    outbuf=(char*) ALLOC(1024*2);
    if(outbuf==NULL)
    {
        LightLoger::log_b("outbuf ==NULL");
        return -1;
    }
    int nRet=checkComplate(inbuf,insize);
    if(nRet!=0)
    {
        LightLoger::log_b(" analysz : bad message ,droped!!");
        return -1;
    }
    getCmdId(inbuf);
    switch (m_cmdId) {
    case CMD_CONNECT_SIGNAL:
    {
        LightLoger::log_b("connect signal");
        bzero(outbuf,1024*2);
        makeConnectReply(CMD_CONNECT_SIGNAL,inbuf,insize,outbuf,outsize);
        LightLoger::log_b("connect signal , operate ok return ");
        return 0;
    }
    case CMD_REGISTER:
    {
        LightLoger::log_b("注册：");
        break;
    }
    case CMD_STATE:
    {
        LightLoger::log_b(" cammer status");
        bzero(outbuf,1024*2);
        analyze(outbuf);
        makeCommonReply(CMD_STATE,inbuf+20,outbuf,outsize,0);
        LightLoger::log_b("cammer status operate ok return");
        return 0;
    }
    case CMD_PARKINGLOT_STATE:
    {
        LightLoger::log_b("parking lot status");

        bzero(outbuf,1024*2);
        analyze(outbuf);
        makeCommonReply(CMD_PARKINGLOT_STATE,inbuf+20,outbuf,outsize,0);
        LightLoger::log_b("cammer status operate ok return");
        return 0;
    }
    case CMD_REAL_TIME_INFO_ONE:
    {
        LightLoger::log_b("实时信息 （一张图片）：");
        break;
    }
    case CMD_HISTORY_INFO_ONE:
    {
        LightLoger::log_b("历史信息 （一张图片）");
        break;
    }
    case CMD_HISTORY_INFO_TWO:
    {
        LightLoger::log_b("2");
        break;
    }
    case CMD_REAL_TIME_INFO_TWO:
    {
        LightLoger::log_b("real time info (2 image)");
        bzero(outbuf,1024*2);
        analyze(outbuf);
        makeCommonReply(CMD_REAL_TIME_INFO_TWO,inbuf+20,outbuf,outsize,0);
        LightLoger::log_b("real time info (2 image) operate ok return");
        return 0;
    }
    case CMD_TEST:
    {
        LightLoger::log_b(" test !!");
        bzero(outbuf,1024*2);
        analyze(outbuf);
        makeCommonReply(CMD_TEST,inbuf+20,outbuf,outsize,0);
        LightLoger::log_b("test   operate ok return");
        return 0;

    }
    default:
        LightLoger::log_b("未知 CmdId");
        break;
    }
}


