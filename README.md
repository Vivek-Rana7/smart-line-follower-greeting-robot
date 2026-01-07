# smart-line-follower-greeting-robot
Line following robot with object detection and voice greeting system
This project demonstrates a smart autonomous line follower robot that follows a predefined path and interacts with objects using a voice greeting system.
The robot uses sensors to make decisions without human control.

✨ Features

Line following using IR sensors

Object detection using ultrasonic sensor

Plays recorded greeting audio when an object is detected

Robot stops movement during greeting

Fully autonomous behavior

🧠 Working Logic

The robot follows a black line on a white surface using IR sensors.

An ultrasonic sensor continuously checks for objects in front.

When an object comes within a fixed distance:

The robot stops

A recorded greeting audio is played

After the object is removed, the robot resumes line following.

🔧 Hardware Used

Arduino / Microcontroller

IR Line Sensors

Ultrasonic Sensor (HC-SR04)

Motor Driver (L298N / L293D)

DC Motors and Wheels

Speaker / Audio Module

Battery and Chassis

💻 Software & Tools

Arduino IDE

Embedded C / Arduino Programming

📂 Project Structure
smart-line-follower-greeting-robot/
├── code/      # Arduino program
├── circuit/   # Circuit diagram
├── audio/     # Greeting audio
├── demo/      # Working video
├── docs/      # Documentation
└── README.md

🚀 Applications

Educational robotics projects

Smart service robots

Beginner autonomous systems

Human–robot interaction demos

🔮 Future Scope

Bluetooth or Wi-Fi control

Voice recognition

Camera-based navigation

AI-based object detection
