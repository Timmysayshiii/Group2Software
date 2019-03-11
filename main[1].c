#include <stdio.h>
#include <string.h>
#include <math.h>

#include "TExaS.h"
#include "uart.h"
#include "PLL.h"
#include "PortInit.h"
#include "UART1.h"
#include "Heading.h"
#define a 6378137.0 //earth equatorial radius (wgs84 standard)
#define flattening 0.00335281 //flattening factor of ellipsoid (f = 1/298.257223563)
#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
#define ecc 0.08181918275 //eccentricity (e^2 = 2f - f^2)
#define Pi 3.14159265358979323846

	void storeLatitude(void);
	void storeLongitude(void);
	void storeAltitude(void);
	void storeCartesian(void);
	void parseSentence(void);
	double convertWholeNumber(void);
	void findStream(void);
	
	long double latitudedegrees, latitudeminutes, latmin123456, cartesianX, cartesianY, cartesianZ, N;
	long double longitudedegrees, longitudeminutes, altitudemeters, latituderadians, longituderadians;
	int x=0, z=0, t=0;
	char latitudefromstream[14], altitudefromstream[8];
	char latdegrees[2], longdegrees[3], altmeters[5];
	char latminutes[10], longminutes[10];
	char longitudefromstream[15];
	char *pointer, *latpointer;
	char nmeasentence[77] = {'$','G','P','G','G','A',',','0',
		                       '9','2','7','2','5','.','0','0',
		                       ',','4','7','1','7','.','1','1',
		                       '3','9','9','0','1',',','N',',',
		                       '0','0','8','3','3','.','9','1',
		                       '5','9','0','0','0',',','E',',',
		                       '1',',','0','8',',','1','.','0',
		                       '1',',','4','9','9','.','6',',',
	                         'M',',','4','8','.','0',',','M',
	                         ',',',','*','5','B',};
						
 char nmeasentence2[77]=("$GNGGA,151839.00,5348.53615,N,00133.41962,W,1,12,0.70,91.6,M,47.8,M,,*61");
////////////////////////////////////////////////////////////////////////////////				
													 
int main(void){
	PLL_Init();	     //Initialise the PLL
	SysTick_Init();  //Initialise the Systick
	UART_Init();     //Initialise UART
	printf("START 2");
	//UART1_Init();    //Initalise UART1 
	//UART2_Init();
  //UART3_Init();
  //UART5_Init();
//printf(" \n START 2 ");
 
	

//	while(1){
//	//unsigned char temp1= UART1_InChar();
//	//unsigned char temp2= UART2_InChar();
//	//unsigned char temp3= UART3_InChar();
//		
//	unsigned char temp5= UART5_InChar();
//  //printf("%c", temp1);
//	printf("%c", temp5);
//	}
		
	printf("\n\nProgram Start");
	
  pointer = nmeasentence2;
	
	printf("\n\nNmea sentence to decode = ");
	for(int i=0; i<77; i++){
		printf("%c", nmeasentence2[i]);
}
	printf("\n\nPointer of Nmea sentence to decode = ");
	for(int i=0; i<77; i++){
		printf("%c", pointer[i]);
	}
	
	float bearing = Bearing_calc(52.56,72.95,42.521,49.85);
	
	findStream();
	
	printf(" \n\n bearing = %f",bearing);
	
	printf("\n\nProgram End");
	
}


///////////////////////////////////////////////////////////////////////////////

void storeLatitude(){
  for(int i=0; i<14; i++){
	latitudefromstream[x] = nmeasentence2[x+17];
	x = x+1;
	}
	
	printf("\n\nLatitude of stream = ");
	for(int i=0; i<14; i++){
		printf("%c", latitudefromstream[i]);
	}
	
	latdegrees[0] = latitudefromstream[0];
	latdegrees[1] = latitudefromstream[1];
	
	printf("\n\nLat degrees = ");
	for(int i=0; i<2; i++){
		printf("%c", latdegrees[i]);
	}
	
	latitudedegrees = (latdegrees[1]-'0') + ((latdegrees[0]-'0')*10.0);
	printf("\n\nLatitude degrees whole number = %Lf", latitudedegrees);
	
	latminutes[0] = latitudefromstream[2];
	latminutes[1] = latitudefromstream[3];
	latminutes[2] = latitudefromstream[4];
	latminutes[3] = latitudefromstream[5];
	latminutes[4] = latitudefromstream[6];
	latminutes[5] = latitudefromstream[7];
	latminutes[6] = latitudefromstream[8];
	latminutes[7] = latitudefromstream[9];
	latminutes[8] = latitudefromstream[10];
	latminutes[9] = latitudefromstream[11];

	
	printf("\n\nlatminutes1 = %c", latminutes[0]);
	printf("\nlatminutes2 = %c", latminutes[1]);
	printf("\nlatminutes3 = %c", latminutes[2]);
	printf("\nlatminutes4 = %c", latminutes[3]);
	printf("\nlatminutes5 = %c", latminutes[4]);
	printf("\nlatminutes6 = %c", latminutes[5]);
	printf("\nlatminutes7 = %c", latminutes[6]);
	printf("\nlatminutes8 = %c", latminutes[7]);
	printf("\nlatminutes9 = %c", latminutes[8]);
	printf("\nlatminutes10 = %c", latminutes[9]);
	
	printf("\n\nLat minutes = ");
	for(int i=0; i<11; i++){
		printf("%c", latminutes[i]);
	}
	
	latitudeminutes = ((latminutes[1]-'0') + ((latminutes[0]-'0')*10.0)) + ((latminutes[5]-'0')/10000000.0)+((latminutes[8]-'0')/1000000.0)+((latminutes[7]-'0')/100000.0)+((latminutes[6]-'0')/10000.0)+((latminutes[5]-'0')/1000.0)+((latminutes[4]-'0')/100.0)+((latminutes[3]-'0')/10.0);
	printf("\n\nLatitude minutes whole number = %Lf", latitudeminutes);
	
	latitudeminutes = latitudeminutes / 60.0;
	printf("\n\nLatitude minutes whole number / 60 = %Lf", latitudeminutes);
	
	latitudedegrees = latitudedegrees + latitudeminutes;
	printf("\n\nLatitude degrees final number = %Lf", latitudedegrees);
	
	if(latitudefromstream[13] == 'S'){
		latitudedegrees = latitudedegrees * -1;
	  printf("\n\nLatitude degrees final number with south = %Lf", latitudedegrees);
  }
	
}

void storeLongitude(){
  for(int i=0; i<15; i++){
	longitudefromstream[z] = nmeasentence2[z+32];
	z = z+1;
	}
	
	printf("\n\nLongitude of stream = ");
	for(int i=0; i<15; i++){
		printf("%c", longitudefromstream[i]);
	}
	
	longdegrees[0] = longitudefromstream[0];
	longdegrees[1] = longitudefromstream[1];
	longdegrees[2] = longitudefromstream[2];
	
	printf("\n\nLong degrees = "); 
	for(int i=0; i<3; i++){
		printf("%c", longdegrees[i]);
	}
	
	longitudedegrees = (longdegrees[2]-'0') + ((longdegrees[1]-'0')*10.0) + ((longdegrees[0]-'0')*100.0);
	printf("\n\nLongitude degrees whole number = %Lf", longitudedegrees);
	
	longminutes[0] = longitudefromstream[3];
	longminutes[1] = longitudefromstream[4];
	longminutes[2] = longitudefromstream[5];
	longminutes[3] = longitudefromstream[6];
	longminutes[4] = longitudefromstream[7];
	longminutes[5] = longitudefromstream[8];
	longminutes[6] = longitudefromstream[9];
	longminutes[7] = longitudefromstream[10];
	longminutes[8] = longitudefromstream[11];
	longminutes[9] = longitudefromstream[12];
	
	printf("\n\nlongminutes1 = %c", longminutes[0]);
	printf("\nlongminutes2 = %c", longminutes[1]);
	printf("\nlongminutes3 = %c", longminutes[2]);
	printf("\nlongminutes4 = %c", longminutes[3]);
	printf("\nlongminutes5 = %c", longminutes[4]);
	printf("\nlongminutes6 = %c", longminutes[5]);
	printf("\nlongminutes7 = %c", longminutes[6]);
	printf("\nlongminutes8 = %c", longminutes[7]);
	printf("\nlongminutes9 = %c", longminutes[8]);
	printf("\nlongminutes10 = %c", longminutes[9]);
	
	printf("\n\nLong minutes = ");
	for(int i=0; i<10; i++){
		printf("%c", longminutes[i]);
	}
	
	longitudeminutes = ((longminutes[1]-'0') + ((longminutes[0]-'0')*10.0)) + ((longminutes[9]-'0')/10000000.0)+((longminutes[8]-'0')/1000000.0)+((longminutes[7]-'0')/100000.0)+((longminutes[6]-'0')/10000.0)+((longminutes[5]-'0')/1000.0)+((longminutes[4]-'0')/100.0)+((longminutes[3]-'0')/10.0);
	printf("\n\nLongitude minutes whole number = %Lf", longitudeminutes);
	
	longitudeminutes = longitudeminutes / 60.0;
	printf("\n\nLongitude minutes whole number / 60 = %Lf", longitudeminutes);
	
	longitudedegrees = longitudedegrees + longitudeminutes;
	printf("\n\nLongitude degrees final number = %Lf", longitudedegrees);
	
	if(longitudefromstream[14] == 'W'){
		longitudedegrees = longitudedegrees * -1;
	  printf("\n\nLongitude degrees final number with W = %Lf", longitudedegrees);
  }
	
}

void storeAltitude(){
  for(int i=0; i<7; i++){
	altitudefromstream[t] = nmeasentence2[t+58];
	t = t+1;
	}
	
	printf("\n\nAltitude of stream = ");
	for(int i=0; i<7; i++){
		printf("%c", altitudefromstream[i]);
	}
	
	altmeters[0] = altitudefromstream[0];
	altmeters[1] = altitudefromstream[1];
	altmeters[2] = altitudefromstream[2];
	altmeters[3] = altitudefromstream[3];
	altmeters[4] = altitudefromstream[4];
	
	printf("\n\naltitudemeters = %c", altmeters[0]);
	printf("\naltitudemeters = %c", altmeters[1]);
	printf("\naltitudemeters = %c", altmeters[2]);
	printf("\naltitudemeters = %c", altmeters[3]);
	printf("\naltitudemeters = %c", altmeters[4]);
	
	printf("\n\nAltitude meters = ");
	for(int i=0; i<5; i++){
		printf("%c", altmeters[i]);
	}
	
	altitudemeters = (altmeters[2]-'0')+((altmeters[1]-'0')*10.0) + ((altmeters[0]-'0')*100.0) + ((altmeters[4]-'0')/10.0);
	printf("\n\nAltitude meters whole number = %Lf", altitudemeters);
}

void storeCartesian(){
	printf("\n\nLatitude degrees in storeCartesian = %Lf", latitudedegrees);
	printf("\n\nLongitude degrees in storeCartesian = %Lf", longitudedegrees);
	printf("\n\nAltitude meters in storeCartesian = %Lf", altitudemeters);	
	
	latituderadians = latitudedegrees * (Pi/180);
	longituderadians = longitudedegrees * (Pi/180);
	
	printf("\n\nLatitude radians in storeCartesian = %Lf", latituderadians);
	printf("\n\nLongitude radians in storeCartesian = %Lf", longituderadians);
	
	N = a/sqrt(1-pow(ecc,2)*pow(sin(latituderadians),2));
	printf("\n\nN - Radius of curvature in prime vertical = %Lf", N);
	
	cartesianX = (N+altitudemeters) * cos(latituderadians) * cos(longituderadians);
	cartesianY = (N+altitudemeters) * cos(latituderadians) * sin(longituderadians);
	cartesianZ = ((1-pow(ecc,2))*(N+altitudemeters)) * sin(latituderadians);
	
	printf("\n\nCartesianX = %Lf", cartesianX);
	printf("\n\nCartesianY = %Lf", cartesianY);
	printf("\n\nCartesianZ = %Lf", cartesianZ);
	
}

void findStream(){
	if(nmeasentence[0] == '$' && nmeasentence[5] == 'A'){
		storeLatitude();
	  storeLongitude();
		storeAltitude();
		storeCartesian();
	}
	else{
	//	printf("\n\nnO sTReAm FoUNd");
	}
}

void parseSentence(){
	while(*pointer!='='){
		
	if (*pointer>='0' && *pointer<='9'){
		  convertWholeNumber();
	}
}
}

//**** Delete this and the fucking code breaks ****//

double convertWholeNumber(){
	double number = 0;
	while (*pointer>='0' && *pointer<='9'){
		number = number *10;
		number = number + *pointer-'0';
		++pointer;
		//printf("\nString = %X", *string);
		//printf("\nnumber in convert = %lf", number);
	}
	if(*pointer == '.'){
		++pointer;
		double weight = 1;
		while (*pointer>='0' && *pointer<='9'){
      weight = weight / 10;
			double scaled = (*pointer - '0') * weight;
			number = number + scaled;
			++pointer;
		  //printf("\nnumber in decimal = %lf", number);
		}			
		
	}
	//printf("\nnumber = %lf", number);
//	store[st] = number;
	//printf("\nArray = %lf", store[st]);
//	st = st+1;
	return number;
}
