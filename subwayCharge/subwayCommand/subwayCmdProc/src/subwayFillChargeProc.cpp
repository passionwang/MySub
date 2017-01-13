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
@ ��ֵ����
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcFillChargeCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    unsigned int cardNo = unCmd.stCmdFillCharge.cardNo;
	unsigned int recharge = unCmd.stCmdFillCharge.cardCharge;
	unsigned int balance = 0;
	EN_RETURN_CODE returnCode;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;

    //��ȡ����Ϣ GetCardInfo
	returnCode = GetCardInfo(cardNo,balance,enCard);
	if(EN_RETURN_SUCC != returnCode)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);
		return;
	}
    //���г�ֵ RechargeCard
	returnCode = RechargeCard(cardNo,recharge);
    //���ݳ�ֵ��Ŀ���Ϣ  GetCardInfo
	if(EN_RETURN_SUCC != returnCode)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);
		return;
	}
	returnCode = GetCardInfo(cardNo,balance,enCard);
    //����ַ���
    GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);

    return;
}