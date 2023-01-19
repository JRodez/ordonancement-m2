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

#include "gestionConvoyeur.h"
#include "RTDS_messages.h"
#include "RTDS_gen.h"

#define RTDS_PROCESS_NUMBER RTDS_process_gestionConvoyeur
#define RTDS_PROCESS_NAME gestionConvoyeur

/*
** PROCESS gestionConvoyeur:
** -------------------------
*/

RTDS_TASK_ENTRY_POINT(gestionConvoyeur)
  {
  short RTDS_transitionExecuted;
  int RTDS_savedSdlState = 0;

  RTDS_BOOLEAN panne = FALSE;
  RTDS_BOOLEAN panne2 = FALSE;
  RTDS_BOOLEAN panne3 = FALSE;
  RTDS_PID robot = NULL;
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


  #include "gestionConvoyeur_tempVars.h"

  RTDS_myLocals[0] = (void*)&panne;
  RTDS_myLocals[1] = (void*)&panne2;
  RTDS_myLocals[2] = (void*)&panne3;
  RTDS_myLocals[3] = (void*)&robot;
  RTDS_localsStack[0] = RTDS_myLocals;


  /* Initial transition */
  RTDS_SDL_STATE_SET(RTDS_state_att);

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
        /* Transitions for state att */
        case RTDS_state_att:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state att - message convLibre */
            case RTDS_message_convLibre:
              panne = 1;

              if ( !(panne) )
                {
                RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_depose, 0, NULL, SENDER);
                RTDS_SDL_STATE_SET(RTDS_state_ConvOccupe);
                break;
                }
              else if ( panne )
                {
                RTDS_SDL_STATE_SET(RTDS_state_Defaillance);
                break;
                }
            /* Transition for state att - message libererConv */
            case RTDS_message_libererConv:
              libererM:
              panne2 = 1;

              if ( !(panne2) )
                {
                RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_Libre, 0, NULL, SENDER);
                RTDS_SDL_STATE_SET(RTDS_state_att);
                break;
                }
              else if ( panne2 )
                {
                RTDS_SDL_STATE_SET(RTDS_state_DefaillanceRetraitMachine);
                break;
                }
            /* Transition for state att - message retP */
            case RTDS_message_retP:
              libererP:
              panne3 = 1;

              if ( !(panne3) )
                {
                RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_Libre, 0, NULL, SENDER);
                RTDS_SDL_STATE_SET(RTDS_state_att);
                break;
                }
              else if ( panne3 )
                {
                RTDS_SDL_STATE_SET(RTDS_state_DefaillanceRetraitRobot);
                break;
                }
            /* Transition for state att - message convLibreM */
            case RTDS_message_convLibreM:
              RTDS_MSG_QUEUE_SEND_TO_ID(RTDS_message_depose, 0, NULL, SENDER);
              RTDS_SDL_STATE_SET(RTDS_state_ConvOccupe);
              break;
            default:
              RTDS_transitionExecuted = 0;
              break;
            } /* End of switch on message */
          break;
        /* Transitions for state ConvOccupe */
        case RTDS_state_ConvOccupe:
          switch(RTDS_currentContext->currentMessage->messageNumber)
            {
            /* Transition for state ConvOccupe - message libererConv */
            case RTDS_message_libererConv:
              goto libererM;
            /* Transition for state ConvOccupe - message convLibre */
            case RTDS_message_convLibre:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
              break;
            /* Transition for state ConvOccupe - message retP */
            case RTDS_message_retP:
              goto libererP;
            /* Transition for state ConvOccupe - message convLibreM */
            case RTDS_message_convLibreM:
              RTDS_MSG_SAVE(RTDS_currentContext->currentMessage);
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
