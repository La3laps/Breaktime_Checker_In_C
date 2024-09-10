#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#define clear() printf("\033[H\033[J")

void shutDown (){

    printf("Do you want to turn off your pc (y/n) ? \n");
    char answer;
    scanf(" %c", &answer);
    int seconds = 10;
    if (answer == 'y'){
        printf("Save your files and close your navigation windows, your pc will shutdown in..\n");
        
        int seconds = 59;
        
        while (seconds != 0 ){
            clear();
            printf(" %02d ", seconds);
            seconds--;
            if (seconds == 10){
                /**** print à demain */
            }
            if (seconds == 0){
                system("shutdown -P now");
            }
            fflush(stdout);
            sleep(1);
            clear();
        }
    } else {
        printf("Bonne jouirnée \n");
    }
}

/*int main () {

    shutDown();

    return 0;
}*/

