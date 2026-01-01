/*
 * FreeRTOS Kernel <DEVELOPMENT BRANCH>
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * https://www.FreeRTOS.org
 * https://github.com/FreeRTOS
 *
 */

/*******************************************************************************
 * This file provides an example FreeRTOSConfig.h header file, inclusive of an
 * abbreviated explanation of each configuration item.  Online and reference
 * documentation provides more information.
 * https://www.freertos.org/a00110.html
 *
 * Constant values enclosed in square brackets ('[' and ']') must be completed
 * before this file will build.
 *
 * Use the FreeRTOSConfig.h supplied with the RTOS port in use rather than this
 * generic file, if one is available.
 ******************************************************************************/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/******************************************************************************/
/* Hardware description related definitions. **********************************/
/******************************************************************************/

/* The default clock speed for the RP2040 is 125MHz. */
#define configCPU_CLOCK_HZ                         ( 125000000 )

#define configSYSTICK_CLOCK_HZ                     ( ( TickType_t ) 1000000 )

/******************************************************************************/
/* Scheduling behaviour related definitions. **********************************/
/******************************************************************************/

/* Tick rate in Hz. 1000Hz means a 1ms tick. */
#define configTICK_RATE_HZ                         ( ( TickType_t ) 1000 )

/* Set configUSE_PREEMPTION to 1 to use pre-emptive scheduling.  Set
 * configUSE_PREEMPTION to 0 to use co-operative scheduling.
 * See https://www.freertos.org/single-core-amp-smp-rtos-scheduling.html. */
#define configUSE_PREEMPTION                       1

/* Set configUSE_TIME_SLICING to 1 to have the scheduler switch between Ready
 * state tasks of equal priority on every tick interrupt.  Set
 * configUSE_TIME_SLICING to 0 to prevent the scheduler switching between Ready
 * state tasks just because there was a tick interrupt.  See
 * https://freertos.org/single-core-amp-smp-rtos-scheduling.html. */
#define configUSE_TIME_SLICING                     0

/* Set configUSE_PORT_OPTIMISED_TASK_SELECTION to 1 to select the next task to
 * run using an algorithm optimised to the instruction set of the target
 * hardware - normally using a count leading zeros assembly instruction.  Set to
 * 0 to select the next task to run using a generic C algorithm that works for
 * all FreeRTOS ports.  Not all FreeRTOS ports have this option.  Defaults to 0
 * if left undefined. */
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    0

/* Set configUSE_TICKLESS_IDLE to 1 to use the low power tickless mode.  Set to
 * 0 to keep the tick interrupt running at all times.  Not all FreeRTOS ports
 * support tickless mode. See
 * https://www.freertos.org/low-power-tickless-rtos.html Defaults to 0 if left
 * undefined. */
#define configUSE_TICKLESS_IDLE                    0
#define configMAX_PRIORITIES                       10
/* Stack size for the idle task in words. */
#define configMINIMAL_STACK_SIZE                   256
#define configMAX_TASK_NAME_LEN                    16
#define configTICK_TYPE_WIDTH_IN_BITS              TICK_TYPE_WIDTH_32_BITS
#define configIDLE_SHOULD_YIELD                    1
#define configTASK_NOTIFICATION_ARRAY_ENTRIES      1
#define configQUEUE_REGISTRY_SIZE                  0
#define configENABLE_BACKWARD_COMPATIBILITY        0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    5
#define configUSE_MINI_LIST_ITEM                   1
#define configSTACK_DEPTH_TYPE                     uint32_t
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t
#define configHEAP_CLEAR_MEMORY_ON_FREE            1
#define configSTATS_BUFFER_MAX_LENGTH              0xFFFF
/* Enable newlib reentrancy for thread-safe C library calls. */
#define configUSE_NEWLIB_REENTRANT                 1

/******************************************************************************/
/* Software timer related definitions. ****************************************/
/******************************************************************************/

#define configUSE_TIMERS                           1
#define configTIMER_TASK_PRIORITY                  ( configMAX_PRIORITIES - 1 )
#define configTIMER_TASK_STACK_DEPTH               configMINIMAL_STACK_SIZE
#define configTIMER_QUEUE_LENGTH                   10

/******************************************************************************/
/* Event Group related definitions. *******************************************/
/******************************************************************************/

#define configUSE_EVENT_GROUPS                     1

/******************************************************************************/
/* Stream Buffer related definitions. *****************************************/
/******************************************************************************/

#define configUSE_STREAM_BUFFERS                   1

/******************************************************************************/
/* Memory allocation related definitions. *************************************/
/******************************************************************************/

#define configSUPPORT_STATIC_ALLOCATION              1
#define configSUPPORT_DYNAMIC_ALLOCATION             1
/* Total heap size for FreeRTOS. RP2040 has 264KB of SRAM. */
#define configTOTAL_HEAP_SIZE                        ( ( size_t ) ( 64 * 1024 ) )
#define configAPPLICATION_ALLOCATED_HEAP             0
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP    0
#define configENABLE_HEAP_PROTECTOR                  0

/******************************************************************************/
/* Interrupt nesting behaviour configuration. *********************************/ 
/******************************************************************************/

/* The RP2040 is a Cortex-M0+ and does not have the BASEPRI register. */
/* FreeRTOS critical sections are implemented by disabling all interrupts. */
/* Therefore, configKERNEL_INTERRUPT_PRIORITY and */
/* configMAX_SYSCALL_INTERRUPT_PRIORITY are not used. */
/* See https://www.freertos.org/RTOS-Cortex-M3-M4.html */
#define configKERNEL_INTERRUPT_PRIORITY          255
#define configMAX_SYSCALL_INTERRUPT_PRIORITY     191 /* equivalent to 0xa0, or priority 2 */
#define configMAX_API_CALL_INTERRUPT_PRIORITY    configMAX_SYSCALL_INTERRUPT_PRIORITY


/******************************************************************************/
/* Hook and callback function related definitions. ****************************/
/******************************************************************************/

#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0
#define configUSE_PASSIVE_IDLE_HOOK           0
#define configUSE_MALLOC_FAILED_HOOK          1
#define configUSE_DAEMON_TASK_STARTUP_HOOK    0
#define configUSE_SB_COMPLETED_CALLBACK       0
#define configCHECK_FOR_STACK_OVERFLOW        2

/******************************************************************************/
/* Run time and task stats gathering related definitions. *********************/
/******************************************************************************/

#define configGENERATE_RUN_TIME_STATS           0
#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    0

/******************************************************************************/
/* Co-routine related definitions. ********************************************/
/******************************************************************************/

#define configUSE_CO_ROUTINES              0
#define configMAX_CO_ROUTINE_PRIORITIES    1

/******************************************************************************/
/* Debugging assistance. ******************************************************/
/******************************************************************************/

#define configASSERT( x ) do { if( ( x ) == 0 ) { portDISABLE_INTERRUPTS(); for( ; ; ) { } } } while( 0 )

/******************************************************************************/
/* SMP( Symmetric MultiProcessing ) Specific Configuration definitions. *******/ 
/******************************************************************************/
#define configNUMBER_OF_CORES                     2
#define configRUN_MULTIPLE_PRIORITIES             1
#define configUSE_CORE_AFFINITY                   1

/******************************************************************************/
/* Definitions that include or exclude functionality. *************************/ 
/******************************************************************************/

#define configUSE_TASK_NOTIFICATIONS           1
#define configUSE_MUTEXES                      1
#define configUSE_RECURSIVE_MUTEXES            1
#define configUSE_COUNTING_SEMAPHORES          1
#define configUSE_QUEUE_SETS                   1
#define configUSE_APPLICATION_TASK_TAG         0
#define configUSE_POSIX_ERRNO                  0

#define INCLUDE_vTaskPrioritySet               1
#define INCLUDE_uxTaskPriorityGet              1
#define INCLUDE_vTaskDelete                    1
#define INCLUDE_vTaskSuspend                   1
#define INCLUDE_xTaskDelayUntil                1
#define INCLUDE_vTaskDelay                     1
#define INCLUDE_xTaskGetSchedulerState         1
#define INCLUDE_xTaskGetCurrentTaskHandle      1
#define INCLUDE_uxTaskGetStackHighWaterMark    1
#define INCLUDE_xTaskGetIdleTaskHandle         1
#define INCLUDE_eTaskGetState                  1
#define INCLUDE_xTimerPendFunctionCall         1
#define INCLUDE_xTaskAbortDelay                1
#define INCLUDE_xTaskGetHandle                 1
#define INCLUDE_xTaskResumeFromISR             1

/* A header file that defines trace macro can be included here. */

#endif /* FREERTOS_CONFIG_H */
