#include <iostream>

#include "pico/stdlib.h"

#include "FreeRTOS.h"
#include "task.h"

#include "HX711.hpp"
#include "CoffeeScale.hpp"

using namespace ADC;
using namespace CoffeeScale;

// Define the LED pin
const uint LED_PIN = 25;

// Task to blink the LED
void led_task(void *pvParameters)
{
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while (true)
    {
        gpio_put(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_put(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_put(LED_PIN, 1);
        vTaskDelay(pdMS_TO_TICKS(100));
        gpio_put(LED_PIN, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

struct HardwareConfiguration
{
public:
    PIO pioInstance_;
    uint pioStateMachine_;
    ADC::Voltage referenceVoltage_;
    uint hx711DataPin_;
    uint hx711ClockPin_;
};

HardwareConfiguration hwConfig = {
    .pioInstance_ = pio0,
    .pioStateMachine_ = 0,
    .referenceVoltage_ = 3.3_V,
    .hx711DataPin_ = 26,
    .hx711ClockPin_ = 27,
};

CoffeeScale::Calibration dummyCalibration = {
    .referenceWeight_ = 750.0_g,
    .voltageAtReferenceWeight_ = 2.0,
};

void main_task(void *pvParameters)
{
    stdio_init_all();

    ADC::HX711 adc = ADC::HX711(hwConfig.referenceVoltage_, hwConfig.pioInstance_, hwConfig.pioStateMachine_, hwConfig.hx711DataPin_, hwConfig.hx711ClockPin_);
    LoadCell loadCell = LoadCell(dynamic_cast<ADC::IADC &>(adc));
    loadCell.SetCalibration(dummyCalibration);

    CoffeeScale::CoffeeScale scale = CoffeeScale::CoffeeScale(loadCell);
    scale.Zero();

    while (true)
    {
        auto weight = scale.GetWeight();
        // std::cout << "Weight: " << weight.value() << "g" << std::endl;
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

extern "C" {

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
    /* Run time stack overflow checking is performed if
    configCHECK_FOR_STACK_OVERFLOW is set to 1 or 2. This hook function is
    called if a stack overflow is detected. */
    ( void ) pcTaskName;
    ( void ) xTask;

    /* Force an assert. */
    configASSERT( ( volatile void * ) NULL );
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetIdleTaskMemory() to provide the memory that is
used by the Idle task. */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer,
                                    StackType_t **ppxIdleTaskStackBuffer,
                                    uint32_t *pulIdleTaskStackSize )
{
/* If the buffers to be provided to the Idle task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function returns. */
    static StaticTask_t xIdleTaskTCB;
    static StackType_t uxIdleTaskStack[ configMINIMAL_STACK_SIZE ];

    /* Pass out a pointer to the StaticTask_t structure in which the Idle task's
    state will be stored. */
    *ppxIdleTaskTCBBuffer = &xIdleTaskTCB;

    /* Pass out the array that will be used as the Idle task's stack. */
    *ppxIdleTaskStackBuffer = uxIdleTaskStack;

    /* Pass out the size of the array pointed to by *ppxIdleTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configMINIMAL_STACK_SIZE is specified in words, not bytes. */
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}

/* configSUPPORT_STATIC_ALLOCATION is set to 1, so the application must provide an
implementation of vApplicationGetPassiveIdleTaskMemory() to provide the memory that is
used by the Passive Idle task. */
void vApplicationGetPassiveIdleTaskMemory( StaticTask_t ** ppxIdleTaskTCBBuffer,
                                           StackType_t ** ppxIdleTaskStackBuffer,
                                           uint32_t * pulIdleTaskStackSize,
                                           BaseType_t xPassiveIdleTaskIndex )
{
    static StaticTask_t xIdleTaskTCBs[ configNUMBER_OF_CORES ];
    static StackType_t uxIdleTaskStacks[ configNUMBER_OF_CORES ][ configMINIMAL_STACK_SIZE ];

    *ppxIdleTaskTCBBuffer = &xIdleTaskTCBs[ xPassiveIdleTaskIndex ];
    *ppxIdleTaskStackBuffer = uxIdleTaskStacks[ xPassiveIdleTaskIndex ];
    *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
}


/* configSUPPORT_STATIC_ALLOCATION and configUSE_TIMERS are both set to 1, so the
application must provide an implementation of vApplicationGetTimerTaskMemory()
to provide the memory that is used by the Timer service task. */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer,
                                     StackType_t **ppxTimerTaskStackBuffer,
                                     uint32_t *pulTimerTaskStackSize )
{
/* If the buffers to be provided to the Timer task are declared inside this
function then they must be declared static - otherwise they will be allocated on
the stack and so not exists after this function returns. */
    static StaticTask_t xTimerTaskTCB;
    static StackType_t uxTimerTaskStack[ configTIMER_TASK_STACK_DEPTH ];

    /* Pass out a pointer to the StaticTask_t structure in which the Timer
    task's state will be stored. */
    *ppxTimerTaskTCBBuffer = &xTimerTaskTCB;

    /* Pass out the array that will be used as the Timer task's stack. */
    *ppxTimerTaskStackBuffer = uxTimerTaskStack;

    /* Pass out the size of the array pointed to by *ppxTimerTaskStackBuffer.
    Note that, as the array is necessarily of type StackType_t,
    configTIMER_TASK_STACK_DEPTH is specified in words, not bytes. */
    *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
}

void vApplicationMallocFailedHook( void )
{
    /* vApplicationMallocFailedHook() will only be called if
    configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
    function that will get called if a call to pvPortMalloc() fails.
    pvPortMalloc() is called internally by the kernel whenever a task, queue,
    timer or semaphore is created. It is also called by various parts of the
    demo application. If heap_1.c or heap_2.c are used, then the size of the
    heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
    FreeRTOSConfig.h, and in this case the RAM heap is allocated statically
    in request to the linker. */
    taskDISABLE_INTERRUPTS();
    for( ;; );
}
}

int main()
{
    // Create the main task
    xTaskCreate(main_task, "MainTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Create the LED task
    xTaskCreate(led_task, "LedTask", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    while (true)
    {
        // Should not be reached
    }
}
