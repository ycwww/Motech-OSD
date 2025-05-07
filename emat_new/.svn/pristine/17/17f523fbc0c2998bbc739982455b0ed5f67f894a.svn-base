#include "sendCmd.h"
#include <stdlib.h>
#include "stdio.h"
#include "windows.h"
#include <qdebug.h>
//#GETTHK%%%%%

char* sendCmd::getSendCommand(SEND_COMMAND_NUMBER_E commandNum, INT8* param, int paramLen)
{
	const INT8 setParamHead[4] = { 0x23, 0x53, 0x45, 0x54 };
	const INT8 setParamtail[4] = { 0x24, 0x25, 0x25, 0x25 };
	const INT8 celiHead[10] = { 0x23, 0x4F, 0x4E, 0x45, 0x4B, 0x45, 0x59, 0x42, 0x44, 0x25 };

	memset(sendCommandList, 0, sizeof(sendCommandList));
	switch (commandNum)
	{
	case SEND_COMMAND_GET_ALL_PARAM:
		//INT8 tmp[COMMAND_LENGTH + 1] = ;//{ 23, 47, 45, 54, 30 , 30, 24, 25, 25, 25, 25, 25 };
		memcpy_s(sendCommandList, sizeof(sendCommandList), "#GET00$%%%%%", strnlen_s("#GET00$%%%%%", COMMAND_LENGTH));
		return (char*)sendCommandList;
		break;
	case SEND_COMMAND_SEND_PARAM:
		if (NULL == param && 4 != paramLen)
		{
			printf("[error] param is wrong\n");
			return NULL;
		}
		memcpy_s(sendCommandList, sizeof(sendCommandList), setParamHead, sizeof(setParamHead));
		memcpy_s(&sendCommandList[sizeof(setParamHead)], sizeof(sendCommandList), param, paramLen);
		memcpy_s(&sendCommandList[sizeof(setParamHead) + paramLen], sizeof(sendCommandList), setParamtail, sizeof(setParamtail));
		break;
	case SEND_COMMAND_READ_WAVE:

		memcpy_s(sendCommandList, sizeof(sendCommandList), "#RST$%%%%%%%",
			strnlen_s("#RST$%%%%%%%", COMMAND_LENGTH));
		break;
	case SEND_COMMAND_CELIBRATE:
		if (NULL == param && 2 != paramLen)
		{
			printf("[error] param is wrong\n");
			return NULL;
		}

		memcpy_s(sendCommandList, sizeof(sendCommandList), celiHead, sizeof(celiHead));
		memcpy_s(&sendCommandList[sizeof(celiHead)], sizeof(sendCommandList), param, paramLen);
		break;
	case SEND_COMMAND_GET_THICK:
		memcpy_s(sendCommandList, sizeof(sendCommandList), "#GETTHK%%%%%", strnlen_s("#GETTHK%%%%%", COMMAND_LENGTH));
		break;
	case SEND_COMMAND_STOP_THICK:
		memcpy_s(sendCommandList, sizeof(sendCommandList), "#STOTHK%%%%%", strnlen_s("#STOTHK%%%%%", COMMAND_LENGTH));
		break;
	case SEND_COMMAND_ELECTRIC_QT:
		memcpy_s(sendCommandList, sizeof(sendCommandList), "#GETBAT%%%%%", strnlen_s("#GETBAT%%%%%", COMMAND_LENGTH));
		break;
	default:
		return NULL;
		break;
	}
	return (char*)sendCommandList;
}
