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

#ifndef UDOO_SENSOR_H
#define UDOO_SENSOR_H

#include <stdint.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/types.h>
#include <linux/i2c-dev.h>
#include <sys/stat.h>
#include <iostream>
static int fd;// file descriptor
static const char *PATH_DEV = "/dev/i2c-1"; //pathname del device


class udooSensor{

		private: 
				  float temperature;
				  float pressure;
				  float altimeter;
		public:

			 
			 static const unsigned int I2C_ADDRESS = 0x60;
			
			 static const unsigned int I2C_ADDRESS_ALT = 0xc0;
			 static const unsigned int status=0x00;
			 static const unsigned int pressure_MSB=0x01;
			 static const unsigned int pressure_CSB=0x02;
			 static const unsigned int pressure_LSB=0x03;
			 static const unsigned int temperature_MSB=0x04;
			 static const unsigned int temperature_LSB=0x05;
			 static const unsigned int PT_Data_Config_Reg=0x13;
			 static const unsigned int CTRL_REG1=0x26;

					 

		/*  ######### Prototipi funzioni ############ */
			
		udooSensor(){
			temperature=0;
			pressure =0;
		};		
		
		/*~udooSensor(){

			Close();

		};*/

		int udooSensor_INIT(unsigned int I2C_ADDR);
		void GetRawData(int fd, unsigned int I2C_ADDR);
		void SetTemperature(int fd, unsigned int I2C_ADDR);
		void SetPressure_ALT(int fd, unsigned int I2C_ADDR);
		float getTemperature();
		float getPressure();
		float getAltimeter();
		void udooSensor_EXIT(int fd);



};



#endif  

