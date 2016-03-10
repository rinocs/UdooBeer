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
#include "udooSensor.h"
using namespace std;

int main (){

	float temp;
	float press;
	float alt;
	int i;
	int FD;

	udooSensor *sensore;
	sensore= new udooSensor;


	FD=sensore-> udooSensor_INIT(0x60);
	





	sensore->GetRawData(FD,0x60);
	sensore->SetTemperature(FD,0x60);
	sensore->SetPressure_ALT(FD,0x60);
	temp=sensore->getTemperature();
	press=sensore->getPressure();
	alt=sensore->getAltimeter();


	cout<<"temperatura:"<<temp<<endl;
	cout<<"pressione:"<<press<<endl;
	cout<<"altezza:"<<alt<<endl;



		

	sensore->udooSensor_EXIT(FD);



	return 0;
















}
