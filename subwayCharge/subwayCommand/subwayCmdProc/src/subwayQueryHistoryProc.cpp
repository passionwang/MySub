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
@ 输出错误结果显示
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void GetOutputStr(EN_CMD_TYPE enCmd, EN_RETURN_CODE enResult, unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int balance, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	string strTemp;
	char temp[10];
	strTemp += "查询<失败><卡号=";
	_itoa_s(cardNo,temp,10);
	strTemp += temp;
	strTemp += "><卡类型=";
	strTemp += GetCardTypeStr(enCard);
	strTemp += "><失败原因=";
	if(cardNo >= MAX_CARD_NUM || EN_CARD_TYPE_BUTT == enCard)
	{
		strTemp += "无效的地铁卡";
	}
	if(EN_RETURN_INPUT_INVALID_CARDTYPE == enResult)
	{
		strTemp += "无效的地铁卡类型";
	}
	if(EN_CARD_TYPE_SINGLE == enCard)
	{
		strTemp += "单程卡没有记录";
	}
	strTemp += ">";

	memcpy(returnStr,strTemp.c_str(),MAX_SEND_BUFFER_LENGTH);
}

/*
@ 输出正确结果显示
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void Output(int cardNo,HistoryNode History[MAX_HISTORY],int HistoryIndex,int HistoryNowHave,char str[MAX_SEND_BUFFER_LENGTH])
{
	int index = 1;
	string strTemp;
	char temp[10];
	strTemp = "查询<成功><卡号=";
	_itoa_s(cardNo,temp,10,10);
	strTemp += temp;
	strTemp += "><卡类型=";
	strTemp += GetCardTypeStr(History[0].enCard);
	strTemp += ">\r\n";

	for(int i=HistoryIndex;i<HistoryNowHave;++i)
	{
		strTemp += "<序号=";
		_itoa_s(index,temp,10);
		strTemp += temp;
		++index;
		strTemp += ",进站时间=";
		_itoa_s(History[i].enterTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].enterTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].enterTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",进站站点=";
		strTemp += History[i].enterStation;
		strTemp += ",出站时间=";
		_itoa_s(History[i].exitTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].exitTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].exitTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",出站站点=";
		strTemp += History[i].exitStation;
		strTemp += ",消费金额=";
		_itoa_s(History[i].money,temp,10);
		strTemp += temp;
		strTemp += ">\r\n";
	}
	for(int i=0;i<HistoryIndex;++i)
	{
		strTemp += "<序号=";
		_itoa_s(index,temp,10);
		strTemp += temp;
		++index;
		strTemp += ",进站时间=";
		_itoa_s(History[i].enterTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].enterTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].enterTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",进站站点=";
		strTemp += History[i].enterStation;
		strTemp += ",出站时间=";
		_itoa_s(History[i].exitTime.hour,temp,10);
		strTemp += temp;
		strTemp += ":";
		if(History[i].exitTime.minutes<10)
			strTemp += "0";
		_itoa_s(History[i].exitTime.minutes,temp,10);
		strTemp += temp;
		strTemp += ",出站站点=";
		strTemp += History[i].exitStation;
		strTemp += ",消费金额=";
		_itoa_s(History[i].money,temp,10);
		strTemp += temp;
		strTemp += ">\r\n";
	}
	memcpy(str,strTemp.c_str(),MAX_SEND_BUFFER_LENGTH);
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
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,EN_CARD_TYPE_BUTT, balance,returnStr);
		return;
	}
	if(enCard == EN_CARD_TYPE_SINGLE || enCard == EN_CARD_TYPE_BUTT)
	{   //卡类型不对
		GetOutputStr(EN_CMD_TYPE_QUERY_HIS,returnCode,unCmd.stCmdQueryHis.cardNo,EN_CARD_TYPE_SINGLE, balance, returnStr);
		return;
	}
	//3.查询信息
	HistoryNode History[MAX_HISTORY];//所有卡的20条记录
	int HistoryIndex;       //记录的当前位置
	int HistoryNowHave;     //已经有的记录总数
	GetHistory(unCmd.stCmdQueryHis.cardNo,History,HistoryIndex,HistoryNowHave);
    Output(unCmd.stCmdQueryHis.cardNo,History,HistoryIndex,HistoryNowHave,returnStr);
	return;
}




