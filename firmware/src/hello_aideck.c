// 飞行代码
#define DEBUG_MODULE "AIDECK"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32fxxx.h"
#include "config.h"
#include "console.h"
#include "uart1.h"
#include "debug.h"
#include "deck.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "log.h"
#include "param.h"
#include "system.h"
#include "uart1.h"
#include "uart2.h"
#include "sleepus.h"

static void setHoverSetpoint(setpoint_t *setpoint, float vx, float vy, float z, float yawrate)
{
  setpoint->mode.z = modeAbs;
  setpoint->position.z = z;


  setpoint->mode.yaw = modeVelocity;
  setpoint->attitudeRate.yaw = yawrate;


  setpoint->mode.x = modeVelocity;
  setpoint->mode.y = modeVelocity;
  setpoint->velocity.x = vx;
  setpoint->velocity.y = vy;

  setpoint->velocity_body = true;
}

void appMain()
{
    // paramVarId_t Effect = paramGetVarId("ring", "effect");
    // paramSetInt(Effect, 7);
    static setpoint_t setpoint;
    
    uint8_t res = -1;
    // paramVarId_t red = paramGetVarId("ring", "solidRed");
    // paramVarId_t blue = paramGetVarId("ring", "solidBlue");
    // paramVarId_t green = paramGetVarId("ring", "solidGreen");
    
    while (1)
    {
        logVarId_t idYaw = logGetVarId("aideck","receivebyte");
        res = logGetInt(idYaw);
        if(res==1)
        {
            DEBUG_PRINT("fly!\n");
            setHoverSetpoint(&setpoint, 0, 0, 0.5, 0);
            commanderSetSetpoint(&setpoint, 3);
        }
        else if(res==2)
        {
            DEBUG_PRINT("land!\n");
            setHoverSetpoint(&setpoint, 0, 0, 0.2, 0);
            commanderSetSetpoint(&setpoint, 3);
            // setHoverSetpoint(&setpoint, 1, 1, 0.3, 0);
            // commanderSetSetpoint(&setpoint, 3);
        }
        else
        {
            // DEBUG_PRINT("zero!\n");
            // memset(&setpoint, 0, sizeof(setpoint_t));
            // setHoverSetpoint(&setpoint, 0, 0, 0.2, 0);
            // commanderSetSetpoint(&setpoint, 3);
        }
        // sleepus(2e6);
        // sleep(1000);
        // if(res==1)
        // {
        //     paramSetInt(red, 255);
        //     paramSetInt(blue, 0);
        //     paramSetInt(green, 0);
        // }
        // else if(res==2)
        // {
        //     paramSetInt(red, 0);
        //     paramSetInt(blue, 255);
        //     paramSetInt(green, 0);
        // }
        // else if(res==3)
        // {
        //     paramSetInt(red, 0);
        //     paramSetInt(blue, 0);
        //     paramSetInt(green, 255);
        // }
        // else
        // {
        //     paramSetInt(red, 20);
        //     paramSetInt(blue, 20);
        //     paramSetInt(green, 20);
        // }
    }
}

