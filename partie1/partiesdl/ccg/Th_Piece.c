/* ***************************************************************** */
/* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Include.c begins       */
/* PragmaDev RTDS win32 integration                                  */

/* Include unistd when using a unix based system or cygwin */
#ifdef __CYGWIN__
#include <unistd.h>
#else
#include <stdlib.h>
#endif

#include <stdio.h>
#include <time.h>

#include "RTDS_MACRO.h"

#if defined( RTDS_FORMAT_TRACE )
#include "RTDS_FormatTrace.h"
#endif

/* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Include.c ends         */
/* ***************************************************************** */

#include "Th_Piece.h"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_Th_Piece
#define RTDS_PROCESS_NAME Th_Piece

/*
** PROCESS Th_Piece:
** -----------------
*/

RTDS_TASK_ENTRY_POINT(Th_Piece)
  {
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  RTDS_PID idMachine = NULL;
  RTDS_MSG_DATA_DECL

  void * RTDS_myLocals[1];
  void ** RTDS_localsStack[1];


  /* ***************************************************************** */
  /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Process_begin.c begins */
  /* PragmaDev RTDS win32 integration                                  */

  int RTDS_sdlStatePrev = 0;
  RTDS_TimerState * RTDS_timer;
  RTDS_TimerState * RTDS_prevTimer;
  RTDS_SdlInstanceId * RTDS_senderId = NULL;

  RTDS_currentContext->readSaveQueue = NULL;
  RTDS_currentContext->writeSaveQueue = NULL;

  /* Synchronize processes at startup time */
  RTDS_START_SYNCHRO_WAIT;

  /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Process_begin.c ends */
  /* *************************************************************** */


  #include "Th_Piece_tempVars.h"

  RTDS_myLocals[0] = (void*)&idMachine;
  RTDS_localsStack[0] = RTDS_myLocals;


  /* Initial transition */
  RTDS_SDL_STATE_SET(RTDS_state_Idle);

  /* ****************************************************************** */
  /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_loopStart.c begins */
  /* PragmaDev RTDS win32 integration                                   */

  /* Event loop */
  for ( ; ; )
    {

    /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_loopStart.c ends */
    /* *************************************************************** */

    /* *************************************************************** */
    /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_middle.c begins */
    /* PragmaDev RTDS win32 integration                                */

    /* Check saved messages */
    if ( RTDS_currentContext->readSaveQueue != NULL )
      {
      RTDS_currentContext->currentMessage = RTDS_currentContext->readSaveQueue;
      RTDS_currentContext->readSaveQueue = RTDS_currentContext->readSaveQueue->next;
      }
    /* If no saved messages left, get message from process's message queue */
    else
      {
      RTDS_currentContext->currentMessage = ( RTDS_MessageHeader * )RTDS_MALLOC( sizeof( RTDS_MessageHeader ) );
      RTDS_MSG_QUEUE_READ( RTDS_currentContext->currentMessage );
      RTDS_currentContext->currentMessage->next = NULL;
      }

    /* Discard cancelled timers */
    if ( RTDS_currentContext->currentMessage->timerUniqueId != 0 )
      {
      RTDS_prevTimer = NULL;
      for ( RTDS_timer = RTDS_currentContext->timerList ;RTDS_timer != NULL; RTDS_timer = RTDS_timer->next )
        {
        /* If timer found and cancelled */
        if ( RTDS_timer->timerUniqueId == RTDS_currentContext->currentMessage->timerUniqueId )
          {
          if ( RTDS_timer->state == RTDS_TIMER_CANCELLED )
            {
            /* Discard current message */
            RTDS_FREE( RTDS_currentContext->currentMessage );
            RTDS_currentContext->currentMessage = NULL;
            /* Remove it from list of timers */
            if ( RTDS_prevTimer == NULL )
              {
              RTDS_currentContext->timerList = RTDS_currentContext->timerList->next;
              }
            else
              {
              RTDS_prevTimer->next = RTDS_timer->next;
              }
            CloseHandle(RTDS_timer->watchDogId);
            RTDS_FREE( RTDS_timer );
            }
          break;
          }
        RTDS_prevTimer = RTDS_timer;
        }
      /* If the timer could not be found in the list. Consider it as cancelled and discard current message */
      if ( RTDS_timer == NULL )
        {
        RTDS_FREE( RTDS_currentContext->currentMessage );
        RTDS_currentContext->currentMessage = NULL;
        }
      }

    /* Let's process the message ! */
    if ( RTDS_currentContext->currentMessage != NULL )
      {
      RTDS_SIMULATOR_TRACE( RTDS_messageReceived, RTDS_currentContext->currentMessage, SELF, RTDS_currentContext );
      RTDS_senderId = RTDS_currentContext->currentMessage->sender;
      RTDS_sdlStatePrev = RTDS_currentContext->sdlState;
      /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_middle.c ends */
      /* ************************************************************* */

      /* Double switch state / signal */
      RTDS_transitionExecuted = 1;
      switch(RTDS_currentContext->sdlState)
        {
        /* Transitions for state attConfUsinage */
        case RTDS_state_attConfUsinage:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attConfUsinage - message usinageConf */
            case RTDS_message_usinageConf:
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_depotReq, 0, NULL, "Th_Robot_Alim", RTDS_process_Th_Robot_Alim);
              RTDS_SDL_STATE_SET(RTDS_state_attConfDep);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attRetConf */
        case RTDS_state_attRetConf:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attRetConf - message retraitConf */
            case RTDS_message_retraitConf:
              RTDS_PROCESS_KILL;
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attConfDep */
        case RTDS_state_attConfDep:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attConfDep - message depotConf */
            case RTDS_message_depotConf:
              RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_depotFini, 0, NULL,               idMachine);
              RTDS_SET_TIMER(RTDS_message_machineEnPanne, 1000 * (0 + 300));
              RTDS_SDL_STATE_SET(RTDS_state_attFinUsinage);
              break;
            /* Transition for state attConfDep - message defaillance */
            case RTDS_message_defaillance:
              RTDS_SDL_STATE_SET(RTDS_state_DefaillanceRobotAlim);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state Idle */
        case RTDS_state_Idle:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state Idle - message pieceArv */
            case RTDS_message_pieceArv:
              RTDS_MSG_RECEIVE_pieceArv(          idMachine);
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_usinageReq, 0, NULL, "Th_Machine", RTDS_process_Th_Machine);
              RTDS_SDL_STATE_SET(RTDS_state_attConfUsinage);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attRemiseConf */
        case RTDS_state_attRemiseConf:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attRemiseConf - message remiseConf */
            case RTDS_message_remiseConf:
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_retraitReq, 0, NULL, "Th_Robot_Ret", RTDS_process_Th_Robot_Ret);
              RTDS_SDL_STATE_SET(RTDS_state_attRetConf);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attFinUsinage */
        case RTDS_state_attFinUsinage:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attFinUsinage - message finUsinage */
            case RTDS_message_finUsinage:
              RTDS_RESET_TIMER(RTDS_message_machineEnPanne);
              RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_remiseReq, 0, NULL, SENDER);
              RTDS_SDL_STATE_SET(RTDS_state_attRemiseConf);
              break;
            /* Transition for state attFinUsinage - message machineEnPanne */
            case RTDS_message_machineEnPanne:
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_machineEnPanne, 0, NULL, "Th_Dialogue", RTDS_process_Th_Dialogue);
              RTDS_PROCESS_KILL;
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        default:
          RTDS_transitionExecuted = 0;
          break;
        } /* End of switch(RTDS_currentContext->sdlState) */
      /* ************************************************************ */
      /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_end.c begins */
      /* PragmaDev RTDS win32 integration                             */
      RTDS_TransitionCleanUp( RTDS_currentContext, RTDS_sdlStatePrev );
      } /* End of if ( RTDS_currentContext->currentMessage != NULL ) to execute transition */
    } /* End of for ( ; ; ) */

  /* $(RTDS_HOME)/share/ccg/windows/bricks/RTDS_Proc_end.c ends */
  /* ********************************************************** */
  }
