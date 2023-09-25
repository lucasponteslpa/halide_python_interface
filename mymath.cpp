#include <Python.h>
#include "run.h"

// This is the definition of a method
static PyObject* division(PyObject *self, PyObject *args) {
    long dividend, divisor;
    if (!PyArg_ParseTuple(args, "ll", &dividend, &divisor)) {
        return NULL;
    }
    if (0 == divisor) {
        PyErr_Format(PyExc_ZeroDivisionError, "Dividing %d by zero!", dividend);
        return NULL;
    }
    return PyLong_FromLong(dividend / divisor);
}

static PyObject* run_c(PyObject *self, PyObject *args) {
    return PyLong_FromLong(run_ext_c(0));
}

// Exported methods are collected in a table
PyMethodDef method_table[] = {
    {"division", (PyCFunction) division, METH_VARARGS, "Method docstring"},
    {"run_c", (PyCFunction) run_c, METH_VARARGS, "Method run extern"},
    {NULL, NULL, 0, NULL} // Sentinel value ending the table
};

// A struct contains the definition of a module
PyModuleDef mymath_module = {
    PyModuleDef_HEAD_INIT,
    "mymath", // Module name
    "This is the module docstring",
    -1,   // Optional size of the module state memory
    method_table,
    NULL, // Optional slot definitions
    NULL, // Optional traversal function
    NULL, // Optional clear function
    NULL  // Optional module deallocation function
};

// The module init function
PyMODINIT_FUNC PyInit_mymath(void) {
    return PyModule_Create(&mymath_module);
}

// int main(int argc, char **argv) {
//     int a = run_ext_c(0);
//     // int a = an_extern_func(1,2);
//     printf("out %d\n", a);
//     return 0;
// }
