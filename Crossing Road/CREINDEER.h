#ifndef _CREINDEER_H_
#define _CREINDEER_H_

#include "CANIMAL.h"

class CREINDEER : public CANIMAL {
public:
	CREINDEER(string typeAsset, string direction, Vector2f pos);
	~CREINDEER() {}

	string getEnemyName() {
		return typeAni;
	}

private:
	string typeAni = "reindeer";
};


#endif // !_CREINDEER_H_
