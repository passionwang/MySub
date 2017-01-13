#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;

unsigned int g_CardNumNow = 0;//当前开卡数量
unsigned int s_IndexNow = 0;//当前最大索引
ST_SUBWAY_CARD G_cardList[MAX_CARD_NUM];  //所有卡信息
/*
@ 初始化所有卡信息
@ 返回值: 无
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
@ 开卡，分配卡号和卡信息
@ 入参：enCard,卡类型; charge: 充值
@ 出参: cardNo, 分配的卡号
@ 返回值: EN_RETURN_SUCC，分配成功; EN_RETURN_CARD_OVERLOW, 分配失败;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
	
    if(999 < charge)
	{
		return EN_RETURN_RECHARGE_OVERFLOW;
	}
	//索引ID未超过99
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
	//索引ID超过99，但是卡片数量没有超过100
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
@ 充值
@ 入参：cardNo,卡号; recharge: 充值
@ 出参: 无
@ 返回值: EN_RETURN_SUCC，成功; 其他, 失败;
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
@ 获取卡余额
@ 入参：cardNo,卡号; 
@ 出参: balance: 余额
        enCard:  卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, 失败;
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
@ 卡扣费
@ 入参：cardNo,卡号; enCard, 卡类型; deductPrice, 扣费票价
@ 出参: balance, 扣费后的余额
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, 失败;
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
@ 删除卡信息
@ 入参：cardNo,卡号; 
@ 出参: 无
@ 返回值: 0，成功; -1, 失败;
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
@ 获取卡类型字符串
@ 入参：enCard,卡类型; 
@ 出参: 无
@ 返回值: 卡类型字符串;
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard)
{
    switch(enCard)
	{
	case EN_CARD_TYPE_SINGLE:
		return "单程卡";
	case EN_CARD_TYPE_ELDER:
		return "老年卡";
	case EN_CARD_TYPE_NOMAL:
		return "普通卡";
	case EN_CARD_TYPE_BUTT:
		return "未知卡类型";
	default:
		return NULL;
	}
}

/*
@ 根据卡类型字符串, 识别卡类型
@ 入参：cardType,      卡类型字符串; 
@ 出参: enCard,        卡类型
@ 返回值: EN_RETURN_SUCC，成功; EN_RETURN_INPUT_INVALID_CARDTYPE, 失败;
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