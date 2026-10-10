/*
 * Home Electricity Bill Estimator
 * A configurable practice tool: rates below are examples, not an official tariff.
 * Build: gcc -std=c11 -Wall -Wextra -Wpedantic main.c -o electricity
 */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int read_double(const char *prompt, double *out) {
    char line[128], *end = NULL;
    printf("%s", prompt);
    if (!fgets(line, sizeof line, stdin)) return 0;
    *out = strtod(line, &end);
    while (*end == ' ' || *end == '\t' || *end == '\n' || *end == '\r') ++end;
    return end != line && *end == '\0' && isfinite(*out);
}

static double energy_charge(double units) {
    /* Example progressive slabs. Replace with your electricity provider's tariff. */
    double charge = 0.0;
    if (units > 500) { charge += (units - 500) * 8.0; units = 500; }
    if (units > 300) { charge += (units - 300) * 6.5; units = 300; }
    if (units > 100) { charge += (units - 100) * 4.5; units = 100; }
    charge += units * 3.0;
    return charge;
}

int main(void) {
    double previous, current, fixed, tax_pct, units, energy, tax, total;
    if (!read_double("Previous meter reading (kWh): ", &previous) ||
        !read_double("Current meter reading (kWh): ", &current) ||
        !read_double("Fixed monthly charge (example: 75): ", &fixed) ||
        !read_double("Tax/surcharge percentage (0-100): ", &tax_pct)) {
        fprintf(stderr, "Invalid input. Enter numeric values only.\n");
        return EXIT_FAILURE;
    }
    if (previous < 0 || current < previous || fixed < 0 || tax_pct < 0 || tax_pct > 100) {
        fprintf(stderr, "Check values: readings/charges cannot be negative, current must be >= previous, and percentage must be 0-100.\n");
        return EXIT_FAILURE;
    }
    units = current - previous;
    energy = energy_charge(units);
    tax = (energy + fixed) * tax_pct / 100.0;
    total = energy + fixed + tax;
    printf("\n--- Estimated monthly bill ---\n");
    printf("Energy used : %.2f kWh\n", units);
    printf("Energy cost : %.2f\n", energy);
    printf("Fixed charge: %.2f\n", fixed);
    printf("Tax/surcharge: %.2f\n", tax);
    printf("Estimated total: %.2f\n", total);
    printf("\nNote: illustrative slab rates only; verify your provider's current tariff.\n");
    return EXIT_SUCCESS;
}
