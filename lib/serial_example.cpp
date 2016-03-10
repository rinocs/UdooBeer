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


#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <iostream> 
#include "serial.h"
#include <cstdio>



using namespace std;


int main (){

	SerialUdoo *comunication ;
	comunication = new SerialUdoo;
	int control,FD;
	char buffer[10];

	FD=comunication->open_port();
	control=comunication->set_interface_attribs(FD,B115200,0);
	if (control!=0 ){


		perror("impossibile settari gli attributi \n ");
	}

	
	comunication->set_blocking (FD, 0);
	FD=comunication->read_port(buffer);

	cout<<"ho letto : "<<buffer<<endl;

		

	return 0;

}