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
@ 充值命令
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcFillChargeCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    unsigned int cardNo = unCmd.stCmdFillCharge.cardNo;
	unsigned int recharge = unCmd.stCmdFillCharge.cardCharge;
	unsigned int balance = 0;
	EN_RETURN_CODE returnCode;
	EN_CARD_TYPE enCard = EN_CARD_TYPE_BUTT;

    //获取卡信息 GetCardInfo
	returnCode = GetCardInfo(cardNo,balance,enCard);
	if(EN_RETURN_SUCC != returnCode)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);
		return;
	}
    //进行充值 RechargeCard
	returnCode = RechargeCard(cardNo,recharge);
    //根据充值后的卡信息  GetCardInfo
	if(EN_RETURN_SUCC != returnCode)
	{
		GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);
		return;
	}
	returnCode = GetCardInfo(cardNo,balance,enCard);
    //输出字符串
    GetOutputResultStr(EN_CMD_TYPE_FILL_CHARGE, returnCode, cardNo, enCard, balance, returnStr);

    return;
}