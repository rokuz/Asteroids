//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once
#include <chrono>

namespace common
{

class Timer
{
public:
	Timer();
	~Timer();

    void reset();
	float elapsed();

private:
	std::chrono::system_clock::time_point m_lastMeasure;
};

}