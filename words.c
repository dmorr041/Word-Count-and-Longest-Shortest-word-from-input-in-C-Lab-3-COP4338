/*
 *	I affirm that this is my original work and not the work of anyone else.
 *
 *	Darien Morrison 3380082
 * 
 *	Simple C program to count the number of words, either from standard input
 *	or from an input file, and optionally provide the longest and shortest 
 *	words in that input using command line parsing through the getopt function.
 *
 *
 * */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	extern char *optarg;
	extern int optind;
	int c, err = 0;

	int count = 0;		// Word count

	char contents[100];	// String we'll store the file contents in
	char longest[100];	// Longest word
	int longlength = 0;	// Length of the longest word
	char shortest[100];	// Shortest word
	int shortlength = 999;	// Length of the shortest word
	
	// File pointer (set to standard input as default)
	FILE* input = stdin;

	// Flags
	int lflag = 0;
	int sflag = 0;
	

	static char usage[] = "Usage: words [-l] [-s] [filename]";

	// Set the flags and values for each case
	while ((c = getopt(argc, argv, "ls")) != -1)
		switch (c) {
		case 'l':
			lflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case '?':
			err = 1;
			break;
		}
	
	if(err)
	{
		fprintf(stderr, usage, argv[0]);
		exit(1);
	}

	char *token;

	// If we have a filename...	
	if(argv[optind] != NULL)
	{
		// Change the file pointer from stdin to the file (located
		// at optind position of argv)
		input = fopen(argv[optind], "r");

		// If there is no file (null file pointer)
		if(input == NULL)
		{	
			printf("File not found\n");	// Tell the user the file was not found
			exit(1);	// Set input back to stdin
		}

		fgets(contents, sizeof(contents), input);

		token = strtok(contents, " ");
	}
	else	// We don't have a file name, so input is stdin. Ask user to enter a string.
	{
		printf("Please enter a string.\n");

		fgets(contents, sizeof(contents), input);

		token = strtok(contents, " ");
	}	

	// While we have a token and it's not a space
	while(token && !isspace(*token))
	{
		// Increment word count each iteration to count the number of words
		count++;
		
		// If the user wants to find the longest word...
		if(lflag == 1)
		{
			// If the length of the token is greater than the current longest length for a word...
			if(strlen(token) > longlength)
			{
				// Copy the token into the longest word
				strcpy(longest, token);
				// Update the new longest length for a word
				longlength = strlen(token);
			} 
		}
		// If the user wants to find the shortest word...
		if(sflag == 1)
		{
			// If the length of the token is less than the current shortest length for a word...
			if(strlen(token) < shortlength)
			{
				// Copy the token into the shortest word
				strcpy(shortest, token);
				// Update the new shortest length for a word
				shortlength = strlen(token);
			}
		}

		// Required to keep iterating
		token = strtok(NULL, " ");
	}

	// Print the word count
	printf("\nNumber of words: %d\n", count);

	// If the user wants to find the longest word...
	if(lflag == 1)
	{
		printf("Longest word: %s\n", longest);
	}

	if(sflag == 1)
	{
		printf("Shortest word: %s\n", shortest);
	}

	return 0;	
}
