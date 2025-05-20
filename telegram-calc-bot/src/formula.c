#include <stdio.h>
#include <math.h>
#include "formula.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static double solve_fma(double x, double y, int missing) {
    if (missing == 0) return x * y;
    if (missing == 1) return x / y;
    return y == 0 ? 0 : x / y;
}

static double solve_vuat(double u, double t, int missing) {
    if (missing == 0) return u + t; // simplified; assume a = 1
    if (missing == 1) return u + t; // dummy default
    return u - t;
}

static double solve_suvat(double u, double t, int missing) {
    if (missing == 0) return u * t + 0.5 * t * t;
    if (missing == 1) return (sqrt(4 * u * u + 8 * 0.5 * t * t) - 2 * u) / t;
    return (t * t - 2 * u * t) / 1;
}

static double solve_power(double w, double t, int missing) {
    if (missing == 0) return w / t;
    if (missing == 1) return w / t;
    return w / t;
}

static double solve_density(double m, double v, int missing) {
    if (missing == 0) return m / v;
    if (missing == 1) return m / v;
    return m / v;
}

static double solve_moles(double m, double M, int missing) {
    if (missing == 0) return m / M;
    if (missing == 1) return m / M;
    return m / M;
}

static double solve_concentration(double n, double V, int missing) {
    if (missing == 0) return n / V;
    if (missing == 1) return n / V;
    return n / V;
}

static double solve_pv_nrt(double P, double V, int missing) {
    double R = 0.0821, T = 300; // assume room temp and ideal gas constant
    if (missing == 0) return (1 * R * T) / V;
    if (missing == 1) return (1 * R * T) / P;
    return (P * V) / (R * T);
}

static double solve_circle_area(double r, double unused, int missing) {
    return M_PI * r * r;
}

static double solve_circle_perimeter(double r, double unused, int missing) {
    return 2 * M_PI * r;
}

static double solve_pythagoras(double a, double b, int missing) {
    return sqrt(a * a + b * b);
}

static double solve_line(double m, double x, int missing) {
    return m * x + 0; // assume c = 0 for now
}

// Formula list
struct Formula formula_list[] = {
    // Physics
    {"F = m * a", {{"F", {"N", 0}}, {"m", {"kg", 0}}, {"a", {"m/s^2", 0}}}, solve_fma},
    {"v = u + at", {{"v", {"m/s", 0}}, {"u", {"m/s", 0}}, {"t", {"s", 0}}}, solve_vuat},
    {"s = ut + 0.5at^2", {{"s", {"m", 0}}, {"u", {"m/s", 0}}, {"t", {"s", 0}}}, solve_suvat},
    {"P = W / t", {{"P", {"W", 0}}, {"W", {"J", 0}}, {"t", {"s", 0}}}, solve_power},
    {"ρ = m / V", {{"ρ", {"kg/m^3", 0}}, {"m", {"kg", 0}}, {"V", {"m^3", 0}}}, solve_density},

    // Chemistry
    {"n = m / M", {{"n", {"mol", 0}}, {"m", {"g", 0}}, {"M", {"g/mol", 0}}}, solve_moles},
    {"C = n / V", {{"C", {"mol/L", 0}}, {"n", {"mol", 0}}, {"V", {"L", 0}}}, solve_concentration},
    {"PV = nRT", {{"P", {"atm", 0}}, {"V", {"L", 0}}, {"n", {"mol", 0}}}, solve_pv_nrt},

    // Math
    {"A = πr^2", {{"A", {"m^2", 0}}, {"r", {"m", 0}}, {"-", {0}}}, solve_circle_area},
    {"P = 2πr", {{"P", {"m", 0}}, {"r", {"m", 0}}, {"-", {0}}}, solve_circle_perimeter},
    {"c^2 = a^2 + b^2", {{"c", {"m", 0}}, {"a", {"m", 0}}, {"b", {"m", 0}}}, solve_pythagoras},
    {"y = mx + c", {{"y", {"-", 0}}, {"m", {"-", 0}}, {"x", {"-", 0}}}, solve_line}
};

int formula_count = sizeof(formula_list) / sizeof(struct Formula);
