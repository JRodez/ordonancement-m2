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

#include "Th_Machine.h"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_Th_Machine
#define RTDS_PROCESS_NAME Th_Machine

/*
** PROCESS Th_Machine:
** -------------------
*/

RTDS_TASK_ENTRY_POINT(Th_Machine)
  {
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  int index = 0;
  RTDS_PID idP = NULL;
  RTDS_BOOLEAN panne = FALSE;
  RTDS_BOOLEAN panne2 = FALSE;
  RTDS_MSG_DATA_DECL

  void * RTDS_myLocals[4];
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


  #include "Th_Machine_tempVars.h"

  RTDS_myLocals[0] = (void*)&idP;
  RTDS_myLocals[1] = (void*)&index;
  RTDS_myLocals[2] = (void*)&panne;
  RTDS_myLocals[3] = (void*)&panne2;
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
        /* Transitions for state attDepot */
        case RTDS_state_attDepot:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attDepot - message remiseReq */
            case RTDS_message_remiseReq:
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_convLibreM, 0, NULL, "gestionConvoyeur", RTDS_process_gestionConvoyeur);
              RTDS_SDL_STATE_SET(RTDS_state_attReponseConv);
              break;
            /* Transition for state attDepot - message usinageReq */
            case RTDS_message_usinageReq:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attConv */
        case RTDS_state_attConv:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attConv - message Libre */
            case RTDS_message_Libre:
              RTDS_RESET_TIMER(RTDS_message_defaillRetrait);
              panne = 1;

              if ( !(panne) )
                {
                RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_finUsinage, 0, NULL,                 idP);
                RTDS_SDL_STATE_SET(RTDS_state_attDepot);
                break;
                }
              else if ( panne )
                {
                RTDS_PROCESS_KILL;
                break;
                }
            /* Transition for state attConv - message usinageReq */
            case RTDS_message_usinageReq:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
              break;
            /* Transition for state attConv - message defaillRetrait */
            case RTDS_message_defaillRetrait:
              RTDS_SDL_STATE_SET(RTDS_state_DefaillanceRetraitMachine);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attDepotAlim */
        case RTDS_state_attDepotAlim:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attDepotAlim - message depotFini */
            case RTDS_message_depotFini:
              RTDS_SET_TIMER(RTDS_message_defaillRetrait, 1000 * (0 + 20));
              RTDS_MSG_QUEUE_SEND_TO_NAME(RTDS_message_libererConv, 0, NULL, "gestionConvoyeur", RTDS_process_gestionConvoyeur);
              RTDS_SDL_STATE_SET(RTDS_state_attConv);
              break;
            /* Transition for state attDepotAlim - message usinageReq */
            case RTDS_message_usinageReq:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state attReponseConv */
        case RTDS_state_attReponseConv:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state attReponseConv - message depose */
            case RTDS_message_depose:
              RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_remiseConf, 0, NULL,               idP);
              RTDS_SDL_STATE_SET(RTDS_state_Idle);
              break;
            /* Transition for state attReponseConv - message usinageReq */
            case RTDS_message_usinageReq:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
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
            /* Transition for state Idle - message usinageReq */
            case RTDS_message_usinageReq:
              idP = SENDER;

              RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_usinageConf, 0, NULL,               idP);
              RTDS_SDL_STATE_SET(RTDS_state_attDepotAlim);
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
