#include <stdio.h>
#include <string.h>
#include <math.h>

#include "TExaS.h"
#include "uart.h"
#include "PLL.h"
//#include "UniversalFunctions.h"
//#include "UniversalFunctions2.h"
//#include "UniversalFunctions3.h"
#include "updatedNmeaFunctions.h"
#include "calculations.h"
#include "Rotation.h"
#include "vector.h"
#include "UART1.h"
#define a 6378137.0 //earth equatorial radius (wgs84 standard)
#define flattening 0.00335281 //flattening factor of ellipsoid (f = 1/298.257223563)
#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
#define ecc 0.08181918275 //eccentricity (e^2 = 2f - f^2)
#define Pi 3.14159265358979323846

//  void storeLatitude(void);
//	void storeLongitude(void);
//	void storeAltitude(void);
//	void storeCartesian(void);
	void parseSentence(void);
//	void findStream(void);
	
//	long double latitudedegrees, latitudeminutes, latmin123456, cartesianX, cartesianY, cartesianZ, N;
//	long double longitudedegrees, longitudeminutes, altitudemeters, latituderadians, longituderadians;
//	int x=0, z=0, t=0;
//	char latitudefromstream[14], altitudefromstream[8];
//	char latdegrees[2], longdegrees[3], altmeters[5];
//	char latminutes[10], longminutes[10];
//	char longitudefromstream[15];
//	char *pointer, *latpointer;

	char nmeasentence[77] = {'$','G','N','G','G','A',',','0',
		                       '9','2','7','2','5','.','0','0',
		                       ',','4','7','1','7','.','1','1',
		                       '3','9','9','0','1',',','S',',',
		                       '0','0','8','3','3','.','9','1',
		                       '5','9','0','0','0',',','W',',',
		                       '4',',','0','8',',','1','.','0',
		                       '1',',','4','9','9','.','6',',',
	                         'M',',','4','8','.','0',',','M',
	                         ',',',','*','5','B',};
	
	char nmeasentence2[77] = {'$','G','P','R','M','C',',','0',
		                       '9','2','7','2','5','.','0','0',
		                       ',','5','8','1','7','.','1','1',
		                       '3','9','9','0','1',',','N',',',
		                       '0','0','9','3','3','.','9','1',
		                       '5','9','0','0','0',',','E',',',
		                       '1',',','0','8',',','1','.','0',
		                       '1',',','4','9','9','.','6',',',
	                         'M',',','4','8','.','0',',','M',
	                         ',',',','*','5','B',};

char nmeafromsystem[85] = {"$GNGGA,164202.00,5348.5082900,N,00133.4443600,W,5,12,0.80,93.4,M,47.8,M,11.0,0000*7B"};
char nmeafromsystem2[85] = {"$GNGGA,164208.00,5348.5087700,N,00133.4450300,W,5,12,0.80,93.6,M,47.8,M,2.0,0000*4D"};
char nmeafromsystem3[88] = {"$GNGGA,164202.00,8348.5094500,N,00133.4460700,W,5,12,0.86,82.5,M,47.8,M,16.0,0000*70"};

char nmeafromsystem4[85] = {"$GNGGA,164208.00,5348.50968,N,00133.44528,W,5,12,0.87,82.4,M,47.8,M,22.0,0000*7C"};
char nmeafromsystem5[85] = {"$GNGGA,164202.00,5348.50944,N,00133.44801,W,5,12,0.79,81.7,M,47.8,M,43.0,0000*78"};
char nmeafromsystem6[85] = {"$GNGGA,164208.00,5348.50946,N,00133.44792,W,5,12,0.94,81.9,M,47.8,M,49.0,0000*72"};
////////////////////////////////////////////////////////////////////////////////				
													 
int main(void){
	
	PLL_Init();	     //Initialise the PLL
	SysTick_Init();  //Initialise the Systick
	UART_Init();     //Initialise UART
  UART1_Init();    //Initialise UART1
	UART2_Init();    //Initalise UART2
  UART3_Init();	   //Initalise UART3
  UART5_Init();    //Initalise UART5
  
	printf("Program Start\n");
//	
//	struct GGA_data gga1;
//	struct GGA_data gga2;
//	struct GGA_data gga3;



while (1){
	char i = UART1_InChar();
	printf("%c",i);
}

//        printf("\nUART1\n");
//        //parseGGA(get_str(vec), &gga1);
//				printf("%s\n", get_str(vec));
//        printf("\nUART2\n");
//        //parseGGA(get_str(vec2), &gga2);
//				printf("%s\n", get_str(vec2));
//        printf("\nUART3\n");
//        //parseGGA(get_str(vec3), &gga3);
//				printf("%s\n", get_str(vec3));

			
	
	printf("\n\nProgram End\n\n");

}

///////////////////////////////////////////////////////////////////////////////


