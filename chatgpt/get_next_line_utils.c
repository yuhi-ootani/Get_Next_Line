#include "get_next_line.h"

char *ft_substr(char *s, unsigned int start, size_t len)
{
    char *sub;
    size_t i;

    if (!s)
        return (NULL);
    if (start >= ft_strlen(s))
        return (NULL);
    if (ft_strlen(s + start) < len)
        len = ft_strlen(s + start);
    sub = malloc(len + 1);
    if (!sub)
        return (NULL);
    i = 0;
    while (i < len && s[start + i])
    {
        sub[i] = s[start + i];
        i++;
    }
    sub[i] = '\0';
    return (sub);
}
#include "get_next_line.h"

char *ft_strjoin(char *s1, char *s2)
{
    size_t i = 0;
    size_t j = 0;
    char *joined;

    if (!s1 && !s2)
        return (NULL);
    if (!s1)
    {
        s1 = malloc(1);
        if (!s1)
            return (NULL);
        s1[0] = '\0';
    }
    joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
    if (!joined)
        return (NULL);
    while (s1[i])
    {
        joined[i] = s1[i];
        i++;
    }
    while (s2[j])
        joined[i++] = s2[j++];
    joined[i] = '\0';
    free(s1);
    return (joined);
}
#include "get_next_line.h"

char *ft_strchr(const char *s, int c)
{
    if (!s)
        return (NULL);
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if (c == '\0')
        return ((char *)s);
    return (NULL);
}
#include "get_next_line.h"

size_t ft_strlen(const char *s)
{
    size_t i = 0;
    if (!s)
        return (0);
    while (s[i])
        i++;
    return (i);
}
