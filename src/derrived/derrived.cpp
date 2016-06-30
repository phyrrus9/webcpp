#include <derrived/derrived.hpp>
#include <core/page.hpp>
#include <stdio.h>

REGISTER_PAGE
REGISTER_SUBPAGE(blarg)

derrived::derrived()
{
	val = 2;
}
void derrived::out()
{
	printf("Derrived class : %d\n", val);
}
void derrived::blarg()
{
	printf("\tblarg!\n");
}

