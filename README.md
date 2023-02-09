# Part 4: Occupancy Detection and Alert System
You are being asked to design a rudimentary occupancy alert system with the following behavior:
- The system when turned on needs to blink the Green LED once every 3 seconds to show it is armed.
- When the occupancy sensor detects someone, it will output a Logic 1, and your system needs to move into a "Warning" state, where the Green LED stops blinking, and the Red LED Blinks once per second (500ms on, 500ms off).
- If the occupancy detector still shows someone there after 10 seconds, your system should indicate this with the RED Led constantly staying on, and move into the ALERT state.
- If the occupancy detector **before** the 15 seconds goes back to a 0, indicating the room is now empty, then the system should go back to the armed state.
- When in the ALERT State, the only way for the system to go back to the Armed state is to press the P4.1 Button.

## Occupancy Sensor
You will be **first** *emulating* the Occupancy Sensor with the P4.1 button. This can be used for pretty much all of your testing and design.

When you have a design that is working, you can then test your code with a [Passive Infrared Occupancy Detector](https://www.amazon.com/DIYmall-HC-SR501-Motion-Infrared-Arduino/dp/B012ZZ4LPM)

## Getting Started
I highly recommend on paper or a whiteboard drawing up a state machine or something to help understand the flow of the system.

From there, you should work on each stage/state and see if the transitions work. For example, can you get the system to go from the armed state to the warning state.

Remember that your code is going to be running in a loop, so you need to make sure you consider how this is going to work when trying to blink the LEDs.

## Do I need to use Interrupts?
Well, it would be cool, but at the end of the day, we are asking you for a design. Start with polling or what you feel comfortable with, but we would like you to try out using the interrupts, maybe at least for the system Disarm Button.

## Navigating multiple states
One way to approach a system with multiple states is to actually use a case statement in your main loop. For example:
```c
#define ARMED_STATE 0
#define WARNING_STATE 1
#define ALERT_STATE 2

// Put some initialization here

char state = ARMED_STATE;

while(1)
{
  switch (state) {
    case ARMED_STATE:
    {
      // Do something in the ARMED state
      // If something happens, you can move into the WARNING_STATE
      // state = WARNING_STATE
    }
    case WARNING_STATE:
    {
      // Do something in the WARNING_STATE
    }
  }
}
```





//Luciano Miletta 
 
 
#include <msp430.h> 
#include <time.h> 
 
int main(void) 
{ 
    WDTCTL = WDTPW | WDTHOLD; //Stops the Watchdog Timer 
 
 
 
    P1OUT &= ~BIT0; //Turns off the Red LED 
    P1DIR |= BIT0; // Turn on P1DIR 
 
    P6DIR |= BIT6; // Turns on the Green LED 
    P6OUT &= ~BIT6; // Turns off the Green LED 
 
 
     P4DIR &= ~BIT1; //Turns on P4DIR 
     P4REN |= BIT1;  //Turns on P4REN 
     P4OUT |= BIT1;  //Turns on P4OUT 
 
     P2DIR &= ~BIT3; //Turns on P2DIR 
     P2REN |= BIT3;  //Turns on P2REN 
     P2OUT |= BIT3;  //Turns on P2OUT 
 
 
     PM5CTL0 &= ~LOCKLPM5; 
 
     unsigned int totaltime; 
 
     totaltime=0; // resets the timer 
     while(1) 
     { 
 
 
         if  (((P4IN & BIT1)==0X002) & (totaltime<0x14))  // If the left button is not pressed and timer is less then 10 seconds 
             { 
                 P1OUT &= ~BIT0;            // Turns off red led 
                 P6OUT ^= BIT6;             // Makes the Green LED Blink 
                 _delay_cycles(3000000);     // 3 secound delay 
                 totaltime=0; // resets the timer 
             } 
 
 
 
 
         if (((P4IN & BIT1)==0X00) & (totaltime<0x14)) // If the Left Button is pressed and timer is less then 10 seconds 
         { 
 
             P6OUT &= ~BIT6;          // Turns off green led 
             P1OUT ^= BIT0;           // Makes the RED LED Blink 
            _delay_cycles(500000);    // .5ms delay 
            totaltime= totaltime+ 1;  // counts up the timer 
         } 
 
 
         if ((totaltime==0X14)) // if timer = 10 secounds 
 
          { 
              P1OUT ^= BIT0;  // Makes the RED LED solid 
          } 
 
         if((((P2IN & BIT3)==0X00))) //If the right button is pressed 
          { 
             totaltime=0; // resets the timer 
          } 
 
     } 
} 
 
## Submission
Description of code

Basically when the code starts and no one is infront of the sensor it will blink the green light every three secounds. Then if someone is infront of the sensor the green light will turn off and the red light will blink every .5 secounds and a timer will start. After that if there is someone infront of the sensor for 10 secounds or more the redlight will turn solid. When the red light is solid then you will press the right button to reset the code form the beggining. 
