#ifndef __NWAY_CALLOUT_H
#define __NWAY_CALLOUT_H

//////////////////////////////////////////////////////////////////////////
//���������ر�Ĳ���
//2014-9-29
//author:li hao
//////////////////////////////////////////////////////////////////////////
#include "../interface/db_center.h"
#include "../../nwaycti/statedef.h"
#include "../../nwaycti/structdef.h"
#include <list>
using namespace std;
class CDBCallout
{
public:
	CDBCallout();
	~CDBCallout();
protected:
	int GetCalloutInfo(list<Callout_info>& lstcallinfo);
private:
};
#endif