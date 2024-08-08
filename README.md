
Description:

    - Example project of calling C++ code using PyBind11
    - Also provides example of calling Python code from C++
    - Use case: 
        - Prototype models in python and implement in C++
        - Python tests can use C++ code
        - C++ code can also run Python models if required to debug
    - Advantages
        - Mixed mode development
        - Single testing site (python) can mix and match modules as needed
        - Can debug with GDB w/ GUI


How to Build:

```bash
mkdir build
cd build
cmake ..
make
```


How to Run:

```bash
cp build/libmodel.so model.so
python test.py
```

How to Debug:

    - Install gdbgui (https://www.gdbgui.com/installation/)

    - `gdbgui --args /path/to/python test.py`


- TODO:

  - Test performance 
  - Try mixed mode debuging (https://www.podoliaka.org/2016/04/10/debugging-cpython-gdb/)