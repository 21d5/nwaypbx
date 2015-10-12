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
#ifndef __NWAY_CTI_STATE_H
#define __NWAY_CTI_STATE_H


//�һ�����
typedef enum NWAY_HANGUP_CAUSE{
	HANGUP_CAUSE_NORMAL=1, //��ͨ�һ�
	HANGUP_CAUSE_IVR_NORMAL,  //IVR��ͨ�һ�
	HANGUP_CAUSE_UNANSWER,   //����Ӧ��
	HANGUP_CAUSE_IVR_UNANSWER,  //ivr����Ӧ��
	HANGUP_CAUSE_NO_FEE,    //���ò���
	HANGUP_CAUSE_BUSY,      //�Է�æ
	HANGUP_CAUSE_VOICEMAIL,  //��������
	HANGUP_CAUSE_UNKNOWN_NUMBER,//�޴˺���
	HANGUP_CAUSE_NOT_CALL,       //�޷�����
	HANGUP_CAUSE_NOT_CALLED      //�޷�����
};
//�һ����򣬼�˭�ȹһ�
enum NWAY_HANGUP_DIRECTION{
	HANGUP_DIRECTION_A_LEG = 0,    //A legһ��Ϊ���У��һ�
	HANGUP_DIRECTION_B_LEG,    //B leg һ��Ϊ���У��һ�
	HANGUP_DIRECTION_TRANFER   //����b legת�Ӹ�c
};
//����ת����ϯ״̬
enum NWAY_CALLIN_STATE{
	CALLIN_STANDBY = 0,    //����
	CALLIN_RINGING,        //����
	CALLIN_TALKING,			//ͨ����
	CALLIN_PENGING,			//�Ҷ���
	CALLIN_IVRING,			//IVR���� ��
	CALLIN_VOICEMAIL,		//��������
	CALLIN_BUSY,			//��æ
	CALLIN_WAIT				//�ȴ�
};
//��������״̬
enum NWAY_CALLOUT_STATE{
	CALLOUT_INIT = 0,		//��ʼ��
	CALLOUT_OUT ,			//����
	CALLOUT_A_TALKING,      //a leg ��ͨ
	CALLOUT_TALKING,		//ͨ����
	CALLOUT_SUCCESS,		//�ɹ�
	CALLOUT_FAILED,			//���ʧ��
				//��������
	CALLOUT_PLAY_RING,      //���Ų���
	CALLOUT_SECOND_PLAY_RING, //���Ŷ��β���
	CALLOUT_TRANS_AGENT      //

};
enum NWAY_AGENT_REG_STATE{
	AGENT_REG_SUCCESS = 0,  //��ע��
	AGENT_REG_FAILED        //δע��
};

enum NWAY_AGENT_LOGIN_STATE{
	AGENT_LOGIN_SUCCESS = 0,  //����
	AGENT_LOGIN_LOGOUT,       //����
	AGENT_LOGIN_BUSY,         //æ
	AGENT_LOGIN_LEAVED        //�뿪
};

enum NWAY_CALL_DIRECTION{
	CALL_DIRECTION_NORMAL = 0, //��ͨ����
	CALL_DIRECTION_CALLOUT 
};

enum NWAY_CALL_OPERATION{
	CALL_OPERATION_SET = 1, //����
	CALL_OPERATION_ANSWER,
	CALL_OPERATION_DTMF,
	CALL_OPERATION_BRIDGE,
	CALL_OPERATION_PLAYRING,
	CALL_OPERATION_SLEEP,
	CALL_OPERATION_SUBMENU,
	CALL_OPERATION_HANGUP,
	CALL_OPERATION_AGENT_LOGIN,
	CALL_OPERATION_AGETN_LOGOUT,
	CALL_OPERATION_ORIGINATE
};
typedef enum NWAY_CALLOUT_CONCURR_TYPE{
	CONCURR_FORECAST_CALL = 1, //Ԥ�����
	CONCURR_PRECISION_CALL,
	CONCURR_RING_CALL

};

typedef enum NWAY_CALL_EVENT{
	CALL_EVENT_CALL_IN = 1, //����
	CALL_EVENT_A_LEG_CALL,
	CALL_EVENT_A_LEG_TALKING,
	CALL_EVENT_A_LEG_HANGUP,
	CALL_EVENT_B_LEG_TALKING,
	CALL_EVENT_B_LEG_HANGUP,
	CALL_EVENT_B_LEG_CALL
};

#endif