#ifndef ADAS_H
#define ADAS_H

#include "common.h"
#include "ev_control.h"

/* ── Alarm levels ────────────────────────────────────────────────── */
typedef enum {
    ALARM_NONE     = 0,
    ALARM_ADVISORY = 1,   /* blind spot / overspeed    */
    ALARM_WARNING  = 2,   /* collision < 50cm or TTC<3s */
    ALARM_CRITICAL = 3    /* collision < 20cm or TTC<1.5s */
} AlarmLevel_t;

/* ── Thresholds ──────────────────────────────────────────────────── */
#define ADAS_FCW_WARN_CM       50.0f   /* forward collision warning  */
#define ADAS_FCW_CRIT_CM       20.0f   /* forward collision critical */
#define ADAS_TTC_WARN_S         3.0f   /* TTC warning threshold      */
#define ADAS_TTC_CRIT_S         1.5f   /* TTC critical threshold     */
#define ADAS_BSD_DIST_CM       30.0f   /* blind spot distance        */
#define ADAS_BSD_SPEED_KMH     20.0f   /* blind spot speed gate      */
#define ADAS_PARK_SPEED_KMH    10.0f   /* parking assist gate        */
#define ADAS_OVERSPEED_KMH    120.0f   /* overspeed advisory         */
#define ADAS_HYSTERESIS_CNT     3U     /* samples before alarm clears */

/* ── ADAS Handle ─────────────────────────────────────────────────── */
typedef struct {					//variable declaration
    float        front_cm;
    float        left_cm;
    float        right_cm;
    float        ttc_sec;
    uint8_t      collision_warn;    /* 0=none 1=warning 2=critical */
    uint8_t      blindspot_left;
    uint8_t      blindspot_right;
    uint8_t      overspeed;
    uint8_t      parking_active;
    uint8_t      parking_score;     /* 0–100 proximity score       */
    AlarmLevel_t alarm_priority;
    /* hysteresis counters — prevent rapid toggling */
  //  uint8_t      hyst_fcw;
    uint8_t  hyst_fcw_crit;   // separate counter for critical threshold
    uint8_t  hyst_fcw_warn;   // separate counter for warning threshold
    uint8_t      hyst_bsd_l;
    uint8_t      hyst_bsd_r;
    uint8_t      hyst_over;
} ADAS_HandleTypeDef;

/* ── API ─────────────────────────────────────────────────────────── */
void ADAS_Init  (ADAS_HandleTypeDef *adas);
void ADAS_Update(ADAS_HandleTypeDef *adas, EV_HandleTypeDef *ev);

#endif

