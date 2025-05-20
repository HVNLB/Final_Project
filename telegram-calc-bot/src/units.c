#include <string.h>
#include "units.h"

struct UnitPrefix {
    const char *prefix;
    double multiplier;
};

static struct UnitPrefix prefixes[] = {
    {"km", 1000.0},
    {"hm", 100.0},
    {"dam", 10.0},
    {"m", 1.0},
    {"dm", 0.1},
    {"cm", 0.01},
    {"mm", 0.001},
    {"kg", 1.0}, // base
    {"g", 0.001},
    {"mg", 0.000001},
    {"s", 1.0},
    {"min", 60.0},
    {"h", 3600.0},
    {"L", 1.0},
    {"mL", 0.001},
    {0}
};

double normalize_unit(const char *input, const char **base_unit_out)
{
    for (int i = 0; prefixes[i].prefix != 0; ++i) {
        size_t len = strlen(prefixes[i].prefix);
        if (strncmp(input, prefixes[i].prefix, len) == 0) {
            if (base_unit_out) *base_unit_out = prefixes[i].prefix;
            return prefixes[i].multiplier;
        }
    }

    if (base_unit_out) *base_unit_out = NULL;
    return -1.0;
}
