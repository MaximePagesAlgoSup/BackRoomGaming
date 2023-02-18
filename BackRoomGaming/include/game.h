#pragma once
#include "level.h"
#include "menu.h"
#include "player.h"

struct Game {
	Player player;
	Level level[3];
};