#ifndef __TRAFFIC_SIM_CPP__
#define __TRAFFIC_SIM_CPP__

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "Intersection.h"
#include "VehicleBase.h"
//#include "TrafficLight.h"
#include "Lane.h"
#include "Vehicle.h"
#include "Animator.h"

vector<VehicleBase> allVehicles;

int main(int argc, char *argv[]){

	ifstream infile;
	string line;
  	float properties[18];
  	int count = 0;

  //Read parameters from input file
  infile.open(argv[1]);
  cout<< "reading from " << argv[0] << endl;
  if (infile.is_open())
  {
    while ( infile.good() )
      {
	       getline(infile, line);
         int colonindex = line.find_first_of(":");
         if(colonindex < 0){
           break;
         }
        // cout << line << endl;
        // cout << line.find_first_of(":") << endl;
        // cout << line.find_first_not_of(" ",line.find_first_of(":") + 1) << endl;
        // cout << line.substr(line.find_first_not_of(" ",line.find_first_of(":") + 1)) << endl;
        // cout << stof(line.substr(line.find_first_not_of(" ",line.find_first_of(":") + 1))) << endl;
         properties[count] = stof(line.substr(line.find_first_not_of(" ",line.find_first_of(":") + 1)));
         count++;
      }
      infile.close();
  }
  else
  {
      cout << "Unable to open file";
  }

  //Create instance of Instersection
  cout<<"read " << count << " lines" << endl;
  cout << count << endl;
  cout << "____Printing properties____" << endl;
  for(int i = 0; i < 18; i++){
    cout << properties[i] << endl;
  }

  //construct lanes
	int inLaneSize = properties[1] + 3;
	int sectionsBeforeIntersection = properties[1];

	Lane northInTemp(inLaneSize);
        Lane northOutTemp(sectionsBeforeIntersection);
        Lane southInTemp(inLaneSize);
        Lane southOutTemp(sectionsBeforeIntersection);
        Lane eastInTemp(inLaneSize);
        Lane eastOutTemp(sectionsBeforeIntersection);
        Lane westInTemp(inLaneSize);
        Lane westOutTemp(sectionsBeforeIntersection);

	cout << "Attempting to print northbound: " << endl;
                for (int k = 0; k < inLaneSize; k++){
                        //cout << northInTemp.getPosition(k)->getVehicleID() << endl;
                        cout << (northInTemp.getPosition(k) == nullptr) << endl;
                }

  Intersection in(properties, &northInTemp, &northOutTemp, &eastInTemp, &eastOutTemp, &southInTemp, &southOutTemp, &westInTemp, &westOutTemp);
  //cout << in.properties[10] << endl;
  cout << "External check of northIn: " << in.northIn->getSize() << endl;

  //Generate clock-tick and progress simulation
	//read in required fields for timing
	int maxSimTime = properties[0];
	int gNStime = properties[2];
	int yNStime = properties[3];
	int gEWtime = properties[4];
	int yEWtime = properties[5];

	//determine number of seconds for a complete cycle
	int totalLoopTime = gNStime + yNStime + gEWtime + yEWtime;
	int gNSend = gNStime;
	int yNSend = gNSend+yNStime;
	int gEWend = yNSend+gEWtime;

	//create instance of animator
  char dummy;

	Animator anim(properties[1]);
	std::vector<VehicleBase*> westbound(properties[1]*2+2, nullptr);
	std::vector<VehicleBase*> eastbound(properties[1]*2+2, nullptr);
	std::vector<VehicleBase*> northbound(properties[1]*2+2, nullptr);
	std::vector<VehicleBase*> southbound(properties[1]*2+2, nullptr);

	cout << "here1" << endl;
	anim.setLightEastWest(LightColor::red);
	cout << "here2" << endl;
	anim.setLightNorthSouth(LightColor::green);

	anim.setVehiclesNorthbound(northbound);
	cout << "here3" << endl;
	anim.setVehiclesWestbound(westbound);
	cout << "here4" << endl;
	anim.setVehiclesSouthbound(southbound);
	cout << "here5" << endl;
	anim.setVehiclesEastbound(eastbound);
	cout << "here6" << endl;

	cout << "Attempting to print northbound: " << endl;
                for (int k = 0; k < inLaneSize; k++){
                        //cout << northInTemp.getPosition(k)->getVehicleID() << endl;
                        cout << (northInTemp.getPosition(k) == nullptr) << endl;
                }

	anim.draw(0);
	std::cin.get(dummy);

	vector<VehicleBase> allVehicles(0);

	for (int i = 1; i < maxSimTime; i++){
		int j = i%totalLoopTime;
		if (j < gNSend){
			//perform green movement clocktick going NS
			cout << "here6.5" << endl;
			in.YellowTickNS(30);
			//animate
			anim.setLightNorthSouth(LightColor::green);
			cout << "here7" << endl;
			anim.setLightEastWest(LightColor::red);
			cout << "here8" << endl;

		}
		else if (j < yNSend){
			//perform yellow movement clocktick going NS
			in.YellowTickNS(yNSend - j);
			//animate
			anim.setLightNorthSouth(LightColor::yellow);
			cout << "here9" << endl;
			anim.setLightEastWest(LightColor::red);
			cout << "here10" << endl;
		}
		else if (j < gEWend){
			//perform green movement clocktick going EW
			in.YellowTickEW(30);
			//animate
			anim.setLightNorthSouth(LightColor::red);
			cout << "here11" << endl;
			anim.setLightEastWest(LightColor::green);
			cout << "here12" << endl;
		}
		else {
			//perform yellow movement clocktick going EW
			in.YellowTickEW(totalLoopTime-j);
			//animate
			anim.setLightNorthSouth(LightColor::red);
			cout << "here13" << endl;
			anim.setLightEastWest(LightColor::yellow);
			cout << "here14" << endl;
		}

		int type;

		if (northInTemp.getPosition(3) == nullptr){
                         cout << "NorthIn has room for a new vehicle." << endl;
                                //if it can, check if it does
                                if (in.randomGen(properties[6])){
                                        //if it does, determine the type and set the spaces appropriately
                                        type = rand()%100;
                                        if (type <= properties[10]*100){
                                                VehicleBase* newNorth = new VehicleBase(VehicleType::car, Direction::north);
                                                allVehicles.push_back(*newNorth);
						northInTemp.setPosition(3, newNorth);
                                                northInTemp.setPosition(2, newNorth);
                                        }

                                        else if (type <= (1 - properties[11])*100){
                                                VehicleBase* newNorth = new VehicleBase(VehicleType::truck, Direction::north);
                                                allVehicles.push_back(*newNorth);
						northInTemp.setPosition(3, newNorth);
                                                northInTemp.setPosition(2, newNorth);
                                                northInTemp.setPosition(1, newNorth);
                                                northInTemp.setPosition(0, newNorth);
                                        }

                                        else {
                                                VehicleBase* newNorth = new VehicleBase(VehicleType::suv, Direction::north);
                                                allVehicles.push_back(*newNorth);
					        northInTemp.setPosition(3, newNorth);
                                                northInTemp.setPosition(2, newNorth);
                                                northInTemp.setPosition(1, newNorth);
                                        }
                                }
                        }


		//check if south can have a new vehicle
                        if (southInTemp.getPosition(3) == nullptr){
                                //if it can, check if it does
                                if (in.randomGen(properties[7])){
                                        //if it does, determine the type and set the spaces appropriately
                                        type = rand()%100;
                                        if (type <= properties[10]*100){
                                                VehicleBase* newSouth = new VehicleBase(VehicleType::car, Direction::south);
                                        	allVehicles.push_back(*newSouth);
					        southInTemp.setPosition(3, newSouth);
                                                southInTemp.setPosition(2, newSouth);
                                        }

                                        else if (type <= (1 - properties[11])*100){
                                                VehicleBase* newSouth = new VehicleBase(VehicleType::truck, Direction::south);
                                                allVehicles.push_back(*newSouth);
                                                southInTemp.setPosition(3, newSouth);
                                                southInTemp.setPosition(2, newSouth);
                                                southInTemp.setPosition(1, newSouth);
                                                southInTemp.setPosition(0, newSouth);
                                        }

                                        else {
                                                VehicleBase* newSouth = new VehicleBase(VehicleType::suv, Direction::south);
                                                allVehicles.push_back(*newSouth);
                                                southInTemp.setPosition(3, newSouth);
                                                southInTemp.setPosition(2, newSouth);
                                                southInTemp.setPosition(1, newSouth);
                                        }
                                }
                        }

		//check if east can have a new vehicle
                        if (eastInTemp.getPosition(3) == nullptr){
                                //if it can, check if it does
                                if (in.randomGen(properties[8])){
                                        //if it does, determine the type and set the spaces appropriately
                                        type = rand()%100;
                                        if (type <= properties[10]*100){
                                                VehicleBase* newEast = new VehicleBase(VehicleType::car, Direction::east);
                                                allVehicles.push_back(*newEast);
                                                eastInTemp.setPosition(3, newEast);
                                                eastInTemp.setPosition(2, newEast);
                                        }

                                        else if (type <= (1 - properties[11])*100){
                                                VehicleBase* newEast = new VehicleBase(VehicleType::truck, Direction::east);
                                        	allVehicles.push_back(*newEast);
					        eastInTemp.setPosition(3, newEast);
                                                eastInTemp.setPosition(2, newEast);
                                                eastInTemp.setPosition(1, newEast);
                                                eastInTemp.setPosition(0, newEast);
                                        }

                                        else {
                                                VehicleBase* newEast = new VehicleBase(VehicleType::suv, Direction::east);
                                        	allVehicles.push_back(*newEast);
					        eastInTemp.setPosition(3, newEast);
                                                eastInTemp.setPosition(2, newEast);
                                                eastInTemp.setPosition(1, newEast);
                                        }
                                }
                        }

                        //check if west can have a new vehicle
                        if (westInTemp.getPosition(3) == nullptr){
                                //if it can, check if it does
                                if (in.randomGen(properties[9])){
                                        //if it does, determine the type and set the spaces appropriately
                                        type = rand()%100;
                                        if (type <= properties[10]*100){
                                                VehicleBase* newWest = new VehicleBase(VehicleType::car, Direction::west);
						allVehicles.push_back(*newWest);
                                                westInTemp.setPosition(3, newWest);
                                                westInTemp.setPosition(2, newWest);

                                        }

                                        else if (type <= (1 - properties[11])*100){
                                                VehicleBase* newWest = new VehicleBase(VehicleType::truck, Direction::west);
						allVehicles.push_back(*newWest);
                                                westInTemp.setPosition(3, newWest);
                                                westInTemp.setPosition(2, newWest);
                                                westInTemp.setPosition(1, newWest);
                                                westInTemp.setPosition(0, newWest);

                                        }

                                        else {
                                                VehicleBase* newWest = new VehicleBase(VehicleType::suv, Direction::west);
						allVehicles.push_back(*newWest);
                                                westInTemp.setPosition(3, newWest);
                                                westInTemp.setPosition(2, newWest);
                                                westInTemp.setPosition(1, newWest);

                                        }
                                }
                        }


		for (int i = 0; i < allVehicles.size(); i++){
			cout << "Vehicle index " << i << " stores val " << allVehicles.at(i).getVehicleID() << endl;
		}

		cout << "Attempting to print northIn: " << endl;
		for (int k = 0; k < inLaneSize; k++){
			if (northInTemp.getPosition(k) == nullptr){
				cout << "Null block" << endl;
			}
			else {
				cout << "Stores vehicle " << northInTemp.getPosition(k)->getVehicleID() << endl;
			}
		}

		westbound = in.getWestbound();
		eastbound = in.getEastbound();
		southbound = in.getSouthbound();
		northbound = in.getNorthbound();

		cout << "Attempting to print northbound: " << endl;
                for (int k = 0; k < northbound.size(); k++){
                        if (northbound.at(k) == nullptr){
                                cout << "Null block" << endl;
                        }
                        else {
                                cout << "Stores vehicle " << northbound.at(k)->getVehicleID() << endl;
                        }
                }

		anim.setVehiclesNorthbound(northbound);
		anim.setVehiclesWestbound(westbound);
		anim.setVehiclesSouthbound(southbound);
		anim.setVehiclesEastbound(eastbound);

		anim.draw(i);
		std::cin.get(dummy);

		northbound.assign(properties[1]*2+2, nullptr);
                southbound.assign(properties[1]*2+2, nullptr);
                eastbound.assign(properties[1]*2+2, nullptr);
                westbound.assign(properties[1]*2+2, nullptr);

	}
	
  return 0;
}


#endif
