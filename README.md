# Mini-Project: Water Storage Tank Control

Authors : Kyle G. Gayliyev, Hazen R. Brown, Prasanna Umbarkar, Mihir Rane <br>
Date: 29- March - 2024<br>
Course: ECE 6780 - Embedded System Design, ECE Department, The University of Utah<br>
GitHub IDs: ggayliye, Hrb2003, prasannaumbarkar09, patientcoderMR7 <br>
Repo:  <br>
Date: By 26-April-2024, 11:59pm (Time of when submission is due/will be ready to be evaluated)<br>
Copyright: ECE 6780, Kyle G. Gayliyev  - This work may not be copied for use in Academic Coursework.

## Overview of the Project
* Pumping water into a container that stops by itself when it's full and fills back again the exact amount when it gets empty. 
* Water fill station that automatically stops dispensing when full, implementation would sense water level without touching it. 
* A small 3V water pump will be connected to the power. The objective is to fill a water container. Once it reaches its high/full level, a signal will be sent to the microcontroller. The microcontroller will interrupt the water pump indicating the water container is full. The same process will take place when it’s empty. The water pump will start working and pump water into the container. 
* The container will include a sensor. This sensor is expected to be placed on the bottom of the container. It’ll sense when the container is “empty” and ready to be filled. To determine the container’s full state, the water-amount-calculation method will be used: the volume of the container will be known (mL), the speed of the pump for flowing water through a vinyl pipe will be known (x mL/s), and we calculate the amount of time the water pump should be kept on. 
* A BJT transistor is planned to be implemented in the circuit to indicate LEDs that will signal the container is full or empty to make it convenient for users. Other signals-such as sound/voice-can also be implemented to warn the container’s state. 
* For user’s drinking water safety, “water safety” measurement will be implemented. This implementation will only be based on chemicals that are ionic and/or electroconductive. Specifically, we will focus on Sodium chloride (NaCl) in our testing. This means that the “unsafe” measurement will be sensitive to salt. 
* The technical implementation of the “unsafe water” indicator is going to be in the container. It’s planned to be a simple design: installing an active power probs inside the container. When water hosts polluting electroconductive elements, it will create a path to transfer electrons that will trigger the measuring sensor. The power source will be set very low; it will be very safe to use. 
* Our design will be very safe to use as we take all precautions and safety measurements before the launch.

## Functional block diagram of The Project: 


## A List of 4 Implementation Milestones:

- Due by March 5th : Determine the sensors.
- Due on April 12nd :  Microcontroller code is ready and working.
- Due on April 19th :  Demonstration of a passing test with all components installed.
- Due on April 26th : Final Delivery.

### Some of the projected tasks to do:
* Develop code to effectively operate the water pump.
* Develop code to collect data from both sensors.
* Assemble the dispenser and integrate the water pump code with the sensor code.
* Test and fine-tune the device for practical functionality.


## Risks Associated With The Project And Plans To Compensate:

The use of water near electronics will require extra protection/care of the devices and connections. Additionally, the use of an ultrasonic sensor to measure the height of water may be difficult and could require extra work to ensure correct functionality. The most challenging part is expected to be implementing the water level sensor.


<pre><ins>Future extensions</ins> : This mini project is abount a month long project. Each week, we'll meet with a TA to discuss about the progress of the project and update the TA about the project's situation. As a group, we'll be continuesly working on this project updating it each week. It'll be finsihed at the end of the semester whether we accomplish our goals or not in this project. </pre>

# Partnership

This project is worked on as a requirement of "ECE 6780 Embedded System Design" class at the ECE Department, The University of Utah. The class requirements demand this project to be done as a group of minimum three,the maximum of four students. The group members for this project are listed on top of this page in the header. Most of the work is expected to be completed collectively/group in this project and not like "divide by task" style. Very limited amount of tasks will be assigned to group members as a diveded work.
# Progress Notes

<ins>1st Week Notes:</ins> <br>

- 
- 
<ins>2nd Week Notes:</ins> <br>

- 
<ins>3rd Week Notes:</ins> <br>

- 
- 
<ins>4th Week Notes:</ins> <br>


- 
- 
<ins>5th Week Notes:</ins> <br>

- 
- 

## Testing


# Time Expenditures:
<pre>Predicted Hours: 15h		Actual Hours:	h		 </pre>

The actual hours recorded on top reflect the time spent for the mini project including the time 
spent in labs for experiments. It excludes time spent reading, researching, and understanding the contexts or materials that require to complete the tasks related to the project.

# Comments to Evaluators:


Thank you for evaluating this project and providing feedback. <br>

Have a wonderful day!

## Testing Instructions:




# Consulted Peers:
N/A

# Caution/Warnings




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






