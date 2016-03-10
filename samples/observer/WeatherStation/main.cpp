#include "WeatherData.h"

int main()
{
	CWeatherData wd;
	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);
	return 0;
}