#ifndef __CMD_QUERY_HISTORY_PROC_H__
#define __CMD_QUERY_HISTORY_PROC_H__
#include "subwayGlobalDef.h"
#include "subwayCmdParse.h"


struct HistoryNode
{
	unsigned int cardNo;  //卡号
	EN_CARD_TYPE enCard;  //卡类型
	ST_SUBWAY_TIME enterTime;//进站时间
	ST_SUBWAY_TIME exitTime;//出站时间
	char enterStation[MAX_STATION_NAME_LENGTH];//进站站点
	char exitStation[MAX_STATION_NAME_LENGTH];//出站站点
	unsigned int money;  //消费金额
};

/*
@ 查询历史命令
@ 入参：stCmdDeduct, 命令内容
@ 出参: returnStr
@ 返回值: void
*/
void ProcQueryHisCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);

#endif