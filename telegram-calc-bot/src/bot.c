#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>  // for sleep()
#include "formula.h"
#include "parser.h"
#include <cjson/cJSON.h>


static char *url_encode(const char *str) {
    char *enc = malloc(strlen(str) * 3 + 1); 
    if (!enc) return NULL;
    char *penc = enc;

    while (*str) {
        if (isalnum((unsigned char)*str) || *str == '-' || *str == '_' || *str == '.' || *str == '~') {
            *penc++ = *str;
        } else {
            sprintf(penc, "%%%02X", (unsigned char)*str);
            penc += 3;
        }
        str++;
    }
    *penc = 0;
    return enc;
}

extern char *http_get(const char *url);

static void send_message(const char *token, long long chat_id, const char *text) {
    char url[2048];
    char *encoded_text = url_encode(text);
    if (!encoded_text) return;

    snprintf(url, sizeof(url),
        "https://api.telegram.org/bot%s/sendMessage?chat_id=%lld&text=%s",
        token, chat_id, encoded_text);

    free(encoded_text);

    char *response = http_get(url);
    if (response) {
        free(response);
    }
}

static const char *subjects_msg =
    "Choose a subject by number:\n"
    "1. Physics\n"
    "2. Chemistry\n"
    "3. Math";

static char *build_formulas_msg(int subject) {
    int base = 0;
    if (subject == 2) base = 5;
    else if (subject == 3) base = 8;

    char *msg = malloc(512);
    if (!msg) return NULL;
    strcpy(msg, "Choose a formula by number:\n");

    for (int i = 0; i < 5 && base + i < formula_count; ++i) {
        char line[64];
        snprintf(line, sizeof(line), "%d. %s\n", i + 1, formula_list[base + i].name);
        strcat(msg, line);
    }
    return msg;
}

enum BotState {
    STATE_SUBJECT = 0,
    STATE_FORMULA = 1,
    STATE_INPUTS = 2
};

struct ChatSession {
    int state;
    int subject;
    int formula_index;
    struct Formula selected_formula;
};

static struct ChatSession session = {STATE_SUBJECT, 0, 0};

static int parse_two_values(const char *input, double *vals, const char **units) {
    char buf[256];
    strncpy(buf, input, sizeof(buf)-1);
    buf[sizeof(buf)-1] = 0;
    return parse_input(buf, vals, units);
}

static void handle_message(const char *token, long long chat_id, const char *text) {
    if (session.state == STATE_SUBJECT) {
        int subj = atoi(text);
        if (subj >= 1 && subj <= 3) {
            session.subject = subj;
            char *form_msg = build_formulas_msg(subj);
            if (form_msg) {
                send_message(token, chat_id, form_msg);
                free(form_msg);
                session.state = STATE_FORMULA;
            } else {
                send_message(token, chat_id, "Error building formulas list.");
            }
        } else {
            send_message(token, chat_id, "Please enter a valid subject number (1-3).");
        }
    } else if (session.state == STATE_FORMULA) {
        int fidx = atoi(text);
        if (fidx >= 1 && fidx <= 5) {
            int base = 0;
            if (session.subject == 2) base = 5;
            else if (session.subject == 3) base = 8;

            session.formula_index = base + fidx - 1;
            if (session.formula_index < formula_count) {
                session.selected_formula = formula_list[session.formula_index];
                char msg[256];
                snprintf(msg, sizeof(msg), "Selected formula: %s\nEnter 2 known values with units (e.g. '10m 5s'):", session.selected_formula.name);
                send_message(token, chat_id, msg);
                session.state = STATE_INPUTS;
            } else {
                send_message(token, chat_id, "Invalid formula number.");
            }
        } else {
            send_message(token, chat_id, "Please enter a valid formula number (1-5).");
        }
    } else if (session.state == STATE_INPUTS) {
        double vals[3] = {0};
        const char *units[3] = {NULL};
        int got = parse_two_values(text, vals, units);
        if (got != 2) {
            send_message(token, chat_id, "Error: Provide exactly 2 known values with correct units.");
            return;
        }

        int missing = -1;
        for (int i = 0; i < 3; ++i) {
            if (!units[i]) {
                missing = i;
                break;
            }
        }
        if (missing == -1) {
            send_message(token, chat_id, "Couldn't determine the missing variable.");
            return;
        }

        double result = session.selected_formula.solver(vals[0], vals[1], missing);

        char msg[256];
        snprintf(msg, sizeof(msg), "Result: %s = %.3lf %s\n\n%s",
                 session.selected_formula.variables[missing].name,
                 result,
                 session.selected_formula.variables[missing].unit_aliases[0] ? session.selected_formula.variables[missing].unit_aliases[0] : "",
                 subjects_msg);

        send_message(token, chat_id, msg);

        session.state = STATE_SUBJECT;
    }
}

void run_bot(const char *token) {
    long long last_update_id = 0;

    send_message(token, 0, "Bot started. Use /start to begin.");

    while (1) {
        char url[1024];
        snprintf(url, sizeof(url),
            "https://api.telegram.org/bot%s/getUpdates?timeout=10&offset=%lld",
            token, last_update_id + 1);

        char *response = http_get(url);
        if (!response) {
            sleep(1);
            continue;
        }

        cJSON *json = cJSON_Parse(response);
        free(response);
        if (!json) {
            sleep(1);
            continue;
        }

        cJSON *ok = cJSON_GetObjectItem(json, "ok");
        if (!ok || !cJSON_IsBool(ok) || !ok->valueint) {
            cJSON_Delete(json);
            sleep(1);
            continue;
        }

        cJSON *result = cJSON_GetObjectItem(json, "result");
        if (!result || !cJSON_IsArray(result)) {
            cJSON_Delete(json);
            sleep(1);
            continue;
        }

        int update_count = cJSON_GetArraySize(result);

        for (int i = 0; i < update_count; i++) {
            cJSON *update = cJSON_GetArrayItem(result, i);
            cJSON *update_id = cJSON_GetObjectItem(update, "update_id");
            if (!update_id) continue;

            long long this_update_id = update_id->valuedouble;
            if (this_update_id <= last_update_id) continue;

            cJSON *message = cJSON_GetObjectItem(update, "message");
            if (!message) continue;

            cJSON *chat = cJSON_GetObjectItem(message, "chat");
            if (!chat) continue;

            cJSON *chat_id_json = cJSON_GetObjectItem(chat, "id");
            if (!chat_id_json) continue;

            long long chat_id = chat_id_json->valuedouble;

            cJSON *text_json = cJSON_GetObjectItem(message, "text");
            if (!text_json) continue;

            const char *text = text_json->valuestring;
            if (!text) continue;

            if (strncmp(text, "/start", 6) == 0) {
                session.state = STATE_SUBJECT;
                send_message(token, chat_id, subjects_msg);
            } else {
                handle_message(token, chat_id, text);
            }

            last_update_id = this_update_id;
        }

        cJSON_Delete(json);
        sleep(1);
    }
}
