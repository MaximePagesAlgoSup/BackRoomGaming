#pragma once
#include "pc.h"
#include "guard.h"

enum State {
	Stealth,
	Panic
};

struct Block
{
	int a;
};


struct Level{
	int ID;
	Guard guards[9999];
	PC player;
	int Timer;
	State state;
	Block blocks[100];
};
