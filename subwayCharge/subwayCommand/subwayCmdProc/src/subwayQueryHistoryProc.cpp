#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
#include "subwayCmdParse.h"
#include "subwayline.h"
#include "subwayPrice.h"
#include "subwayCommon.h"
#include "subwayOutput.h"
#include "subwayError.h"

using namespace std;



/*
@ �����������ʾ
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void GetOutputStr(EN_CMD_TYPE enCmd, EN_RETURN_CODE enResult, unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int balance, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	string strTemp;
	char temp[10];
	strTemp += "��ѯ<ʧ��><����=";
	_itoa_s(cardNo,temp,10);
	strTemp += temp;
	strTemp += "><������=";
	strTemp += GetCardTypeStr(enCard);
	strTemp += "><ʧ��ԭ��=";
	if(cardNo >= MAX_CARD_NUM || EN_CARD_TYPE_BUTT == enCard)
	{
		strTemp += "��Ч�ĵ�����";
	}
	if(EN_RETURN_INPUT_INVALID_CARDTYPE == enResult)
	{
		strTemp += "��Ч�ĵ���������";
	}
	if(EN_CARD_TYPE_SINGLE == enCard)
	{
		strTemp += "���̿�û�м�¼";
	}
	strTemp += ">";

	memcpy(returnStr,strTemp.c_str(),MAX_SEND_BUFFER_LENGTH);
}

/*
@ �����ȷ�����ʾ
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void Output(int cardNo,HistoryNode History[MAX_HISTORY],int HistoryIndex,int HistoryNowHave,char str[MAX_SEND_BUFFER_LENGTH])
{
	int index = 1;
	string strTemp;
	char temp[10];
	strTemp = "��ѯ<�ɹ�><����=";
	_itoa_s(cardNo,temp,10,10);
	strTemp += temp;
	strTemp += "><������=";
	strTemp += GetCardTypeStr(History[0].enCard);
	strTemp += ">\r\n";

	for(int i=HistoryIndex;i<HistoryNowHave;++i)
	{
		strTemp += "<���=";
		_itoa_s(index,temp,10);
		strTemp += temp;
		++index;
		strTemp += ",��վʱ��=";
		_itoa_s(History[i].enterTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].enterTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].enterTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",��վվ��=";
		strTemp += History[i].enterStation;
		strTemp += ",��վʱ��=";
		_itoa_s(History[i].exitTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].exitTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].exitTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",��վվ��=";
		strTemp += History[i].exitStation;
		strTemp += ",���ѽ��=";
		_itoa_s(History[i].money,temp,10);
		strTemp += temp;
		strTemp += ">\r\n";
	}
	for(int i=0;i<HistoryIndex;++i)
	{
		strTemp += "<���=";
		_itoa_s(index,temp,10);
		strTemp += temp;
		++index;
		strTemp += ",��վʱ��=";
		_itoa_s(History[i].enterTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].enterTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].enterTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",��վվ��=";
		strTemp += History[i].enterStation;
		strTemp += ",��վʱ��=";
		_itoa_s(History[i].exitTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].exitTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].exitTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",��վվ��=";
		strTemp += History[i].exitStation;
		strTemp += ",���ѽ��=";
		_itoa_s(History[i].money,temp,10);
		strTemp += temp;
		strTemp += ">\r\n";
	}
	memcpy(str,strTemp.c_str(),MAX_SEND_BUFFER_LENGTH);
}
/*
@ ��ѯ��ʷ����
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void ProcQueryHisCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	unsigned int balance;
	EN_CARD_TYPE enCard;
	//1.ͨ��ID����ȡ����Ϣ
	EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdQueryHis.cardNo,balance,enCard);
	//2.�ж������Ƿ�֧�ֲ�ѯ
	if(returnCode != EN_RETURN_SUCC)
	{   //��Ч�Ŀ����
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,EN_CARD_TYPE_BUTT, balance,returnStr);
		return;
	}
	if(enCard == EN_CARD_TYPE_SINGLE || enCard == EN_CARD_TYPE_BUTT)
	{   //�����Ͳ���
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,EN_CARD_TYPE_SINGLE, balance, returnStr);
		return;
	}
	//3.��ѯ��Ϣ
	HistoryNode History[MAX_HISTORY];//���п���20����¼
	int HistoryIndex;       //��¼�ĵ�ǰλ��
	int HistoryNowHave;     //�Ѿ��еļ�¼����
	GetHistory(unCmd.stCmdQueryHis.cardNo,History,HistoryIndex,HistoryNowHave);
    Output(unCmd.stCmdQueryHis.cardNo,History,HistoryIndex,HistoryNowHave,returnStr);
	return;
}




