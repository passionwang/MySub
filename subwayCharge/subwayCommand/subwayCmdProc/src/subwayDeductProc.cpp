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
@ ����۷�����
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void ProcDeductCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    unsigned int balance = 0;
    EN_CARD_TYPE enCard;
    //���ݿ��Ż�ȡ����Ϣ  GetCardInfo
    EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdDeduct.cardNo,balance,enCard);
    if(returnCode == EN_RETURN_INVALID_CARD)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, EN_CARD_TYPE_BUTT, balance, returnStr);
        return;
    }
    //���ʱ���ʽ  CHECK_TIME
    if(!(CHECK_TIME(&unCmd.stCmdDeduct.enterTime) && CHECK_TIME(&unCmd.stCmdDeduct.exitTime)))
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, EN_RETURN_INVALID_TIME, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //����˳�ʱ��  DIFF_TIME
    int diffMinutes;
    DIFF_TIME(&unCmd.stCmdDeduct.exitTime,&unCmd.stCmdDeduct.enterTime,diffMinutes);
    if(diffMinutes < 0)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, EN_RETURN_INVALID_TIME, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //���������  GetSubwayStationDis
    unsigned int dis;
    returnCode = GetSubwayStationDis(unCmd.stCmdDeduct.enterStation,unCmd.stCmdDeduct.exitStation,dis);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //����۷Ѽ۸� GetDeductPrice
    unsigned int deductPrice;
    returnCode = GetDeductPrice(enCard,balance,dis,unCmd.stCmdDeduct.enterTime,unCmd.stCmdDeduct.exitTime,deductPrice);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //�Գ˳������п۷� DeductCard
    returnCode = DeductCard(unCmd.stCmdDeduct.cardNo,enCard,deductPrice,balance);
    if(returnCode != EN_RETURN_SUCC)
    {
        GetOutputResultStr(EN_CMD_TYPE_DEDUCT, returnCode, unCmd.stCmdDeduct.cardNo, enCard, balance, returnStr);
        return;
    }
    //����ַ���
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