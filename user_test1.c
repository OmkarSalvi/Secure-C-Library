#include <stdio.h>
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

void test_vsprintf(char * str, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsprintf(str, format, args);
	va_end(args);
}

void test_vsnprintf(char * str, size_t n, const char * format, ...)
{
	va_list args;
	va_start(args, format);
	vsnprintf(str, n, format, args);
	va_end(args);
}

int main(int argc, char** argv)
{
   FILE * fp;
   FILE * vfp;
   char strnp1[15];
   char strp1[80];
   char strvsp1[15];
   char strvsnp1[15];

   if (argc != 2)
   {
	  fprintf(stderr, "Usage: %s <name>\n", argv[0]);
	  return -1;
   }

//Tests fprintf functionality.
   fp = fopen ("file1.txt", "w+");
   printf("\n\nOutput of fprintf in file file1.txt.\n");
   fprintf(fp, "hello ");
   fprintf(fp, argv[1]);
   fprintf(fp, "\n");
   fclose(fp);

//Tests snprintf functionality.
   snprintf(strnp1, 15, "hello ");
   snprintf(strnp1, 15, argv[1]);
   printf("\n\nOutput of snprintf : \n");
   puts(strnp1);

//Tests sprintf functionality.
   sprintf(strp1, "hello ");
   sprintf(strp1, argv[1]);
   printf("\n\nOutput of sprintf : \n");
   puts(strp1);

//Tests vfprintf functionality.
   vfp = fopen ("vfile1.txt", "w+");
   printf("\n\nOutput of vfprintf in file vfile1.txt.\n");
   test_vfprintf(vfp, "hello ");
   test_vfprintf(vfp, argv[1]);
   test_vfprintf(vfp, "\n");
   fclose(vfp);

//Tests vprintf functionality.
   printf("\n\nOutput of vprintf : \n");
   test_vprintf("hello ");
   test_vprintf(argv[1]);
   test_vprintf("\n");

//Tests vsprintf functionality.
   test_vsprintf(strvsp1, "hello ");
   test_vsprintf(strvsp1, argv[1]);
   printf("\n\nOutput of vsprintf : \n");
   puts(strvsp1);

//Tests vsnprintf functionality.
   test_vsnprintf(strvsnp1, 15, "hello ");
   test_vsnprintf(strvsnp1, 15, argv[1]);
   printf("\n\nOutput of vsnprintf : \n");
   puts(strvsnp1);

   return 0;
}
