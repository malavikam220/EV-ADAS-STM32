#ifndef FAULT_H
#define FAULT_H

#include "common.h"
#include "ev_control.h"
#include "adas.h"

/* Fault flag bits */
#define FAULT_NONE  0x00
#define FAULT_OT    0x01   /* motor over-temperature  */
#define FAULT_SOC   0x02   /* battery critically low  */
#define FAULT_COL   0x04   /* collision critical       */

typedef struct {
    uint8_t flags;         /* active fault bitmask    */
    uint8_t active;        /* 1 = system in fault state */
} Fault_HandleTypeDef;

void Fault_Init  (Fault_HandleTypeDef *flt);
void Fault_Check (Fault_HandleTypeDef *flt,
                  EV_HandleTypeDef    *ev,
                  ADAS_HandleTypeDef  *adas);
void Fault_Clear (Fault_HandleTypeDef *flt,
                  EV_HandleTypeDef    *ev);

#endif
