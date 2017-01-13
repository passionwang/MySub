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
using namespace std;

/*
@ 办理单程票
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcCreateSingleTicketCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	unsigned int dis=0,cardNo=0;
	int money=0;
	EN_RETURN_CODE returnCode=EN_RETURN_SUCC;

    //获取两个站点间的里程数 GetSubwayStationDis
	returnCode=GetSubwayStationDis(unCmd.stCmdSingleTicket.srcStation,unCmd.stCmdSingleTicket.dstStation,dis);
	if(EN_RETURN_SUCC==returnCode)
	{
		//获取两个站点间的基本票价  GetBasePrice
		money=GetBasePrice(dis);
		//办单程卡 AssignCard
		returnCode=AssignCard(cardNo,EN_CARD_TYPE_SINGLE,money);
	}

    //输出字符串
    GetOutputResultStr(EN_CMD_TYPE_SINGLE_TICKET, returnCode, cardNo, EN_CARD_TYPE_SINGLE, money, returnStr);
    return;
}