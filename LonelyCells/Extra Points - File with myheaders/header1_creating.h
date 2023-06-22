//#ifndef FINAL_PROJECT_HEADER4_CREATING_H
//#define FINAL_PROJECT_HEADER4_CREATING_H

typedef struct {
    int x,y;
    int energy;
    char trait;
}map;
typedef struct {
    int x,y,num;
    char name[50];
    int energy;
    bool belong_to;
}cell;

typedef struct n_node{
    cell *cell;
    struct n_node *next;
}node;
typedef struct node_m{
    map *map;
    struct node_m *next;
}node_map;

typedef struct {
    node_map *head;
}list_map;
typedef struct n_list{
    node *head;
}list;

int new_list (list *n_list){
    n_list->head = NULL;
}
int new_list_map (list_map *n_list){
    n_list->head = NULL;
}

int find(int xx, int yy, list *list_c){
    node *current = list_c->head;

    if(current->cell->x == xx && current->cell->y == yy)
        return 1;

    while (current->next)
    {
        if(current->cell->x == xx && current->cell->y == yy)
            return 1;

        current = current->next;
    }
    if(current->cell->x == xx && current->cell->y == yy)
        return 1;

    return 0;
}

int forbidden(int xx, int yy, list_map *list_m , int n){
    node_map *current_m = list_m->head;
    int i;
    char *three = "3";

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if(yy == current_m->map->y && xx == current_m->map->x)
            if(!strcmp(&current_m->map->trait , three))
                return 1;
    }

    return 0;
}

int check_turns(list *list_c,int turn,int num , int cell_num){
    int test;
    node *current = list_c->head;
    int i;

    if(num > cell_num)
        return 0;

    for(i=0 ; i<num-1 ; i++ , current = current->next);

    if(current->cell->belong_to == turn)
        return 1;
    else
        return 0;
}

char *rand_string(size_t size){
    srand(time(NULL));
    char *str = malloc((size + 1) * sizeof(char));
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    for (size_t i = 0; i < size; i++)
    {
        int key = rand() % (sizeof(charset) / sizeof(char) - 1);
        str[i] = charset[key];
    }
    str[size] = '\0';
    return str;
}

void make_new_cell (list *n_list ,list_map *list_m ,cell *new_cell, int cell_num1 , int cell_num2 , int n){
    static int i=1 , iter1=0 ;
    int xx,yy;

    srand(time(NULL));
    if(!n_list->head)
    {
        do{
            xx = rand()% n;
            yy = rand()% n;
        }while(forbidden(xx,yy,list_m,n));

    }else
        do{
            xx = rand()% n;
            yy = rand()% n;
        }while(find(xx,yy,n_list) || forbidden(xx,yy,list_m,n));

    new_cell->x = xx;
    new_cell->y = yy;
    strcpy(new_cell->name,rand_string(i));
    new_cell->num = i++;
    new_cell->energy = 0;

    if(cell_num1 && cell_num2)
    {
        if(iter1 < cell_num1)
        {
            new_cell->belong_to = 0;
            iter1++;
        } else
            new_cell->belong_to = 1;
    } else
        new_cell->belong_to = 0;
}

int first_add ( list *n_list, list_map *list_m, cell *new_cell){
    node *current;

    node *new_node = (node *) malloc(sizeof(node));
    if(!new_node)
    {
        printf("could not allocate memory\n");
        return -1;
    }

    new_node->cell = new_cell;
    new_node->next = NULL;

    if(!n_list->head)
    {
        n_list->head = new_node;
        return 0;
    }
    else
    {
        for(current = n_list->head; current->next ;current = current->next);
        current->next = new_node;
    }
    return 0;
}

void make_new_blocks (map *new_block , char block , int n){
    static int i=0 , j=0;

    new_block->trait = block;
    new_block->energy = 100;

    new_block->x = j;
    new_block->y = i;
    if(j != n-1)
        j++;
    else{
        i++;
        j=0;
    }
}

int first_add_blocks (list_map *n_list, map *new_block,list *list_c){
    node_map *current;
    node_map *new_node = (node_map *) malloc(sizeof(node_map));
    if(!new_node)
    {
        printf("could not allocate memory\n");
        return -1;
    }

    new_node->map = new_block;
    new_node->next = n_list->head;
    n_list->head = new_node;

    return 0;
}

//#endif FINAL_PROJECT_HEADER4_CREATING_H
