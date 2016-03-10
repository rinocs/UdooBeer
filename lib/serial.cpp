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



using namespace std;
static const char *PORT_NAME = "/dev/ttyMCC";
/*
 * 'open_port()' - Open serial port 1.
 *
 * Returns the file descriptor on success or -1 on error.*/

int SerialUdoo::set_interface_attribs (int fd, int speed, int parity){

        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                cout<<"error from tcgetattr"<< errno<<endl;
                return -1;
        }

        cfsetospeed (&tty, speed);
        cfsetispeed (&tty, speed);

        tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
        // disable IGNBRK for mismatched speed tests; otherwise receive break
        // as \000 chars
        tty.c_iflag &= ~IGNBRK;         // ignore break signal
        tty.c_lflag = 0;                // no signaling chars, no echo,
                                        // no canonical processing
        tty.c_oflag = 0;                // no remapping, no delays
        tty.c_cc[VMIN]  = 0;            // read doesn't block
        tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

        tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

        tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
                                        // enable reading
        tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
        tty.c_cflag |= parity;
        tty.c_cflag &= ~CSTOPB;
        tty.c_cflag &= ~CRTSCTS;

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
        {
                cout<<"error "<<errno<<"from tcsetattr"<<endl;
                return -1;
        }
        return 0;
}

void SerialUdoo::set_blocking (int fd, int should_block){
        

        struct termios tty;
        memset (&tty, 0, sizeof tty);
        if (tcgetattr (fd, &tty) != 0)
        {
                cout<<"error"<<errno<< "from tggetattr"<<endl;
                return;
        }

        tty.c_cc[VMIN]  = should_block ? 1 : 0;
        tty.c_cc[VTIME] = 5;                // 0.5 seconds read timeout

        if (tcsetattr (fd, TCSANOW, &tty) != 0)
                cout<<"error "<< errno<<" setting term attributes"<<endl;
}



 int SerialUdoo::write_port(int bytes,char *context) {
  

  int fd; /* File descriptor for the port */


  fd = open(PORT_NAME, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
   /* Could not open the port. */
    perror("open_port: Unable to open /dev/ttyMCC - ");
  }
  else
    fcntl(fd, F_SETFL, 0);

  int n = write(fd, context, bytes);
  if (n < 0)
    fputs("write() of 4 bytes failed!\n", stderr);

  return (fd);
}




int SerialUdoo::read_port(char *buffer, int fd){

   /*  int fd = open(PORT_NAME, O_RDONLY | O_NOCTTY);
    if (fd == -1)
    {
        /* Could not open the port. */
      /*  perror("open_port: Unable to open /dev/ttyMCC - ");
    } */

    
    int n = read(fd, buffer, sizeof(buffer));
    if (n < 0)
        fputs("read failed!\n", stderr);
    return (fd);
}


int SerialUdoo::open_port(void){


  int fd; /* File descriptor for the port */


  fd = open(PORT_NAME, O_RDWR | O_NOCTTY | O_NDELAY);
  if (fd == -1)
  {
   /* Could not open the port. */
    perror("open_port: Unable to open /dev/ttyS0 - ");
  }
  else
    fcntl(fd, F_SETFL, 0);


        return (fd);



}










