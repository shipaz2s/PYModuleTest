#include "class_py.h"
#include <stdlib.h>


#include <stdio.h>


PyObject *Signals_new(PyTypeObject *type, PyObject *args, PyObject *kwds){
	printf("Signals_new\n");
	SignalsObject *self;
	self = (SignalsObject*) type->tp_alloc(type, 0);
	if(self != NULL){ // -> allocation successfull
		// assign initial values
		self->m_value   = 0;
		self->m_signals = NULL; 
	}
	printf("OBJECT NEW %d\n", self);

	return (PyObject*) self;
}

int Signals_init(PyObject *self, PyObject *args, PyObject *kwds){
	printf("Signals_init\n");
	
	SignalsObject* m = (SignalsObject*)self;

	m->m_value = 123;
	m->m_signals = (Signals*)PyObject_Malloc(sizeof(Signals));

	if(!m->m_signals){
		PyErr_SetString(PyExc_RuntimeError, "Memory allocation failed");
		return -1;
	}

	m->m_signals->size = 0;
	m->m_signals->capacity = 1;
	m->m_signals->data = malloc(sizeof(Signal));

	printf("init size = %llu, capacity = %llu\n", m->m_signals->size, m->m_signals->capacity);
	printf("OBJECT INIT %d\n", self);

	return 0;
}

void Signals_dealloc(PyObject *self){
	printf("Signals_dealloc\n");
	PyTypeObject *tp = Py_TYPE(self);

	SignalsObject* m = (SignalsObject*)self;

	free(m->m_signals->data);

	if(m->m_signals){
		PyObject_Free(m->m_signals);
	}

	tp->tp_free(self);
	Py_DECREF(tp);
};

static PyObject* Signals_append(PyObject* self,
								PyTypeObject* defining_class,
								PyObject* const* args,
								Py_ssize_t nargs,
								PyObject* kwnames){
	printf("Signals_append\n");
	printf("OBJECT APPEND %d\n", self);	
	printf("nargs = %d\n", nargs);
	PyObject *ret = NULL;
	size_t begin, end;

	begin = 0; /* Default value. */
	end = 0;
	printf("parsing args\n");
	if (! PyArg_ParseTuple(args, "KK", &begin, &end)) {
		printf("parsing error\n");
		goto except;
	}

	printf("begin = %llu, end = %llu\n", begin, end);

	SignalsObject* m = (SignalsObject*) self;

	appendSignal(m->m_signals, begin, end);
	printf("appended\n");

	Py_INCREF(Py_None);
	// ret = Py_None;
	ret = Py_BuildValue("i", 0);
	assert(! PyErr_Occurred());
	assert(ret);
	goto finally;
except:
	printf("except\n");
	Py_XDECREF(ret);
	ret = NULL;
	ret = Py_BuildValue("i", -1);
finally:
	printf("finally\n");
	return ret;
}

static PyMethodDef Signals_methods[] = {
	{"append", (PyCFunction)Signals_append, METH_METHOD | METH_FASTCALL | METH_KEYWORDS,  "Append signal"},
	{NULL} /* Sentinel */
};

static struct PyMemberDef Signals_members[] = {
	{NULL} /* Sentinel */
};

PyTypeObject signals_type = {
	PyObject_HEAD_INIT(NULL)
	.tp_name = "Signals",
	.tp_basicsize = sizeof(SignalsObject),
	.tp_dealloc = Signals_dealloc,
	.tp_flags = Py_TPFLAGS_DEFAULT,
	.tp_doc = "Instance if class Signals",
	.tp_methods = Signals_methods,
	.tp_members = Signals_members,
	.tp_init = Signals_init,
	.tp_new = Signals_new,
};