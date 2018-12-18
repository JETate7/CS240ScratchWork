#ifndef __VEHICLE_H__
#define __VEHICLE_H__

#include "VehicleBase.h"

class Vehicle : public VehicleBase
{
	public:
		bool makeTheYellow;
		int vehicleLength;
		Vehicle(int vID, VehicleType type, Direction originalDirection);
		Vehicle(const Vehicle& other);
		~Vehicle();
		int getVehicleLength();
};
#endif
