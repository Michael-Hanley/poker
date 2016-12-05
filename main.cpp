#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>

using namespace std;

const int NUM_CARDS = 52; //number of cards
const int NUM_RANK = 13; // number of ranks
const int HAND = 7; // number of cards in each persons hand
const int STRAIGHT = 5; // number of cards in a straight
const int SUITE = 4; // number of suites
const int FLUSH = 5; // number of cards in a flush
const int SUITE_ARRAY[SUITE] = { 0, 1, 2, 3 }; //numerical representation of the 4 suites
const string SUITE_NAME[4] = { "Spades", "Clubs", "Hearts", "Diamonds" }; // names of suites
const string RANK_NUM[NUM_RANK] = { "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace" }; //actural names of the ranks

void clear();

class Deck {
private:

protected:
	struct card_struct {
		string rank;
		string suite;
		string full_name;
		int shuffle;
		int count;
		int hand;
		int rank_num;
		int suite_num;
	};
	static int count;
	card_struct card[NUM_CARDS];
	static unsigned seed;

public:

	Deck()
	{
		srand((unsigned int)time(0));
		count = 0;
		get_cards();
		shuffle();
	}

	void get_cards();
	void shuffle();
};

class PlayerHands : public Deck
{
	int hand[HAND];
	string answer;
	int hand_power;
	int straight[HAND];
	int straight_hand_count;
	int straight_start;
	int amount_of_chips;
public:

	PlayerHands() : Deck(){}

	void draw_main();
	void finish_hand();
	void hand_value();
	void bubble_sort();
	void Swap(int k);
	void match_check();
	void straight_check();
	void flush_check();

	void show_hand() // shows the first two cards given to the player
	{
		cout << "Your Hand:" << endl;
		cout << card[hand[0]].full_name << endl;
		cout << card[hand[1]].full_name << endl << endl;
	}
	void show_flop() // shows the three cards the player can use that are on the table
	{
		cout << "The Flop:" << endl;
		for(int i = 2; i < 5; i++)
			cout << card[hand[i]].full_name << endl;

		cout << endl;
	}
	void show_turn() // shows the next card that is placed on the table
	{
		cout << "The Turn:" << endl;
		cout << card[hand[5]].full_name << endl << endl;
	}
	void show_river() // shows the last card placed on the river
	{
		cout << "The River:" << endl;
		cout << card[hand[6]].full_name << endl << endl;
	}
	void show_answer() // shows the most powerful hand the places possess
	{
		cout << answer << endl;
	}
	void show_chips() // couts the amount of chips the player owns 
	{
		cout << "Your Chips: $" << amount_of_chips << endl;
	}
	int get_chips() //returns the amount of chips the player has
	{
		return amount_of_chips;
	}
	void set_chips(int current_chips) //sets the players chips to the incoming parameter
	{
		amount_of_chips = current_chips;
	}
	void won_hand(int pot) //adds the amount you won to your chip count
	{
		amount_of_chips += pot;
	}
	void place_bet(int bet) //subtracts the chips you bet
	{
		amount_of_chips -= bet;
	}
	int get_hand_power() //returns the numerical power of your hand
	{
		return hand_power;
	}
};
int Deck::count = 0;
int player_actions(PlayerHands&);
void who_wins(PlayerHands&, PlayerHands&, int pot_amount);
int main()
{
	int j = 0;
	int player_money = 10000;
	int pot_amount;
	int computer_money = 10000;
	PlayerHands *player;

	cout << "Press enter to start a new game." << endl;


	do {
		cin.clear();
		cin.ignore(1000, '\n');
		clear();
		player = new PlayerHands[2];
		for (int i = 0; i < 2; i++)
			player[i].draw_main();

		for (int i = 0; i < 2; i++)
			player[i].finish_hand();


		if (player_money > 0)
			player[1].set_chips(player_money);

		pot_amount = player_actions(player[1]);

		clear();
		player[1].show_chips();
		cout << "-------------------------------------------------" << endl << endl;
		cout << "Amount in the pot: " << pot_amount << endl << endl;
		cout << "--------------------Your Hand--------------------" << endl << endl;
		player[1].show_hand();
		player[1].show_flop();
		player[1].show_turn();
		player[1].show_river();
		player[1].show_answer();


		for (int i = 0; i < 2; i++)
			player[i].hand_value();


		player[1].show_answer();
		cout << "-------------------------------------------------" << endl;
		who_wins(player[1], player[0], pot_amount);
		player_money = player[1].get_chips();
		computer_money = player[0].get_chips();


		cin.clear();


		cin >> j;
		delete[] player;
	} while (j != 1);
}
//
//
//runs through the game and allows the player to bet
//
//
int player_actions(PlayerHands &player)
{
	int bet;
	int pot_amount = 0; 

	for (int i = 0; i < 4; i++)
	{
		player.show_chips();

		cout << "-------------------------------------------------" << endl << endl;
		cout << "Amount in the pot: " << pot_amount << endl << endl;
		cout << "--------------------Your Hand--------------------" << endl << endl;

		player.show_hand();

			if(i > 0)
				player.show_flop();
			if (i > 1)
				player.show_turn();
			if(i > 2)
				player.show_river();


			cout << "-------------------------------------------------" << endl;
		cout << "Please enter how much you would like to bet, enter 0 to pass: ";

		//bet validation
		do {
			cin >> bet;
			if (bet < 0)
				cout << "Please enter a number greater than -1" << endl; 
		} while (bet < 0);

		pot_amount += bet;
		player.place_bet(bet);
		cin.clear();
		cin.ignore(1000, '\n');
		clear();
	}
	return pot_amount;

}

void who_wins(PlayerHands &player, PlayerHands &computer_player, int pot_amount)
{
	int player_power = player.get_hand_power();
	int computer_power = computer_player.get_hand_power();
	int win_action = 0;


	if (player_power < computer_power)
	{
		cout << "Computer Wins!" << endl;
		computer_player.won_hand(pot_amount);
	}
	if (player_power > computer_power)
	{
		cout << "Player Wins!" << endl;
		player.won_hand(pot_amount);
	}
	if (player_power == computer_power)
	{
		cout << "Draw! split pot" << endl;
		player.won_hand(pot_amount / 2);
		computer_player.won_hand(pot_amount / 2);
	}

}

//
//occupies the struct with 52 playing cards
//
//
void Deck::get_cards()
{
	int card_count = 0;
	int suite_count = 0;
	int rank_count = 0;
	do {
		while (rank_count < NUM_RANK)
		{
			card[card_count].rank = RANK_NUM[rank_count];
			card[card_count].rank_num = rank_count;
			card[card_count].suite = SUITE_NAME[suite_count];
			card[card_count].suite_num = suite_count;
			card[card_count].full_name = card[card_count].rank + " of " + card[card_count].suite;
			card[card_count].count = card_count;
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
void Deck::shuffle()
{
	bool swapmade = false;
	int *temp;
	temp = new int[NUM_CARDS];
	int card_num = 0;
	int check_num = 0;
	for (card_num = 0; card_num < NUM_CARDS; card_num++)
	{
		card[card_num].shuffle = rand() % NUM_CARDS;
		temp[card_num] = card[card_num].shuffle;
		do {
			swapmade = false;
			for (check_num = 0; check_num < NUM_CARDS; check_num++)
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
	delete[] temp;
}
//
//
//Give each player the remaining 5 cards that will go into play
//
//
void PlayerHands::finish_hand()
{
	for (int i = 2; i < HAND; i++) {
		hand[i] = card[count].shuffle;
		count++;
	}
	count -= 5;
}
//
//
//Calculates the value of your hand
//
//
void PlayerHands::hand_value()
{
	int hand_count = 0;
	bubble_sort();
	match_check();

	if (answer != "Full House" && answer != "Four of a Kind!!")
	{
		straight_check();
	}
	flush_check();


}
//
//
//sorts the cards based on the rank of the cards
//
//
void  PlayerHands::bubble_sort()
{
	int lastpos = HAND;	//last position to look at this pass
	bool swapmade;       //when true a swap has been made
	int k = 0;
	do
	{
		lastpos--;
		swapmade = false;
		for (k = 0; k < lastpos; k++)
		{
			if (card[hand[k]].rank_num < card[hand[k + 1]].rank_num)
			{
				swapmade = true;
				Swap(k);
			}
		}
	} while (swapmade);
}
//
//
//swaps two cards
//
//
void PlayerHands::Swap(int k)
{
	int temp = hand[k];
	hand[k] = hand[k + 1];
	hand[k + 1] = temp;
}
//
//
//beginning 2 cards each player recieves
//
//
void PlayerHands::draw_main()
{
	for (int i = 0; i < 2; i++)
	{
		hand[i] = card[count].shuffle;
		count++;
	}
}
//
//
// Checks for High card through three of a kind, Full House, And Four of a Kind
//
//
void PlayerHands::match_check()
{
	int pair = 0;     //counter representing number of pairs
	int three = 0;    //counter representing number of three of a kinds
	int four = 0;     //counter representing number of four of a kinds
	int *rank_count;
	rank_count = new int[7];  // Array for the rankings of the ranks of the cards
	int k = 0;
	int s_count = 0;
	int x = 0;
	do {
		while (x < HAND)
		{
			if (card[hand[k]].rank_num == card[hand[x]].rank_num)
				s_count++;
			
			x++;
		}
		rank_count[k] = s_count;
		s_count = 0;
		x = 0;
		k++;
	} while (k < HAND);
	k = 0;
	while (k < HAND)
	{
		if (rank_count[k] == 2)
			pair++;
		if (rank_count[k] == 3)
			three++;
		if (rank_count[k] == 4)
			four++;
		k++;
	}
	k = 0;
	answer = card[hand[k]].full_name;
	hand_power = 0;
	if (pair == 2)
	{
		answer = "Pair";
		hand_power = 1;
	}
	if (pair >= 4)
	{
		answer = "Two Pair!";
		hand_power = 2;
	}
	if (three == 3)
	{
		answer = "Three of a kind!";
		hand_power = 3;
	}
	if ((three > 2 && pair >= 2) || three >= 6)
	{
		answer = "Full House";
		hand_power = 6;
	}
	if (four == 4)
	{
		answer = "Four of a Kind!!";
		hand_power = 7;
	}


	delete[] rank_count;
}
//
//
//Checks to see if cards are in descending order
//
//
void PlayerHands::straight_check()
{
	int k = 0;
	int s_count = 0;
	while (k < (HAND - 1))
	{
		//compares the rank of the first card to that of the next
		//increments if the rank of the first is eaqual to the rank of the next plus 1
		if (card[hand[k]].rank_num == (card[hand[k + 1]].rank_num + 1))
			s_count++;
		//resets count if descending order is broken.
		if (card[hand[k]].rank_num != (card[hand[k + 1]].rank_num + 1) &&
			card[hand[k]].rank_num != (card[hand[k + 1]].rank_num) && s_count < (STRAIGHT - 1))
			s_count = 0;
		
		k++;
	}
	if (s_count >= (STRAIGHT - 1))
	{
		answer = "Straight";
		hand_power = 4;
	}
}
//
//
//
//
//
void PlayerHands::flush_check()
{
	int k = 0;                         //counter
	int x = 0;                         //counter
	int f_count = 0;                   //count of the pairs of matching suits
	bool flush = false;
	int sf_count = 0;
	string temp_answer;
	
	do {
		while (x < HAND)
		{
			if (SUITE_ARRAY[k] == card[hand[x]].suite_num)
				f_count++;
			
			x++;
		}
		if (f_count < FLUSH)
			f_count = 0;
		else
		{
			flush = true;
			break;
		}
		x = 0;
		k++;
	} while (k < SUITE);

	if (flush == true)
		temp_answer = "Flush";

	if ((temp_answer == "Flush" && answer != "Full House") || (temp_answer == "Flush" && answer != "Four of a Kind!!"))
	{
		answer = temp_answer;
		hand_power = 5;
	}

	if (answer == "Flush")
	{
		int *sflush;
		sflush = new int[HAND];
		x = 0;
		for (int i = 0; i < HAND; i++) {
			if (SUITE_ARRAY[k] == card[hand[i]].suite_num)
			{
				sflush[x] = hand[i];
				x++;
			}
		}
		for (int i = 0; i < (x - 1); i++)
		{
			if (card[sflush[i]].rank_num == (card[sflush[i + 1]].rank_num + 1))
				sf_count++;
		}
		if (sf_count >= (STRAIGHT - 1))
		{
			answer = "Straight Flush!";
			hand_power = 8;
			if (card[sflush[0]].rank_num == 12 && card[sflush[1]].rank_num == 11 &&
				card[sflush[2]].rank_num == 10 && card[sflush[3]].rank_num == 9
				&& card[sflush[4]].rank_num == 8)
			{
				answer = "ROYAL FLUSH!";
				hand_power = 9;
			}
		}
		delete[] sflush;
	}
}

void clear()
{
#ifdef _WIN32
	system("cls"); //windows
#else
	system("clear"); //linux
#endif
}




