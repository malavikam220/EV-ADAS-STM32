#include "adas.h"
#include "ultrasonic.h"

/* ── Hysteresis helper ───────────────────────────────────────────── */
/* Returns 1 if alarm is active, 0 if cleared after hysteresis       */
static uint8_t hyst_check(uint8_t *cnt, uint8_t condition)
{
    if (condition)
    {
        *cnt = ADAS_HYSTERESIS_CNT;
        return 1;
    }

    if (*cnt > 0)
    {
        (*cnt)--;
        return 1;
    }

    return 0;
}
/* ── ADAS_Init ───────────────────────────────────────────────────── */
void ADAS_Init(ADAS_HandleTypeDef *adas)
{
    memset(adas, 0, sizeof(*adas));
    adas->front_cm = 400.0f;				//variables initialized with maximum values which will be updated later
    adas->left_cm  = 400.0f;
    adas->right_cm = 400.0f;
    adas->ttc_sec  = 99.9f;
}

/* ── ADAS_Update — call after HCSR04_ReadAll() ───────────────────── */
void ADAS_Update(ADAS_HandleTypeDef *adas, EV_HandleTypeDef *ev)
{
    /* Step 1: Get distances from cache */
    adas->front_cm = HCSR04_GetDistance(HCSR04_FRONT);
    adas->left_cm  = HCSR04_GetDistance(HCSR04_LEFT);
    adas->right_cm = HCSR04_GetDistance(HCSR04_RIGHT);

    /* Step 2: TTC = distance(m) / speed(m/s) */
    float speed_ms = ev->speed_kmh / 3.6f;
    float front_m  = adas->front_cm / 100.0f;		// convert dist in cm to m
    if (speed_ms > 0.5f && adas->front_cm < 200.0f) {
        adas->ttc_sec = front_m / speed_ms;
        adas->ttc_sec = CLAMP(adas->ttc_sec, 0.0f, 99.9f);
    } else {
        adas->ttc_sec = 99.9f;   /* no obstacle or stationary → safe */
    }

    /* Step 3: Forward Collision Warning */
    uint8_t fcw_crit = (adas->front_cm < ADAS_FCW_CRIT_CM)
                     || (adas->ttc_sec  < ADAS_TTC_CRIT_S);

    uint8_t fcw_warn = (adas->front_cm < ADAS_FCW_WARN_CM)
                     || (adas->ttc_sec  < ADAS_TTC_WARN_S);

    if (hyst_check(&adas->hyst_fcw_crit, fcw_crit)) {	// hystersis check (to validate alarm by checking if it true three times)
        adas->hyst_fcw_warn = 0;        // reset warn counter when crit fires
        adas->collision_warn = 2;
    } else if (hyst_check(&adas->hyst_fcw_warn, fcw_warn)) {
        adas->collision_warn = 1;
    } else {
        adas->collision_warn = 0;
    }

    /* Step 4: Blind Spot Detection */
    uint8_t bsd_l = (adas->left_cm  < ADAS_BSD_DIST_CM)
                  && (ev->speed_kmh  > ADAS_BSD_SPEED_KMH);		// if speed of vehicle more than 20kmh and distance less than 30cm
    uint8_t bsd_r = (adas->right_cm < ADAS_BSD_DIST_CM)
                  && (ev->speed_kmh  > ADAS_BSD_SPEED_KMH);

    adas->blindspot_left  = hyst_check(&adas->hyst_bsd_l, bsd_l);
    adas->blindspot_right = hyst_check(&adas->hyst_bsd_r, bsd_r);

    /* Step 5: Overspeed */
    adas->overspeed = hyst_check(&adas->hyst_over,
                       ev->speed_kmh > ADAS_OVERSPEED_KMH);



    /* Step 7: Overall alarm priority */
    if      (adas->collision_warn == 2) adas->alarm_priority = ALARM_CRITICAL;
    else if (adas->collision_warn == 1) adas->alarm_priority = ALARM_WARNING;
    else if (adas->blindspot_left
          || adas->blindspot_right
          || adas->overspeed)           adas->alarm_priority = ALARM_ADVISORY;
    else                                adas->alarm_priority = ALARM_NONE;

    /* Step 8: Drive LEDs */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8,   /* LED_COLLISION */
        (adas->collision_warn > 0) ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_9,   /* LED_BLINDSPOT_L */
        adas->blindspot_left  ? GPIO_PIN_SET : GPIO_PIN_RESET);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10,  /* LED_BLINDSPOT_R */
        adas->blindspot_right ? GPIO_PIN_SET : GPIO_PIN_RESET);
}
