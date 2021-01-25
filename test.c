#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <float.h>

#include "libftprintf.h"

#define BLUE	"\033[34m"
#define BOLD	"\033[1m"
#define RED		"\033[31m"
#define RESET	"\033[0m"
#define YELLOW	"\033[33m"

#define MAXBUF	1024


#define pr(fmt, ...) \
	{ \
		int n1, n2; \
		setvbuf(stdout, NULL, _IONBF, 0); \
		printf("=== \"" BLUE BOLD); \
		write(1, fmt, strlen(fmt)); \
		printf(RESET "\" ======= " BLUE BOLD); \
		printf(#__VA_ARGS__); \
		printf(RESET "\n|" YELLOW); \
		n1 = printf(fmt, __VA_ARGS__); \
		printf(RESET "| %d\n", n1); \
		printf("|" YELLOW); \
		n2 = ft_printf(fmt, __VA_ARGS__); \
		printf(RESET "| "); \
		printf(n1 != n2 ? RED "%d" RESET "\n" : "%d\n", n2); \
	}

int main(void)
{
	char *p = "";

	int	i, j;
	int	*ip, *jp;

	i = 0;
	j = 0;
	ip = &i;
	jp = &j;
	pr("percent \%123", NULL);
	ft_printf("abcde%nfghij%n\n", ip, jp);
	printf("%i %d\n", *ip, *jp);

	pr("%010.10d", -123);
	pr("%.06s", NULL);
	pr("%-.08s", NULL);
	pr("%10d", -123);
	pr("%.40p", p);
	pr("%-s", "hello");
	pr("%10.s", NULL);
	pr("1234 _%20s_ abc%-3%def", "ARGUMENT");
	pr("%6.9s", "abc");
	pr("%10.10d", -123);
	pr("%10.2d", -123);
	pr("%10.0d", -123);
	pr("%10.d", -123);
	pr("%0d", -123);
	pr("%0d", 0);
	pr("%010.4d", 0);
	pr("%02d", 123);
	pr("%010.d", -123);
	pr("%-10.10d", -123);
	pr("%-010.10d", -123);
	pr("%-010.d", -123);
	pr("%X", 123u);
	pr("%X", -123u);
	pr("%0d", 0);
	pr("%.03s", "Abriged string");
	pr("%.03s", NULL);
	pr("%+.3i", 0);
	pr("%0-10d", -123);
	pr("%*.*d", 0, 3, 0);
	pr("%*.*d", 0, 3, 7);
	pr("%p", p);
	pr("%-p", p);
	pr("%-+03d", INT_MAX);
	pr("%d", INT_MIN);
	pr("%d", -2147483649);
	pr("%+d", 3);
	pr("% d", 3);
	pr("%+d", 0);
	pr("% d", 0);
	pr("%+u", 3);
	pr("% u", 3);
	pr("%+u", 0);
	pr("% u", 0);

	pr("%-010d", -123);
	pr("%010.d", 0);
	pr("%010d", 0);
	pr("%010d", -123);
	pr("%010d", 123);
	pr("%+010d", 123);
	pr("% 010d", 123);

	pr("%+010x", 123);
	pr("% 010x", 123);

	pr("%-+030p", NULL);
	pr("%- 030p", p);
	pr("%-+030p", p);
	pr("% 030p", p);
	pr("%+030p", p);
	pr("%-x", 42);
	pr("p19 %.3x", 100);
	pr("%010jx", 0x2bcda);

	pr("percent \%123", NULL);
	pr("percent %123", NULL);

	setlocale(LC_ALL, "");
	pr("%c", L'щ');
	pr("%lc", L'й');
	pr("%hc", L'й');
	pr("%hhc", L'й');
	pr("%llc", L'й');
	pr("%jc", L'й');
	pr("%tc", L'й');
	pr("%zc", L'й');
	pr("%012s", L"щука");
	pr("%012ls", L"йогурт — Who would win? 100 🐜 or 1 🕷 ?");

	pr("===============", NULL);

	pr("%.0e", 2.71);
	pr("%#.0e", 2.71);
	pr("%.0f", 2.71);
	pr("%#.0f", 2.71);
	pr("%.8e", 2.71);
	pr("%.8f", 2.71);
	pr("%F", 1.0 / 0.0);
	pr("%+f", 1.0 / 0.0);
	pr("%f", INFINITY * INFINITY);
	pr("%f", INFINITY * -INFINITY);
	pr("%+0f", NAN);
	pr("% 0F", NAN);
	pr("%0f", NAN);
	pr("%f", 0.0f);
	pr("%0.0f", 0.0f);
	pr("%f", 2e-4);
	pr("%.10f", 2e-4);
	pr("%.f", 0.5);
	pr("%.f", -1.5);
	pr("%.f", -2.5);
	pr("%.f", 2.5);
	pr("%.f", 3.5);
	pr("%.f", 0.51);
	pr("%.f", 0.6);
	pr("%f", 0.11);
	pr("%e", 123.45);
	pr("%.55g", 0.11234785909057654);
	pr("%.55g", -123.45e-32);

	pr("%.100f", 0.1);
	pr("%.f", DBL_MAX);
	return 0;
}
