#include <cassert>
#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <functional>

using namespace std;

using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

FlyBehavior FlyWithWings = []
{
	cout << "I'm flying with wings!!" << endl;
};

FlyBehavior FlyNoWay = [] {};

QuackBehavior JustQuack = [] //QuackBehavior
{
	cout << "Quack Quack!!!" << endl;
};

QuackBehavior Squeak = [] //SqueakBehavior
{
	cout << "Squeek!!!" << endl;
};

QuackBehavior MuteQuack = [] {};

DanceBehavior DanceWaltz = []
{
	cout << "I'm dancing waltz" << endl;
};

DanceBehavior DanceMinuet = []
{
	cout << "I'm dancing minuet" << endl;
};

DanceBehavior NoDance = [] {};

class Duck
{
public:
	Duck(FlyBehavior fly, QuackBehavior quack, DanceBehavior dance)
		: m_fly(fly)
		, m_quack(quack)
		, m_dance(dance)
	{}
	void Quack()
	{
		m_quack();
	}
	void Swim()
	{
		cout << "I'm swimming" << endl;
	}
	void Fly()
	{
		m_fly();
	}
	void Dance()
	{
		m_dance();
	}
	void SetFlyBehavior(FlyBehavior & fly)
	{
		m_fly = fly;
	}
	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_fly;
	QuackBehavior m_quack;
	DanceBehavior m_dance;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, JustQuack, DanceWaltz)
	{}

	void Display() const override
	{
		cout << "I'm mallard duck" << endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, JustQuack, DanceMinuet)
	{
	}
	void Display() const override
	{
		cout << "I'm redhead duck" << endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuack, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm decoy duck" << endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, Squeak, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm rubber duck" << endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, JustQuack, NoDance)
	{
	}
	void Display() const override
	{
		cout << "I'm model duck" << endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	cout << endl;
}

void main()
{
	MallardDuck mallarDuck;
	PlayWithDuck(mallarDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
	modelDuck.Fly();
	modelDuck.Fly();
}
