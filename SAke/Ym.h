/*
 * Ym.h
 *
 *  Created on: 01/lug/2015
 *      Author: AlessioProva
 */

#ifndef YM_H_
#define YM_H_
#include<time.h>
class Ym {
public:
	Ym(){

	};
	virtual ~Ym(){
			};

	 tm& getTime() {
		return time;
	}

	void setTime( tm& time) {
		this->time = time;
	}

	double getValue() {
		return value;
	}

	void setValue(double value) {
		this->value = value;
	}

private:
	tm time;
	double value;
};

#endif /* YM_H_ */
