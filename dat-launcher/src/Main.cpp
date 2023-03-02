#include <DatEngine.h>

class Client : public dat::core::DatApplication
{
public:
	Client(int width, int height, const char* title)
		: dat::core::DatApplication(width, height, title)
	{

	}

public:

};

int main()
{
	auto c = Client(800, 600, "Dat Engine");
	c.run();
}
