//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include "../math/vector2D.h"

namespace logic
{
	const float GAMEFIELD_SIZE_X = 30;
	const int MAX_ASTEROIDS_IN_ROW = 6;

	const float BLAST_LENGTH = 1.0f;
	const float BLAST_VELOCITY = 20.0f;
	const int BLAST_DAMAGE = 10;
    const float BLAST_COLOR[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	const float ASTEROID_GENERATION_TIME = 0.5f;
	const float ASTEROID_ANGULAR_VELOCITY = 0.7f;
	const float ASTEROID_VELOCITY = 10.0f;
	const int ASTEROID_BIG_HEALTH = 10;
	const int ASTEROID_SMALL_HEALTH = 1;
	const int ASTEROID_BIG_DAMAGE = 100;
	const int ASTEROID_SMALL_DAMAGE = 10;
    const float ASTEROID_SMALL_RADIUS = 0.3f;
	const float ASTEROID_COLOR[4] = { 0.3f, 0.3f, 0.3f, 0.3f };

	const float SPACESHIP_OFFSET_Y = 0.5f;
	const vector2d SPACESHIP_SIZE = vector2d(5.0f, 3.0f);
	const float SPACESHIP_SHOT_TIME = 0.2f;
	const int SPACESHIP_HEALTH = 100;
    const float SPACESHIP_COLOR[4] = { 0.9f, 0.9f, 0.9f, 1.0f };
}