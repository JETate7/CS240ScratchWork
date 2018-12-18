#ifndef __INTERSECTION_H__
#define __INTERSECTION_H__

#include "VehicleBase.h"
#include "Lane.h"
//#include "TrafficLight.h"
#include <vector>

using namespace std;

class Intersection
{
	public:
		Lane* northIn;
		Lane* northOut;
		Lane* southIn;
		Lane* southOut;
		Lane* eastIn;
		Lane* eastOut;
		Lane* westIn;
		Lane* westOut;
		VehicleBase* NE;
		VehicleBase* NW;
		VehicleBase* SE;
		VehicleBase* SW;
		double pNewNorthbound;
		double pNewSouthbound;
		double pNewEastbound;
		double pNewWestbound;
		double portionCars;
		double portionSUV;
		double pRtTurnCar;
		double pLfTurnCar;
		double pRtTurnSUV;
		double pLtTurnSUV;
		double pRtTurnTruck;
		double pLfTurnTruck;


		Intersection(float properties[], Lane* NI, Lane* NO, Lane* EI, Lane* EO, Lane* SI, Lane* SO, Lane* WI, Lane* WO);
		//Intersection(float properties[]);
		~Intersection();

		void MoveTrafficNS();
		void MoveTrafficEW();
		void YellowTickNS( int t );
		void YellowTickEW( int t );
		vector<VehicleBase> addEndVehicles();
		bool randomGen(double d);
		vector<VehicleBase*> getWestbound();
		vector<VehicleBase*> getEastbound();
		vector<VehicleBase*> getNorthbound();
		vector<VehicleBase*> getSouthbound();



};
#endif
