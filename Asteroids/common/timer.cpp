//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "timer.h"

namespace common
{

Timer::Timer()
{
	m_lastMeasure = std::chrono::system_clock::from_time_t(0);
}

Timer::~Timer()
{
}
    
void Timer::reset()
{
    m_lastMeasure = std::chrono::system_clock::from_time_t(0);
}

float Timer::elapsed()
{
	if (m_lastMeasure.time_since_epoch().count() == 0)
	{
		m_lastMeasure = std::chrono::system_clock::now();
		return 0.0f;
	}

	auto curTime = std::chrono::system_clock::now();
	float m = (float)std::chrono::duration_cast<std::chrono::milliseconds>(curTime - m_lastMeasure).count() / 1000.0f;
	m_lastMeasure = curTime;
	
	return m;
}

}