/*
    
    Copyright (C) <2016>  <Luciano Bigiotti && Riccardo Nocella>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/





#include <iostream>
#include <cstdio>
#include <math.h>
#include "udooSensor.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;
//  ###############      IMPLEMENTO LE FUNZIONI ################### //



static uint8_t buffer_Temp[2]; 	 	/*buffer used to read temperature(MSB, LSB)*/
static uint8_t buffer_Press[3];  	/*buffer used to read pressure(MSB,CSB,LSB)*/
static __s32 STATUS;		     	/*include Sensor Status Register (0x00)*/
static int16_t data_order;		 	/*variable for the bit reordering */
static int32_t data_order1;		 	/*variable for the bit reordering*/
static int16_t CSB_BIT;			 	/*contain  CSB bit of pressure*/
static int16_t LSB_BIT;			 	/*contain LSB bit  of pressure */
static const double p0 = 101326; 	/* pressure at the sea */



		int udooSensor::udooSensor_INIT(unsigned int I2C_ADDR){

			 fd=0;
			 /* check if the device is connected to the board */

    		 if ((fd = open(PATH_DEV , O_RDWR)) < 0 ){
				 cout<<fd<<endl;
			 	 perror("Can't find the device\n");
			 	 exit(1);
    		 }
    		
    		/* check the comunication with the connected device */	
    		 if ((ioctl(fd, I2C_SLAVE, I2C_ADDR)) < 0){
				 perror("Can't talk with the device\n");
			 	 exit(1);
			 }
	
			if (I2C_ADDR==udooSensor::I2C_ADDRESS){
				
		 
	    	 	/* Enable Data Flags in PT_DATA_CFG */
		 	 	i2c_smbus_write_word_data(fd, udooSensor::PT_Data_Config_Reg, 0x07); 
			
        	 	/*  Set One Shot *//* Set Active */
		 	 	i2c_smbus_write_word_data(fd, udooSensor::CTRL_REG1, 0xB9);
			}
	
    	return fd;


		};



		void udooSensor::GetRawData(int fd, unsigned int I2C_ADDR){


			 cout << "Reading from "<< PATH_DEV << " at address: 0x"<<  I2C_ADDR <<endl;
	 
			 if(I2C_ADDR==udooSensor::I2C_ADDRESS){ 
		
			 /* the data oversampling ratio, High Resolution Mode, oversample = 128 */
			i2c_smbus_write_word_data(fd, udooSensor::CTRL_REG1, (0x38 | 0x01 | 0x00));
		
			STATUS = 0;
		

			/* check DATA is available on the bus  */
			do{												 
					STATUS = i2c_smbus_read_byte_data(fd, udooSensor::status); 
			} while((STATUS & 0x08) == 0);					 
		
				
			buffer_Press[0] = i2c_smbus_read_word_data(fd, udooSensor::pressure_MSB); //pressure_MSB
			buffer_Press[1] = i2c_smbus_read_word_data(fd, udooSensor::pressure_CSB); //pressure_CSB
			buffer_Press[2] = i2c_smbus_read_word_data(fd, udooSensor::pressure_LSB); //pressure_LSB
						
			cout<<"Pressure raw data get from register: 0x"<< buffer_Press[0]<<buffer_Press[1]<< buffer_Press[2]<<endl;
		
			buffer_Temp[0] = i2c_smbus_read_word_data(fd, udooSensor::temperature_MSB); //temperature_MSB
			buffer_Temp[1] = i2c_smbus_read_word_data(fd, udooSensor::temperature_LSB); //temperature_LSB
		

			cout<<" Temperature raw data get from register: 0x"<< buffer_Temp[0]<<buffer_Temp[1]<<endl;
			
	 	}
		 else
			perror("ERROR\n");

			};




		void udooSensor::SetTemperature(int fd, unsigned int I2C_ADDR){


		
			
	
			if (I2C_ADDR== udooSensor::I2C_ADDRESS){
			
							i2c_smbus_write_word_data(fd, udooSensor::CTRL_REG1, (0x38 | 0x01 | 0x00));
			
							STATUS = 0;
			
							do{												 //Verifica che i
								STATUS = i2c_smbus_read_byte_data(fd,udooSensor::status); //dati siano disponibili
								} while((STATUS & 0x08) == 0); 		

											 //sul bus
							buffer_Temp[0] = i2c_smbus_read_word_data(fd, udooSensor::temperature_MSB);  //T_MSB
							buffer_Temp[1] = i2c_smbus_read_word_data(fd, udooSensor::temperature_LSB);  //T_LSB
							
							//riordino i bit per la temperatura
							data_order =  buffer_Temp[0];		
							data_order = data_order << 8; //SLL
             
							data_order = data_order | buffer_Temp[1]; // OR inclusivo
							data_order = data_order >> 4; //SRL
					

							udooSensor::temperature  = data_order * 0.062500;
							cout << "Decimal temperature value:"<< data_order <<endl;
							cout<<"The temperature is: "<< udooSensor::temperature<<"°C"<<endl ;
		
			}else{ 
						perror("ERROR\n");
				}		

		}; 




		void udooSensor::SetPressure_ALT(int fd, unsigned int I2C_ADDR){

				float pressure;float alt;
				if(I2C_ADDR==udooSensor::I2C_ADDRESS){

							if (read(fd, buffer_Temp, 3) != 3 ){
								perror("Can't read from bus i2c");
								exit(1);
							} 
							i2c_smbus_write_word_data(fd, udooSensor::CTRL_REG1, (0x38 | 0x01 | 0x00));
			
							STATUS = 0;
			
							do{												 //Verifica che i
									STATUS = i2c_smbus_read_byte_data(fd, udooSensor::status); //dati siano disponibili
								} while((STATUS & 0x08) == 0); 					 //sul bus
					
							buffer_Press[0] = i2c_smbus_read_word_data(fd, udooSensor::pressure_MSB); //P_MSB
							buffer_Press[1] = i2c_smbus_read_word_data(fd, udooSensor::pressure_CSB); //P_CSB
							buffer_Press[2] = i2c_smbus_read_word_data(fd, udooSensor::pressure_LSB); //P_LSB	
			
								//riordino i bit per la pressione
							data_order1=0;
							pressure = 0.0;
			
							data_order1 = buffer_Press[0];
							data_order1 <<= 12;
						
							CSB_BIT = buffer_Press[1];
							CSB_BIT <<= 4;
							data_order1 |= CSB_BIT;
			
							LSB_BIT = buffer_Press[2];
							LSB_BIT >>= 4;
							data_order1 |= LSB_BIT;
						
							pressure = data_order1 * 0.00025; // Moltipiplicare per il fattore  di scala (0.00025)
								       // per ottenere kPa	
	
							udooSensor::pressure=pressure;

							cout<<"Decimal pressure value: "<< data_order1<<endl;
							cout<<"The pression is: "<<pressure<<"kpa"<<endl;
			
							alt = 44330.77*(1- pow((((pressure)*1000)/p0),0.1902632));  
							udooSensor::altimeter=alt;
							cout<<"The height is:"<< alt<<"m"<<endl;
					
			

				}else{

					perror("ERROR\n");


				}


		};
		float udooSensor::getTemperature(){

			return temperature;

		};


		float udooSensor::getPressure(){

			return pressure;

		};
		float udooSensor::getAltimeter(){

			return altimeter;



		};
		void udooSensor::udooSensor_EXIT(int fd){


				if(close(fd) < 0){
   				     cout<<"ERROR!!!"<<endl;
   					  
   					  }else{	
				
				cout<<"Successfully completed"<<endl;
		     }	

		};
