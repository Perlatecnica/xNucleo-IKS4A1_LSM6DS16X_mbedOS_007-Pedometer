/*
MIT License

Copyright (c) [2024] 
Organization: Perlatecnica APS ETS
Author: Mauro D'Angelo

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "mbed.h"
#include "LSM6DSV16X.h"

LSM6DSV16X AccGyr(I2C_SDA, I2C_SCL); 
Serial pc(USBTX, USBRX);
DigitalOut led(LED1);
InterruptIn intPin(D5);
Timer t;

//Interrupts.
volatile int mems_event = 0;

uint16_t step_count = 0;
char report[256];
uint32_t previous_tick;
uint32_t current_tick;

void INT1Event_cb();


// main() runs in its own thread in the OS
int main()
{
    // Initialize serial for output.
    pc.baud(115200);

    //Interrupts.
    intPin.rise(&INT1Event_cb);

    AccGyr.begin();
    AccGyr.Enable_X();
    AccGyr.Enable_Pedometer(LSM6DSV16X_INT1_PIN);

    previous_tick = t.read_ms();

    while (true) {
        if (mems_event)
        {
            mems_event=0;
            LSM6DSV16X_Event_Status_t status;
            AccGyr.Get_X_Event_Status(&status);
            if (status.StepStatus)
            {
            // New step detected, so print the step counter
            AccGyr.Get_Step_Count(&step_count);
            snprintf(report, sizeof(report), "Step counter: %d", step_count);
            pc.printf("%s",report);

            // Led blinking.
            led = 1;
            thread_sleep_for(100);
            led = 0;
            }
        }
        // Print the step counter in any case every 3000 ms
        current_tick = t.read_ms();
        if((current_tick - previous_tick) >= 3000)
        {
            AccGyr.Get_Step_Count(&step_count);
            snprintf(report, sizeof(report), "Step counter: %d", step_count);
            pc.printf("%s",report);
            previous_tick = t.read_ms();
        }
        
    }
}

void INT1Event_cb()
{
  mems_event = 1;
}

