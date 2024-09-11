#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "shutdown.h"

#define clear() printf("\033[H\033[J")

// Code by Yaman and Rémi

int day, hour, min, sec;
int checkDay;
int verifySignAM = 0;
int verifySignPM = 0;

FILE *s1_file; // read only
FILE *s2_file; // write only

void print(int choice);
int createTime();
void printTime();
void checkConditionsOfDay();
int storeSignature(int signAMorPM, int reset);

int main()
{
    printTime();
    return 0;
}

int createTime()
{

    time_t s, val = 1;
    struct tm *current_time;
    // time in seconds
    s = time(NULL);
    // to get current time
    current_time = localtime(&s);
    day = current_time->tm_mday;
    hour = current_time->tm_hour;
    min = current_time->tm_min;
    sec = current_time->tm_sec;
    return hour, min, sec;
}

int storeSignature(int signAMorPM, int reset)
{
    s1_file = fopen("signatures/s1.txt", "w");
    s2_file = fopen("signatures/s2.txt", "w");

    if (s1_file == NULL)
    {

        printf("Impossible d'accéder au dossier \"/signatures\". Les signatures ne s'afficheront pas à la fermeture du programme");
        return 1;
    }

    if (signAMorPM == 0 && reset == 0)
    {
        fprintf(s1_file, "1");
    }
    if (signAMorPM == 1 && reset == 0)
    {
        fprintf(s2_file, "1");
    }
    else if (reset == 1)
    {
        fprintf(s1_file, "0");
        fprintf(s2_file, "0");
    }
    fclose(s1_file);
    fclose(s2_file);
}

void printTime()
{
    while (1)
    {
        clear();
        system("clear");
        createTime();

        if (hour > 0 && hour < 10 && min <= 30)
        {
            storeSignature(1, 1);
        }
        checkConditionsOfDay();

        fflush(stdout);

        sec++;

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
        printf("\t##  ===-  -==-  =  =  -===  -===  ##\n");
        printf("\t##  |  |  |  |  |  |  |     |     ##\n");
        printf("\t##  -==-  -==-  |  |  -==-  -===  ##\n");
        printf("\t##  |     |  |  |  |     |  |     ##\n");
        printf("\t##  =     =  =  ====  ===-  -===  ##\n");
        printf("\t####################################\n");
        printf("\033[0m");
        break;
    case 2:
        printf("\033[0;36m");
        printf("\t###############################################################\n");
        printf("\t##  ===-  -==-  =  =  -===  -===     =  =   ==   -==-  =  =  ##\n");
        printf("\t##  |  |  |  |  |  |  |     |        |\\/|   ||   |  |  |\\/|  ##\n");
        printf("\t##  -==-  -==-  |  |  -==-  -==      |  |   ||   -==-  |  |  ##\n");
        printf("\t##  |     |  |  |  |     |  |        |  |   ||   |  |  |  |  ##\n");
        printf("\t##  =     =  =  ====  ===-  -===     =  =   ==   =  =  =  =  ##\n");
        printf("\t###############################################################\n");
        printf("\033[0m");
        break;
    case 3:
        printf("\033[0;33m");
        printf("\t#################################################################################\n");
        printf("\t##  ====  ==  =   =    ==-   -===    ==== -==-  =  =  ===\\  =   =  -===  -===  ##\n");
        printf("\t##  |     ||  |\\  |    |  \\  |         |  |  |  |  |  |  |  |\\  |  |     |     ##\n");
        printf("\t##  -==   ||  | \\ |    |   | -==       |  |  |  |  |  -==/  | \\ |  -==   -===  ##\n");
        printf("\t##  |     ||  |  \\|    |  /  |      |  |  |  |  |  |  |  \\  |  \\|  |     |     ##\n");
        printf("\t##  =     ==  =   =    ==-   -===    ==-  -==-  -==-  =   = =   =  -===  -===  ##\n");
        printf("\t#################################################################################\n");
        printf("\033[0m");
        break;
    case 4:
        printf("\033[1;31m");
        printf("\t#############################################################\n");
        printf("\t##  -===  ==  -===  =   =  -==-  ====  =  =  ===\\   -===   ##\n");
        printf("\t##  |     ||  |     |\\  |  |  |   ||   |  |  |   |  |      ##\n");
        printf("\t##  -==-  ||  | ==- | \\ |  -==-   ||   |  |  -==/   -===   ##\n");
        printf("\t##     |  ||  |   | |  \\|  |  |   ||   |  |  |  \\   |      ## \n");
        printf("\t##  ===-  ==  -===  =   =  =  =   ==   -==-  =   =  -===   ##\n");
        printf("\t#############################################################\n");
        printf("\033[0m");
        break;
    default:
        break;
    }
}

void checkConditionsOfDay()
{
    // Verifies if user signed for the morning
    if (verifySignAM == 0 && hour == 10 && min >= 0 && min < 31)
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
                storeSignature(0, 0);
            }
        }
        clear();
        printf("\033[0;32m");
        printf("\t\t\t\t     Noice!\n\n\n\n");
        printf("\033[0m");
        verifySignAM = 1;
        storeSignature(0, 0);
    }
    // Verifies if user signed for the afternoon
    else if (verifySignPM == 0 && hour == 15 && min >= 0 && min < 31)
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
                storeSignature(1, 0);
            }
        }
        clear();
        printf("\033[0;32m");
        printf("\t\t\t\t     Noice!\n\n\n\n");
        printf("\033[0m");
        verifySignPM = 1;
        storeSignature(1, 0);
    }

    // prints break time or end of day time
    else if (hour == 10 && min > 29 && min < 46 || hour == 15 && min >= 0 && min < 16)
    {
        print(1);
    }
    else if (hour == 12 && min > 29 || hour == 13 && min < 16)
    {
        print(2);
    }
    else if (hour >= 16 && min > 43 && hour < 24 || hour >= 17 && hour < 24)
    {
        print(3);
        storeSignature(1, 1);
        shutDown();
    }
    else
    {
        // prints the clock and the signatures' state
        s1_file = fopen("signatures/s1.txt", "r");
        s2_file = fopen("signatures/s2.txt", "r");

        char s1[2];
        char s2[2];

        fgets(s1, 2, s1_file);
        fgets(s2, 2, s2_file);

        // print time in minutes, hours and seconds
        printf("\n\n\n\n\t\t\t\t  %02d", hour);
        printf("\033[1;31m");
        printf(" : ");
        printf("\033[0m");
        printf("%02d", min);
        printf("\033[0m");
        printf("\033[1;31m");
        printf(" : ");
        printf("\033[0m");
        printf("%02d\n\n\n\n\n\n\n\n", sec);

        // print state of signatures (signed or not/ morning or afternoon)
        if (strcmp(s1, "1") == 0)
        {
            printf("\033[1;31m");
            printf("\tSignature du matin:");
            printf("\033[0;32m");
            printf(" signée!\n");
            printf("\033[0m");
        }
        else
        {
            printf("\033[1;31m");
            printf("\tSignature du matin:");
            printf("\033[0m");
            printf(" aucune information.\n");
        }

        if (strcmp(s2, "1") == 0)
        {
            printf("\033[1;31m");
            printf("\tSignature du soir:");
            printf("\033[0;32m");
            printf("  signée!\n\n\n\n");
            printf("\033[0m");
        }
        else
        {
            printf("\033[1;31m");
            printf("\tSignature du soir:");
            printf("\033[0m");
            printf("  aucune information.\n\n\n\n");
        }
        fclose(s1_file);
        fclose(s2_file);
    }
}