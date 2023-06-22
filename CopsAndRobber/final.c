#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <zconf.h>

char board[99][99],mark='a';
int t=1,x_police[50][50],y_police[50][50],x_thief,y_thief,col,row,department,police[50],saw_the_thief[50];

void print() {
    int k, z;

    printf("\n%dth Picture\n", t - 1);

    for (z = 0; z < col; z++) {
        printf("_______");
    }
    printf("_\n");
    for (z = 0; z < row; z++) {
        printf("|");
        for (k = 0; k < col; k++) {
            if (board[k][z] >= 'a' && board[z][k] <= 'z') {
                if ((int) (board[k][z] - 96) > 9)
                    printf("  D%d |", board[k][z] - 96);
                else
                    printf("  D%d  |", board[k][z] - 96);

            } else {
                if (board[k][z] == 'T')
                    printf("  %c   |", 'T');
                else
                    printf("      |");
            }
        }
        printf("\n");
        printf("|");
        for (k = 0; k < col; k++) {
            printf("______|");
        }
        printf("\n");
    }
    t++;
    sleep(5);
    system("cls");
}

double distance (int x1, int y1,int x2,int y2)
{
    double dist;
    dist = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    return dist;
}

int result ()
{
    double dist;
    int k,z,iter;
    iter=0 ;

    for(k=0; k<department ;k++)
    {
        for(z=0; z<police[k] ;z++)
        {
            if(x_thief == x_police[k][z] && y_thief == y_police[k][z])
            {
                print();
                return 1002;
            }
        }
    }
    for(k=0; k<department ;k++)
    {
        for(z=0; z<police[k] ;z++)
        {
            dist=distance(x_police[k][z],y_police[k][z],x_thief,y_thief);
            if(dist <= sqrt(8))
            {
                saw_the_thief[iter] = k;
                iter++;
                break;
            }
        }
    }
    print();
    if( iter != 0 )
        return iter;
    return 1003;
}

int thief_move() {
    int z, k,temp;

    board[x_thief][y_thief] = ' ';

    if (x_thief == 0)
    {
        temp = rand() % 2;
        x_thief += temp;
    }
    else
    {
        if(x_thief == col-1)
        {
            temp = rand() % 2;
            x_thief -= temp;
        }
        else
        {
            temp = rand() % 3;
            x_thief += temp - 1;
        }
    }
    if (y_thief == 0)
    {
        temp = rand() % 2;
        y_thief += temp;
    }
    else
    {
        if(y_thief == row-1)
        {
            temp = rand() % 2;
            y_thief -= temp;
        }
        else
        {
            temp = rand() % 3;
            y_thief += temp - 1;
        }
    }

    board[x_thief][y_thief] = 'T';

    for (k = 0; k < department; k++) {
        for (z = 0; z < police[k]; z++) {
            if (x_thief == x_police[k][z] && y_thief == y_police[k][z]) {
                print();
                return 1001;
            }
        }
    }

    for (k = 0; k < col; k++) {
        for (z = 0; z < row; z++) {
            if (board[k][z] != 'T')
                board[k][z] = ' ';
        }
    }
    return 0;
}

int next_move()
{
    int k,z,thief,temp,x_temp,y_temp;

    thief=thief_move();
    if(thief == 1001)
        return 1001;

    time_t r=time(NULL);
    srand(r);

    for (k = 0; k < department; k++)
    {
        for (z = 0; z < police[k]; z++)
        {
            x_temp = x_police[k][z];
            y_temp = y_police[k][z];

            if(x_police[k][z] == 0)
            {
                temp = rand() % 2;
                x_police[k][z] += temp;
            }
            else
            {
                if(x_police[k][z] == col-1)
                {
                    temp = rand() % 2;
                    x_police[k][z] -= temp;
                }
                else
                {
                    temp = rand() % 3;
                    x_police[k][z] += temp - 1;
                }
            }
            if(y_police[k][z] == 0)
            {
                temp = rand() % 2;
                y_police[k][z] += temp;
            }
            else
            {
                if(y_police[k][z] == row-1)
                {
                    temp = rand() % 2;
                    y_police[k][z] -= temp;
                }
                else
                {
                    temp = rand() % 3;
                    y_police[k][z] += temp - 1;
                }
            }

            if (board[x_police[k][z]][y_police[k][z]] != ' ')
            {
                if(board[x_police[k][z]][y_police[k][z]] != 'T')
                {
                    x_police[k][z] = x_temp;
                    y_police[k][z] = y_temp;
                    z--;
                    continue;
                }
            }

            board[x_police[k][z]][y_police[k][z]] = mark + k;
        }
    }
    return result();
}

int thief_in_sight(int iter)
{
    int z,i,k,temp=0,x_thief_previous,y_thief_previous,test,x_temp,y_temp,thief;

    x_thief_previous = x_thief;
    y_thief_previous = y_thief;

    thief=thief_move();
    if(thief == 1001)
        return 1001;

    for (i=0; i<iter ;i++)
    {
        k = saw_the_thief[i];
        for(z=0; z<police[k]; z++)
        {
            x_temp = x_police[k][z];
            y_temp = y_police[k][z];

            if(y_police[k][z] > y_thief_previous)
                y_police[k][z] -=1;
            else
            {
                if(y_police[k][z] < y_thief_previous)
                    y_police[k][z] += 1;
            }
            if(x_police[k][z] > x_thief_previous)
                x_police[k][z] -=1;
            else
            {
                if(x_police[k][z] < x_thief_previous)
                    x_police[k][z] +=1;
            }
            if (board[x_police[k][z]][y_police[k][z]] != ' ')
            {
                if(board[x_police[k][z]][y_police[k][z]] != 'T')
                {
                    x_police[k][z] = x_temp;
                    y_police[k][z] = y_temp;
                }
            }
            board[x_police[k][z]][y_police[k][z]] = mark + k;
        }
    }

    for (k = 0; k < department; k++)
    {
        test=0;
        for (i=0; i<iter ;i++)
        {
            if(k == saw_the_thief[i])
            {
                test++;
                break;
            }
        }
        if(test != 0)
            continue;

        for (z = 0; z < police[k]; z++)
        {
            x_temp = x_police[k][z];
            y_temp = y_police[k][z];

            if(x_police[k][z] == 0)
            {
                temp = rand() % 2;
                x_police[k][z] += temp;
            }
            else
            {
                if(x_police[k][z] == col-1)
                {
                    temp = rand() % 2;
                    x_police[k][z] -= temp;
                }
                else
                {
                    temp = rand() % 3;
                    x_police[k][z] += temp - 1;
                }
            }
            if(y_police[k][z] == 0)
            {
                temp = rand() % 2;
                y_police[k][z] += temp;
            }
            else
            {
                if(y_police[k][z] == row-1)
                {
                    temp = rand() % 2;
                    y_police[k][z] -= temp;
                }
                else
                {
                    temp = rand() % 3;
                    y_police[k][z] += temp - 1;
                }
            }

            if (board[x_police[k][z]][y_police[k][z]] == ' ' || board[x_police[k][z]][y_police[k][z]] == 'T')
            {
                board[x_police[k][z]][y_police[k][z]] = mark + k;
            }
            else
            {
                x_police[k][z] = x_temp;
                y_police[k][z] = y_temp;
                z--;
                continue;
            }
        }
    }
    return result();
}

int first_move()
{
    int k,z;
    time_t r=time(NULL);
    srand(r);

    for(k=0; k<col ;k++)
    {
        for(z=0; z<row ; z++)
            board[k][z]=' ';
    }

    x_thief = rand() % col;
    y_thief = rand() % row;
    board[x_thief][y_thief] = 'T';

    for (k = 0; k < department; k++) {
        for (z = 0; z < police[k]; z++) {

            x_police[k][z] = rand() % col;
            y_police[k][z] = rand() % row;

            if (board[x_police[k][z]][y_police[k][z]] != ' ')
            {
                z--;
                continue;
            }
            board[x_police[k][z]][y_police[k][z]] = mark + k;
        }
    }
    return result();
}

int main(){
    int res,z,sum=0,k;
    printf("Please Enter Number of columns\n");
    scanf("%d",&col);
    printf("Please Enter Number of Rows\n");
    scanf("%d",&row);
    printf("Please Enter the Number of Department\n");
    scanf("%d",&department);
    for(k=0; k<department ;k++)
    {
        printf("Please Enter the Number of Police in %dth Department\n",k+1);
        scanf("%d",&police[k]);
    }
    system("cls");

    res = first_move();

    while(1)
    {
        if(res == 1001)
        {
            printf("\n\nThe Thief gave himself up\n\n");
            break;
        }
        else
        {
            if(res == 1002)
            {
                printf("\n\nPolice got the Thief\n\n");
                break;
            }
            else
            {
                if(res == 1003)
                {
                    res = next_move();
                    continue;
                }
                else
                {
                    res = thief_in_sight(res);
                    continue;
                }
            }
        }
    }

    printf("The Number of Thief's Moves were %d\n\n",t-2);
    for(k=0; k<department ;k++)
    {
        sum+=police[k];
    }
    printf("The Number of Police's Moves were %d\n\n",(t-2)*sum);
    sleep(10);
    return 0;
}