## Udacity Self-Driving Car Engineer Nanodegree, Term 2, Project 4: PID Controller

The goal of this project is to implement a PID controller in C++ to maneuver a simulated car around a track.

The car and track simulator is the one from the Behavioral cloning project of term 1, this time running in the term 2 simulator application.

The PID controller is fed measurement value of car speed, angle and cross track error. Based on these the PID controller shall compute the steering angle to keep the car on track.

It is also possible to give the simulator a throttle value back together with the steering angle, and so to control both steering and velocity of the car. I did not use this option. My PID controller provides only steering angle as output.

I chose to perform manual tuning of the PID coefficients and not to implement the "twiddle" algorithm presented in the lesson.

Seed code for the project is provided, and the task is to complete this. Seed code is taken from here:

https://github.com/udacity/CarND-PID-Control-Project

## Notes about Installation

I am using a Mac for development.

The uWebSockets were already installed in connection with project 1 of term 2. So I could directly execute the instructions:

1. mkdir build
2. cd build
3. cmake ..
4. make all

As in the previous projects of term 2 I had to modify the generated CMakeLists.txt to use the following line to enable make to find the linker:

link_directories(/usr/local/Cellar/libuv/1.20.3/lib)

The original line referred to the folder /usr/local/Cellar/libuv/1*/lib, and that does not work on my system.

After that everything worked as expected. I used the Sublime text editor and make on the command line to build.

Please note that I only submit the src files, but not the build folder. Please follow the 4 steps above to test my code.

## Rubric Points

### Compilation

#### Your code should compile  

Calling 'make all' on the command line compiles the code without warnings. As mentioned above I had to explicitly set the link path to get things to work properly on my system.

### Implementation

#### The PID procedure follows what was taught in the lessons

I used the provided file structure and implemented the following functions in the file PID.cpp:

1. Init()

2. UpdateError()

3. TotalError()

I also added code to main.cpp to call these functions, using UpdateError to feed a new CTE value into the controller, and TotalError() to get the result of the PID control calculation back. The total error is calculated using the appropriate coefficients as taught in the lesson.

It shall be mentioned that the function TotalError() calculates and the returns the positive sum of the 3 components, meaning that either the coefficients shall be initialized to negative values, or the caller of TotalError must add the minus to the returned value from the TotalError() function. I am doing the latter in main.cpp.

### Reflection

#### Describe the effect each of the P, I and D components had in your Implementation

In order to illustrate the individual effects of the P, I and D parts of the controller I decided to use the controller in exactly this way, and using QuickTime I was able to record mov files showing the how the car drive when controlled by P, I and D controllers only.

The proportional part of the PID controller directly directs the car towards the center line of the track, inversely proportional to the cross track error (which measures the diversion from the center line. As we saw in the lesson this parameter alone leads to sinus curves around the center line, and depending on the value of Kp the car even goes off the track very quickly. Here is a link to a video which shows how the car drives when controlled by a P controller alone, using Kp = 1.0 (I implemented that by initializing my PID controller with the K values 1.0, 0.0 and 0.0):

[./ProportionalOnly.mov](./ProportionalOnly.mov)

The purpose of the integral part of the PID controller is to eliminate systematic bias. Because it uses the total error over the entire time the integral part is very slow in reacting. When used alone the I part makes the car go off the road very quickly, and I furthermore found that even when used in combination with the P and D parts I had to set the Ki coefficient to a very small value to keep the car on the road. Here is a link to a video of the car being controlled by my PID controller using only the I part with K1 = 1.0:

[./IntegralOnly.mov](./IntegralOnly.mov)

Finally the differential part of the controller aims a reducing overshoot, by trying to reduce the rate of change of the error. As for the P and I parts, the D part does not work well when used alone. In the following video you will see that the car falls off the road when controlled by only the D part of my controller with Kd = 1.0.

[./DifferentialOnly.mov](./DifferentialOnly.mov)

#### Describe how the final hyperparameters were chosen

I chose the Kp, Ki and Kd values essentially manually, but not quite by trial and error. As described in Wikipedia the following general rules of thumb make sense for manual tuning:

First set Ki and Kd to zero. Increase Kp until the output of the loop oscillates, then Kp should be set to approximately half of that value for a "quarter amplitude decay" type response. Then increase Ki until any offset is corrected in sufficient time for the process. Too much Ki will cause instability. Finally, increase Kd until the loop is acceptably quick to reach its reference. Too much Kd will cause excessive response and overshoot.

I found that Ki could even be set to 0, and the car would still stay on track. For the submission the following parameters were used:

Kp = 0.15
Ki = 0.001
Kd = 2.5

Unfortunately Github does not allow me to upload a video of a complete track using these parameters.

### Simulation

#### The vehicle must successfully drive a lap around the track

The vehicle did that.
