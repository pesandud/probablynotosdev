#include <stddef.h>
size_t strlen(const char *s) {
  size_t len = 0;
  while (s[len++]);
  return len - 1;
}

char *strcpy(char *dst, char *src) {
  if (dst == NULL || src == NULL)
    return;
  char *tmp = dst;
  while (*dst++ = *src++)
    ;
  return tmp;
}

char *strncpy(char *dst, char *src, size_t n) {
  if (dst == NULL || src == NULL)
    return;
  char *tmp = dst;
  while (n) {
    *dst++ = *src++;
  }
  return tmp;
}

int strcmp(const char *s1, const char *s2) {
  for (int i = 0; i < strlen(s1); i++) {
    int ret = s1[i] - s2[i];
    if (ret > 0)
      return 1;
    else if (ret < 0)
      return -1;
  }
}
