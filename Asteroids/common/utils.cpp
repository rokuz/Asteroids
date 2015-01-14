//
//  Asteroids
//
//  Created by Roman Kuznetsov on 03.09.14.
//  Copyright (c) 2014 rokuz. All rights reserved.
//

#include "utils.h"

#include <stdlib.h>
#include <time.h>

namespace utils
{

void init()
{
	srand((unsigned int)time(0));
}

float random(float _minValue, float _maxValue)
{
	float r = float(rand() % 1000) / float(999);
	return _minValue + r * (_maxValue - _minValue);
}

int random(int _minValue, int _maxValue)
{
	if (_maxValue < _minValue) return 0;
	if (_minValue == _maxValue) return _minValue;
	return _minValue + rand() % (_maxValue - _minValue + 1);
}

bool readFileToString(const std::string& fileName, std::string& out)
{
	FILE* fp = 0;
	size_t filesize = 0;

	fp = fopen(fileName.c_str(), "rb");

	if (!fp) return false;

	fseek(fp, 0, SEEK_END);
	filesize = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	out.resize(filesize + 1);
	fread(&out[0], 1, filesize, fp);
	out[filesize] = 0;

	fclose(fp);

	return true;
}

}