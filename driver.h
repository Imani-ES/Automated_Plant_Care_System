// Le Farmers
//November 2020
//Project 3: Automated Plant Care System
//This system will help you keep plants alive in your home through the use of technology.
// ** Driver Config **
//Inputs/Outputs:    
// Integers & Serial Moniter
//**Important notes**
// Copyright 2020 Imani Muhammad-Graham
#ifndef driver_H
#define driver_H
 
#include "mbed.h"
  
/** Class for Driver functions
 * 
 * Example:
 * @code
 * #include "mbed.h"
 * #include "driver.h"
 *
 * int main() {
 *     PortE_initialize(14,1);// Pin PE_14 as input
 * }
 * @endcode
 */
 int PortA_initialize(int p_n,bool i_o);// Initialization function for Port A
    int PortB_initialize(int p_n,bool i_o);// Initialization function for Port B
    int PortC_initialize(int p_n,bool i_o);// Initialization function for Port C
    int PortD_initialize(int p_n,bool i_o);// Initialization function for Port D
    int PortE_initialize(int p_n,bool i_o);// Initialization function for Port E
    int PortF_initialize(int p_n,bool i_o);// Initialization function for Port F
    int PortG_initialize(int p_n,bool i_o);// Initialization function for Port G
    
    /** Helper functions setting input ant output bits
     *
     * @returns
     *   hex value for GPIO MODERs
     */
    int find_init_hex(int p_n);//helper function sets the pin to input initially
    int out_hex(int p_n);// helper function that gives output hex bit
class driver
{
public:
    /** GPIO Initialization Functions for each Port
     *
     * @param pin PinName for the sensor pin.
     * @param bool 1 for input, 0 for output
     */
    int PortA_initialize(int p_n,bool i_o);// Initialization function for Port A
    int PortB_initialize(int p_n,bool i_o);// Initialization function for Port B
    int PortC_initialize(int p_n,bool i_o);// Initialization function for Port C
    int PortD_initialize(int p_n,bool i_o);// Initialization function for Port D
    int PortE_initialize(int p_n,bool i_o);// Initialization function for Port E
    int PortF_initialize(int p_n,bool i_o);// Initialization function for Port F
    int PortG_initialize(int p_n,bool i_o);// Initialization function for Port G
    
    /** Helper functions setting input ant output bits
     *
     * @returns
     *   hex value for GPIO MODERs
     */
    int find_init_hex(int p_n);//helper function sets the pin to input initially
    int out_hex(int p_n);// helper function that gives output hex bit
 
private:
    const bool input = 1; // input is 1
    const bool outpt = 0;// out put is 0
};
 
#endif