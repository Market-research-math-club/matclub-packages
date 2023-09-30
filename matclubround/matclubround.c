#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include <stdio.h>
#include <math.h>


double round_half_up(double n, int decimals) {
    double multiplier = pow(10, decimals);
    return floor(n * multiplier + 0.5) / multiplier;
}

double round_half_away_from_zero(double n, int decimals) {
    double rounded_abs = round_half_up(fabs(n), decimals);
    return copysign(rounded_abs, n);
}

double c_normal_round(double x, int decimals) {
    if (decimals) {
        return round_half_away_from_zero(x, decimals);
    }
    double pre_rounded = round_half_away_from_zero(x, 2);
    return round_half_away_from_zero(pre_rounded, 0);
}


static PyObject *
py_normal_round(PyObject *self, PyObject *args)
{
    const double n_x;
    const int n_decimals;
    double result;

    if (!PyArg_ParseTuple(args, "di", &n_x, &n_decimals))
        return NULL;
    result = c_normal_round(n_x, n_decimals);
    int int_res = (int) result;
    if (int_res == result) {
        return PyLong_FromLong(int_res);
    }
    return PyFloat_FromDouble(result);
}


static PyMethodDef CountingMethods[] = {
    {"normal_round", py_normal_round, METH_VARARGS, "Round like school"},
    {NULL, NULL, 0, NULL}
};


static struct PyModuleDef matclubroundmodule = {
  PyModuleDef_HEAD_INIT,
  "matclubround",                              
  "C library for matclub",  
  -1,                                   
  CountingMethods                          
};


PyMODINIT_FUNC PyInit_matclubround(void) {
  return PyModule_Create(&matclubroundmodule);
};
