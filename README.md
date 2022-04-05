<div id="top"></div>

<!-- PROJECT SHIELDS -->
<!--
*** I'm using markdown "reference style" links for readability.
*** Reference links are enclosed in brackets [ ] instead of parentheses ( ).
*** See the bottom of this document for the declaration of the reference variables
*** for contributors-url, forks-url, etc. This is an optional, concise syntax you may use.
*** https://www.markdownguide.org/basic-syntax/#reference-style-links
-->


<h3 align="center">Embedded System Car</h3>

  <p align="center">
    Design, build and program a car to complete basic tasks including driving autonomously.
  </p>
</div>


<!-- ABOUT THE PROJECT -->
## About The Project

Project Objectives were to complete tasks culminating in steering the car through an obstacle course with the final stage autonomously driving the car along a black line that is drawn on the ground. 
Tasks:
  * Assemble Car
  * Add Wheels to drive forward/back 
  * Use PWM to Steer Car in different shapes
  * Control car via Wifi
  * Create On Board Menu system
  * Autonomous steering along black line
  * Combine all of the above tasks in full obstacle course
<br />

## What I Learned
This project gave me exposure to the designing an embedded system from the initial diagrams to final product. The biggest lesson that I learned was 
the importance of code optimization and using interrupts. Using such a small board meant that code had to be reduced to the simplest form so that the 
program wouldn't run over the allotted memory. With some of the complicated tasks this became quite a challenge, but it is a practice that I continue to apply 
even when storage is not a limitation.

Another interesting challenge that I came across was signal interruption. Driving through the obstacle course required wireless controls of the car. The class of 300 
students were all driving the cars in the same atrium within a few hours. With all of us using the same channel, the bandwidth was split and some student's cars would 
stall while driving through the course. I accounted for this by utilizing simple encryption keys so that other vehicle comands would not be misinterpreted.

This project also gave me practice with a technical write up. To read more about the specifics of the project, see the full writeup included within the repsoitory.

[![LinkedIn][linkedin-shield]][linkedin-url]

### Built With

* [C](https://en.wikipedia.org/wiki/C_(programming_language))
* [Python](https://www.python.org/)

<br />   

<img src= "https://github.com/barillamw/Autonomous-Car/blob/main/Car%20Pictures/car.jpg" style = "width:500px" alt= "Image of embedded system car" />


<p align="right">(<a href="#top">back to top</a>)</p>

[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/michael-barilla/
