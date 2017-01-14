#ifndef __CMD_QUERY_HISTORY_PROC_H__
#define __CMD_QUERY_HISTORY_PROC_H__
#include "subwayGlobalDef.h"
#include "subwayCmdParse.h"


struct HistoryNode
{
	unsigned int cardNo;  //����
	EN_CARD_TYPE enCard;  //������
	ST_SUBWAY_TIME enterTime;//��վʱ��
	ST_SUBWAY_TIME exitTime;//��վʱ��
	char enterStation[MAX_STATION_NAME_LENGTH];//��վվ��
	char exitStation[MAX_STATION_NAME_LENGTH];//��վվ��
	unsigned int money;  //���ѽ��
};

/*
@ ��ѯ��ʷ����
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void ProcQueryHisCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);

#endif