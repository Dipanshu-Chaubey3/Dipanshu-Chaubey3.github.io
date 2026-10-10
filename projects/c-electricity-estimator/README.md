# Home Electricity Bill Estimator (C)

A small command-line tool that estimates household electricity cost from meter readings. It calculates usage, progressive example slabs, a fixed monthly charge, and an optional percentage surcharge.

## Why it is useful
It helps households estimate a bill before it arrives and understand how usage affects the total.

## Build and run
```bash
gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o electricity
./electricity
```
On Windows with MinGW, run `electricity.exe` after compiling.

## Important
The rates in `energy_charge()` are **illustrative examples, not an official tariff**. Edit the slabs and fixed charge to match the current rate schedule from your own provider. Subsidies, meter fees, time-of-use pricing and local taxes are not automatically included.

## Concepts practised
C functions, input validation, progressive slabs, arithmetic, formatted output, and defensive error handling.
