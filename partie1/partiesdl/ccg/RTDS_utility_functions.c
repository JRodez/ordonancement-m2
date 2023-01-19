#include <limits.h>

#include "RTDS_Common.h"
#include "RTDS_CommonTypes.h"

#include "RTDS_gen.h"
#include "CellProd.h"
char * RTDS_get_message_name(RTDS_String name, int id)
  {
  switch (id)
    {
    default :
    RTDS_StringAssign(name,"noType");
    break;
    }
return name;
  }


int RTDS_machinesArray_cmp(machinesArray v1, machinesArray v2)
  {
  int cmp;
  int i;
  for(i = 0; i < (RTDS_INT_MAX - RTDS_INT_MIN); i++)
    {
    cmp = (int)((v1[i]) - (v2[i]));
    if ( ((v1[i]) != (v2[i])) && (cmp == 0) ) { cmp = (((v1[i]) < (v2[i])) ? -1 : 1); }
    if (cmp != 0) return cmp;
    }
  return 0;
  }
