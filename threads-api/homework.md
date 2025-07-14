Threads API
===========

1. It does report the right lines of code, and shows what other lines of code
   contain the original writes that are conflicting. It also shows the size
   of written data.
2. If one of the offending lines is removed, it outputs no errors or warnings.
   If a lock is added to one location, it describes the lock and the
   unprotected write. If locks are added in both places, it doesn't output
   any error messages, but does make a note about approx history flags for
   speed (hinting that it picked up on the locks that were happening).
3. In the deadlock, each thread acquires 1 of 2 locks, then tries to acquire
   the other lock, which is already held by the other thread.
4. `helgrind` describes how the lock order was established by the first thread
   to run (in this case, `m1` then `m2`) in order for everything to run smoothly.
   The locks have to be used in the same order across threads so that the first
   lock controls access to the later locks, which are themselves a kind of
   shared resource.
5. It does not have the same problem, because the `g` mutex controls access to
   the other 2 mutexes. However, `helgrind` still shows an error around the
   acquisition order of the mutexes, since the threads acquire the latter 2 of
   3 in different orders. It seems to be limited in observing the acquisition
   order of mutexes on each thread (more a code smell than a confirmed bug) but
   can't actually validate whether or not the usage is correct or safe.
6. The parent just spins until the child is done, rather than the thread going
   to sleep and being usable for other system resources.
7. `helgrind` reports a possible data race, which isn't true, but it is again
   not actually able to validate safe usage, but only recognize global access
   without locks.
8. This program is correct, and it performs much better than the basic signal
   program. It both:
   1. uses mutexes to sleep the waiting thread until the other has finished
   2. uses a flag to confirm that the thread is being awoken after the true
      completion of the other thread, rather than randomly awoken by the
      scheduler
9. It does not report any errors.
