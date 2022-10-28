// 2 lists with left , right
// function to calculete C
// function to calculate F
// function add_at in list

double C (int timestamp,double left,double right)
{
    double data;
    data = (timestamp - left)/(right-left);
    return data;
}

double w(double i, double k)
{
    double j;

    double numarator = 0, numitor = 0;

    numarator = (i/(k-1))*(i/(k-1))*0.9+0.1;    
    
    for(j = 0 ;j < k; j++)
        numitor += (j/(k-1))*(j/(k-1))*0.9+0.1;
    
    return numarator/numitor;
}

void completeaza(Tlist *list)
{
    
    int poz=0,left1,left2,left3,right1,right2,right3;
    double w1,w2,w3,dl1,dl2,dl3,dr1,dr2,dr3;

    node* parcurge ;
    node* aux;

    w1 = w(0,3);
    w2 = w(1,3);
    w3 = w(2,3);

    parcurge = list->head->next->next;
    poz = 3;

    while(parcurge->next->next->next != NULL)
    {
        
        aux = parcurge;
          if(parcurge->next->timestamp - parcurge->timestamp >= 1000)
        {
            
            left3 = parcurge->timestamp;
            dl3 = parcurge->data;
            dl2 = parcurge->prev->data;
            dl1 = parcurge->prev->prev->data;
            right3 = parcurge->next->timestamp;
            dr3 = parcurge->next->data;
            dr2 = parcurge->next->next->data;
            dr1 = parcurge->next->next->next->data;
            
            
            while(aux->timestamp+200 < aux->next->timestamp)
            {
                double data,c;  

                c = C(aux->timestamp+200,left3,right3);

                data = (1-c) * (dl1*w1 + dl2*w2 + dl3*w3) + c * (dr1 * w1 + dr2 * w2 + dr3 * w3);
                add_at(list,poz,aux->timestamp+200,data);
                poz++;
                aux = aux->next;
            }
            
        }
        parcurge = aux->next;
        poz++;
    }
}
