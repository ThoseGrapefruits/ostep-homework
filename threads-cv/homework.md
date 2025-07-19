Homework (code) -- Condition Variables
======================================

1.  It will allocate a buffer of length 1 and run 1 producer and 1 consumer on a
    single value.
2.  Larger buffers allow for a given consumer or producer to run for longer at
    once, having fewer context switches.
3.  __TODO__ run on macOS
4.  It will take about 10 seconds, because the buffer size is 1 and each
    consumer is essentially blocking all other consumers.
5.  It seems like changing the buffer size to 3 would affect the runtime because
    each consumer can now consume 3 entries at a time, so that pause will
    (probably) only happen once per 3 entries, and the overall runtime should be
    about 3s. However, this depends on how much each producer actually adds to the
    queue, and because the producer yields (with `Cond_signal(&fill);`) after
    _each_ addition, it's likely to never add more than 1 element at a time and
    have a runtime comparable to `-m 1`, depending on how things race out.
6.  This runtime is going to be much faster, because the lock has been released
    for other consumers. Even if the buffer is small, all 3 consumers will be
    able to run in parallel relatively efficiently. It should be approximately
    the input length (10) divided by 3, plus some overhead. It is a little over
    5s in my test runs.
7.  In this case, an increased buffer size is going to reduce the amount of time
    that producers have to wait to add things to the queue, but the overall
    runtime will be about the same.
8.  I think with 1 producer and 1 consumer, there isn't a way to trigger an
    error or deadlock in this code, thanks to using Mesa semantics and safely
    double-checking our condition variable with a `while` loop.
9.  With 2 consumers, there is not a way to trigger an error or deadlock because
    it is using 2 separate condition variables: one for the buffer being empty,
    and the other for the buffer being full.
10. Yes, a race is possible if the underlying condition in the consumer or
    producer (the buffer being empty or full) isn't actually re-checked with a
    `while` loop after `Cond_wait`, which may have already been reset by
    another consumer or producer.
11. Two different producers could call `do_fill` at the same time, with an
    interrupt happening between incrementing the buffer and incrementing the
    fill count. This would result in a value being lost.

