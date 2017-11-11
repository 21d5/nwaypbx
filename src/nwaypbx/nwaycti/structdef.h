#ifndef NWAY_STRUCT_DEF_H
#define NWAY_STRUCT_DEF_H
//
#include <string>
#include <list>
#include <time.h>
#include "../common/NwayDef.h"
#include "statedef.h"
#include <pcre.h>
using namespace std;
class NwayRing
{
public:
	nway_uint64_t id;
	string filename;
	NwayRing();
	NwayRing(const NwayRing& t);
	NwayRing& operator=(const NwayRing& t);
};

class NwayExtensionGroup
{
public:
	nway_uint64_t id;
	string group_name;
	NwayExtensionGroup();
	NwayExtensionGroup(const NwayExtensionGroup& t);
	NwayExtensionGroup& operator=(const NwayExtensionGroup& t);
};
//�ֻ�


class NwayExtension 
{
public:
	nway_uint64_t id;
	string extension_name;
	string extension_number;
	string password;//�绰�޸���ϯ����ʱ���ã��ݲ�֧��
	//int is_reg;
	//int login_state;
	int is_allow_callout;
	nway_uint64_t group_id;
	string callout_number;
	int extension_type;
	bool is_record;
	bool is_disable;
	nway_uint64_t callout_gateway;
	NWAY_AGENT_REG_STATE reg_state;
	NWAY_AGENT_LOGIN_STATE login_state;
	NWAY_CALLIN_STATE call_state;
	NWAY_CALLOUT_STATE callout_state;
	void clear();
	 
	NwayExtension();
	 
	NwayExtension& operator=(const NwayExtension& t) ;
	
	NwayExtension(const NwayExtension& t);

};
//�������
class NwayCalloutGateway{
public:
	nway_uint64_t id;// integer NOT NULL,
	string	name ;//character varying(255) NOT NULL,
	nway_uint64_t	gateway_id; //bigint
	NwayCalloutGateway();
	~NwayCalloutGateway();
	void Clear();
	NwayCalloutGateway(const NwayCalloutGateway& t);
	NwayCalloutGateway& operator=(const NwayCalloutGateway& t);
};
//����
class NwayGateway 
{
public:
	nway_uint64_t id;//bigserial;// NOT NULL,
	string	gateway_name ;//character varying(255), -- ��������
	string	gateway_url; // character varying(255),
	string	call_prefix;// character varying(50), -- ���ֹ���
	int	max_call;// integer, 
	NwayGateway();
	NwayGateway(const NwayGateway& t);
	NwayGateway& operator=(const NwayGateway& t);
	void clear();
};

//������ϸ
class NwayDialplanDetail 
{
public:
	nway_uint64_t id;
	nway_uint64_t dialplan_id ;
	string 	dialplan_detail_tag ;
	int 	dialplan_detail_type_id ;
	string 	dialplan_detail_data ;
	string	dialplan_detail_inline ;
	nway_uint64_t	dialplan_detail_group_id;
	nway_uint64_t ring_id;
	int	dialplan_detail_order ;
	bool	dialplan_detail_break ;
	NwayDialplanDetail();
	void clear();
	NwayDialplanDetail(const NwayDialplanDetail& t);
	NwayDialplanDetail& operator=(const NwayDialplanDetail& t);
	bool operator<(const NwayDialplanDetail& t);
	

};
//���żƻ�
class NwayDialplan
{
public:
	nway_uint64_t id;
	 
	string	dialplan_name ;
	string 	dialplan_context ;
	string	dialplan_number ;
	bool	dialplan_continue ;
	int	dialplan_order ;
	
	bool	dialplan_enabled ;
	//pcre *re;

	//const char *error;
	//int erroffset;
	NwayDialplan();
	void clear();
	NwayDialplan(const NwayDialplan& t);
	NwayDialplan& operator=(const NwayDialplan& t);
};
//IVR��ϸ
class NwayIVRDetail 
{
public:
	nway_uint64_t id;
	nway_uint64_t ivr_menu_id ;  
	string	ivr_menu_option_digits ;
	int	ivr_menu_option_action_id;
	string	ivr_menu_option_param ;
	int	ivr_menu_option_order ;
	string	ivr_menu_option_description ;
	NwayIVRDetail();
	void clear();
	NwayIVRDetail(const NwayIVRDetail& t);
	NwayIVRDetail& operator=(const NwayIVRDetail& t);
	bool operator<(const NwayIVRDetail& t);

};
//IVR
class NwayIVR 
{
public:
	nway_uint64_t id;
	string ivr_menu_name ;
	string	ivr_menu_extension ;	 
	nway_uint64_t	ivr_menu_greet_long_id ;//bigint,
	nway_uint64_t	ivr_menu_greet_short_id;// bigint,
	nway_uint64_t	ivr_menu_invalid_sound_id;// bigint,
	nway_uint64_t	ivr_menu_exit_sound_id;// bigint,
	nway_uint64_t	ivr_menu_ringback_id;// bigint,
	int	ivr_menu_exit_app_id;// integer,
	string	ivr_menu_confirm_macro ;
	string	ivr_menu_confirm_key ;
	int	ivr_menu_confirm_attempts ;// -- ���Դ���
	int	ivr_menu_timeout ;// -- ��ʱ����
	 
	string	ivr_menu_exit_data ;
	int	ivr_menu_inter_digit_timeout ;// -- �м䲻����ʱ�ĳ�ʱʱ��
	int	ivr_menu_max_failures ;//integer, -- ���ivr��������
	int	ivr_menu_max_timeouts ;//integer, -- ivr���ʱ����
	int ivr_menu_digit_len ;//integer, -- ���ְ�����󳤶�
	string	ivr_menu_direct_dial;// character varying(200),
	 
	string	ivr_menu_cid_prefix;// character varying(200),
	string	ivr_menu_description;// text, -- ˵��
	int	ivr_menu_call_crycle_order;// integer, -- �������ѭ�����еģ�ʵʱ��¼��ǰ���е��ӽڵ��order
	bool	ivr_menu_enabled ;//boolean,
	nway_uint64_t	ivr_menu_call_order_id ;//bigint,
	NwayIVR();
	void clear();
	NwayIVR(const NwayIVR& t);
	NwayIVR& operator=(const NwayIVR& t);
};
//base_config
//��������
class base_config 
{
public:
	nway_uint64_t id ;
	string config_name ;
	string config_param ;
	base_config();
	void clear();
	base_config(const base_config& t);
	base_config& operator=(const base_config& t);
};
//CDR
class NwayCDR
{
public:
	nway_uint64_t id  ;
	string accountcode  ;
	string xml_cdr  ;
	string  caller_id_name ;
	string caller_id_number ;
	string destination_number ;
	int star_epoch ;//�Ǵ�Epoch��1970��1��1��00:00:00 UTC����ʼ�����������������������롣
	string start_stamp;
	string a_answer_stamp ;//timestamp without time zone,
	int a_answer_epoch ;//numeric,�Ǵ�Epoch��1970��1��1��00:00:00 UTC����ʼ�����������������������롣

	int a_end_epoch ;//numeric,
	string a_end_stamp ;//timestamp without time zone,
	string b_answer_stamp ;//timestamp without time zone,
	int b_answer_epoch ;//numeric,�Ǵ�Epoch��1970��1��1��00:00:00 UTC����ʼ�����������������������롣

	int b_end_epoch ;//numeric,
	string b_end_stamp ;//timestamp without time zone,

	int duration ;//numeric,��Ϊ����a�ļ�ʱ
	int mduration ;//numeric,��Ϊ����b�ļ�ʱ
	int billsec;// numeric,
	string recording_file;// character varying(255),
	string conference_name;// character varying(50),
	nway_uint64_t conference_id ;//bigint,
	string digites_dialed;// character varying(50),
	string hangup_cause;// character varying(200),
	nway_uint64_t hangup_cause_id;// bigint,
	int waitsec ;//integer,
	nway_uint64_t call_gateway_id;// bigint,
	int hangup_direction;//�һ�����
	string called_number;// bigint, -- ���ܺ��뻹�Ǻ����ĺ���,���и���Ӫ�̸���0596-6147000�ĺ��룬�û��Ǵ�����Ȼ����ת������ĺ���
	NwayCDR();
	void clear();
	NwayCDR(const NwayCDR& t);
	NwayCDR& operator=(const NwayCDR& t);
};

//��������
class Outside_line 
{
public:
	nway_uint64_t id ;
	string outside_line_name;// character varying(50), -- ��������
	string	outside_line_number;// character varying(50), -- ���ߺ���
	string	inside_line_number;// character varying(50) DEFAULT NULL::character varying, -- ���ߺ���
	bool	is_record ;//integer DEFAULT 0, -- �Ƿ�¼����0��¼��1¼
	bool	is_voice_mail;// integer, -- �Ƿ��������䣬0����ͨ��1��ͨ
	nway_uint64_t	call_order_id;// bigint DEFAULT 0, -- ����˳�����߿���ֱת���ߺ��룬���������ö����ivr
	nway_uint64_t	call_crycle_order;// bigint DEFAULT 0, -- ѭ�����еĵ�ǰ���е���ֵ
	Outside_line();
	Outside_line(const Outside_line& t);
	void clear();
	Outside_line& operator=(const Outside_line& t);
};

//�����߶�Ӧ
//���ư󶨺���
//����ʹ���У�����������಻��̫�ã��ݲ���
//2014-10-29
class In_Out_Mapping
{
public:
	nway_uint64_t outside_line_id;// bigint;// DEFAULT 0,
	nway_uint64_t	inside_line_id ;//bigint DEFAULT 0,
	nway_uint64_t	order_number;// integer DEFAULT 0, 
	In_Out_Mapping();
	void clear();
	In_Out_Mapping(const In_Out_Mapping& t);
	In_Out_Mapping& operator=(const In_Out_Mapping& t);
};
//���봦��
class Call_info 
{
public:
	nway_uint64_t id;
	//���±���Ϊ��directionΪCALL_DIRECTION_CALLOUTʱ������д���������Ӧ�Ĳ���������׼������ֱ�Ӻ�����ϯ���Ǿ�׼����
	//�ǵȴ�������ٺ���ϯ
	nway_uint64_t callout_id; //���������ģ����¼�����id�������ں����󽫺���״̬�޸�
	NWAY_CALL_DIRECTION call_direction;
	int waitsec;//�ȴ�����
	string to_agent_group;//Ҫת����ϯ����
	string ring_path;//����
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	string caller_uuid; //��Ϊ�����У����磬������ֵĿͻ����룩
	string caller_number;
	string called_number; //���к���
	list<NwayExtension> lstBind;//Ҫ��ת���ĺ���ȫ���ڴ˴�
	string trans_uuid; //ת��uuid
	string trans_number;//ת������
	NWAY_CALLIN_STATE caller_state; //��������״̬
	NWAY_CALLOUT_STATE trans_state; //��ת��״̬
	NWAY_HANGUP_CAUSE caller_hangup; 
	NWAY_HANGUP_CAUSE trans_hangup;
	NWAY_HANGUP_DIRECTION hangup_direction;
	int call_info_type; //0��ͨ���� ��1 IVR ���룬2 ���
	bool bHangup; //bleg �ȹһ�

	time_t   caller_callin_tm; //����ʱ��
	time_t   caller_answer_tm; //�����ͨ
	time_t   caller_hangup_tm; //����һ�
	time_t   trans_callout_tm ; //������ת����ʱ��
	time_t   trans_answer_tm;  //
	time_t   trans_hangup_tm; //

	nway_uint64_t cdr_id;//������cdrʱ��id,����ʱ��Ҫcdr_ID
	Call_info();
	void clear();
	Call_info(const Call_info& t);
	Call_info& operator=(const Call_info& t);

};
//������Ϣ

class Callout_info 
{
public:

	//////////////////////////////////////////////////////////////////////////
	nway_uint64_t id;// NOT NULL,
	nway_uint64_t group_id;// bigint,
	string	number;//����
	int	is_called ;//integer DEFAULT 0, -- �Ƿ���й���
	int	call_state;// integer DEFAULT 0, -- ����״̬
	//	start_time timestamp without time zone,
	//	answer_time timestamp without time zone,
	//	hangup_time timestamp without time zone,
	nway_uint64_t	hangup_reason_id;// bigint,
	nway_uint64_t	answer_extension_id;// bigint,
	
	string	record_file;// character varying(255), -- ¼���ļ�
	int	wait_sec ;//integer, -- �ȴ�ʱ��

	//////////////////////////////////////////////////////////////////////////
	string gateway_url;//gateway url
	string call_prefix;//����ǰ׺
	int ring_times;//���岥�Ŵ�����Ĭ��1
	string call_a_leg_uuid; //����ʱaleg��uuid
	string call_b_leg_uuid; //����ʱ��bleg uuid

	nway_uint64_t cdrid;
	bool bAlegHangup; //���йһ�
	bool bBlegHangup; //b leg hangup
	bool bRemoveThis;//�ں���ʧ��ʱ�Ƿ�ɾ���������

	string extension_number;
	//////////////////////////////////////////////////////////////////////////
	NWAY_CALLOUT_STATE callout_state;
	Callout_info();
	void clear();
	Callout_info(const Callout_info& t);
	Callout_info& operator=(const Callout_info& t);
};

//��������
class Callout_Task{
public:
	nway_uint64_t id ;
	string	callout_name;
	nway_uint64_t number_group_id; //���к�����
	string	number_group_uploadfile;// character varying(255),
	nway_uint64_t	run_position;//��order by�����е�idλ��
	nway_uint64_t	time_rule_id ;//ʱ��ƻ����ݲ���
	string	start_time; //��ʼʱ��
	string	stop_time ;//����ʱ��
	nway_uint64_t	ring_id;//����
	int	after_ring_play ;// �����Ĳ�������call_after_opt��Ӧ����Ҫ�Ǽ������壬�һ���ת��ϯ
	int	ring_timeout;// -- ����ʱ��,����ʱδ������һ�
	nway_uint64_t	group_id;// -- ���е���ϯ��
	nway_uint64_t	call_project_id;
	nway_uint64_t	concurr_type_id ;// -- �������ͣ�0Ϊ��������ϯ�����ı�����1Ϊָ��ֵ
	int	concurr_number;//  -- �������������������ʹ�������
	nway_uint64_t	callout_state_id;//  �ȴ����У����ں��У���ͣ�����
	int	total_number ;//�ܺ��������������ڱ�Ӧ���и�
	int	wait_number ;//integer DEFAULT 0, -- �ȴ�����,����-��ͨ-ʧ��
	int	success_number;// integer DEFAULT 0, -- ��ͨ����, ��ͨ+��Ӧ����ÿ�εĽ�ͨ��
	int	failed_number ;//integer DEFAULT 0, -- ��ͨʧ������
	int	cancel_number ;//integer DEFAULT 0, -- ȡ��������,�ݲ��ù�
	bool	has_parse_from_file;// ���ϴ����ļ����Ƿ���ļ��н��������ݲ嵽���ݱ��У�������������Ϊtrue
	nway_uint64_t	callout_gateway_id;// ������ص�id
	int	max_concurr_number;//    -- ��󲢷�����ǰһ��concurr_numberΪ��������
	nway_uint64_t	second_ring_id ;//-- ��after_ring_play��Ϊ���Ų�����Ч
	int	second_after_ring_opt ;//integer DEFAULT 0, -- �ڶ����ٲ��ź�Ĳ�������call_after_opt��Ӧ
	string	after_ring_key ;// -- ��������ʱ������ֹ����
	int	after_key_opt_id ;// -- ������Ĳ�������call_after_opt��Ӧ
	string outside_line_number;//���Ժ���
	//////////////////////////////////////////////////////////////////////////
	//��Ϊ���ݿ����ֶΣ�������Ϣ�����ݿ��ѯʱ���
	nway_uint64_t gateway_id;//������ض�Ӧ�ľ������ʵ���ص�id
	string gateway_url;//gateway url
	string call_prefix;//����ǰ׺
	int gateway_max_line;//���ص�����������
	//////////////////////////////////////////////////////////////////////////
	list<Callout_info> lstCalloutInfo;//��Ա�������ĺ����嵥
	Callout_Task();
	void Clear();
	Callout_Task(const Callout_Task& t);
	Callout_Task& operator=(const Callout_Task& t);
};


typedef struct Call_Task 
{
public:
	NWAY_CALL_OPERATION task_operate; // so : originate , playback, bridge
	string a_uuid;  //
	string b_uuid;
	string task_cmd; //it is a command for running 
	bool a_leg_answer;//a leg is answered?

	Call_Task();
	void Clear();
	Call_Task(const Call_Task& t);
	Call_Task& operator=(const Call_Task& t);
};
typedef struct Click_Dial
{
	nway_uint64_t id ;//bigserial NOT NULL,
	string	caller_number;// character(50), -- �ͻ��绰�����ֻ��ţ�����3721����0
	bool	is_agent ;//boolean DEFAULT false, -- �Ƿ�����voip����
	bool	is_immediately;// boolean DEFAULT false, -- �Ƿ�����ִ��
	string	trans_number;// character varying(50), -- ת�Ӻ���
	time_t	time_plan;// timestamp without time zone, -- ��is_immediatelyΪFALSEʱ��Ч����ʱ����
	string	account_number ;//character varying(50), -- �Ʒ��ʻ�
	bool	is_called;// boolean DEFAULT false, -- �Ƿ����
	Click_Dial();
	~Click_Dial();
	void Clear();
	Click_Dial(const Click_Dial& t);
	Click_Dial& operator=(const Click_Dial& t);
};
#endif