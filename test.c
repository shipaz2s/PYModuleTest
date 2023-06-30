#include "class_py.h"

int main(int argc, char *argv[], char *envp[])
{
	// Py_SetProgramName(L"DbgPythonCppExtension");
	Py_Initialize();

	PyObject *pmodule = PyImport_ImportModule("PYModule");
	if (!pmodule) {
		PyErr_Print();
		printf("Failed to import module PYModule\n");
		return -1;
	}

	PyObject *myClassType = PyObject_GetAttrString(pmodule, "Signals");
	if (!myClassType) {
		printf("Unable to get type Signals from MyModule\n");
		return -1;
	}

	PyObject *myClassInstance = PyObject_CallObject(myClassType, NULL);

	if (!myClassInstance) {
		printf("Instantioation of MyClass failed\n");
		return -1;
	}

 	PyObject* args = Py_BuildValue("OKK", myClassInstance, 1, 2);    
	PyObject* keywords = PyDict_New();
	// PyObject* result = PyObject_Call(PyObject_GetAttrString(myClassInstance, "append"), args, keywords);

	// PyObject* result = PyObject_CallMethod(myClassInstance, "append", "KK", 1ULL, 2ULL);

	PyErr_Clear();

	PyObject* fnct = PyObject_GetAttrString(myClassInstance, "append");
	PyObject* fname = PyUnicode_FromString("append");
	PyObject* result = PyObject_CallMethodObjArgs(myClassInstance, fname, PyLong_FromUnsignedLongLong(1LL), PyLong_FromUnsignedLongLong(2LL), NULL);

	if (result == NULL) {
		printf("result is NULL\n");
		PyErr_Print();
	} else {
		printf("result is OK\n");
	}

	Py_DECREF(args);
	Py_DECREF(keywords);

	Py_DecRef(myClassInstance); // invoke deallocation
	return 0;
}