//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "gameField.h"
#include "gameParams.h"
#include "spaceship.h"
#include "asteroid.h"
#include "blast.h"
#include "../common/utils.h"
#include "../graphics/spaceGraphics.h"
#include "../physics/asteroidPhysics.h"
#include "../physics/blastPhysics.h"

namespace logic
{

GameField::GameField(const vector2d& _size) :
	m_size(_size),
	m_lastGeneration(0.0f),
	m_gameStarted(false),
	m_isPaused(false),
    m_isGameOver(false),
	m_gameTime(0.0f)
{
}

GameField::~GameField()
{
	destroy();
}

bool GameField::init()
{
	m_graphics.reset(new graphics::SpaceGraphics());
	m_graphics->init(m_size);
	if (!m_graphics->isValid()) return false;

	m_spaceship.reset(new Spaceship());
	if (!m_spaceship->create(SPACESHIP_HEALTH, vector2d(0, -m_size.y * 0.5f + SPACESHIP_OFFSET_Y), SPACESHIP_SIZE, m_size))
	{
		return false;
	}
	m_spaceship->setCriticalDamageHandler(std::bind(&GameField::onSpaceshipDestroyed, this, std::placeholders::_1));

	return true;
}

void GameField::destroy()
{
	finishGame();

	m_graphics.reset();
	m_spaceship.reset();

	m_asteroidsCache.clear();
	m_blastsCache.clear();
	m_asteroidsToDestroy.clear();
	m_blastsToDestroy.clear();
}

void GameField::startGame()
{
	m_gameStarted = true;
	m_lastGeneration = 0.0f;
	m_gameTime = 0.0f;

	m_spaceship->setHealth(SPACESHIP_HEALTH);
	processGameField(0.0f, true);
}

void GameField::finishGame()
{
	m_gameStarted = false;
    
    m_spaceship->fire(false);

	m_asteroidsCache.insert(m_asteroidsCache.begin(), m_asteroids.begin(), m_asteroids.end());
	m_asteroids.clear();

	m_blastsCache.insert(m_blastsCache.begin(), m_blasts.begin(), m_blasts.end());
	m_blasts.clear();
}
    
bool GameField::isPlaying() const
{
    return m_gameStarted;
}
    
bool GameField::isGameOver() const
{
    return m_isGameOver;
}

void GameField::pauseGame()
{
	m_isPaused = true;
}

void GameField::resumeGame()
{
	m_isPaused = false;
}

void GameField::update(float _dt)
{
	if (m_isPaused) _dt = 0;

	m_graphics->update(_dt);

	if (m_gameStarted)
	{
		processGameField(_dt, false);
		m_gameTime += _dt;
	}

	m_spaceship->setTransformToGameField(m_graphics->getProjection());
	m_spaceship->update(_dt);

	for (auto & asteroid : m_asteroids)
	{
		asteroid->setTransformToGameField(m_graphics->getProjection());
		asteroid->update(_dt);
	}

	for (auto & blast : m_blasts)
	{
		blast->setTransformToGameField(m_graphics->getProjection());
		blast->update(_dt);
	}
}

void GameField::render()
{
	m_graphics->render();
	m_spaceship->render();

	for (auto & asteroid : m_asteroids)
	{
		asteroid->render();
	}

	for (auto & blast : m_blasts)
	{
		blast->render();
	}
}

void GameField::processGameField(float _dt, bool _forceGenerate)
{
	// check for hits: blasts and asteroids
	std::list<std::shared_ptr<Asteroid> > asteroids(m_asteroids.begin(), m_asteroids.end());
	for (auto it = m_blasts.begin(); it != m_blasts.end(); ++it)
	{
		auto blastPhysics = (*it)->getPhysics();
		for (auto & asteroid : asteroids)
		{
			if (blastPhysics->intersects(*asteroid->getPhysics()))
			{
				asteroid->damage(BLAST_DAMAGE);
				m_blastsToDestroy.push_back(*it);
				break;
			}
		}
	}
    
    // check for hits: spaceship and asteroids
	auto spaceshipPhysics = m_spaceship->getPhysics();
	for (auto & asteroid : asteroids)
	{
		if (spaceshipPhysics->intersects(*asteroid->getPhysics()))
		{
			m_spaceship->damage(asteroid->getType() == BIG_ASTEROID ? ASTEROID_BIG_DAMAGE : ASTEROID_SMALL_DAMAGE);
			m_asteroidsToDestroy.push_back(asteroid);
		}
	}

	updateCache();

	// generate new big asteroids
	bool generate = _forceGenerate && !m_isGameOver;
	m_lastGeneration += _dt;
	if (m_lastGeneration >= ASTEROID_GENERATION_TIME)
	{
		m_lastGeneration -= ASTEROID_GENERATION_TIME * (int)(m_lastGeneration / ASTEROID_GENERATION_TIME);
		generate = true;
	}
	if (generate)
	{
		auto positions = generateBigAsteroids();
		for (size_t i = 0; i < positions.size(); i++)
		{
			createAsteroid(BIG_ASTEROID, positions[i]);
		}
	}

	// generate blasts
	auto blasts = m_spaceship->getBlasts(_dt);
	for (size_t i = 0; i < blasts.size(); i++)
	{
		createBlast(blasts[i]);
	}
}

std::vector<vector2d> GameField::generateBigAsteroids()
{
	std::vector<vector2d> result;
	result.reserve(MAX_ASTEROIDS_IN_ROW);

	float slotSize = m_size.x / MAX_ASTEROIDS_IN_ROW;
	for (int i = 0; i < MAX_ASTEROIDS_IN_ROW; i++)
	{
		if (utils::random(0, 1) == 0) continue;
		float x = slotSize * ((float)i + 0.5f) - m_size.x * 0.5f;
		float y = m_size.y * 0.5f + m_size.x * 0.5f / MAX_ASTEROIDS_IN_ROW;
		result.push_back(vector2d(x, y));
	}

	return result;
}


std::vector<vector2d> GameField::generateSmallAsteroids(const vector2d& _position)
{
	std::vector<vector2d> result;

	float offset = 0.25f * m_size.x / MAX_ASTEROIDS_IN_ROW;
	vector2d possiblePositions[3] = 
	{
		_position + vector2d(offset, offset),
		_position + vector2d(-offset, offset),
		_position + vector2d(0, -offset)
	};
	int smallAsteroidsCount = utils::random(2, 3);
	result.reserve(smallAsteroidsCount);
	for (int i = 0; i < smallAsteroidsCount; i++)
	{
		result.push_back(possiblePositions[i]);
	}

	return result;
}

void GameField::createAsteroid(AsteroidType _type, const vector2d& _position)
{
	auto it = std::find_if(m_asteroidsCache.begin(), m_asteroidsCache.end(), [&](std::shared_ptr<Asteroid>& _asteroid) -> bool
	{
		return _asteroid->getType() == _type;
	});

	if (it != m_asteroidsCache.end())
	{
		auto p = *it;
		m_asteroidsCache.erase(it);

		p->setHealth(_type == BIG_ASTEROID ? ASTEROID_BIG_HEALTH : ASTEROID_SMALL_HEALTH);
		p->setPosition(_position);
		m_asteroids.push_back(p);
	}
	else
	{
		std::shared_ptr<Asteroid> asteroid(new Asteroid());

		float r = 0.5f * m_size.x / MAX_ASTEROIDS_IN_ROW;
		if (_type == SMALL_ASTEROID) r *= ASTEROID_SMALL_RADIUS;
		int h = _type == BIG_ASTEROID ? ASTEROID_BIG_HEALTH : ASTEROID_SMALL_HEALTH;

		if (asteroid->create(_type, h, r, _position))
		{
			asteroid->setCriticalDamageHandler(std::bind(&GameField::onAsteroidDestroyed, this, std::placeholders::_1));
			m_asteroids.push_back(asteroid);
		}
	}
}

void GameField::createBlast(const vector2d& _position)
{
	if (!m_blastsCache.empty())
	{
		auto p = *m_blastsCache.begin();
		m_blastsCache.erase(m_blastsCache.begin());

		p->setPosition(_position);
		m_blasts.push_back(p);
	}
	else
	{
		std::shared_ptr<Blast> blast(new Blast());
		if (blast->create(_position))
		{
			m_blasts.push_back(blast);
		}
	}
}

void GameField::updateCache()
{
	for (auto it = m_asteroids.begin(); it != m_asteroids.end();)
	{
		if (isOutsideField(**it) || std::find(m_asteroidsToDestroy.begin(), 
											  m_asteroidsToDestroy.end(), *it) != m_asteroidsToDestroy.end())
		{
			auto p = *it;
			it = m_asteroids.erase(it);
			m_asteroidsCache.push_back(p);
		}
		else ++it;
	}
	m_asteroidsToDestroy.clear();

	for (auto it = m_blasts.begin(); it != m_blasts.end();)
	{
		if (isOutsideField(**it) || std::find(m_blastsToDestroy.begin(), 
											  m_blastsToDestroy.end(), *it) != m_blastsToDestroy.end())
		{
			auto p = *it;
			it = m_blasts.erase(it);
			m_blastsCache.push_back(p);
		}
		else ++it;
	}
	m_blastsToDestroy.clear();
}

bool GameField::isOutsideField(const Asteroid& _asteroid)
{
	auto phys = _asteroid.getPhysics();
	auto position = phys->getTransform().position();
	float d = -m_size.y * 0.5f - 2.0f * phys->getRadius();
	return position.y <= d;
}

bool GameField::isOutsideField(const Blast& _blast)
{
	auto phys = _blast.getPhysics();
	auto position = phys->getTransform().position();
	float d = m_size.y * 0.5f + phys->getLength();
	return position.y >= d;
}

std::shared_ptr<Spaceship> GameField::getSpaceship() const
{
	return m_spaceship;
}

float GameField::getGameTime() const
{
	return m_gameTime;
}

void GameField::onAsteroidDestroyed(Asteroid* _asteroid)
{
	// generate small asteroids
	if (_asteroid->getType() == BIG_ASTEROID)
	{
		auto positions = generateSmallAsteroids(_asteroid->getPhysics()->getTransform().position());
		for (size_t i = 0; i < positions.size(); i++)
		{
			createAsteroid(SMALL_ASTEROID, positions[i]);
		}
	}

	// destroy asteroid
	auto it = std::find_if(m_asteroids.begin(), m_asteroids.end(), [&](std::shared_ptr<Asteroid>& _a) -> bool
	{
		return _a.get() == _asteroid;
	});
	if (it != m_asteroids.end())
	{
		auto p = *it;
		m_asteroidsToDestroy.push_back(p);
	}
}

void GameField::onSpaceshipDestroyed(Spaceship* _spaceship)
{
	finishGame();
    m_isGameOver = true;
}

}