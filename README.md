# ASM-Analyser

## Introduction

ASM-Analyser is a tool for dynamic program analysis written in Python 3.9. Currently it is based on ARMv7-A assembly. It can be used to evaluate the number of executed  instructions. In addition, various branch prediction strategies can be simulated.

Currently it is possible to directly provide an ARMv7-A or ARMv7-A compatible assembly file as input or to use a GCC crosscompiler to compile a C program to ARM assembly. The cross-compiler (`arm-linux-gnueabi-gcc`) used in this project can be installed [this](https://www.acmesystems.it/arm9_toolchain) way. The corresponding documentation can be found [here](https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html).

## Usage

If you want to use an assembly file directly, it should be located in the `test_files/asm` directory. Otherwise, C input programs should be placed in the `test_files/c_in` directory. To execute the script, run the **main.py** the following:

`python main.py <PROGRAM_NAME> <OPTIMIZATION> <BRANCH_PRED>`

The first argument is required and specifies the name of the program you want to run (located in the folder mentioned above). If you pass the filename with the **.s** ending, the assembly file will be used and no C code will be compiled. However, if you use the **.c** ending or no ending, the C code is compiled before the tool is run.

For the compilation process, you can specify the level of optimization GCC should use. This can be left


## Example

dawdaw

### SubSubtitle
#### SubSubSubtitle

Just a sample repo for learning the basics of GitHub.

More text with two line breaks between.

- dwada
- dawdawd
  - hallo
  - hallo2
    1. test
    2. test1

[this is the description](https://www.google.com)

This paragraph has some `variable` inline code.

```Python
def test(hallo:str) -> None:
    print('test')
```

![alt text](https://picsum.photos/200/200)

Some paragraph with text
> blockquote text below the paragraph

| heading | header | head |
| --- | --- | --- |
| content | more content | text |
| content2 | content3 | content4 |

This is being *created* on a ~~Saturday~~ **Sunday**.

