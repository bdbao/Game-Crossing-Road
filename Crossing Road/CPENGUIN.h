#ifndef _CPENGUIN_H_
#define _CPENGUIN_H_

#include "CANIMAL.h"

class CPENGUIN : public CANIMAL {
public:
	CPENGUIN(string typeAsset, string direction, Vector2f pos);
	~CPENGUIN() {}

	string getEnemyName() {
		return typeAni;
	}

private:
	string typeAni = "penguin";
};

#endif // !_CPENGUIN_H_