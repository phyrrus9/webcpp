#include <core/base.hpp>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef base *create_t();
typedef void destroy_t(base *);
typedef void subfnc_t(base *);

struct runable
{
	void *obj;
	char *page;
	create_t *createRunable;
	destroy_t *destroyRunable;
	base *runableClass;
};

base *newClass(struct runable *r)
{
	if (r->createRunable == NULL)
		return (base *)NULL;
	else if (r->runableClass != (base *)NULL)
		return r->runableClass;
	r->runableClass = r->createRunable();
	return r->runableClass;
}
void deleteClass(struct runable *r)
{
	if (r->createRunable != NULL && r->runableClass != (base *)NULL)
		r->destroyRunable(r->runableClass);
	r->runableClass = (base *)NULL;
}
char *backtrackString(char *str, char split)
{
	char *ret = strdup(str);
	char *t = ret;
	char *sp = new char[3];
	sprintf(sp, "%c", split);
	while (strstr(t, sp))
		t = strstr(t, sp) + 1;
	*(t - 1) = 0;
	delete sp;
	return ret;
}
struct runable *loadClass(char *path)
{
	struct runable *r = new struct runable;
	char *buf, *buf2, *tmp;
	r->createRunable = (create_t *)NULL;
	r->destroyRunable = (destroy_t *)NULL;
	r->runableClass = (base *)NULL;
	if ((r->obj = dlopen(path, RTLD_LAZY)) != NULL)
	{
		r->page = strdup(path + strlen("./obj/"));
	}
	else //failed, check for /index
	{
		tmp = strdup(path + strlen("./obj/"));
		buf2 = new char[strlen(path) + 1];
		sprintf(buf2, "./obj/%s", tmp);
		if (r->obj == NULL && strstr(tmp, "/"))
		{
			tmp = backtrackString(tmp, '/');
			sprintf(buf2, "./obj/%s", tmp);
			if ((r->obj = dlopen(buf2, RTLD_LAZY)) != NULL)
				r->page = strdup(buf + strlen("./obj/"));
		}
		delete buf2;
		if (r->obj == NULL)
			return (struct runable *)NULL;
	}
	dlerror();
	r->createRunable = (create_t *)dlsym(r->obj, "create");
	r->destroyRunable = (destroy_t *)dlsym(r->obj, "destroy");
	return r;
}
void unloadClass(struct runable *r)
{
	deleteClass(r);
	dlclose(r->obj);
	r->createRunable = (create_t *)NULL;
	r->destroyRunable = (destroy_t *)NULL;
	r->runableClass = (base *)NULL;
	r->obj = NULL;
}

int main(int argc, char ** argv)
{
	if (argc < 2)
	{
		printf("Usage: %s objectName\n", argv[0]);
		return 1;
	}
	int i;
	char *buf;
	char *page = argv[1];
	char *path = new char[1024];
	const char *dlsym_error;
	subfnc_t *sub;
	struct runable *r;
	base *c;
	buf = strdup(page);
	if (strstr(buf, "/"))
		*(strstr(buf, "/")) = 0;
	sprintf( path, "./obj/%s", buf );
	delete buf;
	r = loadClass(path);
	c = newClass(r);
	dlerror();
	if (strstr(page, "/"))
	{
		sub = (subfnc_t *)dlsym(r->obj, strstr(page, "/") + 1);
		dlsym_error = dlerror();
		sub(c);
		
	}
	else
	{
		c->out();
	}
	return 0;
}
