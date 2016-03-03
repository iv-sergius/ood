#include <iostream>

using namespace std;

class Duck
{
public:
	void Quack() const
	{
		cout << "Quack Quack!!!" << endl;
	}

	void Swim() const
	{
		cout << "I'm swimming" << endl;
	}

	virtual void Display() const = 0;

	virtual ~Duck() {};
};

class MallardDuck : public Duck
{
public:

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void main()
{
	DrawDuck(MallardDuck());
	DrawDuck(RedheadDuck());
}
