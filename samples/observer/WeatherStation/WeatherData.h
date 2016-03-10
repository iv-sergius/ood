#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class IObserver
{
public:
	virtual void Update(double temp, double humidity, double pressure) = 0;
protected:
	~IObserver() = default;
};

class CDisplay: public IObserver
{
public:
	void Update(double temp, double humidity, double pressure) override
	{
		std::cout << "Current Temp " << temp << std::endl;
		std::cout << "Current Hum " << humidity << std::endl;
		std::cout << "Current Pressure " << pressure << std::endl;
		std::cout << "----------------" << std::endl;
	}
};

class IObservable
{
public:
	virtual ~IObservable() = default;
	virtual void RegisterObserver(IObserver & observer) = 0;
	virtual void NotifyObservers() = 0;
};

class CWeatherData : public IObservable
{
public:
	void RegisterObserver(IObserver & observer) override
	{
		m_observers.push_back(observer);
	}

	void NotifyObservers() override
	{
		double temp = GetTemperature();
		double humidity = GetHumidity();
		double pressure = GetPressure();
		for (auto & observer : m_observers)
		{
			observer.get().Update(temp, humidity, pressure);
		}
	}
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

private:
	vector<reference_wrapper<IObserver>> m_observers;

	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
