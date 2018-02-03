#ifndef __XMLOPERTATOR_H__
#define __XMLOPERTATOR_H__

#include "tinyxml.h"
#include <iostream>
#include <string.h>
#include <iterator>
#include <vector>
using namespace std;

class XmlOpertator
{
public:
private:
public:
    static char m_Carplate[64];
    static char m_PlateConfidence[8];
    static char m_PlateType[8];
    static char m_PlateColor[8];
    static char m_llegalTime[64];
    static char m_llegalTyte[16];
    static char m_PlaceCode[64];
    static char m_Recordid[32];
    static char m_Camid[64];
    static char m_TotalPicNum[8];
    static char m_PicType1[8];
    static char m_ossPicPath1[1024];
    static char m_ossPicPath2[1024];
    static char m_ossPicPath3[1024];
    static char m_ossPicPath4[1024];
    static char m_ossPicPath5[1024];
    static char m_ACKBollXML[1024];
    static char m_Send2ServerXml[1024*10];
    static char m_XMlHeartCheckToGai[1024 * 2];

public:
	XmlOpertator();
	~XmlOpertator();
	//static unsigned char *
    static bool ReadXml(char * buf);
    static void XMLACK(char *result,char *cmdid);
	void DestoryObject(){ delete this; }
	void Send2ServerXml(unsigned long num);
	void XmlHeartCheckToGaiLaoBan(vector<string> *vec);
private:
    static bool getCamid(char * buf);
    static bool getPlateConfidence(char * buf);
    static bool getPlateType(char * buf);
    static bool getPlateColor(char * buf);
    static bool getllegalTime(char * buf);
    static bool getllegalTyte(char * buf);
    static bool getPlaceCode(char * buf);
    static bool getRecordid(char * buf);
    static bool getTotalPicNum(char * buf);
    static bool getCarPlate(char *buf);
    static bool getPicType1(char *buf);
    static bool getossPicPath1();
    static bool getossPicPath2();
    static bool getossPicPath3();
    static bool getossPicPath4();
    static bool getossPicPath5();
	

};


#endif
