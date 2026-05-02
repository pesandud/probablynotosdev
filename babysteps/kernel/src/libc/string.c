#include <stddef.h>
size_t strlen(const char *s) {
  size_t len = 0;
  while (s[len++]);
  return len - 1;
}

char *strcpy(char *dst, char *src) {
  if (dst == NULL || src == NULL)
    return NULL;
  char *tmp = dst;
  while (*dst++ = *src++)
    ;
  return tmp;
}

char *strncpy(char *dst, char *src, size_t n) {
  if (dst == NULL || src == NULL)
    return NULL;
  char *tmp = dst;
  while (n > 0 && *src != '\0') {
    *dst++ = *src++;
		n--;
  }

	// if n > length of src, pad the rest with \0
	while (n > 0) {
		*dst++ = '\0';
		n--;
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
