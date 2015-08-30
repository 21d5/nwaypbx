#ifndef __SG_LOG_H____
#define __SG_LOG_H____
/*************************************************************************
based for NwayPBX
Copyright (C) 2015-, Li hao <lihao@nway.com.cn>
License�� GPL
author: Li hao
email: lihao@nway.com.cn
The Initial Developer of the Original Code is
Li hao<lihao@nway.com.cn>
Portions created by the Initial Developer are Copyright (C)
the Initial Developer. All Rights Reserved.
Contributor(s):
**************************************************************************/
//////////////////////////////////////////////////////////////////////////
//�������ɿ�ƽ̨����־��
//author:lihao
//date:2006-3-16
#include <stdexcept>
#include <string>
#include <iostream>
#include "IVCLog.h"
using namespace std;
#ifndef MAX_PATH
#define MAX_PATH 260
#endif
//#ifdef _UNICODE
//typedef wstring TString;//�����UNICODEģʽ����ô�ַ���ʹ�ÿ��ַ�����
//#else
//typedef string TString;
//#endif



#define MAX_FILE_SIZE 24*1024
class CNwayLog
{
public:
	



	static CNwayLog* GetInstance();
	void Release();
	virtual ~CNwayLog();
public:
	int Write(const char* fmt,...);
protected:
	int GetFileName(string &strFilename);//��������ʱ���������־�ļ�
	int GetTimeStr(string & strTimeStr);//���ʱ���ַ�������ms
	int Close();
	int Open();
private:
	CNwayLog();//���캯����Ϊ˽�У��Ӷ�����־ֻ����һ��
	string _strFilename;
	CLog_T* _log;
	bool bOpen;//��־�ļ��Ƿ��
	
};
#endif

