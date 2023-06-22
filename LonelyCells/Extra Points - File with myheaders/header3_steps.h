//#ifndef FINAL_PROJECT_HEADER3_STEPS_H
//#define FINAL_PROJECT_HEADER3_STEPS_H

int move(list *list_c ,list_map *list_m ,int pm ,int num , int cell_num , int n){
    node *current_c = list_c->head, *current_c_t = list_c->head;
    node_map *current_m = list_m->head;
    int i,j,test=0;

    for(i=0 ; i<cell_num ; i++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }
    switch(pm)
    {
        case 1:
        {
            if(!find(current_c->cell->x,current_c->cell->y+1,list_c) && current_c->cell->y+1<n)
            {
                if(!forbidden(current_c->cell->x,current_c->cell->y+1,list_m,n))
                {
                    current_c->cell->y++;
                    return 0;
                } else{
                    printf("Forbidden Block\n");
                    return -1;
                }
            } else
                return -1;
        }
        case 2:
        {
            if(!find(current_c->cell->x,current_c->cell->y-1,list_c) && current_c->cell->y-1>=0)
            {
                if(!forbidden(current_c->cell->x,current_c->cell->y-1,list_m,n))
                {
                    current_c->cell->y--;
                    return 0;
                } else{
                    printf("Forbidden Block\n");
                    return -1;
                }
            }else
                return -1;
        }
        case 3:
        {
            if((current_c->cell->x %2 != 0 && n%2 ==0) || (n%2 !=0 && current_c->cell->x %2 == 0))
            {
                if(!find(current_c->cell->x+1,current_c->cell->y,list_c) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y,list_m,n))
                    {
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            } else{
                if((!find(current_c->cell->x+1,current_c->cell->y+1,list_c) && current_c->cell->y+1<n) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y+1,list_m,n))
                    {
                        current_c->cell->x++;
                        current_c->cell->y++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }
        }
        case 4:
        {
            if((current_c->cell->x %2 != 0 && n%2 ==0) || (n%2 !=0 && current_c->cell->x %2 == 0))
            {
                if(!find(current_c->cell->x-1,current_c->cell->y,list_c) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y,list_m,n))
                    {
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }else{
                if((!find(current_c->cell->x-1,current_c->cell->y+1,list_c) && current_c->cell->y+1<n) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y+1,list_m,n))
                    {
                        current_c->cell->x--;
                        current_c->cell->y++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }
        }
        case 5:
        {
            if((current_c->cell->x %2 != 0 && n%2 ==0) || (n%2 !=0 && current_c->cell->x %2 == 0))
            {
                if((!find(current_c->cell->x+1,current_c->cell->y-1,list_c) && current_c->cell->y-1>=0) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y-1,list_m,n))
                    {
                        current_c->cell->y--;
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }
            else{
                if(!find(current_c->cell->x+1,current_c->cell->y,list_c) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y,list_m,n))
                    {
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }
        }
        case 6:
        {
            if((current_c->cell->x %2 != 0 && n%2 ==0) || (n%2 !=0 && current_c->cell->x %2 == 0))
            {
                if((!find(current_c->cell->x-1,current_c->cell->y-1,list_c) && current_c->cell->y-1>=0) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y-1,list_m,n))
                    {
                        current_c->cell->y--;
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }else{
                if(!find(current_c->cell->x-1,current_c->cell->y,list_c) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y,list_m,n))
                    {
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n");
                        return -1;
                    }
                }else
                    return -1;
            }
        }
        default:
            printf("Invalid Number\n");
            return -1;
    }
}

int split(list *list_c, int x,int y, int num ,list_map *list_m, int turn , int cell_num){
    node *current_c = list_c->head, *current;
    int j;

    for(j=0 ; j<cell_num ; j++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }

    cell* new_cell = (cell*) malloc(sizeof(cell));
    if(!new_cell)
    {
        printf("could not allocate memory\n");
        return -1;
    }
    new_cell->x = current_c->cell->x + x;
    new_cell->y = current_c->cell->y + y;
    new_cell->num = cell_num+1;
    new_cell->energy = 40;
    current_c->cell->energy = 40;
    strcpy(new_cell->name , rand_string(num+1));
    new_cell->belong_to = turn;

    node *new_node = (node *) malloc(sizeof(node));
    if(!new_node)
    {
        printf("could not allocate memory\n");
        return -1;
    }
    new_node->cell = new_cell;
    new_node->next = NULL;

    if(!list_c->head)
    {
        list_c->head = new_node;
        return 0;
    }
    else
    {
        for(current = list_c->head; current->next ;current = current->next);
        current->next = new_node;
    }
    return 0;
}

int split_check(list *list_c,list_map *list_m, int num, int turn , int cell_num, int n){
    node *current_c = list_c->head;
    node_map *current_m = list_m->head;
    int i ;
    char *two="2";

    for(i=0 ; i<cell_num ; i++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if(current_m->map->x == current_c->cell->x  && current_m->map->y == current_c->cell->y)
        {
            if(!strcmp(&current_m->map->trait , two))
            {
                if(current_c->cell->energy >= 80)
                {
                    if((current_c->cell->x+1<n && !find(current_c->cell->x+1,current_c->cell->y,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y,list_m,n))
                    {
                        split(list_c,1,0,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if(((current_c->cell->x+1<n && current_c->cell->y+1<n) && !find(current_c->cell->x+1,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y+1,list_m,n))
                    {
                        split(list_c,1,1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if((current_c->cell->y+1<n && !find(current_c->cell->x,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x,current_c->cell->y+1,list_m,n))
                    {
                        split(list_c,0,1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if(((current_c->cell->x+1<n && current_c->cell->y-1>=0) && !find(current_c->cell->x+1,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y-1,list_m,n))
                    {
                        split(list_c,1,-1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if((current_c->cell->y-1>=0 && !find(current_c->cell->x,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x,current_c->cell->y-1,list_m,n))
                    {
                        split(list_c,0,-1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if((current_c->cell->x-1>=0 && !find(current_c->cell->x-1,current_c->cell->y,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y,list_m,n))
                    {
                        split(list_c,-1,0,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if(((current_c->cell->x-1>=0 && current_c->cell->y+1<n) && !find(current_c->cell->x-1,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y+1,list_m,n))
                    {
                        split(list_c,-1,1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    if(((current_c->cell->x-1>=0 && current_c->cell->y-1>=0) && !find(current_c->cell->x-1,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y-1,list_m,n))
                    {
                        split(list_c,-1,-1,num,list_m,turn, cell_num);
                        return 0;
                    }
                    else
                    {
                        printf("Not Enough Space\n");
                        return -1;
                    }
                } else
                {
                    printf("Not Enough Energy\n");
                    return -1;
                }
            } else
            {
                printf("Not in the Mitosis Block\n");
                return -1;
            }
        }
    }
}

void boost(list *list_c, list_map *list_m, int num, int cell_num ,int n ,int row, int cell_num1 ,int cell_num2){
    node *current_c = list_c->head;
    node_map *current_m = list_m->head;
    int i ,test;
    char *one="1";

    for(i=0 ; i<cell_num ; i++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if (current_m->map->x == current_c->cell->x && current_m->map->y == current_c->cell->y)
        {
            if (!strcmp(&current_m->map->trait, one))
            {
                if(current_m->map->energy != 0)
                {
                    if(current_m->map->energy <15 && current_m->map->energy >0)
                    {
                        if(current_c->cell->energy >85)
                        {
                            test = fminf(100 - current_c->cell->energy , current_m->map->energy);
                            current_c->cell->energy += test;
                            current_m->map->energy -= test;
                        }else{
                            current_c->cell->energy += current_m->map->energy;
                            current_m->map->energy = 0;
                        }
                    }else{
                        if(current_c->cell->energy >85)
                        {
                            current_m->map->energy -= 100 - current_c->cell->energy;
                            current_c->cell->energy = 100;
                        }else{
                            current_c->cell->energy += 15;
                            current_m->map->energy -= 15;
                        }
                    }
                    show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
                } else
                    printf("Doesn't Have Any Energy\n");
            } else
                printf("Not in the Energy Block\n");
        }
    }
}

//#endif FINAL_PROJECT_HEADER3_STEPS_H
