#include <Python.h>

#include "class_py.h"

PyModuleDef PYModule = {
	.m_base = PyModuleDef_HEAD_INIT,
	.m_name = "PYModule",
	.m_doc = "Module for test",
	.m_size = 0,
	.m_methods = NULL,
};


PyMODINIT_FUNC 
PyInit_PYModule(void) {

	if (PyType_Ready(&signals_type) < 0) {
		return NULL;
	}

	PyObject* module = PyModule_Create(&PYModule);

	if (module == NULL) {
		return NULL;
	}

	Py_INCREF(&signals_type);
	PyModule_AddObject(module, signals_type.tp_name, (PyObject*)&signals_type);

	// PyObject *signalClass = PyType_FromSpec(&spec_signal);
	// if (signalClass == NULL){
	// 	return NULL;
	// }
	// Py_INCREF(signalClass);

	// PyObject *signalsClass = PyType_FromSpec(&spec_signals);
	// if (signalsClass == NULL){
	// 	return NULL;
	// }
	// Py_INCREF(signalsClass);

	// if(PyModule_AddObject(module, "Signals", signalsClass) < 0){
	// 	Py_DECREF(signalsClass);
	// 	Py_DECREF(module);
	// 	return NULL;
	// }

	// if(PyModule_AddObject(module, "Signal", signalClass) < 0){
	// 	Py_DECREF(signalClass);
	// 	Py_DECREF(module);
	// 	return NULL;
	// }



	return module;
}