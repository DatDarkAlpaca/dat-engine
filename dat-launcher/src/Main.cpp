#include "pch.hpp"
#include <DatEngine.hpp>

using namespace dat;

dat::dat_unique<dat::DatEngine> CreateEngine()
{
	return dat::MakeUnique<dat::DatEngine>();
}