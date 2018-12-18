#ifndef __VEHICLE_CPP__
#define __VEHICLE_CPP__

#include "VehicleBase.h"
#include "Vehicle.h"



    //default constructor assigning private values
		Vehicle::Vehicle(int vID, VehicleType type, Direction originalDirection){
      this->vehicleID = vID;
      this->vehicleType = type;
      this->vehicleDirection = originalDirection;
    }

    //copy constructor, should we change the ID?
		Vehicle::Vehicle(const Vehicle& other){
      this->vehicleID = other.vehicleID;
      this->vehicleType = other.vehicleType;
      this->vehicleDirection = other.originalDirection;
    }

		Vehicle::~Vehicle(){}

    //type is enumerated
		int Vehicle::getVehicleLength(){
      if(this->vehicleType == 0){
        return 2;
      }
      if(this->vehicleType == 1){
        return 3;
      }
      if(this->vehicleType == 2){
        return 4;
      }
    }


#endif
