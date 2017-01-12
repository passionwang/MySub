#include "stdafx.h"
#include <iostream>
#include "list.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "subwayCard.h"
using namespace std;

unsigned int g_CardNumNow = 0;
ST_SUBWAY_CARD G_cardList[MAX_CARD_NUM];  //所有卡信息
/*
@ 初始化所有卡信息
@ 返回值: 无
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
@ 开卡，分配卡号和卡信息
@ 入参：enCard,卡类型; charge: 充值
@ 出参: cardNo, 分配的卡号
@ 返回值: EN_RETURN_SUCC，分配成功; EN_RETURN_CARD_OVERLOW, 分配失败;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge)
{
	static unsigned int s_IndexNow = 0;
	//索引ID未超过99
    if(s_IndexNow < MAX_CARD_NUM)
	{
		cardNo = g_CardNumNow;
		G_cardList[cardNo].balance = charge;
		G_cardList[cardNo].usrFlag = true;
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
			if(false == G_cardList[i].usrFlag)
			{
				cardNo = i;
				G_cardList[cardNo].balance = charge;
				G_cardList[cardNo].usrFlag = true;
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
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_SINGLE || G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_BUTT;
	if(G_cardList[cardNo].balance + recharge > 999)
		return EN_RETURN_BUTT;
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
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_SINGLE || G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_INVALID_CARD;
    balance = G_cardList[cardNo].balance;
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
	if(G_cardList[cardNo].enCard == EN_CARD_TYPE_SINGLE || G_cardList[cardNo].enCard == EN_CARD_TYPE_BUTT)
		return EN_RETURN_INVALID_CARD;
    if(G_cardList[cardNo].balance - deductPrice < 0)
		return EN_RETURN_BALANCE_NOT_ENOUGH;
	G_cardList[cardNo].balance -= deductPrice;
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
	if(false == G_cardList[cardNo].usrFlag)
		return -1;
	G_cardList[cardNo].balance = 0;
	G_cardList[cardNo].enCard = EN_CARD_TYPE_BUTT;
	G_cardList[cardNo].usrFlag = false;
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
		break;
	case EN_CARD_TYPE_ELDER:
		return "老年卡";
		break;
	case EN_CARD_TYPE_NOMAL:
		return "普通卡";
		break;
	case EN_CARD_TYPE_BUTT:
		return "卡卡";
		break;
	default:
		return NULL;
			break;
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
    

    return EN_RETURN_SUCC;
}