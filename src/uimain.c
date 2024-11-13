#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "history.h"

int main() {
    puts("Welcome!");
    List *history = init_history();  // Initialize history
    if (history == NULL) {
        printf("Failed to initialize history.\n");
        return 1;  // Exit if initialization fails
    }
    

   
    while (1) { // Infinite loop to keep accepting input
        fputs("$ ", stdout);  // Indicator for the user
        fflush(stdout);       // Flush stdout to ensure the prompt shows immediately
       
        char command[256];
        if (fgets(command, sizeof(command), stdin) == NULL) {
            break;  // Exit if there is an input error (EOF)
        }

        // Remove the trailing newline if present
        command[strcspn(command, "\n")] = '\0';
	add_history(history,command);
        // Echo back the input
        printf("You entered: %s\n", command);

        // Handle commands based on the input
        if (strcmp(command, "q") == 0) {  // Quit the program
            puts("Bye!");
            break;
        } 
        else if (strcmp(command, "h") == 0) {  // Retrieve history by ID
            int id;
            fputs("Enter ID to retrieve: ", stdout);
            fflush(stdout);

            if (scanf("%d", &id) !=1) {
                printf("Invalid ID, try again.\n");
                while (getchar() != '\n');
		 add_history(history,command);// Clear the buffer
                continue;
            }

            char *item = get_history(history, id);  // Fetch history item
            if (item != NULL) {
	      printf("History item with ID %d: %s\n",id, item);
            } else {
                printf("Invalid ID, try again.\n");
            }

            // Clear the buffer after reading ID
            while (getchar() != '\n');
        } 
        else if (strcmp(command, "p") == 0) {  // Print the entire history
            printf("Printing all history items:\n");
	    print_history(history);
        } 
        else if (strcmp(command, "t") == 0) {  // Tokenize a string
            fputs("Enter a string to tokenize: ", stdout);
            fflush(stdout);

            char token_str[256];
            if (fgets(token_str, sizeof(token_str), stdin) != NULL) {
                token_str[strcspn(token_str, "\n")] = '\0';  // Remove newline
		add_history(history,token_str); //Allows the tokens to be part of the history
                char **tokens = tokenize(token_str);        // Tokenize the input
                printf("Tokens:\n"); //prints the string(s) individually as token
                for (int i = 0; tokens[i] != NULL; i++) {
                    printf("%s\n", tokens[i]);  // Print each token
                    free(tokens[i]);  // Free each token after use
                }
                free(tokens);  // Free the token array
            }
        } 
        else {
            printf("Invalid input, try again!\n");  // if anything other than q, h, t, p is typed out its invalid
        }
    }

    free_history(history);  // Clean up the history
    free(history);
    return 0;
}
