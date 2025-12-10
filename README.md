### python-mini-task-12-Tsunari123
## C-extension module that implements a function for exponentiating matrices


# Мини-задача #12

Написать C-extension модуль, в котором реализовать
функцию для возведения матриц в степень:

PyObject *foreign_matrix_power(PyObject *self, PyObject *args)

В качестве аргументов такая функция принимает матрицу (list из
list-ов float-ов) и одно целое положительное число - степень.
В качестве результата возвращает новую матрицу, полученную
возведением оригинальной в заданную степень.

Написать C-extension модуль, в котором реализовать
функцию для возведения матриц в степень:

PyObject *foreign_matrix_power(PyObject *self, PyObject *args)

```py
import foreign
m = [[1.0, 2.0], [3.0, 4.0]]

print(foreign.foreign_matrix_power(m, 3))

# [[37.0, 54.0], [81.0, 118.0]]
```
