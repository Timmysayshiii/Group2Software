#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#include "TExaS.h"
#include "uart.h"
#include "PLL.h"
#include "UniversalFunctions2.h"

#define a 6378137.0 //earth equatorial radius (wgs84 standard)
#define flattening 0.00335281 //flattening factor of ellipsoid (f = 1/298.257223563)
#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
#define ecc 0.08181918275 //eccentricity (e^2 = 2f - f^2)
#define Pi 3.14159265358979323846 

	extern long double latitudedegrees2, longitudedegrees2, altitudemeters2 /*,cartesianX, cartesianY, cartesianZ, N*/;
	long double latitudeminutes2, longitudeminutes2, latituderadians2, longituderadians2;
//	int x=0, z=0, t=0;
	char latdegrees2[2], longdegrees2[3], latminutes2[10], longminutes2[10], altmeters2[4];
	char timehours2[2], timemins2[2], timesecs2[5], messageID2[6], checksum2[3];
	char latDirection2[1], longDirection2[1], qualityofFix2[1], numofSatellites2[2], HDOP2[4], altUnits2[1], geoidSeperation2[4], geoidUnits2[1], diffAge2[4], diffStationID2[4];
	char encodedGGA2[100];
	char *scanner2, *pointer2;
	
	
void findStream2(char stream[]){
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
	  parseGGA2(stream);
	  encodeGGA2();
	}
	else{
		printf("\n\nnO sTReAm FoUNd");
	}
}

void parseGGA2(char GGA[]){
	scanner2 = GGA;		
	skipName2();
	extractTime2();
	extractLatitude2();
	extractlatDirection2();
	extractLongitude2();
	extractlongDirection2();
	extractqualityofFix2();
	extractnumofSatellites2();
	extractHDOP2();
	extractAltitude2();
	extractaltitudeUnit2();
	extractgeoidSeperation2();
	extractgeoidsepUnit2();
	extractdiffcorrectionAge2();
	extractdiffStationIDandChecksum2();
//	storeCartesian2();
}

void encodeGGA2(void){
	int x=0;
	for (int i=0; i<sizeof(messageID2); i++){
		encodedGGA2[x] = messageID2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(timehours2); i++){
		encodedGGA2[x] = timehours2[i]; x++;
	}
	for (int i=0; i<sizeof(timemins2); i++){
		encodedGGA2[x] = timemins2[i]; x++;
	}
	for (int i=0; i<sizeof(timesecs2); i++){
		encodedGGA2[x] = timesecs2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(latdegrees2); i++){
		encodedGGA2[x] = latdegrees2[i]; x++;
	}
	for (int i=0; i<sizeof(latminutes2); i++){
		encodedGGA2[x] = latminutes2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(latDirection2); i++){
		encodedGGA2[x] = latDirection2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(longdegrees2); i++){
		encodedGGA2[x] = longdegrees2[i]; x++;
	}
	for (int i=0; i<sizeof(longminutes2); i++){
		encodedGGA2[x] = longminutes2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(longDirection2); i++){
		encodedGGA2[x] = longDirection2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(qualityofFix2); i++){
		encodedGGA2[x] = qualityofFix2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(numofSatellites2); i++){
		encodedGGA2[x] = numofSatellites2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(HDOP2); i++){
		encodedGGA2[x] = HDOP2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(altmeters2); i++){
		encodedGGA2[x] = altmeters2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(altUnits2); i++){
		encodedGGA2[x] = altUnits2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(geoidSeperation2); i++){
		encodedGGA2[x] = geoidSeperation2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(geoidUnits2); i++){
		encodedGGA2[x] = geoidUnits2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(diffAge2); i++){
		encodedGGA2[x] = diffAge2[i]; x++;
	}
	  encodedGGA2[x] = ','; x++;
	for (int i=0; i<sizeof(diffStationID2); i++){
		encodedGGA2[x] = diffStationID2[i]; x++;
	}
	for (int i=0; i<sizeof(checksum2); i++){
		encodedGGA2[x] = checksum2[i]; x++;
	}
	  
	printf("\n\nEncoded NMEA sentence = ");
	for(int i=0; i<sizeof(encodedGGA2); i++){
		printf("%c", encodedGGA2[i]);
}
	x=0;
}

void extractLatitude2(void){
	//printf("\n");
	int i=0;
	if (*scanner2 != ','){
	  //printf("\npointer2 extractLatitude %c", *scanner2);
		latdegrees2[0] = *scanner2; scanner2++;
	  //printf("\npointer2 extractLatitude %c", *scanner2);
		latdegrees2[1] = *scanner2; scanner2++;
		
		latitudedegrees2 = convertWholeNumber2(latdegrees2);

		while (*scanner2 != ','){
			latminutes2[i] = *scanner2; i++;
			//printf("\npointer2 extractLatitude %c", *scanner2);
			scanner2++;
		}
		
		latitudeminutes2 = convertWholeNumber2(latminutes2);
		//printf("\nLatitude minutes in convertWholeNumber = %.8Lf", latitudeminutes2); 
		latitudeminutes2 = latitudeminutes2 / 60;
		//printf("\nLatitude minutes / 60 = %.8Lf", latitudeminutes2);
	  latitudedegrees2 = latitudedegrees2 + latitudeminutes2;
	  //printf("\nLatitude degrees final number = %.8Lf", latitudedegrees2);
		
	}
	  //printf("\npointer2 extractLatitude %c", *scanner2);
    scanner2++;	
}

void extractlatDirection2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractlatDirection %c", *scanner2);
		latDirection2[i] = *scanner2; i++;
	if(*scanner2 == 'S'){
		latitudedegrees2 = latitudedegrees2 * -1;
	  //printf("\nLatitude degrees final number with south = %.8Lf", latitudedegrees2);
  }
	scanner2++;
	}
	//printf("\npointer2 extractlatDirection %c", *scanner2);
	scanner2++;
}

void extractLongitude2(void){
	//printf("\n");
	int i=0;
	if (*scanner2 != ','){
	  //printf("\npointer2 extractLongitude %c", *scanner2);
		longdegrees2[0] = *scanner2; scanner2++;
	  //printf("\npointer2 extractLongitude %c", *scanner2);
		longdegrees2[1] = *scanner2; scanner2++;
	  //printf("\npointer2 extractLongitude %c", *scanner2);
		longdegrees2[2] = *scanner2; scanner2++;
		
		longitudedegrees2 = convertWholeNumber2(longdegrees2);

		while (*scanner2 != ','){
			longminutes2[i] = *scanner2; i++;
			//printf("\npointer2 extractLongitude %c", *scanner2);
			scanner2++;
		}
		
		longitudeminutes2 = convertWholeNumber2(longminutes2);
		//printf("\nLongitude minutes after convertWholeNumber = %.8Lf", longitudeminutes2);
		longitudeminutes2 = longitudeminutes2 / 60.0;
		//printf("\nLongitude minutes after /60 = %.8Lf", longitudeminutes2);
	  longitudedegrees2 = longitudedegrees2 + longitudeminutes2;
	  //printf("\nLongitude degrees final number = %.8Lf", longitudedegrees2);
		
	}
	  //printf("\npointer2 extractLongitude %c", *scanner2);
    scanner2++;	
}

void extractlongDirection2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractlongDirection %c", *scanner2);
		longDirection2[i] = *scanner2; i++;
	if(*scanner2 == 'W'){
		longitudedegrees2 = longitudedegrees2 * -1;
	  //printf("\nLongitude degrees final number with south = %.8Lf", longitudedegrees2);
  }
	scanner2++;
	}
	//printf("\npointer2 extractlongDirection %c", *scanner2);
	scanner2++;
}

void extractqualityofFix2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractqualityofFix %c", *scanner2);
		qualityofFix2[i] = *scanner2;  i++;
		if (*scanner2 == '1'){
			printf("\nQuality of fix = %c = Standard GPS (2D/3D)", *scanner2);
		}
		if (*scanner2 == '2'){
			printf("\nQuality of fix = %c = Differential GPS", *scanner2);
		}
		if (*scanner2 == '0'){
			printf("\nQuality of fix = %c = No Fix", *scanner2);
		}
		if (*scanner2 == '4'){
			printf("\nQuality of fix = %c = RTK Fixed", *scanner2);
		}
		if (*scanner2 == '5'){
			printf("\nQuality of fix = %c = RTK Float", *scanner2);
		}
		if (*scanner2 == '6'){
			printf("\nQuality of fix = %c = Estimated (DR) Fix", *scanner2);
		}		
		scanner2++;
	}
	//printf("\npointer2 extractqualityofFix %c", *scanner2);
	scanner2++;
}

void extractnumofSatellites2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractnumofSatellites %c", *scanner2);
		numofSatellites2[i] = *scanner2; i++;
		scanner2++;
	}
	//printf("\npointer2 extractnumofSatellites %c", *scanner2);
	scanner2++;	
}

void extractHDOP2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractHDOP %c", *scanner2);
		HDOP2[i] = *scanner2; i++;
		scanner2++;
	}
	//printf("\npointer2 extractHDOP %c", *scanner2);
	scanner2++;	
}

void extractAltitude2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractAltitude %c", *scanner2);
		altmeters2[i] = *scanner2; i++;
		scanner2++;
	}
	altitudemeters2 = convertWholeNumber2(altmeters2);
	//printf("\npointer2 extractAltitude %c", *scanner2);
	scanner2++;	
}

void extractaltitudeUnit2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractaltitudeUnit %c", *scanner2);
		altUnits2[i] = *scanner2;  i++;
		scanner2++;
	}
	//printf("\npointer2 extractaltitudeUnit %c", *scanner2);
	scanner2++;	
}

void extractgeoidSeperation2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractgeoidSeperation %c", *scanner2);
		geoidSeperation2[i] = *scanner2;  i++;
		scanner2++;
	}
	//printf("\npointer2 extractgeoidSeperation %c", *scanner2);
	scanner2++;	
}

void extractgeoidsepUnit2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractgeoidsepUnit %c", *scanner2);
		geoidUnits2[i] = *scanner2;  i++;
		scanner2++;
	}
	//printf("\npointer2 extractgeoidsepUnit %c", *scanner2);
	scanner2++;	
}

void extractdiffcorrectionAge2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != ','){
		//printf("\npointer2 extractdiffcorrectionAge %c", *scanner2);
		diffAge2[i] = *scanner2;  i++;
		scanner2++;
	}
	//printf("\npointer2 extractdiffcorrectionAge %c", *scanner2);
	scanner2++;	
}

void extractdiffStationIDandChecksum2(void){
	//printf("\n");
	int i=0;
	while (*scanner2 != '*'){
		//printf("\npointer2 extractdiffcorrectionStationID %c", *scanner2);
		diffStationID2[i] = *scanner2; i++;
		scanner2++;
	}
	if (*scanner2 == '*'){
		//printf("\npointer2 extractChecksum %c", *scanner2);
		checksum2[0] = *scanner2; scanner2++;
		//printf("\npointer2 extractChecksum %c", *scanner2);
		checksum2[1] = *scanner2; scanner2++;
		//printf("\npointer2 extractChecksum %c", *scanner2);
		checksum2[2] = *scanner2; scanner2++;
	}
	//printf("\npointer2 extractdiffcorrectionStationID %c", *scanner2);
	scanner2++;	
}

void skipName2(void){
	int i=0;
	while (*scanner2 != ','){
	  //printf("\npointer2 skipName %c", *scanner2);
		messageID2[i] = *scanner2; i++;
		scanner2++;		
	}
	  //printf("\npointer2 skipName %c", *scanner2);
    scanner2++;	
}

void extractTime2(void){
	//printf("\n");
	if (*scanner2 != ','){
	  //printf("\npointer2 extractTime %c", *scanner2);
		timehours2[0] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timehours2[1] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timemins2[0] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timemins2[1] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timesecs2[0] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timesecs2[1] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timesecs2[2] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
		timesecs2[3] = *scanner2; scanner2++;
	  //printf("\npointer2 extractTime %c", *scanner2);
	  timesecs2[4] = *scanner2; scanner2++;
	}	
	  //printf("\npointer2 extractTime %c", *scanner2);
	  scanner2++;
}

//void storeCartesian2(){
//  printf("\n");
//	printf("\nLatitude degrees in storeCartesian = %.8Lf", latitudedegrees2);
//	printf("\nLongitude degrees in storeCartesian = %.8Lf", longitudedegrees2);
//	printf("\nAltitude meters in storeCartesian = %.8Lf", altitudemeters2);	
//	
//	latituderadians2 = latitudedegrees2 * (Pi/180);
//	longituderadians2 = longitudedegrees2 * (Pi/180);
//	
////	printf("\n\nLatitude radians in storeCartesian = %.8Lf", latituderadians2);
////	printf("\n\nLongitude radians in storeCartesian = %.8Lf", longituderadians2);
//	
//	N2 = a/sqrt(1-pow(ecc,2)*pow(sin(latituderadians2),2));
////	printf("\n\nN - Radius of curvature in prime vertical = %.8Lf", N);
//	
//	cartesianX2 = (N2+altitudemeters2) * cos(latituderadians2) * cos(longituderadians2);
//	cartesianY2 = (N2+altitudemeters2) * cos(latituderadians2) * sin(longituderadians2);
//	cartesianZ2 = ((1-pow(ecc,2))*(N2+altitudemeters2)) * sin(latituderadians2);
//	
//	printf("\n\ncartesianX2 = %.8Lf", cartesianX2);
//	printf("\ncartesianY2 = %.8Lf", cartesianY2);
//	printf("\ncartesianZ2 = %.8Lf", cartesianZ2);
//	
//}
// 
double convertWholeNumber2(char numberstring[]){
	pointer2 = numberstring;
	double number = 0;
	while (*pointer2>='0' && *pointer2<='9'){
		number = number *10;
		number = number + *pointer2-'0';
		++pointer2;
		//printf("\nString = %X", *string);
		//printf("\nnumber in convert = %.8Lf", number);
	}
	if(*pointer2 == '.'){
		++pointer2;
		double weight = 1;
		while (*pointer2>='0' && *pointer2<='9'){
      weight = weight / 10;
			double scaled = (*pointer2 - '0') * weight;
			number = number + scaled;
			++pointer2;
		  //printf("\nnumber in decimal = %.8Lf", number);
		}			
		
	}
//	printf("\nnumber = %.8Lf", number);
	return number;
}
