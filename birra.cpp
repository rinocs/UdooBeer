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


#include "birra.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <iostream>
using namespace std;

/*######################## BIRRA MODULE DECLARATION ############## */
 		Birra::Birra(){
			temperature=0;
			pressure=0;
			alcohol=0;

			}
		Birra::~Birra(){

			cout<< "fine lavoro";
			
		}
		float Birra::Get_Temperature() const{

			return temperature;
			}

		float Birra::Get_Pressure() const{

			return pressure;
			}

		float Birra::Get_Alcohol() const{

			return alcohol;
			}

		void Birra::Set_Temperature(float _temperature){

			temperature=_temperature;


			}

		void Birra::Set_Pressure(float _pressure){

			pressure=_pressure;


			}

		void Birra::Set_Alcohol(float _alcohol){

			alcohol=_alcohol;


			}
			

