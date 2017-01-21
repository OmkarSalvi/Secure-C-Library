#define _GNU_SOURCE
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <stdarg.h>


int printf(const char *format, ...)
{
        va_list list;
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(printf) *old_printf;

	parg = format;
	temp = format;
	
	old_printf = dlsym(RTLD_NEXT, "printf");

	va_start(list, format);

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_printf)("%%");
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_printf)("%d", ival);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_printf)("%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_printf)("%u", uval);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_printf)("%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_printf)("%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_printf)("%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_printf)("%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_printf)("%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_printf)("%F", dval);
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
						putchar(*sval);
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_printf)("%c", cval);
					break;
		
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					//(*old_printf)("%x");
					break;
				case 'p':
					nval = va_arg(list, int);
					//(*old_printf)("%p");
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					putchar(*parg);
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_printf)("%c", *temp);
		}
	}//end of while

	va_end (list);

	return 0;
}

int vprintf(const char *format, va_list list)
{
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(printf) *old_printf;

	parg = format;
	temp = format;
	
	old_printf = dlsym(RTLD_NEXT, "printf");

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_printf)("%%");
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_printf)("%d", ival);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_printf)("%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_printf)("%u", uval);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_printf)("%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_printf)("%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_printf)("%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_printf)("%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_printf)("%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_printf)("%F", dval);
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
						putchar(*sval);
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_printf)("%c", cval);
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					//(*old_printf)("%x");
					break;
				case 'p':
					nval = va_arg(list, int);
					//(*old_printf)("%p");
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					putchar(*parg);
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_printf)("%c", *temp);
		}
	}//end of while

	return 0;
}

int fprintf(FILE *stream, const char *format, ...)
{
        va_list list;
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(fprintf) *old_fprintf;

	parg = format;
	temp = format;
	
	old_fprintf = dlsym(RTLD_NEXT, "fprintf");

	va_start(list, format);

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_fprintf)(stream, "%%");
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_fprintf)(stream, "%d", ival);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_fprintf)(stream, "%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_fprintf)(stream, "%u", uval);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%F", dval);
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
						fputc(*sval, stream);
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_fprintf)(stream, "%c", cval);
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					//(*old_fprintf)(stream, "%x");
					break;
				case 'p':
					nval = va_arg(list, int);
					//(*old_fprintf)(stream, "%p");
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					fputc(*parg, stream);
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_fprintf)(stream, "%c", *temp);
		}
	}//end of while

	va_end (list);

	return 0;
}

int vfprintf(FILE *stream, const char *format, va_list list)
{
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(fprintf) *old_fprintf;

	parg = format;
	temp = format;
	
	old_fprintf = dlsym(RTLD_NEXT, "fprintf");

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_fprintf)(stream, "%%");
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_fprintf)(stream, "%d", ival);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_fprintf)(stream, "%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_fprintf)(stream, "%u", uval);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_fprintf)(stream, "%F", dval);
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
						fputc(*sval, stream);
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_fprintf)(stream, "%c", cval);
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					//(*old_fprintf)(stream, "%x");
					break;
				case 'p':
					nval = va_arg(list, int);
					//(*old_fprintf)(stream, "%p");
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					fputc(*parg, stream);
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_fprintf)(stream, "%c", *temp);
		}
	}//end of while

	return 0;
}

int sprintf(char *str, const char *format, ...)
{
        va_list list;
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	int char_count = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(sprintf) *old_sprintf;

	parg = format;
	temp = format;
	
	old_sprintf = dlsym(RTLD_NEXT, "sprintf");

	va_start(list, format);

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;					
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_sprintf)((str + char_count), "%%");
					char_count++;
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%d", ival);
					char_count = char_count + sizeof(int);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%u", uval);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%F", dval);
					break;
				case 's':
					for(sval = va_arg(list, char *); *sval; sval++)
					{
						(*old_sprintf)((str + char_count), "%c", *sval);
						char_count++;
					}
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_sprintf)((str + char_count), "%c", cval);
					char_count++;
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'p':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					(*old_sprintf)((str + char_count), *parg);
					char_count++;
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_sprintf)((str + char_count), "%c", *temp);
			char_count++;
		}
	}//end of while
	
	(*old_sprintf)((str + char_count), "\0");
	va_end (list);

	return char_count;
}

int vsprintf(char * str, const char *format, va_list list)
{
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	int char_count = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(sprintf) *old_sprintf;

	parg = format;
	temp = format;
	
	old_sprintf = dlsym(RTLD_NEXT, "sprintf");

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;					
				}
			}
			
			switch (*parg)
			{
				case '%':
					(*old_sprintf)((str + char_count), "%%");
					char_count++;
					break;
				case 'd':
					ival = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%d", ival);
					char_count = char_count + sizeof(int);
					break;
				case 'o':
					ival = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%o", ival);
					break;
				case 'u':
					uval = va_arg(list, int);
					(*old_sprintf)((str + char_count), "%u", ival);
					break;
				case 'e':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%e", dval);
					break;
				case 'E':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%E", dval);
					break;
				case 'f':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%f", dval);
					break;
				case 'F':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%F", dval);
					break;
				case 'g':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%f", dval);
					break;
				case 'G':
					dval = va_arg(list, double);
					(*old_sprintf)((str + char_count), "%F", dval);
					break;
				case 's':
					for(sval = va_arg(list, char *); *sval; sval++)
					{
						(*old_sprintf)((str + char_count), "%c", *sval);
						char_count++;
					}
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					cval = (char) va_arg(list, int);
					(*old_sprintf)((str + char_count), "%c", cval);
					char_count++;
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'p':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					(*old_sprintf)((str + char_count), *parg);
					char_count++;
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			(*old_sprintf)((str + char_count), "%c", *temp);
			char_count++;
		}
	}//end of while
	
	(*old_sprintf)((str + char_count), "\0");

	return char_count;
}

int snprintf (char * str, size_t n, const char * format, ... )
{
        va_list list;
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	int char_count = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(sprintf) *old_snprintf;

	parg = format;
	temp = format;
	
	old_snprintf = dlsym(RTLD_NEXT, "snprintf");

	va_start(list, format);

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;
				}
			}
			
			switch (*parg)
			{
				case '%':
					if(char_count < (n - 1))
					{
						(*old_snprintf)((str + char_count), (n - char_count), "%%");
						char_count++;
					}
					break;
				case 'd':
					if(char_count < (n - 1))
					{
						ival = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%d", ival);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'o':
					if(char_count < (n - 1))
					{
						ival = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%o", ival);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'u':
					if(char_count < (n - 1))
					{
						uval = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%u", uval);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'e':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%e", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'E':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%E", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'f':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%f", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'F':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%F", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'g':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%g", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'G':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%G", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
					{
						if(char_count < (n-1))
						{
							(*old_snprintf)((str + char_count), (n - char_count), "%c", *sval);
							char_count++;
						}
					}
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					if(char_count < (n-1))
					{
						cval = (char) va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%c", cval);
						char_count++;
					}
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'p':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					if(char_count <= (n-1))
					{
						(*old_snprintf)((str + char_count), (n - char_count), *parg);
						char_count++;
					}
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			if(char_count < (n-1))
			{
				(*old_snprintf)((str + char_count), (n - char_count), "%c", *temp);
				char_count++;
			}
		}
	}//end of while

	(*old_snprintf)((str + char_count), 1, "\0");

	va_end (list);

	return char_count;
}

int vsnprintf(char * str, size_t n, const char *format, va_list list)
{
	char *parg, *temp, *sval;

	int ival, nval;
	unsigned int uval;
   	double dval;
	char cval;
	int i = 0;
	int entered = 0;
	int char_count = 0;
	
	const char flags[] = {'-','+','0',' ','#','1','2','3','4','5','6','7','8','9','.','*','h','l','L','z','j','t'};

	typeof(sprintf) *old_snprintf;

	parg = format;
	temp = format;
	
	old_snprintf = dlsym(RTLD_NEXT, "snprintf");

	while(!(*parg == '\0'))
	{
		entered = 0;
		temp = parg;
		*parg++;

		if(*temp == '%')
		{
			entered = 1;
			for(i = 0; i < 22; i++)
			{
				if(*parg == flags[i])
				{
					*temp++;
					*parg++;
					i = -1;				
				}
			}
			
			switch (*parg)
			{
				case '%':
					if(char_count < (n - 1))
					{
						(*old_snprintf)((str + char_count), (n - char_count), "%%");
						char_count++;
					}
					break;
				case 'd':
					if(char_count < (n - 1))
					{
						ival = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%d", ival);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'o':
					if(char_count < (n - 1))
					{
						ival = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%o", ival);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'u':
					if(char_count < (n - 1))
					{
						uval = va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%u", uval);
						if((char_count + sizeof(int)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(int);
						}
					}
					break;
				case 'e':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%e", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'E':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%E", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'f':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%f", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'F':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%F", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'g':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%g", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 'G':
					if(char_count < (n - 1) )
					{
						dval = va_arg(list, double);
						(*old_snprintf)((str + char_count), (n - char_count), "%G", dval);
						if((char_count + sizeof(double)) > (n - 1))
						{
							char_count = (n - 1);
						}
						else
						{
							char_count = char_count + sizeof(double);
						}
					}
					break;
				case 's':
					for (sval = va_arg(list, char *); *sval; sval++)
					{
						if(char_count < (n-1))
						{
							(*old_snprintf)((str + char_count), (n - char_count), "%c", *sval);
							char_count++;
						}
					}
					break;
				case 'c':              // char : need a cast here since va_arg only takes fully promoted types
					if(char_count < (n-1))
					{
						cval = (char) va_arg(list, int);
						(*old_snprintf)((str + char_count), (n - char_count), "%c", cval);
						char_count++;
					}
					break;
				case 'X':
				case 'x':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'p':
					nval = va_arg(list, int);
					// Avoid Data Leakage. Do not print anything.
					break;
				case 'n':
					nval = va_arg(list, int);
					break;
				default:
					if(char_count <= (n-1))
					{
						(*old_snprintf)((str + char_count), (n - char_count), *parg);
						char_count++;
					}
					break;
			}
			*parg++;
		}//end of if

		if (entered == 0)
		{
			if(char_count < (n-1))
			{
				(*old_snprintf)((str + char_count), (n - char_count), "%c", *temp);
				char_count++;
			}
		}
	}//end of while

	(*old_snprintf)((str + char_count), 1, "\0");

	return char_count;
}
