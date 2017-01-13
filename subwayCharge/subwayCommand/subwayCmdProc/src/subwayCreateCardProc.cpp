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
@ ������ͨ��
@ ��Σ�unCmd, ��������
@ ����: returnStr
@ ����ֵ: ��
*/
void ProcCreateCardCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
    //ʶ������ 
	 EN_CARD_TYPE enCard;
	 EN_RETURN_CODE returnCode;
	 returnCode = GetCardType(unCmd.stCmdCreateCard.cardType,enCard);

	 if(enCard == EN_CARD_TYPE_SINGLE || enCard == EN_CARD_TYPE_BUTT)
	{
		returnCode = EN_RETURN_INPUT_INVALID_CARDTYPE;
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, 0, enCard, 0, returnStr);
		return;
	}

    //�쿨 
	unsigned int cardNo;
	returnCode = AssignCard(cardNo,enCard,unCmd.stCmdCreateCard.cardCharge);
	if(returnCode != EN_RETURN_SUCC)
	{
		GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, 0, enCard, 0, returnStr);
		return;
	}
	 //����ַ���
    GetOutputResultStr(EN_CMD_TYPE_CREATE_CARD, returnCode, cardNo, enCard, unCmd.stCmdCreateCard.cardCharge, returnStr);
    return;
}