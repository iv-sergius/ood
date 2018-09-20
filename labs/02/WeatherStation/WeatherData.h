#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <climits>
#include <string>
#include "Observer.h"

using namespace std;

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
};

template <typename TData>
class CParameterStats
{
public:
	void AddValue(TData value)
	{
		m_maxValue = value > m_maxValue ? value : m_maxValue;
		m_minValue = value < m_minValue ? value : m_minValue;
		m_accValue += value;
		++m_countValue;
	}
	TData GetMin()const
	{
		return m_minValue;
	}
	TData GetMax()const
	{
		return m_maxValue;
	}
	TData GetAverage()const
	{
		return m_accValue / m_countValue;
	}
private:
	TData m_minValue = std::numeric_limits<TData>::max();
	TData m_maxValue = std::numeric_limits<TData>::min();
	TData m_accValue = 0;
	size_t m_countValue = 0;
};

class CDisplay: public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
		Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
		остается публичным
	*/
	void Update(SWeatherInfo const& data) override
	{
		std::cout << "---- Update Display ----" << std::endl;
		std::cout << "Current Temp " << data.temperature << std::endl;
		std::cout << "Current Hum " << data.humidity << std::endl;
		std::cout << "Current Pressure " << data.pressure << std::endl;
	}
};

class CStatsDisplay : public IObserver<SWeatherInfo>
{
private:
	/* Метод Update сделан приватным, чтобы ограничить возможность его вызова напрямую
	Классу CObservable он будет доступен все равно, т.к. в интерфейсе IObserver он
	остается публичным
	*/
	template <typename TData>
	void PrintParameter(CParameterStats<TData> const& parameter, const std::string const& parameterName)
	{
		std::cout << std::setw(12) << parameterName << " : "
			<< " Max: " << std::setw(5) << parameter.GetMax()
			<< " Min: " << std::setw(5) << parameter.GetMin()
			<< " Average: " << std::setw(6) << parameter.GetAverage() << std::endl;
	}
	void Update(SWeatherInfo const& data) override
	{
		m_humidity.AddValue(data.humidity);
		m_pressure.AddValue(data.pressure);
		m_temperature.AddValue(data.temperature);

		std::cout << "---- Update StatsDisplay ----" << std::endl;
		PrintParameter(m_humidity, "Humidity");
		PrintParameter(m_pressure, "Pressure");
		PrintParameter(m_temperature, "Temperature");
	}
	CParameterStats<double> m_humidity;
	CParameterStats<double> m_pressure;
	CParameterStats<double> m_temperature;
};

class CWeatherData : public CObservable<SWeatherInfo>
{
public:
	// Температура в градусах Цельсия
	double GetTemperature()const
	{
		return m_temperature;
	}
	// Относительная влажность (0...100)
	double GetHumidity()const
	{
		return m_humidity;
	}
	// Атмосферное давление (в мм.рт.ст)
	double GetPressure()const
	{
		return m_pressure;
	}

	void MeasurementsChanged()
	{
		NotifyObservers();
	}

	void SetMeasurements(double temp, double humidity, double pressure)
	{
		m_humidity = humidity;
		m_temperature = temp;
		m_pressure = pressure;

		MeasurementsChanged();
	}
protected:
	SWeatherInfo GetChangedData()const override
	{
		SWeatherInfo info;
		info.temperature = GetTemperature();
		info.humidity = GetHumidity();
		info.pressure = GetPressure();
		return info;
	}
private:
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
