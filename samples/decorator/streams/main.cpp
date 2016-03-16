#include <iostream>
#include <string>

using namespace std;

class ITextOutputStream
{
public:
	virtual void WriteText(const string& text) = 0;
	virtual ~ITextOutputStream() = default;
};


int main()
{
	

	return 0;
}