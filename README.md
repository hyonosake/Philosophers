The Dining Philosopher Problem states that K philosophers seated around a circular table with one chopstick between each pair of philosophers. There is one chopstick between each philosopher. A philosopher may eat if he can pickup the two chopsticks adjacent to him. One chopstick may be picked up by any one of its adjacent followers but not both.

A two-way solution on dining philosophers problem:
1. Using threads to represent philosophers and mutexes to represent forks.
2. Using processes to represent philosophers and semaphores to represent availible forks.