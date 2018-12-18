#ifndef __TRAFFIC_LIGHT_CPP__
#define __TRAFFIC_LIGHT_CPP__

#include "VehicleBase.h"
#include "TrafficLight.h"

		void TrafficLight::setLight(int lightNum){
			this.light = lightNum;
		}

		LightColor TrafficLight::getLight(){
			return this.light;
		}

#endif
