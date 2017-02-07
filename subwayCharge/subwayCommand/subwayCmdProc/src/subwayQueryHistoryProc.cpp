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
@ ��������ʾ
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
	GetHistory(unCmd.stCmdQueryHis.cardNo,returnStr);
    return;
}


