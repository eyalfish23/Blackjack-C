#include "functions.h"
#include <time.h>


/*This program works on C99 Standard*/



int main(void)
{
	//deck linked list
	Card** deck = NULL;
	//dealer_hand linked list
	Card** dealer_hand = NULL;
	//player_hand linked list
	Card** player_hand = NULL;

	//Instantiate time
	srand(time(NULL));
	//Instantiate cash and bet
	int cash = 1000, bet = 0, bet_input = 0;
	//Variable that holds the current cards in the deck
	int current_cards_in_deck = MAX_NUM_CARDS_IN_A_DECK;
	//Instantiate card value
	int calc_player_cards_value = 0;
	//default 1->continue to play, 0->exit
	int is_playing = 1;

	do
	{
		/*Game Initialization*/

		//Release any memory from pervious bet (if any)
		//free deck
		free_list(deck);
		//free dealer_hand
		free_list(dealer_hand);
		//free player_hand
		free_list(player_hand);

		//Init deck,dealer_hand and player_hand
		deck = (Card**)malloc(sizeof(Card*));
		dealer_hand = (Card**)malloc(sizeof(Card*));
		player_hand = (Card**)malloc(sizeof(Card*));
		//first element==NULL
		(*deck) = NULL;
		(*dealer_hand) = NULL;
		(*player_hand) = NULL;

		//Load deck with 52 cards
		init_card_list(deck);
		//deck is full at start
		current_cards_in_deck = MAX_NUM_CARDS_IN_A_DECK;
		//Reset bet input
		bet_input = 0;

		//Start playing
		while (is_playing)
		{
			//While true --> we continue to play

			/*Betting phase*/

			//Print player's current cash and bet
			printf("Player Cash:%d\tPlayer Bet:%d\n\n", cash, bet);

			//Get bet value
			//Clear the buffer
			fflush(stdin);
			printf("How much do you want to bet? ");
			scanf("%d", &bet_input);

			//Check if bet is valid
			if (check_if_valid_bet(cash, bet, bet_input) == 0)
			{
				//Bet input is invalid

				//Set flag to 0 --> stop playing
				is_playing = 0;
				//Exit
				break;
			}
			//Bet is valid
			//Deduct the bet from the total cash
			cash -= bet_input;
			//Add the bet_input(value) to the total bet
			bet += bet_input;

			/*Initial Deal phase*/

			//Draw 2 cards into the dealer hand
			draw_card(deck, dealer_hand, &current_cards_in_deck);
			draw_card(deck, dealer_hand, &current_cards_in_deck);
			//Draw 2 cards into the player hand
			draw_card(deck, player_hand, &current_cards_in_deck);
			draw_card(deck, player_hand, &current_cards_in_deck);

			//Show dealer cards (second one is hidden)
			printf("\n");
			printf("dealer: ");
			show_dealer_cards(*dealer_hand);
			printf("\n");
			//Show player cards
			printf("player: ");
			show_cards(*player_hand);
			printf("\n");


			/*Black Jack*/

			//Calc player cards value
			calc_player_cards_value = 0;
			calc_player_cards_value = get_cards_value(*player_hand);

			//Check if BlackJack==21
			if (calc_player_cards_value == BLACKJACK)
			{
				printf("Black Jack!\n");
				//Add one and a half the bet to the cash
				bet *= 1.5;
				printf("Player won %d\n", bet);
				cash += bet;
				//Reset bet to back to zero
				bet = 0;
				bet_input = 0;
				check_for_continue(&is_playing, &cash);
				//The game will continue or stop according to player's answer and his cash
				break;
			}
			else
			{
				//Not a BlackJack - continue

				/*Hit or Stand Phase*/
				hit_or_strand(deck, player_hand, dealer_hand, &cash, &bet, &is_playing, calc_player_cards_value, &current_cards_in_deck);
				break;
			}

		}
	} while (is_playing);//Continue while is_playing(flag) is true



	/*End*/
	printf("\nThank you for playing\n");
	printf("Player Cash:%d\n", cash);

	//Release memory and exit
	//free deck
	free_list(deck);
	//free dealer_hand
	free_list(dealer_hand);
	//free player_hand
	free_list(player_hand);
	return 0;
}


