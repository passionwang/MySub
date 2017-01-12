#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;

unsigned int g_CardNumNow = 0;
ST_SUBWAY_CARD G_cardList[MAX_CARD_NUM];  //���п���Ϣ
/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo()
{
    for(int i = 0; i < MAX_CARD_NUM; i++)
    {
		G_cardList[i].balance = 0;
		G_cardList[i].cardNo = i;
		G_cardList[i].usrFlag = false;
		G_cardList[i].enCard = EN_CARD_TYPE_BUTT;
    }
}

/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
    if(g_CardNumNow < MAX_CARD_NUM-1)
	{
		cardNo = g_CardNumNow;
		G_cardList[cardNo].balance = charge;
		G_cardList[cardNo].usrFlag = true;
		G_cardList[cardNo].enCard = enCard;
		++g_CardNumNow;
		return EN_RETURN_SUCC;
	}
	if(g_CardNumNow == MAX_CARD_NUM-1)
	{
		return EN_RETURN_CARD_OVERLOW;
	}
    return EN_RETURN_SUCC;
}

/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge)
{
	if(G_cardList[cardNo].balance + recharge > 999)
		return EN_RETURN_BUTT;
	G_cardList[cardNo].balance += recharge;
    return EN_RETURN_SUCC;
}

/*
@ ��ȡ�����
@ ��Σ�cardNo,����; 
@ ����: balance: ���
        enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard)
{
    balance = G_cardList[cardNo].balance;
    return EN_RETURN_SUCC;
}

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance)
{
    if(G_cardList[cardNo].balance - deductPrice < 0)
		return EN_RETURN_BALANCE_NOT_ENOUGH;
	G_cardList[cardNo].balance -= deductPrice;
    return EN_RETURN_SUCC;
}

/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����; 
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo)
{
	G_cardList[cardNo].balance = 0;
	G_cardList[cardNo].enCard = EN_CARD_TYPE_BUTT;
	G_cardList[cardNo].usrFlag = false;
    return 0;
}

/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������; 
@ ����: ��
@ ����ֵ: �������ַ���;
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard)
{
    switch(enCard)
	{
	case EN_CARD_TYPE_SINGLE:
		return "���̿�";
		break;
	case EN_CARD_TYPE_ELDER:
		return "���꿨";
		break;
	case EN_CARD_TYPE_NOMAL:
		return "��ͨ��";
		break;
	case EN_CARD_TYPE_BUTT:
		return "����";
		break;
	default:
		return NULL;
			break;
	}
}

/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���; 
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard)
{
    

    return EN_RETURN_SUCC;
}