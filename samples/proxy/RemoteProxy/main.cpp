#include <iostream>
#include <string>
#include <functional>
#include <tuple>
#include <unordered_map>
#include <stdexcept>
#include <sstream>
#include <boost/format.hpp>

using namespace std;

enum class Direction
{
	North, West, South, East
};
struct IDuck
{
	virtual void Fly(Direction direction, int distance) = 0;
	virtual void Quack(const string & name) = 0;
	virtual int GetTotalFlyDistance() const = 0;
	virtual ~IDuck() = default;
};

string DirectionToString(Direction direction)
{
	return
		(direction == Direction::East) ? "east" :
		(direction == Direction::North) ? "north" :
		(direction == Direction::South) ? "south" : "west";
}

Direction StringToDirection(const string& direction)
{
	return
		(direction == "east") ? Direction::East :
		(direction == "west") ? Direction::West :
		(direction == "south") ? Direction::South :
		(direction == "north") ? Direction::North : 
		throw invalid_argument("unknown direction");
}

class CDuck : public IDuck
{
public:
	void Quack(const string & name) override
	{
		cout << "Quack Quack " << name << endl;
	}

	void Fly(Direction direction, int distance) override
	{
		cout << boost::format("I am flying %1% %2% km.") 
			% DirectionToString(direction) % distance << endl;
		m_totalDistance += distance;
	}
	int GetTotalFlyDistance() const override
	{
		return m_totalDistance;
	}
private:
	int m_totalDistance = 0;
};


class CMessageQueue
{
public:
	typedef function<string(const string& data)> MessageHandler;
	void RegisterMessageReceiver(const string& url, const MessageHandler & handler)
	{
		auto result = m_receivers.emplace(url, handler);
		if (!result.second)
		{
			throw invalid_argument("Message receiver has already been registered");
		}
	}
	void UnregisterMessageReceiver(const string& url)
	{
		m_receivers.erase(url);
	}
	string SendMessage(const string& url, const string& data)
	{
		return m_receivers.at(url)(data);
	}
private:
	unordered_map<string, MessageHandler> m_receivers;
};

class CDuckStub
{
public:
	static const string QUACK_METHOD_ID;
	static const string FLY_METHOD_ID;
	static const string GET_TOTAL_FLY_DISTANCE_METHOD_ID;

	CDuckStub(CMessageQueue & queue, const string& id)
		: m_queue(queue)
	{
		m_queue.RegisterMessageReceiver(GetURL(id, QUACK_METHOD_ID), [this](const string& data) {
			m_duck.Quack(data);
			return "";
		});
		m_queue.RegisterMessageReceiver(GetURL(id, FLY_METHOD_ID), [this](const string& data) {
			istringstream strm(data);
			string direction;
			int distance;
			if (strm >> direction >> distance)
			{
				m_duck.Fly(StringToDirection(direction), distance);
			}
			else
			{
				throw invalid_argument("Invalid data");
			}
			return "";
		});
		m_queue.RegisterMessageReceiver(GetURL(id, GET_TOTAL_FLY_DISTANCE_METHOD_ID), [this](const string& data) {
			if (!data.empty())
			{
				throw invalid_argument("Not data is expected");
			}
			return to_string(m_duck.GetTotalFlyDistance());
		});
	}
	~CDuckStub()
	{
		m_queue.UnregisterMessageReceiver(GetURL(m_id, QUACK_METHOD_ID));
	}
	static string GetURL(const string& objectId, const string& methodName)
	{
		return "msg:CDuckStub/" + objectId + "/" + methodName;
	}
private:
	CDuck m_duck;
	string m_id;
	CMessageQueue & m_queue;
};
const string CDuckStub::QUACK_METHOD_ID = "Quack";
const string CDuckStub::FLY_METHOD_ID = "Fly";
const string CDuckStub::GET_TOTAL_FLY_DISTANCE_METHOD_ID = "GetTotalFlyDistance";

class CDuckProxy : public IDuck
{
public:
	CDuckProxy(CMessageQueue & queue, const string& id)
		: m_queue(queue)
		, m_id(id)
	{
	}
	void Quack(const string & name) override
	{
		m_queue.SendMessage(GetMethodURL(CDuckStub::QUACK_METHOD_ID), name);
	}
	void Fly(Direction direction, int distance) override
	{
		m_queue.SendMessage(GetMethodURL(CDuckStub::FLY_METHOD_ID),
			DirectionToString(direction) + " " + to_string(distance));
	}
	int GetTotalFlyDistance() const override
	{
		return stoi(m_queue.SendMessage(
			GetMethodURL(CDuckStub::GET_TOTAL_FLY_DISTANCE_METHOD_ID),
			""));
	}
private:
	string GetMethodURL(const string& methodName)const
	{
		return CDuckStub::GetURL(m_id, methodName);
	}
	mutable CMessageQueue m_queue;
	string m_id;
};

void PlayWithDuck(IDuck & duck)
{
	duck.Quack("John");
	duck.Fly(Direction::North, 10);
	duck.Fly(Direction::East, 5);
	cout << "Total fly distance " << duck.GetTotalFlyDistance() << "km\n";
}

int main()
{
	CMessageQueue msgQueue;
	CDuckStub stub(msgQueue, "duck1");
	CDuckProxy proxy(msgQueue, "duck1");
	PlayWithDuck(proxy);

	return 0;
}
