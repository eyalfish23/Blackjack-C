#ifndef  FUNC_H
#define FUNC_H



#pragma warning(disable:4996)
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define BLACKJACK 21
#define DEALER_CARDS_VALUE_THRESHOLD 17
#define MAX_NUM_CARDS_IN_A_DECK 52
#define NUM_OF_SUIT_TYPES 4
#define MAX_NUM_OF_CHARACTERS_PER_SUIT 9
#define NUM_OF_RANK_TYPES 13
#define MAX_NUM_OF_CHARACTERS_PER_Rank 6

/*struct card contains:
	sr_type (suit and rank)
	[0:1] = First 2 bits represent the suit
	[2:5] = Next 4 bits represent the rank
	[6:7] = Last 2 bits are unused
*/

typedef struct Card
{
	uint8_t sr_type;
	struct Card* next;
}Card;



//Functions
uint8_t calc_rank_number(const char* get_rank);
void init_card_list(Card** p_card_list);
void add_last(Card** card_list, Card* card);
void show_cards(Card* card_list);
void show_dealer_cards(Card* card_list);
int get_amount_based_on_rank_index(int index);
void free_list(Card** p_card_list);
Card* draw_card(Card** deck, Card** target_list, int* current_cards_in_deck);
Card* remove_card(Card** p_card_list, int position);
int check_if_valid_bet(int cash, int current_bet, int bet_input);
int get_cards_value(Card* card_list);
int calc_rank_index(uint8_t rank);
void hit_or_strand(Card** deck, Card** player_hand, Card** dealer_hand, int* cash, int* bet, int* is_playing, int player_cards_value, int* current_cards_in_deck);
void dealer_draw(Card** deck, Card** player_hand, Card** dealer_hand, int* cash, int* bet, int* is_playing, int calc_player_cards_value, int* current_cards_in_deck);
void check_for_continue(int* is_playing, int* cash);


#endif



