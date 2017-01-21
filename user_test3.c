#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

void test_vfprintf(FILE * fp, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vfprintf(fp, format, args);
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
   int output;
   char strsnp3[25];
   char strsp3[80];
   char strvsnp3[25];
   char strvsp3[25];
   
   if (argc != 1)
   {
	  fprintf(stderr, "Usage: %s\n", argv[0]);
	  return -1;
   }

//Tests fprintf functionality.
   fp = fopen ("file3.txt", "w+");
   printf("\n\nOutput of fprintf in file file3.txt.\n");
   fprintf(fp, "hello world%n %s\n", &output, "CSE 545!");
   fprintf(fp, "%d\n", output);
   fclose(fp);

//Tests snprintf functionality.
   snprintf(strsnp3, 19, "hello world%n %s\n", &output, "CSE 545!");
   printf("\n\nOutput of snprintf :\n");
   puts(strsnp3);

//Tests sprintf functionality.
   sprintf(strsp3, "hello world%n %s\n", &output, "CSE 545!");
   printf("\n\nOutput of sprintf :\n");
   puts(strsp3);

//Tests vfprintf functionality.
   vfp = fopen ("vfile3.txt", "w+");
   printf("\n\nOutput of fprintf in file vfile3.txt.\n");
   test_vfprintf(vfp, "hello world%n %s\n", &output, "CSE 545!");
   test_vfprintf(vfp, "%d\n", output);
   fclose(vfp);

//Tests vprintf functionality.
   printf("\n\nOutput of vprintf :\n");
   test_vprintf("hello world%n %s\n", &output, "CSE 545!");
   test_vprintf("%d\n", output);

//Tests vsnprintf functionality.
   test_vsnprintf(strvsnp3, 21, "hello world%n %s\n", &output, "CSE 545!");
   printf("\n\nOutput of vsnprintf :\n");
   puts(strvsnp3);

//Tests vsprintf functionality.
   test_vsprintf(strvsp3, "hello world%n %s\n", &output, "CSE 545!");
   printf("\n\nOutput of vsprintf :\n");
   puts(strvsp3);

   return 0;
}
