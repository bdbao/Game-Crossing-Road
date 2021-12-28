#ifndef _CBULL_H_
#define _CBULL_H_

#include "CANIMAL.h"

class CBULL : public CANIMAL {
public:
	CBULL(string typeAsset, string direction, Vector2f pos);
	~CBULL() {}

private:
	string typeAni = "bulls";
};


#endif // !_CBULL_H_
