#include "DirectCall.h"
#include "fs_ext.h"

int DirectCall( esl_handle_t& handle,nway_uint64_t& cdrid, nway_uint64_t& diplanid,const char* str_extension,
	const char* aleg_uuid,  const char* basepath,\
	list<NwayDialplan>& lstDialplans,\
	list<NwayDialplanDetail>& lstDialplanDetails,list<NwayRing>& lstRings, list<NwayExtension>& lstExtensions,\
	vector<MatchResult>& matchs , bool& hasAnswer , list<Call_Task>& lstCallTask, pthread_mutex_t& taskMutex , const char* origination_number,
	pthread_mutex_t& configMutex)
{
	int nStatus = 0;
	list<NwayDialplanDetail> myDetails;
	list<NwayDialplanDetail>::iterator it = lstDialplanDetails.begin();
	for (; it != lstDialplanDetails.end(); it++)
	{
		NwayDialplanDetail myobj =*it;
		if (myobj.dialplan_id == diplanid)
		{
			//����������żƻ��Ĳ���
			myDetails.push_back(myobj);
		}
	}
	myDetails.sort();
	//��order�����Ĳ���
	it = myDetails.begin();
	for (; it != myDetails.end(); it++)
	{
		//��order������Ӧ�Ĳ���ִ��
		NwayDialplanDetail& myDetail = *it;
		esl_log(ESL_LOG_INFO,"NwayDialplanDetail:%d,extension:%s\n",myDetail.dialplan_detail_type_id,str_extension);
		switch(myDetail.dialplan_detail_type_id)
		{
		case CALL_OPERATION_SET:
			{
				char dial_string[1024]={0};
				get_nway_dialstring(myDetail.dialplan_detail_data.c_str(),dial_string,matchs);
				esl_execute(&handle, "set",  dial_string, NULL);
			}
			break;
		case CALL_OPERATION_ANSWER:
			{
				hasAnswer = true;
				CCallDetailRecord cdr;
				cdr.A_AnswerCall(cdrid);
				esl_execute(&handle, "answer", NULL, NULL);
				string s_str_extension = str_extension;
				string s_origination_number = origination_number;
				//��¼b�����¼�
				nway_uint64_t ext_id = 0;
				GetExtensionId( s_str_extension,ext_id, lstExtensions , configMutex);
				InsertCallEvent(cdrid, ext_id,s_origination_number,s_str_extension,s_str_extension, CALL_EVENT_A_LEG_TALKING);
				//UpdateCallEvent(nwayci.cdrid,ext_id);
				//////////////////////////////////////////////////////////////////////////
			}
			break;
		case CALL_OPERATION_DTMF:
			{

				//�˴�����dtmf
			}
			break;
		case CALL_OPERATION_BRIDGE:
			{
				//��Ҫ�ж�$1,$0֮��ķ���������ı��к���
				char dial_string[2048]={0};
                //sprintf(dial_string,"a_leg_uuid=%s\0",aleg_uuid);
                //esl_execute(&handle, "set", dial_string, NULL); 
				//get_nway_dialstring(myDetail.dialplan_detail_data.c_str(),dial_string,matchs);
				char new_uuid[128] = {0};
				get_uuid(&handle,new_uuid);
				get_nway_dialstring_uuid(myDetail.dialplan_detail_data.c_str(),dial_string, aleg_uuid,new_uuid,0, matchs,origination_number);
				printf(dial_string);
				Call_Task ct;
				ct.task_operate = CALL_OPERATION_ORIGINATE;
				ct.task_cmd = dial_string;
				ct.a_uuid = aleg_uuid;
				ct.b_uuid = new_uuid;
				
				//////////////////////////////////////////////////////////////////////////
				//here insert a list for call task ,and wait for process it in other thread
				pthread_mutex_lock(&taskMutex); 
				lstCallTask.push_back(ct);
				pthread_mutex_unlock(&taskMutex);
                
			}
			break;
		case CALL_OPERATION_PLAYRING:
			{
				 string strfullname;
				 GetRing(myDetail.ring_id,strfullname,lstRings,basepath , configMutex);
				 printf("%s, %d\t%s\n",__FILE__,__LINE__,strfullname.c_str());
				 esl_execute(&handle, "playback", strfullname.c_str(), NULL); 
			}
			break;
		case CALL_OPERATION_SLEEP:
			{
				 esl_execute(&handle, "sleep", myDetail.dialplan_detail_data.c_str(), NULL); 
			}
			break;
		case CALL_OPERATION_SUBMENU:
			{
				;
			}
			break;
		case CALL_OPERATION_HANGUP:
			{
				esl_execute(&handle, "hungup", NULL , NULL); 
			}
		case CALL_OPERATION_AGENT_LOGIN:
			{
				//������Ϊע��ɹ���һ�
				pthread_mutex_lock(&configMutex);
				list<NwayExtension>::iterator it = lstExtensions.begin();
				for (; it!= lstExtensions.end(); it++)
				{
					NwayExtension& ne = *it;
					if (ne.extension_number == origination_number )
					{
						//�ҵ�
						
						//*it = ne;
						//д�����ݿ���
						SetAgentLoginState(ne.id, 0 );
						esl_execute(&handle,"speak","flite|slt|shanxian",NULL);
						esl_log(ESL_LOG_INFO,"login successed\n");
						NwaySleep(3000);
						ne.callout_state = CALLOUT_INIT;
						ne.reg_state = AGENT_REG_SUCCESS;
						ne.login_state = AGENT_LOGIN_SUCCESS;
						esl_execute(&handle, "hangup", NULL , NULL); 
						break;
					}
				}
				pthread_mutex_unlock(&configMutex);
			}
			break;
		case CALL_OPERATION_AGETN_LOGOUT:
			{
				//������Ϊ�ǳ�������������ԭ���Ժ������չ��dtmf��ȷ��
				pthread_mutex_lock(&configMutex);
				list<NwayExtension>::iterator it = lstExtensions.begin();
				for (; it!= lstExtensions.end(); it++)
				{
					NwayExtension& ne = *it;
					if (ne.extension_number == origination_number  )
					{
						//�ҵ�
						
						//*it = ne;
						SetAgentLoginState(ne.id, 1 );
						esl_log(ESL_LOG_INFO,"logout successed\n");
						esl_execute(&handle,"speak","flite|slt|xiaxian",NULL);
						NwaySleep(4000);
						ne.reg_state = AGENT_REG_SUCCESS;
						ne.login_state = AGENT_LOGIN_LOGOUT;
						esl_execute(&handle, "hangup", NULL , NULL); 
						break;
					}
				}
				pthread_mutex_unlock(&configMutex);
			}
			break;
		default:
			;
		}
	}
	return nStatus;
}
