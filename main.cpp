// Authors:
//Imani Muhammad-Graham github@ Imani-ES
// Brian Chen - github@ frostedbranflakes
//November 2020
//Project 3: Automated Plant Care System
//This system will help you keep plants alive in your home through the use of technology.
//Inputs:  
//The humidity sensor will detect when it is too humid to water the plant.
//The rotary encoder will detect when the inputted amount of water is poured into the plant.
//Outputs:    
// The servo tilts the water bottle to water the plant.
// The LED displays when it is too humid to water the plant.
// Serial monitor for debugging and functionality coinfirmation
//**Important notes**
//Water bottle must be manually refilled and reset when empty.
//The frequency of watering, the amount of water, and the cutoff humidity need to be inputted before the system can start.
//Sufficient space is needed for the bottle to turn when watering.
//The bottle cannot be swapped out for another bottle.
//Sources/ Links: 
//    Professor Jennifer Winikus
#include "mbed.h"
#include "iostream"
#include "DHT.h"
#include "driver.h"
#include "1802.h"
#define OK   0
#define not_OK   1
//Interrupt and ISR for user Input
    InterruptIn submitQuery(USER_BUTTON);
    void submit(void);
//ROTARY ENCODER 
    int aVal;
    int aPrev;
//SERVO
    PwmOut myServo(PB_6);
    int water();//holder function for servo
//Tickers and logic
    int volume;// how long each watering session is (in seconds, not actual volume)
    int volume_lost;
    int watering = 0;
    int period; // how long each period is
// DHT, watch dog and functionality
    DHT11 sensor(PE_15);// DHT Object
    int high_h = 57;// acceptable humidity levels vary from plant to plant
    int low_h = 53;
    int curr_h;
    int state =0;// State of system(initial, user input, and system running)
    int init();
    int query();
    int update();// DHT periodic feedback output to LCD, kick watchdog
// Set up the watchdog
    Watchdog &safe = Watchdog::get_instance();
    #define safe_timeout 20000// set for 2 hours (20 seconds for demo)
EventQueue printer(32 * EVENTS_EVENT_SIZE);//This print queue will hold all print statements
Thread tp;
int main(){
    safe.start(safe_timeout);//system completely reboots 
    tp.start(callback(&printer,&EventQueue::dispatch_forever));// Begin queue
    printer.call(printf, "----Start----\n");
    if(init()){// call initialization function
        printer.call(printf, "---- System Retarting----\n");

    }
    printer.call(printf, "---- Initialized----\n");
    if (query()){//call query function
        printer.call(printf, "---- System Retarting----\n");
    }
    printer.call(printf, "---- System Starting----\n");
    int cnt = 0;
    while(state == 4){// state should be 4 once passed through init and query
        update();
        if(cnt >= period){
            if(water()){
                printer.call(printf, "---- System Error, restarting----\n");
                thread_sleep_for(safe_timeout);// Let watch dog kick in
            }
            cnt = 0;
        }
        cnt ++;
        thread_sleep_for(1000);// sleep for 1 second u
    }
    return OK;
}
void submit(void){
    if(state >0 and state<=3){
        state++;
    }
    thread_sleep_for(100);// 
}
//RE END
int water(){// Waters plants for chosen period
    if(curr_h < high_h){
    //servo turn CW
        watering = 1;
        printer.call(printf, "-------------Watering-----------\n");
        myServo.period_ms(20);
        int drip = 0;
        GPIOD -> ODR |= 0x8;//Blink Green 
        myServo.pulsewidth_us(2500);
        while(drip <= volume){// drips for one decasecond until volume (10ml/sec)
            if(drip%2){
                GPIOD -> ODR |= 0x8;//Blink Green 
            }
             else{
                 GPIOD -> ODR &= ~(0x8);//Blink Green 
             }
             drip ++;
            thread_sleep_for(1000); // 1 decasecond
        }
        volume_lost += volume;
        safe.kick();
        printer.call(printf, "-------------Finished watering-----------\n");
        myServo.pulsewidth_us(500);// servo turn CCW back to original position
        GPIOD -> ODR &= ~(0x8);//Turn Green off
        watering = 0;
    }
    return OK;
}
int init(){
    printer.call(printf, "----Initializing----\n");
    PortB_initialize(10,1); // Rotary Encode Pin1 (input)
    PortB_initialize(11,1); // Rotary Encoder pin 2(input)
    PortD_initialize(3,0); // Watering(output) -Blinking Green
    PortD_initialize(4,0); // Humidity Low (output)- Yellow
    PortD_initialize(5,0); // Humidity Good(output) -GREEN
    PortD_initialize(6,0); // Humidity High(output) - RED
    PortD_initialize(7,0); // User Input(output) - BLUE
    //Interrput functionality
    submitQuery.rise(printer.event(&submit));
    state++;
    return OK;
}
int query(){
    // Prompt user
    GPIOD -> ODR |= 0x10;// Light up Yellow LED
    printer.call(printf, "Input integer value of watering period (hrs)\n");
        while(state==1){
        aVal = DigitalIn(PB_11);
        if(aVal != aPrev){
            safe.kick();// if the encoder is changing, dont restart
            if(DigitalIn(PB_10)!=aVal){
            period++;
            printer.call(printf,"Period(s): %d\n",period); 
            }
            else{
                if(period>1){period--;}// dont go negative
                printer.call(printf,"Period(s): %d\n",period);
            }
        }
        aPrev = aVal;
    }
    printer.call(printf, "Period Inputted: %d\n",period);
    printer.call(printf, "Input integer value of watering volume (ml)\n");
    while(state==2){
        aVal = DigitalIn(PB_11);
        if(aVal != aPrev){
            safe.kick();// if the encoder is changing, dont restart
            if(DigitalIn(PB_10)!=aVal){
                volume++;
                printer.call(printf,"Volume (ml): %d\n",volume); 
            }
            else{
                if(volume>1){
                    volume--;
                }
                printer.call(printf,"Volume (ml): %d\n",volume);
            }
        }
        aPrev = aVal;
    }
    printer.call(printf, "Volume Inputted: %d\n", volume);
    printer.call(printf, "Input cutoff humidity\n");
    while(state==3){
        aVal = DigitalIn(PB_11);
        if(aVal != aPrev){
            safe.kick();// if the encoder is changing, dont restart
            if(DigitalIn(PB_10)!=aVal){
            high_h++;
            printer.call(printf,"Humidity inputted: %d\n",high_h); 
            }
            else{
                if(high_h>1){high_h--;}// Can't go negative
                printer.call(printf,"Humidity inputted: %d\n",high_h);
            }
        }
        aPrev = aVal;
    }
    printer.call(printf, "Humidity:%d\n",high_h);
    GPIOD -> ODR &= ~(0x20);//Turn Yellow LED off
    return OK;
}
int update(){//Read sensor's values, and update corresponfing LEDS
    sensor.read();
    curr_h = sensor.getHumidity();//Update Humidity
    printer.call(printf, "-------------Humidity: %d\n",curr_h);
    if(curr_h>=high_h){// Red LED
        GPIOD -> ODR |= 0x40;
        GPIOD -> ODR &= ~(0x20);
        GPIOD -> ODR &= ~(0x10);
    }
    else if( curr_h<= low_h){//Yellow LED
        GPIOD -> ODR |= 0x10;
        GPIOD -> ODR &= ~(0x40);
        GPIOD -> ODR &= ~(0x20);
    }
    else{ //Green LED
        GPIOD -> ODR |= 0x20;
        GPIOD -> ODR &= ~(0x40);
        GPIOD -> ODR &= ~(0x10);
    }
    // Kick watchdog 
    safe.kick();
    return OK;
}