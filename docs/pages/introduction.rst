Introduction
============

This tool is intended to provide a simple way to dynamically analyse programs while generating as little overhead as possible. If the code to be analysed is provided in ARMv7-A (or compatible) assembly, it does not need to be compiled beforehand. Thus the tool can be used on any system that runs Python 3.6 or newer. Otherwise, the code is compiled using a GCC cross-compiler which needs to be installed on the system.

The main concept is to translate the assembly code to C. This is relatively straightforward since most ARM instructions can
be translated line by line into C. By doing so, it is possible to construct all kinds of datastructures and variables around the input program. This allows us to analyse many things about the execution of a program, e.g. number of instructions executed, branch prediction rates, number of cache misses, etc.

At the moment, the A32 instruction set for the ARMv7-A architecture is used as the assembly language. However, the tool can be easily extended to other assembly languages.