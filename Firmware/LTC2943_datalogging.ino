/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>

/*End of auto generated code by Atmel studio */


#include <stdint.h>
#include "LTC2943.h"
#include <Wire.h>

//Beginning of Auto generated function prototypes by Atmel Studio
int8_t poll_Ltc2943(int8_t mAh_or_Coulombs, int8_t celcius_or_kelvin, uint16_t prescalar_mode, uint16_t prescalarValue, uint16_t alcc_mode);
//End of Auto generated function prototypes by Atmel Studio

#define LTC2943_PRESCALAR_M_4096 0x30
#define LTC2943_ALERT_MODE 0x04


const float resistor = .024;                               //!< resistor value on demo board

// the setup routine runs once when you press reset:
void setup() {                
  int8_t LTC2943_mode;
  int8_t ack = 0;  
  LTC2943_mode = LTC2943_AUTOMATIC_MODE|LTC2943_PRESCALAR_M_4096|LTC2943_ALERT_MODE ;               //! Set the control register of the LTC2943 to automatic mode as well as set prescalar and AL#/CC# pin values.
  Serial.begin(9600);     
  Serial.println(F("Charge in mAh,Current,Voltage,Temperature"));
  Wire.begin();
  ack |= LTC2943_write(LTC2943_I2C_ADDRESS, LTC2943_CONTROL_REG, LTC2943_mode);   //! Writes the set mode to the LTC2943 control register
}

// the loop routine runs over and over again forever:
void loop() {
    //Serial.println("Alive");
  poll_Ltc2943(1,0,LTC2943_PRESCALAR_M_4096,4096,LTC2943_ALERT_MODE);
}

int8_t poll_Ltc2943(int8_t mAh_or_Coulombs, int8_t celcius_or_kelvin ,uint16_t prescalar_mode, uint16_t prescalarValue, uint16_t alcc_mode)                     
//! @return Returns the state of the acknowledge bit after the I2C address write. 0=acknowledge, 1=no acknowledge.
{                                                         
  int8_t ack = 0; 
   
  Serial.println();                                                               
  
  uint8_t status_code, hightemp_code, lowtemp_code;
  uint16_t charge_code, current_code, voltage_code, temperature_code;
  
  volatile uint16_t ret1;
  
  ack |= LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_ACCUM_CHARGE_MSB_REG, &charge_code);     //! Read MSB and LSB Accumulated Charge Registers for 16 bit charge code
  ack |= LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_VOLTAGE_MSB_REG, &voltage_code);         //! Read MSB and LSB Voltage Registers for 16 bit voltage code
  ack |= LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_CURRENT_MSB_REG, &current_code);         //! Read MSB and LSB Current Registers for 16 bit current code
  ack |= LTC2943_read_16_bits(LTC2943_I2C_ADDRESS, LTC2943_TEMPERATURE_MSB_REG, &temperature_code); //! Read MSB and LSB Temperature Registers for 16 bit temperature code
  ack |= LTC2943_read(LTC2943_I2C_ADDRESS, LTC2943_STATUS_REG, &status_code);                       //! Read Status Register for 8 bit status code
  
  
  float charge, current, voltage, temperature;
  if(mAh_or_Coulombs)
  {
  charge = LTC2943_code_to_coulombs(charge_code, resistor, prescalarValue); //! Convert charge code to Coulombs if Coulomb units are desired.
  Serial.print(charge, 4);
  Serial.print(F(","));
  }
  else
  {
  charge = LTC2943_code_to_mAh(charge_code, resistor, prescalarValue);      //! Convert charge code to mAh if mAh units are desired.
  Serial.print(charge, 4);
  Serial.print(F(","));
  }
  
  current = LTC2943_code_to_current(current_code, resistor);                //! Convert current code to Amperes
  voltage = LTC2943_code_to_voltage(voltage_code);                          //! Convert voltage code to Volts
  
  Serial.print(current, 4);
  Serial.print(F(","));
  
  Serial.print(voltage, 4);
  Serial.print(F(","));
  
  
  if(celcius_or_kelvin){
      temperature = LTC2943_code_to_kelvin_temperature(temperature_code);   //! Convert temperature code to kelvin
      Serial.print(temperature, 4);
      Serial.print(F(","));
  }
  else
  {
      temperature = LTC2943_code_to_celcius_temperature(temperature_code);  //! Convert temperature code to celsius
      Serial.print(temperature, 4);
      Serial.print(F(","));
  }
  
   delay(200);                                      //! Delay for 1s before next polling

}

