#ifndef __CMD_QUERY_HISTORY_PROC_H__
#define __CMD_QUERY_HISTORY_PROC_H__
#include "subwayGlobalDef.h"
#include "subwayCmdParse.h"

/*
@ ��ѯ��ʷ����
@ ��Σ�stCmdDeduct, ��������
@ ����: returnStr
@ ����ֵ: void
*/
void ProcQueryHisCmd(UN_CMD &unCmd, char returnStr[MAX_SEND_BUFFER_LENGTH]);

#endif