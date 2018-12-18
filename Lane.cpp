#ifndef __LANE_CPP__
#define __LANE_CPP__

#include <iostream>
#include "VehicleBase.h"
#include "Lane.h"

using namespace std;

Lane::Lane(){
	size = 0;}

Lane::Lane(int n){
	//vector<VehicleBase*> lane(n, nullptr);
	for (int i = 0; i < n; i++){
		lane.push_back(nullptr);
	}
        size = n;
}

Lane::~Lane(){}

int Lane::getSize(){
        return size;
}

VehicleBase* Lane::getPosition(int i){
        return lane.at(i);
}

VehicleBase* Lane::getEndPosition(){
	/*cout << "In getEndPosition method" << endl;
	cout << "Size: " << size << endl;
	int lastIndex = size - 1;
	cout << "Last index: " << lastIndex << endl;
	VehicleBase* returnItem = lane[lastIndex];
	cout << "return item: " << returnItem << endl;
*/      int lastIndex = size -1;
	return lane.at(lastIndex);
}

VehicleBase* Lane::setPosition(int i, VehicleBase* val){
        VehicleBase* temp = lane.at(i);
	lane.at(i) = val;
	return temp;
}

int Lane::findBackBumper(VehicleBase* val){
        //return first instance that matches the bumper
        for (int i = 0; i < size; i++){
                if (lane.at(i) == val){
                        return i;
                }
        }

        return -1;
}


//Move all vehicles forward one spot, accepting a new *vehicle to enter
//the lane and returning the *vehicle in the spot exiting the lane.
VehicleBase* Lane::greenMovement(VehicleBase* newSpot){
	/*cout << "In green movement!" << endl;
        VehicleBase* exitingVehicle = lane.at(size - 1);
	cout << "Exiting Vehicle: " << exitingVehicle << endl;
        for (int i = size - 1; i > 0; i--){
                lane.at(i)=lane.at(i-1);
        }
        lane.at(0) = newSpot;*/

	VehicleBase* exitingVehicle = lane.at(size - 1);
	vector<VehicleBase*> temp(size);
	VehicleBase* current;
		
	for (int i = 0; i < size - 1; i++){
		if (lane.at(i) != nullptr){
			current = lane.at(i);
			cout << "Moving vehicle: " << current->getVehicleID() << endl;
			temp.at(i+1) = &(*current);
			cout << "Moved vehicle: " << temp.at(i+1)->getVehicleID() << endl;
		}
                else {
			temp.at(i+1) = nullptr;
		}
        }

	cout << "new spot: " << endl;
	if (newSpot == nullptr){
		cout << "NULL" << endl;
	} else {
		cout << "ID: " << newSpot->getVehicleID() << endl;
	}

	temp.at(0) = newSpot;

	lane.assign(size, nullptr);

	lane = temp;

	cout << "printing adjusted lane: " << endl;
	for (int i = 0; i < size; i++){
		if (lane.at(i) == nullptr) {
			cout << "NULL BLOCK" << endl;
		} else {
			cout << lane.at(i)-> getVehicleID() << endl;
		}
	}

        return exitingVehicle;
}

//Move vehicles forward one spot if they can, with none leaving the lane.
void Lane::redMovement(VehicleBase* newSpot){
        for (int i = size - 1; i > 0; i--){
                if (lane.at(i) == nullptr){ //If the spot ahead is empty, move the *vehicle forward
                        lane.at(i) = &(*lane.at(i-1));
                        lane.at(i-1) = nullptr;
                }
        }
        if (lane.at(0) == nullptr){ //If there's room in the lane, add the potential new vehicle
                lane.at(0) = newSpot;
        }
}
#endif

