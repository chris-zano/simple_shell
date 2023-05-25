#include "shell.h"

/**
 * _memchr - searches the first n bytes of the memory area pointed to by s
 * @s: memory area to scan
 * @c_in: first instance to look for
 * @n: size in bytes
 *
 * Return: void
 */

void *_memchr(void const *s, int c_in, size_t n)
{
	const unsigned char *char_ptr;
	longword *longword_ptr, repeated_one, repeated_c, longword1;
	unsigned char c = (unsigned char) c_in;
	size_t i;

	for (char_ptr = (const unsigned char *) s;
	 n > 0 && (size_t) char_ptr % sizeof(longword) != 0;
	 --n, ++char_ptr)
	if (*char_ptr == c)
		return ((void *) char_ptr);
	longword_ptr = (longword *) char_ptr;
	repeated_one = 0x01010101;
	repeated_c = c | (c << 8);
	repeated_c |= repeated_c << 16;
	if (0xffffffffU < (longword) -1)
	{
		repeated_one |= repeated_one << 31 << 1;
		repeated_c |= repeated_c << 31 << 1;
		if (sizeof(longword) > 8)
		{
			for (i = 64; i < sizeof(longword) * 8; i *= 2)
			{
				repeated_one |= repeated_one << i;
				repeated_c |= repeated_c << i;
			}
		}
	}
	while (n >= sizeof(longword))
	{
		longword1 = *longword_ptr ^ repeated_c;
		if ((((longword1 - repeated_one) & ~longword1) & (repeated_one << 7)) != 0)
			break;
		longword_ptr++;
		n -= sizeof(longword);
	}
	char_ptr = (const unsigned char *) longword_ptr;
	for (; n > 0; --n, ++char_ptr)
		if (*char_ptr == c)
			return ((void *) char_ptr);
	return (NULL);
}
