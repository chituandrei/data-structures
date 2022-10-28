typedef struct graph {
    int nr_nodes; //numarul de noduri din graf
    struct node** neighbours; // reprezentarea pe liste de adiacenta
    int *visited;   // vectorul visited pentru a verifica daca un nod a fost sau nu verificat
} graph;

typedef struct node {
    int depozit; // daca valoarea este 1 inseamna ca nodul din graf este depozit
    int y;  // valoarea nodului adiacent
    float cost; // costul de a ajunge la y
    struct node* next; // urmatorul node
} node;

struct node* createNode(int x,float cost) {
    struct node* new_node = malloc(sizeof(struct node)); // aloc memorie pentru urmatorul elemnt din lista i
    new_node->y = x;
    new_node->cost = cost;
    new_node->next = NULL;
    return new_node; // returnez nodul alocat 
}

struct graph* createGraph(int nodes_number){
    struct graph* new_graph = malloc(sizeof(struct graph)); 
    new_graph->nr_nodes = nodes_number;  
    new_graph->neighbours = malloc(nodes_number * sizeof(struct node*));
    new_graph->visited = calloc(nodes_number , sizeof(int));

    int i;
    for(i = 0; i < nodes_number; i++)
        new_graph->neighbours[i] = NULL;
    
    return new_graph;
}

void addGraphEdge(struct graph* graph, int n1, int n2,float val){
    struct node* new_node = createNode(n2,val); // memoria alocata si intializarea pentru noul nod
    new_node->depozit = 0; // initializez nodurile ca nefiind depozite
    new_node->next = graph->neighbours[n1]; // adauga la lista lui n1 (la inceput)
    graph->neighbours[n1] = new_node; 
}

void freeGraph(struct graph* Graf){
    int i;
    for(i = 0; i < Graf->nr_nodes; i++)
        {
            node* aux1,*aux2;
            aux1 = Graf->neighbours[i];
            aux2 = aux1;

            while(aux1!=NULL)
            {
                aux1 = aux1->next;
                free(aux2);
                aux2 = aux1;
            }
        }
    free(Graf->visited);
    free(Graf->neighbours);    
    free(Graf);
}
float** buildGraphMatrix (graph* Graf){ // functie de transformarea a grafului din liste de adiacenta in Matrice
    float **matrix = malloc(Graf->nr_nodes * sizeof(float *)); // aloc memorie pentru matrice
    int i,j;

    for(i = 0; i < Graf->nr_nodes; i++)
        *(matrix+i) = malloc(Graf->nr_nodes * sizeof(float));   
    
    for(i = 0; i < Graf->nr_nodes; i++){
        for(j = 0; j < Graf->nr_nodes; j++)
            matrix[i][j] = -1;  // initializez toate elementele cu -1
    }

    
    for(i = 0 ; i < Graf->nr_nodes; i++)
        {
            node *temp = Graf->neighbours[i];

            while(temp != NULL){
                matrix[i][temp->y] = temp->cost; // copiez costurile in matrice
                temp = temp->next;
            }
        }
     
        return matrix;    
}   
void freeGraphMatrix(float **matrix,int nr_nodes){ // dezalocarea memoriei pentru matrice
    int i;
    for (i = 0 ; i < nr_nodes; i++)
        free(matrix[i]);
    free(matrix);
}
typedef struct Queue {
struct node_queue *head, *tail;
int len;
} Queue;

typedef struct node_queue {
int data;
unsigned long long mask;
struct node_queue *next;
} node_queue;

void init_queue (Queue **q)
{
    (*q) = calloc(1,sizeof(Queue));
    (*q)->head = NULL;
    (*q)->tail = NULL;
    (*q)->len = 0;
}

void free_queue (Queue **q)
{
    node_queue *aux,*sters;
    aux = (*q)->head;
    
    while(aux != NULL)
    {   sters = aux;
        aux = aux->next;
        free(sters);
    }
    
}

int add_queue (Queue *q, int val,unsigned long long mask)
{
   node_queue *newNode = calloc(1,sizeof(node_queue));   

   newNode->data = val;
   newNode->mask = mask;
   if(q->head == NULL)
        {
            q->head = q->tail = newNode;
            q->len ++;
        }
   
   else{
         q->tail->next = newNode;
         q->tail = newNode;
         q->tail->next = NULL;
         q->len++;
        }
    
}
void pop_queue(Queue *q)
{
    node_queue *aux;
    aux = q->head;  //copiez head ul 
    q->head = q->head->next; // actualizez head ul
    free(aux); // eliberez memoria pentru head
    q->len--;  // lungimea scade(am eliminat un elemnt)
}
int front_val (Queue *q)
{
    return q->head->data; 
}

unsigned long long front_mask (Queue *q)
{
    return q->head->mask;
}

int is_empty_queue(Queue *q)
{
    if(q->len == 0)
        return 1;
    else return 0;
}

typedef struct vizitat{
    int val;
    unsigned long long mask;
}vizitat;

typedef struct distante{
    float val;
    unsigned long long mask;
}distante;

void add_viz(vizitat *viz,int val,int mask,int lviz){ // functia care adauga la vectorul de viz nodul si masca sa

    viz[lviz].val = val;
    viz[lviz].mask = mask;
}

int find_viz(vizitat *viz,int val,int mask,int lviz){  // verifica daca un nod cu o anumita masca a fost vizitat

    int i;

    for(i = 0; i < lviz; i++)
        if(viz[i].val == val && viz[i].mask == mask)
            return 1;

    return 0;
}