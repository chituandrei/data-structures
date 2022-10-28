// Am creeat o functie care sterge legaturile dintre noduri si depozite
float** sterge_Depozite(graph * Graf){
    float **matrix = malloc(Graf->nr_nodes * sizeof(float *));
    int i,j;

    for(i = 0; i < Graf->nr_nodes; i++)
        *(matrix+i) = malloc(Graf->nr_nodes * sizeof(float));   
    
    for(i = 0; i < Graf->nr_nodes; i++){
        for(j = 0; j < Graf->nr_nodes; j++)
            matrix[i][j] = -1;
    }
    // Am alocat memorie si am initializat matricea cu -1

    for(i = 0 ; i < Graf->nr_nodes; i++)
        {
            node *temp = Graf->neighbours[i];

            while(temp != NULL){
                
                if(Graf->neighbours[temp->y]->depozit != 1 && Graf->neighbours[i]->depozit !=1) //Adaug muchia a-b daca 
                    matrix[i][temp->y] = temp->cost;                                      //a si b nu sunt depozite
                temp = temp->next;
            }
        }
        return matrix;
}

int DFS(int start,int dest,graph *Graf,float** matrix){

    int i;
    
    Graf->visited[start] = 1; // marchez nodul de plecare ca vizitat
    
    for(i = 0; i < Graf->nr_nodes; i++){

        if(matrix[start][i] !=-1 && Graf->visited[i] ==0) // Daca exista muchie de la start la i si i este nevizitat
            DFS(i,dest,Graf,matrix);
        
    }
    if(Graf->visited[dest] == 1) // Daca exista drum de la start la dest returnez 1
        return 1;
    return 0;    
}
void reinitializez(graph *Graf){
    int t;
    for(t = 0; t < Graf->nr_nodes; t++) // initializez visited cu 0 penntru alt dfs
        Graf->visited[t] = 0;
}

// Functia verifica daca am afisat toate nodurile (adica toate componentele tare conexe) pentru a nu afisa un spatiu
// in plus la final
int verific_daca_afisez_spatiu(int *sol, int in,graph *Graf){
    int r;
    for(r = in; r < Graf->nr_nodes; r++)
        if(sol[r] == 0 && Graf->neighbours[r]->depozit ==0)
            return 1;
    return 0; 
}

void cerinta2(graph * Graf){
    int p =0,i,j,*sol = calloc(Graf->nr_nodes , sizeof(int));
    float ** matrix = sterge_Depozite(Graf);
    
    //merg de la j la fiecare nod care nu este depozit si numar cate dfs uri fac pentru a parcurge tot graful
    for(j = 0; j< Graf->nr_nodes;j++){   
        if(sol[j] == 0 && Graf->neighbours[j]->depozit == 0){
            sol[j] = 1; // un alt vector de visited care retine cate dfs uri fac
                for(i = 0; i< Graf->nr_nodes; i++)
                    if(i!=j){
                        reinitializez(Graf);
                            if(DFS(j,i,Graf,matrix)==1){   
                                reinitializez(Graf);
                                    if(DFS(i,j,Graf,matrix)==1) // daca exista drum de la i la j
                                        sol[i]=1; // marchez i ca fiind parte dintr o componenta tare conexa
                    }
                }
                p++; // contorizez numarul de componente tare conexe
        } 
    }   
    printf("%d\n",p);
    
    reinitializez(Graf);
    
    for(j=0; j < Graf->nr_nodes; j++)
        sol[j] = 0;
    
    // Repet acelasi algoritm doar ca acum nu mai numar cate DFS uri se fac si afisez calea
    for(j = 0; j< Graf->nr_nodes;j++){   
        if(sol[j] == 0 && Graf->neighbours[j]->depozit == 0){
            sol[j] = 1;
            printf("%d",j);
            
            for(i = 0; i< Graf->nr_nodes; i++)
                if(i!=j){
                    reinitializez(Graf);
                        if(DFS(j,i,Graf,matrix)==1){   
                            reinitializez(Graf);
                                if(DFS(i,j,Graf,matrix)==1)
                                    printf(" %d",i),sol[i]=1;
                }
            }   
            if(verific_daca_afisez_spatiu(sol,j,Graf) == 1)
                printf("\n");
        }
    }   
    free(sol);
    freeGraphMatrix(matrix,Graf->nr_nodes);
}

