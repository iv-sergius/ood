#pragma once
#include <iostream>
#include <map>
#include <boost/optional.hpp>

enum class WalkDirection
{
	North,
	South,
	West,
	East,
};

class CRobot
{
public:
	void TurnOn()
	{
		if (!m_turnedOn)
		{
			m_turnedOn = true;
			std::cout << "It am waiting for your commands\n";
		}
	}

	void TurnOff()
	{
		if (m_turnedOn)
		{
			m_turnedOn = false;
			m_direction.reset();
			std::cout << "It is a pleasure to serve you\n";
		}
	}

	void Walk(WalkDirection direction)
	{
		using namespace std;

		if (m_turnedOn)
		{
			m_direction = direction;
			static const map<WalkDirection, string> directionToString = {
				{ WalkDirection::East, "east" },
				{ WalkDirection::South, "south" },
				{ WalkDirection::West, "west" },
				{ WalkDirection::North, "north" },
			};
			cout << "Walking " << directionToString.at(direction) << endl;
		}
	}

	void Stop()
	{
		if (m_turnedOn)
		{
			if (m_direction)
			{
				m_direction.reset();
				std::cout << "Stopped\n";
			}
			else
			{
				std::cout << "I am staying still\n";
			}
		}
	}
private:
	bool m_turnedOn = false;
	boost::optional<WalkDirection> m_direction;
};