# Bus Ticket Reservation

A command-line seat reservation program written in C. It models 20 bus seats with a linked list and supports the full reservation lifecycle from availability checks to cancellation.

## Features

- View the current status of every seat
- Reserve an available seat for a passenger
- Prevent duplicate reservations for the same national code
- Cancel a reservation after identity verification
- Find a passenger by name or national code
- Color-coded terminal feedback

## Build and run

### With CMake

```bash
cmake -S . -B build
cmake --build build
./build/Bus_Ticket_Reservation
```

### With a C compiler

```bash
cc -std=c23 -Wall -Wextra -pedantic main.c -o bus-ticket-reservation
./bus-ticket-reservation
```

## How it works

Each seat is stored as a node containing its number, reservation state, passenger name, national code, and a pointer to the next seat. The program validates seat numbers, blocks duplicate national codes, and requires the matching code before a reservation can be cancelled.
