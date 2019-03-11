// Class used to determine the direction the frame is heading
#include <math.h>
#include "VincentyDistance.h"


struct X_pos{
	double X_lat;
	double X_lng;
}x_position;

float Bearing_calc(double i_lat,double i_lng,double n_lat,double n_lng){

struct X_pos xpos;
	
xpos.X_lat = n_lat;
xpos.X_lng = i_lng;
	
// need to find distance between inital lat & long and pos X lat&long using vincinties formula
	double Ax_distance=distanceVincenty(xpos.X_lat,xpos.X_lng, i_lat,i_lng);
	
// need to find distance between new lat & long and pos X lat&long using vincinties formula	
	double Bx_distance = distanceVincenty(xpos.X_lat,xpos.X_lng, n_lat,n_lng);

// heading angle
	float heading_angle = atan(Ax_distance/Bx_distance);
	
	return heading_angle;
}





