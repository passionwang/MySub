#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;

unsigned int g_CardNumNow = 0;//��ǰ��������
unsigned int s_IndexNow = 0;//��ǰ�������
ST_SUBWAY_CARD G_cardList[MAX_CARD_NUM];  //���п���Ϣ
/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo()
{
    g_CardNumNow = 0;
	s_IndexNow = 0;
    for(int i = 0; i < MAX_CARD_NUM; i++)
    {
		G_cardList[i].balance = 0;
		G_cardList[i].cardNo = i;
		G_cardList[i].usrFlag = 0;
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
	
    if(999 < charge)
	{
		return EN_RETURN_RECHARGE_OVERFLOW;
	}
	//����IDδ����99
    if(s_IndexNow < MAX_CARD_NUM)
	{
		cardNo = g_CardNumNow;
		G_cardList[cardNo].balance = charge;
		G_cardList[cardNo].usrFlag = 1;
		G_cardList[cardNo].enCard = enCard;
		++g_CardNumNow;
		++s_IndexNow;
		return EN_RETURN_SUCC;
	}
	//����ID����99�����ǿ�Ƭ����û�г���100
	else if(s_IndexNow >= MAX_CARD_NUM && g_CardNumNow < MAX_CARD_NUM)
	{
		for(int i=0;i<MAX_CARD_NUM;++i)
		{
			if(0 == G_cardList[i].usrFlag)
			{
				cardNo = i;
				G_cardList[cardNo].balance = charge;
				G_cardList[cardNo].usrFlag = 1;
				G_cardList[cardNo].enCard = enCard;
				++g_CardNumNow;
			}
		}
		return EN_RETURN_SUCC;
	}
	else
	{
		return EN_RETURN_CARD_OVERLOW;
	}
}

/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge)
{
    if(cardNo >= MAX_CARD_NUM)
        return EN_RETURN_INVALID_CARD;
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_SINGLE)
		return EN_RETURN_SINGLE_CARD_CANNOT_RECHARGE;
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_INVALID_CARD;
	if(G_cardList[cardNo].balance + recharge > 999)
		return EN_RETURN_RECHARGE_OVERFLOW;
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
    if(cardNo >= MAX_CARD_NUM)
        return EN_RETURN_INVALID_CARD;
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_INVALID_CARD;
    balance = G_cardList[cardNo].balance;
    enCard = G_cardList[cardNo].enCard;
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
    if(cardNo >= MAX_CARD_NUM)
        return EN_RETURN_INVALID_CARD;
    if(G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_INVALID_CARD;
    if(G_cardList[cardNo].balance < deductPrice)
        return EN_RETURN_BALANCE_NOT_ENOUGH;
    G_cardList[cardNo].balance = G_cardList[cardNo].balance - deductPrice;
    if(enCard == EN_CARD_TYPE_SINGLE) {
		G_cardList[cardNo].enCard = EN_CARD_TYPE_BUTT;
		G_cardList[cardNo].balance = 0;
		G_cardList[cardNo].usrFlag = false;
		g_CardNumNow--;
		balance=0;
	}
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
    if(cardNo >= MAX_CARD_NUM)
        return EN_RETURN_INVALID_CARD;
	if(0 == G_cardList[cardNo].usrFlag)
		return -1;
	G_cardList[cardNo].balance = 0;
	G_cardList[cardNo].enCard = EN_CARD_TYPE_BUTT;
	G_cardList[cardNo].usrFlag = 0;
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
	case EN_CARD_TYPE_ELDER:
		return "���꿨";
	case EN_CARD_TYPE_NOMAL:
		return "��ͨ��";
	case EN_CARD_TYPE_BUTT:
		return "δ֪������";
	default:
		return NULL;
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
    if(cardType[0]=='a')
	{
		enCard=EN_CARD_TYPE_SINGLE;
		return EN_RETURN_SUCC;
	}
	else if(cardType[0]=='b')
	{
		enCard=EN_CARD_TYPE_ELDER;
		return EN_RETURN_SUCC;
	}
	else if(cardType[0]=='c')
	{
		enCard=EN_CARD_TYPE_NOMAL;
		return EN_RETURN_SUCC;
	}
	else
	{
		enCard=EN_CARD_TYPE_BUTT;
		return EN_RETURN_SUCC;
	}
    return EN_RETURN_INPUT_INVALID_CARDTYPE;
}