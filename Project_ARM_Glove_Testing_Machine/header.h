/* 
 * File:   header.h
 * Author: ccsn
 *
 * Created on January 9, 2016, 9:09 PM
 */

#ifndef HEADER_H
#define	HEADER_H

typedef struct Test_Setting_Tag
{
	unsigned char Gloves_Size;						//65,70,75,80,85
	unsigned char Inflate_time_1;				//For time settings Range 0 to 10
	unsigned char Inflate_time_2;				//For time settings Range 0 to 10
	unsigned char Air_eject_time_for_good;			//Eject time to push good glove to bin
	unsigned char Air_eject_time_for_bad;			//Eject time to push bad glove to bin
}testspec;
testspec glove;
typedef struct Pressure_Setting_Tag
{
	unsigned int Upper_Threshold;				//Setting for glove rejection criteria
	unsigned int Lower_Threshold;				//Setting for glove rejection criteria
	unsigned int Nominal_Pressure;				//Setting for glove rejection criteria
	unsigned int Positive_Tolerance;			//Setting for glove rejection criteria
	unsigned int Negative_Tolerance;			//Setting for glove rejection criteria
}pressurespec;

pressurespec value;
typedef struct Sensor_Data_To_Send_Tag
{
	unsigned int sensor_offset;			//Initial pressure read before air filled
	unsigned int sensor_P1;				//Pressure 1 for test 1
	unsigned int sensor_P2;				//Pressure 2 for test 2
	unsigned int sensor_P3;				//Pressure 3 for test 3
	unsigned int sensor_P4;				//Pressure 4 for test 4
	unsigned char sensor_Status;		//Status of the sensor shown in enum Sensor_Status
}sensordata;

sensordata sensor[4];

#endif	/* HEADER_H */

