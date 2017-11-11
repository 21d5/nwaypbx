#include "fs_ext.h"
#ifdef WIN32
#include "../unistd.h"
#else
#include "unistd.h"
#endif
int check_event_body(const char*eventbody,char*dtmfbuf,int maxdtmf,char* endchar,int *channel_execute)
{	
	char tmp[128];
	unsigned int i,len;

	if (eventbody==NULL) return 0;
	len=strlen(eventbody);
	if(len>64) len=64;
	strncpy(tmp,eventbody+strlen("Event-Name: "),len);
	tmp[len]=0;
	for(i=0;i<strlen(tmp);i++) if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}

	//disp_msg("Event-Name:[%s]", tmp);
	if(strcmp(tmp,"CHANNEL_EXECUTE_COMPLETE")==0)
	{
		if(*channel_execute) return 1;
		//disp_msg("CHANNEL_EXECUTE_COMPLETE invalid");
		return 0;
	}
	if(strcmp(tmp,"CHANNEL_EXECUTE")==0) *channel_execute=1;	
	if(strcmp(tmp,"CHANNEL_HANGUP")==0) return -98;
	//disp_msg("event_body:%s", eventbody);
	//if(strcmp(tmp,"CHANNEL_PROGRESS")==0)

	//if(_strnicmp(eventbody,"Event-Name: DTMF",strlen("Event-Name: DTMF"))==0)
	if (strncasecmp(eventbody,"Event-Name: DTMF",strlen("Event-Name: DTMF"))==0)
	{							
		char*p;

		if(p=(char *)strstr(eventbody,"DTMF-Digit: "))
		{
			strcpy(tmp,p+strlen("DTMF-Digit: "));
			for(i=0;i<strlen(tmp);i++)if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}
			if(strcmp(tmp,"%23")==0) strcpy(tmp,"#");
			//disp_msg("dtmf:[%s]", tmp);
			if(dtmfbuf && strlen(dtmfbuf)<64) strcat(dtmfbuf,tmp);
			if(strlen(dtmfbuf)>=maxdtmf) return 2;
			len=strlen(endchar);		
			//֧�����3����������
			if(len>0) if(tmp[0]==endchar[0]) return 3;
			if(len>1) if(tmp[0]==endchar[1]) return 3;
			if(len>2) if(tmp[0]==endchar[2]) return 3;
		}
	}
	return 0;
}


int check_acm_body(const char*eventbody,char*uuid)
{	
	char tmp[4096];
	unsigned int i,len;
	char*p;
	if (eventbody==NULL) return 0;
	len=strlen(eventbody);
	if(len>64) len=64;
	strncpy(tmp,eventbody+strlen("Event-Name: "),len);
	tmp[len]=0;
	for(i=0;i<strlen(tmp);i++) if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}

	//disp_msg("Event-Name:[%s]", tmp);

	//	//disp_msg("event_body:%s", eventbody);
	if(strcmp(tmp,"CHANNEL_PROGRESS")!=0)
	{
		return 0;
	}




	if(p=(char *)strstr(eventbody,"Unique-ID: "))
	{
		strcpy(tmp,p+strlen("Unique-ID: "));
		for(i=0;i<strlen(tmp);i++)if(tmp[i]=='\n' || tmp[i]=='\r') {tmp[i]=0;break;}

		//disp_msg("acm UUID:[%s]", tmp);
		strcpy(uuid,tmp);			 
	}

	return 1;
}
int check_event(esl_handle_t *handle,int timer)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0;
	int  channel_execute=0;
	dtmf[0]=0;
	printf("%s,%d check_event\n",__FILE__,__LINE__);
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
		//disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=100;break;}

		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");

			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					//disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_event_body(eventbody,dtmf,1,"#",&channel_execute)))
					{
						//disp_msg("check_event_body res=%d.",res);
						if(res<0)	break;
					}
				}

			}
		} 	
	}
	//disp_msg("check_event res=%d",res);
	return res;
}

int check_last_event(esl_handle_t *handle,int timer)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0;
	int  channel_execute=0;

	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
		//	//disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=99;break;}

		if (done) 
		{
			if (time(NULL) >= exp) {res=-99;	break;	}		 
			continue;
		} 
		if (status == ESL_SUCCESS) 
		{

			const char *type = esl_event_get_header(handle->last_event, "content-type");


			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					//disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						done = 1;
						exp = time(NULL) + 5;
					}
				}

				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_event_body(eventbody,dtmf,1,"#",&channel_execute)))
					{
						//disp_msg("check_last_event_body res=%d.",res);
					}
				}

			}
		} 	
	}
	//disp_msg("check_last_event res=%d.",res);
	return res;
}

int check_acm_event(esl_handle_t *handle,int timer,char* uuid)
{
	int done = 0,c=0;
	esl_status_t status;
	time_t exp = 0;
	int res=0;

	uuid[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{	
		c++;
		//	//disp_msg("Waiting 1 seconds events.\n");
		if(timer>0 && c>=timer){res=99;break;}

		if (done) 
		{
			if (time(NULL) >= exp) {res=-99;	break;	}		 
			continue;
		} 
		if (status == ESL_SUCCESS) 
		{

			const char *type = esl_event_get_header(handle->last_event, "content-type");


			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					//disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						done = 1;
						exp = time(NULL) + 5;
					}
				}

				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					if((res=check_acm_body(eventbody,uuid)))
					{
						//disp_msg("check_acm_body res=%d.",res);
						break;
					}
				}
			}
		} 	
	}
	//disp_msg("check_acm_event res=%d.",res);
	return res;
}

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
int check_play_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int done = 0,c=0,twodtmfc=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0,press_dtmf;
	int  channel_execute=0;

	press_dtmf=0;
	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{
		if(press_dtmf)
		{
			twodtmfc++;	
			c++;
		}
		////disp_msg("Waiting 1 seconds events.\n");
		if(MaxTimer>0 && c>=MaxTimer){
			;//disp_msg("Waiting alldtmf %d seconds timout.",c);
			res=100;break;
		}
		if(TwoDtmfTimer>0 && twodtmfc>0 && twodtmfc>=TwoDtmfTimer){
			;//disp_msg("Waiting twodtmf %d seconds timout.",c);
			res=101;break;
		}
		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					//disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					int oldlen=strlen(outdtmf);
					if(res=check_event_body(eventbody,outdtmf,MaxDtmf,enddtmf,&channel_execute))
					{
						//disp_msg("check_play_dtmf_event res=%d.",res);						 
						if(res==1)//play ���� ��ʼ�Ȱ���
						{
							press_dtmf=1;
							if(MaxDtmf==0) break;
						}
						else
							break;
					}			
					if(oldlen==1) press_dtmf=1;
					if(strlen(outdtmf)>oldlen)	twodtmfc=0;
				}
			}
		} 	
	}
	return res;
}
//����ȡ����
//����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
//����:handle:�Ựhandle
//filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
//EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
//MaxDtmf:��󰴼�������������,0��ʾû�а���������������
//MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
//TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
//dtmf:�յ����û��İ���(�������),������������������,����"#"
//˵��:����ֻ�в���,����ȡ���� ���ã�MaxDtmf=0
//#define  playdir  "d:/data/system"
int play_get_dtmf(esl_handle_t *handle,const char*filename0,const char* invalidfile,const char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,int MaxFailure,char*outdtmf)
{
	int res=0;
	char cmd_tmp[1024],enddtmf[128],outdtmfbuff[128],filename[128];
	if(EndDtmf==NULL || EndDtmf[0]==0) 
		strcpy(enddtmf,"q");
	else
		strcpy(enddtmf,EndDtmf);
	if(outdtmf) outdtmf[0]=0;
	memset(outdtmfbuff,0,sizeof(outdtmfbuff));

	sprintf(filename,"%s", filename0);			
	if(access(filename,0)==-1)
		sprintf(filename,"%s/default.alaw",playdir); 

	//<min> <max> <tries> <timeout ms> <terminators> <file> 
	sprintf(cmd_tmp,"1 %d %d %d %s %s",MaxDtmf, MaxFailure, MaxTimer*1000, EndDtmf, filename );  //����һ����������Ч���������Դ�����
	//disp_msg("play_get_dtmf %s",filename);
	printf("%s, %d\tplay_and_get_digits:%s\n",__FILE__,__LINE__,cmd_tmp);
	esl_execute(handle, "play_and_get_digits",cmd_tmp, NULL);

	res=check_play_dtmf_event(handle,enddtmf,MaxDtmf,MaxTimer,TwoDtmfTimer,outdtmfbuff);
	if(outdtmf) strcpy(outdtmf,outdtmfbuff);	
	//disp_msg("play_get_dtmf %s end,dtmf=[%s]",filename,outdtmfbuff);
	return res;
}
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

int check_record_dtmf_event(esl_handle_t *handle,char*enddtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int done = 0,c=0,twodtmfc=0;
	esl_status_t status;
	time_t exp = 0;
	char dtmf[128];
	int res=0,press_dtmf;
	int  channel_execute=0;

	press_dtmf=1;
	dtmf[0]=0;
	while((status = esl_recv_timed(handle, 1000)) != ESL_FAIL) 
	{
		if(press_dtmf)
		{
			twodtmfc++;	
			c++;
		}
		if(MaxTimer>0 && c>=MaxTimer){
			//disp_msg("Waiting alldtmf %d seconds timout.",c);
			res=100;break;}
		if(TwoDtmfTimer>0 && twodtmfc>0 && twodtmfc>=TwoDtmfTimer){
			;//disp_msg("Waiting twodtmf %d seconds timout.",c); 
			res=101;break;
		}
		if (status == ESL_SUCCESS) 
		{
			const char *type = esl_event_get_header(handle->last_event, "content-type");
			if (type)
			{
				if(strcasecmp(type, "text/disconnect-notice")==0) 
				{
					const char *dispo = esl_event_get_header(handle->last_event, "content-disposition");
					//disp_msg("Got a disconnection notice dispostion: [%s]", dispo ? dispo : "");
					if (dispo && strcmp(dispo, "linger")==0) 
					{
						res=-99;
						break;					 
					}
				}
				if(strcasecmp(type, "text/event-plain")==0) 
				{		
					const char *eventbody=esl_event_get_body(handle->last_event);
					int oldlen=strlen(outdtmf);
					if((res=check_event_body(eventbody,outdtmf,MaxDtmf,enddtmf,&channel_execute)))
					{
						break;
					}			
					if(oldlen==1) press_dtmf=1;
					if(strlen(outdtmf)>oldlen)	twodtmfc=0;
				}
			}
		} 	
	}
	return res;
}
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
int record_get_dtmf(esl_handle_t *handle,char*uuid,char*filename,char*EndDtmf,int MaxDtmf,int MaxTimer,int TwoDtmfTimer,char*outdtmf)
{
	int res;
	char cmd_tmp[1024],enddtmf[128],outdtmfbuff[128];
	if(EndDtmf==NULL || EndDtmf[0]==0) 
		strcpy(enddtmf,"q");
	else
		strcpy(enddtmf,EndDtmf);
	if(outdtmf) outdtmf[0]=0;

	//disp_msg("record_get_dtmf:%s",filename);
	memset(outdtmfbuff,0,sizeof(outdtmfbuff));
	sprintf(cmd_tmp,"api uuid_record %s start %s %d",uuid,filename,MaxTimer*2);//MaxTimer*2��������Ϊ�˱�֤uuid_record ��������Ч������ͨ���Լ���ivr check_record_dtmf_event���������������¼�������ж�
	esl_send_recv_timed(handle, cmd_tmp,1000); 	
	res=check_record_dtmf_event(handle,enddtmf,MaxDtmf,MaxTimer,TwoDtmfTimer,outdtmfbuff);
	if(outdtmf) strcpy(outdtmf,outdtmfbuff);
	//disp_msg("record_get_dtmf:%s,end,dtmf=[%s]",filename,outdtmfbuff);
	sprintf(cmd_tmp,"api uuid_record %s stop all",uuid);
	//disp_msg("record_get_dtmf:%s stop",filename);
	esl_send_recv_timed(handle, cmd_tmp,1000);
	//disp_msg("record_get_dtmf:%s stop end",filename);

	return res;
}

void get_nway_dialstring( const char* srcstr,char* desstr, vector<MatchResult>& matchs )
{
	 
	//user/${dialed_extension}@${domain_name}
	char beginstr[200]={0};
	char endstr[200]={0};
	char convertstr[30]={0};
	const char* dpos=strchr(srcstr,'$');//
	const char* apos = strchr(srcstr,'@');//
	bool bDollar = false;
	bool bAt = false;
	int nBegin =0;
	int nEnd = 0;
	int nConvert = 0;
	if (dpos && apos)
	{

		int len1 = dpos - srcstr ;
		strncpy(beginstr,srcstr,len1);
		apos = strchr (dpos,'@'); //so: @{domain_name}
		if (apos)
		{
			strncpy(convertstr,dpos+1,apos-dpos - 1);
		}
		else
		{
			//see: user/$1
			strncpy(convertstr,dpos+1,1);
		}
			if( nway_isdigit(convertstr) )
			{
				printf("%s, %d\tthe last string is %s\n",__FILE__,__LINE__, apos);
				nConvert = atoi(convertstr);
				printf("%s, %d\tbegingstr:%s,nConvert:%d\n",__FILE__,__LINE__,beginstr,nConvert);
				if (matchs.size()>0)
				{
					sprintf(desstr,"%s%s%s\0",beginstr,matchs[0].value[nConvert].c_str(),apos);
				}
				else
					strncpy(desstr,srcstr,strlen(srcstr));
			}

			else
			{
				strncpy(desstr,srcstr,strlen(srcstr));

			}

		
		
	}
	else
	{
		if (dpos)
		{
			int len1 = dpos - srcstr ;
			strncpy(beginstr,srcstr,len1);
			//strcpy(convertstr,dpos+1);
			strncpy(convertstr,dpos+1, 1);
			if( nway_isdigit(convertstr) )
			{
				 
				nConvert = atoi(convertstr);
				printf("^s, %d\tonly dpos begingstr:%s,nConvert:%d,matchs size:%d\n",__FILE__,__LINE__,beginstr,nConvert,matchs.size());
				//printf("matchs value:%s\n",matchs[0].value[nConvert-1].c_str());
				if (matchs.size()>0)
				{
					sprintf(desstr,"%s%s\0",beginstr,matchs[0].value[nConvert].c_str() );
					//printf(desstr);
				}
				else
					strncpy(desstr,srcstr,strlen(srcstr));
			}

			else
			{
				strncpy(desstr,srcstr,strlen(srcstr));

			}
		}
		else
			strncpy(desstr,srcstr,strlen(srcstr));
	}
	
	//printf(desstr);

}

bool nway_isdigit( const char* str )
{
	int len = strlen(str);
	bool bResult = true;
	for (int i =0; i< len; i++)
	{
		if (!isdigit(str[i]))
		{
			bResult = false;
			break;
		}
	}
	return bResult;
}

//void get_nway_dialstring_uuid( const char* srcstr,char* desstr, const char* auuid,const char* new_uuid,int a_leg_answer,
//	vector<MatchResult>& matchs , const char* origination_number)
//{
//	char beginstr[200]={0};
//	char endstr[200]={0};
//	char convertstr[30]={0};
//	const char* dpos=strchr(srcstr,'$');//
//	const char* apos = strchr(srcstr,'@');//
//	bool bDollar = false;
//	bool bAt = false;
//	int nBegin =0;
//	int nEnd = 0;
//	int nConvert = 0;
//	//sprintf(tmp,"bgapi originate {origination_uuid=%s,originate_timeout=30}sofia/internal/1005%c192.168.1.102 &park()\n\n",uuid,'%');
//	if (dpos && apos)
//	{
//
//		int len1 = dpos - srcstr ;
//		strncpy(beginstr,srcstr,len1);
//		apos = strchr (dpos,'@'); //so: @{domain_name}
//		if (apos)
//		{
//			strncpy(convertstr,dpos+1,apos-dpos - 1);
//		}
//		else
//		{
//			//see: user/$1
//			strncpy(convertstr,dpos+1,1);
//		}
//		if( nway_isdigit(convertstr) )
//		{
//			printf("the last string is %s\n", apos);
//			nConvert = atoi(convertstr);
//			printf("begingstr:%s,nConvert:%d\n",beginstr,nConvert);
//			if (matchs.size()>0)
//			{
//				//bridge_early_media=true,return_ring_ready=true,
//				sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s%s%s &park()\n\n",\
//					 a_leg_answer, new_uuid, origination_number,origination_number, auuid, beginstr,matchs[0].value[nConvert].c_str(),apos);
//			}
//			else
//				//strncpy(desstr,srcstr,strlen(srcstr));
//				sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
//				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
//		}
//
//		else
//		{
//			sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
//				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
//
//		}
//
//
//
//	}
//	else
//	{
//		if (dpos)
//		{
//			int len1 = dpos - srcstr ;
//			strncpy(beginstr,srcstr,len1);
//			//strcpy(convertstr,dpos+1);
//			strncpy(convertstr,dpos+1, 1);
//			if( nway_isdigit(convertstr) )
//			{
//
//				nConvert = atoi(convertstr);
//				printf("only dpos begingstr:%s,nConvert:%d,matchs size:%d\n",beginstr,nConvert,matchs.size());
//				//printf("matchs value:%s\n",matchs[0].value[nConvert-1].c_str());
//				if (matchs.size()>0)
//				{
//					sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s%s &park()\n\n",\
//						 a_leg_answer, new_uuid,origination_number,origination_number,auuid,beginstr,matchs[0].value[nConvert].c_str() );
//					printf(desstr);
//				}
//				else
//					//strncpy(desstr,srcstr,strlen(srcstr));
//					sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
//					     a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
//			}
//
//			else
//			{
//				//strncpy(desstr,srcstr,strlen(srcstr));
//				sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
//					 a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
//			}
//		}
//		else
//			sprintf(desstr,"bgapi originate {bridge_answer_timeout=10,a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
//			     a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
//	}
//
//	printf(desstr);
//}
//intercept

void get_nway_dialstring_uuid( const char* srcstr,char* desstr, const char* auuid,const char* new_uuid,int a_leg_answer,
	vector<MatchResult>& matchs , const char* origination_number)
{
	char beginstr[200]={0};
	char endstr[200]={0};
	char convertstr[30]={0};
	const char* dpos=strchr(srcstr,'$');//
	const char* apos = strchr(srcstr,'@');//
	bool bDollar = false;
	bool bAt = false;
	int nBegin =0;
	int nEnd = 0;
	int nConvert = 0;
	//sprintf(tmp,"bgapi originate {origination_uuid=%s,originate_timeout=30}sofia/internal/1005%c192.168.1.102 &park()\n\n",uuid,'%');
	if (dpos && apos)
	{

		int len1 = dpos - srcstr ;
		strncpy(beginstr,srcstr,len1);
		apos = strchr (dpos,'@'); //so: @{domain_name}
		if (apos)
		{
			strncpy(convertstr,dpos+1,apos-dpos - 1);
		}
		else
		{
			//see: user/$1
			strncpy(convertstr,dpos+1,1);
		}
		if( nway_isdigit(convertstr) )
		{
			printf("%s, %d\tthe last string is %s\n",__FILE__,__LINE__, apos);
			nConvert = atoi(convertstr);
			printf("%s, %d\tbegingstr:%s,nConvert:%d\n",__FILE__,__LINE__,beginstr,nConvert);
			if (matchs.size()>0)
			{
				//bridge_early_media=true,return_ring_ready=true,bridge_answer_timeout=20,
				/*
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s%s%s &intercept(%s)\n\n",\
					 a_leg_answer, new_uuid, origination_number,origination_number, auuid, beginstr,matchs[0].value[nConvert].c_str(),apos,auuid);
					 */
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s%s%s &park()\n\n",\
					a_leg_answer, new_uuid, origination_number,origination_number, auuid, beginstr,matchs[0].value[nConvert].c_str(),apos);
			}
			else
				//strncpy(desstr,srcstr,strlen(srcstr));
				/*
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &intercept(%s)\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr,auuid);
				*/
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &park()\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
		}

		else
		{
			/*
			sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &intercept(%s)\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr,auuid);*/
			sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &park()\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);

		}



	}
	else
	{
		if (dpos)
		{
			int len1 = dpos - srcstr ;
			strncpy(beginstr,srcstr,len1);
			//strcpy(convertstr,dpos+1);
			strncpy(convertstr,dpos+1, 1);
			if( nway_isdigit(convertstr) )
			{

				nConvert = atoi(convertstr);
				printf("only dpos begingstr:%s,nConvert:%d,matchs size:%d\n",beginstr,nConvert,matchs.size());
				//printf("matchs value:%s\n",matchs[0].value[nConvert-1].c_str());
				if (matchs.size()>0)
				{
					/*sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s%s &intercept(%s)\n\n",\
						 a_leg_answer, new_uuid,origination_number,origination_number,auuid,beginstr,matchs[0].value[nConvert].c_str() ,auuid);*/
					sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s%s &park()\n\n",\
						a_leg_answer, new_uuid,origination_number,origination_number,auuid,beginstr,matchs[0].value[nConvert].c_str() );
					//printf(desstr);
				}
				else
					//strncpy(desstr,srcstr,strlen(srcstr));
					sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &park()\n\n",\
					     a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
			}

			else
			{
				//strncpy(desstr,srcstr,strlen(srcstr));
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &park())\n\n",\
					a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr );
			}
		}
		else
			sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=45}%s &park()\n\n",\
			     a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
	}

	//printf(desstr);
}
bool get_uuid( esl_handle_t* pHandle,char* uuid )
{
	esl_send_recv(pHandle, "api create_uuid\n\n");
	if (pHandle->last_sr_event && pHandle->last_sr_event->body) 
	{
		//disp_msg("uuid:[%s]****************************************************\n", pHandle->last_sr_event->body);
		strcpy(uuid,pHandle->last_sr_event->body);
		return true;
		//strcpy(uuid,(handle.last_sr_event->body)+strlen("+OK Job-UUID: "));
	} 
	else 
	{
		//disp_msg("[%s] last_sr_reply\n", pHandle->last_sr_reply);
		return false;
	}
}

bool get_uuid( esl_handle_t* pHandle,string& uuid )
{
	esl_send_recv(pHandle, "api create_uuid\n\n");
	if (pHandle->last_sr_event && pHandle->last_sr_event->body) 
	{
		//disp_msg("uuid:[%s]****************************************************\n", pHandle->last_sr_event->body);
		//strcpy(uuid,pHandle->last_sr_event->body);
		uuid = pHandle->last_sr_event->body;
		return true;
		//strcpy(uuid,(handle.last_sr_event->body)+strlen("+OK Job-UUID: "));
	} 
	else 
	{
		//disp_msg("[%s] last_sr_reply\n", pHandle->last_sr_reply);
		return false;
	}
}

void get_nway_dialstring_uuid_ex( const char* srcstr,char* desstr, const char* auuid,const char* new_uuid,int a_leg_answer, vector<MatchResult>& matchs, const char* origination_number,string& extension_number )
{
	char beginstr[200]={0};
	char endstr[200]={0};
	char convertstr[30]={0};
	const char* dpos=strchr(srcstr,'$');//
	const char* apos = strchr(srcstr,'@');//
	bool bDollar = false;
	bool bAt = false;
	int nBegin =0;
	int nEnd = 0;
	int nConvert = 0;
	//sprintf(tmp,"bgapi originate {origination_uuid=%s,originate_timeout=30}sofia/internal/1005%c192.168.1.102 &park()\n\n",uuid,'%');
	if (dpos && apos)
	{

		int len1 = dpos - srcstr ;
		strncpy(beginstr,srcstr,len1);
		apos = strchr (dpos,'@'); //so: @{domain_name}
		if (apos)
		{
			strncpy(convertstr,dpos+1,apos-dpos - 1);
		}
		else
		{
			//see: user/$1
			strncpy(convertstr,dpos+1,1);
		}
		if( nway_isdigit(convertstr) )
		{
			printf("%s, %d\tthe last string is %s\n", __FILE__,__LINE__,apos);
			nConvert = atoi(convertstr);
			printf("begingstr:%s,nConvert:%d\n",beginstr,nConvert);
			if (matchs.size()>0)
			{
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s%s%s &park()\n\n",\
					a_leg_answer, new_uuid, origination_number,origination_number, auuid, beginstr,matchs[0].value[nConvert].c_str(),apos);
				extension_number = matchs[0].value[nConvert];
			}
			else
				//strncpy(desstr,srcstr,strlen(srcstr));
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
		}

		else
		{
			sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
				a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);

		}



	}
	else
	{
		if (dpos)
		{
			int len1 = dpos - srcstr ;
			strncpy(beginstr,srcstr,len1);
			//strcpy(convertstr,dpos+1);
			strncpy(convertstr,dpos+1, 1);
			if( nway_isdigit(convertstr) )
			{

				nConvert = atoi(convertstr);
				printf("%s, %d\tonly dpos begingstr:%s,nConvert:%d,matchs size:%d\n",__FILE__,__LINE__,beginstr,nConvert,matchs.size());
				//printf("matchs value:%s\n",matchs[0].value[nConvert-1].c_str());
				if (matchs.size()>0)
				{
					sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s%s &park()\n\n",\
						a_leg_answer, new_uuid,origination_number,origination_number,auuid,beginstr,matchs[0].value[nConvert].c_str() );
					extension_number = matchs[0].value[nConvert];
					//printf(desstr);
				}
				else
					//strncpy(desstr,srcstr,strlen(srcstr));
					sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
					a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
			}

			else
			{
				//strncpy(desstr,srcstr,strlen(srcstr));
				sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
					a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
			}
		}
		else
		{
			sprintf(desstr,"bgapi originate {a_leg_answer=%d,origination_uuid=%s,origination_caller_id_name=%s,origination_caller_id_number=%s,a_leg_uuid=%s,originate_timeout=30}%s &park()\n\n",\
			a_leg_answer, new_uuid,origination_number,origination_number, auuid, srcstr);
		}
	}

	//printf(desstr);
}

bool nway_hangup( esl_handle_t* pHandle, const char* uuid )
{
	char szCmd[2048] = {0};
	sprintf(szCmd,"bgapi uuid_kill %s\n\n",uuid);
	esl_send_recv(pHandle,szCmd);// "bgapi originate {originate_timeout=30}sofia/internal/1005%192.168.1.102 &park()\n\n");
	//	uuid[0]=0;
	if (pHandle->last_sr_event && pHandle->last_sr_event->body) 
	{
		printf("[%s]\n", pHandle->last_sr_event->body);
		//	strcpy(uuid,(handle.last_sr_event->body)+strlen("+OK Job-UUID: "));
		return true;
	} 
	else 
	{
		printf("[%s] last_sr_reply\n", pHandle->last_sr_reply);
		return false;
	}
}
