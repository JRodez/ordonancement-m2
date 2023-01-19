#ifndef _RTDS_MESSAGES_H_
#define _RTDS_MESSAGES_H_

#include "RTDS_CommonTypes.h"
#include "CellProd.h"

#ifdef __cplusplus
extern "C" {
#endif


/* DATA TYPES FOR MESSAGES */
#ifndef RTDS_pieceArv_DATA_DEFINED
typedef struct RTDS_pieceArv_data
{
	RTDS_PID	param1;
} RTDS_pieceArv_data;
#define RTDS_pieceArv_DATA_DEFINED
#endif

#ifndef RTDS_piece_DATA_DEFINED
typedef struct RTDS_piece_data
{
	int	param1;
} RTDS_piece_data;
#define RTDS_piece_DATA_DEFINED
#endif


/* MACRO FOR DECLARATIONS FOR MESSAGE SEND/RECEIVE */

#ifndef RTDS_MSG_DATA_DECL
#define RTDS_MSG_DATA_DECL unsigned char * RTDS_msgData;
#endif  /* RTDS_MSG_DATA_DECL defined */


/* MACRO FOR RECEPTION OF MESSAGE piece */

#ifndef RTDS_MSG_RECEIVE_piece
#define RTDS_MSG_RECEIVE_piece(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		RTDS_PARAM1 = ((RTDS_piece_data*)(RTDS_currentContext->currentMessage->pData))->param1; \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_piece defined */


/* MACRO FOR SENDING MESSAGE piece TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_piece_TO_NAME
#define RTDS_MSG_SEND_piece_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_piece_data)); \
	((RTDS_piece_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_piece, sizeof(RTDS_piece_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_piece_TO_NAME defined */


/* MACRO FOR SENDING MESSAGE piece TO A PROCESS ALL_NAME */

#ifndef RTDS_MSG_SEND_piece_TO_ALL_NAME
#define RTDS_MSG_SEND_piece_TO_ALL_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_piece_data)); \
	((RTDS_piece_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ALL_NAME(RTDS_message_piece, sizeof(RTDS_piece_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_piece_TO_ALL_NAME defined */


/* MACRO FOR SENDING MESSAGE piece TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_piece_TO_ID
#define RTDS_MSG_SEND_piece_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_piece_data)); \
	((RTDS_piece_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_piece, sizeof(RTDS_piece_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_piece_TO_ID defined */


/* MACROS FOR SENDING MESSAGE piece TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_piece_TO_ENV
#define RTDS_MSG_SEND_piece_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_piece_data)); \
	((RTDS_piece_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_piece, sizeof(RTDS_piece_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_piece_TO_ENV defined */


#ifndef RTDS_MSG_SEND_piece_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_piece_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_piece_data)); \
	((RTDS_piece_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	MACRO_NAME(RTDS_message_piece, sizeof(RTDS_piece_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_piece_TO_ENV defined */


/* MACRO FOR RECEPTION OF MESSAGE pieceArv */

#ifndef RTDS_MSG_RECEIVE_pieceArv
#define RTDS_MSG_RECEIVE_pieceArv(RTDS_PARAM1) \
	{ \
	if ( RTDS_currentContext->currentMessage->pData != NULL ) \
		{ \
		RTDS_PARAM1 = ((RTDS_pieceArv_data*)(RTDS_currentContext->currentMessage->pData))->param1; \
		} \
	else \
		{ \
		RTDS_MSG_INPUT_ERROR; \
		} \
	}
#endif /* RTDS_MSG_RECEIVE_pieceArv defined */


/* MACRO FOR SENDING MESSAGE pieceArv TO A PROCESS NAME */

#ifndef RTDS_MSG_SEND_pieceArv_TO_NAME
#define RTDS_MSG_SEND_pieceArv_TO_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_pieceArv_data)); \
	((RTDS_pieceArv_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_pieceArv, sizeof(RTDS_pieceArv_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_pieceArv_TO_NAME defined */


/* MACRO FOR SENDING MESSAGE pieceArv TO A PROCESS ALL_NAME */

#ifndef RTDS_MSG_SEND_pieceArv_TO_ALL_NAME
#define RTDS_MSG_SEND_pieceArv_TO_ALL_NAME(RECEIVER, RECEIVER_NUMBER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_pieceArv_data)); \
	((RTDS_pieceArv_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ALL_NAME(RTDS_message_pieceArv, sizeof(RTDS_pieceArv_data), RTDS_msgData, RECEIVER, RECEIVER_NUMBER); \
	}
#endif /* RTDS_MSG_SEND_pieceArv_TO_ALL_NAME defined */


/* MACRO FOR SENDING MESSAGE pieceArv TO A PROCESS ID */

#ifndef RTDS_MSG_SEND_pieceArv_TO_ID
#define RTDS_MSG_SEND_pieceArv_TO_ID(RECEIVER, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_pieceArv_data)); \
	((RTDS_pieceArv_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_pieceArv, sizeof(RTDS_pieceArv_data), RTDS_msgData, RECEIVER); \
	}
#endif /* RTDS_MSG_SEND_pieceArv_TO_ID defined */


/* MACROS FOR SENDING MESSAGE pieceArv TO ENVIRONMENT */

#ifndef RTDS_MSG_SEND_pieceArv_TO_ENV
#define RTDS_MSG_SEND_pieceArv_TO_ENV(RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_pieceArv_data)); \
	((RTDS_pieceArv_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	RTDS_MSG_QUEUE_SEND_TO_ENV(RTDS_message_pieceArv, sizeof(RTDS_pieceArv_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_pieceArv_TO_ENV defined */


#ifndef RTDS_MSG_SEND_pieceArv_TO_ENV_W_MACRO
#define RTDS_MSG_SEND_pieceArv_TO_ENV_W_MACRO(MACRO_NAME, RTDS_PARAM1) \
	{ \
	RTDS_msgData = (unsigned char *)RTDS_MALLOC(sizeof(RTDS_pieceArv_data)); \
	((RTDS_pieceArv_data*)RTDS_msgData)->param1 = RTDS_PARAM1; \
	MACRO_NAME(RTDS_message_pieceArv, sizeof(RTDS_pieceArv_data), RTDS_msgData); \
	}
#endif /* RTDS_MSG_SEND_pieceArv_TO_ENV defined */


#ifdef __cplusplus
}
#endif

#endif /* defined(_RTDS_MESSAGES_H_) */

