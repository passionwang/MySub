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
@ 查询地铁线
@ 入参：unCmd, 命令内容
@ 出参: returnStr
@ 返回值: 无
*/
void ProcQueryLineCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH])
{
	string res="";
	GetLineInfo(res);
	memcpy(returnStr,res.c_str(),MAX_SEND_BUFFER_LENGTH);
    //查询所有地铁线 GetLineInfo
    return;
}