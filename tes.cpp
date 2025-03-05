#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char types[101];
    char price[101];
    char name[101];
}

void createBooking();
void viewBooking();
void deleteBooking();



int main(){
    int input = -1;
    do{
        do{
            puts("Hotel Gransylvania");
            puts("1. Booking Hotel ");
            puts("2. View Bookings");
            puts("3. Delete Booking");
            puts("4.Exit");
        }while(input < 1 || input > 3);
        
        switch(input){
            case 1:

        }
    }while(1);
}