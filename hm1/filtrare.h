void mediana(Tlist* list)
{
   node* adaugare,*aux_list; // auxiliar to iterate the list
   aux_list = list->head; 
   
   while(aux_list->next->next->next->next!=NULL)
    {
    
      Tlist* clist; //building an auxiliar list
      init(&clist); // initiating
      
      add(clist,aux_list->data,aux_list->timestamp);
      add(clist,aux_list->next->data,aux_list->next->timestamp);
      add(clist,aux_list->next->next->data,aux_list->next->next->timestamp);
      add(clist,aux_list->next->next->next->data,aux_list->next->next->next->timestamp);
      add(clist,aux_list->next->next->next->next->data,aux_list->next->next->next->next->timestamp);

      aux_list->timestamp = clist->head->next->next->timestamp;
      
      sortare(clist);

      aux_list->data = clist->head->next->next->data;      
        
      aux_list = aux_list->next;
     
      freeList(clist);
      free(clist);
    }
    
   deleteLast4(list);
    
}   
void aritmetica(Tlist* list)
{  double ma = 0;
   node *aux_list ,*calcul; 
   aux_list = list->head; 

   while(aux_list->next->next->next->next!=NULL)
    {
      ma = 0;
      Tlist* rlist; 
      init(&rlist); 

      add(rlist,aux_list->data,aux_list->timestamp);
      add(rlist,aux_list->next->data,aux_list->next->timestamp);
      add(rlist,aux_list->next->next->data,aux_list->next->next->timestamp);
      add(rlist,aux_list->next->next->next->data,aux_list->next->next->next->timestamp);
      add(rlist,aux_list->next->next->next->next->data,aux_list->next->next->next->next->timestamp);

      calcul = rlist->head;
      while(calcul!=NULL)
      {
        ma += calcul -> data;
        calcul = calcul ->next;
      }
      ma = ma/5;
      aux_list->data = ma;
      aux_list->timestamp = rlist->head->next->next->timestamp;
    
      aux_list = aux_list->next;

      freeList(rlist);
      free(rlist);
    }
    
    deleteLast4(list);
}   


