//#include <stdio.h>
//#include <string.h>
//#include <math.h>
//#include <stdlib.h>

//#include "TExaS.h"
//#include "uart.h"
//#include "PLL.h"
//#include "UniversalFunctions.h"

//#define a 6378137.0 //earth equatorial radius (wgs84 standard)
//#define flattening 0.00335281 //flattening factor of ellipsoid (f = 1/298.257223563)
//#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
//#define ecc 0.08181918275 //eccentricity (e^2 = 2f - f^2)
//#define Pi 3.14159265358979323846 

//  /*,cartesianX, cartesianY, cartesianZ, N*/
//	long double latitudeminutes, longitudeminutes, latituderadians, longituderadians;
//	int x=0, z=0, t=0;
//	char latdegrees[2], longdegrees[3], latminutes[10], longminutes[10], altmeters[4];
//	char timehours[2], timemins[2], timesecs[5], messageID[6], checksum[3];
//	char latDirection[1], longDirection[1], qualityofFix[1], numofSatellites[2], HDOP[4], altUnits[1], geoidSeperation[4], geoidUnits[1], diffAge[4], diffStationID[4];
//	char encodedGGA[100];
//	char *scanner, *pointer;
//	
//	
//void findStream(char stream[]){
////		printf("\n\nNmea sentence INPUT INTO FINDSTREAM = ");
////		for(int i=0; i<84; i++){
////			printf("%c", stream[i]);
////		}
//	
//	if(stream[0] == '$' && stream[1] == 'G' && stream[2] == 'N' && stream[3] == 'G' && stream[4] == 'G' && stream[5] == 'A'){
//		
//		printf("\n\nNmea sentence to decode = ");
//		for(int i=0; i<84; i++){
//			printf("%c", stream[i]);
//		}
//	
//		printf("\n\nSentence found - GPGGA\n");
//	  parseGGA(stream);
//	  encodeGGA();
//	}
//	else{
//		printf("\n\nnO sTReAm FoUNd");
//	}
//}

//void parseGGA(char GGA[]){
//	scanner = GGA;		
//	skipName();
//	extractTime();
//	extractLatitude();
//	extractlatDirection();
//	extractLongitude();
//	extractlongDirection();
//	extractqualityofFix();
//	extractnumofSatellites();
//	extractHDOP();
//	extractAltitude();
//	extractaltitudeUnit();
//	extractgeoidSeperation();
//	extractgeoidsepUnit();
//	extractdiffcorrectionAge();
//	extractdiffStationIDandChecksum();
//	storeCartesian();
//}

//void encodeGGA(void){
//	int x=0;
//	for (int i=0; i<sizeof(messageID); i++){
//		encodedGGA[x] = messageID[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(timehours); i++){
//		encodedGGA[x] = timehours[i]; x++;
//	}
//	for (int i=0; i<sizeof(timemins); i++){
//		encodedGGA[x] = timemins[i]; x++;
//	}
//	for (int i=0; i<sizeof(timesecs); i++){
//		encodedGGA[x] = timesecs[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(latdegrees); i++){
//		encodedGGA[x] = latdegrees[i]; x++;
//	}
//	for (int i=0; i<sizeof(latminutes); i++){
//		encodedGGA[x] = latminutes[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(latDirection); i++){
//		encodedGGA[x] = latDirection[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(longdegrees); i++){
//		encodedGGA[x] = longdegrees[i]; x++;
//	}
//	for (int i=0; i<sizeof(longminutes); i++){
//		encodedGGA[x] = longminutes[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(longDirection); i++){
//		encodedGGA[x] = longDirection[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(qualityofFix); i++){
//		encodedGGA[x] = qualityofFix[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(numofSatellites); i++){
//		encodedGGA[x] = numofSatellites[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(HDOP); i++){
//		encodedGGA[x] = HDOP[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(altmeters); i++){
//		encodedGGA[x] = altmeters[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(altUnits); i++){
//		encodedGGA[x] = altUnits[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(geoidSeperation); i++){
//		encodedGGA[x] = geoidSeperation[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(geoidUnits); i++){
//		encodedGGA[x] = geoidUnits[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(diffAge); i++){
//		encodedGGA[x] = diffAge[i]; x++;
//	}
//	  encodedGGA[x] = ','; x++;
//	for (int i=0; i<sizeof(diffStationID); i++){
//		encodedGGA[x] = diffStationID[i]; x++;
//	}
//	for (int i=0; i<sizeof(checksum); i++){
//		encodedGGA[x] = checksum[i]; x++;
//	}
//	  
//	printf("\n\nEncoded NMEA sentence = ");
//	for(int i=0; i<sizeof(encodedGGA); i++){
//		printf("%c", encodedGGA[i]);
//}
//	x=0;
//}

//void extractLatitude(void){
//	//printf("\n");
//	int i=0;
//	if (*scanner != ','){
//	  //printf("\nPointer extractLatitude %c", *scanner);
//		latdegrees[0] = *scanner; scanner++;
//	  //printf("\nPointer extractLatitude %c", *scanner);
//		latdegrees[1] = *scanner; scanner++;
//		
//		latitudedegrees = convertWholeNumber(latdegrees);

//		while (*scanner != ','){
//			latminutes[i] = *scanner; i++;
//			//printf("\nPointer extractLatitude %c", *scanner);
//			scanner++;
//		}
//		
//		latitudeminutes = convertWholeNumber(latminutes);
//		//printf("\nLatitude minutes in convertWholeNumber = %.8Lf", latitudeminutes); 
//		latitudeminutes = latitudeminutes / 60;
//		//printf("\nLatitude minutes / 60 = %.8Lf", latitudeminutes);
//	  latitudedegrees = latitudedegrees + latitudeminutes;
//	  //printf("\nLatitude degrees final number = %.8Lf", latitudedegrees);
//		
//	}
//	  //printf("\nPointer extractLatitude %c", *scanner);
//    scanner++;	
//}

//void extractlatDirection(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractlatDirection %c", *scanner);
//		latDirection[i] = *scanner; i++;
//	if(*scanner == 'S'){
//		latitudedegrees = latitudedegrees * -1;
//	  //printf("\nLatitude degrees final number with south = %.8Lf", latitudedegrees);
//  }
//	scanner++;
//	}
//	//printf("\nPointer extractlatDirection %c", *scanner);
//	scanner++;
//}

//void extractLongitude(void){
//	//printf("\n");
//	int i=0;
//	if (*scanner != ','){
//	  //printf("\nPointer extractLongitude %c", *scanner);
//		longdegrees[0] = *scanner; scanner++;
//	  //printf("\nPointer extractLongitude %c", *scanner);
//		longdegrees[1] = *scanner; scanner++;
//	  //printf("\nPointer extractLongitude %c", *scanner);
//		longdegrees[2] = *scanner; scanner++;
//		
//		longitudedegrees = convertWholeNumber(longdegrees);

//		while (*scanner != ','){
//			longminutes[i] = *scanner; i++;
//			//printf("\nPointer extractLongitude %c", *scanner);
//			scanner++;
//		}
//		
//		longitudeminutes = convertWholeNumber(longminutes);
//		//printf("\nLongitude minutes after convertWholeNumber = %.8Lf", longitudeminutes);
//		longitudeminutes = longitudeminutes / 60.0;
//		//printf("\nLongitude minutes after /60 = %.8Lf", longitudeminutes);
//	  longitudedegrees = longitudedegrees + longitudeminutes;
//	  //printf("\nLongitude degrees final number = %.8Lf", longitudedegrees);
//		
//	}
//	  //printf("\nPointer extractLongitude %c", *scanner);
//    scanner++;	
//}

//void extractlongDirection(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractlongDirection %c", *scanner);
//		longDirection[i] = *scanner; i++;
//	if(*scanner == 'W'){
//		longitudedegrees = longitudedegrees * -1;
//	  //printf("\nLongitude degrees final number with south = %.8Lf", longitudedegrees);
//  }
//	scanner++;
//	}
//	//printf("\nPointer extractlongDirection %c", *scanner);
//	scanner++;
//}

//void extractqualityofFix(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractqualityofFix %c", *scanner);
//		qualityofFix[i] = *scanner;  i++;
//		if (*scanner == '1'){
//			printf("\nQuality of fix = %c = Standard GPS (2D/3D)", *scanner);
//		}
//		if (*scanner == '2'){
//			printf("\nQuality of fix = %c = Differential GPS", *scanner);
//		}
//		if (*scanner == '0'){
//			printf("\nQuality of fix = %c = No Fix", *scanner);
//		}
//		if (*scanner == '4'){
//			printf("\nQuality of fix = %c = RTK Fixed", *scanner);
//		}
//		if (*scanner == '5'){
//			printf("\nQuality of fix = %c = RTK Float", *scanner);
//		}
//		if (*scanner == '6'){
//			printf("\nQuality of fix = %c = Estimated (DR) Fix", *scanner);
//		}		
//		scanner++;
//	}
//	//printf("\nPointer extractqualityofFix %c", *scanner);
//	scanner++;
//}

//void extractnumofSatellites(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractnumofSatellites %c", *scanner);
//		numofSatellites[i] = *scanner; i++;
//		scanner++;
//	}
//	//printf("\nPointer extractnumofSatellites %c", *scanner);
//	scanner++;	
//}

//void extractHDOP(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractHDOP %c", *scanner);
//		HDOP[i] = *scanner; i++;
//		scanner++;
//	}
//	//printf("\nPointer extractHDOP %c", *scanner);
//	scanner++;	
//}

//void extractAltitude(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractAltitude %c", *scanner);
//		altmeters[i] = *scanner; i++;
//		scanner++;
//	}
//	altitudemeters = convertWholeNumber(altmeters);
//	//printf("\nPointer extractAltitude %c", *scanner);
//	scanner++;	
//}

//void extractaltitudeUnit(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractaltitudeUnit %c", *scanner);
//		altUnits[i] = *scanner;  i++;
//		scanner++;
//	}
//	//printf("\nPointer extractaltitudeUnit %c", *scanner);
//	scanner++;	
//}

//void extractgeoidSeperation(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractgeoidSeperation %c", *scanner);
//		geoidSeperation[i] = *scanner;  i++;
//		scanner++;
//	}
//	//printf("\nPointer extractgeoidSeperation %c", *scanner);
//	scanner++;	
//}

//void extractgeoidsepUnit(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractgeoidsepUnit %c", *scanner);
//		geoidUnits[i] = *scanner;  i++;
//		scanner++;
//	}
//	//printf("\nPointer extractgeoidsepUnit %c", *scanner);
//	scanner++;	
//}

//void extractdiffcorrectionAge(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != ','){
//		//printf("\nPointer extractdiffcorrectionAge %c", *scanner);
//		diffAge[i] = *scanner;  i++;
//		scanner++;
//	}
//	//printf("\nPointer extractdiffcorrectionAge %c", *scanner);
//	scanner++;	
//}

//void extractdiffStationIDandChecksum(void){
//	//printf("\n");
//	int i=0;
//	while (*scanner != '*'){
//		//printf("\nPointer extractdiffcorrectionStationID %c", *scanner);
//		diffStationID[i] = *scanner; i++;
//		scanner++;
//	}
//	if (*scanner == '*'){
//		//printf("\nPointer extractChecksum %c", *scanner);
//		checksum[0] = *scanner; scanner++;
//		//printf("\nPointer extractChecksum %c", *scanner);
//		checksum[1] = *scanner; scanner++;
//		//printf("\nPointer extractChecksum %c", *scanner);
//		checksum[2] = *scanner; scanner++;
//	}
//	//printf("\nPointer extractdiffcorrectionStationID %c", *scanner);
//	scanner++;	
//}

//void skipName(void){
//	int i=0;
//	while (*scanner != ','){
//	  //printf("\nPointer skipName %c", *scanner);
//		messageID[i] = *scanner; i++;
//		scanner++;		
//	}
//	  //printf("\nPointer skipName %c", *scanner);
//    scanner++;	
//}

//void extractTime(void){
//	//printf("\n");
//	if (*scanner != ','){
//	  //printf("\nPointer extractTime %c", *scanner);
//		timehours[0] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timehours[1] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timemins[0] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timemins[1] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timesecs[0] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timesecs[1] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timesecs[2] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//		timesecs[3] = *scanner; scanner++;
//	  //printf("\nPointer extractTime %c", *scanner);
//	  timesecs[4] = *scanner; scanner++;
//	}	
//	  //printf("\nPointer extractTime %c", *scanner);
//	  scanner++;
//}
// 
////void storeCartesian(){
////  printf("\n");
////	printf("\nLatitude degrees in storeCartesian = %.8Lf", latitudedegrees);
////	printf("\nLongitude degrees in storeCartesian = %.8Lf", longitudedegrees);
////	printf("\nAltitude meters in storeCartesian = %.8Lf", altitudemeters);	
////	
////	latituderadians = latitudedegrees * (Pi/180);
////	longituderadians = longitudedegrees * (Pi/180);
////	
//////	printf("\n\nLatitude radians in storeCartesian = %.8Lf", latituderadians);
//////	printf("\n\nLongitude radians in storeCartesian = %.8Lf", longituderadians);
////	
////	N = a/sqrt(1-pow(ecc,2)*pow(sin(latituderadians),2));
//////	printf("\n\nN - Radius of curvature in prime vertical = %.8Lf", N);
////	
////	cartesianX = (N+altitudemeters) * cos(latituderadians) * cos(longituderadians);
////	cartesianY = (N+altitudemeters) * cos(latituderadians) * sin(longituderadians);
////	cartesianZ = ((1-pow(ecc,2))*(N+altitudemeters)) * sin(latituderadians);
////	
////	printf("\n\nCartesianX = %.8Lf", cartesianX);
////	printf("\nCartesianY = %.8Lf", cartesianY);
////	printf("\nCartesianZ = %.8Lf", cartesianZ);
////	
////}
//// 
//double convertWholeNumber(char numberstring[]){
//	pointer = numberstring;
//	double number = 0;
//	while (*pointer>='0' && *pointer<='9'){
//		number = number *10;
//		number = number + *pointer-'0';
//		++pointer;
//		//printf("\nString = %X", *string);
//		//printf("\nnumber in convert = %.8Lf", number);
//	}
//	if(*pointer == '.'){
//		++pointer;
//		double weight = 1;
//		while (*pointer>='0' && *pointer<='9'){
//      weight = weight / 10;
//			double scaled = (*pointer - '0') * weight;
//			number = number + scaled;
//			++pointer;
//		  //printf("\nnumber in decimal = %.8Lf", number);
//		}			
//		
//	}
////	printf("\nnumber = %.8Lf", number);
//	return number;
//}
