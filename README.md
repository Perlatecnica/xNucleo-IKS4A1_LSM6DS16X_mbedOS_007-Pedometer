# xNucleo-IKS4A1_LSM6DSV16X_mbedOS_007-Pedometer

This application shows how to use LSM6DSV16X accelerometer to count steps.

---
### Description:

This code showcases the usage of interrupts with the LSM6DSV16X sensor to detect steps (pedometer functionality). It configures an interrupt to trigger when a step is detected by the sensor. Upon detecting a step, it increments a step counter, blinks an LED, and prints the step count over the serial connection. Additionally, it periodically prints the step count every 3000 milliseconds.

### How it works:

- **Initialization**: 
  - It includes necessary libraries for communication (`mbed.h`) and for interfacing with the LSM6DSV16X sensor (`plt_iks4a1.h`).
  - It initializes objects for serial communication (`Serial`), an LED for visual indication, an interrupt pin (`InterruptIn`), and a timer (`Timer`).
  - It sets up an interrupt callback function (`INT1Event_cb`) to handle interrupts.

- **Sensor Configuration**: 
  - It initializes the LSM6DSV16X sensor and enables the accelerometer.
  - It configures the sensor to detect steps (pedometer functionality) and assigns the interrupt pin for interrupt triggering.

- **Main Loop**:
  - It enters an infinite loop where it continuously checks if a step event has occurred.
  - When a step event is detected, it increments the step counter, toggles the LED to indicate detection, and prints the step count over the serial connection.
  - It also periodically prints the step count every 3000 milliseconds to provide continuous updates.

- **Interrupt Event Handler**:
  - When the interrupt occurs, it sets a flag to indicate an event.

---

This description provides an overview of the code's functionality, including initialization, interrupt setup, sensor configuration, step event detection, and step count reporting.