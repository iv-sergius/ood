#define CATCH_CONFIG_MAIN
#include "catch2/catch.hpp"
#include "../WeatherStation/WeatherData.h"

CWeatherData wd;
TEST_CASE("Can add observers", "[WeatherData]") {

	class CUnsafeObserver : public IObserver<SWeatherInfo>
	{
	private:
		void Update(SWeatherInfo const& data) override
		{
			wd.RemoveObserver(*this);
		}
	};
	CUnsafeObserver unsafeObserver;
	wd.RegisterObserver(unsafeObserver);
	SECTION("Should not fall") {
		wd.NotifyObservers();
		CHECK(true);
	}
}