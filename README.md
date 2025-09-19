# 🤖 ESP32 4-DOF Robotic Arm

This project implements a **4-DOF robotic arm** controlled by **ESP32** and **SG90 servos**, with **potentiometer-based control** and **teach-and-repeat functionality**.

## 🎯 Features
- 4-DOF control via potentiometers
- Record & Play motion sequences with push buttons
- Smooth 180° servo motion
- Compact reach (~26 cm)

## 🛠️ Hardware
- ESP32
- 4x SG90 Servo Motors
- 4x 10k Potentiometers
- 2x Push Buttons
- Breadboard & Jumper Wires
- Power Supply (5V)

## 🧠 Working Principle
Potentiometer readings (0-4095) are mapped to servo angles (0-180°). The ESP32 controls servos in real-time and can store movements for later playback.


## 🚀 Future Development
- 6-DOF upgrade with belt-driven actuation
- Stepper motors for higher torque
- AI-powered drawing capability
- Autonomous task planning

## 🌟 Inspiration
Inspired by [Epson Robots](https://epson.com/robots), [Trossen Robotics](https://www.trossenrobotics.com), [Kinova Robotics](https://www.kinovarobotics.com), [RobotAnno](https://www.robotanno.com), and [NVIDIA Robotics](https://developer.nvidia.com/embedded/robotics).

---
