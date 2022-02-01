#include "functions.h"



//Type of suits
const char suit_type[NUM_OF_SUIT_TYPES][MAX_NUM_OF_CHARACTERS_PER_SUIT] = { "Spades","Hearts","Clubs","Diamonds" };
//Type of rank
const char rank_type[NUM_OF_RANK_TYPES][MAX_NUM_OF_CHARACTERS_PER_Rank] = { "Ace","2","3","4","5","6","7","8","9","10","Jack","Queen","King" };

void init_card_list(Card** p_card_list)
{
	//Initiliaze list
	size_t i;
	size_t j;

	//s_card* temp=NULL;
	uint8_t get_rank_number = 0;
	uint8_t u8_sr_type = 0;
	Card* temp = NULL;

	for (i = 0; i < NUM_OF_SUIT_TYPES; i++)
	{
		for (j = 0; j < NUM_OF_RANK_TYPES; j++)
		{
			//Instantiate uint8_t suit and rank holder to 0 --> 0 0 0 0 0 0 0 0
			u8_sr_type = 0;
			get_rank_number = 0;

			//Get rank number based on its type  --> uint8_t
			get_rank_number = calc_rank_number(rank_type[j]);

			if (get_rank_number == 0)
			{
				//Function error
				return;
			}

			//Add suit and rank bits
			u8_sr_type |= i;//Last 2 bits (suit)
			u8_sr_type |= get_rank_number;//Next 4 bits (ranks)

			temp = NULL;

			//Create a node , That we will add to the end of the list
			temp = (Card*)malloc(sizeof(Card));
			if (temp == NULL)
			{
				//Return allocating error
				return;
			}
			//Assign node's value
			temp->sr_type = u8_sr_type;
			temp->next = NULL;

			//Add card to end of the list
			add_last(p_card_list, temp);
		}
	}
}

void add_last(Card** card_list, Card* card)
{
	Card* ptr = NULL;
	if ((*card_list) == NULL)
	{
		//If list is NULL = This is our first node
		(*card_list) = card;
	}
	else
	{
		//The list is not NULL = We will add our node to end
		//First we will iterate to the end of the list
		ptr = (*card_list);
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		//Second we will add our created node to the end of the list
		ptr->next = card;
		ptr->next->next = NULL;
	}

}

uint8_t calc_rank_number(const char* get_rank)
{
	//Get rank number mask: in hex -> based on rank type

	//Default value
	uint8_t return_val = 0;

	if (strcmp(get_rank, rank_type[0]) == 0)
	{
		//Ace == 1
		//D D 0 0 | 0 1 D D
		return_val = 0x4;
	}
	else if (strcmp(get_rank, rank_type[1]) == 0)
	{
		//2
		//D D 0 0 | 1 0 D D
		return_val = 0x8;
	}
	else if (strcmp(get_rank, rank_type[2]) == 0)
	{
		//3
		//D D 0 0 | 1 1 D D
		return_val = 0xC;
	}
	else if (strcmp(get_rank, rank_type[3]) == 0)
	{
		//4
		//D D 0 1 | 0 0 D D
		//1 0
		return_val = 0x10;
	}
	else if (strcmp(get_rank, rank_type[4]) == 0)
	{
		//5
		//D D 0 1 | 0 1 D D
		//1 4
		return_val = 0x14;
	}
	else if (strcmp(get_rank, rank_type[5]) == 0)
	{
		//6
		//D D 0 1 | 1 0 D D
		//1 8
		return_val = 0x18;
	}
	else if (strcmp(get_rank, rank_type[6]) == 0)
	{
		//7
		//D D 0 1 | 1 1 D D
		//1 C
		return_val = 0x1C;
	}
	else if (strcmp(get_rank, rank_type[7]) == 0)
	{
		//8
		//D D 1 0 | 0 0 D D
		//2 0
		return_val = 0x20;
	}
	else if (strcmp(get_rank, rank_type[8]) == 0)
	{
		//9
		//D D 1 0 | 0 1 D D
		//2 4
		return_val = 0x24;
	}
	else if (strcmp(get_rank, rank_type[9]) == 0)
	{
		//10
		//D D 1 0 | 1 0 D D
		//2 8
		return_val = 0x28;
	}
	else if (strcmp(get_rank, rank_type[10]) == 0)
	{
		//Jack
		//D D 1 0 | 1 1 D D
		//2 C
		return_val = 0x2C;
	}
	else if (strcmp(get_rank, rank_type[11]) == 0)
	{
		//Queen
		//D D 1 1 | 0 0 D D
		//3 0
		return_val = 0x30;
	}
	else//12
	{
		//King
		//D D 1 1 | 0 1 D D
		//3 4
		return_val = 0x34;
	}
	return return_val;
}

int calc_rank_index(uint8_t rank)
{
	switch (rank)
	{
	case 0x4:
		return 0;
		break;
	case 0x8:
		return 1;
		break;
	case 0xC:
		return 2;
		break;
	case 0x10:
		return 3;
		break;
	case 0x14:
		return 4;
		break;
	case 0x18:
		return 5;
		break;
	case 0x1C:
		return 6;
		break;
	case 0x20:
		return 7;
		break;
	case 0x24:
		return 8;
		break;
	case 0x28:
		return 9;
		break;
	case 0x2C:
		return 10;
		break;
	case 0x30:
		return 11;
		break;
	default://0x34
		return 12;
		break;
	}

}

int get_amount_based_on_rank_index(int index)
{
	switch (index)
	{
	case 0://Ace
		return 1;
		break;
	case 1://2
		return 2;
		break;
	case 2://3
		return 3;
		break;
	case 3://4
		return 4;
		break;
	case 4://5
		return 5;
		break;
	case 5://6
		return 6;
		break;
	case 6://7
		return 7;
		break;
	case 7://8
		return 8;
		break;
	case 8://9
		return 9;
		break;
	case 9://10
		return 10;
		break;
	default://Jack/Queen/King ==10
		return 10;
		break;
	}

}

int get_cards_value(Card* card_list)
{
	//Instantiate value
	int value = 0;
	int rank_index;
	Card* ptr = NULL;
	//Instantiate rank mask -> 0 0 1 1 1 1 0 0
	uint8_t rank_mask = 0x3C;
	//Instantiate rank value
	uint8_t rank_val = 0x0;
	//Flag that indicates if there is at least 1 ACE
	//default->0 (false) 
	int is_ace = 0;

	ptr = card_list;
	while (ptr != NULL)
	{
		rank_val = 0x0;

		//Get rank from uint8_t value
		rank_val = ((ptr->sr_type) & (rank_mask));
		//get the index when the value(rank) is stored
		rank_index = calc_rank_index(rank_val);
		//Append to value based on the index
		value += get_amount_based_on_rank_index(rank_index);
		//Check if the value is ACE
		if ((get_amount_based_on_rank_index(rank_index)) == 1)
		{
			is_ace = 1;
		}
		ptr = ptr->next;
	}

	//Check if ACE flag is on
	if (is_ace)
	{
		//Hand contains at least 1 ACE
		//we add 10 to the value
		value += 10;
		//Check if the value is more than 21 after the adding
		if (value > BLACKJACK)
		{
			//If so,We subtruct the 10
			value -= 10;
		}
	}

	//Return the calculated value
	return value;
}

void show_cards(Card* card_list)
{
	Card* ptr = NULL;
	//Instantiate suit_mask -> 0 0 0 0 0 0 1 1
	uint8_t suit_mask = 0x3;
	//Instantiate rank_mask -> 0 0 1 1 1 1 0 0
	uint8_t rank_mask = 0x3C;
	uint8_t suit_val = 0x0;
	uint8_t rank_val = 0x0;

	//Point to first node of the list
	ptr = card_list;
	while (ptr != NULL)
	{
		suit_val = 0x0;
		rank_val = 0x0;

		//Print node's value
		//Get suit from uint8_t value
		suit_val = ((ptr->sr_type) & (suit_mask));
		//Get rank from uint8_t value
		rank_val = ((ptr->sr_type) & (rank_mask));
		if ((ptr->next) == NULL)
		{
			//print without comma at the end
			printf("%s of %s ", rank_type[calc_rank_index(rank_val)], suit_type[suit_val]);
		}
		else
		{
			printf("%s of %s, ", rank_type[calc_rank_index(rank_val)], suit_type[suit_val]);
		}
		//printf("%" PRId8 " ",ptr->sr_type);
		ptr = ptr->next;
	}
	printf("\n");

}

void show_dealer_cards(Card* card_list)
{
	Card* ptr = NULL;
	int card_counter = 0;
	//Instantiate suit_mask -> 0 0 0 0 0 0 1 1
	uint8_t suit_mask = 0x3;
	//Instantiate rank_mask -> 0 0 1 1 1 1 0 0
	uint8_t rank_mask = 0x3C;
	uint8_t suit_val = 0x0;
	uint8_t rank_val = 0x0;

	//Point to first node of the list
	ptr = card_list;
	while (ptr != NULL)
	{
		suit_val = 0x0;
		rank_val = 0x0;

		//Print node's value
		//Get suit from uint8_t value
		suit_val = ((ptr->sr_type) & (suit_mask));
		//Get rank from uint8_t value
		rank_val = ((ptr->sr_type) & (rank_mask));
		if (card_counter == 1)
		{
			//Second card is hidden
			printf("%s ", "????????");
		}
		else
		{
			printf("%s of %s, ", rank_type[calc_rank_index(rank_val)], suit_type[suit_val]);
		}
		ptr = ptr->next;
		card_counter++;
	}
	printf("\n");

}


Card* remove_card(Card** p_card_list, int position)
{
	Card* ptr = NULL;
	Card* ptr_next = NULL;
	Card* first_node_holder = NULL;

	int current_pos = 1;

	ptr = (*p_card_list);
	//Stay static -> in case we need to remove the first card of the list
	first_node_holder = ptr;
	ptr_next = (*p_card_list)->next;

	//Remove the first node of the list
	if (position == 0)
	{
		//make the second node as the current head of the list
		(*p_card_list) = ptr->next;
		return first_node_holder;
	}

	while (ptr_next != NULL)
	{
		if (current_pos == position)
		{
			//we found our node
			//connect the node before to the next node of our found card
			ptr->next = ptr_next->next;
			//get the card back
			return ptr_next;
		}

		//move to next node
		current_pos++;
		ptr = ptr->next;
		ptr_next = ptr_next->next;
	}

	//Card has not been found (err)
	return NULL;
}

Card* draw_card(Card** deck, Card** target_list, int* current_cards_in_deck)
{
	int get_random_index;
	Card* get_card_at_index = NULL;

	//Get random index from the current cards in the deck
	get_random_index = rand() % (*current_cards_in_deck);

	//Remove the card from the deck
	//And get it into a variable
	get_card_at_index = remove_card(deck, get_random_index);

	if (get_card_at_index == NULL)
	{
		//Error getting card
		return NULL;
	}
	get_card_at_index->next = NULL;
	//Subtruct the deck counter by 1
	*current_cards_in_deck = (*current_cards_in_deck) - 1;

	//Append the card to the end of the target_list(player_hand/dealer_hand)
	add_last(target_list, get_card_at_index);
	return get_card_at_index;
}

int check_if_valid_bet(int cash, int current_bet, int bet_input)
{
	//return 1->valid bet, 0->cant

	//Check if bet input is more than the cash
	if (bet_input > cash)
	{
		//Err-> Can't bet more than available cash
		printf("Your bet:%d is higher than your cash:%d\n", bet_input, cash);
		return 0;
	}
	//Check if bet input is multiply of 10
	if ((bet_input % 10) != 0)
	{
		//Err-> bet is not multiply of 10
		printf("Your bet:%d must be a multiply of 10\n", bet_input);
		return 0;
	}
	//Check if bet input is 0 and current bet is greater than 0
	if ((bet_input == 0) && (current_bet <= 0))
	{
		//Err-> bet input==0 and current bet==0
		printf("You can't bet on 0 if the current bet is also 0\n");
		return 0;
	}

	//bet input is valid
	return 1;
}

void check_for_continue(int* is_playing, int* cash)
{
	//Flag that holds a value (y/n) if the player wish to continue to gamble
	//default value is no
	char if_bet_again = 'n';

	//Show the player his current cash
	printf("\nPlayer Cash:%d\n", *cash);

	if ((*cash) < 10)
	{
		//cash is less than 10 -- Game Over
		printf("Out of cash to bet. Game Over\n");
		//return 0(false) --> stop playing(/betting)
		(*is_playing) = 0;
	}
	else
	{
		//Clear the buffer
		fseek(stdin, 0, SEEK_END);
		fflush(stdin);
		printf("Do you wish to bet again (y/n): ");
		scanf("%c", &if_bet_again);
		

		//Check answer
		if (if_bet_again == 'y' || if_bet_again == 'Y')
		{
			//player wish to continue 
			//return 1(true) --> continue playing(/betting)
			(*is_playing) = 1;
		}
		else
		{
			//player wish to stop					
			//return 0(false) --> stop playing(/betting)
			(*is_playing) = 0;
		}
	}
	printf("\n");
}

void hit_or_strand(Card** deck, Card** player_hand, Card** dealer_hand, int* cash, int* bet, int* is_playing, int player_cards_value, int* current_cards_in_deck)
{
	//Hit or Stand input
	char hit_stand[6];
	//Instantiate player's cards value with its current cards value
	int calc_player_cards_value = player_cards_value;
	//Flag that indicates a player wants to draw another card
	//default->1 true
	int continue_to_hit = 1;

	while (continue_to_hit)
	{
		//Ask player if he wants to hit or stand
		//Clear the buffer
		//fseek(stdin, 0, SEEK_END);
		printf("Do you wish to hit or stand: ");
		scanf("%s", hit_stand);
		
		//Check player's input
		if ((strcmp(hit_stand, "hit") == 0) || (strcmp(hit_stand, "Hit") == 0) || (strcmp(hit_stand, "HIT") == 0))
		{
			//player wish to "hit"

			//Draw 1 more card into the player hand
			draw_card(deck, player_hand, current_cards_in_deck);

			//Calc player cards value
			calc_player_cards_value = get_cards_value(*player_hand);

			//Show player cards
			printf("\nplayer: ");
			show_cards(*player_hand);
			printf("\n");

			//Check if cards value are higher than 21
			if (calc_player_cards_value > BLACKJACK)
			{
				printf("Player bust\n");
				printf("Player lose %d!\n", *bet);
				//set bet back to zero
				(*bet) = 0;
				//Ask the player if he wants to bet again(yes/no)
				check_for_continue(is_playing, cash);
				//exit function
				return;
			}

			//Check if Blackjack
			if (calc_player_cards_value == BLACKJACK)
			{
				printf("Black Jack!\n");
				//Add one and a half the bet to the cash
				(*bet) = ((*bet) * 1.5);
				printf("Player won %d\n", *bet);
				(*cash) = (*cash) + (*bet);
				//Reset bet to back to zero
				(*bet) = 0;
				//Ask the player if he wants to bet again(yes/no)
				check_for_continue(is_playing, cash);
				//exit function
				return;
			}

			//cards value are less than 21
			//"hit" again
			continue_to_hit = 1;
		}
		else
		{
			//player wish to "stand"
			continue_to_hit = 0;

			/*Dealer draw phase*/
			dealer_draw(deck, player_hand, dealer_hand, cash, bet, is_playing, calc_player_cards_value, current_cards_in_deck);
			//Exit function
			return;
		}
	}//End while loop
}

void dealer_draw(Card** deck, Card** player_hand, Card** dealer_hand, int* cash, int* bet, int* is_playing, int calc_player_cards_value, int* current_cards_in_deck)
{
	//Instantiate card value of the dealer
	int calc_dealer_cards_value = 0;
	//Flag that indicates we need to keep drawing cards to dealer
	//default value->1 true
	int continue_dealer_draw = 1;

	//Calc dealer hand		
	calc_dealer_cards_value = get_cards_value(*dealer_hand);

	//Show unhidden card
	printf("\n");
	printf("dealer: ");
	show_cards(*dealer_hand);
	printf("\n");


	//Check if dealer hand is already greater than or equals to 17(threshold)
	if (calc_dealer_cards_value >= DEALER_CARDS_VALUE_THRESHOLD)
	{
		//Check if dealer bust-->greater than 21 (blackjack)
		//or player hand is greater than the dealer
		if ((calc_dealer_cards_value > BLACKJACK) || (calc_player_cards_value > calc_dealer_cards_value))
		{
			printf("Dealer bust\n");
			//add twice the bet to the player cash
			(*bet) *= 2;
			printf("Player won %d\n", *bet);
			(*cash) += (*bet);
			//set bet back to zero
			(*bet) = 0;
			continue_dealer_draw = 0;
			//Ask the player if he wants to bet again(yes/no)
			check_for_continue(is_playing, cash);
			//exit function
			return;
		}
		//check if dealer hand is greater than player hand
		if (calc_dealer_cards_value > calc_player_cards_value)
		{
			printf("Dealer wins\n");
			printf("Player lose %d!\n", *bet);
			//set bet back to zero
			(*bet) = 0;
			continue_dealer_draw = 0;
			//Ask the player if he wants to bet again(yes/no)
			check_for_continue(is_playing, cash);
			//exit function
			return;
		}
		//check if tie
		if (calc_dealer_cards_value == calc_player_cards_value)
		{
			printf("tie\n");
			//bet does not reset back to zero
			continue_dealer_draw = 0;
			//Ask the player if he wants to bet again(yes/no)
			check_for_continue(is_playing, cash);
			//exit function
			return;
		}

	}

	//Dealer gonna draw cards until he wins over a player of bust
	//dealer hand must be 17 or more
	do
	{
		//Draw 1 more card into the dealer hand
		draw_card(deck, dealer_hand, current_cards_in_deck);

		//Calc dealer hand		
		calc_dealer_cards_value = get_cards_value(*dealer_hand);

		//Show dealer's cards
		printf("\n");
		printf("dealer: ");
		show_cards(*dealer_hand);
		printf("\n");

		//Check if dealer hand is above or equals DEALER_CARDS_VALUE_THRESHOLD=17
		if (calc_dealer_cards_value >= DEALER_CARDS_VALUE_THRESHOLD)
		{
			//dealer hand is 17 or more

			//Check if dealer bust-->greater than 21 (blackjack)
			//or player hand is greater than the dealer
			if ((calc_dealer_cards_value > BLACKJACK) || (calc_player_cards_value > calc_dealer_cards_value))
			{
				printf("Dealer bust\n");
				//add twice the bet to the player cash
				(*bet) *= 2;
				printf("Player won %d\n", *bet);
				(*cash) += (*bet);
				//set bet back to zero
				(*bet) = 0;
				continue_dealer_draw = 0;
				//Ask the player if he wants to bet again(yes/no)
				check_for_continue(is_playing, cash);
				//exit function
				return;
			}

			//check if dealer hand is greater than player hand
			if (calc_dealer_cards_value > calc_player_cards_value)
			{
				printf("Dealer wins\n");
				printf("Player lose %d!\n", *bet);
				//set bet back to zero
				(*bet) = 0;
				continue_dealer_draw = 0;
				//Ask the player if he wants to bet again(yes/no)
				check_for_continue(is_playing, cash);
				//exit function
				return;
			}

			//check if tie
			if (calc_dealer_cards_value == calc_player_cards_value)
			{
				printf("tie\n");
				//bet does not reset back to zero
				continue_dealer_draw = 0;
				//Ask the player if he wants to bet again(yes/no)
				check_for_continue(is_playing, cash);
				//exit function
				return;
			}

		}
		//dealer has not reach 17 yet-->continue to draw another card to the dealer
		continue_dealer_draw = 1;

	} while (continue_dealer_draw);
}

void free_list(Card** p_card_list)
{
	Card* ptr = NULL, * current = NULL;

	if (p_card_list == NULL)
	{
		//List has not been created yet
		return;
	}
	if ((*p_card_list) == NULL)
	{
		//List is empty
		//We will free only the pointer to NULL ref
		free(p_card_list);
		p_card_list = NULL;
		return;
	}

	//ptr Point to next node of the list
	ptr = (*p_card_list)->next;
	//current Point to first node of the list
	current = (*p_card_list);

	while (ptr != NULL)
	{
		free(current);
		current = ptr;
		ptr = ptr->next;
	}
	free(current);
	free(p_card_list);
	p_card_list = NULL;

}


