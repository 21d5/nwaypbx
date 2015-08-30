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

#ifndef  _IV_CLOG_H_
#define  _IV_CLOG_H_

#define MAX_LEVEL  256

#define TBUF_SIZE 102400
#define PATH_MAX_SIZE 256

#ifdef _WIN32
#include <windows.h>
#else
#include <pthread.h>
#endif

#define ANSI

#ifndef HAVE_STD_IOSTREAM
#define HAVE_STD_IOSTREAM
#endif

#include <string>
#include <stdarg.h>



#ifdef HAVE_STD_IOSTREAM
using namespace std;
#endif

	class CLog_T
	{
	#if defined(WIN32)
		CRITICAL_SECTION	_mutex;
	#else
		pthread_mutex_t		_mutex;
	#endif
	protected:
		FILE *m_pf;
		string m_Suffix;
		string m_Prefix;

		unsigned m_LogOptions;
		unsigned m_LogLevel;
		string m_LogFileName;
		char m_strBuf[TBUF_SIZE];
		char m_LogPath[PATH_MAX_SIZE];
		bool m_bEnable;
		string m_DebugFileName;
		int m_LineNum;
		
		//��ʱ���ʽ��20030910061630��Ϊ2003 09-10 10:30:30
		string FormatTime(string systemTime);
		void lock();
		void unlock();
		//д��־��¼��ͷ
		short BeginLog(unsigned level);
		//����ʱ���,ÿ��ֻдһ��

		short BeginLogHead(unsigned level);	
		//���ļ���ǰ����·��
		string AddPath(const char *fileName);

		void SetFileAndLine(const char *fileName,int lineNum)
		{
			m_DebugFileName = fileName;
			m_LineNum = lineNum;
		}

	public:		
		// �������ѡ��
		enum Options {    
			FileByDay = 1,	//�������־
			DateAndTime = 2,//����ʱ���			
			TraceLevel = 4,//�����ǰ�ļ���
			FileAndLine = 16,//��ѡ����ʱû����Ϊ����׼����
			DisplayScreen = 32,//����Ļ����ʾ
			FileByName = 64		//��ָ���ļ���������־
		};	

		CLog_T();
		~CLog_T();
		CLog_T( unsigned level,unsigned options,const char *filename );
		void  ReturnFileName(char *filename);

		// ����ѡ��
		void SetOptions(unsigned options );	
		void ClearOptions(unsigned options );	
		unsigned GetOptions( );
		void AddOptions(unsigned options);
		
		// ���õȼ�
		void SetLevel(unsigned level );	
		unsigned GetLevel();
		
		//�жϵ��Եȼ��Ƿ�ﵽ
		bool CanTrace(unsigned level );
		//������־�ļ�����ֻ�������ó�FileByNameʱ����Ч
		short SetFile( const char *fileName );
		void SetLogPath( const char *logPath );
		//�򿪹ر���־���
		void Enable(bool enable=true )
		{
			m_bEnable = enable;
		}
		//���������־ʱ�����ļ�����ǰ׺���׺������prefix��ivsender, suffix��log��ʱ����2011-03-21���ļ���Ϊivsender20110321.log
		void SetPrefixSuffix(const char *prefix, const char *suffix)
		{
			m_Prefix = prefix;
			m_Suffix = suffix;
		}
		//����ļ���
		void Flush()
		{
#ifdef WIN32
			fflush(m_pf);
#endif
		}
		//��ȡϵͳʱ�䣬���β���ϵͳ
		static string GetSystemTime();
		static string GetFileTime();
		//д��־�ĺ�������д��ʽ��printf���ƽ�������һ����־�������
	#ifdef ANSI	
		long Userlog(unsigned level,const char *fmt,...);
	#else
		long Userlog(unsigned level,const char *fmt,va_alist);
	#endif	

	#ifdef ANSI	
		long UserlogHead(unsigned level,const char *fmt,...);
	#endif
	};
		


#endif // (_IV_CLOG_H_)
