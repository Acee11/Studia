#include <cstdio>
#include <stdint.h>
#include <string.h>
#include <tuple>
#include <vector>
#include <queue>
#include <unordered_map>
#define MAX_N 500000


typedef size_t ull;
//typedef std::tuple<ull, ull, ull> triple;
struct triple
{
	ull t1;
	ull t2;
	ull t3;
	bool operator == (const triple &x) const
	{
		return t1 == x.t1 && t2 == x.t2 && t3 == x.t3;
	}

};

struct key_hash : public std::unary_function<triple, size_t>
{
	std::size_t operator()(const triple& k) const
 	{
   		return k.t1 ^ k.t2 ^ k.t3;
 	}
};

typedef std::unordered_map<triple, size_t, key_hash> id_map;

int main()
{

	unsigned int tests;
	if(scanf("%u", &tests) != 1)
	{
		fprintf(stderr, "error while reading tests\n");
		return 0;
	}
	for(unsigned int d = 0; d < tests; ++d)
	{
		size_t n;
		if(scanf("%lu", &n) != 1)
		{
			fprintf(stderr, "error while reading n\n");
			return 0;
		}
		getchar();
		if(n == 1)
		{
			printf("TAK\n");
			continue;
		}

		std::vector< unsigned int > T1(n+1, 0);
		std::vector< unsigned int > T2(n+1, 0);

		unsigned int id_count1 = 0;

		std::queue< unsigned int > T1_leaves;
		std::queue< unsigned int > T2_leaves;

		std::vector< unsigned int > T1_childs(n+1, 0);
		std::vector< unsigned int > T2_childs(n+1, 0);

		std::vector< triple > T1_hash(n+1, {0,0,0});//////
		std::vector< triple > T2_hash(n+1, {0,0,0});//////

		unsigned int T1_leaves_overall = 0;
		unsigned int T2_leaves_overall = 0;

		id_map m1;
		

		for(size_t i = 0; i < n-1; ++i)
		{
			unsigned int v1, v2;
			if(scanf("%u %u", &v1, &v2) != 2)
			{
				fprintf(stderr, "Error while reading edges\n");
				return 0;
			}
			getchar();

			T1[v1-1] ^= v2-1;
			T1[v2-1] ^= v1-1;
			++T1_childs[v1-1];
			++T1_childs[v2-1];

		}
		for(size_t i = 0; i < n-1; ++i)
		{
			unsigned int v1, v2;
			if(scanf("%u %u", &v1, &v2) != 2)
			{
				fprintf(stderr, "Error while reading edges\n");
				return 0;
			}
			getchar();
			T2[v1-1] ^= v2-1;
			T2[v2-1] ^= v1-1;
			++T2_childs[v1-1];
			++T2_childs[v2-1];
		}

		for(unsigned int i = 0; i < n; ++i)
		{
			if(T1_childs[i] == 1)
			{
				++T1_leaves_overall;
				T1_leaves.push(i);
			}
			if(T2_childs[i] == 1)
			{
				++T2_leaves_overall;
				T2_leaves.push(i);
			}
		}

		unsigned int n1 = n;

		bool exit = false;

		while(!T1_leaves.empty())
		{
			
			if(T1_leaves_overall != T2_leaves_overall)
			{
				printf("NIE\n");
				break;
			}
			if(n1 == 2)
			{
				
				unsigned int r1 = T1_leaves.front();
				T1_leaves.pop();
				unsigned int r2 = T1_leaves.front();
				T1_leaves.push(r1);
				T1[r1] ^= n ^ r2;
				T1[r2] ^= n ^ r1;
				T1[n] ^= r1;
				T1[n] ^= r2;
				T1_childs[n] = 2;

				r1 = T2_leaves.front();
				T2_leaves.pop();
				r2 = T2_leaves.front();
				T2_leaves.push(r1);
				T2[r1] ^= n ^ r2;
				T2[r2] ^= n ^ r1;
				T2[n] ^= r1;
				T2[n] ^= r2;
				T2_childs[n] = 2;
				++n1;
			}

			unsigned int next_T1lo = 0;
			unsigned int next_T2lo = 0;
			for(unsigned int i = 0; i < T1_leaves_overall; ++i)
			{
				--n1;
				unsigned int v1 = T1_leaves.front();
				unsigned int v2 = T2_leaves.front();
				T1_leaves.pop();
				T2_leaves.pop();

				triple h1 = T1_hash[v1];
				triple h2 = T2_hash[v2];

				id_map::const_iterator got1 = m1.find(h1);

				unsigned int id1;
				unsigned int id2;

				if(got1 == m1.end())
				{
					++id_count1;
					m1[h1] = id_count1;
					id1 = id_count1;
					
				}
				else
					id1 = got1->second;

				id_map::const_iterator got2 = m1.find(h2);
				if(got2 == m1.end())
				{
					++id_count1;
					m1[h2] = id_count1;
					id2 = id_count1;
					
				}
				else
					id2 = got2->second;
				
				if(n1 == 0)
				{
					if(id1 == id2)
						printf("TAK\n");
					else
						printf("NIE\n");
					exit = true;
					break;
				}

				unsigned int father1 = T1[v1];
				unsigned int father2 = T2[v2];

				T1_hash[father1].t1 ^= id1;
				unsigned int tmp1 = id1*id1;
				T1_hash[father1].t2 += tmp1;
				T1_hash[father1].t3 += tmp1 * id1;
				if(--T1_childs[father1] == 1)
				{
					++next_T1lo;
					T1_leaves.push(father1);
				}
				T1[father1] ^= v1;

				T2_hash[father2].t1 ^= id2;
				unsigned int tmp2 = id2*id2;
				T2_hash[father2].t2 += tmp2;
				T2_hash[father2].t3 += tmp2 * id2;
				if(--T2_childs[father2] == 1)
				{
					++next_T2lo;
					T2_leaves.push(father2);
				}
				T2[father2] ^= v2;
			}

			if(exit)
				break;
			T1_leaves_overall = next_T1lo;
			T2_leaves_overall = next_T2lo;
		}
	}
	return 0;
}
