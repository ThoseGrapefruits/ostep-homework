## Interlude: Process API (Simulation)

1.  ```
    a

    Action: a forks b

    a
    |- b

    Action: a forks c

    a
    |- b
    |- c

    Action: c EXITS

    a
    |- b

    Action: a forks d

    a
    |- b
    |- d

    Action: a forks e

    a
    |- b
    |- d
    |- e
```

2. The trees will get taller/deeper as the fork percentage increases.

3. Yep, the actions are clear from the tree diffs. Removals are clear, and
   which process forked a new process is also clear.

4. After a top-level process hosting children exits, the parent of that
   original process could adopt the child processes, but that might cause more
   problems than keeping them orphaned. In Unix, an orphan process is
   immediately reparented to an implementation-defined system process.

5. ```
    Action: a forks b
    Action: a forks c
    Action: b EXITS
    Action: a forks d
    Action: c forks e

    a
    |- c
       |- e
    |- d
```

6. There are a lot of ways to arrive at the same tree by multiple add and
   remove steps, and especially if there's reparenting.

