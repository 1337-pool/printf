#include "ft_printf_bonus.h"

size_t pf_strlen(const char *s)
{
	size_t i = 0; if (!s) return 0; while (s[i]) i++; return i;
}

char *pf_strdup(const char *s)
{
	size_t n = pf_strlen(s);
	char *p = (char *)malloc(n + 1);
	if (!p) return NULL;
	for (size_t i=0;i<n;i++) p[i]=s[i];
	p[n]='\0';
	return p;
}

char *pf_strjoin_free(char *a, char *b)
{
	if (!a || !b) { free(a); free(b); return NULL; }
	size_t la = pf_strlen(a), lb = pf_strlen(b);
	char *r = (char *)malloc(la + lb + 1);
	if (!r) { free(a); free(b); return NULL; }
	for (size_t i=0;i<la;i++) r[i]=a[i];
	for (size_t j=0;j<lb;j++) r[la+j]=b[j];
	r[la+lb]='\0';
	free(a); free(b);
	return r;
}

char *pf_pad_left(char *s, int total, char pad)
{
	int len = (int)pf_strlen(s);
	if (len >= total) return s;
	int need = total - len;
	char *r = (char *)malloc(total + 1);
	if (!r) { free(s); return NULL; }
	for (int i=0;i<need;i++) r[i]=pad;
	for (int i=0;i<len;i++) r[need+i]=s[i];
	r[total]='\0';
	free(s);
	return r;
}

char *pf_pad_right(char *s, int total, char pad)
{
	int len = (int)pf_strlen(s);
	if (len >= total) return s;
	int need = total - len;
	char *r = (char *)malloc(total + 1);
	if (!r) { free(s); return NULL; }
	for (int i=0;i<len;i++) r[i]=s[i];
	for (int i=0;i<need;i++) r[len+i]=pad;
	r[total]='\0';
	free(s);
	return r;
}

int pf_write(const char *s) { return (int)write(1, s, pf_strlen(s)); }
int pf_max(int a, int b) { return (a>b)?a:b; }
int pf_isdigit(int c) { return (c >= '0' && c <= '9'); }

/* ----- integer to string helpers ----- */
char *pf_utoa_base(unsigned long n, int base, int upper)
{
	char buf[65]; /* enough for base 2 of 64-bit */
	const char *digits = upper ? "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	                           : "0123456789abcdefghijklmnopqrstuvwxyz";
	int i = 64;
	buf[i] = '\0';
	if (n == 0) { buf[--i] = '0'; }
	else
	{
		while (n)
		{
			buf[--i] = digits[n % (unsigned)base];
			n /= (unsigned)base;
		}
	}
	return pf_strdup(&buf[i]);
}

char *pf_itoa_signed(long n)
{
	if (n == 0) return pf_strdup("0");
	int neg = (n < 0);
	unsigned long u = neg ? (unsigned long)(-n) : (unsigned long)n;
	char *d = pf_utoa_base(u, 10, 0);
	if (!d) return NULL;
	if (neg)
	{
		char *r = pf_strjoin_free(pf_strdup("-"), d);
		return r;
	}
	return d;
}