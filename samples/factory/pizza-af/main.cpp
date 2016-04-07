#include <iostream>
#include "PizzaStore.h"

int main()
{
	CNYPizzaStore store;
	CChicagoPizzaStore chicagoStore;
	//auto pizza = store.OrderPizza("cheese");
	//std::cout << pizza->ToString();

	auto clamPizza = chicagoStore.OrderPizza("clam");
	std::cout << clamPizza->ToString();
	return 0;
}