#include "XmlOpertator.h"
#include <stdlib.h>
#include <string>
#include <time.h>


 char XmlOpertator:: m_Carplate[64];
 char XmlOpertator:: m_PlateConfidence[8];
 char XmlOpertator:: m_PlateType[8];
 char XmlOpertator:: m_PlateColor[8];
 char XmlOpertator:: m_llegalTime[64];
 char XmlOpertator:: m_llegalTyte[16];
 char XmlOpertator:: m_PlaceCode[64];
 char XmlOpertator:: m_Recordid[32];
 char XmlOpertator:: m_Camid[64];
 char XmlOpertator:: m_TotalPicNum[8];
 char XmlOpertator:: m_PicType1[8];
 char XmlOpertator:: m_ossPicPath1[1024];
 char XmlOpertator:: m_ossPicPath2[1024];
 char XmlOpertator:: m_ossPicPath3[1024];
 char XmlOpertator:: m_ossPicPath4[1024];
 char XmlOpertator:: m_ossPicPath5[1024];
 char XmlOpertator:: m_ACKBollXML[1024];
 char XmlOpertator:: m_Send2ServerXml[1024*10];
 char XmlOpertator:: m_XMlHeartCheckToGai[1024 * 2];


using namespace std;
XmlOpertator::XmlOpertator()
{

}
XmlOpertator::~XmlOpertator()
{

}
bool XmlOpertator::ReadXml(char * buf)
{
	getCamid( buf);
	getPlateConfidence( buf);
	getPlateType( buf);
	getPlateColor( buf);
	getllegalTime(buf);
	getllegalTyte(buf);
	getPlaceCode(buf);
	getRecordid( buf);
	getTotalPicNum(buf);
	getPicType1(buf);
	getCarPlate(buf);
//	getossPicPath1();
//	getossPicPath2();
//	getossPicPath3();
//	getossPicPath4();
//	getossPicPath5();
	//printf("%s",m_Carplate);
	return true;
}
bool XmlOpertator::getCamid(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		return false;
	}
	memset(m_Camid, 0,64);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{

		 elemname = elem->Value();
		if (strcmp(elemname.c_str(), "TollgateID") == 0)
		{
			attr = elem->GetText();
			if (attr != NULL)
			strcpy(m_Camid, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getPlateConfidence(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_PlateConfidence, 0, 8);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		 elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PlateConfidence") == 0)
		{
			attr = elem->GetText();
			if (attr!=NULL)
			strcpy(m_PlateConfidence, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;

}
bool XmlOpertator::getPlateType(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_Recordid, 0, 32);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		 elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PlateType") == 0)
		{
			attr = elem->GetText();
			strcpy(m_PlateType, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getPlateColor(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_PlateColor, 0,8);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		 elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PlateColor") == 0)
		{
			attr = elem->GetText();
			strcpy(m_PlateColor, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getllegalTime(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		delete pdoc;
		return false;
	}
	memset(m_llegalTime, 0, 64);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PassTime") == 0)
		{
			attr = elem->GetText();
			strcpy(m_llegalTime, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getllegalTyte(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_llegalTyte, 0, 16);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(), "DriveStatus") == 0)
		{
			attr = elem->GetText();
			strcpy(m_llegalTyte, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getPlaceCode(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		return false;
	}
	memset(m_PlaceCode, 0, 64);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		 elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PlaceCode") == 0)
		{
			attr = elem->GetText();
			if (attr != NULL)
			strcpy(m_PlaceCode, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getRecordid(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_Recordid, 0, 32);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(), "RecordID") == 0)
		{
			attr = elem->GetText();
			strcpy(m_Recordid, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getTotalPicNum(char * buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_TotalPicNum, 0, 8);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(), "PicNumber") == 0)
		{
			attr = elem->GetText();
			strcpy(m_TotalPicNum, attr);
			pdoc->Clear();
			delete pdoc;
			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getCarPlate(char *buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	memset(m_Carplate, 0, 64);
	TiXmlElement *elem = root->FirstChildElement();
	string elemname;
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(), "CarPlate") == 0)
		{
			attr = elem->GetText();
			strcpy(m_Carplate, attr);
			pdoc->Clear();
			delete pdoc;

			return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
bool XmlOpertator::getPicType1(char *buf)
{
	const char *attr;
	TiXmlDocument *pdoc = new TiXmlDocument;
	TiXmlElement *imageFirst;
	TiXmlElement *imageNext;
	pdoc->Parse(buf);
	TiXmlElement *root = pdoc->FirstChildElement();
	if (root == NULL)
	{
		pdoc->Clear();
		return false;
	}
	string elemname;
	int i=0;
	memset(m_PicType1,0,8);
	TiXmlElement *elem = root->FirstChildElement();
	for (elem = root->FirstChildElement(); elem != NULL; elem = elem->NextSiblingElement())
	{
		elemname = elem->Value();
		if (strcmp(elemname.c_str(),"Image")==0)
		{	
			imageFirst = elem;
			for (imageNext=imageFirst; imageNext != NULL;imageNext=imageNext->NextSiblingElement())
			{
				if (strcmp(imageNext->Value(), "Image") != 0)
				{
						if (strlen(m_PicType1) != 0)
						{
							pdoc->Clear();
							delete pdoc;
							return true;
						}
						pdoc->Clear();
						delete pdoc;
						return false;
					
				}
				for (elem = imageNext->FirstChildElement();elem!=NULL;elem=elem->NextSiblingElement())
				{
					
					if (strcmp(elem->Value(),"ImageType")==0)
					{
						m_PicType1[i] = *elem->GetText();
						i++;

						//strcat(m_PicType1,elem->GetText());
					}
				}
			}
			//return true;
		}
	}
	pdoc->Clear();
	delete pdoc;
	return false;
}
//bool XmlOpertator::getPicType2();
//bool XmlOpertator::getPicType3();
//bool XmlOpertator::getPicType4();
//bool XmlOpertator::getPicType5();
bool XmlOpertator::getossPicPath1()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m/%d/", localtime(&t));
	char a[8] = { 0 };
	a[0] = *m_PicType1;
	memset(m_ossPicPath1,0,1024);
	strcat(m_ossPicPath1, tmp);
	strcat(m_ossPicPath1, m_Camid);
	strcat(m_ossPicPath1, "-");
	strcat(m_ossPicPath1,m_Recordid) ;
	strcat(m_ossPicPath1,"-");	
	strcat(m_ossPicPath1, "1");
	strcat(m_ossPicPath1, "-");
	strcat(m_ossPicPath1,a);
	//strcat(m_ossPicPath1, "-");

	//strcat(m_ossPicPath1, m_llegalTime);
	//strcat(m_ossPicPath1, m_Carplate);
	strcat(m_ossPicPath1,".jpg");
	//strcat(m_ossPicPath1, "-");
	//strcat(m_ossPicPath1, m_llegalTime);
	return true;
}
bool XmlOpertator::getossPicPath2()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m/%d/", localtime(&t));
	char a[8] = { 0 };
	a[0] = *(m_PicType1+1);
	memset(m_ossPicPath2, 0, 1024);
	strcat(m_ossPicPath2, tmp);
	strcat(m_ossPicPath2, m_Camid);
	strcat(m_ossPicPath2, "-");
	strcat(m_ossPicPath2, m_Recordid);
	strcat(m_ossPicPath2, "-");
	strcat(m_ossPicPath2, "2");
	strcat(m_ossPicPath2, "-");
	strcat(m_ossPicPath2, a);
	//strcat(m_ossPicPath2, "-");
	//strcat(m_ossPicPath2, m_llegalTime);
	//strcat(m_ossPicPath2, m_Carplate);
	strcat(m_ossPicPath2, ".jpg");
	//strcat(m_ossPicPath2, "-");
	//strcat(m_ossPicPath2, m_llegalTime);
	return true;
}
bool XmlOpertator::getossPicPath3()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m/%d/", localtime(&t));
	char a[8] = { 0 };
	a[0] = *(m_PicType1 + 2);
	memset(m_ossPicPath3, 0, 1024);
	strcat(m_ossPicPath3, tmp);
	strcat(m_ossPicPath3, m_Camid);
	strcat(m_ossPicPath3, "-");
	strcat(m_ossPicPath3, m_Recordid);
	strcat(m_ossPicPath3, "-");
	strcat(m_ossPicPath3, "3");
	strcat(m_ossPicPath3, "-");
	strcat(m_ossPicPath3, a);
	//strcat(m_ossPicPath3, "-");
	//strcat(m_ossPicPath3, m_llegalTime);
	//strcat(m_ossPicPath3, m_Carplate);
	strcat(m_ossPicPath3, ".jpg");
	//strcat(m_ossPicPath3, "-");
	//strcat(m_ossPicPath3, m_llegalTime);
	return true;
}
bool XmlOpertator::getossPicPath4()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m/%d/", localtime(&t));
	char a[8] = { 0 };
	a[0] = *(m_PicType1 + 3);
	memset(m_ossPicPath4, 0, 1024);
	strcat(m_ossPicPath4, tmp);
	strcat(m_ossPicPath4, m_Camid);
	strcat(m_ossPicPath4, "-");
	strcat(m_ossPicPath4, m_Recordid);
	strcat(m_ossPicPath4, "-");
	strcat(m_ossPicPath4, "4");
	strcat(m_ossPicPath4, "-");
	strcat(m_ossPicPath4, a);
	//strcat(m_ossPicPath4, "-");
	//strcat(m_ossPicPath4, m_llegalTime);
	//strcat(m_ossPicPath4, m_Carplate);
	strcat(m_ossPicPath4, ".jpg");
	//strcat(m_ossPicPath4, "-");
	//strcat(m_ossPicPath4, m_llegalTime);
	return true;
}
bool XmlOpertator::getossPicPath5()
{
	time_t t = time(0);
	char tmp[64];
	strftime(tmp, sizeof(tmp), "%Y%m/%d/", localtime(&t));
	char a[8] = { 0 };
	a[0] = *(m_PicType1 + 4);
	memset(m_ossPicPath5, 0, 1024);
	strcat(m_ossPicPath5, tmp);
	strcat(m_ossPicPath5, m_Camid);
	strcat(m_ossPicPath5, "-");
	strcat(m_ossPicPath5, m_Recordid);
	strcat(m_ossPicPath5, "-");
	strcat(m_ossPicPath5, "5");
	strcat(m_ossPicPath5, "-");
	strcat(m_ossPicPath5, a);
	//strcat(m_ossPicPath5, "-");
	//strcat(m_ossPicPath5, m_llegalTime);
	//strcat(m_ossPicPath5, m_Carplate);
	strcat(m_ossPicPath5, ".jpg");
	//strcat(m_ossPicPath5, "-");
	//strcat(m_ossPicPath5, m_llegalTime);
	return true;
}

void XmlOpertator::XMLACK(char *result,char *cmdid)
{
	memset(m_ACKBollXML,0,1024);

	TiXmlDocument * pdoc = new TiXmlDocument;
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
	pdoc->LinkEndChild(pDeclaration);
    TiXmlElement *root = new TiXmlElement("Response");
	pdoc->LinkEndChild(root);

	TiXmlElement *pelem = new TiXmlElement("CamID");
	TiXmlText * pelemcontext = new TiXmlText(m_Camid);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("RecordID");
	pelemcontext = new TiXmlText(m_Recordid);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("Result");
	pelemcontext = new TiXmlText(result);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("ReqCmdID");
	pelemcontext = new TiXmlText(cmdid);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("DBRecordID");
	pelemcontext = new TiXmlText(" ");
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	TiXmlPrinter printer;
	printer.SetIndent(0); // 设置缩进字符，设为 0 表示不使用缩进。默认为 4个空格，也可设为'\t'  
	pdoc->Accept(&printer);

	strcpy(m_ACKBollXML,printer.CStr());

	pdoc->Clear();
	delete pdoc;


}

void XmlOpertator::Send2ServerXml(unsigned long num)
{
	memset(m_Send2ServerXml, 0, 1024*10);

	TiXmlDocument * pdoc = new TiXmlDocument;
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
	pdoc->LinkEndChild(pDeclaration);
	TiXmlElement *root = new TiXmlElement("root");
	pdoc->LinkEndChild(root);

	TiXmlElement *pelem = new TiXmlElement("devID");
	TiXmlText * pelemcontext = new TiXmlText(m_Camid);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("cmdID");
	pelemcontext = new TiXmlText("600");
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("recordID");
	pelemcontext = new TiXmlText(m_Recordid);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("carPlate");
	pelemcontext = new TiXmlText(m_Carplate);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("illegalTime");
	pelemcontext = new TiXmlText(m_llegalTime);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("illegalType");
	pelemcontext = new TiXmlText(m_llegalTyte);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("plateConfidence");
	pelemcontext = new TiXmlText(m_PlateConfidence);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("placeCode");
	pelemcontext = new TiXmlText(m_PlaceCode);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("plateColor");
	pelemcontext = new TiXmlText(m_PlateColor);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("picNum");
	pelemcontext = new TiXmlText(m_TotalPicNum);
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("picture");
	root->LinkEndChild(pelem);
	TiXmlElement *pPic=pelem;
	
	if (num == 2)
	{
		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath1);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath2);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);
	}

	if (num == 3)
	{
		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath1);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath2);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath3);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);
	}
	if (num == 4)
	{
		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath1);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath2);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath3);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath4);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);
	}
	if (num == 5)
	{
		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath1);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath2);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath3);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath4);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);

		pelem = new TiXmlElement("pic");
		pelemcontext = new TiXmlText(m_ossPicPath5);
		pelem->LinkEndChild(pelemcontext);
		pPic->LinkEndChild(pelem);
	}

	TiXmlPrinter printer;
	printer.SetIndent(0); // 设置缩进字符，设为 0 表示不使用缩进。默认为 4个空格，也可设为'\t'  
	pdoc->Accept(&printer);

	strcpy(m_Send2ServerXml, printer.CStr());

	pdoc->Clear();
	delete pdoc;
}
void XmlOpertator::XmlHeartCheckToGaiLaoBan(vector<string> *vec)
{
	memset(m_XMlHeartCheckToGai, 0, 1024 * 2);
	string str_num;
	char num[8];
	TiXmlDocument * pdoc = new TiXmlDocument;
	TiXmlDeclaration *pDeclaration = new TiXmlDeclaration("1.0", "UTF-8", "yes");
	pdoc->LinkEndChild(pDeclaration);
	TiXmlElement *root = new TiXmlElement("root");
	pdoc->LinkEndChild(root);

	TiXmlElement *pelem = new TiXmlElement("devID");
	TiXmlText * pelemcontext = new TiXmlText("SongGuangHua");
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("heartCheck");
	pelemcontext = new TiXmlText("HeartCheck");
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("cmdID");
	pelemcontext = new TiXmlText("602");
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("disConnectNum");
	sprintf(num,"%d",(*vec).size());
	str_num = num;
	pelemcontext = new TiXmlText(str_num.c_str());
	pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);

	pelem = new TiXmlElement("disConnect");
	//pelemcontext = new TiXmlText("");
	//pelem->LinkEndChild(pelemcontext);
	root->LinkEndChild(pelem);
	TiXmlElement *pDis=pelem;
	for (size_t i = 0; i <(*vec).size(); i++)
	{
		pelem = new TiXmlElement("devID");
		pelemcontext = new TiXmlText((*vec)[i].c_str());
		pelem->LinkEndChild(pelemcontext);
		pDis->LinkEndChild(pelem);
	}

	TiXmlPrinter printer;
	printer.SetIndent(0); // 设置缩进字符，设为 0 表示不使用缩进。默认为 4个空格，也可设为'\t'  
	pdoc->Accept(&printer);

	strcpy(m_XMlHeartCheckToGai, printer.CStr());

	pdoc->Clear();
	delete pdoc;
}

