#include "Utility.h"
#include <algorithm>


int Utility::combineBytes(uint8_t MSB, uint8_t LSB)
{
	int combined = 0;

	combined = MSB;
	combined = (MSB << 8) + LSB;

	return combined;
}

int Utility::combineBytesSigned(uint8_t MSB, uint8_t LSB)
{
	int16_t combined = 0;

	combined = MSB;
	combined = (MSB << 8) + LSB;

	return int(combined);
}

bool Utility::IsOutOfRange (float f) {
	return (f < 90 || f > 270);
}

std::vector<float> Utility::fixAngles(std::vector<float> v){
	unsigned int counter =  count_if(v.begin(), v.end(), Utility::IsOutOfRange);
	if (counter > (v.size()/2)) {
		std::vector<float> newV(v);
		for (float& f : newV) {
			if (f > 180 && f < 360) {
				f -= 360;
			}
		}
		return newV;
	}
	return v;
}

float Utility::getMedianValue(std::vector<float> v) {
	if(v.empty()) {
		return 0;
	}
	std::vector<float> fixedV = Utility::fixAngles(v);
	sort(fixedV.begin(), fixedV.begin() + fixedV.size());
	unsigned int middle = (int) fixedV.size()/2;
	float middleValue = 0;
	if (fixedV.size() % 2 == 1) {
		middleValue = fixedV.at(middle);
	}
	else {
		if (fixedV.size() > middle) {
			middleValue = (fixedV.at(middle-1) + fixedV.at(middle)) / 2;
		}
		else {
			middleValue = fixedV.at(middle);
		}
	}
	if(middleValue < 0 ){
		middleValue+=360;
	}
	return middleValue;
}

float Utility::mean(std::vector<float> values)
{
	if (values.size() < 1) return 0;

	float sum = 0;

	for(std::vector<float>::iterator it = values.begin();
		it != values.end(); ++it)
	{
		sum += *it;
	}

	return sum / values.size();
}

/*
 * uses formula for calculating mean of angles
 * https://en.wikipedia.org/wiki/Mean_of_circular_quantities
 */
float Utility::meanOfAngles(std::vector<float> anglesInDegrees)
{
	if (anglesInDegrees.size() < 1) return 0;
	 
	std::vector<float> xx, yy;
	float x, y;

	// convert all angles to cartesian coordinates
	for(std::vector<float>::iterator it = anglesInDegrees.begin();
		it != anglesInDegrees.end(); ++it)
	{
		polarToCartesian(*it, x, y);
		xx.push_back(x);
		yy.push_back(y);
	}

	// use formula
	float meanAngleRadians = atan2(mean(yy), mean(xx));
	// atan2 produces results in the range (−π, π],
	// which can be mapped to [0, 2π) by adding 2π to negative results
	if (meanAngleRadians < 0) meanAngleRadians += 2*M_PI;
	
	return meanAngleRadians * 180/M_PI;
}

void Utility::polarToCartesian(float degrees, float& x, float& y)
{
	x = cos(degrees * M_PI/180);
	y = sin(degrees * M_PI/180);
}

bool Utility::isAngleInSector(double angle, double sectorAngle1, double sectorAngle2)
{
	double diff1 = angleDifference(angle, sectorAngle1);
	double diff2 = angleDifference(angle, sectorAngle2);
	double sectorDiff = angleDifference(sectorAngle1, sectorAngle2);

	if (diff1 < sectorDiff && diff2 < sectorDiff)
		return true;
	else
		return false;
}


double Utility::angleDifference(double angle1, double angle2)
{
	const double fullRevolution = 360;
	
	double diff = std::abs(limitAngleRange(angle1) - limitAngleRange(angle2));
	if (diff > fullRevolution/2) diff = fullRevolution - diff;

	return diff;
}


double Utility::limitAngleRange(double angle)
{
	const double fullRevolution = 360;
	const double minAngle = 0;

	while (angle < minAngle)
		angle += fullRevolution;

	while (angle >= minAngle + fullRevolution)
		angle -= fullRevolution;

	return angle;
}


double Utility::degreeToRadian(double degrees)
{
	return degrees * M_PI / 180;
}


double Utility::radianToDegree(double radians)
{
	return radians / M_PI * 180;
}