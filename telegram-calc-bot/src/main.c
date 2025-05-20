#include <stdio.h>
#include <stdlib.h>
#include "bot.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <telegram_bot_token>\n", argv[0]);
        return 1;
    }

    const char *token = argv[1];
    run_bot(token);

    return 0;
}
