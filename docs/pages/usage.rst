Usage
=====

The tool was developed using Python 3.9. On versions older than Python 3.6, the tool is not guaranteed to run. The tool can be used to evaluate the number of executed instructions. In addition, different branch prediction strategies can be simulated.

Currently it is possible to directly provide an ARMv7-A or ARMv7-A compatible assembly file as input or to use a GCC crosscompiler to compile a C program to ARM assembly. The cross-compiler (``arm-linux-gnueabi-gcc``) used in this project can be installed `this <https://www.acmesystems.it/arm9_toolchain>`_ way. The corresponding documentation can be found `here <https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html>`_.

To install the package, run ``pip install .`` in the root directory of this project. After installation, the command **asm-analyse** should be available to you. Instead of installing the package and using the command, it is also possible to run the tool by executing the **main.py** file in the **asm_analyser** directory. The first argument for the file name is required. The other arguments are optional:

``asm-analyse -f INPUT_FILE -o OPTIMIZATION -b BRANCH_PRED -s STACK_SIZE``

The first argument specifies the path to the input program you want to run. You can either pass an assembly file which then won't be compiled anymore, or a C file.

The next argument can then be used to specify the optimization level with which GCC should compile the C file to assembly. This can be either empty (no optimization) or take one of the following values: ``O1``, ``O2``, ``O3``.

The third argument can be used to specify the desired branch prediction strategy. By default, a simple one bit branch prediction is used (one_bit). Currently three different branch prediction methods are implemented: ``one_bit``, ``two_bit1`` and ``two_bit2``. The first one uses one single bit to track whether a branch was taken or not during its last execution. The next two methods can be seen as four-state state machines in which the next prediction is based on the current state.

The last argument specifies the size of the simulated stack in bytes. The value needs to be between 1000 and 2147483590. The default value is 10000.