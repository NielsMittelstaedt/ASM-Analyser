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

These classes and other modules are all documented in the `code documentation <https://asm-analyser.readthedocs.io/en/latest/modules.html>`__. They have already been implemented for ARM assembly, which can be used as a guide. The correct classes then need to be instantiated in the ``main.py`` or in the ``asm-analyse`` script.

Adding More Branch Prediction Strategies
----------------------------------------



Adding More Features
--------------------

Due to time constraints, not all feature ideas could be implemented. Some 


All these classes are implemented in the ``architectures.arm`` package. 

Different Assembly languages
More features
More branch prediction strategies
More instructions/auxiliary functions
Other improvements (speedups, better features,...)