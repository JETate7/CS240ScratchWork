#ifndef __INTERSECTION_CPP__
#define __INTERSECTION_CPP__

#include "VehicleBase.h"
#include "Lane.h"
//#include "TrafficLight.h"
#include "Intersection.h"
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;


		Intersection::Intersection(float properties[], Lane* NI, Lane* NO, Lane* EI, Lane* EO, Lane* SI, Lane* SO, Lane* WI, Lane* WO)
		{
			//initialize probabilities
			pNewNorthbound = properties[6];
			pNewSouthbound = properties[7];
			pNewEastbound = properties[8];
			pNewWestbound = properties[9];
			portionCars = properties[10];
			portionSUV = properties[11];
			double portionTruck = 1 - portionCars - portionSUV;
			pRtTurnCar = properties[12];
			pLfTurnCar = properties[13];
			pRtTurnSUV = properties[14];
			pLtTurnSUV = properties[15];
			pRtTurnTruck = properties[16];
			pLfTurnTruck = properties[17];

			//lane size
			int sectionsBeforeIntersection = properties[1];
			int inLaneSize = sectionsBeforeIntersection + 3;

			//create lanes
		/*	Lane northInTemp(inLaneSize);
			northIn = &northInTemp;
			Lane northOutTemp(sectionsBeforeIntersection);
			northOut = &northOutTemp;
			Lane southInTemp(inLaneSize);
			southIn = &southInTemp;
                        Lane southOutTemp(sectionsBeforeIntersection);
			southOut = &southOutTemp;
			Lane eastInTemp(inLaneSize);
			eastIn = &eastInTemp;
			Lane eastOutTemp(sectionsBeforeIntersection);
			eastOut = &eastOutTemp;
			Lane westInTemp(inLaneSize);
			westIn = &westInTemp;
                        Lane westOutTemp(sectionsBeforeIntersection);
			westOut = &westOutTemp;
		*/
			northIn = NI;
			northOut = NO;
			eastIn = EI;
			eastOut = EO;
			southIn = SI;
			southOut = SO;
			westIn = WI;
			westOut = WO;	
			cout << "In constructor: " << endl;
			//cout << "NorthInTemp size: " << northInTemp.getSize() << endl;
			cout << "NorthIn size: " << northIn->getSize() << endl;
		}

		Intersection::~Intersection(){}
/*
		void Intersection::MoveTrafficNS(){

			int type;



			//check if there is a vehicle in the S/W or N/E spots.
			if (NE != nullptr){
				//Check to see if the vehicles have already progressed to N/W or the EO lane
				//If they have already progressed, continue them in either their straight or right turn pattern.
				if (NW == NE){
					northOut->greenMovement(NW);
					NW = NE;
					NE = northIn->greenMovement(nullptr);
					eastOut->greenMovement(nullptr);
				}
				else if (NE == eastOut->getPosition(0)){
					eastOut->greenMovement(NE);
					NE = northIn->greenMovement(nullptr);
					northOut->greenMovement(NW);
					NW = nullptr;
				}
				//If they haven't, determine using random generator if they are turning right or going straight
				else {
					VehicleType next = NE->getVehicleType();
					bool turningRight;
					if (next == VehicleType::truck){
						turningRight = randomGen(pRtTurnTruck);
					}
					if (next == VehicleType::car){
						turningRight = randomGen(pRtTurnCar);
					}
					if (next == VehicleType::suv){
						turningRight = randomGen(pRtTurnSUV);
					}
					//progress according to whether or not they turn right
					if (turningRight){
						eastOut->greenMovement(NE);
						NE = northIn->greenMovement(nullptr);
						northOut->greenMovement(nullptr);
					}
					else {
						northOut->greenMovement(NW);
						NW = NE;
						NE = northIn->greenMovement(nullptr);
						eastOut->greenMovement(nullptr);
					}
				}

			}
			//Otherwise, just progress all traffic in a straight line
			else{
				northOut->greenMovement(NW);
				NW = NE;
				NE = northIn->greenMovement(nullptr);
				eastOut->greenMovement(nullptr);
			}

			if (SW != nullptr){
				//Check to see if the vehicles have already progressed to S/E or the WO lane
				//If they have already progressed, continue them in either their straight or right turn pattern.
				if (SW == SE){
					southOut->greenMovement(SE);
					SE = SW;
					SW = southIn->greenMovement(nullptr);
					westOut->greenMovement(nullptr);
				}
				else if (SW == eastOut->getPosition(0)){
					westOut->greenMovement(SW);
					SW = southIn->greenMovement(nullptr);
					southOut->greenMovement(SE);
					SE = nullptr;
				}
				//If they haven't, determine using random generator if they are turning or going straight
				else {
					VehicleType next = SW->getVehicleType();
					bool turningRight;
					if (next == VehicleType::truck){
						turningRight = randomGen(pRtTurnTruck);
					}
					if (next == VehicleType::car){
						turningRight = randomGen(pRtTurnCar);
					}
					if (next == VehicleType::suv){
						turningRight = randomGen(pRtTurnSUV);
					}
					//progress according to whether or not they turn right
					if (turningRight){
						westOut->greenMovement(SW);
						SW = southIn->greenMovement(nullptr);
						//to ensure all lanes that could be moved are moved
						southOut->greenMovement(nullptr);
					}
					else {
						southOut->greenMovement(SE);
						SE = SW;
						SW = southIn->greenMovement(nullptr);
						westOut->greenMovement(nullptr);
					}
				}
			}
			//Otherwise, just progress all traffic in a straight line
			else {
				southOut->greenMovement(SE);
				SE = SW;
				SW = southIn->greenMovement(nullptr);
			}

			//progress the remaining blocks and lanes; only eastIn->and westIn
			westIn->redMovement(nullptr);
			eastIn->redMovement(nullptr);


			//check to add vehicles to all incoming lanes and add them if it's possible
			addEndVehicles();
		}

		void Intersection::MoveTrafficEW(){}*/

		void Intersection::YellowTickNS(int timeRemaining){
		//For the north lane:
			//Check if there is a vehicle at the start line
			cout << "in YellowTickNS method: " << endl;
			cout << "NorthIn size: " << northIn->getSize() << endl;
			cout << northIn->getEndPosition() << endl;
			if (northIn->getEndPosition() != nullptr){
				cout << "northIn has vehicle in end of lane: " << endl;
				int pos = northIn->findBackBumper(northIn->getEndPosition());
				int remainingSpaces = northIn->getSize() - pos + 2;
				//If the vehicle can't make the red, move using red movement
				if (timeRemaining < remainingSpaces){
					northIn->redMovement(nullptr);
					if (NW == NE){
						northOut->greenMovement(NW);
						NW = NE;
						NE = nullptr;
						eastOut->greenMovement(nullptr);
					}
					else if (NE == eastOut->getPosition(0)){
						eastOut->greenMovement(NE);
						NE = nullptr;
						northOut->greenMovement(NW);
						NW = nullptr;
					}
				}
				//Otherwise, move the vehicle the same as we did in the green method
				else {
					if (NW == NE){
						northOut->greenMovement(NW);
						NW = NE;
						NE = northIn->greenMovement(nullptr);
						eastOut->greenMovement(nullptr);
					}
					else if (NE == eastOut->getPosition(0)){
						eastOut->greenMovement(NE);
						NE = northIn->greenMovement(nullptr);
						northOut->greenMovement(NW);
						NW = nullptr;
					}
					//If they haven't started turning or going straight, determine their path
					//using random generator if they are turning right or going straight
					else {
						VehicleType next = NE->getVehicleType();
						bool turningRight;
						if (next == VehicleType::truck){
							turningRight = randomGen(pRtTurnTruck);
						}
						if (next == VehicleType::car){
							turningRight = randomGen(pRtTurnCar);
						}
						if (next == VehicleType::suv){
							turningRight = randomGen(pRtTurnSUV);
						}
						//progress according to whether or not they turn right
						if (turningRight){
							eastOut->greenMovement(NE);
							NE = northIn->greenMovement(nullptr);
							northOut->greenMovement(nullptr);
						}
						else {
							northOut->greenMovement(NW);
							NW = NE;
							NE = northIn->greenMovement(nullptr);
							eastOut->greenMovement(nullptr);
						}
					}
				}
			}
				//If there isn't a vehicle at the start line, we just progress normally.
				else{
					cout << "Attempting to go straight forward" << endl;
					northOut->greenMovement(NW);
					NW = NE;
					NE = northIn->greenMovement(nullptr);
					eastOut->greenMovement(nullptr);
					cout << "Succeeded" << endl;
				}

		//For the south lane:
			//Check if there is a vehicle at the start line
			if (southIn->getEndPosition() != nullptr){
				int pos = southIn->findBackBumper(southIn->getEndPosition());
				int remainingSpaces = southIn->getSize() - pos + 2;
				//If the vehicle can't make the red, move using red movement
				if (timeRemaining < remainingSpaces){
					southIn->redMovement(nullptr);
					if (SE == SW){
						southOut->greenMovement(SE);
						SE = SW;
						SW = nullptr;
						westOut->greenMovement(nullptr);
					}
					else if (SW == eastOut->getPosition(0)){
						westOut->greenMovement(SW);
						SW = nullptr;
						southOut->greenMovement(SW);
						SE = nullptr;
					}
				}
				//Otherwise, move the vehicle the same as we did in the green method
				else {
					if (SE == SW){
						southOut->greenMovement(SE);
						SE = SW;
						SW = southIn->greenMovement(nullptr);
						westOut->greenMovement(nullptr);
					}
					//if a vehicle had already started turning right
					else if (SW == eastOut->getPosition(0)){
						westOut->greenMovement(SW);
						SW = southIn->greenMovement(nullptr);
						southOut->greenMovement(SE);
						SE = nullptr;
					}
					//If they haven't started turning or going straight, determine their path
					//using random generator if they are turning right or going straight
					else {
						VehicleType next = SW->getVehicleType();
						bool turningRight;
						if (next == VehicleType::truck){
							turningRight = randomGen(pRtTurnTruck);
						}
						if (next == VehicleType::car){
							turningRight = randomGen(pRtTurnCar);
						}
						if (next == VehicleType::suv){
							turningRight = randomGen(pRtTurnSUV);
						}
						//progress according to whether or not they turn right
						if (turningRight){
							westOut->greenMovement(SW);
							SW = northIn->greenMovement(nullptr);
							southOut->greenMovement(nullptr);
						}
						else {
							southOut->greenMovement(SE);
							SE = SW;
							SW = southIn->greenMovement(nullptr);
							westOut->greenMovement(nullptr);
						}
					}
				}
			}
				//If there isn't a vehicle at the start line, we just progress normally.
				else{
					southOut->greenMovement(SE);
					SE = SW;
					SW = southIn->greenMovement(nullptr);
					westOut->greenMovement(nullptr);
				}

			//Progress the incoming west and east lanes by red movement
			westIn->redMovement(nullptr);
			eastIn->redMovement(nullptr);
		}



		void Intersection::YellowTickEW(int timeRemaining){
		//For the east lane:
			//replace:
			//east = south, north = east
			//NE = SE, NW = NE
			//Check if there is a vehicle at the start line
			if (eastIn->getEndPosition() != nullptr){
				int pos = eastIn->findBackBumper(eastIn->getEndPosition());
				int remainingSpaces = eastIn->getSize() - pos + 2;
				//If the vehicle can't make the red, move using red movement
				if (timeRemaining < remainingSpaces){
					eastIn->redMovement(nullptr);
					//(was NW == NE)
					if (NE == SE){
						eastOut->greenMovement(NE);
						NE = SE;
						SE = nullptr;
						southOut->greenMovement(nullptr);
					}
					else if (SE == southOut->getPosition(0)){
						southOut->greenMovement(SE);
						SE = nullptr;
						eastOut->greenMovement(NE);
						NE = nullptr;
					}
				}
				//Otherwise, move the vehicle the same as we did in the green method
				else {
					if (NE == SE){
						eastOut->greenMovement(NE);
						NE = SE;
						SE = eastIn->greenMovement(nullptr);
						southOut->greenMovement(nullptr);
					}
					else if (SE == southOut->getPosition(0)){
						southOut->greenMovement(SE);
						SE = eastIn->greenMovement(nullptr);
						eastOut->greenMovement(NE);
						NE = nullptr;
					}
					//If they haven't started turning or going straight, determine their path
					//using random generator if they are turning right or going straight
					else {
						VehicleType next = SE->getVehicleType();
						bool turningRight;
						if (next == VehicleType::truck){
							turningRight = randomGen(pRtTurnTruck);
						}
						if (next == VehicleType::car){
							turningRight = randomGen(pRtTurnCar);
						}
						if (next == VehicleType::suv){
							turningRight = randomGen(pRtTurnSUV);
						}
						//progress according to whether or not they turn right
						if (turningRight){
							southOut->greenMovement(SE);
							SE = eastIn->greenMovement(nullptr);
							eastOut->greenMovement(nullptr);
						}
						else {
							eastOut->greenMovement(NE);
							NE = SE;
							SE = eastIn->greenMovement(nullptr);
							southOut->greenMovement(nullptr);
						}
					}
				}
			}
				//If there isn't a vehicle at the start line, we just progress normally.
				else{
					eastOut->greenMovement(NE);
					NE = SE;
					SE = eastIn->greenMovement(nullptr);
					southOut->greenMovement(nullptr);
				}

		//For the west lane:
			//replace:
			//west = north, south = west
			//SW = NW, SE = SW
			//Check if there is a vehicle at the start line
			if (westIn->getEndPosition() != nullptr){
					int pos = westIn->findBackBumper(westIn->getEndPosition());
					int remainingSpaces = westIn->getSize() - pos + 2;
					//If the vehicle can't make the red, move using red movement
					if (timeRemaining < remainingSpaces){
								westIn->redMovement(nullptr);
								//was (SE == SW)
								if (SW == NW){
								southOut->greenMovement(SW);
								SW = NW;
								NW = nullptr;
								northOut->greenMovement(nullptr);
								}
								else if (NW == northOut->getPosition(0)){
										northOut->greenMovement(NW);
										NW = nullptr;
										westOut->greenMovement(NW);
										SW = nullptr;
								}
				}
				//Otherwise, move the vehicle the same as we did in the green method
				else {
							if (SW == NW){
									westOut->greenMovement(SW);
									SW = NW;
									NW = westIn->greenMovement(nullptr);
									northOut->greenMovement(nullptr);
							}
							//if a vehicle had already started turning right
							else if (NW == northOut->getPosition(0)){
									northOut->greenMovement(SE);
									NW = westIn->greenMovement(nullptr);
									westOut->greenMovement(SW);
									SW = nullptr;
							}
							//If they haven't started turning or going straight, determine their path
							//using random generator if they are turning right or going straight
							else {
									VehicleType next = NW->getVehicleType();
									bool turningRight;
									if (next == VehicleType::truck){
											turningRight = randomGen(pRtTurnTruck);
									}
									if (next == VehicleType::car){
											turningRight = randomGen(pRtTurnCar);
									}
									if (next == VehicleType::suv){
											turningRight = randomGen(pRtTurnSUV);
									}
									//progress according to whether or not they turn right
									if (turningRight){
											northOut->greenMovement(NW);
											NW = westIn->greenMovement(nullptr);
											westOut->greenMovement(nullptr);
									}
									else {
											westOut->greenMovement(SW);
											SW = NW;
											NW = westIn->greenMovement(nullptr);
											northOut->greenMovement(nullptr);
									}
							}
					}
			}
				//If there isn't a vehicle at the start line, we just progress normally.
			else{
					westOut->greenMovement(SW);
					SW = NW;
					NW = westIn->greenMovement(nullptr);
					northOut->greenMovement(nullptr);
			}

			//Progress the incoming north and south lanes by red movement
			northIn->redMovement(nullptr);
			southIn->redMovement(nullptr);
		}

		vector<VehicleBase> Intersection::addEndVehicles(){

			//create new incoming vehicles;
			vector<VehicleBase> newVs;
			//VehicleBase newNorth;
			//VehicleBase newSouth;
			//VehicleBase newEast;
			//VehicleBase newWest;
			int type;

			//check to see if north can have a new vehicle
			if (northIn->getPosition(3) == nullptr){
				cout << "NorthIn has room for a new vehicle." << endl;
				//if it can, check if it does
				if (randomGen(pNewNorthbound)){
					//if it does, determine the type and set the spaces appropriately
					type = rand()%100;
					if (type <= portionCars*100){
						VehicleBase newNorth(VehicleType::car, Direction::north);
						northIn->setPosition(3, &newNorth);
						northIn->setPosition(2, &newNorth);
						newVs.push_back(std::move(newNorth));
					}

					else if (type <= (1 - portionSUV)*100){
						VehicleBase newNorth(VehicleType::truck, Direction::north);
						northIn->setPosition(3, &newNorth);
						northIn->setPosition(2, &newNorth);
						northIn->setPosition(1, &newNorth);
						northIn->setPosition(0, &newNorth);
			                        newVs.push_back(move(newNorth));
					}

					else {
						VehicleBase newNorth(VehicleType::suv, Direction::north);
						northIn->setPosition(3, &newNorth);
						northIn->setPosition(2, &newNorth);
						northIn->setPosition(1, &newNorth);
                                                newVs.push_back(move(newNorth));
					}
				}
			}

			//check if south can have a new vehicle
			if (southIn->getPosition(3) == nullptr){
				//if it can, check if it does
				if (randomGen(pNewSouthbound)){
					//if it does, determine the type and set the spaces appropriately
					type = rand()%100;
					if (type <= portionCars*100){
						VehicleBase newSouth(VehicleType::car, Direction::south);
						southIn->setPosition(3, &newSouth);
						southIn->setPosition(2, &newSouth);
                                                newVs.push_back(newSouth);
					}

					else if (type <= (1 - portionSUV)*100){
						VehicleBase newSouth(VehicleType::truck, Direction::south);
						southIn->setPosition(3, &newSouth);
						southIn->setPosition(2, &newSouth);
						southIn->setPosition(1, &newSouth);
						southIn->setPosition(0, &newSouth);
                                                newVs.push_back(newSouth);
					}

					else {
						VehicleBase newSouth(VehicleType::suv, Direction::south);
						southIn->setPosition(3, &newSouth);
						southIn->setPosition(2, &newSouth);
						southIn->setPosition(1, &newSouth);
                                                newVs.push_back(newSouth);
					}
				}
			}

			//check if east can have a new vehicle
			if (eastIn->getPosition(3) == nullptr){
				//if it can, check if it does
				if (randomGen(pNewEastbound)){
					//if it does, determine the type and set the spaces appropriately
					type = rand()%100;
					if (type <= portionCars*100){
						VehicleBase newEast(VehicleType::car, Direction::east);
						eastIn->setPosition(3, &newEast);
						eastIn->setPosition(2, &newEast);
                                                newVs.push_back(newEast);
					}

					else if (type <= (1 - portionSUV)*100){
						VehicleBase newEast(VehicleType::truck, Direction::east);
						eastIn->setPosition(3, &newEast);
						eastIn->setPosition(2, &newEast);
						eastIn->setPosition(1, &newEast);
						eastIn->setPosition(0, &newEast);
                                                newVs.push_back(newEast);
					}

					else {
						VehicleBase newEast(VehicleType::suv, Direction::east);
						eastIn->setPosition(3, &newEast);
						eastIn->setPosition(2, &newEast);
						eastIn->setPosition(1, &newEast);
                                                newVs.push_back(newEast);
					}
				}
			}

			//check if west can have a new vehicle
			if (westIn->getPosition(3) == nullptr){
				//if it can, check if it does
				if (randomGen(pNewWestbound)){
					//if it does, determine the type and set the spaces appropriately
					type = rand()%100;
					if (type <= portionCars*100){
						VehicleBase newWest(VehicleType::car, Direction::west);
						westIn->setPosition(3, &newWest);
						westIn->setPosition(2, &newWest);
                                                newVs.push_back(newWest);

					}

					else if (type <= (1 - portionSUV)*100){
						VehicleBase newWest(VehicleType::truck, Direction::west);
						westIn->setPosition(3, &newWest);
						westIn->setPosition(2, &newWest);
						westIn->setPosition(1, &newWest);
						westIn->setPosition(0, &newWest);
                                                newVs.push_back(newWest);

					}

					else {
						VehicleBase newWest(VehicleType::suv, Direction::west);
						westIn->setPosition(3, &newWest);
						westIn->setPosition(2, &newWest);
						westIn->setPosition(1, &newWest);
                                                newVs.push_back(newWest);

					}
				}
			}
			
			cout << "Added vehicles: " << endl;
			for (int i = 0; i < newVs.size(); i++){
				cout << "ID: " << newVs.at(i).getVehicleID();
				cout << " Direction: ";
				if (newVs.at(i).getVehicleOriginalDirection() == Direction::north){
					cout << "north" << endl;
				} else if (newVs.at(i).getVehicleOriginalDirection() == Direction::south){
					cout << "south" << endl;
				} else if (newVs.at(i).getVehicleOriginalDirection() == Direction::west){
					cout << "west" << endl;
				} else if (newVs.at(i).getVehicleOriginalDirection() == Direction::east){
					cout << "east" << endl;
				}
			}
			
			return (std::move(newVs));
		}

		bool Intersection::randomGen(double probability){
			cout << "In random generator method" << endl;
			int val = rand()%100 + 1;
			int threshold = (int) (probability*100);

			cout << "Random value: " << val << " Threshold: " << threshold << endl;

			return (val <= threshold);
		}


		std::vector<VehicleBase*> Intersection::getNorthbound(){
			std::vector<VehicleBase*> northLane;
			for(int i = 3; i < northIn->getSize(); i++){
				northLane.push_back(northIn->getPosition(i));
			}
			northLane.push_back(NE);
			northLane.push_back(NW);
			for(int i = 0; i < northOut->getSize(); i++){
				northLane.push_back(northOut->getPosition(i));
			}
			return northLane;
		}

		std::vector<VehicleBase*> Intersection::getSouthbound(){
			std::vector<VehicleBase*> southLane;
			for(int i = 3; i < southIn->getSize(); i++){
				southLane.push_back(southIn->getPosition(i));
			}
			southLane.push_back(SW);
			southLane.push_back(SE);
			for(int i = 0; i < southOut->getSize(); i++){
				southLane.push_back(southOut->getPosition(i));
			}
			return southLane;
		}

		std::vector<VehicleBase*> Intersection::getEastbound(){
			std::vector<VehicleBase*> eastLane;
			for(int i = 3; i < eastIn->getSize(); i++){
				eastLane.push_back(eastIn->getPosition(i));
			}
			eastLane.push_back(SE);
			eastLane.push_back(NE);
			for(int i = 0; i < eastOut->getSize(); i++){
				eastLane.push_back(eastOut->getPosition(i));
			}
			return eastLane;
		}

		std::vector<VehicleBase*> Intersection::getWestbound(){
			std::vector<VehicleBase*> westLane;
			for(int i = 3; i < westIn->getSize(); i++){
				westLane.push_back(westIn->getPosition(i));
			}
			westLane.push_back(NW);
			westLane.push_back(SW);
			for(int i = 0; i < westOut->getSize(); i++){
				westLane.push_back(westOut->getPosition(i));
			}
			return westLane;
		}



#endif
