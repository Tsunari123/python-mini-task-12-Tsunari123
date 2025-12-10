#define PY_SSIZE_T_CLEAN
#include </usr/include/python3.13/Python.h>
#include <stdlib.h>

static PyObject* matrix_power(PyObject* self, PyObject* args) {
    PyObject* py_matrix;
    int power;
    
    if (!PyArg_ParseTuple(args, "Oi", &py_matrix, &power)) {
        return NULL;
    }
    
    if (!PyList_Check(py_matrix)) {
        PyErr_SetString(PyExc_TypeError, "First argument must be a list");
        return NULL;
    }
    
    int n = PyList_Size(py_matrix);
    
    double** matrix = (double**)malloc(n * sizeof(double*));
    double** result = (double**)malloc(n * sizeof(double*));
    double** temp = (double**)malloc(n * sizeof(double*));
    
    for (int i = 0; i < n; i++) {
        matrix[i] = (double*)malloc(n * sizeof(double));
        result[i] = (double*)malloc(n * sizeof(double));
        temp[i] = (double*)malloc(n * sizeof(double));
        
        PyObject* row = PyList_GetItem(py_matrix, i);
        if (!PyList_Check(row) || PyList_Size(row) != n) {
            PyErr_SetString(PyExc_ValueError, "Matrix must be square");
            for (int j = 0; j <= i; j++) {
                free(matrix[j]);
                free(result[j]);
                free(temp[j]);
            }
            free(matrix);
            free(result);
            free(temp);
            return NULL;
        }
        
        for (int j = 0; j < n; j++) {
            PyObject* item = PyList_GetItem(row, j);
            matrix[i][j] = PyFloat_AsDouble(item);
            result[i][j] = (i == j) ? 1.0 : 0.0;  // Инициализируем единичную матрицу
        }
    }
    
    double** original_matrix = matrix;
    double** original_result = result;
    double** original_temp = temp;
    
    double** base = matrix;
    int p = power;
    
    while (p > 0) {
        if (p % 2 == 1) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    double sum = 0.0;
                    for (int k = 0; k < n; k++) {
                        sum += result[i][k] * base[k][j];
                    }
                    temp[i][j] = sum;
                }
            }
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    result[i][j] = temp[i][j];
                }
            }
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                double sum = 0.0;
                for (int k = 0; k < n; k++) {
                    sum += base[i][k] * base[k][j];
                }
                temp[i][j] = sum;
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                base[i][j] = temp[i][j];
            }
        }
        
        p /= 2;
    }
    
    PyObject* py_result = PyList_New(n);
    for (int i = 0; i < n; i++) {
        PyObject* row = PyList_New(n);
        for (int j = 0; j < n; j++) {
            PyList_SET_ITEM(row, j, PyFloat_FromDouble(result[i][j]));
        }
        PyList_SET_ITEM(py_result, i, row);
    }
    
    for (int i = 0; i < n; i++) {
        free(original_matrix[i]);
        free(original_result[i]);
        free(original_temp[i]);
    }
    free(original_matrix);
    free(original_result);
    free(original_temp);
    
    return py_result;
}

static PyMethodDef matrixMethods[] = {
    {"matrix_power", matrix_power, METH_VARARGS, "Raise matrix to power"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef matrixmodule = {
    PyModuleDef_HEAD_INIT,
    "matrix_",
    NULL,
    -1,
    matrixMethods
};

PyMODINIT_FUNC PyInit_matrix_(void) {
    return PyModule_Create(&matrixmodule);
}