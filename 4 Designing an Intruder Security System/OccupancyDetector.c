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





