#ifndef ___NWAY_CTI_H__
#define ___NWAY_CTI_H__
#include <esl.h>
#include "../database/dbimp/CDBOperator.h"
//originate {return_ring_ready=true}sofia/gateway/liangping/18621575908 &bridge(user/8001)ͬʱ����

#define SYSTEM_V_CALL 9999                //4��9������һ�����������ţ����������ʱ�򣬺��������ȹ���Ȼ���ٰ���Ӧ���߼����д���

int get_uuid(char* uuid);
bool InitDatabase();
bool LoadConfigFromDb(list<base_config>& lstBaseConfig, list<NwayExtensionGroup>& lstExtensionGroup, list<NwayExtension>& lstExtension, \
	list<NwayGateway>& lstGateway, list<NwayDialplanDetail>& lstDialplanDetail, list<NwayDialplan>& lstDialplan, \
	list<NwayIVRDetail>& lstIvrDeatail, list<NwayIVR>& lstIvr, list<NwayRing>& lstRings, list<Outside_line>& lstOutsides,\
	list<In_Out_Mapping>& lstInOutMapping, list<NwayCalloutGateway>& lstCalloutGateways);
#endif