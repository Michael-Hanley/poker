/***************************************************************************************
poker game
Currently single player, texas holdem style poker game
Michael Hanley
pasaqualI@gmail.com
*******************************************************************************************/

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
    int hand;
    int rank_num;

};

void intro();
void get_cards(card_struct[]);
void shuffle(card_struct[]);
void draw(card_struct[], int, int &, int &);
void BubbleSort(card_struct[], int);
void Swap(card_struct &a, card_struct &b);
int play(card_struct[]);

const int NUM_CARDS = 52;
const int DRAW = 2;
const int FLOP = 3;
const int TURN = 1;
const int RIVER = 1;

int main()
{
    card_struct *card=NULL;
    card = new card_struct[NUM_CARDS];
    int count = 0;
    char again_c;
    bool again;
    do{

    intro();                        //introduces the poker program
    get_cards(card);                //fills the data struct will cards
    shuffle(card);                  //shuffles cards
    count = play(card);
    BubbleSort(card, count);

    int i;
    for (i=0;i<count;i++)
    {
        cout << card[card[i].hand].full_name << endl;
    }

    cout << "Would you like to run it again?(y/n)";
    cin >> again_c;
    cin.ignore(0, '\n');
        if (again_c == 'y')
            again=true;
        else 
            again=false;
    } while (again);
    delete[] card;
    return 0;

}
    /***************************************************************
    string suite[4] = { "Spades", "Clubs", "Hearts", "Diamonds" };
    string rank[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };
    int i = 0;
    string answer;
    string temp;

    if ()


       
 do{   
 while(i < count)
    {   
        if (rank[card[i].shuffle] == rank[card[i + 1].shuffle])
        {
            answer = "Pair";
        }
        i++;
    }
    } while (x <)
    while (i < 13)
    {
        


        else if((*rank[card[i].shuffle]) < (*rank[card[i + 1].shuffle))
        {
            answer = card[i].shuffle
        }



    i++;
    }
    cout << "grats you got a " << answer;
    *****************************************************/
//
//
//
//
//
int play(card_struct card[])
{
    int count = 0;
    int bcount = 0;
    cout << "Your cards: " << endl;
    draw(card, DRAW, count, bcount);     //player draws
    bcount++;                            //burn
    cout << "The Flop:" << endl;        
    draw(card, FLOP, count, bcount);     // the flop
    bcount++;                            //burn
    cout << "The Turn" << endl;
    draw(card, TURN, count, bcount);     //the turn
    bcount++;                            //burn
    cout << "The River" << endl;   
    draw(card, RIVER, count, bcount);    //the river
    return count;
}
// 
//
//Declare what the program does
//
//
void intro()
{
    cout << "Hello and welcome to my poker simulator!" <<endl << endl;
    cout << "New game? Press anything to continue" << endl;
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
    string rank[13] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" };

    do{
        while (rank_count < 13)
        {
            card[card_count].rank = rank[rank_count];
            card[card_count].rank_num = rank_count;
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
//draws a card from the deck
//
//
void draw(card_struct card[], int num_cards, int &count, int &bcount)
{
    int draw = 0;
    //initial draw

    for (draw = 0; draw < num_cards; draw++)
    {
        
        card[card[count].shuffle] = card[card[bcount].shuffle];
        card[count].hand = card[count].shuffle;
        cout << "            " << card[card[count].hand].full_name << endl;
        count++;
        bcount++;
    }

}

//
//
//sorts the cards based on the rank of the cards
//
//
void  BubbleSort(card_struct card[], int count)
{
    int lastpos = count;	//last position to look at this pass
    bool swapmade;       //when true a swap has been made
    int k;
    do
    {
        lastpos--;
        swapmade = false;
        for (k = 0; k<lastpos; k++)
        {
            if (card[card[k].hand].rank_num < card[card[k+1].hand].rank_num)
            {
                swapmade = true;
                Swap(card[card[k].hand], card[card[k+1].hand]);
            }
        }
    } while (swapmade);
}
//
//
//
//
//
void Swap(card_struct &a, card_struct &b)
{
    card_struct temp;
    temp = a;
    a = b;
    b = temp;
} 