Example
=======

We can now execute the following command, for example:

``asm-analyse -f quicksort.c -o O2 -b one_bit``

This produces the following output:

.. image:: docs/sample_console.png

We can also see the branch prediction success rate and the number of times each assembly line was executed in the assembly file::

    1.00 6 	add	r1, r4, #1
    1.00 6 	cmp	r1, r6
    0.67 6 	blt	.L10
    1.00 1 	pop	{r4, r5, r6, r7, r8, r9, r10, pc}

For non-branch instructions, the sucess rate is always 1.00.