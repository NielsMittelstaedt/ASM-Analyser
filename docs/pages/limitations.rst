Limitations
===========

- Only ARMv7-A or ARMv7-A compatible assembly is supported.
- "long" Datatype in C is not supported.
- The instruction translations were added in a lazy manner. This may cause a few translations to be missing.
- Auxiliary functions have been created to translate function calls from C libraries. The most common ones are covered by this approach. However some functions may still be missing.
- The printf auxiliary function for the translation supports only up to two format specifiers.
- If variable names such as those of the global variables or function names such as those of the auxiliary functions are used in the input program, this can cause the tool not to function as desired. To prevent this problem, a function is required that checks this and renames the variables or auxiliary functions if necessary.