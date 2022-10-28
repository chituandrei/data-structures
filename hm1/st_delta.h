void st(Tlist *list, int delta)
{
    int minim=0,maxim=0;
    sortare(list);
    
    minim = list->head->data;
    maxim = list->tail->data;
    
    if(minim<0 && minim != list->head->data) minim -= 1;
    if(maxim<0 && maxim != list->tail->data) maxim -= 1;

    if(minim>0 && minim != list->head->data) minim += 1;
    if(maxim>0 && maxim != list->tail->data) maxim += 1;
    
    node *aux ;
    int sol = 0;
    aux = list->head;
    
    while(aux != NULL)
    {
        if(aux->data > minim + delta )
        {
            printf("[%d, %d] %d\n",minim,minim+delta,sol);
            sol =0;
            while(aux->data > minim + delta)
            minim = minim + delta;
        }
        sol++;
        aux = aux->next;

    }
    if(sol!=0) printf("[%d, %d] %d\n",minim,minim+delta,sol);
    
}