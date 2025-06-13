## Homework (Simulation)

1. CPU utilization should be 100%. 
2. With `-l 4:100,1:0`, it would take 4 instructions plus the time taken to
   complete the cycle of I/O.
3. It should only take the longer of the length of the I/O or 4 instructions,
   plus time to start and tear down each process.
4. The CPU waits on the blocked process until IO completes, then finishes that
   process, then switches to the other one.
5. It runs as before in problem 3, only taking as much time as the longest of
   the two processes + cleanup time.
6. The I/O-heavy process is the long-tail, as its later I/O can't start until
   all of the other CPU-intensive tasks are complete, at which point it only
   has I/O to do and the CPU sits idle.
7. It's far more efficient because the I/O-intensive task is able to kick off
   further I/O, then yield control back to other processes to use the CPU while
   it waits for each stage of I/O to complete. This could be a good idea
   because a task doing I/O is likely focused on doing so, and is doing small
   amounts of computation between larger I/O operations.
8. Random programs doing an even mix of I/O and CPU are probably going to
   behave better when `IO_RUN_IMMEDIATE` is enabled, and significantly worse
   when using `SWICH_ON_END` vs `..._ON_IO`.

