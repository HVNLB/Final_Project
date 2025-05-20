#ifndef HTTP_H
#define HTTP_H

char *http_get(const char *url);
char *http_post(const char *url, const char *post_fields);

#endif
