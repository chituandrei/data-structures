double media(node * aux)
{
    node *prev1,*prev2,*next1,*next2;
    prev1 = aux->prev;
    prev2 = aux->prev->prev;
    next1 = aux->next;
    next2 = aux->next->next;
    double rez;
    rez = (prev1->data + prev2->data + next1->data + next2->data + aux->data)/5;
    return rez;
}
double dev(node* aux,double medie)
{   int i=0;double sum=0;
    aux = aux->prev->prev;
    for(i=1;i<=5;i++)
        {
        	sum+=(aux->data-medie)*(aux->data-medie);
        	aux = aux->next;
        }
    
    sum = sum/5;
    sum = sqrt(sum);
    return sum;
}
void statistici(Tlist *list)
{
    int i;
	node *aux;
    aux = list->head->next->next;
    for(i=2;i<list->len-2;i++)
    {   
        double medie, deviatia ;
        medie = media(aux);
        deviatia = dev(aux,medie);
        aux=aux->next;
        if(aux->prev->data < medie - deviatia || aux->prev->data > medie  + deviatia)
           aux->prev->ok = 1;                
    }
    aux = list->head;
    while(aux!=NULL)
    {

    	if(aux->ok==0)
    	{
            aux = aux->next;
    	}
        else
        {
            aux = aux->next;
            deleteNode(list,aux->prev);
        }
    }
}