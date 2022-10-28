#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "graf_implementation.h"
#include "cerinta1.h"
#include "cerinta2.h"
#include "cerinta3.h"

int main(){
    
    int n, m, nr_dep, i;
    
    graph *Graf;
    
    scanf("%d %d %d", &n, &m, &nr_dep); // citesc prima linie

    int *depozite = malloc(nr_dep * sizeof(int));

    Graf = createGraph(n);  // aloc memorie pentru Graf

    for (i = 0; i < m; i++){
        int x, y;
        float val;
        scanf("%d %d %f", &x, &y, &val);

        addGraphEdge(Graf, x, y, val); // adaug muchiile
    }

    for(i = 0; i < nr_dep; i++){
        int id_dep;
        scanf("%d",&id_dep);
        Graf->neighbours[id_dep]->depozit = 1;
        *(depozite + i) = id_dep;
        // Parcurge graful si marcheaza nodurile care sunt depozite
    }
    
    int nr_cerinte; // citesc numarul de cerinte

    scanf("%d", &nr_cerinte);

    int p;

    for(p = 0; p < nr_cerinte; p++){
        char *input = (char *)malloc(3 * sizeof(char));
        scanf("%s",input);
        if(p > 0)printf("\n");
         if(strcmp(input,"e1") == 0) cerinta1(Graf); // execut cerinta1
         if(strcmp(input,"e2") == 0) cerinta2(Graf); // execut cerinta2
         if(strcmp(input,"e3") == 0) cerinta3(Graf,depozite,nr_dep); // execut cerinta3
         
         free(input); // dezaloc input
         
    }
    free(depozite);
    freeGraph(Graf);   
}