
#include "stats.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h> //used for helpful functions like isalpha and isspace

/**
 * Initializes the statistics structure
 * @param st an uninitialized WordStats struct
 * @return an initialized WordStats struct 
 */
WordStats initStats(WordStats st)
{	st.wordCount = 0; 	//all will begin at zero
	st.consonantCount = 0;
	st.vowelCount = 0;
	for(int i = 0; i < 26; i++){
	st.histo[i]=0;
	}
 	return st;
}

/**
 * Updates vowels and consonants in the struct
 * @param st WordStats structure
 * @param input the user-input string
 * @return an updated WordStats struct 
 */
WordStats updateVowelCons(WordStats st, const char str[])
{ 	
	int len = strlen(str);
	for(int i = 0; i < len; i++) //pass through entire string
	{
	 if (str[i] == 'a' || str[i] == 'e' || str[i] == 'i' ||	//check for lowercase and uppercase vowels
        str[i] == 'o' || str[i] == 'u' || str[i]=='A'||str[i]=='E'||str[i]=='I'||str[i]=='O'||str[i]=='U') {
		 st.vowelCount++; 
		}	
	 else if (( (str[i] >= 'A' && str[i] <= 'Z')|| (str[i]>='A'+32 && str[i]<= 'Z'+32))) { //+32 ASCIIZ upper to lower conversion
      st.consonantCount++;
    }
	} 
return st;
}
	
/**
 * Updates word count in the struct
 * @param st 
 * @param str 
 * @return an updated WordStats struct 
 */
WordStats updateWordCount(WordStats st, const char str[])
{
	int bool = 0; //used to keep track of if the char currently being looked at is a space
	for(int i = 0; i < strlen(str); i++){
		
		if(isspace(str[i])){ //if it is, dont do anyhting (isspace is used because it will include things like \n and \t)
			bool = 0;
		} else if(bool == 0 && isalpha(str[i])){ //if it isnt, must be a new word increment count
			st.wordCount++;
			bool = 1;
		}
	
	}
	return st;
}

/**
 * Outputs vowel and consonant stats
 * @param st WordStats structure
 */
void printVowelConsFreq(WordStats st)
{
	int total = st.vowelCount + st.consonantCount; //total letters will be sum of vowels and consonants
	float vowFreq = (float) st.vowelCount/total;  //float cast to find frequencies
	float consFreq = (float) st.consonantCount/total; //.2f will truncate a float to the hundred place
	printf("Vowels = %d(%.2f%%), Consonants = %d(%.2f%%) , Total = %d\n",st.vowelCount, vowFreq, st.consonantCount, consFreq, total);
}

/**
 * Outputs word count
 * @param st WordStats structure
 */
void printWordCount(WordStats st)
{	int words = st.wordCount;
	printf("Words: %d\n", words);
}

/**
 * Outputs histogram vertically
 * @param st WordStats structure
 */
void printHistogram(WordStats st)
{	int temp[26];
    memcpy(temp, st.histo, sizeof(st.histo));
	int max = st.histo[0]; //begin with max at histo[0]
	for(int i = 0; i < 26; i++){ 
		if(st.histo[i]>max){ //if histo(i) > max a new max has been found so reset it
			max = st.histo[i];
		}
	}
	for(int i = 1; i <= max; i++){ //outerloop controls what will be the highest bar of the graph
		for(int j = 0; j < 26; j++){ //inner loop goes through histo
			if(st.histo[j]==(max-i+1)){ 
			 printf("*"); //print a star
			 st.histo[j]--; //decrement count at that spot
			}else{
			 printf(" "); //print nothing
			}
		}
		printf("\n"); 
	}
	for(char c='a'; c<='z'; c++){ //display alphabet
		printf("%c", c);
	}
	printf("\n");
	int len = sizeof(temp)/sizeof(temp[0]);
	for(int i = 0; i < len; i++){
	 printf("%d", temp[i]);
	}


}

/**
 * Update the histogram
 * @param histo	the histogram
 * @param str	the string used to update the histogram
 */
void updateHistogram(int histo[], const char str[])
{
int len = strlen(str);
	for(char i = 'A'; i <= 'Z'; i++){ //outer loop loops through alphabet 
		for(int j = 0; j < len; j++){ //inner loop goes through string
			if(str[j]==i || str[j]==i+32){ //ACIIZ lower to upper
				histo[i-'A']++; //if the string contains the char I is at, increment that spot in histo
			}
		}
	}

}
