#include<cstdlib>
#include<iostream>
#include<iomanip>
#include<string>
#include<ctime>

using namespace std;

const int STARTING_CASH = 1000; //ammount each player starts with
const int SHORT_PAUSE = 1000;
const int LONG_PAUSE = 3000;
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
void delay(int);
void computer_delays();

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

	PlayerHands() : Deck() {}

	void draw_main();
	void finish_hand();
	void hand_value();
	void bubble_sort();
	void Swap(int k);
	void match_check();
	void straight_check();
	void flush_check();

	void show_hand(int i) // shows the first two cards given to the player
	{
		cout << "Your Hand:" << endl;
		if (i == 0) // i represents the dealer action, 0 = dealing the hand
			delay(SHORT_PAUSE);
		cout << card[hand[0]].full_name << endl;
		if (i == 0)
			delay(SHORT_PAUSE);
		cout << card[hand[1]].full_name << endl << endl;
		if (i == 0)
			delay(SHORT_PAUSE);
	}
	void show_flop(int x) // shows the three cards the player can use that are on the table
	{
		cout << "The Flop:" << endl;
		for (int i = 2; i < 5; i++)
		{
			if (x == 1) // x represents the dealer action, 1 = dealing the flop
				delay(SHORT_PAUSE);
			cout << card[hand[i]].full_name << endl;
		}
		if (x == 1)
			delay(SHORT_PAUSE);
		cout << endl;
	}
	void show_turn(int i) // shows the next card that is placed on the table
	{
		cout << "The Turn:" << endl;
		if (i == 2)// i represents the dealer action, 2 = Turn
			delay(SHORT_PAUSE);
		cout << card[hand[5]].full_name << endl << endl;
		if (i == 2)
			delay(SHORT_PAUSE);
	}
	void show_river(int i) // shows the last card placed on the river
	{
		cout << "The River:" << endl;
		if (i == 3)// i represents the dealer action, 3 = River
			delay(SHORT_PAUSE);
		cout << card[hand[6]].full_name << endl << endl;
		if (i == 3)
			delay(SHORT_PAUSE);
	}
	void show_player_answer() // shows the most powerful hand the places possess
	{
		cout << "Players Hand: " << answer << endl;
	}
	void show_computer_answer() // shows the most powerful hand the places possess
	{
		cout << "Computer Hand: " << answer << endl;
	}
	void show_chips() // couts the amount of chips the player owns 
	{
		cout << "Your Chips: $" << amount_of_chips << endl;
	}
	void show_computer_chips() // couts the amount of chips the computer owns
	{
		cout << "Computer Chips: $" << amount_of_chips << endl;
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
	int get_intial_hand() //figures out the power of the computers first two cards. MAX VALUE = 24
	{
		return card[hand[0]].rank_num + card[hand[1]].rank_num;
	}
	int get_flop_power() //figures out the power of the computers first five card. MAX VALUE = 59
	{
		return card[hand[0]].rank_num + card[hand[1]].rank_num + card[hand[2]].rank_num + card[hand[3]].rank_num + card[hand[3]].rank_num;
	}
	int get_turn_power() //figures out the power of the computers first five card. MAX VALUE = 70
	{
		return card[hand[0]].rank_num + card[hand[1]].rank_num + card[hand[2]].rank_num + card[hand[3]].rank_num + card[hand[3]].rank_num + card[hand[4]].rank_num;
	}
	int get_river_power() //figures out the power of the computers first five card. MAX VALUE = 81
	{
		return card[hand[0]].rank_num + card[hand[1]].rank_num + card[hand[2]].rank_num + card[hand[3]].rank_num + card[hand[3]].rank_num + card[hand[4]].rank_num + card[hand[5]].rank_num;
	}
};
int Deck::count = 0;
int player_actions(PlayerHands&, PlayerHands&, bool&);
void who_wins(PlayerHands&, PlayerHands&, int pot_amount);
int player_bet_choices(PlayerHands);
int main()
{
	int d = 0;
	int player_money = STARTING_CASH;
	int pot_amount;
	int computer_money = STARTING_CASH;
	bool end_loop = false;
	bool fold = false;
	PlayerHands *player;

	cout << "Press enter to start a new game." << endl;

	do {
		cin.ignore(1000, '\n');
		clear();
		cout << "\a";
		player = new PlayerHands[2];
		for (int i = 0; i < 2; i++)
			player[i].draw_main();

		for (int i = 0; i < 2; i++)
			player[i].finish_hand();

		if (player_money > 0)
		{
			player[1].set_chips(player_money);
			player[0].set_chips(computer_money);
		}

		pot_amount = player_actions(player[1], player[0], fold);
		if (fold == false)
		{
			player[1].show_chips();
			player[0].show_computer_chips();
			cout << "-------------------------------------------------" << endl << endl;
			cout << "Amount in the pot: $" << pot_amount << endl << endl;
			cout << "--------------------Your Hand--------------------" << endl << endl;
			player[1].show_hand(1);
			player[1].show_flop(0);
			player[1].show_turn(1);
			player[1].show_river(1);

			for (int i = 0; i < 2; i++)
				player[i].hand_value();

			cout << "Press enter to see who wins!" << endl << endl;
			cin.ignore(1000, '\n');

			player[1].show_player_answer();
			player[0].show_computer_answer();

			cout << "-------------------------------------------------" << endl;
			who_wins(player[1], player[0], pot_amount);
		}
		if (fold == true)
			player[0].won_hand(pot_amount);

		player_money = player[1].get_chips();
		computer_money = player[0].get_chips();

		cin.clear();
		if (player_money > 0)
		{
			cout << "Another Round? Press 1 to continue, 0 to exit" << endl;
			cin >> d;
		}
		if (d == 0 || player_money <= 0)
		{
			end_loop = true;
		}
		cin.clear();
		delete[] player;
	} while (end_loop == false);
	clear();
	cin.clear();
	cin.ignore(1000, '\n');
	cout << "--------------------GAME OVER--------------------\a" << endl << endl;
	cin.clear();
	cin.ignore(1000, '\n');
}
//
//
//runs through the game and allows the player to bet
//
//
int player_actions(PlayerHands &player, PlayerHands &computer_player, bool &fold)
{
	int player_bet = 0;
	int computer_bet = 0;
	int pot_amount = 0;
	bool correct_bet = false;
	bool out_of_chips = false;
	int computer_power = 0;
	bool dealer_action = true;
	fold = false;
	for (int i = 0; i < 4; i++)
	{
		player.show_chips();
		cout << endl;
		computer_player.show_computer_chips();
		cout << "-------------------------------------------------" << endl << endl;
		cout << "Amount in the pot: $" << pot_amount << endl << endl;
		if (i > 0)
			cout << "Computer Bet: $" << computer_bet << endl;
		cout << "--------------------Your Hand--------------------" << endl << endl;
		player.show_hand(i);
		if (i > 0)
		{
			if (i == 1)
			{
				cout << "Press enter to show next card." << endl;
				cin.ignore(1000, '\n');
			}
			player.show_flop(i);
		}
		if (i > 1)
		{
			if (i == 2)
			{
				cout << "Press enter to show next card." << endl;
				cin.ignore(1000, '\n');
			}
			player.show_turn(i);
		}
		if (i > 2)
		{
			if (i == 3)
			{
				cout << "Press enter to show next card." << endl;
				cin.ignore(1000, '\n');
			}
			player.show_river(i);
		}
		cout << "-------------------------------------------------\a" << endl;
		player_bet = player_bet_choices(player);
		if (player_bet == -1)
		{
			fold = true;
			player_bet = 0;
		}
		if (fold == true)
			i = 4;
		player.place_bet(player_bet);
		if (fold == false)
		{
			computer_delays();
			if (i == 0)
			{
				computer_power = computer_player.get_intial_hand();
				if (computer_power < 5)
				{
					computer_bet = 0;
				}
				if (computer_power >= 5 && computer_power <= 10)
				{
					computer_bet = 25;
				}
				if (computer_power >= 11 && computer_power <= 16)
				{
					computer_bet = 50;
				}
				if (computer_power >= 17 && computer_power <= 24)
				{
					computer_bet = 100;
				}
			}
			if (i == 1)
			{
				computer_power = computer_player.get_flop_power();
				if (computer_power < 10)
				{
					computer_bet = 0;
				}
				if (computer_power >= 10 && computer_power <= 22)
				{
					computer_bet = 25;
				}
				if (computer_power >= 23 && computer_power <= 40)
				{
					computer_bet = 50;
				}
				if (computer_power >= 41 && computer_power <= 59)
				{
					computer_bet = 100;
				}
			}
			if (i == 2)
			{
				computer_power = computer_player.get_turn_power();
				if (computer_power < 20)
				{
					computer_bet = 0;
				}
				if (computer_power >= 20 && computer_power <= 34)
				{
					computer_bet = 25;
				}
				if (computer_power >= 35 && computer_power <= 54)
				{
					computer_bet = 50;
				}
				if (computer_power >= 55 && computer_power <= 70)
				{
					computer_bet = 100;
				}
			}
			if (i == 3)
			{
				computer_power = computer_player.get_river_power();
				if (computer_power < 30)
				{
					computer_bet = 0;
				}
				if (computer_power >= 30 && computer_power <= 41)
				{
					computer_bet = 25;
				}
				if (computer_power >= 42 && computer_power <= 59)
				{
					computer_bet = 50;
				}
				if (computer_power >= 60 && computer_power <= 81)
				{
					computer_bet = 100;
				}
			}
			if (computer_bet < player_bet)
				computer_bet = player_bet;
			if (computer_player.get_chips() < computer_bet)
				computer_bet = computer_player.get_chips();
			if (computer_bet > player_bet)
			{
				char choice;
				bool correct_choice = false;
				clear();
				int difference = computer_bet - player_bet;
				cout << "The computer has bet " << difference << " More than you." << endl;
				cout << "Would you like to match, raise, or fold ? " << endl;
				do {
					cout << "A = match, B = raise, Q = fold" << endl;
					cin >> choice;
					if (choice == 'a' || choice == 'A')
					{
						player_bet += difference;
						correct_choice = true;
						cin.ignore(1000, '\n');
					}
					if (choice == 'b' || choice == 'B')
					{
						cout << "How much more would you like to bet?" << endl;
						int raise = difference + player_bet_choices(player);
						player_bet += raise;
						player.place_bet(raise);
					}
					if (choice == 'q' || choice == 'Q')
					{
						fold = true;
						i = 4;
					}
				} while (correct_choice = false);
			}

			int bet = computer_bet + player_bet;
			pot_amount += bet;
			if (fold == false)
				computer_player.place_bet(computer_bet);
		}
		cin.clear();
		clear();
	}
	return pot_amount;
}
int player_bet_choices(PlayerHands player)
{
	bool correct_bet = false;
	int player_bet;
	char bet_choice;
	bool out_of_chips = false;
	cout << "Please enter how much you would like to bet, enter 0 to pass" << endl;
	do {
		cout << "A = $25, B = $50, C = $100, q = Fold" << endl;
		cin >> bet_choice;
		if (bet_choice == 'a' || bet_choice == 'A')
		{
			player_bet = 25;
			correct_bet = true;
		}
		if (bet_choice == 'b' || bet_choice == 'B')
		{
			player_bet = 50;
			correct_bet = true;
		}
		if (bet_choice == 'c' || bet_choice == 'C')
		{
			player_bet = 100;
			correct_bet = true;
		}
		if (bet_choice == '0')
		{
			player_bet = 0;
			correct_bet = true;
		}
		if (bet_choice == 'q' || bet_choice == 'Q')
		{
			player_bet = 0;
			correct_bet = true;
			player_bet = -1;
		}
		if (player_bet > player.get_chips())
		{
			correct_bet = false;
			out_of_chips = true;
		}
		if (correct_bet == false)
		{
			clear();
			if (out_of_chips == true)
				cout << "Please enter an ammount less than the amount of chips you have" << endl;
			cout << "Please enter A, B, C, or 0" << endl << endl;
		}
		cin.clear();
		cin.ignore(1000, '\n');
	} while (correct_bet == false);
	return player_bet;
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
//
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
void computer_delays()
{
	clear();
	cout << "Computer is thinking..." << endl;
	delay(LONG_PAUSE);
	cout << endl << "Computer is betting..." << endl;
	delay(LONG_PAUSE);
}

void clear()
{
#ifdef _WIN32
	system("cls"); //windows
#else
	system("clear"); //linux
#endif
}

#ifdef _WIN32
#include <windows.h>
void delay(int pause)
{
	Sleep(pause);
}
#else  /* POSIX */
#include <unistd.h>
void delay(int pause)
{
	usleep(pause);
}
#endif 
