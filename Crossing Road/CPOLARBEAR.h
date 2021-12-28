#ifndef _CPOLARBEAR_H_
#define _CPOLARBEAR_H_

#include "CANIMAL.h"

class CPOLARBEAR : public CANIMAL {
public:
	CPOLARBEAR(string typeAsset, string direction, Vector2f pos);
	~CPOLARBEAR() {}

	string getEnemyName() {
		return typeAni;
	}

private:
	string typeAni = "polarBear";
};


#endif // !_CPOLARBEAR_H_