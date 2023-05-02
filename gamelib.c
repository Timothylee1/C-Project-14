/*!
@file       gamelib.c
@author     Timothy Lee (timothykexin.lee@digipen.edu.sg)
@course     RSE 1201
@section    Assignment 9
@Assignment Implement a solitaire card game.
@date       19/11/2021
@brief      This file contains definitions of the functions del_card, load_game, play_game
			display_game. These functions are executed to mimic the steps to achieve the
			final outcome of the Accrodion Solitaire card game.
			The rules of the game are as follows:
			1) Leftmost available move takes precedence, when there is a choice of making 
			   a three position move or a one position move, choose the former.
			2) If one position move is the only available move, it may be made starting with 
		   	   the leftmost. 
			A standard playing deck is used. The cards from the entire deck are spread out  
			in a single line. Whenever the card matches its immediate neighbor on the left, 
			or matches the third card to the left, it may be moved onto that card. Cards 
			match if they are of the same suit or same rank. After making a move, look to 
			see if it has made additional moves possible. When a card is moved, all the cards 
			in the pile are moved. Gaps left behind are filled by moving all piles on the 
			right of the gap to the left. Deal out the whole pack, combining cards towards 
			the left whenever possible. The game is won if the pack is reduced to a single 
			pile.
			The first character represents the suit, C(lub), D(iamond), H(eart), S(pade).
			The second character represents the rank, 1.9, T for 10, J(ack), Q(ueen), K(ing)

*//*________________________________________________________________________________________*/

#include <stdio.h>
#include "gamelib.h"

/*!
@brief  This function takes a game and an index representing a position of a Card object 
		to delete from the game; deleting means shifting all cards after the indicated 
		position one place to the left to fill the gap caused by the deletion.

@param  index is declared as data type int
		N is defined as an integer literal of 53
		game is a function parameter of struct card which contains char 
		position is a function parameter of unsigned char

@return Nothing 
*//*_______________________________________________________________________________________*/
void del_card(Card game[], CardIndex position)
{
	//replaces positioned card with card on right till end of array 
	//     0         1        2        3         4   
	// | H | 3 ||  D | 3 || S | T || C | K ||'\0'|'\0'| - original sequence of cards
	// | D | 3 ||  D | 3 || S | T || C | K ||'\0'|'\0'| - done by function play_game 
	// | D | 3 ||  S | T || C | K ||'\0'|'\0'| - done by del_card

	for (int index = (int) position; index < N; index++) { 
		game[index].suit = game[index+1].suit;	
		game[index].rank = game[index+1].rank;												//*pointer.structure member

		if((game[index].suit == '0'))														//Last
		    break;
	}

}

/*!
@brief  This function loads a game by reading it from text array(str) into the array of 
		cards(game).

@param  i, num are declared as data type int
		LEN is defined as an integer literal of (3 * 53 +2)
		str is a function parameter of an array of const char
		game is a function parameter of struct card which contains char 

@return Nothing 
*//*_______________________________________________________________________________________*/
void load_game(const char str[], Card game[]) {	
	
	for(int i = 0, num = 0; i < N ; i++, num++){ 											//num++ to ignore whitespace

		game[i].suit = str[num++]; 
		game[i].rank = str[num++];

		if(game[i].suit == '0') { 															//Last
			break;
		}
	}
}	

/*!
@brief  This function enables the game to be played. 

@param  i is declared as data type int
		N is defined as an integer literal of 53
		game is a function parameter of struct card which contains char 

@return Nothing 
*//*_______________________________________________________________________________________*/
void play_game(Card game[]) {

	for(int i = 0; i < N;) {
		//three position move 
		//check if 3 pos from left has same suit or rank
		if( (game[i].suit == game[i-3].suit) || (game[i].rank == game[i-3].rank)) {

				game[i-3].suit = game[i].suit;												//places over suit
				game[i-3].rank = game[i].rank;												//places over rank
					
				del_card(game, (CardIndex)i );												//call del function; CardIndex is typedef as unsigned char
				i = 0;
		}
		//one position move provided no three position move available
		//check if immediate left has same suit or rank
		else if ((game[i].suit == game[i-1].suit) || (game[i].rank == game[i-1].rank)) {
			   
				game[i-1].suit = game[i].suit;												//places over suit
				game[i-1].rank = game[i].rank;												//places over rank
				 
				del_card(game, (CardIndex)i );												//call del function
				i = 0;
		}
		else
			i++;
	
		if(game[i].suit == '0') break; 														//Last
    }                                                              
}

/*!
@brief  This function displays the sequence of cards

@param  i is declared as data type int
		game is a function parameter of struct card which contains char 

@return Nothing 
*//*_______________________________________________________________________________________*/
void display_game(const Card game[]) {
	for(int i = 0; i < N; i++){
		
		printf("%c%c " ,game[i].suit, game[i].rank);  

		if(game[i].suit == '0'){ 															//Last
            printf("\n");
            break;
		} 
	}
}