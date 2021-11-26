#ifndef _CPEOPLE_H_
#define _CPEOPLE_H_

#include "CANIMAL.h"
#include "CVEHICLE.h"

class CPEOPLE {
	int mX, mY;
	bool mState; //Trạng thái sống chết
public:
	CPEOPLE();
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);
	bool isFinish();
	bool isDead();
};

#endif // !_CPEOPLE_H_
