#include "fault.h"
#include "ultrasonic.h"

extern TIM_HandleTypeDef htim1;

void Fault_Init(Fault_HandleTypeDef *flt)
{
    flt->flags  = FAULT_NONE;
    flt->active = 0;
}

void Fault_Check(Fault_HandleTypeDef *flt,
                 EV_HandleTypeDef *ev,
                 ADAS_HandleTypeDef *adas)
{
    uint8_t new_flags = FAULT_NONE;

    if (ev->motor_temp >= EV_MAX_MOTOR_TEMP_C)
        new_flags |= FAULT_OT;

    if (ev->soc <= EV_FAULT_SOC_PCT)
        new_flags |= FAULT_SOC;

    if (adas->collision_warn == 2 && HCSR04_IsValid(HCSR04_FRONT))
        new_flags |= FAULT_COL;

    flt->flags = new_flags;

    if (flt->flags != FAULT_NONE)
    {
        flt->active = 1;
        ev->state    = STATE_FAULT;   // ← add this



        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_SET);	// yellow LED ON
    }
    else
    {
        flt->active = 0;
        ev->state =STATE_DRIVING;

        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);	// yellow LED OFF
    }
}

void Fault_Clear(Fault_HandleTypeDef *flt, EV_HandleTypeDef *ev)
{
    flt->flags  = FAULT_NONE;
    flt->active = 0;

    ev->state = STATE_PARKED;

    /* Reset EV to safe state */
    ev->speed_kmh   = 0.0f;
    ev->motor_torque = 0.0f;
    ev->motor_temp  = 25.0f;
    ev->soc         = 80.0f;

    /* Turn off fault LED */
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_11, GPIO_PIN_RESET);
}
