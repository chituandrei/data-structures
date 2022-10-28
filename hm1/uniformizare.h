void u(Tlist *list)
{
	node *aux;
	aux = list->head;
	aux = aux->next;
	while(aux->next!=NULL)
	{
	    	if(aux->timestamp-aux->prev->timestamp>=100&&aux->timestamp-aux->prev->timestamp<=1000)
		{
				aux->data = (aux->data+aux->prev->data)/2;
				aux->timestamp = (aux->timestamp+aux->prev->timestamp)/2;
		}
        aux = aux->next;
	}
	if(aux->timestamp-aux->prev->timestamp>=100&&aux->timestamp-aux->prev->timestamp<=1000)
    {
				aux->data = (aux->data+aux->prev->data)/2;
				aux->timestamp = (aux->timestamp+aux->prev->timestamp)/2;
	}
}