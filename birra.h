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




#ifndef BIRRA_H
#define BIRRA_H

class Birra{

	private:
		float temperature;
		float alcohol;
		float pressure;

	public:
		/* definisco i prototipi*/
		Birra();
		~Birra();
		//~Birra(Birra *elem);
		float Get_Temperature() const;
		float Get_Pressure() const;
		float Get_Alcohol() const;
		void Set_Temperature(float _temperature);
		void Set_Pressure(float _pressure);
		void Set_Alcohol(float _alcohol);
};

/*
class Sensor_temperature{

	private:
		float temperature;
	public:
		Sensor_temperature();
		~Sensor_temperature();
		void Random_temp();
		float Get_sensor_temp() const;

};

	
class Sensor_Alcohol{

	private:
		float alcohol;
	public:
		Sensor_Alcohol();
		~Sensor_Alcohol();
		void Random_alcohol();
		float Get_sensor_alcohol() const;

};

*/



#endif
