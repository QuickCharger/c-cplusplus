/*ProgramtocreatebackupoftheAUTOEXEC.BATfile*/
#include <stdio.h>
int main(void)
{
	char c;
    FILE *in,*out;
    in = fopen("d:/test_EditPlus/test_EditPlus.cpp", "rt");
    if(in == NULL)
    {
        fprintf(stderr, "Can not open inputfile.\n");
        return 1;
    }
    out = fopen("d:/test_EditPlus/test_EditPlus", "wt");
    if(out == NULL)
    {
        fprintf(stderr, "Can not open outputfile.\n");
        return 1;
    }
/*    while(!feof(in))
	{
        fputc(fgetc(in), out);
	}
*/
	while((c = fgetc(in)) != EOF )
	{
		fputc(c, out);
		puts(&c);
	}
    fclose(in);
    fclose(out);
    return 0;
}