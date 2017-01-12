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
@ ������Ʊ
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	unsigned int dis = 0;
	unsigned int cardNo = 0;
	int basePrice = 0;
	EN_RETURN_CODE returnCode;
    //��ȡ����վ��������� GetSubwayStationDis
	returnCode= GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation,unCmd.stCmdSingleTicket.dstStation,dis);
	if(EN_RETURN_SUCC != returnCode)
	{
		GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
		return;
	}
	//��ȡ����վ���Ļ���Ʊ��  GetBasePrice
	basePrice = GetBasePrice(dis);
    //�쵥�̿� AssignCard
	returnCode = AssignCard(cardNo,EN_CARD_TYPE_SINGLE,basePrice);
    //����ַ���
    GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, basePrice, returnStr);
    return;
}