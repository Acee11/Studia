#include <cstdio>
#include <stdint.h>
#include <ctime>
#include <vector>
#include <algorithm>
#define MAX_N 1000000
#define INF 36
#define PRINT_BOARD 1
#define PRINT_TIME 0


struct conf
{
	uint16_t conf0 : 3;
	uint16_t conf1 : 3;
	uint16_t conf2 : 3;
};

struct double_conf
{
	uint8_t conf_i : 3;
	uint8_t conf_j : 3;
};

union udouble_conf
{
	uint8_t c;
	double_conf dconf;
};


int main()
{
std::vector< std::vector<uint8_t> > prev_confs = {
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
{0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21, 24, 26, 28, 30, 32, 34},
{0, 2, 8, 10, 12, 14, 20, 22, 24, 25, 28, 29, 30, 31, 34, 35},
{0, 8, 12, 20, 24, 28, 30, 34},
{0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21, 24, 26, 28, 30, 32, 34},
{0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21, 24, 26, 28, 30, 32, 34},
{0, 8, 12, 20, 24, 28, 30, 34},
{0, 8, 12, 20, 24, 28, 30, 34},
{0, 1, 2, 3, 8, 9, 10, 11, 24, 25, 28, 29},
{0, 1, 8, 9, 24, 28},
{0, 2, 8, 10, 24, 25, 28, 29},
{0, 8, 24, 28},
{0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15, 16, 17, 18, 19},
{0, 1, 4, 5, 12, 13, 16, 17},
{0, 2, 12, 14},
{0, 12},
{0, 1, 4, 5, 12, 13, 16, 17},
{0, 1, 4, 5, 12, 13, 16, 17},
{0, 12},
{0, 12},
{0, 1, 2, 3},
{0, 1},
{0, 2},
{0},
{0, 2, 4, 6, 8, 10, 24, 25, 26, 27, 28, 29},
{0, 2, 8, 10, 24, 25, 28, 29},
{0, 4, 8, 24, 26, 28},
{0, 8, 24, 28},
{0, 2, 8, 10, 24, 25, 28, 29},
{0, 2, 8, 10, 24, 25, 28, 29},
{0, 2, 4, 6},
{0, 2},
{0, 4},
{0},
{0, 2},
{0, 2}
};

std::vector< std::vector<uint8_t> > no_collision = {
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35},
{0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21, 24, 26, 28, 30, 32, 34},
{0, 4, 8, 12, 16, 20, 24, 26, 28, 30, 32, 34},
{0, 1, 2, 3, 8, 9, 10, 11, 12, 13, 14, 15, 20, 21, 22, 23, 24, 25, 28, 29, 30, 31, 34, 35},
{0, 2, 8, 10, 12, 14, 20, 22, 24, 25, 28, 29, 30, 31, 34, 35},
{0, 1, 8, 9, 12, 13, 20, 21, 24, 28, 30, 34},
{0, 8, 12, 20, 24, 28, 30, 34},
{0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15, 16, 17, 18, 19, 24, 25, 26, 27, 30, 31, 32, 33},
{0, 2, 4, 6, 12, 14, 16, 18, 24, 25, 26, 27, 30, 31, 32, 33},
{0, 1, 4, 5, 12, 13, 16, 17, 24, 26, 30, 32},
{0, 4, 12, 16, 24, 26, 30, 32},
{0, 1, 2, 3, 12, 13, 14, 15, 24, 25, 30, 31},
{0, 2, 12, 14, 24, 25, 30, 31},
{0, 1, 12, 13, 24, 30},
{0, 12, 24, 30},
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 24, 25, 26, 27, 28, 29},
{0, 2, 4, 6, 8, 10, 24, 25, 26, 27, 28, 29},
{0, 1, 4, 5, 8, 9, 24, 26, 28},
{0, 4, 8, 24, 26, 28},
{0, 1, 2, 3, 8, 9, 10, 11, 24, 25, 28, 29},
{0, 2, 8, 10, 24, 25, 28, 29},
{0, 1, 8, 9, 24, 28},
{0, 8, 24, 28},
{0, 1, 2, 3, 4, 5, 6, 7, 24, 25, 26, 27},
{0, 2, 4, 6, 24, 25, 26, 27},
{0, 1, 4, 5, 24, 26},
{0, 4, 24, 26},
{0, 1, 2, 3, 24, 25},
{0, 2, 24, 25},
{0, 1, 24},
{0, 24},
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23},
{0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22},
{0, 1, 4, 5, 8, 9, 12, 13, 16, 17, 20, 21},
{0, 4, 8, 12, 16, 20},
{0, 1, 2, 3, 8, 9, 10, 11, 12, 13, 14, 15, 20, 21, 22, 23},
{0, 2, 8, 10, 12, 14, 20, 22},
{0, 1, 8, 9, 12, 13, 20, 21},
{0, 8, 12, 20},
{0, 1, 2, 3, 4, 5, 6, 7, 12, 13, 14, 15, 16, 17, 18, 19},
{0, 2, 4, 6, 12, 14, 16, 18},
{0, 1, 4, 5, 12, 13, 16, 17},
{0, 4, 12, 16},
{0, 1, 2, 3, 12, 13, 14, 15},
{0, 2, 12, 14},
{0, 1, 12, 13},
{0, 12},
{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11},
{0, 2, 4, 6, 8, 10},
{0, 1, 4, 5, 8, 9},
{0, 4, 8},
{0, 1, 2, 3, 8, 9, 10, 11},
{0, 2, 8, 10},
{0, 1, 8, 9},
{0, 8},
{0, 1, 2, 3, 4, 5, 6, 7},
{0, 2, 4, 6},
{0, 1, 4, 5},
{0, 4},
{0, 1, 2, 3},
{0, 2},
{0, 1},
{0}
};

struct double_conf dconf_tab[36] = {
	{0, 0}, {1, 0}, {2, 0}, {3, 0},
	{4, 0}, {5, 0}, {6, 0}, {7, 0}, 
	{0, 1}, {1, 1}, {2, 1}, {3, 1},
	{0, 2}, {1, 2}, {2, 2}, {3, 2},
	{4, 2}, {5, 2}, {6, 2}, {7, 2}, 
	{0, 3}, {1, 3}, {2, 3}, {3, 3}, 
	{0, 4}, {2, 4}, {4, 4}, {6, 4}, 
	{0, 5}, {2, 5}, {0, 6}, {2, 6},
	{4, 6}, {6, 6}, {0, 7}, {2, 7}
};

unsigned int dknights[36] = {
	0, 1, 1, 2,
	1, 2, 2, 3,
	1, 2, 2, 3,
	1, 2, 2, 3,
	2, 3, 3, 4,
	2, 3, 3, 4,
	1, 2, 2, 3,
	2, 3, 2, 3,
	3, 4, 3, 4
};

	clock_t t1, t2;
	t1 = clock();
	unsigned int n;
	int err = scanf("%u", &n);
	unsigned int N = n/2 + (n % 2);
	if(err == 0)
		return 1;
	getchar();

	uint8_t* brd = new uint8_t[MAX_N];
	std::vector< std::vector<unsigned int> > t(MAX_N/2, std::vector<unsigned int>(36, 0));
	std::vector< std::vector<unsigned char> > prev(MAX_N/2, std::vector<unsigned char>(36, INF));
	udouble_conf board;

	board.c = 0b111111;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b011;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b101;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b110;
	getchar();
	brd[0] = board.dconf.conf_j;
	if(n > 1)
	{
		if(getchar() == '.')
			board.dconf.conf_i &= 0b011;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b101;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b110;
		getchar();
		brd[1] = board.dconf.conf_i;
	}
	else
	{
		printf("%u\n",(((~board.dconf.conf_j) & 1) + (((~board.dconf.conf_j)>>1) & 1) + (((~board.dconf.conf_j)>>2) & 1)));
		#if PRINT_BOARD
		if(board.dconf.conf_j & 0b100)
			printf("x");
		else
			printf("S");
		if(board.dconf.conf_j & 0b010)
			printf("x");
		else
			printf("S");
		if(board.dconf.conf_j & 0b001)
			printf("x");
		else
			printf("S");
		#endif
		return 0;
	}	
	for(uint8_t j : no_collision[board.c])
		t[0][j] = dknights[j];

	t2 = clock();
	
	for(unsigned int i = 1; i < N; ++i)
	{
		board.c = 0b111111;

		if(getchar() == '.')
			board.dconf.conf_j &= 0b011;
		if(getchar() == '.')
			board.dconf.conf_j &= 0b101;
		if(getchar() == '.')
			board.dconf.conf_j &= 0b110;
		getchar();
		brd[i<<1] = board.dconf.conf_j;
		if((i == N-1) && (n%2 == 1))
		{
			board.dconf.conf_i = 0b111;
		}

		else
		{
			if(getchar() == '.')
				board.dconf.conf_i &= 0b011;
			if(getchar() == '.')
				board.dconf.conf_i &= 0b101;
			if(getchar() == '.')
				board.dconf.conf_i &= 0b110;
			getchar();
		}
		brd[(i<<1) + 1] = board.dconf.conf_i;

		for(uint8_t j : no_collision[board.c])
		{
			for(uint8_t k : prev_confs[j])
			{
				unsigned int maxval = t[i-1][k] + dknights[j];
				if(maxval > t[i][j])
				{
					t[i][j] = maxval;
					prev[i][j] = k;
				}
			}
		}
	}
	t2 = clock() - t2;

	unsigned int max_knights = 0;
	unsigned int max_knights_idx = 0;
	for(int i = 0; i < 36; ++i)
	{
		if(t[N-1][i] > max_knights)
		{
			max_knights = t[N-1][i];
			max_knights_idx = i;
		}
	}

	printf("%u\n",max_knights);

	udouble_conf res_conf;
	uint8_t k = prev[N-1][max_knights_idx];
	
	for(int i = N-2; i >= 0; --i)
	{
		int tmp = prev[i][k];
		prev[i][k] = max_knights_idx;
		max_knights_idx = k;
		k = tmp;
	}
	int j = 0;
	for(int i = 0; i < N; ++i)
	{
		res_conf.dconf = dconf_tab[max_knights_idx];
		char res[9];
		if(res_conf.dconf.conf_j & 0b100)
			res[0] = 'S';
		else if(brd[j] & 0b100)
			res[0] = 'x';
		else res[0] = '.';;
		if(res_conf.dconf.conf_j & 0b010)
			res[1] = 'S';
		else if(brd[j] & 0b010)
			res[1] = 'x';
		else res[1] = '.';
		if(res_conf.dconf.conf_j & 0b001)
			res[2] = 'S';
		else if(brd[j] & 0b001)
			res[2] = 'x';
		else res[2] = '.';
		res[3] = '\n';

		if(i != N-1 || (!(n&1)))
		{
			if(res_conf.dconf.conf_i & 0b100)
				res[4] = 'S';
			else if(brd[j+1] & 0b100)
				res[4] = 'x';
			else res[4] = '.';;
			if(res_conf.dconf.conf_i & 0b010)
				res[5] = 'S';
			else if(brd[j+1] & 0b010)
				res[5] = 'x';
			else res[5] = '.';
			if(res_conf.dconf.conf_i & 0b001)
				res[6] = 'S';
			else if(brd[j+1] & 0b001)
				res[6] = 'x';
			else res[6] = '.';
		}
		else
		{
			res[3] = '\n';
			res[4] = '\0';
		}
		res[7] = '\n';
		res[8] = '\0';
		printf("%s",res);
		j+=2;
		max_knights_idx = prev[i][max_knights_idx];

	}
	t1 = clock() - t1;


	printf("Total time: %f\n t2 = %f\n", ((double)t1)/CLOCKS_PER_SEC, ((double)t2)/CLOCKS_PER_SEC);


	return 0;
}
