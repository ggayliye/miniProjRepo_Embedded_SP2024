# Final-Project: Water Storage Tank Refill And Safety Control

Authors : Kyle G. Gayliyev, Hazen R. Brown, Prasanna Umbarkar, Mihir Rane <br>
Date: 29- March - 2024<br>
Course: ECE 6780 - Embedded System Design, ECE Department, The University of Utah<br>
GitHub IDs: ggayliye, Hrb2003, prasannaumbarkar09, patientcoderMR7 <br>
Repo: https://github.com/ggayliye/miniProjRepo_Embedded_SP2024 <br>
Date: By 26-April-2024, 11:59pm (Time of when submission is due/will be ready to be evaluated)<br>
Copyright: ECE 6780, Kyle G. Gayliyev  - This work may not be copied for use in Academic Coursework.

## Overview of the Project
* Pumping water into a container that stops by itself when it's full and fills back again the exact amount when it gets empty. 
* Water fill station that automatically stops dispensing when full, implementation would sense water level without touching it. 
* A small 4V water pump will be connected to the power. The objective is to refill a water container. Once it reaches its high/full level, a signal will be sent to the microcontroller. The microcontroller will interrupt the water pump indicating the water container is full. The same process will take place when it’s empty. The water pump will start working and pump water into the container. 
* The container will include a sensor. This sensor will be placed on the bottom of the container. It’ll sense when the container is “empty” and ready to be refilled. To determine the container’s full state, the water-amount-calculation method will be used: the volume of the container will be known (mL), the speed of the pump for flowing water through a vinyl pipe will be known (x mL/s), and we calculate the amount of time the water pump should be kept on. 
* For the water safety control circuit, we use a MOSFET, an op-amp, an LED, and a speaker. When the water gets salty (adding salt to the water), the alarm will sound along with an LED warning the water is not safe.
* Once the water starts filling the tank, a message is popped on the terminal "Tank empty-water filling in progress" and when completed "tank filled". Also when salt is added toxicity of water can be indicated by "toxic water" on the terminal. This is all done by UART.
* The water safety implementation will only be based on chemicals that are ionic and/or electroconductive. Specifically, we will focus on Sodium chloride (NaCl) in our testing. This means that the “unsafe” measurement will be sensitive to salt. 
* The technical implementation of the “unsafe water” indicator is going to be in the container. It’s planned to be a simple design: installing an active power probs inside the container. When water hosts polluting electroconductive elements, it will create a path to transfer electrons that will trigger the measuring sensor. The power source will be set very low; it will be very safe to use. 
* This project has applications in drinking water storage tanks, petroleum refineries, and more. 
* Our design will be very safe to use as we take all precautions and safety measurements before the launch.
* In this project, we implemented interrupt, GPIO, UART, and motor drive.

## List of Materials : 

![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/7.PartsList.jpg)

## Functional block diagram of The Project: 

![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/1.schematic.jpg)

## A List of 4 Implementation Milestones:

- Due by March 5th :  Determine the sensors.
- Due on April 12th:  Microcontroller code is ready and working.
- Due on April 19th:  Demonstration of a passing test with all components installed.
- Due on April 26th : Final Delivery.

### Some of the projected tasks to do:
* Develop code to effectively operate the water pump.
* Develop code to collect data from both sensors.
* Assemble the dispenser and integrate the water pump code with the sensor code.
* Test and fine-tune the device for practical functionality.

## Risks Associated With The Project And Plans To Compensate:

The use of water near electronics will require extra protection/care of the devices and connections. Additionally, the use of an ultrasonic sensor to measure the height of water may be difficult and could require extra work to ensure correct functionality. The most challenging part is expected to be implementing the water level sensor.


<pre><ins>Future extensions</ins> : This mini-project is about a month-long project. Each week, we'll meet with a TA 
to discuss the progress of the project and update the TA about the project's situation. As a group, 
we'll be continuously working on this project updating it each week. It'll be finished at the end 
of the semester whether we accomplish our goals or not in this project. </pre>

# Partnership

This project is worked on as a requirement of the "ECE 6780 Embedded System Design" class at the ECE Department at the University of Utah. The class requirements demand this project to be done as a group of a minimum of three, and a maximum of four students. The group members for this project are listed on top of this page in the header. Most of the work is expected to be completed collectively/in groups in this project and not like the "divide by task" style. A very limited amount of tasks will be assigned to group members as individual work/divided work.

# Progress Notes

<ins>1st Week Notes:</ins> <br>

By March 13th

- The project proposal is submitted.
- Feedback about our project proposal is received from the TA. It reads as follows:<br>

*"Good that you are considering safety. Think about how you can test the system without a tank and pump.* <br>

*Float sensors are another possibility you can consider for measuring the height.* <br>

*Be careful of relying on a "known" rate, such as the pump time. Variations can make the integration of the rate become increasingly wrong over time as the error accumulates. Use the expected rate to do initial conditions and then use sensor feedback to adjust.* <br>

*You need to expand the detail of your milestones. You use verbs for activities, which is good. Some of your targets are less clear - be as detailed as possible about how you will demonstrate it working and what a successful implementation would be. What does "working" mean? How do you demo that?* <br>

*Your first milestone falls into the "getting materials" anti-milestone. You cannot test something you don't have, and you need to make progress towards other goals.* <br>

*Your risks are identified, but think about what you can do it the risk turns out to be true. If the water sensor is the challenge, do you have a fallback? What happens if you run over schedule?* <br>

*Finally, make sure you don't fall in the trap of splitting the work up by person and then trying to bring everything together. This is a classic mistake everyone always tries."*

<ins>2nd Week Notes:</ins> <br>
By March 22nd:

- The project GitHub account is created.
- All members added to the repo and members practised "commit" action.

<ins>3rd Week Notes:</ins> <br>
By March 29th:

 <pre>Mini-Project Milestone 1 :  </pre>

This week on Thursday, we met with Ashton during office hours and discussed our project's status.<br>

We talked about the implementation of the microcontroller, the motor's pumping speed, and water level sensors. As we mentioned in our project proposal, we're expecting the water level sensor to be the difficult part of the project.<br>

We updated the TA on what we have done and talked about our team meeting in the week. We determined the tasks we planned to do in this week's experiment. <br>

Today on Friday, we met with the team to test our motor, microcontroller, and measure the speed of the pump. <br>

In our group meeting today, we measured the speed of the pump. We found the running current of the motor to be 170 mA. The other experiment results with the water pump are below:

1. *138 mL of water is filled in 4.75 sec.*
 
2. *100ml of water is filled in 4.58 sec.*
 
3. *100mL of water is filled in 5.92 sec.*
 
4. *100ml of water is filled in 5.35 sec.*
 
5. *100ml of water is filled in 6.17 sec.*
 
Avg: 5.505 sec for 100ml.<br>

- We will be testing the completed section of the project each week. Before the final week, we'll be testing the project with all components together. In the final week, we'll also demonstrate the project's function as a whole.

Pictures from the experiment day: <br><br>
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/1stExpPics/1.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/1stExpPics/2.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/1stExpPics/3.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/1stExpPics/4.jpg)

<ins>4th Week Notes:</ins> <br>
By April 5th:
<pre> Mini-Project Milestone 2 :</pre><br>

- This week on Friday, we met with TA Baily in the morning lab hours and discussed our project's status.

- We talked about the implementation of the microcontroller and a water-level sensor prototype.  We tested an LM324 comparator and metal probes to sense the water level. We successfully were able to trigger the interrupt that signals when the water storage tank is empty (water level). 

- After the lab, we met to do the sensor-level testing and the comparator implementation.  Also, we were able to send the interrupt signal to the microcontroller to be able to read the signal and respond as an interrupt. The L292, from our soldering PCB assignment, is used to run the motor and change the motor speed adjusting PWM.

- The water pump motor is driven at 4V allowing modulation (PWM) between 80% and 100%.

- We foresee our working motor speed may change when we progress on this project.

Pictures from the Milestone 2 experiment day: <br><br>
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/2ndExpPics/1.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/2ndExpPics/2.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/2ndExpPics/3.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4.SensorPrototype_WaterLevel.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/emptySensor/Schematic%20Photo.JPG)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/emptySensor/Main%20overview%20drawing.JPG)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/emptySensor/toxic%20water%20drawing.jpeg)



<ins>5th Week Notes:</ins> <br>
<pre> Mini-Project Milestone 3 : </pre><br>

- On Friday during our lab time on the 12th of April, we gathered with all team members to progress our project one step further. In our meeting, we implemented the sensor signal-microcontroller interface and UART-microcontroller interface.

- At the beginning of the project, we had predicted the most challenging part would have been implementing the water level sensor. This sensor implementation was expected to be challenging because it should sense the empty status of the water container. However, it's good news that we were able to successfully implement it during our lab meeting this week.

- To give a little bit of background information on how the empty tank sensing should work is that we implemented the physical sensor on the bottom of the water tank wired with a microcontroller connection. When the water level reaches low, the sensor sends an analog signal to an op-amp that works as a comparator. It compares the Vp and Vn input pins and outputs Vcc in the Vout that is connected to the microcontroller. When the analog signal is received from the op-amp, which will signal that the container is empty, the microcontroller will turn the water pump on, and the pump starts refilling the water container. The microcontroller will interrupt in the end when the container is full and that will indicate the time to stop pumping water.

![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/1.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/2.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/3.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/4.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/5.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/3rdExpPics/6.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/6.UART_USB.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/5.MotorDriver.jpg)




<ins>6th Week Notes:</ins> <br>
<pre> Mini-Project Milestone 4 Final submission : </pre><br>
- Today, on April 24th, we meet up to complete our project in the lab. We successfully implemented toxicity detection, as well as water level detection with UART messages displayed in the terminal.
- Our project implemented water storage tank refill and safety control. In our previous milestones, we had implemented water pump control using a motor driver we created and soldered in one of our class lab assignments, microcontroller, UART transmit and receive interface, and GPIO LED implementation. 
- The project implementation starts when the water storage tank is full. Today during our lab tests, first, we drained water and checked the water level sensor's response.
- The water level sensor is set close to the bottom of the tank. When the tank was fairly empty, we verified that the microcontroller gave a start to the pump.
- The water pump kept running while pumping water until the water storage tank was refilled. It was interrupted by the microcontroller stopping the pump when the water level reached full. 
- Second, we tested the safety control of the water container. As we mentioned before, we did this test with NaCl(salt). 
- After setting up the experiment equipment, we poured some salt into the container. Our circuit implements safety control triggered by the salt added into the water alarming by a speaker and making an LED on.
- The alarm system is built using an op-amp and an NMOS. The NMOS transistor works as a switch allowing a square wave set up as a sweep flowing from drain to source.
- Additionally, our system allows for manual control of the pump over UART. A user can turn the pump on and off, as well as change between three preset pump rates. The microcontroller will automatically send messages to the terminal when the tank is empty, or full, or if the water has gone toxic. 
- Overall, we completed all milestones and tasks for this mini-project that were initially set.


![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/1.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/2.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/3.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/4.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/5.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/6.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/7.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/8.jpg)
![alt text](https://github.com/ggayliye/miniProjRepo_Embedded_SP2024/blob/main/materials/4thExpPics_final/9.jpg)





# Time Expenditures:
<pre>Predicted Hours: 15h		Actual Hours:	16h		 </pre>

The actual hours recorded on top reflect the time spent on the mini-project including the time spent in labs for experiments. It excludes time spent reading, researching, and understanding the contexts or materials that are required to complete the tasks related to the project.

# Comments to Evaluators:

Thank you for evaluating this project and providing feedback. <br>

Have a wonderful day!

# Testing


- The water storage tank should be at a higher level than the water container that water is pumped from. Otherwise, the water transfer will occur until both containers' levels are balanced with the help of gravity without the pump.

## Project Testing Set Up

- Two water containers are needed: one of them to be filled with water and the other with just enough water to cover the level sensor. 
- The water level sensor is constructed from two copper wires taped to an insulating rod. These wires attach to the water level comparing circuit which sends a high or low signal to the microcontroller. 
- To measure toxicity, both containers should host a wire to allow current to flow through the water. This will measure the resistance of the water, ensure equal residency in case pH (potentially may change between 0-14) changes, and compare the "standard" water sample to the "tested" container by sending the signals to the LM324 op-amp's Vp and Vn pins. Depending on the safety, the op-amp will have 2 distinct outputs that help trigger the safety alarm if NaCl is detected.
- This op-amp's output should go to an NMOS transistor gate. The NMOS transistor's drain receives a square wave with a sweep from 10 Hz to 1.5 kHz. The sweep time should be set to 900ms. The amplitude should be set to 4 Vpp. On the source of the NMOS, a speaker is connected. The speaker's other end is connected to the Ground. 
- The op-amp receives 5V in DC on the +Vdd and 0V/Ground on the -Vdd.
- When the water contains enough salt to be determined unsafe, the comparator triggers the rest of the toxicity circuit to sound the alarm and illuminate the LED. This toxicity circuit also sends a high or low signal to the microcontroller. 
- The low-level circuit output signal is connected to pin PA0 of the STM32, and the toxic water circuit output signal is connected to PB3 of the STM32. These signals trigger interrupts within the microcontrollers software which allow for enabling and disabling the pump. 
- The water pump is connected to the motor driver. We are driving the motor at 4V so we supply the motor diver with a constant 4V DC supply. 
- For full USART capability, PUTTY or any other UART terminal is required. 
- To test the system, water can be drained from the water tank. Draining the tank below the set threshold will automatically trigger the motor to turn on and begin refilling the container. When the pump kicks on, a message will be transmitted over UART signaling the pump is running. The pump will then pump for a preset time until the water tank is full, once again signaling over UART that the tank is full.
- In the case a user wishes to change the pump rate, or manually enable/disable the pump, these commands can be sent over UART. Pressing M followed by 1 in the terminal will turn the pump on, and M - 0 will turn the pump off. To select various pump speeds, the commands A - 0, A - 1, and A - 2 can be used. 0 commands 100% PWM, the "1" commands 95%, and "2" commands 90%. 
- To test the water toxicity circuit, salt can be added to a full water tank. Once enough salt is added to this tank the alarm will sound and a message will be transmitted over UART signaling an operator to manually reset the system. All functions of the system will be disabled at this time. 


*Obtaining the components, this project can also be tested in a different setting. However, we don't recommend testing this project to anyone who doesn't have full/complete information about this project.*


# Credits
- Thang Tran, Department of Chemical Engineering, The University of Utah:
	*- Thank you for your support on providing supplies in our experiments!*

- Ashton Snelgrove, Department of Electrical and Computer Engineering, The University of Utah:
	*- Thank you for your continuous support until the end of the semester!*


# Caution/Warnings

* Don't use any electric component that exceeds 5V.
* Don't use any metal with a wet hand and touch an electric component.
* Wash your hands after each experiment.
* Don't drink the water used for the testing/experiment.
* Make sure you check and be familiar with the op-amp and transistor's type and physics before starting the experiment.


# Examples of Good Software Practice (GSP)
<pre><ins>DRY</ins> :</pre>
DRY is an abbreviation of "Don't repeat yourself". It's a principle of Software Engineering that
has the goal of reducing repetition and redundancy in the coding. Using abstractions and normalization
are advised over redundancy <a href="https://en.wikipedia.org/wiki/Don%27t_repeat_yourself">[2]</a>.

<pre><ins>Separation of Concerns</ins> :</pre>
This concept is similar to the "divide and conquer" principle where you divide
a big software project into small projects to complete. A software design technique that focuses on separating 
and freeing functionalities of a program is called Modular programming. Making each of the divided small 
projects independent and addressing a separate concern, it'll make it easy to reduce, detect 
and fix the errors. <a href="https://en.wikipedia.org/wiki/Separation_of_concerns">[3]</a>

<pre><ins>Good Code Typing Practices</ins> :</pre>
Good coding practices can be listed as: Naming variables with a relevant name, commenting 
in between code lines with a brief explanation if the code is not self-explanatory, creating 
helper methods that can be used multiple times and by other sections.


<pre><ins>Testing Strategies</ins> :</pre>
Unit Testing can be summarized in 3 types of techniques:<br>

1. <ins>Black Box Testing : </ins> In this testing, input, user interface, and output parts are covered.
2. <ins>White Box Testing : </ins> In this testing, functionality, design structure, and code models are covered.
3. <ins>Gray Box Testing : </ins> In this testing, analysis of code performance, relevant test cases,
methods, and functions are covered.<a href="https://www.geeksforgeeks.org/unit-testing-software-testing/">[4]</a>


# References:
1. Canvas Page Class Materials.(For example, lecture slides, additional resources and pdf files). <br>
2. https://en.wikipedia.org/wiki/Don%27t_repeat_yourself<br>
3. https://en.wikipedia.org/wiki/Separation_of_concerns<br>
4. https://www.geeksforgeeks.org/unit-testing-software-testing/<br>






