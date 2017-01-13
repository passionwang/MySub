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
@ 处理扣费命令
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void ProcDeductCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    unsigned int balance = 0;
    EN_CARD_TYPE enCard;
    //根据卡号获取卡信息  GetCardInfo
    EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdDeduct.cardNo,balance,enCard);
    if(returnCode == EN_RETURN_INVALID_CARD)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, EN_CARD_TYPE_BUTT, balance, returnStr);
        return;
    }
    //检查时间格式  CHECK_TIME
    if(!(CHECK_TIME(&unCmd.stCmdDeduct.enterTime) && CHECK_TIME(&unCmd.stCmdDeduct.exitTime)))
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, EN_RETURN_INVALID_TIME, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //计算乘车时长  DIFF_TIME
    int diffMinutes;
    DIFF_TIME(&unCmd.stCmdDeduct.exitTime,&unCmd.stCmdDeduct.enterTime,diffMinutes);
    if(diffMinutes < 0)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, EN_RETURN_INVALID_TIME, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //计算里程数  GetSubwayStationDis
    unsigned int dis;
    returnCode = GetSubwayStationDis(unCmd.stCmdDeduct.enterStation,unCmd.stCmdDeduct.exitStation,dis);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //计算扣费价格 GetDeductPrice
    unsigned int deductPrice;
    returnCode = GetDeductPrice(enCard,balance,dis,unCmd.stCmdDeduct.enterTime,unCmd.stCmdDeduct.exitTime,deductPrice);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //对乘车卡进行扣费 DeductCard
    returnCode = DeductCard(unCmd.stCmdDeduct.cardNo,enCard,deductPrice,balance);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //输出字符串
    if(balance < 20 && enCard != EN_CARD_TYPE_SINGLE)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, EN_RETURN_BALANCE_TOO_LOW, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
    }
    else
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
    }
    return;
}