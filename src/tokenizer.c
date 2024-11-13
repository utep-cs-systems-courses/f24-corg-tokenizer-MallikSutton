#include <stdlib.h>
#include <stdio.h>
#include "tokenizer.h"
#include "history.h"
#include <string.h>
#define _TOKENIZER_


/* Return true (non-zero) if c is a whitespace characer
   ('\t' or ' ').  
   Zero terminators are not printable (therefore false) */
int space_char(char c){
  return ((c == '\t' || c == ' ')&& c !='0');
     }

/* Return true (non-zero) if c is a non-whitespace 
   character (not tab or space).  
Zero terminators are not printable (therefore false) */ 
int non_space_char(char c){
  return((c != '\t' || c != ' ')&& c !='0');
}
				      
/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens. */
char *token_start(char *str){
 while(space_char(*str)){
    str++;
     }
return *str ? str:NULL;

}

/* Returns a pointer terminator char following *token */
char *token_terminator(char *token){
  while(non_space_char(*token)){
      token++;
    }
  return token;
}

/* Counts the number of tokens in the string argument. */
    int count_tokens(char *str){
      int count =0;

      /*ignores the whitespace in the beginning */
      while(space_char(*str)){
	str++;
      }
       /*string loop */
      while(*str != '\0'){
	 /*if a non-whitespace character is found then its a token */
	if(non_space_char(*str)){
	   /*token count */
	  count++;

	   /*move to the end of the token */
	  str=token_terminator(str);
	}
	else{
	  str++;
	}

	/*ignore whitespaces again before the next token */
	while(space_char(*str)){
	  str++;
      }
	 /*returns the amount of tokens found */
      }
       return count;
 }

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
    char *copy_str(char *inStr, short len){
    char *newStr = malloc(len + 1); // Allocate memory for the token + null terminator
    if (newStr == NULL) {
        return NULL;
    }
    for (int i = 0; i < len; i++) {
        newStr[i] = inStr[i];
    }
    newStr[len] ='\0';
    return newStr;
}

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.

   For example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0
*/
    char **tokenize(char* str){
      int num_tokens =count_tokens(str);
      char **tokens = malloc(sizeof(char *) * (num_tokens + 1));;
      int index=0;
      while(*str){
	while (*str == ' ' || *str == '\t') str++;
        
        if (*str) { // We've found the start of a token
            char *start = str;
            while (*str && *str != ' ' && *str != '\t') str++;
            
            int len = str - start;
            tokens[index] = malloc(len + 1); // Allocate memory for the token
            strncpy(tokens[index], start, len); // Copy token
            tokens[index][len] = '\0'; // Null-terminate
            index++;

      }
      
    }
      tokens[index] =NULL;
      return tokens;
    }


    

/* Prints all tokens. */
    void print_tokens(char **tokens){
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token %d: %s\n", i, tokens[i]);
    }
}
    

/* Frees all tokens and the vector containing themx. */
    void free_tokens(char **tokens){
      for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]); // Free each token
    }
    free(tokens); // Free the array of pointers
}
