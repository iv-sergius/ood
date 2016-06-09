#include "CoW.h"
#include <iostream>

using namespace std;

struct Logger
{
	Logger()
	{
		cout << "New Logger was created" << endl;
	}
	Logger(Logger const& logger)
	{
		cout << "Logger was copied" << endl;
	}

	int data = 42;
};

struct ISomething
{
	virtual int GetData()const = 0;
	virtual void SetData(int newData) = 0;
	virtual unique_ptr<ISomething> Clone()const = 0;
	virtual ~ISomething() = default;
};

struct CSomething : public ISomething
{
	void DoSomethingElse()
	{
		cout << "something else" << endl;
	}

	void SetData(int newData) override
	{
		data = newData;
	}

	virtual int GetData() const override
	{
		return data;
	}

	unique_ptr<ISomething> Clone() const override
	{
		return make_unique<CSomething>(*this);
	}
private:
	int data = 0;

};


int main()
{
	CCow<Logger> logger1;
	CCow<Logger> logger2(logger1);

	cout << logger1->data << endl;
	cout << logger2->data << endl;

	logger1.Write().data = 55;

	cout << logger1->data << endl;
	cout << logger2->data << endl;

	logger1.Write().data = 66;

	cout << logger1->data << endl;
	cout << logger2->data << endl;

	CCow<Logger> logger3(logger2);
	cout << logger1->data << endl;
	cout << logger2->data << endl;
	cout << logger3->data << endl;

	logger3--->data = 99;

	logger3.WriteShared();

	cout << logger1->data << endl;
	cout << logger2->data << endl;
	cout << logger3->data << endl;

	
	CCow<ISomething> something1(unique_ptr<ISomething>(new CSomething()));
	if (auto p = dynamic_pointer_cast<CSomething>(something1.WriteShared()))
	{
		p->DoSomethingElse();
	}
	
	auto somethingElse(something1);
	somethingElse--->SetData(42);
	cout << something1->GetData() << endl;
	cout << somethingElse->GetData() << endl;


	return 0;
}