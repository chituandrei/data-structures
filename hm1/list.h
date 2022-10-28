typedef struct node {
    int timestamp;
    double data;
    struct node* next;
    struct node* prev;
    int ok;
}node;

typedef struct Tlist {
	int len;
	struct node* head;
	struct node* tail;
}Tlist;

void init (Tlist **list)
{
    *list = calloc(1,sizeof(node));
    (*list)->head = NULL;
    (*list)->tail = NULL;
    (*list)->len = 0;
}

void add (Tlist *list,double  data,int timestamp)
{   
    if(list->len !=0)
    {
        node *new_node = calloc(1,sizeof(node));
        new_node->data = data; /// adding data
        new_node->timestamp = timestamp;
        new_node->prev = list->tail; 
        list->tail->next = new_node; 
        new_node->next = NULL; 
        list->tail = new_node; ///tail modified
        new_node -> ok =0;
        list->len++;
    }
    if(list->len==0)
    {
        node *new_node = calloc(1,sizeof(node));
        list->head = new_node;
        list->tail = new_node;
        new_node->data = data;
        new_node->timestamp = timestamp;
        list->len++;
        new_node -> ok =0;
    }
    
}
void deleteNode(Tlist *list , node* del) {
   if (list->head == NULL || del == NULL) {
      return;
   }    /// checking if the node exists
   if (list->head == del) {
      list->head = del->next;
   }    /// checking if the node that must be deleted is head node
   if (del->next != NULL) {
      (del->next)->prev = del->prev;
   }    /// condition to stay in the list
   if (del->prev != NULL) {
      (del->prev)->next = del->next;
   }    /// condition to stay in the list
   list->len--;
   free(del);
   return;
}
void deleteLast4(Tlist* list)
{
    node *aux, *sterge;

    aux = list->tail->prev->prev->prev->prev;

    sterge = aux->next->next->next->next;
    aux->next->next->next->next = NULL;
    free(sterge);

    sterge = aux->next->next->next;
    aux->next->next->next = NULL;
    free(sterge);

    sterge = aux->next->next;
    aux->next->next = NULL;
    free(sterge);

    sterge = aux->next;
    aux->next = NULL;
    free(sterge);
    
    list->tail = aux;
    aux->next = NULL;
    list->len -- ;
    list->len -- ;
    list->len -- ;
    list->len -- ;
}
void print (Tlist *list)
{
    printf("%d\n",list->len);
    node *aux = list->head;
    while(aux!=NULL)
    {
        printf("%d %0.2lf\n",aux->timestamp,aux->data);
        aux = aux->next;
    }
    
}
void sortare(Tlist *list)
{
    node *aux;
    
    int srt=0;
    
    while(srt==0)
    {
      srt=1;
      aux = list->head;
      node *swap = (node *)calloc(1,sizeof(node));
      while(aux->next!=NULL)
      {
          
        if(aux->data>aux->next->data)
        {   
            swap->data = aux->next->data;
            swap->timestamp = aux->next->timestamp;

            aux->next->data = aux->data;
            aux->next->timestamp = aux->timestamp;
            
            aux->data = swap->data;
            aux->timestamp = swap->timestamp;
            
        srt=0;
        }
        aux = aux->next;
      }
        free(swap);
    }
    
}
void add_at(Tlist *list, int i , int timestamp, double data)
{   
    int j;
    node *aux = calloc(1,sizeof(node)),*temp;
    temp = list->head;
    aux->data = data;
    aux->ok = 0;
    aux->timestamp = timestamp;

    for(j=1 ; j<i ; j++)
    {
        if(temp->next == NULL)break;
        temp = temp->next;
    }   
        aux->next= temp->next;
        temp->next = aux;
    list->len++;

}
void freeList(Tlist *list)
{
   node* tmp;
   while (list->head != NULL)
    {
       tmp = list->head;
       list->head = list->head->next;
       free(tmp);
    }
    
}
