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
#ifndef __NWAY_PBX_BASE_CONFIG_H
#define __NWAY_PBX_BASE_CONFIG_H
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <string>
#include <vector>
#include <limits.h>  
#include "../interface/db_center.h"
//#include "../interface/db_struct.h"
#include "../../nwaypbx/statedef.h"
#include "../../nwaypbx/structdef.h"
//////////////////////////////////////////////////////////////////////////
/*���ڼ�������·�����á�����һЩ���ã���Ӧ�ڱ�call_base_config
�ڴ�Ӧ���в�������£�ֻ�ܶ�ȡ
*/
//////////////////////////////////////////////////////////////////////////
using namespace std;
int LoadBaseConfig(list<base_config>& lstBaseConfig);
//���еķֻ��飬�����ǹ̶���
int LoadExtensionGroup(list<NwayExtensionGroup>& lstExtensionGroup);
//���еķֻ������ǿ��Ը��µģ�������Ϊ��
class CExtension
{
public:
	CExtension();
	~CExtension();
	//////////////////////////////////////////////////////////////////////////
	//extension_reg_state���ַ�ֵΪ registered,unregistered
	//extension_login_state���ַ�ֵΪ success, logout,busy,leaved
	int LoadExtension(list<NwayExtension>& lstExtension);
	//0=success,1 = logout,2=busy,3=leaved
	int UpdateLoginState(nway_uint64_t& id,int nLogin);
	int UpdateRegState(nway_uint64_t& id, const char* szState);
private:
};
//������ص�����
int LoadCalloutGateway(list<NwayCalloutGateway>& lstCalloutGateways);
//������ص�����
int LoadGateway(list<NwayGateway>& lstGateway);
//���żƻ���ϸ
int LoadDialplanDetails(list<NwayDialplanDetail>& lstDialplanDetail);

//���żƻ�
int LoadDialplan(list<NwayDialplan>& lstDialplan);

//IVR��ϸ
int LoadIvrDetails(list<NwayIVRDetail>& lstIvrDeatail);

//IVRģ��
int LoadIvrs(list<NwayIVR>& lstIvr);

//�������
int LoadRings(list<NwayRing>& lstRings);

//��������
int LoadOutsides(list<Outside_line>& lstOutsides);

//�����߶�Ӧ����
int LoadInOutMapping(list<In_Out_Mapping>& lstInOutMapping);

//CDRģ��
class CCallDetailRecord
{
public:
	CCallDetailRecord();
	~CCallDetailRecord();
	//caller_name,caller_number��aleg��called_number�Ǿ���ĺ��������Ĵ���룬id�����ɵ�cdr id
	int StartCall(const char* caller_name, const char* caller_number, const char* called_number, nway_uint64_t& id);
	int StartCall(const char* caller_name, const char* caller_number, const char* called_number, nway_uint64_t& id,bool bAutoCallout, nway_uint64_t& task_id);

	//������Ϊ�Ƕ�alegժ����أ���һ����Ӧ��
	int A_AnswerCall(nway_uint64_t& id);
	//���ļ�Ӧ��
	int B_AnswerCall(nway_uint64_t& id, const char* dest_number, const char* digites_dail);

	int A_EndCall(nway_uint64_t& id, NWAY_HANGUP_CAUSE cause, int gatewayid, NWAY_HANGUP_DIRECTION direction);
	
	//b-cause���Բ��ù�,�Ժ��б�Ҫ��չb�һ�����ʱ��˵
	int B_EndCall(nway_uint64_t& id, const char* dest_number, NWAY_HANGUP_CAUSE cause);


	int SetRecordFile(nway_uint64_t& id,const char* filename);
	
	//д���ʱ���ڹһ�����У������У�ͳ��a-leg,b-leg,a��b�ͨ��ʱ��
	int CountTime(nway_uint64_t& id);

	int SetDtmf(nway_uint64_t& id, const char* dtmf);


private:
};

//д���¼���Ϣ
int InsertCallEvent(nway_uint64_t& cdr_id, nway_uint64_t& ext_id,string& a_leg_number,string& b_leg_number,string& route_number, NWAY_CALL_EVENT iEvent);
//�������¼�ת��ĳ��ext_id,����Ϊ����ivr��ʱ��ֱ�����粻��ĳ������ֻ�������Ҫǿ��ָ��һ��
int UpdateCallEvent(nway_uint64_t& cdr_id, nway_uint64_t& ext_id);




class CDBCalloutTask{
public:
	CDBCalloutTask();
	~CDBCalloutTask();
	int GetTasks(list<Callout_Task>& lstCalloutTasks, list<NwayGateway>& lstGateways,list<NwayCalloutGateway>& lstCalloutGateways);//���û���֣�����Ϊ��ͣ���鲻������������Ϊ���
	int UpdateTaskStatus(nway_uint64_t& id, nway_uint64_t& run_postion, int total,int success, int failed, int cancled);
	int UpdateTaskState(nway_uint64_t& id, int nState);//����״̬��1,�ȴ����У� 2���������3����ɣ�4��ͣ
	int GetIdleAgentNumber(nway_uint64_t& groupid,int& nNumber );
	int GetCalloutNumbers(Callout_Task& nwayct, int nMaxnumber);

};

class CDBCalloutInfo{
public:
	CDBCalloutInfo();
	~CDBCalloutInfo();
	int StartCallout(nway_uint64_t& id,nway_uint64_t& cdrid);
	int ExtensionAnswer(nway_uint64_t& id,nway_uint64_t& extension_id,const char* record_file);
	int SetAlegAnswer(nway_uint64_t& id);
	int SetAlegHangup(nway_uint64_t& id, int nHangupid);
	int SetCalled(nway_uint64_t&id);
};

int DBGetClickDials(vector<Click_Dial>& vecClickDials);

int DBSetClickDialed(nway_uint64_t& id);

int DBGetConfigChanged(vector<int>& vecConfigs);

int DBSetConfigChanged(int orderid);
#endif
