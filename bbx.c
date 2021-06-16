#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


int main(int argc,char **argv)
{
      /*   
	BITMAP_FILE_INFO_HEADER pixels;
	FILE *fp;
	fp = fopen("","r");

	if(fp == NULL)
	{
		printf("bmp fucking error");
	}
       */

	FILE *xx = fopen("n.txt","w");
        int shit = 5;
        char filenumber[10];

        for(int i=0; i<3 ; i++){          
        char buf[] = "#if define(__ICCARM__)\n#pragma\n locationn=\"ExtFlashSection\"\n";
		
          fprintf(xx,"%s",buf);

	  sprintf(filenumber,"%d",i);  //number to string
	  char filename[] = "unit32 display_";
          strcat(filename,filenumber);  //unit32 display_0
	  strcat(filename,"\n");
          fprintf(xx,"%s",filename);
	}

        fprintf(xx,"\n fucking end%d",shit);

        fclose(xx);	

	return 0;

}

