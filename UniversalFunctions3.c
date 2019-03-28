#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "TExaS.h"
#include "uart.h"
#include "PLL.h"
#include "UniversalFunctions3.h"

#define a 6378137.0 //earth equatorial radius (wgs84 standard)
#define flattening 0.0035281 //flattening factor of ellipsoid (f = 1/298.257223563)
#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
#define ecc 0.08181918275 //eccentricity (e^2 = 2f - f^2)
#define Pi 3.14159265358979323846 

	extern long double latitudedegrees3, longitudedegrees3, altitudemeters3 /*,cartesianX, cartesianY, cartesianZ, N*/;
	long double latitudeminutes3, longitudeminutes3, latituderadians3, longituderadians3;
//	int x=0, z=0, t=0;
	char latdegrees3[2], longdegrees3[3], latminutes3[10], longminutes3[10], altmeters3[4];
	char timehours3[2], timemins3[2], timesecs3[5], messageID3[6], checksum3[3];
	char latDirection3[1], longDirection3[1], qualityofFix3[1], numofSatellites3[2], HDOP3[4], altUnits3[1], geoidSeperation3[4], geoidUnits3[1], diffAge3[4], diffStationID3[4];
	char encodedGGA3[100];
	char *scanner3, *pointer3;
	
	
void findStream3(char stream[]){
//		printf("\n\nNmea sentence INPUT INTO FINDSTREAM = ");
//		for(int i=0; i<84; i++){
//			printf("%c", stream[i]);
//		}
	
	if(stream[0] == '$' && stream[1] == 'G' && stream[2] == 'N' && stream[3] == 'G' && stream[4] == 'G' && stream[5] == 'A'){
		
		printf("\n\nNmea sentence to decode = ");
		for(int i=0; i<84; i++){
			printf("%c", stream[i]);
		}
	
		printf("\n\nSentence found - GPGGA\n");
	  parseGGA3(stream);
	  encodeGGA3();
	}
	else{
		printf("\n\nnO sTReAm FoUNd");
	}
}

void parseGGA3(char GGA[]){
	scanner3 = GGA;		
	skipName3();
	extractTime3();
	extractLatitude3();
	extractlatDirection3();
	extractLongitude3();
	extractlongDirection3();
	extractqualityofFix3();
	extractnumofSatellites3();
	extractHDOP3();
	extractAltitude3();
	extractaltitudeUnit3();
	extractgeoidSeperation3();
	extractgeoidsepUnit3();
	extractdiffcorrectionAge3();
	extractdiffStationIDandChecksum3();
//	storeCartesian3();
}

void encodeGGA3(void){
	int x=0;
	for (int i=0; i<sizeof(messageID3); i++){
		encodedGGA3[x] = messageID3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(timehours3); i++){
		encodedGGA3[x] = timehours3[i]; x++;
	}
	for (int i=0; i<sizeof(timemins3); i++){
		encodedGGA3[x] = timemins3[i]; x++;
	}
	for (int i=0; i<sizeof(timesecs3); i++){
		encodedGGA3[x] = timesecs3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(latdegrees3); i++){
		encodedGGA3[x] = latdegrees3[i]; x++;
	}
	for (int i=0; i<sizeof(latminutes3); i++){
		encodedGGA3[x] = latminutes3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(latDirection3); i++){
		encodedGGA3[x] = latDirection3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(longdegrees3); i++){
		encodedGGA3[x] = longdegrees3[i]; x++;
	}
	for (int i=0; i<sizeof(longminutes3); i++){
		encodedGGA3[x] = longminutes3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(longDirection3); i++){
		encodedGGA3[x] = longDirection3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(qualityofFix3); i++){
		encodedGGA3[x] = qualityofFix3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(numofSatellites3); i++){
		encodedGGA3[x] = numofSatellites3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(HDOP3); i++){
		encodedGGA3[x] = HDOP3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(altmeters3); i++){
		encodedGGA3[x] = altmeters3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(altUnits3); i++){
		encodedGGA3[x] = altUnits3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(geoidSeperation3); i++){
		encodedGGA3[x] = geoidSeperation3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(geoidUnits3); i++){
		encodedGGA3[x] = geoidUnits3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(diffAge3); i++){
		encodedGGA3[x] = diffAge3[i]; x++;
	}
	  encodedGGA3[x] = ','; x++;
	for (int i=0; i<sizeof(diffStationID3); i++){
		encodedGGA3[x] = diffStationID3[i]; x++;
	}
	for (int i=0; i<sizeof(checksum3); i++){
		encodedGGA3[x] = checksum3[i]; x++;
	}
	  
	printf("\n\nEncoded NMEA sentence = ");
	for(int i=0; i<sizeof(encodedGGA3); i++){
		printf("%c", encodedGGA3[i]);
}
	x=0;
}

void extractLatitude3(void){
	//printf("\n");
	int i=0;
	if (*scanner3 != ','){
	  //printf("\npointer3 extractLatitude %c", *scanner3);
		latdegrees3[0] = *scanner3; scanner3++;
	  //printf("\npointer3 extractLatitude %c", *scanner3);
		latdegrees3[1] = *scanner3; scanner3++;
		
		latitudedegrees3 = convertWholeNumber3(latdegrees3);

		while (*scanner3 != ','){
			latminutes3[i] = *scanner3; i++;
			//printf("\npointer3 extractLatitude %c", *scanner3);
			scanner3++;
		}
		
		latitudeminutes3 = convertWholeNumber3(latminutes3);
		//printf("\nLatitude minutes in convertWholeNumber = %.8Lf", latitudeminutes); 
		latitudeminutes3 = latitudeminutes3 / 60;
		//printf("\nLatitude minutes / 60 = %.8Lf", latitudeminutes);
	  latitudedegrees3 = latitudedegrees3 + latitudeminutes3;
	  //printf("\nLatitude degrees final number = %.8Lf", latitudedegrees);
		
	}
	  //printf("\npointer3 extractLatitude %c", *scanner3);
    scanner3++;	
}

void extractlatDirection3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractlatDirection %c", *scanner3);
		latDirection3[i] = *scanner3; i++;
	if(*scanner3 == 'S'){
		latitudedegrees3 = latitudedegrees3 * -1;
	  //printf("\nLatitude degrees final number with south = %.8Lf", latitudedegrees);
  }
	scanner3++;
	}
	//printf("\npointer3 extractlatDirection %c", *scanner3);
	scanner3++;
}

void extractLongitude3(void){
	//printf("\n");
	int i=0;
	if (*scanner3 != ','){
	  //printf("\npointer3 extractLongitude %c", *scanner3);
		longdegrees3[0] = *scanner3; scanner3++;
	  //printf("\npointer3 extractLongitude %c", *scanner3);
		longdegrees3[1] = *scanner3; scanner3++;
	  //printf("\npointer3 extractLongitude %c", *scanner3);
		longdegrees3[2] = *scanner3; scanner3++;
		
		longitudedegrees3 = convertWholeNumber3(longdegrees3);

		while (*scanner3 != ','){
			longminutes3[i] = *scanner3; i++;
			//printf("\npointer3 extractLongitude %c", *scanner3);
			scanner3++;
		}
		
		longitudeminutes3 = convertWholeNumber3(longminutes3);
		//printf("\nLongitude minutes after convertWholeNumber = %.8Lf", longitudeminutes);
		longitudeminutes3 = longitudeminutes3 / 60.0;
		//printf("\nLongitude minutes after /60 = %.8Lf", longitudeminutes);
	  longitudedegrees3 = longitudedegrees3 + longitudeminutes3;
	  //printf("\nLongitude degrees final number = %.8Lf", longitudedegrees);
		
	}
	  //printf("\npointer3 extractLongitude %c", *scanner3);
    scanner3++;	
}

void extractlongDirection3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractlongDirection %c", *scanner3);
		longDirection3[i] = *scanner3; i++;
	if(*scanner3 == 'W'){
		longitudedegrees3 = longitudedegrees3 * -1;
	  //printf("\nLongitude degrees final number with south = %.8Lf", longitudedegrees);
  }
	scanner3++;
	}
	//printf("\npointer3 extractlongDirection %c", *scanner3);
	scanner3++;
}

void extractqualityofFix3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractqualityofFix %c", *scanner3);
		qualityofFix3[i] = *scanner3;  i++;
		if (*scanner3 == '1'){
			printf("\nQuality of fix = %c = Standard GPS (2D/3D)", *scanner3);
		}
		if (*scanner3 == '2'){
			printf("\nQuality of fix = %c = Differential GPS", *scanner3);
		}
		if (*scanner3 == '0'){
			printf("\nQuality of fix = %c = No Fix", *scanner3);
		}
		if (*scanner3 == '4'){
			printf("\nQuality of fix = %c = RTK Fixed", *scanner3);
		}
		if (*scanner3 == '5'){
			printf("\nQuality of fix = %c = RTK Float", *scanner3);
		}
		if (*scanner3 == '6'){
			printf("\nQuality of fix = %c = Estimated (DR) Fix", *scanner3);
		}		
		scanner3++;
	}
	//printf("\npointer3 extractqualityofFix %c", *scanner3);
	scanner3++;
}

void extractnumofSatellites3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractnumofSatellites %c", *scanner3);
		numofSatellites3[i] = *scanner3; i++;
		scanner3++;
	}
	//printf("\npointer3 extractnumofSatellites %c", *scanner3);
	scanner3++;	
}

void extractHDOP3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractHDOP %c", *scanner3);
		HDOP3[i] = *scanner3; i++;
		scanner3++;
	}
	//printf("\npointer3 extractHDOP %c", *scanner3);
	scanner3++;	
}

void extractAltitude3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractAltitude %c", *scanner3);
		altmeters3[i] = *scanner3; i++;
		scanner3++;
	}
	altitudemeters3 = convertWholeNumber3(altmeters3);
	//printf("\npointer3 extractAltitude %c", *scanner3);
	scanner3++;	
}

void extractaltitudeUnit3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractaltitudeUnit %c", *scanner3);
		altUnits3[i] = *scanner3;  i++;
		scanner3++;
	}
	//printf("\npointer3 extractaltitudeUnit %c", *scanner3);
	scanner3++;	
}

void extractgeoidSeperation3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractgeoidSeperation %c", *scanner3);
		geoidSeperation3[i] = *scanner3;  i++;
		scanner3++;
	}
	//printf("\npointer3 extractgeoidSeperation %c", *scanner3);
	scanner3++;	
}

void extractgeoidsepUnit3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractgeoidsepUnit %c", *scanner3);
		geoidUnits3[i] = *scanner3;  i++;
		scanner3++;
	}
	//printf("\npointer3 extractgeoidsepUnit %c", *scanner3);
	scanner3++;	
}

void extractdiffcorrectionAge3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != ','){
		//printf("\npointer3 extractdiffcorrectionAge %c", *scanner3);
		diffAge3[i] = *scanner3;  i++;
		scanner3++;
	}
	//printf("\npointer3 extractdiffcorrectionAge %c", *scanner3);
	scanner3++;	
}

void extractdiffStationIDandChecksum3(void){
	//printf("\n");
	int i=0;
	while (*scanner3 != '*'){
		//printf("\npointer3 extractdiffcorrectionStationID %c", *scanner3);
		diffStationID3[i] = *scanner3; i++;
		scanner3++;
	}
	if (*scanner3 == '*'){
		//printf("\npointer3 extractChecksum %c", *scanner3);
		checksum3[0] = *scanner3; scanner3++;
		//printf("\npointer3 extractChecksum %c", *scanner3);
		checksum3[1] = *scanner3; scanner3++;
		//printf("\npointer3 extractChecksum %c", *scanner3);
		checksum3[2] = *scanner3; scanner3++;
	}
	//printf("\npointer3 extractdiffcorrectionStationID %c", *scanner3);
	scanner3++;	
}

void skipName3(void){
	int i=0;
	while (*scanner3 != ','){
	  //printf("\npointer3 skipName %c", *scanner3);
		messageID3[i] = *scanner3; i++;
		scanner3++;		
	}
	  //printf("\npointer3 skipName %c", *scanner3);
    scanner3++;	
}

void extractTime3(void){
	//printf("\n");
	if (*scanner3 != ','){
	  //printf("\npointer3 extractTime %c", *scanner3);
		timehours3[0] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timehours3[1] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timemins3[0] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timemins3[1] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timesecs3[0] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timesecs3[1] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timesecs3[2] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
		timesecs3[3] = *scanner3; scanner3++;
	  //printf("\npointer3 extractTime %c", *scanner3);
	  timesecs3[4] = *scanner3; scanner3++;
	}	
	  //printf("\npointer3 extractTime %c", *scanner3);
	  scanner3++;
}

//void storeCartesian3(){
//  printf("\n");
//	printf("\nLatitude degrees in storeCartesian = %.8Lf", latitudedegrees3);
//	printf("\nLongitude degrees in storeCartesian = %.8Lf", longitudedegrees3);
//	printf("\nAltitude meters in storeCartesian = %.8Lf", altitudemeters3);	
//	
//	latituderadians3 = latitudedegrees3 * (Pi/180);
//	longituderadians3 = longitudedegrees3 * (Pi/180);
//	
////	printf("\n\nLatitude radians in storeCartesian = %.8Lf", latituderadians);
////	printf("\n\nLongitude radians in storeCartesian = %.8Lf", longituderadians);
//	
//	N3 = a/sqrt(1-pow(ecc,2)*pow(sin(latituderadians3),2));
////	printf("\n\nN - Radius of curvature in prime vertical = %.8Lf", N);
//	
//	cartesianX3 = (N3+altitudemeters3) * cos(latituderadians3) * cos(longituderadians3);
//	cartesianY3 = (N3+altitudemeters3) * cos(latituderadians3) * sin(longituderadians3);
//	cartesianZ3 = ((1-pow(ecc,2))*(N3+altitudemeters3)) * sin(latituderadians3);
//	
//	printf("\n\nCartesianX = %.8Lf", cartesianX3);
//	printf("\nCartesianY = %.8Lf", cartesianY3);
//	printf("\nCartesianZ = %.8Lf", cartesianZ3);
//	
//}
// 
double convertWholeNumber3(char numberstring[]){
	pointer3 = numberstring;
	double number = 0;
	while (*pointer3>='0' && *pointer3<='9'){
		number = number *10;
		number = number + *pointer3-'0';
		++pointer3;
		//printf("\nString = %X", *string);
		//printf("\nnumber in convert = %.8Lf", number);
	}
	if(*pointer3 == '.'){
		++pointer3;
		double weight = 1;
		while (*pointer3>='0' && *pointer3<='9'){
      weight = weight / 10;
			double scaled = (*pointer3 - '0') * weight;
			number = number + scaled;
			++pointer3;
		  //printf("\nnumber in decimal = %.8Lf", number);
		}			
		
	}
//	printf("\nnumber = %.8Lf", number);
	return number;
}
