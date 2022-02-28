Extending the Tool
==================

Adding Another Assembly Language
--------------------------------

To support another assembly language, the most important classes need to be implemented:

- ``Parser (parser.py)``: Reads the input file and parses it into code blocks.
- ``Processor (processor.py)``: Used for some further processing depending on the assembly language.
- ``Counter (counter.py)``: Responsible for the instruction counting.
- ``BranchPredictor (branch_pred.py)``: Responsible for the branch prediction simulation.
- ``Translator (translator.py)``: Responsible for the translation of an assembly file.

These classes and other modules are all documented in the `code documentation <https://asm-analyser.readthedocs.io/en/latest/modules.html>`__. They have already been implemented for ARM assembly in the ``architectures.arm`` package, which can be used as a guide for other assembly languages. The correct classes then need to be instantiated in the ``main.py`` or in the ``asm-analyse`` script.

Adding More Branch Prediction Strategies
----------------------------------------

Branch prediction strategies can be implemented similar to the ones that currently exist in the ``ArmBranchPredictor`` class. The corresponding methods always initialize the necessary datastructures and update their values based on whether a branch was taken or not.

Adding More Features
--------------------

Due to time constraints, not all feature ideas could be implemented. Here are some features that could be added in the future:

- Number of cache misses that occurred
- Call graphs
- Time spent in subroutines

The easiest way to implement another feature would be to create a module which then works on the code or datastructures in the ``run_analysis`` function of the ``main.py``.

Other Improvements
------------------

Missing Instructions and Auxiliary Functions
********************************************

The ARM instructions have been added in a lazy manner. That is why a few rare instructions might still be missing for the translations. The same applies to the auxiliary functions. Maybe there is a way to translate the function calls directly from the library as soon as it is called. This would eliminate the need for a fixed dictionary for the auxiliary functions.

Supporting all C Datatypes
**************************

Not all C datatypes are supported at the moment. Variables of type ``long`` will not be translated correctly. They take up two registers in 32 bit ARM which makes the translation a bit harder. Combinations of the primitive data types in C may also cause problems. This needs to be tested further and a method for translating all the types needs to be developed.

Speedups
********

The status bits for the conditional instructions in ARM could only be calculated when needed. Since not all four bits are needed for a conditional instruction in many cases.

.. TODO: vllt das mit den Basic Blocks als Speedup hinzufügen. Aber nochmal mit Daniel besprechen, ob es wirklich ein Speedup ist.