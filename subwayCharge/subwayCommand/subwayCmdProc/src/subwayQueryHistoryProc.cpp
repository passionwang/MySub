#include "stdafx.h"
#include <iostream>
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
	char str1[MAX_SEND_BUFFER_LENGTH];
	printf_s(str1,"��ѯ<ʧ��><����=%d><������=%s>"
		,cardNo
		,GetCardTypeStr(enCard));
	strTemp += str1;
	memset(str1,0,MAX_SEND_BUFFER_LENGTH);
	if(cardNo >= MAX_CARD_NUM)
	{
		printf_s(str1,"<ʧ��ԭ��=%s\n>"
					  "��Ч�ĵ�����");
	}
	if(EN_RETURN_INPUT_INVALID_CARDTYPE == enResult)
	{
		printf_s(str1,"<ʧ��ԭ��=%s\n>"
					  "��Ч�ĵ���������");
	}
	if(EN_CARD_TYPE_SINGLE == enCard)
	{
		printf_s(str1,"<ʧ��ԭ��=%s\n>"
					  "���̿�û�м�¼");
	}
	strTemp += str1;
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
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,enCard, balance,returnStr);
	}
	if(enCard == EN_CARD_TYPE_SINGLE || enCard == EN_CARD_TYPE_BUTT)
	{   //�����Ͳ���
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,enCard, balance, returnStr);
	}
	//3.��ѯ��Ϣ
	GetHistory(unCmd.stCmdQueryHis.cardNo,returnStr);
    return;
}


