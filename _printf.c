#include "main.h"

void print_buffer(char buffer[], int *buff);

/**
 * _printf - Printf function
 * @format: format.
 * Return: Printed charters.
 */
int _printf(const char *format, ...)
{
	int i, p = 0, chars = 0;
	int flag, width, prec, size, buff = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);

	for (i = 0; format && format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			buffer[buff++] = format[i];
			if (buff == BUFF_SIZE)
				print_buffer(buffer, &buff);
			/* write(1, &format[i], 1);*/
			chars++;
		}
		else
		{
			print_buffer(buffer, &buff);
			flag = get_flags(format, &i);
			size = get_size(format, &i);
			width = get_width(format, &i, list);
			prec = get_precision(format, &i, list);
			++i;
			p = handle_print(format, &i, list, buffer,
				flag, width, prec, size);
			if (p == -1)
				return (-1);
			chars += p;
		}
	}

	print_buffer(buffer, &buff);

	va_end(list);

	return (chars);
}

/**
 * print_buffer - Prints contents of buffer only if it exist
 * @buffer: Array of chars
 * @buff: Index at which to add next char, reps length.
 */
void print_buffer(char buffer[], int *buff)
{
	if (*buff > 0)
		write(1, &buffer[0], *buff);

	*buff = 0;
}
