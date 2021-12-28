#ifndef _CSIBERIANDOG_H_
#define _CSIBERIANDOG_H_

#include "CANIMAL.h"

class CSIBERIANDOG : public CANIMAL {
public:
	CSIBERIANDOG(string typeAsset, string direction, Vector2f pos);
	~CSIBERIANDOG() {}

	string getEnemyName() {
		return typeAni;
	}

private:
	string typeAni = "siberiandog";
};

#endif // !_CSIBERIANDOG_H_
