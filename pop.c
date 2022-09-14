/* 
# pop.c
# Nicolas Metzler
# Student ID: 501050712
# Assignment #2 - Pop Machine
# CPS 393 Section 3J0
# Instructor: L. Hiraki
# Purpose: To simulate a pop machine.
#
# I hereby attest that I am the sole owner and author of this code (except for wording of print statements provided by Prof. Hiraki) and that to the best of my knowledge, this code has not infringed on anyone’s copyright. Credit for any ideas, coding, and other materials used to develop this code has been given to the owners of the sources used in accordance to the rules of Ryerson's Academic Integrity Policy.
*/

/* include necessary libraries */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define POPNAME "Pop"

/* Variables for argument */
#define UPPERLIMITPRICE 105
#define LOWERLIMITPRICE 30
#define LOWESTDENOMINATOR 5 /* Price must be divisible by this value */

/* Coin Names */
#define COIN1NAME "Quarter"
#define COIN2NAME "Dime"
#define COIN3NAME "Nickel"

/* Coin values */
#define COIN1VALUE 25 /* Quarter Value */
#define COIN2VALUE 10 /* Dime Value */
#define COIN3VALUE 5 /* Nickel Value */

/* User inputs */
/* Coin 1 (Quarter) Inputs */
#define COIN1INPUTUPPERCASE 'Q'
#define COIN1INPUTLOWERCASE 'q'
/* Coin 2 (Dime) Inputs */
#define COIN2INPUTUPPERCASE 'D'
#define COIN2INPUTLOWERCASE 'd'
/* Coin 3 (Nickel) Inputs */
#define COIN3INPUTUPPERCASE 'N'
#define COIN3INPUTLOWERCASE 'n'
/* Change Inputs */
#define CHANGEINPUTUPPERCASE 'R'
#define CHANGEINPUTLOWERCASE 'r'
/* Maintanence/Exit Inputs */
#define EXITINPUTUPPERCASE 'E'
#define EXITINPUTLOWERCASE 'e'

/* Name of Currency used */
#define CURRENCYNAME "cents"

int main( int argc, char *argv[] ) {
    /* Point to argument and take it as an int variable  */
    int sodaPrice = 0;
    if( argc == 2 ){
        char *sodaChar = argv[1];
        sodaPrice = atoi(sodaChar);
    }
    /* Check if Price exists or is valid */
    if( argc < 2){
        printf("ERROR: Please specify selling price as a command line argument.\nUsage: pop [price]\n");
    }
    else if( argc > 2) {
        printf("ERROR: Please only enter one argument\n");
    }
    else if( sodaPrice > UPPERLIMITPRICE || sodaPrice < LOWERLIMITPRICE ){
        printf("ERROR: Price must be from %d to %d %s inclusive\n", LOWERLIMITPRICE, UPPERLIMITPRICE, CURRENCYNAME);
    }
    else if( sodaPrice % LOWESTDENOMINATOR != 0 ){
        printf("ERROR: Price must be a multiple of %d\n", LOWESTDENOMINATOR); 
    }
    /* Machine boots up */
    else {
        /* Variable declarations */
        char coinChoice;
        int balance = 0;
        int owed;
        int change = 0;
        int workingNumber;
        int numberOfCoin2 = 0;
        int numberOfCoin3 = 0;
        /* Welcome message */
        printf("\nWelcome to my C Pop Machine!");

        /* Keep machine running unless maintanence commands are entered */
        while( coinChoice != EXITINPUTUPPERCASE || coinChoice != EXITINPUTLOWERCASE ) {
            printf("\n\n%s is %d %s.\nPlease insert any combination of %s [%c or %c], %s [%c or %c] or %s [%c or %c]. You can also press %c or %c for coin return.\n", POPNAME, sodaPrice, CURRENCYNAME, COIN3NAME, COIN3INPUTUPPERCASE, COIN3INPUTLOWERCASE, COIN2NAME, COIN2INPUTUPPERCASE, COIN2INPUTLOWERCASE, COIN1NAME, COIN1INPUTUPPERCASE, COIN1INPUTLOWERCASE, CHANGEINPUTUPPERCASE, CHANGEINPUTLOWERCASE);
            
            /* Keep prompting for tender until right amount is achieved */
            while( balance < sodaPrice ) {
                printf("\nEnter coin (%c%c%c%c) : ", COIN3INPUTUPPERCASE, COIN2INPUTUPPERCASE, COIN1INPUTUPPERCASE, CHANGEINPUTUPPERCASE);
                
                scanf(" %c", &coinChoice);
                printf("%c", coinChoice);
                
                /* Figure out which input was passed through */
                if( coinChoice == COIN3INPUTUPPERCASE || coinChoice == COIN3INPUTLOWERCASE ) {
                    balance = balance + COIN3VALUE;
                    printf("\n%s detected.", COIN3NAME);
                } 
                else if( coinChoice == COIN2INPUTUPPERCASE || coinChoice == COIN2INPUTLOWERCASE ) {
                    balance = balance + COIN2VALUE;
                    printf("\n%s detected.", COIN2NAME);
                }
                else if( coinChoice == COIN1INPUTUPPERCASE || coinChoice == COIN1INPUTLOWERCASE ) {
                    balance = balance + COIN1VALUE;
                    printf("\n%s detected.", COIN1NAME);
                }
                /* If Maintenence or Return, break the loop */
                else if(( coinChoice == CHANGEINPUTUPPERCASE || coinChoice == CHANGEINPUTLOWERCASE ) || ( coinChoice == EXITINPUTUPPERCASE || coinChoice == EXITINPUTLOWERCASE )) {
                    break;
                }
                /* Invalid Input */
                else {
                    printf("\nUnknown coin detected, please try again");
                }
                
                /* Show user how much they have entered */
                printf("\nYou have inserted a total of %d %s.", balance, CURRENCYNAME);
                
                /* Show user how much more tender is needed */
                if( balance < sodaPrice ){
                    owed = (sodaPrice - balance);
                    printf("\nPlease insert %d more %s\n", owed, CURRENCYNAME);
                    change = balance;
                }
                /* Allow machine to dispense the Pop, and calculate the change amount */
                else{
                    printf("\n\n%s is dispensed. Thank you for your business! Please come again.", POPNAME);
                    change = balance - sodaPrice;
                }
                
            }
            /* Prompt Loop is broken */
            /* Calculate the amount of each coin needed for change */
            workingNumber = change;
            while( workingNumber >= COIN3VALUE ) {
                if( workingNumber >= COIN2VALUE ){
                    numberOfCoin2 = numberOfCoin2 + 1;
                    workingNumber = workingNumber - COIN2VALUE;
                }
                else if( workingNumber == COIN3VALUE ){
                    numberOfCoin3 = numberOfCoin3 + 1;
                    workingNumber = workingNumber - COIN3VALUE;
                }
            }
            /* Print the change dialogue with proper information from calculation above */
            printf("\nChange given : %d %s as %d %s(s) and %d %s(s)", change, CURRENCYNAME, numberOfCoin2, COIN2NAME, numberOfCoin3, COIN3NAME);

            /* If Maintanence command was entered */
            if( coinChoice == EXITINPUTUPPERCASE || coinChoice == EXITINPUTLOWERCASE ){
                printf("\nNow exiting...");
                break;
            }

            /* Reset the machine and the variables */
            numberOfCoin2 = 0;
            numberOfCoin3 = 0;
            balance = 0;
        }
    }
}

