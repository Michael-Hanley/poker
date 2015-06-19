#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>

using namespace std;
struct card_struct{
    string rank;
    string suite;
    string full_name;
    int shuffle;
    int count;
};

void intro();
void get_cards(card_struct[]);
void shuffle(card_struct[]);
int draw(card_struct[], int, int);

const int NUM_CARDS = 52;
const int DRAW = 2;
const int FLOP = 3;
const int TURN = 1;
const int RIVER = 1;
const int BURN = 1;

int main()
{
    card_struct *card=NULL;
    card = new card_struct[NUM_CARDS];
    int count=0;


    intro();                        //introduces the poker program
    get_cards(card);                //fills the data struct will cards
    shuffle(card);                  //shuffles cards
    count = draw(card, DRAW, count);       //draw 2 cards
     


    delete[] card;
    return 0;
}

// 
//
//Declare what the program does
//
//

void intro()
{
    cout << "Hello and welcome to my poker simulator!" <<endl << endl;
    cout << "New game?";
    cin.ignore();
}

//
//occupies the struct with 52 playing cards
//
//

void get_cards(card_struct card[])
{
    int card_count = 0;
    int suite_count = 0;
    int rank_count = 0;
    string suite[4] = { "Spades", "Clubs", "Hearts", "Diamonds" };
    string rank[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };

    do{
        while (rank_count < 13)
        {
            card[card_count].rank = rank[rank_count];
            card[card_count].suite = suite[suite_count];
            card[card_count].full_name = card[card_count].rank + " " + "of" + " " + card[card_count].suite;
            card[card_count].count=card_count;
            rank_count++;
            card_count++;
        }
        rank_count = 0;
        suite_count++;

    } while (suite_count < 4);
}

//
//
//Function to randomize a set of 52 non repeating numbers and tie it to the
//struct for a shuffle
//

void shuffle(card_struct card[])
{
    srand((unsigned int)time(0));
    bool swapmade = false;
    int temp[52];
    int card_num = 0;
    int check_num = 0;
    for (card_num = 0; card_num < NUM_CARDS; card_num++)
    {
        card[card_num].shuffle = rand() % NUM_CARDS;
        temp[card_num] = card[card_num].shuffle;
        do{
            swapmade = false;
            for (check_num = 0; check_num <= NUM_CARDS; check_num++)
            {

                if (card[card_num].shuffle == temp[check_num] && check_num != card_num)
                {
                    card[card_num].shuffle = rand() % NUM_CARDS;
                    temp[card_num] = card[card_num].shuffle;
                    swapmade = true;
                }
            }
        } while (swapmade);
    }
}
//
//
//draws 2 cards from the deck
//
//
int draw(card_struct card[], int num_cards, int count)
{
    int draw = 0;
    //initial draw

    for (draw = 0; draw <num_cards; draw++)
    {
        cout << card[card[count].shuffle].full_name << endl;
        count++;
    }
return count;
}