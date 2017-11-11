#include "NwayIVR.h"

int NwayIVRCall( esl_handle_t& handle,nway_uint64_t& cdrid, const char* str_extension,const char* aleg_uuid,  const char* basepath,
	list<NwayDialplan>& lstDialplans,list<NwayDialplanDetail>& lstDialplanDetails,list<NwayRing>& lstRings, 
	list<NwayExtension>& lstExtensions,
	vector<MatchResult>& matchs , list<NwayIVR>& lstIVRs, list<NwayIVRDetail>& lstIVRDetails, bool& hasAnswer,
	list<Call_Task>& lstCallTask, pthread_mutex_t& taskMutex , const char* origination_number, pthread_mutex_t& configMutex)
{
	int nStatus = 0;
	//����󣬻�ȡIVR�����Ϣ
	NwayIVR myIVR;
	bool bFound =false;
	char dtmf[128];
	//�õ���Ӧ��ivr�ڵ�
	list<NwayIVR>::iterator itIVR = lstIVRs.begin();
	printf("%s, %d\tsearch IVR record\n",__FILE__,__LINE__);
	for ( ; itIVR != lstIVRs.end(); itIVR++)
	{
		myIVR = *itIVR;
		if (myIVR.ivr_menu_extension == str_extension)
		{
			//�ҵ���ivr�ڵ�
			bFound = true;
			printf("%s, %d\tfound a IVR record\n",__FILE__,__LINE__);
			break;
		}
	}
	if (bFound)
	{
		//�ҵ���ivr���д���
		//�����Ƚ�ͨ����
		esl_execute(&handle, "answer", NULL, NULL);
		CCallDetailRecord cdr;
		cdr.A_AnswerCall(cdrid);
		printf("%s, %d\tanswer the call in\n",__FILE__,__LINE__);
		do
		{
			if(check_event(&handle,2)<0) break;
			//���Ż�ӭ�µ�xx��˾����xx��תĳ
			string ringfullname;
			string invalidname;
			int nStatus = GetRing(myIVR.ivr_menu_greet_long_id, ringfullname, lstRings, basepath, configMutex);
			if (nStatus != 0) break;//û���������壬���ܽ���ivr���˳�
			nStatus = GetRing(myIVR.ivr_menu_invalid_sound_id , invalidname, lstRings, basepath, configMutex);
			int i=1;
			printf("%s, %d\tivr ring:%s,invalid ring:%s\n",__FILE__,__LINE__,ringfullname.c_str(),invalidname.c_str());
			while (i++ < myIVR.ivr_menu_max_failures)
			{
			
				if(play_get_dtmf(&handle,ringfullname.c_str(),invalidname.c_str(), myIVR.ivr_menu_confirm_key.c_str(),myIVR.ivr_menu_digit_len,myIVR.ivr_menu_max_timeouts,myIVR.ivr_menu_timeout,myIVR.ivr_menu_max_failures, dtmf)<0) break;
				//��ȡ����dtmf
				//Ϊ�˱ȽϷ��㣬dtmf����string��
				//printf("play_get_dtmf\n");
				string strDtmf = dtmf;
				list<NwayIVRDetail> myIVRDetails;
				GetIVRDetails(myIVR.id, lstIVRDetails, myIVRDetails, configMutex);
				list<NwayIVRDetail>::iterator itDetail = myIVRDetails.begin();
				NwayIVRDetail myDetail;
				bFound = false;
				for (; itDetail != myIVRDetails.end(); itDetail++)
				{
					myDetail = *itDetail;
					if (myDetail.ivr_menu_option_digits == strDtmf)
					{
						bFound = true;
						//printf("found detail\n");
						break;
					}
				}
				if (bFound)
				{
					//�ҵ������IVR��ϸ��������Ӧ�Ĵ���
					switch(myDetail.ivr_menu_option_action_id)
					{
					case CALL_OPERATION_BRIDGE:
						{
							//��Ҫ�ж�$1,$0֮��ķ���������ı��к���
							char dial_string[1024]={0};
							char new_uuid[128] = {0};
							get_uuid(&handle,new_uuid);
							string extension_number;
							//printf("")
							get_nway_dialstring_uuid_ex(myDetail.ivr_menu_option_param.c_str(),dial_string, aleg_uuid,new_uuid, 1,matchs,origination_number,extension_number);
							printf("%s,%d: dail_string:%s\n",__FILE__,__LINE__,dial_string);
							Call_Task ct;
							ct.task_operate = CALL_OPERATION_ORIGINATE;
							ct.task_cmd = dial_string;
							ct.a_uuid = aleg_uuid;
							ct.b_uuid = new_uuid;
							ct.a_leg_answer = true;
							//////////////////////////////////////////////////////////////////////////
							//here insert a list for call task ,and wait for process it in other thread
							pthread_mutex_lock(&taskMutex); 
							lstCallTask.push_back(ct);
							pthread_mutex_unlock(&taskMutex);
							//////////////////////////////////////////////////////////////////////////
							string shortRing;
							nStatus = GetRing(myIVR.ivr_menu_greet_short_id , shortRing, lstRings, basepath , configMutex);
							printf("%s,-+++++++++++++++++++++++++\n\n",shortRing.c_str());
							esl_execute(&handle,"playback",shortRing.c_str() , NULL);//����ת�Ӷ�����
							nway_uint64_t ext_id = 0;
							GetExtensionId( extension_number,ext_id, lstExtensions ,configMutex);
							string str_origination_number = origination_number;
							string str_extension_number = extension_number;
							string s_str_extension = str_extension;
							InsertCallEvent(cdrid,ext_id,str_origination_number, str_extension_number, s_str_extension  , CALL_EVENT_A_LEG_CALL);

						}
						break;
					default:
						//�Ժ����չsub ivr,��ǰ�汾�Ȳ�����
						;
					}
					break; //�˳�whileѭ��
				}
				else
				{
					//û�ҵ����򲥷ų����������������ѭ��������
					esl_execute(&handle,"playback",invalidname.c_str() , NULL);//������Ч����
				}
			}
		}while(false);


	}
	return nStatus;
}
