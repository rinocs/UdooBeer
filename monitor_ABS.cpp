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

    
#include <stdlib.h>
#include <unistd.h>/* UNIX standard function definitions */
#include <math.h>
#include "birra.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cstdio>   /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <algorithm>
#include "lib/serial.h"
#include "lib/udooSensor.h"
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */

using namespace std;



int main ()  {

	float temp,press;
    float alcohol_val;
    int FD_u;  
	int control,FD_a;
	char buffer_alcohol[7];
	float gradazione;
	float BAC;
	float percentage;

	/*########## unmount kernel module of sensor mpl3115 to take control ######### */

	system ("rmmod mpl3115"); 
	
	Birra *peroni;
	peroni = new Birra();

	udooSensor *sensore_udoo;
	sensore_udoo = new udooSensor;

	SerialUdoo *comunication ;
	comunication = new SerialUdoo;



	/*###########-sensorUDOO init-#############*/
	FD_u=sensore_udoo-> udooSensor_INIT(0x60);

	/*################ init serial comunication ############ */
	FD_a=comunication->open_port();
	control=comunication->set_interface_attribs(FD_a,B115200,0);
	if (control!=0 ){

		perror("impossibile settari gli attributi \n ");
	}

	comunication->set_blocking (FD_a, 0);
	
	/*############### init gpio led ##############à*/
	system("echo 18 > /sys/class/gpio/export");
	system("echo out > /sys/class/gpio/gpio18/direction");
	
	
	
	
	
	
	
	/*############- build the file path  -####################*/
	srand (time(NULL));
	
	time_t dataCorrente=time(NULL);
	struct tm *strutturaData=localtime(&dataCorrente);
	char fileName[50];
	strftime(fileName , 50 , "%d-%m-%Y.csv" , localtime(&dataCorrente));
	
	string path= "/var/www/udooBEER/csv/";
	string temp_file;
	temp_file.assign(fileName);
	string PATH_FILE= path + temp_file	;
	
	 
	const char *FILE=PATH_FILE.c_str();
	
	
	/*######## open stream + control ######### */
	ifstream check(FILE);
	//cout<<strerror(errno);
	if (check){
	cout <<"THE FILE EXIST\n\n"<<endl;
	
		ofstream outline;
			//cout<<strerror(errno);
			outline.open(FILE,ios::app);
			 //se il file non esiste lo crea, altrimenti lo sovrascrive!
			if(!outline.is_open()) {
				cout<<"Errore nella creazione del file!   1"<<endl;
				return -1;
				}
			/* ######   initialize the  recevitor ########*/ 
			while(1){
			
			time_t t = time(NULL); // return  hour
			tm *tempo;
			tempo = localtime(&t);
			

			/* ######### read data in the sensor object ################*/
			sensore_udoo->GetRawData(FD_u,0x60);
			sensore_udoo->SetTemperature(FD_u,0x60);
			sensore_udoo->SetPressure_ALT(FD_u,0x60);
			temp=sensore_udoo->getTemperature();
			press=sensore_udoo->getPressure();
			
			
			do{	
					FD_a=comunication->read_port(buffer_alcohol,FD_a);
					alcohol_val=atof(buffer_alcohol);	

		   } while(alcohol_val > 1023.0  );
		   
		   cout<< "sensore alcohol:"<<alcohol_val<<endl;
		   
		   percentage= alcohol_val/1023.0;
		   BAC=percentage * 0.21;

		   if ( BAC < 0.10 ){

			gradazione=0;


		}else if ( BAC >= 0.10  && BAC <= 0.12){


			gradazione=3.5;

		}else if ( BAC > 0.12 && BAC <= 0.14 ){

			gradazione=5.5;

		}else if ( BAC > 0.14 && BAC<= 0.16    ){

			gradazione=8;


		}else if ( BAC > 0.16 && BAC <= 0.17 ){

			gradazione=10;

		}else if ( BAC > 0.17 && BAC <= 0.18 ) {

			gradazione=20;


		}else if( BAC > 0.20 && BAC <= 0.21 ) {
			gradazione=30.5;

		}else gradazione=40.5;



			
	
			/*################ DATA SET in beer object #####################*/
	
			peroni->Set_Alcohol(gradazione);
			peroni->Set_Temperature(temp);
			peroni->Set_Pressure(press);
	
			
			cout<<"Temperatura:" << peroni->Get_Temperature()<<"\n";
			cout<<"Pressione:" << peroni->Get_Pressure()<<"\n";
			cout<<"Alcohol:" <<peroni->Get_Alcohol()<<"\n";

			/*#########  write on csv file ################### */
			
			
				
				outline<< peroni->Get_Temperature()<<","<<peroni->Get_Alcohol()<<","<<peroni->Get_Pressure()<< ","<<tempo->tm_hour<<","<<tempo->tm_min<<","<<tempo->tm_sec<<","<<tempo->tm_mday<<"/"<<tempo->tm_mon + 1<<"/"<<tempo->tm_year + 1900 <<endl; //si può inserire qualsiasi cosa nello stream, stringhe

				cout<<"Scrittura avvenuta con successo! \n\n";
    
				
    
				if (peroni->Get_Temperature() < 22  ){
					
					system ("echo 1 >/sys/class/gpio/gpio18/value");
					
					}else {
						
						system ("echo 0 >/sys/class/gpio/gpio18/value");
						
						}
			
				
				sleep(1);
						
			}

			/*############## CLOSE THE FILE ################*/
			outline.close();
			
		}else{
	
			/*########## open the file where i write data to database ##############*/
			ofstream outline;
			//cout<<strerror(errno);
			outline.open(FILE,ios::out);
			
			if(!outline.is_open()) {
				cout<<"error to create file"<<endl;
				return -1;
				}
				
			outline<<"Temperature: "<<","<<"Alcohol:"<<","<<"Pressure:"<<","<<"Hour: "<<","<<"Minute:"<<","<<"Second:"<<","<<"Date:(Y.M.D) "<<endl;
			
		
		 
			while(1){
			
			time_t t = time(NULL); 
			tm *tempo;
			tempo = localtime(&t);
			
			
			
			/* ######### read data in the sensor object ################*/
			
			sensore_udoo->GetRawData(FD_u,0x60);
			sensore_udoo->SetTemperature(FD_u,0x60);
			sensore_udoo->SetPressure_ALT(FD_u,0x60);
			temp=sensore_udoo->getTemperature();
			press=sensore_udoo->getPressure();
			
			
			
			do {
				
			FD_a=comunication->read_port(buffer_alcohol,FD_a);
			alcohol_val=atof(buffer_alcohol);	

		   }while(alcohol_val < 100.0 && alcohol_val > 1023  );	

			cout<< "sensore alcohol:"<<alcohol_val<<endl;
		   
		   percentage= alcohol_val/1023.0;
		   BAC=percentage * 0.21;

		
		   if ( BAC < 0.10 ){

			gradazione=0;


		}else if ( BAC >= 0.10  && BAC <= 0.12){


			gradazione=3.5;

		}else if ( BAC > 0.12 && BAC <= 0.14 ){

			gradazione=5.5;

		}else if ( BAC > 0.14 && BAC<= 0.16    ){

			gradazione=8;


		}else if ( BAC > 0.16 && BAC <= 0.17 ){

			gradazione=10;

		}else if ( BAC > 0.17 && BAC <= 0.18 ) {

			gradazione=20;


		}else if( BAC > 0.20 && BAC <= 0.21 ) {
			gradazione=30.5;

		}else gradazione=40.5;

			
			
	
		/*################ DATA SET in beer object #####################*/
	
			peroni->Set_Alcohol(gradazione);
			peroni->Set_Temperature(temp);
			peroni->Set_Pressure(press);

	
		 
			cout<<"Temperatura:" << peroni->Get_Temperature()<<"\n";
			cout<<"Pressione:" << peroni->Get_Pressure()<<"\n";
			cout<<"Alcohol:" <<peroni->Get_Alcohol()<<"\n";
	
			/*#########  write on csv file ################### */
			outline << peroni->Get_Temperature()<<","<<peroni->Get_Alcohol()<<","<<peroni->Get_Pressure()<< ","<<tempo->tm_hour<<","<<tempo->tm_min<<","<<tempo->tm_sec <<","<<tempo->tm_mday<<"/"<<tempo->tm_mon + 1<<"/"<<tempo->tm_year + 1900 <<endl; //si può inserire qualsiasi cosa nello stream, stringhe

	
			cout<<"Scrittura avvenuta con successo! \n\n";
    
		
				if (peroni->Get_Temperature() < 22  ){
								 
					system ("echo 1 >/sys/class/gpio/gpio18/value");
					
					}else {
						
						system ("echo 0 >/sys/class/gpio/gpio18/value");
						
						}
					
			
			sleep(1);
		
		}
		/*############## CLOSE THE FILE ################*/
		outline.close();
		}
	
	
	sensore_udoo->udooSensor_EXIT(FD_u);
	
	check.close();
	delete &sensore_udoo;
	delete peroni;
    //delete sensore;
	//delete alcohol;
	

	return 0;
}
