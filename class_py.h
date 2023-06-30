#pragma once

#include <Python.h>
#include <structmember.h>

#include "class.h"

extern PyTypeObject signals_type;

typedef struct {
	PyObject_HEAD
	int m_value;
	Signals* m_signals;
} SignalsObject;

