#include <DatEngine.h>

int main()
{
	auto app = dat::core::DatApplication(800, 600, "DatEngine");
	app.run();

	return 0;
}