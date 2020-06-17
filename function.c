#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include "stdbool.h"
#include<inttypes.h>
#include<stdlib.h>
#include"memzero.h"
#include"memzero.c"
#include "bip39_english.h"
#define MAX_CHAR 100
typedef char string[MAX_CHAR+1];

int mnemonic_to_entropy(const char *mnemonic, uint8_t *entropy);
int mnemonic_to_entropy(const char *mnemonic, uint8_t *entropy)
{

  if (!mnemonic) {

    return 0;
  }

  uint32_t i = 0, n = 0;

  while (mnemonic[i]) {

    if (mnemonic[i] == ' ') {
      n++;
    }
    i++;
  }
  n++;

  // check number of words
  if (n != 12 && n != 18 && n != 24) {
    return 0;
  }

  char current_word[10] = {0};
  uint32_t j = 0, k = 0, ki = 0, bi = 0;
  uint8_t bits[32 + 1] = {0};

  memzero(bits, sizeof(bits));
  i = 0;
  while (mnemonic[i]) {
    j = 0;
    while (mnemonic[i] != ' ' && mnemonic[i] != 0) 
	{
      if (j >= sizeof(current_word) - 1) {
        return 0;
      }
      current_word[j] = mnemonic[i];
      i++;
      j++;
    }
    current_word[j] = 0;
    if (mnemonic[i] != 0) {
      i++;
    }
    k = 0;
    for (;;) {
      if (!wordlist[k]) 
	  {  // word not found
        return 0;
      }
      if (strcmp(current_word, wordlist[k]) == 0) {  // word found on index k
        for (ki = 0; ki < 11; ki++) {
          if (k & (1 << (10 - ki))) {
            bits[bi / 8] |= 1 << (7 - (bi % 8));
          }
          bi++;
        }
        break;
      }
      k++;
    }
  }
  if (bi != n * 11) 
  {
    return 0;
  }

   //printf("%d",sizeof(bits));
  //memcpy(entropy, bits, sizeof(bits));
  return n * 11;
}

int main()
{
   const char *a = "orbit phrase snow puppy zero music style casual term fox expand return total glory little used demise lyrics assault legal romance argue feel labor" ;
   uint8_t *entropy;


// long  string asm a = "orbit phrase snow puppy zero music style casual term fox expand return total glory little used demise lyrics assault legal romance argue feel labor" ;
int d = mnemonic_to_entropy(a,entropy );
printf("%d",d);
  return 0;
}
