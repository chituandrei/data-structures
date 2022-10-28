float costMinimDeLaNodLaNod(float **matrix,int start,int dest,graph *Graf,int *v){
    int i;
    float raspuns = 99999999,adun; 

    if(start == dest) // daca am ajuns la nodul dest
        return 0;

    Graf->visited[start] = 1; // marchez start ca vizitat
    
    for (i = Graf->nr_nodes-1 ; i >= 0; i--){
        if(matrix[start][i] != -1 && !Graf->visited[i]){    // daca nodul este nevizitat si exista muchie     
            adun = costMinimDeLaNodLaNod(matrix,i,dest,Graf,v); // Aplez recursiv drumul
            
            if(raspuns > matrix[start][i] + adun){     //verific daca cost_total + muchie < raspuns
                    raspuns = matrix[start][i] + adun;  // modific rezultatul
                    v[start] = i ;  // creez vectorul pentru afisarea path-ului
            } 
        }
    }
    
    Graf->visited[start] = 0; // marchez nodul de start ca nevizitat pentru celelate DFS uri
    return raspuns;    // returnez costul minim de la drum la drum
}
void printPath(int parent[], int j,int v[],int *lv){
    if (parent[j] == -1) // cazul de baza
        return;
    printPath(parent, parent[j],v,lv); // merg recursiv pe vector
    *(lv) = *(lv) + 1; // modific lungimea vectorului rezultat
    v[*(lv)] = j;   // actualizez vectorul rezultat
}
void cerinta1(graph* Graf){
    
    int nod_start,numar_noduri_finale,nod_final,i;
    int *v = malloc(Graf->nr_nodes * sizeof(int));
    int *sol1 = malloc(Graf->nr_nodes * sizeof(int));
    int *sol2 = malloc(Graf->nr_nodes * sizeof(int));
    float cost_total = 0,**matrix = buildGraphMatrix(Graf);
    
    scanf("%d",&nod_start);
    scanf("%d",&numar_noduri_finale);

    for (i = 0; i <numar_noduri_finale; i++){
        int t,j,lv = 0,lv2 = 0;

        scanf("%d",&nod_final);
        printf("%d\n",nod_final); // afisez nodul la care trebuie sa ajung

        for(t = 0 ; t < Graf->nr_nodes; t++) // initializez vectorul de tati cu -1 
            v[t] = -1;

        // afisez lungimea drumului de la start la dest si retin in v , vectorul de tati
        printf("%0.1f ",costMinimDeLaNodLaNod(matrix,nod_start,nod_final,Graf,v));                                                                         

        //calculez costul total 
        cost_total += costMinimDeLaNodLaNod(matrix,nod_start,nod_final,Graf,v);

        //retin in sol1 calea de la a la b
        printPath(v,nod_start,sol1,&lv);

        //reinitializez vectorul de tati
        for(t = 0 ; t < Graf->nr_nodes; t++)
            v[t] = -1;   

        printf("%0.1f\n",costMinimDeLaNodLaNod(matrix,nod_final,nod_start,Graf,v));        
        
        cost_total += costMinimDeLaNodLaNod(matrix,nod_final,nod_start,Graf,v);
        
        //retin in sol2 calea de la b la a
        printPath(v,nod_final,sol2,&lv2);

        //afisez nodul de start
        printf("%d ",nod_start);

        //afisez invers vectorul de cale de la a la b
        for (j = lv-1; j >= 1; j--)
            printf("%d ",sol1[j]);

        printf("%d ",nod_final);

        for (j = lv2-1; j >= 1; j--)
            printf("%d ",sol2[j]);
        
        printf("%d",nod_start);

        printf("\n");
        
    }
    printf("%0.1f",cost_total);

    free(v);
    free(sol1);
    free(sol2);
    freeGraphMatrix(matrix,Graf->nr_nodes);
}
