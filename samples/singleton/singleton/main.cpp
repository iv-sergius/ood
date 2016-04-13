#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class CMeyersSingleton
{
public:
	static CMeyersSingleton & GetInstance()
	{
		static CMeyersSingleton instance;
		return instance;
	}

	void DoSomething()
	{
		cout << "Doing something" << endl;
	}

	// Запрещаем копирование и присваивание экземпляров
	CMeyersSingleton(const CMeyersSingleton &) = delete;
	CMeyersSingleton & operator=(const CMeyersSingleton &) = delete;
private:
	CMeyersSingleton()
	{
	}
};

struct ILogger
{
	virtual void Enable(bool enable) = 0;
	virtual void LogMessage(const string& msg) = 0;

	virtual ~ILogger() = default;
	ILogger(const ILogger&) = delete;
	ILogger& operator=(const ILogger&) = delete;
protected:
	ILogger() = default;
};

ILogger & GetDefaultLogger()
{
	static struct Logger : ILogger
	{
		void LogMessage(const string& msg) override
		{
			if (m_enabled)
			{
				if (!m_strm.is_open())
				{
					m_strm.open("log.txt", ios::app);
				}
				m_strm << msg << endl;
				m_strm.flush();
			}
		}

		void Enable(bool enable) override
		{
			if (m_enabled != enable)
			{
				m_enabled = enable;
				if (!enable && m_strm.is_open())
				{
					m_strm.close();
				}
			}
		}

		ofstream m_strm;
		bool m_enabled = false;
	} logger;

	return logger;
}

int main()
{
	auto & instance = CMeyersSingleton::GetInstance();
	instance.DoSomething();

	{
		auto & logger = GetDefaultLogger();
		logger.LogMessage("this message will not be logged");
		logger.Enable(true);
		logger.LogMessage("This message will be logged");
	}
	return 0;
}