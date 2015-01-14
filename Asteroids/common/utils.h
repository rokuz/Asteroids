//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#pragma once

#include <string>

namespace utils
{

void init();

float random(float _minValue, float _maxValue);
int random(int _minValue, int _maxValue);
bool readFileToString(const std::string& _fileName, std::string& _out);

}