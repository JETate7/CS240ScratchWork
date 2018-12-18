#ifndef __LANE_H__
#define __LANE_H__

#include "VehicleBase.h"
#include <vector>

class Lane{
        protected:
                int size;
                std::vector<VehicleBase*> lane;

        public:

                Lane();
                Lane(int n);
                ~Lane();

                //VehicleBase * getLane();
                int getSize();
                VehicleBase* getPosition(int i);
                VehicleBase* setPosition(int i, VehicleBase* val);
                VehicleBase* greenMovement(VehicleBase* newSpot);
                VehicleBase* getEndPosition();
                int findBackBumper(VehicleBase* val);
                void redMovement(VehicleBase* newSpot);
};
#endif
