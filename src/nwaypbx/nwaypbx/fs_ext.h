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

#ifndef __NWAY_PBX_FREESWITCH_EXT__
#define __NWAY_PBX_FREESWITCH_EXT__
#include <esl.h>
#include <vector>
#include "../common/nway-lib/PcreCpp.h"

using namespace std;
//��������һ���ִ���������������-���ӿĳһ��������Դ�����ļ���

int check_event_body(const char*eventbody, char*dtmfbuf, int maxdtmf, char* endchar, int *channel_execute);


int check_acm_body(const char*eventbody, char*uuid);
int check_event(esl_handle_t *handle, int timer);

int check_last_event(esl_handle_t *handle, int timer);

int check_acm_event(esl_handle_t *handle, int timer, char* uuid);

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
int check_play_dtmf_event(esl_handle_t *handle, char*enddtmf, int MaxDtmf, int MaxTimer, int TwoDtmfTimer, char*outdtmf);
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
//#define  playdir  "d:/data/system"
int play_get_dtmf(esl_handle_t *handle, const char*filename0, const char* invalidfile, const char*EndDtmf, int MaxDtmf, int MaxTimer, int TwoDtmfTimer, int MaxFailure, char*outdtmf);
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

int check_record_dtmf_event(esl_handle_t *handle, char*enddtmf, int MaxDtmf, int MaxTimer, int TwoDtmfTimer, char*outdtmf);
// ¼ ��ȡ��������
// ����: <0 ��ʾ�Է��һ���=100 ��ʾ�������ʱ������������� =101 ��ʾ����������ļ��ʱ�����������������,=3��ʾ ������������,����"#" ���㣬=2��ʾ ��󰴼������������� ����
// ����:handle:�Ựhandle
// uuid�� �Ự��id
// filename:�����ļ����ƣ�����ļ��Էֺ�";"����,�ļ����ƿ��Դ�.wav,��չ��,����û��,Ĭ����.pcm��չ��.��ָ��·��,����û��,Ĭ�������������./data/systemĿ¼��
// EndDtmf:������������,����"#"��ʾ��#�Ž�������,""��ʾû�н�����������//֧�����3���������� ���� EndDtmf="*0#" ��ʾ�� 0��* ����#�����Խ���
// MaxDtmf:��󰴼�������������,0��ʾû�а���������������
// MaxTimer:�������ʱ���������,��λ��,0��ʾû�����ʱ���������
// TwoDtmfTimer:����������ļ��ʱ���������,��λ��,0��ʾû������������ļ��ʱ���������
// outdtmf:�յ����û��İ���(�������),������������������,����"#"
int record_get_dtmf(esl_handle_t *handle, char*uuid, char*filename, char*EndDtmf, int MaxDtmf, int MaxTimer, int TwoDtmfTimer, char*outdtmf);

bool get_uuid(esl_handle_t* pHandle, char* uuid);

bool nway_hangup(esl_handle_t* pHandle, const char* uuid);

bool nway_isdigit(const char* str);

bool nway_bridge(esl_handle_t* pHandle, const char* a_uuid, const char* b_uuid);

bool nway_playring(esl_handle_t* pHandle, const char* uuid, const char* ring_file);

void get_nway_dialstring(const char* srcstr, char* desstr, vector<MatchResult>& matchs);
#endif



