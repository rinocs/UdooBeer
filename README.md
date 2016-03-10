# UdooBeer
fermentation process monitor with web site control.

Authors: Nocella Riccardo && Bigiotti Luciano.

>Description.

This project is build on Udoo neo ,you can find something about this board on [http://www.udoo.org/docs-neo/Introduction/Introduction.html].
We use this board to build a fermentation process monitor where we can 


>Instructions.

  -install something for our web server , follows the guide udoo official web site  at this [link]          [http://www.udoo.org/tutorial/udoo-web-server/ ].

  -create a database  "dati" with phpmyadmin. 

  -rename "UdooBEER-site " in "UdooBEER" and copy it in /var/www/ .

  -build : g++ -o monitor monitor_ABS.cpp lib/serial.cpp lib/udooSensor.cpp .
  
  - launch the program in the terminal.
  
  

WORK IN PROGRESS ... .
