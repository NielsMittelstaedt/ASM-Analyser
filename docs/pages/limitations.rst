Limitations
===========

- Only ARMv7-A or ARMv7-A compatible assembly is supported.
- "long" Datatype in C is not supported.
- The instruction translations were added in a lazy manner. This may cause a few translations to be missing.
- Auxiliary functions have been created to translate function calls from C libraries. The most common ones are covered by this approach. However some functions may still be missing.
- The printf auxiliary function for the translation supports only up to two format specifiers.