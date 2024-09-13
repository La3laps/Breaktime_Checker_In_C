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

// print certain texts (like "pause", or "signature") on stdout.
void print(int choice);

// gets current machine time
int createTime();

// prints everything depending on conditions of day
void printAll();

// checks for pauses, signature, lunch break
void checkConditionsOfDay();

// store signatures for morning/evening (signAMorPM) or resets them if needed
int storeSignature(int signAMorPM, int reset);

int main()
{
    printAll();
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

    // creates time
    day = current_time->tm_mday;
    hour = current_time->tm_hour;
    min = current_time->tm_min;
    sec = current_time->tm_sec;
    return hour, min, sec;
}

int storeSignature(int signAMorPM, int reset)
{

    // SignAmorPM == 0 means morning
    if (signAMorPM == 0)
    {
        s1_file = fopen("signatures/s1.txt", "w");
        // changes content of s1.txt to "1"
        fprintf(s1_file, "1");
        fclose(s1_file);
    }
    // SignAmorPM == 1 means evening
    else if (signAMorPM == 1)
    {
        s2_file = fopen("signatures/s2.txt", "w");
        // changes content of s2.txt to "1"
        fprintf(s2_file, "1");
        fclose(s2_file);
    }
    // reset == 1 turns the text files with "1" in them to "0"
    else if (reset == 1)
    {
        s1_file = fopen("signatures/s1.txt", "w");
        s2_file = fopen("signatures/s2.txt", "w");
        // changes content of s1.txt and s2.txt to "0"
        fprintf(s1_file, "0");
        fprintf(s2_file, "0");
        fclose(s1_file);
        fclose(s2_file);
    }
}

void printAll()
{
    while (1)
    {
        // clears screen linux/windows
        clear();
        system("clear");

        // gets current time
        createTime();

        // check for morning (before 9:30AM) to reset signature
        if (hour > 0 && hour < 10 && min <= 30)
        {
            storeSignature(1, 1);
        }

        // prints different things to stdout depending on time of day/signature
        checkConditionsOfDay();

        // flush stdout
        fflush(stdout);

        // keeps screen from flickering
        sleep(1);
    }
}

void print(int choice)
{
    switch (choice)
    {
    case 1:
        // print(1) prints "PAUSE"
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
        // print(2) prints "PAUSE MIAM"
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
        // print(3) prints "FIN DE JOURNEE"
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
        // print(4) prints "SIGNATURE"
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
    // Checks if user hasn't signed for the morning
    if (verifySignAM == 0 && hour == 10 && min >= 45 && min <= 59)
    {

        print(4);
        printf("\n");

        // ask user for input on signature
        char sign;

        printf("\033[1;31m");
        printf("\n As-tu signé? y/n\n");
        printf("\033[0m");
        scanf(" %c", &sign);

        // following while runs if user does not answer "y"
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
        // following code runs if signed
        clear();
        printf("\033[0;32m");
        printf("\n\n\n\n\t\t\t\t  A signé pour le matin.\n\n\n\n");
        printf("\033[0m");
        // stores signature for morning
        verifySignAM = 1;
        storeSignature(0, 0);
    }
    // Checks if user hasn't signed for the afternoon
    else if (verifySignPM == 0 && hour == 15 && min >= 16 && min <= 45)
    {
        print(4);
        printf("\n");

        char sign;
        // ask user for input on signature
        printf("\033[1;31m");
        printf("\n As-tu signé? y/n\n");
        printf("\033[0m");
        scanf(" %c", &sign);

        // following while runs if user does not answer "y"
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
        // following code runs if signed
        clear();
        printf("\033[0;32m");
        printf("\n\n\n\n\t\t\t\t  A signé pour l'après-midi.\n\n\n\n");
        printf("\033[0m");
        // stores signature for afternoon
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
    else if (hour >= 16 && min >= 40 && hour < 24 || hour >= 17 && hour < 24)
    {
        print(3);
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