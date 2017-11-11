#ifndef __SG_LOG_H____
#define __SG_LOG_H____
//////////////////////////////////////////////////////////////////////////
//�������ɿ�ƽ̨����־��
//author:lihao
//date:2011-3-16
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

