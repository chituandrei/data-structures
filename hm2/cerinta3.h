float** buildSubGraf(float** generata,int* zona,int nr){
	
	float **matrix = malloc(nr * sizeof(float *)); // aloc memorie pentru matrice
    int i,j;

    for(i = 0; i < nr; i++)
        *(matrix+i) = malloc(nr * sizeof(float));   
    
    for(i = 0; i < nr; i++){
        for(j = 0; j < nr; j++)
            matrix[i][j] = -1;  // initializez toate elementele cu -1
    }
	for(i = 0; i < nr-1; i ++){
		for(j = i + 1; j < nr; j++){

			matrix[i][j] = generata[zona[i]][zona[j]];  // in matrix[i][j] retin legatura dintre nodul i si j din zona 
			matrix[j][i] = generata[zona[j]][zona[i]]; // astfel numaratoarea nodurilor incepe de la 0 si se termina la
		}												// nr_noduri - 1 (Am facut asta pentru a shifta direct in mask)
	}
	return matrix;
}
unsigned long long countSetBits(unsigned long long n)
{
    unsigned long long nrBits1 = 0;
    while (n) {		
        nrBits1 += n & 1; // numar cati biti de 1 are fiecare masca
        n >>= 1;
    }
    return nrBits1;
}
float E3minimumPath(float ** matrix,int n){
	int i,lviz = -1;
	unsigned long long masca_finala,newMask,count_mask,count_newMask;
	float r,cost;

	vizitat *viz = malloc(1000 * sizeof(vizitat)); // structura in care retin toate perechile vizitate
	distante *d = calloc(2000 , sizeof(int));	// structura in care retin si actualizez distantele
	
	Queue *q;
	init_queue(&q);
	add_queue(q,0,1); // adaug in coada nodul de start si starea lui
	
	for(i = 0; i < n; i++)
		d[i].mask = 0,d[i].val = 99999999;  // initializez mastile cu 0 si val cu maxim (Nu era necesar pt valoare)

	d[0].val = 0; // retin distanta initiala pana la 0
	d[0].mask = 1; // retiin masca lui 0
	
	while(is_empty_queue(q) == 0){  
		
		unsigned long long mask = front_mask(q); // extrag din coada masca
		int nod = front_val(q);	// extrag din coada nodul
		
		pop_queue(q);

		lviz++;	// lungimea structurii creste
		add_viz(viz,nod,mask,lviz); //adaug in structura de vizitati nodul si masca
		
		for(i = 0; i < n; i ++)
			if(matrix[nod][i] >= 0){	//daca exista muchie de la nod la i

				newMask = (mask | (1 << i));  // calculez noua masca pentru nodul i
				count_mask = countSetBits(d[i].mask); // numar cati biti de 1 are prima masca
				count_newMask = countSetBits(newMask); // numar cati biti de 1 are a doua masca
				cost = matrix[nod][i];	// retin costul pentru a nu face apel in matrice de prea multe ori

				if(count_mask < count_newMask  || (count_mask == count_newMask && d[i].val > d[nod].val + cost)){
					// actualizez costul doar daca am gasit o masca cu mai multi biti de 1, adica mai multe noduri 
					// vizitate sau daca am acelasi numar de noduri vizitate pana in acel punct al algoritmului
					// dar costul este mai mic
					d[i].val = d[nod].val + cost;
					d[i].mask = newMask; 
					}
				
				if(find_viz(viz,nod,newMask,lviz) == 0) // daca nu a fost vizitata perechea
						add_queue(q,i,newMask);			// o adaug in coada
			}	
	}
	r = d[0].val; // retin rezultatul pentru a nu se pierde in free-uri

	free_queue(&q); 
	free(viz);
	free(q);
	free(d);
	
	return r;
}
void cerinta3(graph* Graf,int *depozite,int nr_dep){
	int lv=0,i,numar_zone,y,j,nr;
	int t,p,k;
	float minim = 99999999;
	
	scanf("%d",&numar_zone);
	
	for(i = 0; i < numar_zone; i++){
		
		lv = 0;
		scanf("%d",&nr);
		
		int *zona = (int *)malloc((nr+1) * sizeof(int));  // aloc vectorul ce retine nodurile din zona i din cerinta

		for(j = 0; j < nr; j ++){
			scanf("%d",&y);
			if(Graf->neighbours[y]->depozit == 0)
				lv++,*(zona+lv) = y; // adaug in zona nodurile incepand cu pozitia 1
		}

		for(p = 0; p < nr_dep; p++){
			zona[0] = depozite[p]; // pe pozitia 0 pastrata libera adaug fiecare depozit pe rand
									// si calculez costum minim din drum pentru fiecare depozit aflat pe poz de inceput
		float ** generata = buildGraphMatrix(Graf); // generez matricea care incepe de la 0 si retine doar 
		float ** matrix = buildSubGraf(generata,zona,nr+1); // muchiile dintre nodurile din zona si depozit
		float valMinPath = E3minimumPath(matrix,nr+1); // retin valoarea minima a drumului pentru a nu apela functi
														// de mai multe ori
		if(minim>valMinPath)
			minim = valMinPath;
		
		freeGraphMatrix(matrix,nr+1);
		freeGraphMatrix(generata,Graf->nr_nodes);
		}
		if(i == 0) printf("%0.1f",minim);
		else printf("\n%0.1f",minim);

		free(zona);
	}	
}