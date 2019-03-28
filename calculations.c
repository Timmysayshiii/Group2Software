#include <math.h>
#include "calculations.h"

#define a 6378137.0 //earth equatorial radius (wgs84 standard)
#define flattening 0.00335281 //flattening factor of ellipsoid (f = 1/298.257223563)
#define b 6356752.3142  //semi-minor axis (b = a * (1-f)
#define ecc 0.00669437866 //eccentricity (e^2 = 2f - f^2)
#define Pi 3.14159265358979323846

//long double latitudedegreescombined, longitudedegreescombined, altitudemeterscombined;
//long double latituderadianscombined, longituderadianscombined;
//long double cartesianX, cartesianY, cartesianZ, N;

//void combinePositions(lat, lon, alt, lat2, lon2, alt2, lat3, lon3, alt3){
//  printf("\n");
//  latitudedegreescombined = (lat+lat2+lat3)/3;
//	longitudedegreescombined = (lon+lon2+lon3)/3;
//	altitudemeterscombined = (alt+alt2+alt3)/3;
//	printf("\nLatitude combined = %.8Lf", latitudedegreescombined);
//	printf("\nLongitude combined = %.8Lf", longitudedegreescombined);
//	printf("\nAltitude combined = %.8Lf", altitudemeterscombined);	
//}

void getCartesian(double lat, double lng, double altitude, double xyz[3]) {
	lat *= Pi / 180;
	lng *= Pi / 180;
	double N = a/sqrt(1-ecc*pow(sin(lat),2));
	xyz[0] = (N+altitude) * cos(lat) * cos(lng);
	xyz[1] = (N+altitude) * cos(lat) * sin(lng);
	xyz[2] = ((1-ecc)*(N+altitude)) * sin(lat);
}

void getPolar(double *lat, double *lng, double *altitude, double xyz[3]) {
	*lng = atan2(xyz[1], xyz[0]) * (180/Pi);
	
	double p = sqrt(xyz[0] * xyz[0] + xyz[1] * xyz[1]);
	double phi = atan(xyz[2] / ((1 - ecc) * p));
	double h;
	
	double N = a / sqrt(1-ecc*pow(sin(phi), 2));
	h = p / cos(phi) - N;
	phi = atan(xyz[2] / ((1 - ecc * (N / (N + h))) * p));
	
	*altitude = h;
	*lat = phi * (180 / Pi);
}

//void storeCartesian(){
//	
//  printf("\n");
//	printf("\nLatitude degrees in storeCartesian = %.8Lf", latitudedegreescombined);
//	printf("\nLongitude degrees in storeCartesian = %.8Lf", longitudedegreescombined);
//	printf("\nAltitude meters in storeCartesian = %.8Lf", altitudemeterscombined);	
//	
//	latituderadianscombined = latitudedegreescombined * (Pi/180);
//	longituderadianscombined = longitudedegreescombined * (Pi/180);
//	
////	printf("\n\nLatitude radians in storeCartesian = %.8Lf", latituderadians);
////	printf("\n\nLongitude radians in storeCartesian = %.8Lf", longituderadians);
//	
//	N = a/sqrt(1-pow(ecc,2)*pow(sin(latituderadianscombined),2));
////	printf("\n\nN - Radius of curvature in prime vertical = %.8Lf", N);
//	
//	cartesianX = (N+altitudemeterscombined) * cos(latituderadianscombined) * cos(longituderadianscombined);
//	cartesianY = (N+altitudemeterscombined) * cos(latituderadianscombined) * sin(longituderadianscombined);
//	cartesianZ = ((1-pow(ecc,2))*(N+altitudemeterscombined)) * sin(latituderadianscombined);
//	
//	printf("\n\nCartesianX = %.8Lf", cartesianX);
//	printf("\nCartesianY = %.8Lf", cartesianY);
//	printf("\nCartesianZ = %.8Lf", cartesianZ);
//	
//}
