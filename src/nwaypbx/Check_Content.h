#ifndef __NWAY_CHECK_CONTENT_H
#define __NWAY_CHECK_CONTENT_H
#include "nwaycti/nwaycti.h"
#include "log/log.h"
#include <list>
#include <string>
#include <vector>
#include <pthread.h>
using namespace std;
int CheckIsInside(string dest_number, NwayExtension& ext, list<NwayExtension>& lstExtension , pthread_mutex_t& configMutex);//�����Ƿ������ߺ���
int CheckIdleAgent(const nway_uint64_t& agent_group_id,list<NwayExtension>& lstExtension , pthread_mutex_t& configMutex);//���ҿ��е���ϯ���������к͹һ���תΪ����

int GetIdleAgent(const nway_uint64_t& agent_group_id, string& ext_number,list<NwayExtension>& lstExtension, pthread_mutex_t& configMutex); //��ȡһ�����еĺ���

int SetIdleAgent(const nway_uint64_t& agent_group_id, string& ext_number,list<NwayExtension>& lstExtension, pthread_mutex_t& configMutex); //����һ����ϯ��

int SetBusyAgent(const nway_uint64_t& agent_group_id, string& ext_number,list<NwayExtension>& lstExtension, pthread_mutex_t& configMutex);//����һ����ϯæ

int GetBindPhones(string& caller_number,string& dest_number, list<NwayExtension>& lstBinds, list<NwayExtension>& lstExtensions);//ͨ�������Ŀ����������ת����Щ���룬did��ֱ��һ������
int GetCalloutNumbers(const nway_uint64_t& agent_group_id, list<Callout_info>& lstCalloutinfo , pthread_mutex_t& configMutex );//������ĳ����ϯ����������

int GetGateway(const string& ext_number, string& gateway, list<NwayGateway>& lstGateway, list<NwayExtension>& lstExtension, pthread_mutex_t& configMutex);//���������ʱ��ȡ��Ӧ������

int GetRing(nway_uint64_t id , string& fullname, list<NwayRing>& lstRings, const string& basepath, pthread_mutex_t& configMutex);  //ͨ��id����һ�������ļ���ȫ·��

int GetCalloutTask(list<Callout_Task>& lstCalloutTasks, list<NwayExtension>& lstExtensions, list<NwayGateway>& lstGateways,list<NwayCalloutGateway>& lstCalloutGateways, pthread_mutex_t& configMutex); //��ʱ�����������

int GetBasePath(string& pth, list<base_config>& lstbc);

int GetOutlineLen(list<base_config>& lstbc, pthread_mutex_t& configMutex);

int SetDtmf(nway_uint64_t& id, const char* dtmf);

//�����л�ȡһ�����ߺ���
int GetInline(const string& OutsideNumber, string& InsideNumber, list<Outside_line>& lstOutsideline, pthread_mutex_t& configMutex);

int GetExtension(const string& strExtension,NwayExtension& ext, list<NwayExtension>& lstExtensions, pthread_mutex_t& configMutex);
int GetExtensionId(const string& strExtension,nway_uint64_t& id,list<NwayExtension>& lstExtensions, pthread_mutex_t& configMutex);

int GetIVRDetails(nway_uint64_t id, list<NwayIVRDetail>& lstIvrDetails, list<NwayIVRDetail>& myDetails, pthread_mutex_t& configMutex);

int SetAgentLoginState(nway_uint64_t id,int LoginState );//0,success, 1,logout, 2,busy, 3,leaved
int SetAgentRegState(const char* strExtension, list<NwayExtension>& lstExtensions, NWAY_AGENT_REG_STATE RegState, pthread_mutex_t& configMutex);// 0:REGED, 1:NOREGED
int SetAgentLoginStateBusyOrIdle(const char* strExtension,list<NwayExtension>& lstExtensions, int LoginState, pthread_mutex_t& configMutex);//0,success, 1,logout, 2,busy, 3,leaved);
int SetCallNumberCalled(nway_uint64_t& id );
//////////////////////////////////////////////////////////////////////////
//strFile��ȥ��basePath��·������records/xxx/xxx/xxx-xxxx-xxx-xxx.wav
//strFullName��ȫ�ļ�·��/home/voices/records/xxx/xxx/xxx-xxx-xxx-xxx.wav
int GetRecordFileName( string &strExtension, string &strFile, string &strFullName,  string& basePath ); 
//��ȡ����غ����б�
int GetClickDials(vector<Click_Dial>& vecClickDials);

int SetClickDialed(nway_uint64_t& id);

int GetConfigChanged(vector<int>& vecConfigs);
int SetConfigChanged(int orderid);

int ReLoadExtensions(list<NwayExtension>& lstExtensions );

#endif