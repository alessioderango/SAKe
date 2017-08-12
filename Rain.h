/*
 * Rain.h
 *
 *  Created on: 30/giu/2015
 *      Author: AlessioProva
 */

#ifndef RAIN_H_
#define RAIN_H_

#include <time.h>

class Rain {
public:

	Rain(){}
	Rain(tm _time, double _rain_mm){
		time = _time;
		rainfall_mm = _rain_mm;
	}
	virtual ~Rain(){}

	double getRainMm()  {
		return rainfall_mm;
	}

	void setRainMm(double rainMm) {
		rainfall_mm = rainMm;
	}

	 tm& getTime()  {
		return time;
	}

	void setTime( tm& time) {
		this->time = time;
	}

private:
	tm time;
	double rainfall_mm;

};


#endif /* RAIN_H_ */
