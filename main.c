/* WordStats - CS 475
 * Author: Madison Sanchez-Forman | Version: 1.27.22 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "stats.h"
#include "menu.h"

#define MAX_INPUT_LEN 128 /** maximum length of input users can enter */

/**
 * Helper for main function, used to begin allowing string input and tracking stats.
 * also used in main during case switch if user wants to continue entering more strings
 * @param st WordStat struct tracking strings current statistics 
 */
WordStats begin(WordStats st)
{
	char input[MAX_INPUT_LEN]; //holds user-input string
	printf("Enter strings (# to stop): \n");
	while(fgets(input, sizeof(input), stdin))
	{ //while the array still has storage space
		st = updateVowelCons(st, input); //update the statistics
		st = updateWordCount(st, input);
		updateHistogram(st.histo,input);
			for(int i = 0; i < strlen(input); i++)
			{ //if a '#' is entered, display menu (see main)
				if(input[i]=='#'){
			 		return st; //return the struct with updated info on the string
		    	}
			}
	}
	return st;
}
/**
 * Main function
 * 
 * @param argc the number of command line arguments (ignore for this assignment)
 * @param argv an array of command line arguments (ignore for this assignment)
 */
int main(int argc, char **argv){   
	int choice;
	WordStats stats = initStats(stats); //initialize struct
	stats = begin(stats); 				//will handle input and '#' case
			do{ 						//while the user has not chosen 5 (quit)
			 choice = getMenuOption();	//display menu store response
			 switch(choice){  			//if response is 1,2,3,4,5 execute cases respectively and redisplay menu
				case 1:
				printVowelConsFreq(stats);
				break;
				case 2:
				printWordCount(stats);
				break;
				case 3:
				printHistogram(stats);
				printf("\n");
				break;
				case 4:
				stats = begin(stats);
				break;
				case 5:
				break; 									//if quit choice break the loop and go to print/return statement
				default: 							    //else choice was invalid
				printf("Invalid choice %d, Try again. \n", choice);
			 	}	
			} while (choice != 5);
		printf("Exiting... \n"); 
		return 0;										//exit cleanly
	} 
	
	
	

