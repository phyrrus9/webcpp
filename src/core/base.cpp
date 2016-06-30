#include <core/base.hpp>
#include <stdio.h>

base::base()
{
	val = 1;
}
base::~base()
{
}
void base::out()
{
	printf("Base class : %d\n", val);
}
