#ifndef __SUBWAY_CARD_H__
#define __SUBWAY_CARD_H__
#include "subwayError.h"
#include "subwayGlobalDef.h"

//�������ϵͳ��100�ŵ�����
#define MAX_CARD_NUM 100
#define MAX_STATION_NAME_LENGTH 32//���ֳ���
#define MAX_HISTORY 20

//������ֵ
#define MAX_BALANCE 999

//����������
typedef enum
{
    EN_CARD_TYPE_SINGLE = 0,
    EN_CARD_TYPE_ELDER,
    EN_CARD_TYPE_NOMAL,
    EN_CARD_TYPE_BUTT
}EN_CARD_TYPE;

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

struct ST_SUBWAY_CARD
{
    EN_CARD_TYPE enCard;  //������
    unsigned int cardNo;  //����
    int usrFlag;          //���Ƿ�����
    unsigned int balance; //�����
};

/*
@ ��ʼ�����п���Ϣ
@ ����ֵ: ��
*/
void InitCardManagerInfo();

/*
@ ���������俨�źͿ���Ϣ
@ ��Σ�enCard,������; charge: ��ֵ
@ ����: cardNo, ����Ŀ���
@ ����ֵ: EN_RETURN_SUCC������ɹ�; EN_RETURN_CARD_OVERLOW, ����ʧ��;
*/
EN_RETURN_CODE AssignCard(unsigned int &cardNo, EN_CARD_TYPE enCard, unsigned int charge);

/*
@ ��ֵ
@ ��Σ�cardNo,����; recharge: ��ֵ
@ ����: ��
@ ����ֵ: EN_RETURN_SUCC���ɹ�; ����, ʧ��;
*/
EN_RETURN_CODE RechargeCard(unsigned int cardNo, unsigned int recharge);

/*
@ ��ȡ����Ϣ
@ ��Σ�cardNo,����; 
@ ����: balance: ���
        enCard:  ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, ʧ��;
*/
EN_RETURN_CODE GetCardInfo(unsigned int cardNo, unsigned int &balance, EN_CARD_TYPE &enCard);

/*
@ ���۷�
@ ��Σ�cardNo,����; enCard, ������; deductPrice, �۷�Ʊ��
@ ����: balance, �۷Ѻ�����;
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INVALID_CARD, EN_RETURN_BALANCE_NOT_ENOUGH, ʧ��;
*/
EN_RETURN_CODE DeductCard(unsigned int cardNo, EN_CARD_TYPE enCard, unsigned int deductPrice, unsigned int &balance);

/*
@ ���ݿ������ַ���, ʶ������
@ ��Σ�cardType,      �������ַ���; 
@ ����: enCard,        ������
@ ����ֵ: EN_RETURN_SUCC���ɹ�; EN_RETURN_INPUT_INVALID_CARDTYPE, ʧ��;
*/
EN_RETURN_CODE GetCardType(char cardType[], EN_CARD_TYPE &enCard);

/*
@ ɾ������Ϣ
@ ��Σ�cardNo,����; 
@ ����: ��
@ ����ֵ: 0���ɹ�; -1, ʧ��;
*/
int DeleteCard(unsigned int cardNo);

/*
@ ��ȡ�������ַ���
@ ��Σ�enCard,������; 
@ ����: ��
@ ����ֵ: �������ַ���������"��ͨ��";
*/
char* GetCardTypeStr(EN_CARD_TYPE enCard);

/*
@ ���õ���ʷ��¼
@ ��Σ�cardNo,��ID;
		enCard,������ 
		enterTime,��վʱ��
		exitTime,��վʱ��
		enterStation,��վվ��
		exitStation,��վվ��
		money,���ѽ��
@ ����: ��
@ ����ֵ: ��;
*/
void SetHistory(unsigned int cardNo,
				EN_CARD_TYPE enCard,
				ST_SUBWAY_TIME enterTime,
				ST_SUBWAY_TIME exitTime,
				char enterStation[MAX_STATION_NAME_LENGTH],
				char exitStation[MAX_STATION_NAME_LENGTH],
				unsigned int money);

/*
@ ��ȡ������ʷ��¼
@ ��Σ�cardNo,��ID; 
@ ����: str,ƥ����ַ���
@ ����ֵ: ��;
*/
void GetHistory(int cardNo,HistoryNode History[MAX_HISTORY],int& HistoryIndex,int& HistoryNowHave);

#endif