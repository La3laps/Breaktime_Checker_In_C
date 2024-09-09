#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define clear() printf("\033[H\033[J")

// Code by Yaman and Rémi

int hour, min, sec;
int verifySignAM = 0;
int verifySignPM = 0;

void print(int choice);
void createTime();
void printTime(int hour, int min, int sec);

int main()
{
    createTime();
    printTime(hour, min, sec);

    return 0;
}

void createTime()
{

    time_t s, val = 1;
    struct tm *current_time;
    // time in seconds
    s = time(NULL);
    // to get current time
    current_time = localtime(&s);
    hour = current_time->tm_hour;
    min = current_time->tm_min;
    sec = current_time->tm_sec;
}

void printTime(int hour, int min, int sec)
{
    while (1)
    {
        clear();

        if (verifySignAM == 0 && hour == 10 && min > 0 && min < 30)
        {

            print(4);
            printf("\n");

            char sign;

            printf("\033[1;31m");
            printf("\n As-tu signé? y/n\n");
            printf("\033[0m");
            scanf(" %c", &sign);

            while (sign != 'y')
            {
                printf("\033[1;31m");
                printf("\n Toujours pas ? y/n\n");
                printf("\033[0m");
                scanf(" %c", &sign);

                if (sign == 'y')
                {

                    verifySignAM = 1;
                }
            }
            clear();
            printf("\033[0;32m");
            printf("\t\t\t\t     Noice!\n\n\n\n");
            printf("\033[0m");
            verifySignAM = 1;
        }
        else if (verifySignPM == 0 && hour == 14 && min >= 0 && min < 31)
        {
            print(4);
            printf("\n");

            char sign;

            printf("\033[1;31m");
            printf("\n As-tu signé? y/n\n");
            printf("\033[0m");
            scanf(" %c", &sign);

            while (sign != 'y')
            {
                printf("\033[1;31m");
                printf("\n Toujours pas ? y/n\n");
                printf("\033[0m");
                scanf(" %c", &sign);

                if (sign == 'y')
                {

                    verifySignPM = 1;
                }
            }
            clear();
            printf("\033[0;32m");
            printf("\t\t\t\t     Noice!\n\n\n\n");
            printf("\033[0m");
            verifySignPM = 1;
        }

        if (hour == 10 && min > 29 && min < 46 || hour == 15 && min >= 0 && min < 31)
        {
            print(1);
        }
        else if (hour == 12 && min > 29 || hour == 13 && min < 16)
        {
            print(2);
        }
        else if (hour >= 16 && min >= 45 || hour >= 17)
        {
            print(3);
        }
        else
        {

            // print time in minutes, hours and seconds
            printf("\n\n\n\n\t\t\t\t  %02d : %02d : %02d\n\n\n\n\n\n\n\n", hour, min, sec);
            if (verifySignAM == 1)
            {
                printf("\033[1;31m");
                printf("Signature du matin:");
                printf("\033[0m");
                printf(" signée!\n");
            }
            else
            {
                printf("\033[1;31m");
                printf("Signature du matin:");
                printf("\033[0m");
                printf(" aucune information.\n");
            }

            if (verifySignPM == 1)
            {
                printf("\033[1;31m");
                printf("Signature du soir:");
                printf("\033[0m");
                printf("  signée!\n\n\n\n");
            }
            else
            {
                printf("\033[1;31m");
                printf("Signature du soir:");
                printf("\033[0m");
                printf("  aucune information.\n\n\n\n");
            }
        }
        fflush(stdout);

        sec++;

        // update hour, minute and second
        if (sec == 60)
        {
            min += 1;
            sec = 0;
        }
        if (min == 60)
        {
            hour += 1;
            min = 0;
        }
        if (hour == 24)
        {
            hour = 0;
            min = 0;
            sec = 0;
            verifySignAM = 0;
            verifySignPM = 0;
        }

        sleep(1);
    }
}

void print(int choice)
{
    switch (choice)
    {
    case 1:

        printf("\033[0;36m");
        printf("\t####################################\n");
        printf("\t##  ====  ====  =  =  ====  ====  ##\n");
        printf("\t##  |  |  |  |  |  |  |     |     ##\n");
        printf("\t##  |===  |==|  |  |  |==|  |===  ##\n");
        printf("\t##  |     |  |  |  |     |  |     ##\n");
        printf("\t##  =     =  =  ====  ====  ====  ##\n");
        printf("\t####################################\n");
        printf("\033[0m");
        break;
    case 2:
        printf("\033[0;36m");
        printf("\t###############################################################\n");
        printf("\t##  ====  ====  =  =  ====  ====     =  =   ==   ====  =  =  ##\n");
        printf("\t##  |  |  |  |  |  |  |     |        |\\/|   ||   |  |  |\\/|  ##\n");
        printf("\t##  |===  |==|  |  |  |==|  ===      |  |   ||   |==|  |  |  ##\n");
        printf("\t##  |     |  |  |  |     |  |        |  |   ||   |  |  |  |  ##\n");
        printf("\t##  =     =  =  ====  ====  |===     =  =   ==   =  =  =  =  ##\n");
        printf("\t###############################################################\n");
        printf("\033[0m");
    case 3:
        printf("\033[0;33m");
        printf("\t#################################################################################\n");
        printf("\t##  ====  ==  =   =    ===   ====    ==== ====  =  =  ===\\  =   =  ====  ====  ##\n");
        printf("\t##  |     ||  |\\  |    |  \\  |         |  |  |  |  |  |  |  |\\  |  |     |     ##\n");
        printf("\t##  |==   ||  | \\ |    |   | |==       |  |  |  |  |  |==/  | \\ |  |==   |===  ##\n");
        printf("\t##  |     ||  |  \\|    |  /  |      |  |  |  |  |  |  |  \\  |  \\|  |     |     ##\n");
        printf("\t##  =     ==  =   =    ===   ====    ===  ====  ====  =  == =   =  ====  ====  ##\n");
        printf("\t#################################################################################\n");
        printf("\033[0m");
        break;
    case 4:
        printf("\033[1;31m");
        printf("\t#############################################################\n");
        printf("\t##  ====  ==  ====  =   =  ====  ====  =  =  ===\\   ====   ##\n");
        printf("\t##  |     ||  |     |\\  |  |  |   ||   |  |  |   |  |      ##\n");
        printf("\t##  |==|  ||  | ==| | \\ |  |==|   ||   |  |  |==/   |===   ##\n");
        printf("\t##     |  ||  |   | |  \\|  |  |   ||   |  |  |  \\   |      ## \n");
        printf("\t##  ====  ==  ====  =   =  =  =   ==   ====  =   =  ====   ##\n");
        printf("\t#############################################################\n");
        printf("\033[0m");
        break;
    default:
        break;
    }
}
