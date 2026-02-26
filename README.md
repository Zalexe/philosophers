Philosophers – 42 School Project
## Overview

Philosophers is a concurrency project from the 42 curriculum based on the classic synchronization problem described by Edsger W. Dijkstra: the Dining Philosophers Problem.

The objective is to simulate multiple philosophers sitting at a table, alternating between eating, thinking, and sleeping, while sharing limited resources (forks). The challenge is to coordinate access to shared resources without causing deadlocks, race conditions, or starvation.

## Project Scope

The project includes:

·  Creating and managing multiple threads (one per philosopher)

·  Synchronizing shared resources using mutexes

·  Preventing race conditions

·  Avoiding deadlocks

·  Detecting philosopher death based on timing constraints

·  Handling precise time measurement

·  Ensuring clean thread termination and memory management

Implemented in:

·  C

·  POSIX Threads (pthreads)

·  Mutexes for synchronization

## Project Focus

Philosophers focuses on:

·  Understanding thread creation and lifecycle management

·  Coordinating access to shared resources

·  Designing synchronization strategies

·  Managing concurrent state safely

·  Working with timing constraints in a multithreaded environment

·  Structuring deterministic behavior under concurrency

## Technical Scope

The project explores fundamental concurrency concepts. It involves designing a synchronization model where philosophers compete for limited resources while ensuring the system remains stable.

Special attention is required to:

·  Order of mutex locking

·  Preventing circular wait conditions

·  Monitoring thread state without introducing data races

·  Balancing performance with correctness

The emphasis is on understanding how concurrent systems behave and how subtle timing issues can affect correctness.

## Build & Run
    make
    ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
