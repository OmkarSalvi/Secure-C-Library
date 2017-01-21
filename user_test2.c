#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void test_vfprintf(FILE * vfp, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(vfp, format, args);
	va_end(args);
}

void test_vprintf(const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vprintf(format, args);
	va_end(args);
}

void test_vsnprintf(char * str, size_t n, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(str, n, format, args);
	va_end(args);
}

void test_vsprintf(char * str, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
}


int main(int argc, char** argv)
{
   FILE * fp;
   FILE * vfp;
   char* str;
   char* strvp;
   int limit = 100;

   char strsnp2[15];
   char strsp2[150];
   char strvsnp2[15];

   if (argc != 2)
   {
	  fprintf(stderr, "Usage: %s <name>\n", argv[0]);
	  return -1;
   }

   str = malloc(limit);
   strncat(str, "Hello ", limit-1);
   strncat(str, argv[1], limit-1);

//Tests fprintf functionality.
   fp = fopen ("file2.txt", "w+");
   printf("\n\nOutput of fprintf in file file2.txt.\n");
   fprintf(fp, str);
   fprintf(fp, "\n");
   fclose(fp);

//Tests snprintf functionality.
   snprintf(strsnp2, 15, str);
   printf("\n\nOutput of snprintf : \n");
   puts(strsnp2);

//Tests sprintf functionality.
   sprintf(strsp2, str);
   printf("\n\nOutput of sprintf : \n");
   puts(strsp2);

//Tests vfprintf functionality.
   vfp = fopen ("vfile2.txt", "w+");
   printf("\n\nOutput of vfprintf in file vfile2.txt.\n");
   test_vfprintf(vfp, str);
   test_vfprintf(vfp, "\n");
   fclose(fp);

//Tests vprintf functionality.
   printf("\n\nOutput of vprintf : \n");
   test_vprintf(str);
   test_vprintf("\n");

//Tests vsnprintf functionality.
   test_vsnprintf(strvsnp2, 15, str);
   printf("\n\nOutput of vsnprintf : \n");
   puts(strvsnp2);

   return 0;
}
