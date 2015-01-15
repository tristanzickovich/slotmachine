#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>  //doesn't work on windows
#include <ctime>
#include <climits>
#include "slots.h"

using namespace std;
slots::slots()
 : welcome("***TRISTAN'S TREASURE SLOTS***"), wager(0), tokens(100)
 {}
 
void slots::wagerSetup()
{
    int wagerAmount;
    bool validWager = false;
    while(!validWager)
    {
        cout << "Total Tokens: " << tokens << endl;
        cout << "Choose Wager Amount: ";
        cin >> wagerAmount;
        if(cin.fail()){
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << endl << "Error: Please enter a number" << endl << endl;
        }
        else if(wagerAmount > tokens)
        {
            cout << endl << "Not enough tokens. Please wager lower." << endl
            << endl;
        }
        else if(wagerAmount < 1){
            cout << endl << "Invalid amount. Please wager at least 1 token." 
            << endl << endl;
        }
        else
        {
            validWager = true;
        }
    }
    
    this->wager = wagerAmount;
    cout << string(50, '\n');
    cout << "Wagering " << wagerAmount << " Token(s). Good Luck!" << endl;
}
 
void slots::spin()
{
    cout << endl << "Spinning!" << endl << endl;
    const bool winner = ( rand() % 100 ) < 20; // 20 % odds (roughly)
    if (winner)
    {
       this->slotOne = this->slotTwo = this->slotThree = rand() % 6 + 1;  
    }
    else
    {
       do
       {
            this->slotOne = rand() % 6 + 1;    
            this->slotTwo = rand() % 6 + 1;    
            this->slotThree = rand() % 6 + 1;    
       } while ( slotOne == slotTwo && slotTwo == slotThree );
    }
    this->oneFruit = spinTOfruit(this->slotOne);
    this->twoFruit = spinTOfruit(this->slotTwo);
    this->threeFruit = spinTOfruit(this->slotThree);
}

string slots::spinTOfruit(int currentSlot)
{
    if(currentSlot == 1)
    {
        return "apple";
    }
    else if(currentSlot == 2)
    {
        return "orange";
    }
    else if(currentSlot == 3)
    {
        return "cherry";
    }
    else if(currentSlot == 4)
    {
        return "strawberry";
    }
    else if(currentSlot == 5)
    {
        return "lemon";
    }
    else if(currentSlot == 6)
    {
        return "banana";
    }
}

void slots::spinOutput()
{
    string one = "?", two = "?", three = "?";
    for(int i = 3; i >= 0; --i)
    {
        cout << "----------------------------------------" << endl;
        cout.width(15); cout << left << one;
        cout.width(15); cout << left << two;
        cout.width(15); cout << left << three << endl;
        cout << "----------------------------------------" << endl;
        usleep(2000000);
        if(i == 3)
        {
            usleep(2000000);
            one = oneFruit;
            cout << string(50, '\n');
        }
        else if(i == 2)
        {
            two = twoFruit;
            cout << string(50, '\n');
        }
        else if(i == 1)
        {
            three = threeFruit;
            cout << string(50, '\n');
        }
    }
    roundOutcome();
}

void slots::roundOutcome()
{
    if(slotOne == slotTwo && slotOne == slotThree)
    {
        cout << "Winner! Congratulations!" << endl;
        this->tokens += wager;
        cout << "New Token Balance: " << tokens << endl;
    }
    else
    {
        cout << "Aww. Better luck next time." << endl;
        this->tokens -= wager;
        cout << "Tokens Remaining: " << tokens << endl;
    }
}

void slots::run_slots()
{
    char gameplay = 'Y';
    bool winner = true;
    srand(time(0));
    while(gameplay != 'n' && gameplay != 'N')
    {
        cout << string(50, '\n');
        cout << welcome << endl;
        wagerSetup();
        spin();
        spinOutput();
        if(tokens > 0)
        {
            cout << "Continue Playing? (Y or N): ";
            cin >> gameplay;
            cout << endl;
            while(gameplay != 'n' && gameplay != 'N' && gameplay != 'Y' && gameplay != 'y'){
                cout << "Invalid Option. Continue Playing? (Y or N): ";
                cin >> gameplay;
                cout << endl;
            }
        }
        else
        {
            winner = false;
            break;
        }
    }
    if(winner)
    {
        cout << "Thanks for playing!" << endl;
        cout << "You ended with " << tokens << " tokens!" << endl;
    }
    else
    {
        cout << "No tokens remaining. You Lose." << endl;
    }
}
