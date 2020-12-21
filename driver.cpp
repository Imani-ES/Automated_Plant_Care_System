// Le Farmers
//November 2020
//Project 3: Automated Plant Care System
//This system will help you keep plants alive in your home through the use of technology.
// ** Driver Config **
//Inputs/Outputs:    
// Integers & Serial Moniter
//**Important notes**
// Copyright 2020 Imani Muhammad-Graham

#include "mbed.h"
#include "driver.h"

int find_init_hex(int p_n){// returns friendly input bit configuration in hex for each pin number
    if(p_n == 15){
        return ~(0xC0000000);
    }
    else if(p_n == 14){
        return ~(0x30000000);
    }
    else if(p_n == 13){
        return ~(0xC000000);
    }else if(p_n == 12){
        return ~(0x3000000);
    }else if(p_n == 11){
        return ~(0xC00000);
    }else if(p_n == 10){
        return ~(0x300000);
    }else if(p_n == 9){
        return ~(0xC0000);
    }else if(p_n == 8){
        return ~(0x30000);
    }else if(p_n == 7){
        return ~(0xC000);
    }else if(p_n == 6){
        return ~(0x3000);
    }else if(p_n == 5){
        return ~(0xC00);
    }else if(p_n == 4){
        return ~(0x300);
    }else if(p_n == 3){
        return ~(0xC0);
    }else if(p_n == 2){
        return ~(0x30);
    }else if(p_n == 1){
        return ~(0xC);
    }
    return ~(0x3);
}
int out_hex(int p_n){ // Gives output bit config hex for each pin number
    if(p_n == 15){
        return 0x40000000;
    }
    else if(p_n == 14){
        return 0x10000000;
    }
    else if(p_n == 13){
        return 0x4000000;
    }else if(p_n == 12){
        return 0x1000000;
    }else if(p_n == 11){
        return 0x400000;
    }else if(p_n == 10){
        return 0x100000;
    }else if(p_n == 9){
        return 0x40000;
    }else if(p_n == 8){
        return 0x10000;
    }else if(p_n == 7){
        return 0x4000;
    }else if(p_n == 6){
        return 0x1000;
    }else if(p_n == 5){
        return 0x400;
    }else if(p_n == 4){
        return 0x100;
    }else if(p_n == 3){
        return 0x40;
    }else if(p_n == 2){
        return 0x10;
    }else if(p_n == 1){
        return 0x4;
    }
    return 0x1;
}
int PortA_initialize(int p_n,bool i_o){// Initialization function for Port A
    RCC -> AHB2ENR |= 0x1;// Enable port A
    GPIOA -> MODER &= find_init_hex(p_n); // set as initial (00)
    if(!i_o){
        GPIOA -> MODER |= out_hex(p_n); // if bool is output, add a 1 to get (01)
    }
    return 0; // return 0 to avoid memory loss 
}
int PortB_initialize(int p_n,bool i_o){// Initialization function for Port B
    RCC -> AHB2ENR |= 0x2;// Enable port B
    GPIOB -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOB -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}
int PortC_initialize(int p_n,bool i_o){// Initialization function for Port C
    RCC -> AHB2ENR |= 0x4;// Enable port C
    GPIOC -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOC -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}
int PortD_initialize(int p_n,bool i_o){// Initialization function for Port D
    RCC -> AHB2ENR |= 0x8;// Enable port D
    GPIOD -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOD -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}
int PortE_initialize(int p_n,bool i_o){// Initialization function for Port E
    RCC -> AHB2ENR |= 0x10;// Enable port E
    GPIOE -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOE -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}
int PortF_initialize(int p_n,bool i_o){// Initialization function for Port F
    RCC -> AHB2ENR |= 0x20;// Enable port F
    GPIOF -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOF -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}
int PortG_initialize(int p_n,bool i_o){// Initialization function for Port G
    RCC -> AHB2ENR |= 0x40;// Enable port G
    GPIOG -> MODER &= find_init_hex(p_n);// set as initial (00)
    if(!i_o){
        GPIOG -> MODER |= out_hex(p_n);// if bool is output, add a 1 to get (01)
    }
    return 0;
}