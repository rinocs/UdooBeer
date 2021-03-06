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


#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stdlib.h>




class SerialUdoo{



		public:



		
			int set_interface_attribs (int fd, int speed, int parity);
			void set_blocking (int fd, int should_block);
			int open_port(void);
			int read_port(char *buffer, int fd);
			int write_port(int bytes,char *context);




};




#endif  