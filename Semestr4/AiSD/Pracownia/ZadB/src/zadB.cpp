#include <cstdio>
#include <stdint.h>
#include <ctime>
#include <vector>
#include <algorithm>
#define MAX_N 1000001
#define INF 36
#define T(i, j) t[(j) + 36*(i)]
#define PREV(i, j) prev[(j) + 36*(i)]
//#define PREV2(i, j, k) prev2[(k) + 8*(j) + 64*(i)]
#define RES(i, j) res[(j) + 4*(i)]

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

struct conf conf_tab[8] = {
	{0b000, 0b000, 0b000},
	{0b001, 0b100, 0b010},
	{0b010, 0b000, 0b101},
	{0b011, 0b100, 0b111},
	{0b100, 0b001, 0b010},
	{0b101, 0b101, 0b010},
	{0b110, 0b001, 0b111},
	{0b111, 0b101, 0b111}
};

unsigned int knights[8] = {
	0,
	1,
	1,
	2,
	1,
	2,
	2,
	3
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

/*
	for(uint8_t i = 0; i < 0b111111; ++i)
	{
		udouble_conf conf;
		conf.c = i;
		printf("{");
		for(uint8_t j = 0; j < 36; ++j)
		{

			double_conf jconf = dconf_tab[j];
			if((jconf.conf_i & conf.dconf.conf_i) || (jconf.conf_j & conf.dconf.conf_j))
				continue;
			if(j != 0)
				printf(", ");
			printf("%hhu",j);
		}
		printf("},\n");
	}
	udouble_conf conf;
	conf.c = 0b100001;
	printf("%u %u", conf.dconf.conf_j, conf.dconf.conf_i);
*/
	clock_t t1, t2;
	t1 = clock();
	unsigned int n;
	int err = scanf("%u", &n);
	unsigned int N = n/2;
	if(err == 0)
		return 1;
	getchar();

	//uint8_t* board = new uint8_t[n+1];
	//uint8_t board[MAX_N];
	std::vector< std::vector<unsigned int> > t(N + 1, std::vector<unsigned int>(36, 0));
	std::vector< std::vector<unsigned char> > prev(N + 1, std::vector<unsigned char>(36, INF));
	udouble_conf board;

	board.c = 0b111111;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b011;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b101;
	if(getchar() == '.')
		board.dconf.conf_j &= 0b110;
	getchar();
	if(n > 1)
	{
		if(getchar() == '.')
			board.dconf.conf_i &= 0b011;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b101;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b110;
		getchar();
	}
	//printf("%u\n", N);
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

		if(getchar() == '.')
			board.dconf.conf_i &= 0b011;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b101;
		if(getchar() == '.')
			board.dconf.conf_i &= 0b110;
		getchar();

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
	if(n%2 == 1 && n > 1)
	{
		board.c = 0b111111;

		if(getchar() == '.')
			board.dconf.conf_j &= 0b011;
		if(getchar() == '.')
			board.dconf.conf_j &= 0b101;
		if(getchar() == '.')
			board.dconf.conf_j &= 0b110;
		getchar();

		for(uint8_t j : no_collision[board.c])
		{
			for(uint8_t k : prev_confs[j])
			{
				unsigned int maxval = t[N-1][k] + dknights[j];
				if(maxval > t[N][j])
				{
					t[N][j] = maxval;
					prev[N][j] = k;
				}
			}
		}	
	/*
	*/
		++N;	
	}

	unsigned int max_knights = *std::max_element(t[N-1].begin(), t[N-1].end());
	printf("%u\n",max_knights);
	t1 = clock() - t1;

	std::vector< std::string > res(n, "...");
	for(int i = N-1; i >= 0; --i)
	{
		res[i] = "";
	}

	printf("Total time: %f\n t2 = %f", ((double)t1)/CLOCKS_PER_SEC, ((double)t2)/CLOCKS_PER_SEC);
/*
	//1 - destroyed
	//0 - not destroyed
	if(n%2 == 1)
	{
		board[n] = 0b111;

	}
	if(n == 1)
	{
		unsigned int res = 0;
		char r[4];
		r[3] = '\0';
		if(board[0] & 4)
			r[0] = 'x';
		else
		{
			r[0] = 'S';
			++res;
		}
		if(board[0] & 2)
			r[1] = 'x';
		else
		{
			r[1] = 'S';
			++res;
		}
		if(board[0] & 1)
			r[2] = 'x';
		else
		{
			r[2] = 'S';
			++res;
		}
		printf("%u\n", res);
		printf("%s\n", r);
		return 0;
	}
	
	//unsigned int* t = new unsigned int[(n/2)*36];
	std::vector< std::vector<unsigned int> > t(n/2, std::vector<unsigned int>(36));
	unsigned char* prev = new unsigned char[(n/2)*36];

	for(unsigned int i = 0; i < 36; ++i)
	{
		double_conf c = dconf_tab[i];
		t[0][i] = ((board[0] & c.conf_j) || (board[1] & c.conf_i)) ? 0 : dknights[i];
		PREV(0,i) = INF;
		//prev[0][i] = INF;
	}
	
	t2 = clock();
	for(unsigned int i = 1; i < n/2; ++i)
	{
		for(unsigned int j = 0; j < 36; ++j)
		{
			double_conf c = dconf_tab[j];
			double_conf bconf = {board[2*i + 1], board[2*i]}
			if((board[i<<1] & c.conf_j) || (board[(i<<1) + 1] & c.conf_i))
					continue;
			t[i][j] = 0;
			PREV(i, j) = INF;
			//prev[i][j] = INF;
			for(uint8_t k : prev_confs[j])
			{
				double_conf ck = dconf_tab[k];
				if((board[(i<<1)-2] & ck.conf_j) || (board[(i<<1) - 1] & ck.conf_i))
					continue;
				unsigned int maxval = t[i-1][k] + dknights[j];
				if(maxval > t[i][j])
				{
					t[i][j] = maxval;
					PREV(i, j) = k;
					//prev[i][j] = k;
				}
			}
		}
	}
	t2 = clock() - t2;
	char* res = new char[4*n];
	unsigned int mx = 0;
	int max_conf = 0;
	unsigned int res_i = n-1;

	for(int j = 0; j < 36; ++j)
	{
		if(t[n/2 - 1][j] > mx)
		{
			mx = t[n/2 - 1][j];
			max_conf = j;
		}
	}


	if(n % 2 == 1)
	{
		int max_confs = 0;
		for(int i = 0; i < 8; ++i)
		{
			struct conf cnf = conf_tab[i];
			if(cnf.conf0 & board[n-1])
				continue;
			//printf("%u\n",i);
			for(int j = 0; j < 36; ++j)
			{
				struct double_conf dcnf = dconf_tab[j];
				if((dcnf.conf_i & cnf.conf1) || (dcnf.conf_j & cnf.conf2) 
					|| (dcnf.conf_i & board[n-2]) || (dcnf.conf_j & board[n-3]))
					continue;
				unsigned int maxval = t[n/2-1][j] + knights[i];
				if(maxval > mx)
				{
					mx = maxval;
					max_conf = j;
					max_confs = i;
				}
			}
		}
		//printf("%u\n", max_conf);
		struct conf pconf = conf_tab[max_confs];

		for(int k = 2; k >= 0; --k)
		{
			if(pconf.conf0 & (1<<k))
				RES(n-1, 2-k) = 'S';
			else
			{
				if(board[n-1] & (1<<k))
					RES(n-1, 2-k) = 'x';
				else
					RES(n-1, 2-k) = '.';
			}
		}
		RES(n-1, 3) = '\0';
		--res_i;
	}



	for(int i = res_i; i >= 0; i-=2)
	{
		struct double_conf pconf = dconf_tab[max_conf];
		for(int k = 2; k >= 0; --k)
		{

			if(pconf.conf_i & (1<<k))
				RES(i, 2-k) = 'S';
			else
			{
				if(board[i] & (1<<k))
					RES(i, 2-k) = 'x';
				else
					RES(i, 2-k) = '.';
			}

			if(pconf.conf_j & (1<<k))
				RES(i-1, 2-k) = 'S';
			else
			{
				if(board[i-1] & (1<<k))
					RES(i-1, 2-k) = 'x';
				else
					RES(i-1, 2-k) = '.';
			}
		}
		RES(i, 3) = '\0';
		RES(i-1, 3) = '\0';
		max_conf = PREV(i/2, max_conf);
		//max_conf = prev[i/2][max_conf];
	}

	printf("%u\n", mx);


	//for(unsigned int i = 0; i < n; ++i)
	//	printf("%s\n", &RES(i,0));
			
	t1 = clock() - t1;

	printf("Total time: %f\n t2 = %f", ((double)t1)/CLOCKS_PER_SEC, ((double)t2)/CLOCKS_PER_SEC);
	/*
	*/
	return 0;
}