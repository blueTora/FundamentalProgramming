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

#include "header1_creating.h"
#include "header2_coloring.h"
#include "header3_steps.h"

int n, cell_num, cell_num1, cell_num2, row=0 ,loaded = 0;

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

        show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
        row += 4+cell_num+n*n+5;

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

                make_new_blocks(new_block,blk,n);

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

                make_new_cell(list_c,list_m,new_cell,cell_num1,cell_num2,n);

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

            show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
            row += 4+cell_num+n*n+5;
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

                    test_m = move(list_c,list_m,player_move,num,cell_num,n);
                    if(test_m)
                        printf("\nNot Possible\nChose another Direction\n",row += 3);

                }while (test_m);

                show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
                row += 4+cell_num+n*n+5;

            }else
            if(step == 2)
            {
                if(!split_check(list_c,list_m,num,0,cell_num,n))
                {
                    cell_num++;
                    show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
                    row += 4+cell_num+n*n+5;
                }
            }else
            if(step == 3)
            {
                boost(list_c,list_m,num,cell_num,n,row,cell_num1,cell_num2);
                row += 4+cell_num+n*n+5;
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

                make_new_blocks(new_block,blk,n);

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

                make_new_cell(list_c,list_m,new_cell,cell_num1,cell_num2,n);

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

            show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
            row += 4+cell_num+n*n+5;
        }

        int turn=0;
        do{
            if(!turn)
            {
                printf("\nPlayer 1 Turn\nPlease choose one of your cells\nWrite it's Number:\n");
                scanf("%d",&num);

                while(!check_turns(list_c,turn,num,cell_num))
                {
                    printf("Wrong\nThis Cell Does Not Belong to You\nChose Another Cell\n");
                    scanf("%d",&num);
                    row += 4;
                }

                turn = 1;
            } else{
                printf("\nPlayer 2 Turn\nPlease choose one of your cells\nWrite it's Number:\n");
                scanf("%d",&num);

                while(!check_turns(list_c,turn,num,cell_num))
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

                    test_m = move(list_c,list_m,player_move,num,cell_num,n);
                    if(test_m)
                        printf("\nNot Possible\nChose another Direction\n",row += 3);

                }while (test_m);

                show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
                row += 4+cell_num+n*n+5;

            }else
            if(step == 2)
            {
                int t;
                t = turn ? 0 : 1;

                if(!split_check(list_c,list_m,num,t,cell_num,n))
                {
                    if(turn)
                        cell_num2++;
                    else
                        cell_num1++;

                    show_map(list_c,list_m,n,cell_num,cell_num1,cell_num2,row);
                    row += 4+cell_num+n*n+5;
                }
            }else
            if(step == 3)
            {
                boost(list_c,list_m,num,cell_num,n,row,cell_num1,cell_num2);
                row += 4+cell_num+n*n+5;
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