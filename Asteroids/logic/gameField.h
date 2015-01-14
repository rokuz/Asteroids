//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <memory>
#include <list>
#include <vector>
#include "../math/vector2D.h"
#include "asteroid.h"

namespace graphics
{
	class SpaceGraphics;
}

namespace logic
{

class Spaceship;
class Blast;

class GameField
{
public:
	GameField(const vector2d& _size);
	~GameField();
	bool init();
	void destroy();
    
    bool isPlaying() const;
    bool isGameOver() const;

	void startGame();
	void finishGame();
	void pauseGame();
	void resumeGame();

	std::shared_ptr<Spaceship> getSpaceship() const;
	float getGameTime() const;

	void update(float _dt);
	void render();

private:
	vector2d m_size;
	std::shared_ptr<graphics::SpaceGraphics> m_graphics;

	bool m_gameStarted;
	bool m_isPaused;
    bool m_isGameOver;
	float m_gameTime;

	std::shared_ptr<Spaceship> m_spaceship;

	std::list<std::shared_ptr<Asteroid> > m_asteroids;
	std::list<std::shared_ptr<Asteroid> > m_asteroidsToDestroy;
	std::list<std::shared_ptr<Asteroid> > m_asteroidsCache;	
	float m_lastGeneration;
	
	std::list<std::shared_ptr<Blast> > m_blasts;
	std::list<std::shared_ptr<Blast> > m_blastsToDestroy;
	std::list<std::shared_ptr<Blast> > m_blastsCache;

	void processGameField(float _dt, bool _forceGenerate);
	void createAsteroid(AsteroidType _type, const vector2d& _position);
	void createBlast(const vector2d& _position);
	std::vector<vector2d> generateBigAsteroids();
	std::vector<vector2d> generateSmallAsteroids(const vector2d& _position);
	void updateCache();
	
	bool isOutsideField(const Asteroid& _asteroid);
	bool isOutsideField(const Blast& _blast);

	void onAsteroidDestroyed(Asteroid* _asteroid);
	void onSpaceshipDestroyed(Spaceship* _spaceship);
};

}