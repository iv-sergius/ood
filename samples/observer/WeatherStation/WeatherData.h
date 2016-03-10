#pragma once

class CDisplay
{
public:
	void Update(double temp, double humidity, double pressure)
	{

	}
};

class CWeatherData
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
		double temp = GetTemperature();
		double humidity = GetHumidity();
		double pressure = GetPressure();

		m_currentConditionsDisplay.Update(temp, humidity, pressure);
		m_statisticsDisplay.Update(temp, humidity, pressure);
		m_forecastDisplay.Update(temp, humidity, pressure);
	}

private:
	CDisplay m_currentConditionsDisplay;
	CDisplay m_statisticsDisplay;
	CDisplay m_forecastDisplay;
	double m_temperature = 0.0;
	double m_humidity = 0.0;	
	double m_pressure = 760.0;	
};
