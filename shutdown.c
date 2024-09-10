#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

void shutDown()
{
    printf("\033[0;33m");
    printf("\n\n\tDo you want to turn off your pc (y/n) ? \n\t");
    printf("\033[0m");

    char answer;
    scanf(" %c", &answer);
    int seconds = 10;
    if (answer == 'y')
    {

        int seconds = 59;

        while (seconds != 0)
        {
            clear();
            printf("\033[1;31m");
            printf("\n\n\tSave your files and close your navigation windows, your pc will shutdown in..\n");
            printf("\033[0m");
            printf("\n\n\n\t %02d \n\n", seconds);
            seconds--;
            if (seconds < 10)
            {
                printf("\n\n");
                printf("\033[1;31m");
                printf("\t########################################################################\n");
                printf("\t##  ===-  -==-  =   =  =   =  -===   -===  -==-  ==  ==-  -===  -===  ##\n");
                printf("\t##  |  |  |  |  |\\  |  |\\  |  |      |     |  |  ||  |  | |     |     ##\n");
                printf("\t##  -==   |  |  | \\ |  | \\ |  |==    -==-  |  |  ||  |=-  |==   |==   ##\n");
                printf("\t##  |  |  |  |  |  \\|  |  \\|  |         |  |  |  ||  | \\  |     |     ##\n");
                printf("\t##  ===-  -==-  =   =  =   =  -===   ===-  -==-  ==  =  = -===  -===  ##\n");
                printf("\t########################################################################\n");
                printf("\033[0m");
            }
            if (seconds == 0)
            {
                system("shutdown -P now");
            }
            fflush(stdout);
            sleep(1);
            clear();
        }
    }
    else
    {
        printf("\tLe PC ne sera pas redémarré. \n");
    }
}