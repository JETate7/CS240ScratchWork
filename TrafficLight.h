#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "VehicleBase.h"

class TrafficLight
{
	public:
		LightColor light;
		void setLight();
		LightColor getLight();
};
#endif