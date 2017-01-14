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
@ 输出结果显示
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void GetOutputStr(EN_CMD_TYPE enCmd, EN_RETURN_CODE enResult, unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int balance, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	string strTemp;
	char str1[MAX_SEND_BUFFER_LENGTH];
	printf_s(str1,"查询<失败><卡号=%d><卡类型=%s>"
		,cardNo
		,GetCardTypeStr(enCard));
	strTemp += str1;
	memset(str1,0,MAX_SEND_BUFFER_LENGTH);
	if(cardNo >= MAX_CARD_NUM)
	{
		printf_s(str1,"<失败原因=%s\n>"
					  "无效的地铁卡");
	}
	if(EN_RETURN_INPUT_INVALID_CARDTYPE == enResult)
	{
		printf_s(str1,"<失败原因=%s\n>"
					  "无效的地铁卡类型");
	}
	if(EN_CARD_TYPE_SINGLE == enCard)
	{
		printf_s(str1,"<失败原因=%s\n>"
					  "单程卡没有记录");
	}
	strTemp += str1;
	memcpy(returnStr,strTemp.c_str(),MAX_SEND_BUFFER_LENGTH);
}

/*
@ 查询历史命令
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void ProcQueryHisCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	unsigned int balance;
	EN_CARD_TYPE enCard;
	//1.通过ID，获取卡信息
	EN_RETURN_CODE returnCode = GetCardInfo(unCmd.stCmdQueryHis.cardNo,balance,enCard);
	//2.判断类型是否支持查询
	if(returnCode != EN_RETURN_SUCC)
	{   //无效的卡输出
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,enCard, balance,returnStr);
	}
	if(enCard == EN_CARD_TYPE_SINGLE || enCard == EN_CARD_TYPE_BUTT)
	{   //卡类型不对
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,enCard, balance, returnStr);
	}
	//3.查询信息
	GetHistory(unCmd.stCmdQueryHis.cardNo,returnStr);
    return;
}


