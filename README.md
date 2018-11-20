//ERROR -ModuleNotFoundError
Расширить интрпритатор(Встроить в др. приложение) Python.Тестовый пример с сайта-https://docs.python.org/2/extending/embedding.html.Должен сам управлять ходом выполнения
интерпритатора.Собирается binExe_call.exe,ложу в папку python36.dll.Даю
>binExe_call.exe ./module_pythonFile_multyply.py func_multiply_sIIrI 4 5
или
>binExe_call.exe module_pythonFile_multyply.py func_multiply_sIIrI 4 5
D:\NetBeansCppProjects\call\dist\Debug\MinGW-Windows>binExe_call.exe ./module_pythonFile_multyply.py func_multiply_sIIrI 4 5
Вывод:
ModuleNotFoundError: No module named './module_pythonFile_multyply'
Failed to load "./module_pythonFile_multyply.py"
или
ModuleNotFoundError: No module named 'module_pythonFile_multyply.py'; 'module_pythonFile_multyply' is not a package
Failed to load "module_pythonFile_multyply.py"

module_pythonFile_multyply.py питон скрипт из измененного интерпритатора.