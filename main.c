/* 
 * File:   main.c
 * Author: papa
 *
 * Created on 15 ноября 2018 г., 20:25
 */

#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

#include <Python.h>

int
main(int argc, char *argv[])
{
    // PName об. модуля из pythonfile,pModule об. модуля,pFunc функция модуля 
    PyObject *pName, *pModule, *pFunc;
    // pArgs кортеж значений для функции,pValue - одно значение от туда
    PyObject *pArgs, *pValue;
    // i для цикла
    int i;
    // д. б. 3 и более Cmd аргументов
    if (argc < 3) {
        fprintf(stderr,"Usage: call pythonfile funcname [args]\n");
        // ret ошибка
        return 1;
    }
   // иниц. инпритатора
    Py_Initialize();
/*
    PyObject* PyUnicode_DecodeLocaleAndSize(const char *str, Py_ssize_t len, const char *errors)
Decode a string from UTF-8 on Android, or from the current locale encoding on other platforms.
The supported error handlers are "strict" and "surrogateescape" (PEP 383). The decoder uses
"strict" error handler if errors is NULL. str must end with a null character but cannot contain
embedded null characters.
Use PyUnicode_DecodeFSDefaultAndSize() to decode a string from
Py_FileSystemDefaultEncoding (the locale encoding read at Python startup).
This function ignores the Python UTF-8 mode.
*/
    pName = PyUnicode_DecodeFSDefault(argv[1]);

    /* Error checking of pName left out */
   /* Return value: New reference. This is a higher-level interface that calls
    *  the current “import hook
function” (with an explicit level of 0, meaning absolute import). 
    * It invokes the __import__() function
from the __builtins__ of the current globals. This means that the 
    * import is done using whatever
import hooks are installed in the current environment.
*/
    /*
     * Высокоур. интф.,вызыв. тек. "import функцию"
     */
    pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != NULL) {
        // выделяем элемент функция из модуля ret pFunc:PyObject*
        pFunc = PyObject_GetAttrString(pModule, argv[2]);
     

        if (pFunc && PyCallable_Check(pFunc)) {
           // Созд. кортеж с аргументами для функции ret кортеж,pArgs:PyObject*
            pArgs = PyTuple_New(argc - 3);
            for (i = 0; i < argc - 3; ++i) {
                // Из С int/long в Об. Long: PyObject*
                pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    // декреф ссылки
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fprintf(stderr, "Cannot convert argument\n");
                    // ret ошибка 
                    return 1;
                }
                // Вставл. об. pValue в об. pArgs на позиц i:int
                PyTuple_SetItem(pArgs, i, pValue);
            }
            // Вызыв. вызываемый Py об. с арг. кортежом-ret новая ссылка
            pValue = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pValue != NULL) {
           // Возр. С long представл. Py об.
                printf("Result of call: %ld\n", PyLong_AsLong(pValue));
                // декреф ссылки
                Py_DECREF(pValue);
            }
            else {
                // декреф ссылки
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fprintf(stderr,"Call failed\n");
                // ret ошибка 
                return 1;
            }
        }
        else {
            if (PyErr_Occurred())
                PyErr_Print();
            fprintf(stderr, "Cannot find function \"%s\"\n", argv[2]);
        }
         // декреф ссылки
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    }
    else {
        PyErr_Print();
        fprintf(stderr, "Failed to load \"%s\"\n", argv[1]);
        // ret ошибка 
        return 1;
    }
    //финализ. инпритатора
    if (Py_FinalizeEx() < 0) {
        // ret ошибка 120
        return 120;
    }
    // норм. конец
    return 0;
}
