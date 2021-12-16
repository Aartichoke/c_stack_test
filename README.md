# c_stack_test
Test how c allocates memory with different overflow issues

First disable address space layout randomization (ASLR) 
sudo sysctl -w kernel.randomize_va_space=0

Tracer1:
Addresses:
rc = 0xffffd52c
buf = 0xffffd537
x = 0xffffd570
It appears they are in descending order of definition, with x being the first. Each run had the same address.

Tracer2:
Buffer and array are in higher addresses than stuff.
The function does not recurse, because int depth is set to 10 on the function call, and the recursion only
occurs if function < 10. The addresses remain the same.
Changing the depth to 1, however, we can observe that the addresses get lower with each loop.
A new space is being allocated for each loop, with buf being allocated first (having the highest address), then 
stuff getting memory space slightly lower, then rc getting space as the return value of the function at an
even lower address.

Tracer3:
The addresses dont' change each run. the stack variables are in the 0xffffdxx block, the local functions are in 0x56555xxx, 
and the c print function is in the lowest 0xf7e3ec60 address. 
The local variables are addressed in the stack, while the global functions are located lower in the address 
space in the heap. The stack appears to use more of a top down approach.

Tracer4:
Each hex digit represents four bits, and it would appear three (~12 bits) of them are being randomized on the stack when 
comparing the differences between array, buffer, and x on each execution to the previous runs without ASLR randomizing.
It appears only the two most significant hex digits remain the same, so 4 x 6 bits are addressable here in total. 
Highest for buffer: 0xfff8a294
Lowest for buffer: 0xffd1d004
It sppears the 3 most significant digits don't change, so 4 x 5 bits are addressable here.
Highest for function: 0x5659b5dd
Lowest for function: 0x5656a5dd
Lastly, it appears anything above 0x56000000 is usable by the code.
Highest: 0xfff8a294
Lowest: 0x5656a5dd
