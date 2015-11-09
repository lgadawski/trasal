/*
 * City.cpp
 *
 *  Created on: 25 paź 2015
 *      Author: ponaszki
 */
#include <sstream>
#include "City.h"

using namespace std;
string City::ToString() {
	stringstream ss;
	string result;
	ss << this->id;
	ss >> result;
	return result;
}

