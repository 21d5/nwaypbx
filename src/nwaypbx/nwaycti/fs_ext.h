#ifndef __FREESWITCH_EXT_NWAY_H
#define __FREESWITCH_EXT_NWAY_H
#include<stdio.h>
//#include <io.h>
#include <stdlib.h>
#include "../esl/esl.h"
#include <vector>
#include <string>
#include "../common/PcreCpp.h"
//char guuid[128];
//originate {return_ring_ready=true}sofia/gateway/liangping/18621575908 &bridge(user/8001)ͬʱ����
//�����һ���ת����һ��
//transfer_after_bridge 

// execute_after_bridge_app

using namespace std;
//#define disp_msg  printf
int check_event_body(const char*eventbody,char*dtmfbuf,int maxdtmf,char* endchar,int *channel_execute);


int check_acm_body(const char*eventbody,char*uuid);
int check_event(esl_handle_t *handle,int timer);

int check_last_event(esl_handle_t *handle,int timer);

int check_acm_event(esl_handle_t *handle,int timer,char* uuid);

//����֮���ȡ������麯��
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//enddtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
//����˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0
int check_play_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf);
//����ȡ����
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//dtmf:�յ����û��İ���(�������),������������������,����"#"
//invalidfile:������Чʱ����ʾ����
//Maxfailure:��ೢ�Դ���
//˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0
#define  playdir  "d:/data/system"
int play_get_dtmf(esl_handle_t *handle,const char*filename0,const char* invalidfile, const char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,int MaxFailure,char*outdtmf);
//¼��֮���ȡ������麯��
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//enddtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
//����˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0

int check_record_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf);
//¼��ȡ��������
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//uuid�� �Ự��id
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//outdtmf:�յ����û��İ���(�������),������������������,����"#"
int record_get_dtmf(esl_handle_t *handle,char*uuid,char*filename,char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf);

void get_nway_dialstring(const char* srcstr,char* desstr, vector<MatchResult>& matchs);
void get_nway_dialstring_uuid(const char* srcstr,char* desstr, const char* auuid,const char* new_uuid,int a_leg_answer,
	vector<MatchResult>& matchs, const char* origination_number);
void get_nway_dialstring_uuid_ex(const char* srcstr,char* desstr, const char* auuid,const char* new_uuid,int a_leg_answer,
	vector<MatchResult>& matchs, const char* origination_number,string& extension_number);
bool nway_isdigit(const char* str);
bool get_uuid(esl_handle_t* pHandle,char* uuid);
bool get_uuid(esl_handle_t* pHandle,string& uuid);
bool nway_hangup(esl_handle_t* pHandle, const char* uuid);
//int get_uuid( char* uuid )
//{
//	uuid[0]=0;
//	CInboundHandle* ihInstance = CInboundHandle::GetInstance();//
//	esl_handle_t* ghandle = ihInstance->GetHandle();
//	esl_send_recv(ghandle,"api create_uuid\n\n");
//	if (*ghandle.last_sr_event && *ghandle.last_sr_event->body)
//	{
//
//		strcpy(uuid,*ghandle.last_sr_event->body);
//		return 0;
//	}
//	return 1;
//}
//
//
//	if(check_event(&handle,2)<0) goto END;
//	
//	if(play_get_dtmf(&handle,"hello.alaw","#",0,0,0,dtmf)<0) goto END;	//hello.alaw:"��ӭ�µ��ҹ�˾�����ǹ�˾��ת���ṩ400����˾"	
//	while(1)
//	{
//		if(play_get_dtmf(&handle,"menu.alaw","*0#",5,20,0,dtmf)<0) goto END;//menu.alaw:"������ֻ����룬��#��ȷ�ϣ������밴�Ǻţ��˹������밴0,�μӻ����밴#��"		
//		if(dtmf[0]!=0) 
//		{
//			break;
//		}
//	}
//	switch(dtmf[0])
//	{
//	case '*'://����
//		{
//			if(play_get_dtmf(&handle,"startrecord.alaw","#",0,0,0,dtmf)<0)   goto END;	//startrecord.alaw:���������ε�һ��֮��ʼ¼���������������¼��,��.....
//			sprintf(recordfilename,"z:/%s.alaw",uuid);//¼�Ƶ� z:/Ŀ¼�� .alaw ��չ�� ¼��Ϊ 8K16bit ��alaw ��ʽ������.wav��չ��¼��Ϊ 8K16bit ������pcm��ʽ����
//			if(record_get_dtmf(&handle,uuid,recordfilename,"#",1,30,0,dtmf)<0) goto END;	
//			if(play_get_dtmf(&handle,recordfilename,"#",0,0,0,dtmf)<0)   goto END;	
//			if(play_get_dtmf(&handle,"bye.alaw","#",0,0,0,dtmf)<0)   goto END;	//bye.alaw:"ллʹ�ã��ټ�"
//			break;
//		}
//	case '0'://�˹�����
//		{
//			esl_execute(&handle, "bridge", "user/1000@${domain_name}", NULL); 
//			
//			if(check_event(&handle,0)<0) goto END;
//			break;
//		}
//
//	case '#'://�μӻ���
//		{
//			esl_execute(&handle, "conference", "3000@default", NULL);	
//			if(check_event(&handle,0)<0) goto END;
//			break;
//		}
//
//	default: 
//		{
//			strtok(dtmf,"#");//ȥ��#�ż�
//			sprintf(cmd_tmp,"user/%s@${domain_name}",dtmf);////${domain_name}=192.168.1.236
//			esl_execute(&handle, "bridge",cmd_tmp , NULL);
//			if(check_event(&handle,0)<0) goto END;
//			break;
//		}
//	}
//	disp_msg("ivr hangup.....\n");
//	sprintf(cmd_tmp,"api uuid_kill %s",uuid);
//	esl_send_recv_timed(&handle, cmd_tmp,1000);
//
//END:	
//	disp_msg("check_last_event start.....\n");
//	check_last_event(&handle,10);
//	disp_msg("Disconnected!");
//	esl_disconnect(&handle);
//
#endif
