#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "list.h" // lista si toate functiile 
#include "statistici.h" // task1
#include "filtrare.h" // task2
#include "uniformizare.h" //task3
#include "completare.h" // task4 
#include "st_delta.h" // task5

int main (int argc, char *argv[])
{
    int len = 0, i = 0, timestamp = 0,cerinta = 0;;
	double data = 0;
    Tlist *list;
    init(&list); 
	scanf("%d",&len);	
	
	for(i=0;i<len;i++) 
	{
        scanf("%d",&timestamp);
		scanf("%lf",&data);
		add(list,data,timestamp);
	}
	cerinta = 1;
    for (i = 1; i < argc; ++i)
        {
			if(strstr(argv[i],"e1") != NULL)statistici(list);
			if(strstr(argv[i],"e2") != NULL)mediana(list);
			if(strstr(argv[i],"e3") != NULL)aritmetica(list);
			if(strstr(argv[i],"u") != NULL)u(list);
			if(strstr(argv[i],"c") != NULL)completeaza(list);

			if(strstr(argv[i],"st") != NULL)
				{	cerinta = 2;
					int nr=0,j=0,lv = -1;
					while(argv[i][++lv] != 't');
					
					for(j = lv+1 ; j < strlen(argv[i]); j++)
						nr = nr * 10 + (argv[i][j] - '0');
					
					st(list,nr);
				}
		}
	if(cerinta == 1)
		print(list);

	freeList(list);
	free(list);
	
}
