#include "stdafx.h"
#include "subwayGlobalDef.h"
#include "subwayMacro.h"
#include "include/basePrice.h"
#include "include/deductPrice.h"
#include "subwayPrice.h"
#include <iostream>
using namespace std;

/*
@ ��ȡ�۷�Ʊ�ۣ��������;
@   1. �����Ϊ0����ʱ���շ�;
@   2. �������Ϊ0;
@ ����ֵ: 
*/
EN_RETURN_CODE GetDeductPrice(EN_CARD_TYPE enCardType, unsigned int balance, unsigned int meters, ST_SUBWAY_TIME &enterTime, ST_SUBWAY_TIME &exitTime, unsigned int &deductPrice)
{
    //�����Ϊ0��ͬվ������
	if(meters == 0){
		//С��30����
		if((exitTime.hour - enterTime.hour) * 60 + (exitTime.minutes - enterTime.minutes) <= 30){
			if(EN_CARD_TYPE_SINGLE == enCardType){
				deductPrice = balance;
			}else{
				deductPrice = 0;
			}
		}else{
			if(EN_CARD_TYPE_SINGLE == enCardType){
				deductPrice = balance > 3 ? balance : 3;
			}else{
				deductPrice = 3;
			}
		}
	}else{
		deductPrice = GetBasePrice(meters);
		if(EN_CARD_TYPE_NOMAL == enCardType){
			;
		}else if(EN_CARD_TYPE_ELDER == enCardType){
			if(enterTime.hour >= 10 && enterTime.hour < 15){
				deductPrice = (int)(deductPrice * 0.8);
			}
		}else if(EN_CARD_TYPE_SINGLE == enCardType){
			deductPrice = deductPrice > balance ? deductPrice : balance;
		}
	}
    return EN_RETURN_SUCC;
}

