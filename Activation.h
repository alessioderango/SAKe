/*
 * Activation.h
 *
 *  Created on: 01/lug/2015
 *      Author: AlessioProva
 */

#ifndef ACTIVATION_H_
#define ACTIVATION_H_
#include <time.h>

class Activation {
public:
	Activation(tm _start,tm _end){
		start =_start;
		end =_end;
	}

	Activation(){}
	virtual ~Activation(){};

     tm& getEnd()  {
		return end;
	}

    void setEnd( tm& end) {
		this->end = end;
	}

     tm& getStart()  {
		return start;
	}

    void setStart( tm& start) {
		this->start = start;
	}

private:
	tm start;
	tm end;

};

#endif /* ACTIVATION_H_ */
