# ZephyrAuto+ - Advanced Driver Assistance System Prototype
ZephyrAuto+: Advanced automotive system enhancing road safety and vehicle technology through sensor-based interventions and driver assistance features.

# ZephyrAuto+ - Autonomous Vehicle Control System

ZephyrAuto+ is an advanced automotive system aimed at revolutionizing road safety and vehicle technology. It integrates a plethora of features such as Adaptive Evasive Maneuvering, Adaptive Cruise Control, Lane-Keeping Assist, Automatic Emergency Braking, Blind Spot Monitoring, and more. These features rely on a sophisticated array of sensors to monitor the vehicle's surroundings, predict potential hazards, and provide timely warnings or interventions to prevent accidents.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [License](#license)

## Introduction

ZephyrAuto+ is developed to enhance vehicle automation, providing a safer and more efficient driving experience. It leverages a combination of sensors and actuators to control the vehicle's movements, react to its environment, and assist the driver in various scenarios.

## Features

### Adaptive Evasive Maneuvering (AEM)

Adaptive Evasive Maneuvering (AEM) is a critical safety feature that utilizes sensor data to calculate and execute optimal evasive maneuvers in real-time to prevent collisions or reduce their severity.

#### Working

- **Sensor-Based Data Analysis:** AEM analyzes data from radar, lidar, cameras, and ultrasonic sensors to assess positions and movements of nearby objects.
- **Optimal Evasive Maneuver Calculation:** Based on sensor data and algorithms, AEM calculates the most effective evasive maneuver to avoid collisions or minimize impact.
- **Autonomous Evasive Action:** If a collision risk is imminent, AEM autonomously executes the calculated maneuver, such as swerving or braking, to avoid the obstacle.
- **Driver Alert and Preparation:** AEM alerts the driver with audible warnings, preparing them for the upcoming evasive action.

### Adaptive Cruise Control (ACC)

Adaptive Cruise Control (ACC) is an advanced driver assistance system that automatically adjusts the vehicle's speed to maintain a safe distance from vehicles in front, enhancing comfort and safety.

#### Working

- **Ultrasonic Sensors and Traffic Tracking:** ACC utilizes ultrasonic sensors, radar, or lidar to monitor traffic conditions and adjust speed accordingly.
- **Automatic Speed Adjustment:** When detecting a slower vehicle ahead, ACC automatically adjusts speed to maintain a safe following distance, applying brakes if necessary.
- **Collision Probability Assessment:** ACC assesses the likelihood of a collision based on distance and relative speed, taking aggressive measures if the risk is high.

### High Beam Assist (HBA)

High Beam Assist (HBA) dynamically adjusts the vehicle's high beams to optimize road visibility while preventing glare for other drivers.

#### Working

- **Dynamic High Beam Control:** HBA intelligently manages high beams, switching between high and low beams based on changing conditions.
- **Glare Prevention and Safety:** HBA automatically dims high beams when detecting oncoming vehicles or taillights, reducing glare and enhancing safety.
- **Light Level Detection (LDR):** HBA uses Light Dependent Resistor (LDR) technology to sense changes in ambient light levels, triggering high beams for improved visibility.

### Lane Guidance Assist (LGA)

Lane Guidance Assist enhances vehicle stability and safety by monitoring the vehicle's position within its lane using a combination of sensors.

#### Working

- **Multisensory Monitoring:** LGA employs ultrasonic sensors, IR sensors, and sensor fusion to create a detailed understanding of the vehicle's position and proximity to lane boundaries.
- **Real-time Steering Corrections:** LGA makes precise steering corrections to keep the vehicle within its lane, providing feedback through the steering wheel and auditory alerts.

### Safe Exit Warning (SEW)

Safe Exit Warning (SEW) utilizes ultrasonic sensors to monitor the vehicle's surroundings, especially blind spots, to detect pedestrians, cyclists, or vehicles approaching during door opening.

#### Working

- **Ultrasonic Sensor Monitoring:** SEW creates a 360-degree monitoring zone around the vehicle using ultrasonic sensors to detect approaching objects.
- **Audible Warnings for Passenger Safety:** SEW activates audible warnings when potential hazards are detected, promoting caution before opening doors to prevent accidents.

### Blind Spot Collision Assist (BCA)

Blind Spot Collision Assist detects objects entering the vehicle's blind spots using ultrasonic sensors and provides warnings or autonomous interventions to prevent collisions.

#### Working

- **Ultrasonic Sensor Detection:** BCA utilizes ultrasonic sensors to continuously monitor blind spots and detect objects entering them.
- **Onboard Computer Analysis:** Data collected by sensors is processed in real-time to determine potential obstacles in blind spots.
- **Auditory Alerts and Active Interventions:** BCA provides audible warnings and can offer steering assistance or braking to prevent collisions when changing lanes.

### Leading Vehicle Departure Alert (LVDA)

Leading Vehicle Departure Alert (LVDA) enhances safety by detecting the movements of vehicles in front and providing immediate alerts to prevent collisions caused by sudden departures.

#### Working

- **Ultrasonic Sensor-Based Detection:** LVDA monitors the distance between the host vehicle and the leading vehicle using ultrasonic sensors.
- **Immediate Alert System:** LVDA provides immediate alerts to the driver if the leading vehicle unexpectedly departs or performs a sudden maneuver, enhancing reaction time and preventing collisions.

### Rear Cross Traffic Alert (RCTA)

Rear Cross Traffic Alert (RCTA) utilizes ultrasonic sensors to monitor the area behind and to the sides of the vehicle, providing warnings of potential collision risks from cross-traffic when reversing.

#### Working

- **Ultrasonic Sensor-Based Monitoring:** RCTA continuously scans surrounding areas using ultrasonic sensors to detect cross-traffic hazards.
- **Detection of Cross-Traffic Hazards:** RCTA identifies potential collision risks from cross-traffic, issuing audible warnings to alert the driver.
- **Driver Response and Collision Avoidance:** Upon receiving warnings, the driver can take appropriate action to prevent collisions while reversing, enhancing parking safety.

### Forward Collision Warning (FCW)

#### Working

 - Utilizes ultrasonic sensors to detect objects ahead of the vehicle.
 - Issues personalized audible warnings based on the severity of potential collisions.
 - Can autonomously intervene by applying brakes if the driver doesn't respond promptly.

## Installation

To install ZephyrAuto+ on your vehicle, follow these steps:

1. Clone the repository to your local machine:

    ```bash
    git clone https://github.com/spyderbeast/zephyrauto.git
    ```

2. Connect the necessary hardware components to your vehicle according to the pin configuration specified in the code.

3. Upload the master code to the Arduino board controlling the vehicle's main functions.

4. Upload the slave code to the Arduino board responsible for receiving commands and controlling peripherals.

## Usage

To use ZephyrAuto+:

1. Power on the vehicle and ensure all sensors are functioning correctly.

2. Use the keypad interface to select the desired mode (DRIVE, REVERSE, PARK, CRUISE, LANEKEEP).

3. Follow the instructions displayed on the LCD screen for each mode.

4. The System will take action automatically according to the data received from the sensors.

## Contributing

Contributions to ZephyrAuto+ are welcome! If you have ideas for improvements or new features, feel free to open an issue or submit a pull request. Please follow the contribution guidelines outlined in the repository.

## License

This project is licensed under the [MIT License](LICENSE).

