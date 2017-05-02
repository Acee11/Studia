#include <cstdio>
#include <stdint.h>
#include <string.h>
#include <vector>
#define MAX_N 1001

int main()
{

	int D, num_prod1, num_prod2;
	int err;

	uint8_t map_table[8] = {0b1, 0b10, 0b100, 0b1000, 0b10000, 0b100000, 0b1000000, 0b10000000};
	char word[MAX_N+1];

	uint8_t nonterminals[129][129];
	uint8_t terminals[26];
	
	std::vector< std::vector< uint8_t > > T(MAX_N, std::vector< uint8_t >(MAX_N));
	
	err = scanf("%d\n",&D);
	if(err == 0)
		return 1;

	for(int test = 0; test < D; ++test)
	{
		for(uint8_t i = 1; i != 0; i<<=1)
			for(uint8_t j = 1; j != 0; j<<=1)
			nonterminals[i][j] = 0;
		for(int i = 0; i < 26; ++i)
			terminals[i] = 0;

		err = scanf("%d %d\n", &num_prod1, &num_prod2);
		if(err == 0)
			return 1;
		for(int j = 0; j < num_prod1; ++j)
		{
			char nt, nt1, nt2;
			err = scanf("%c %c %c\n", &nt, &nt1, &nt2);
			if(err == 0)
				return 1;
			nonterminals[map_table[nt1 - 'A']][map_table[nt2 - 'A']] |= map_table[nt - 'A'];
		}
		for(int j = 0; j < num_prod2; ++j)
		{
			char nonterm, term;
			err = scanf("%c %c\n", &nonterm, &term);
			if(err == 0)
				return 1;
			terminals[term - 'a'] |= map_table[nonterm - 'A'];
		}


		fgets(word, MAX_N, stdin);
		int n = strlen(word);
		if(word[n-1] == '\n')
			--n;
		for(int i = 0; i < n; ++i)
			word[i] -= 'a';

		for(int i = 0; i < n; ++i)
			T[0][i] = terminals[(uint8_t)word[i]];

		for(int i = 1; i < n; ++i)
		{
			for(int j = 0; j < n-i; ++j)
			{
				uint8_t tmp = 0;
				for(int k = 0; k < i; ++k)
				{
					if(tmp == 0xff)
						break;
					uint8_t b1 = T[k][j];
					
					while(b1)
					{
						if(tmp == 0xff)
							break;
						uint8_t mask1 = b1 & (-b1);
						uint8_t b2 = T[i-k-1][j+k+1];
						while(b2)
						{
							uint8_t mask2 = b2 & (-b2);
							tmp |= nonterminals[mask1][mask2];
							b2 ^= mask2;
						}
						b1 ^= mask1;
					}
				}
				T[i][j] = tmp;
			}
		}
		if(T[n-1][0] & 1)
			printf("TAK\n");
		else
			printf("NIE\n");
	}
	return 0;
}