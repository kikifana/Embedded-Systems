# Embedded Systems
## Project: Generation of Poisson and Rayleigh noise in color images.
### Goal:
Apply various optimization techniques in the original code (programming language C) in order to reduce the commands and cycles needed for its execution.
In order to see instructions and cycles ARMulator was used. 
### Optimization Techniques:
- **Avoiding C built-in functions**: Opt for operations directly because built in functions contain controls and parameters for general use, which
perform more processes burdening the code with more instructions and loops.
- **Loop Unrolling**: Small loops can be unrolled for higher performance,even though the code size is increased. When a loop is unrolled, a loop counter needs to be updated less often and fewer branches are executed.
The step for unrolling should not pass a certain number because then we only increase code size with no reduction in metrics.
- **Loop Fusion**: Two loops merge into one benefitting from parallelism and data reuse. Note that the loops need to have the same number of iterations in order to merge.
- **Loop interchange**: In loop interchange, the order of the nested for() changes. This happens to ensure that the elements of a multidimensional array are accessed in the order that
are located in memory improving locality.
- **Loop Inversion**: Use while() instead of for() and then if-do-while() instead of while().
Loop Inversion with Loop Unroll were the optimization techniques with the best metrics.
Then, memory was insterted with the files: scatter.txt, memory.map and stackheap.c.
### Memory:
- The next step is to adjust the memory size based on the size of ZI data.
- Tried SRAM,DRAM and seperated ZI data in 2 groups, variables that are frequently accessed and variables that are less accessed.
- Tried different read/write times. 
- Opt for ZI data to be inside main(), because then they are inside stack-heap which provides memory locality so less memory calls.
### Reuse Data Transformations:
- Insert buffer in order to re use data and have less memory calls. Buffers temporarily store parts of the original large arrays.
- Buffers need to be in the fastest memory.
- Buffers are Zero Initialized data, so  if they are in RAM they just add overhead.
