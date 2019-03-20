#include "ruby.h"

#if SIZEOF_LONG == SIZEOF_VOIDP
# define nonspecial_obj_id(obj) (VALUE)((SIGNED_VALUE)(obj)|FIXNUM_FLAG)
# define obj_id_to_ref(objid) ((objid) ^ FIXNUM_FLAG) /* unset FIXNUM_FLAG */
#elif SIZEOF_LONG_LONG == SIZEOF_VOIDP
# define nonspecial_obj_id(obj) LL2NUM((SIGNED_VALUE)(obj) / 2)
# define obj_id_to_ref(objid) (FIXNUM_P(objid) ? \
   ((objid) ^ FIXNUM_FLAG) : (NUM2PTR(objid) << 1))
#else
# error not supported
#endif

static VALUE
rb_memory_location(VALUE self)
{
    return nonspecial_obj_id(self);
}

void
Init_memory_location(void)
{
    rb_define_method(rb_mKernel, "memory_location", rb_memory_location, 0);
}

