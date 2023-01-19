/* Project: c:\users\green\desktop\ordonancement-m2\partie1\cellprod\cellprod.rdp */
/* Diagram: c:\Users\green\Desktop\ordonancement-m2\partie1\CellProd\CellProd.rdd */

#include "RTDS_MACRO.h"
#include "RTDS_CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DEFINES FOR STATES */
#define RTDS_state_attConfUsinage 1
#define RTDS_state_attRetConf 2
#define RTDS_state_DefaillanceRobotAlim 3
#define RTDS_state_attConv 4
#define RTDS_state_attConvoyeur 5
#define RTDS_state_DefaillanceRetraitRobot 6
#define RTDS_state_ConvOccupe 7
#define RTDS_state_attDepotAlim 8
#define RTDS_state_att 9
#define RTDS_state_attConfDep 10
#define RTDS_state_attReponseConv 11
#define RTDS_state_Idle 12
#define RTDS_state_Defaillance 13
#define RTDS_state_attRemiseConf 14
#define RTDS_state_DefaillanceRetraitMachine 15
#define RTDS_state_DEfaillanceRobotRetrait 16
#define RTDS_state_attDepot 17
#define RTDS_state_attFinUsinage 18

/* DEFINES FOR SIGNALS AND TIMERS */
char * RTDS_get_message_name(char * name, int id);
#define RTDS_message_libererConv 1
#define RTDS_message_depose 2
#define RTDS_message_depotConf 3
#define RTDS_message_depotFini 4
#define RTDS_message_usinageReq 5
#define RTDS_message_pieceArv 6
#define RTDS_message_retP 7
#define RTDS_message_retraitReq 8
#define RTDS_message_Libre 9
#define RTDS_message_retraitConf 10
#define RTDS_message_reveil 11
#define RTDS_message_remiseReq 12
#define RTDS_message_machineEnPanne 13
#define RTDS_message_finUsinage 14
#define RTDS_message_remiseConf 15
#define RTDS_message_usinageConf 16
#define RTDS_message_depotReq 17
#define RTDS_message_defaillRobotRet 18
#define RTDS_message_convLibre 19
#define RTDS_message_defaillance 20
#define RTDS_message_convLibreM 21
#define RTDS_message_piece 22
#define RTDS_message_attenteDepot 23
#define RTDS_message_defaillRetrait 24

/* DEFINES FOR SEMAPHORES */

/* DEFINES FOR PROCESSES */
#define RTDS_process_Th_Robot_Alim 1
#define RTDS_process_Th_Piece 2
#define RTDS_process_gestionConvoyeur 3
#define RTDS_process_Th_Dialogue 4
#define RTDS_process_Th_Machine 5
#define RTDS_process_Th_Robot_Ret 6

/* PROCESS PROTOTYPES */
RTDS_TASK_ENTRY_POINT_PROTO(Th_Robot_Alim);
RTDS_TASK_ENTRY_POINT_PROTO(Th_Piece);
RTDS_TASK_ENTRY_POINT_PROTO(gestionConvoyeur);
RTDS_TASK_ENTRY_POINT_PROTO(Th_Dialogue);
RTDS_TASK_ENTRY_POINT_PROTO(Th_Machine);
RTDS_TASK_ENTRY_POINT_PROTO(Th_Robot_Ret);

#ifdef __cplusplus
}
#endif

