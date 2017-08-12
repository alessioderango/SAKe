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
        i = 0;
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

    int getI() const{
        return i;
    }
    void setI(int value){
        i = value;
    }

private:
    tm time;
    double value;
    int i;
};

#endif /* YM_H_ */

