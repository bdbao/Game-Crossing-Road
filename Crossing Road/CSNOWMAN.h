#ifndef _CSNOWMAN_H_
#define _CSNOWMAN_H_

#include "CANIMAL.h"

class CSNOWMAN : public CANIMAL {
public:
	CSNOWMAN(string typeAsset, string direction, Vector2f pos);
	~CSNOWMAN() {}

	string getEnemyName() {
		return typeAni;
	}

private:
	string typeAni = "snowman";
};


#endif // !_CSNOWMAN_H_
