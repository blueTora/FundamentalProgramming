#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <zconf.h>
#include <windows.h>
#include <dos.h>
#include <dir.h>
#include <string.h>
#include <stdbool.h>

int n, cell_num, cell_num1, cell_num2, row=0 ,loaded = 0;

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

void move_toxy(int x,int y){
    COORD coord = { x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
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

void setcolor(WORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}
void setcolor_background_text(int ForeGroundColor,int BackGroundColor){
    int color=16*BackGroundColor+ForeGroundColor;
    setcolor(color);
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

int forbidden(int xx, int yy, list_map *list_m){
    node_map *current_m = list_m->head;
    int i;

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if(yy == current_m->map->y && xx == current_m->map->x)
            if(current_m->map->trait == '3')
                return 1;
    }

    return 0;
}

void show_map (list *list_c,list_map *list_m){
    int x , y , color=1, k, test , base_color = 6;
    node *current_c = list_c->head;
    node_map *current_m = list_m->head;
    if(n%6 == 0)
        base_color = 5;

    for(int i=1+row ; i<=n+row ; i++)
    {
        x = 6*n,y = 3*i;
        for(int j=1; j<=n/2 ;j++)
        {
            if(color == base_color)
                color = 1;
            else
                color++;

            setcolor_background_text(0,color);
            move_toxy(x,y);
            printf("      ");

            move_toxy(x,++y);
            for(k=0,current_c = list_c->head ,test=0 ; k<cell_num ;k++ , current_c = current_c->next)
            {
                if(current_c->cell->x == current_m->map->x && current_c->cell->y == current_m->map->y)
                {
                    test++;
                    break;
                }
            }
            if(test != 0)
            {
                if(current_c->cell->num>0 && current_c->cell->num<10)
                    printf("  0%d  ",current_c->cell->num);
                else
                    printf("  %d  ",current_c->cell->num);
            }
            else
                printf("      ");

            move_toxy(x,++y);
            printf("      ");

            current_m = current_m->next;
            x -= 6, y -= 3;

            if(color == base_color)
                color = 1;
            else
                color++;

            setcolor_background_text(0,color);
            move_toxy(x,y);
            printf("      ");

            move_toxy(x,++y);
            for(k=0,current_c = list_c->head ,test=0 ; k<cell_num ;k++ , current_c = current_c->next)
            {
                if(current_c->cell->x == current_m->map->x && current_c->cell->y == current_m->map->y)
                {
                    test++;
                    break;
                }
            }
            if(test != 0)
            {
                if(current_c->cell->num>0 && current_c->cell->num<10)
                    printf("  0%d  ",current_c->cell->num);
                else
                    printf("  %d  ",current_c->cell->num);
            }
            else
                printf("      ");

            move_toxy(x,++y);
            printf("      ");

            current_m = current_m->next;
            x -= 6, y = 3*i;
        }
        if(n%2 != 0)
        {
            if(color == base_color)
                color = 1;
            else
                color++;

            setcolor_background_text(0,color);
            move_toxy(x,y);
            printf("      ");

            move_toxy(x,++y);
            for(k=0,current_c = list_c->head ,test=0 ; k<cell_num ;k++ , current_c = current_c->next)
            {
                if(current_c->cell->x == current_m->map->x && current_c->cell->y == current_m->map->y)
                {
                    test++;
                    break;
                }
            }
            if(test != 0)
            {
                if(current_c->cell->num>0 && current_c->cell->num<10)
                    printf("  0%d  ",current_c->cell->num);
                else
                    printf("  %d  ",current_c->cell->num);
            }
            else
                printf("      ");

            move_toxy(x,++y);
            printf("      ");

            current_m = current_m->next;
            x -= 6, y = 3*i;
        }
    }

    printf("\n\n");

    printf("\n");

    printf("\nCells\n");
    for(current_c = list_c->head, k=0; k<cell_num ;k++ , current_c = current_c->next)
    {
        if((cell_num1 && cell_num2) && current_c->cell->belong_to)
            printf("Player 2 Cells\t");
        else
        if((cell_num1 && cell_num2) && !current_c->cell->belong_to)
            printf("Player 1 Cells\t");

        printf("[ %d ]  %s  ( %d , %d )\tEnergy = %d\n",current_c->cell->num,current_c->cell->name,current_c->cell->x,current_c->cell->y,current_c->cell->energy);
    }

    printf("\nBlocks\n");
    for(current_m = list_m->head, k=0; k<n*n ;k++ , current_m = current_m->next)
    {
        if(current_m->map->trait == '1')
            printf("( %d , %d )\tEnergy Cell\tEnergy = %d\n",current_m->map->x,current_m->map->y,current_m->map->energy);
        else
        if(current_m->map->trait == '2')
            printf("( %d , %d )\tMitosis Cell\n",current_m->map->x,current_m->map->y);
        else
        if(current_m->map->trait == '3')
            printf("( %d , %d )\tForbidden Cell\n",current_m->map->x,current_m->map->y);
        else
            printf("( %d , %d )\tNormal Cell\n",current_m->map->x,current_m->map->y);
    }

    printf("\n");
    row += 4+cell_num+n*n+5;
}

void make_new_cell (list *n_list ,list_map *list_m ,cell *new_cell){
    static int i=1 , iter1=0 ;
    int xx,yy;

    srand(time(NULL));
    if(!n_list->head)
    {
        do{
            xx = rand()% n;
            yy = rand()% n;
        }while(forbidden(xx,yy,list_m));

    }else
        do{
            xx = rand()% n;
            yy = rand()% n;
        }while(find(xx,yy,n_list) || forbidden(xx,yy,list_m));

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

void make_new_blocks (map *new_block , char block){
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

int move(list *list_c ,list_map *list_m ,int pm ,int num){
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
                if(!forbidden(current_c->cell->x,current_c->cell->y+1,list_m))
                {
                    current_c->cell->y++;
                    return 0;
                } else{
                    printf("Forbidden Block\n",row += 1);
                    return -1;
                }
            } else
                return -1;
        }
        case 2:
        {
            if(!find(current_c->cell->x,current_c->cell->y-1,list_c) && current_c->cell->y-1>=0)
            {
                if(!forbidden(current_c->cell->x,current_c->cell->y-1,list_m))
                {
                    current_c->cell->y--;
                    return 0;
                } else{
                    printf("Forbidden Block\n",row += 1);
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
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y,list_m))
                    {
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
                        return -1;
                    }
                }else
                    return -1;
            } else{
                if((!find(current_c->cell->x+1,current_c->cell->y+1,list_c) && current_c->cell->y+1<n) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y+1,list_m))
                    {
                        current_c->cell->x++;
                        current_c->cell->y++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
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
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y,list_m))
                    {
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
                        return -1;
                    }
                }else
                    return -1;
            }else{
                if((!find(current_c->cell->x-1,current_c->cell->y+1,list_c) && current_c->cell->y+1<n) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y+1,list_m))
                    {
                        current_c->cell->x--;
                        current_c->cell->y++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
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
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y-1,list_m))
                    {
                        current_c->cell->y--;
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
                        return -1;
                    }
                }else
                    return -1;
            }
            else{
                if(!find(current_c->cell->x+1,current_c->cell->y,list_c) && current_c->cell->x+1<n)
                {
                    if(!forbidden(current_c->cell->x+1,current_c->cell->y,list_m))
                    {
                        current_c->cell->x++;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
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
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y-1,list_m))
                    {
                        current_c->cell->y--;
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
                        return -1;
                    }
                }else
                    return -1;
            }else{
                if(!find(current_c->cell->x-1,current_c->cell->y,list_c) && current_c->cell->x-1>=0)
                {
                    if(!forbidden(current_c->cell->x-1,current_c->cell->y,list_m))
                    {
                        current_c->cell->x--;
                        return 0;
                    }else{
                        printf("Forbidden Block\n",row += 1);
                        return -1;
                    }
                }else
                    return -1;
            }
        }
        default:
            printf("Invalid Number\n", row += 1);
            return -1;
    }
}

int split(list *list_c, int x,int y, int num ,list_map *list_m, int turn){
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

    cell_num++;
    if(cell_num2 && cell_num1)
    {
        if(turn)
            cell_num2++;
        else
            cell_num1++;
    }
    show_map(list_c,list_m);
    return 0;
}

void split_check(list *list_c,list_map *list_m, int num, int turn){
    node *current_c = list_c->head;
    node_map *current_m = list_m->head;
    int i ;

    for(i=0 ; i<cell_num ; i++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if(current_m->map->x == current_c->cell->x  && current_m->map->y == current_c->cell->y)
        {
            if(current_m->map->trait == '2')
            {
                if(current_c->cell->energy >= 80)
                {
                    if((current_c->cell->x+1<n && !find(current_c->cell->x+1,current_c->cell->y,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y,list_m))
                        split(list_c,1,0,num,list_m,turn);
                    else
                    if(((current_c->cell->x+1<n && current_c->cell->y+1<n) && !find(current_c->cell->x+1,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y+1,list_m))
                        split(list_c,1,1,num,list_m,turn);
                    else
                    if((current_c->cell->y+1<n && !find(current_c->cell->x,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x,current_c->cell->y+1,list_m))
                        split(list_c,0,1,num,list_m,turn);
                    else
                    if(((current_c->cell->x+1<n && current_c->cell->y-1>=0) && !find(current_c->cell->x+1,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x+1,current_c->cell->y-1,list_m))
                        split(list_c,1,-1,num,list_m,turn);
                    else
                    if((current_c->cell->y-1>=0 && !find(current_c->cell->x,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x,current_c->cell->y-1,list_m))

                        split(list_c,0,-1,num,list_m,turn);
                    else
                    if((current_c->cell->x-1>=0 && !find(current_c->cell->x-1,current_c->cell->y,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y,list_m))
                        split(list_c,-1,0,num,list_m,turn);
                    else
                    if(((current_c->cell->x-1>=0 && current_c->cell->y+1<n) && !find(current_c->cell->x-1,current_c->cell->y+1,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y+1,list_m))
                        split(list_c,-1,1,num,list_m,turn);
                    else
                    if(((current_c->cell->x-1>=0 && current_c->cell->y-1>=0) && !find(current_c->cell->x-1,current_c->cell->y-1,list_c)) && !forbidden(current_c->cell->x-1,current_c->cell->y-1,list_m))
                        split(list_c,-1,-1,num,list_m,turn);
                    else
                        printf("Not Enough Space\n",row +=1);
                } else
                    printf("Not Enough Energy\n",row += 1);
            } else
                printf("Not in the Mitosis Block\n",row += 1);
        }
    }
}

void boost(list *list_c, list_map *list_m, int num){
    node *current_c = list_c->head;
    node_map *current_m = list_m->head;
    int i ,test;

    for(i=0 ; i<cell_num ; i++ , current_c = current_c->next)
    {
        if(current_c->cell->num == num)
            break;
    }

    for(i=0 ; i<n*n ; i++ , current_m = current_m->next)
    {
        if (current_m->map->x == current_c->cell->x && current_m->map->y == current_c->cell->y)
        {
            if (current_m->map->trait == '1')
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
                    show_map(list_c,list_m);
                } else
                    printf("Doesn't Have Any Energy\n",row += 1);
            } else
                printf("Not in the Energy Block\n",row += 1);
        }
    }
}

int check_turns(list *list_c,int turn,int num){
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

int main() {
    int first_step=0, player_move , step, num ;
    char file_name[100];
    FILE *input;

    printf("[1]Load\n[2]New single player game\n[3]New Multiplayer game\n[4]Exit\n");
    scanf("%d",&first_step);
    row += 5;

    list *list_c = (list*) malloc(sizeof(list));
    list_map *list_m = (list_map*) malloc(sizeof(list_map));
    new_list(list_c);
    new_list_map(list_m);

    if(first_step == 1)
    {
        FILE *input_m, *input_c;

        input_m = fopen("D:\\save_map.bin","rb");
        if(!input_m)
        {
            printf("Can not Open the Map File\n");
            sleep(5);
            return -1;
        }

        fread(&n, sizeof(int),1,input_m);

        for(int i=0; i<n*n ;i++)
        {
            int temp;
            map *new_block = (map*) malloc(sizeof(map));
            if(!new_block)
            {
                printf("could not allocate memory\n");
                sleep(5);
                return -1;
            }

            temp = fread(new_block, sizeof(map),1,input_m);
            if(temp<1)
            {
                printf("Error\nNot Enough Input\n");
                sleep(5);
                return -1;
            }

            temp = first_add_blocks(list_m,new_block,list_c);
            if(temp)
            {
                printf("could not allocate memory\n");
                sleep(5);
                return -1;
            }
        }

        fclose(input_m);

        input_c = fopen("D:\\save_cells.bin","rb");
        if(!input_c)
        {
            printf("Can not Open the Cells File\n");
            sleep(5);
            return -1;
        }

        fread(&first_step, sizeof(int), 1, input_c);

        if(first_step == 2)
            fread(&cell_num, sizeof(int),1,input_c);
        else{
            fread(&cell_num1, sizeof(int),1,input_c);
            fread(&cell_num2, sizeof(int),1,input_c);
            cell_num = cell_num1 + cell_num2;
        }

        for(int i=0; i<cell_num ;i++)
        {
            int temp;

            cell *new_cell = (cell*) malloc(sizeof(cell));
            if(!new_cell)
            {
                printf("could not allocate memory\n");
                sleep(5);
                return -1;
            }

            temp = fread(new_cell, sizeof(cell),1,input_c);
            if(temp<1)
            {
                printf("Error\nNot Enough Input\n");
                sleep(5);
                return -1;
            }

            temp = first_add(list_c,list_m,new_cell);
            if(temp)
            {
                printf("could not allocate memory\n");
                sleep(5);
                return -1;
            }
        }

        fclose(input_c);

        show_map(list_c,list_m);

        loaded++;

    }

    if(first_step == 2)
    {
        if(!loaded)
        {
            printf("Enter the Name of Map File\n");
            scanf("%s",file_name);
            //C:\\map.bin
            //strcpy(file_name,"C:\\map.bin");

            input = fopen(file_name,"rb");
            if(!input)
            {
                printf("Can not Open the File\n");
                sleep(5);
                return -1;
            }

            printf("Enter the Number of Cells\n");
            scanf("%d",&cell_num);

            fread(&n, sizeof(int),1,input);
            char blk;
            row += 4;

            for(int i=0; i<n*n ;i++)
            {
                int temp;
                map *new_block = (map*) malloc(sizeof(map));
                if(!new_block)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }

                temp = fread(&blk, sizeof(char),1,input);

                if(temp<1)
                {
                    printf("Error\nNot Enough Input\n");
                    sleep(5);
                    return -1;
                }

                make_new_blocks(new_block,blk);

                temp = first_add_blocks(list_m,new_block,list_c);
                if(temp)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }
            }

            for(int i=0; i<cell_num ;i++)
            {
                cell *new_cell = (cell*) malloc(sizeof(cell));
                if(!new_cell)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }

                make_new_cell(list_c,list_m,new_cell);

                int temp;
                temp = first_add(list_c,list_m,new_cell);
                if(temp)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }
            }

            fclose(input);

            show_map(list_c,list_m);

        }
        do{
            printf("\nPlease choose one of your cells\nWrite it's Number:\n");
            scanf("%d",&num);

            while(num>cell_num || num<1)
            {
                printf("Wrong Number\nChose Another Cell\n");
                scanf("%d",&num);
                row += 3;
            }

            printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
            scanf("%d",&step);
            row += 7;

            if(step == 1)
            {
                int test_m;

                do{
                    printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n");
                    scanf("%d",&player_move);
                    row += 7;

                    test_m = move(list_c,list_m,player_move,num);
                    if(test_m)
                        printf("\nNot Possible\nChose another Direction\n",row += 3);

                }while (test_m);

                show_map(list_c,list_m);

            }else
            if(step == 2)
            {
                split_check(list_c,list_m,num,0);
            }else
            if(step == 3)
            {
                boost(list_c,list_m,num);
            }else
            if(step == 4)
            {
                node_map *current_m = list_m->head;
                node *current_c = list_c->head;
                FILE *save_m,*save_c;
                int k,l;

                save_m = fopen("D:\\save_map.bin","wb");
                if(!save_m)
                {
                    printf("Can't Create the Map File\n");
                    sleep(5);
                    return -1;
                }

                fwrite(&n, sizeof(int),1,save_m);

                for(k=n*n; k>0 ;k--)
                {
                    for(l=1 , current_m = list_m->head; l<k ;l++ , current_m = current_m->next);
                    fwrite(current_m->map,sizeof(map),1,save_m);
                }

                fclose(save_m);

                save_c = fopen("D:\\save_cells.bin","wb");
                if(!save_c)
                {
                    printf("Can't Create the Cells File\n");
                    sleep(5);
                    return -1;
                }

                fwrite(&first_step, sizeof(int), 1, save_c);
                fwrite(&cell_num, sizeof(int),1,save_c);

                for(k=0; k<cell_num ;k++ , current_c = current_c->next)
                    fwrite(current_c->cell, sizeof(cell),1,save_c);

                fclose(save_c);

            }else
            if(step == 5)
            {
                free(list_c);
                free(list_m);
                return 0;
            }
            else
            {
                printf("Invalid Number\n");
                sleep(5);
                return -1;
            }

        }while(step != 5);

    }

    if(first_step == 3)
    {
        if(!loaded)
        {
            printf("Enter the Name of Map File\n");
            scanf("%s",file_name);
            //C:\\map.bin
            //strcpy(file_name,"C:\\map.bin");

            input = fopen(file_name,"rb");
            if(!input)
            {
                printf("Can not Open the File\n");
                sleep(5);
                return -1;
            }

            printf("Enter the Number of Cells for Player 1\n");
            scanf("%d",&cell_num1);
            printf("Enter the Number of Cells for Player 2\n");
            scanf("%d",&cell_num2);
            cell_num = cell_num1 + cell_num2;
            row += 6;

            fread(&n, sizeof(int),1,input);
            char blk;

            for(int i=0; i<n*n ;i++)
            {
                int temp;
                map *new_block = (map*) malloc(sizeof(map));
                if(!new_block)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }

                temp = fread(&blk, sizeof(char),1,input);
                if(temp<1)
                {
                    printf("Error\nNot Enough Input\n");
                    sleep(5);
                    return -1;
                }

                make_new_blocks(new_block,blk);

                temp = first_add_blocks(list_m,new_block,list_c);
                if(temp)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }
            }

            for(int i=0; i<cell_num ;i++)
            {
                cell *new_cell = (cell*) malloc(sizeof(cell));
                if(!new_cell)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }

                make_new_cell(list_c,list_m,new_cell);

                int temp;
                temp = first_add(list_c,list_m,new_cell);
                if(temp)
                {
                    printf("could not allocate memory\n");
                    sleep(5);
                    return -1;
                }
            }

            fclose(input);

            show_map(list_c,list_m);
        }

        int turn=0;
        do{
            if(!turn)
            {
                printf("\nPlayer 1 Turn\nPlease choose one of your cells\nWrite it's Number:\n");
                scanf("%d",&num);

                while(!check_turns(list_c,turn,num))
                {
                    printf("Wrong\nThis Cell Does Not Belong to You\nChose Another Cell\n");
                    scanf("%d",&num);
                    row += 4;
                }

                turn = 1;
            } else{
                printf("\nPlayer 2 Turn\nPlease choose one of your cells\nWrite it's Number:\n");
                scanf("%d",&num);

                while(!check_turns(list_c,turn,num))
                {
                    printf("Wrong\nThis Cell Does Not Belong to You\nChose Another Cell\n");
                    scanf("%d",&num);
                    row += 4;
                }

                turn = 0;
            }

            printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
            scanf("%d",&step);
            row += 10;

            if(step == 1)
            {
                int test_m;

                do{
                    printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n");
                    scanf("%d",&player_move);
                    row += 7;

                    test_m = move(list_c,list_m,player_move,num);
                    if(test_m)
                        printf("\nNot Possible\nChose another Direction\n",row += 3);

                }while (test_m);

                show_map(list_c,list_m);

            }else
            if(step == 2)
            {
                int t;
                t = turn ? 0 : 1;
                split_check(list_c,list_m,num,t);
            }else
            if(step == 3)
            {
                boost(list_c,list_m,num);
            }else
            if(step == 4)
            {
                node_map *current_m = list_m->head;
                node *current_c = list_c->head;
                FILE *save_m,*save_c;
                int k,l;

                save_m = fopen("D:\\save_map.bin","wb");
                if(!save_m)
                {
                    printf("Can't Create the Map File\n");
                    sleep(5);
                    return -1;
                }

                fwrite(&n, sizeof(int),1,save_m);

                for(k=n*n; k>0 ;k--)
                {
                    for(l=1 , current_m = list_m->head; l<k ;l++ , current_m = current_m->next);
                    fwrite(current_m->map,sizeof(map),1,save_m);
                }

                fclose(save_m);

                save_c = fopen("D:\\save_cells.bin","wb");
                if(!save_c)
                {
                    printf("Can't Create the Cells File\n");
                    sleep(5);
                    return -1;
                }

                fwrite(&first_step, sizeof(int), 1, save_c);
                fwrite(&cell_num1, sizeof(int),1,save_c);
                fwrite(&cell_num2, sizeof(int),1,save_c);

                for(k=0; k<cell_num ;k++ , current_c = current_c->next)
                    fwrite(current_c->cell, sizeof(cell),1,save_c);

                fclose(save_c);

                turn = turn ? 0 : 1;
            }else
            if(step == 5)
            {
                free(list_c);
                free(list_m);
                return 0;
            }
            else
            {
                printf("Invalid Number\n");
                sleep(5);
                return -1;
            }

        }while(step != 5);

    }

    return 0;
}