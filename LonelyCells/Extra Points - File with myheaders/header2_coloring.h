//#ifndef FINAL_PROJECT_HEADER1_H
//#define FINAL_PROJECT_HEADER1_H

void move_toxy(int x,int y){
    COORD coord = { x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void setcolor(WORD color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    return;
}
void setcolor_background_text(int ForeGroundColor,int BackGroundColor){
    int color=16*BackGroundColor+ForeGroundColor;
    setcolor(color);
}

void show_map (list *list_c,list_map *list_m , int n , int cell_num , int cell_num1 , int cell_num2, int row){
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
        }
    }

    printf("\n\n");

    printf("\n");

    for(current_c = list_c->head, k=0; k<cell_num ;k++ , current_c = current_c->next)
    {
        if((cell_num1 && cell_num2) && current_c->cell->belong_to)
            printf("Player 2 Cells\t");
        else
        if((cell_num1 && cell_num2) && !current_c->cell->belong_to)
            printf("Player 1 Cells\t");

        printf("[ %d ]  %s  ( %d , %d )\tEnergy = %d\n",current_c->cell->num,current_c->cell->name,current_c->cell->x,current_c->cell->y,current_c->cell->energy);
    }

    char *one = "1", *two = "2", *three = "3";
    printf("\nBlocks\n");
    for(current_m = list_m->head, k=0; k<n*n ;k++ , current_m = current_m->next)
    {
        if(!strcmp(&current_m->map->trait , one))
            printf("( %d , %d )\tEnergy Cell\tEnergy = %d\n",current_m->map->x,current_m->map->y,current_m->map->energy);
        else
        if(!strcmp(&current_m->map->trait , two))
            printf("( %d , %d )\tMitosis Cell\n",current_m->map->x,current_m->map->y);
        else
        if(!strcmp(&current_m->map->trait , three))
            printf("( %d , %d )\tForbidden Cell\n",current_m->map->x,current_m->map->y);
        else
            printf("( %d , %d )\tNormal Cell\n",current_m->map->x,current_m->map->y);
    }

    printf("\n");
}

//#endif FINAL_PROJECT_HEADER1_H
