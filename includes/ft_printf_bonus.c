#include "ft_printf_bonus.h"

static t_flags pf_init(void)
{
	t_flags f;

	f.minus = 0;
	f.zero = 0;
	f.dot = 0;
	f.width = -1;
	f.precision = -1;
	f.hash = 0;
	f.plus = 0;
	f.space = 0;
	f.spec = 0;
	return (f);
}

int ft_printf(const char *fmt, ...)
{
	va_list ap;
	int     count = 0;

	if (!fmt)
		return (-1);
	va_start(ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%')
		{
			t_flags f = pf_init();
			fmt = pf_parse(fmt + 1, &f, ap);
			if (f.spec) {
				char *raw = pf_conv(ap, &f);
				if (!raw) { va_end(ap); return (-1); }
				count += pf_emit(raw, &f);
				free(raw);
			}
			else {
				/* invalid or stray %, print '%' literally */
				count += write(1, "%", 1);
			}
		}
		else
			count += write(1, fmt, 1);
		if (*fmt)
			fmt++;
	}
	va_end(ap);
	return (count);
}