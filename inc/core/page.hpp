#define CALL_MEMBER_FN(o, p) (o->*p)
#define PAGE CLS : public base
typedef void (CLS::*_v_memberfnc)();
#define PGSYM extern "C"
#define REGISTER_PAGE \
	PGSYM CLS *create() { return new CLS(); }\
	PGSYM void destroy(base *p) { delete p; }
#define REGISTER_SUBPAGE(p) \
        PGSYM void p(CLS *o) { \
		_v_memberfnc _p = &CLS::p; \
		CALL_MEMBER_FN(o, _p)(); }
