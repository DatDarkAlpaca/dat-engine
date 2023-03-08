#include <DatEngine.h>

class Client : public dat::DatApplication
{
public:
	Client(int width, int height, const char* title)
		: dat::DatApplication(width, height, title)
	{

	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
