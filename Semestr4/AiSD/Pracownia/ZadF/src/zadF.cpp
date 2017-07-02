#include <iostream>
#include <cstdio>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>
#include <limits>


int main()
{
	int tests;
	if(scanf("%d\n", &tests) != 1)
	{
		fprintf(stderr, "Error while reading tests number\n");
		return 1;
	}
	for(int t = 0; t < tests; ++t)
	{
		
		size_t n;
		if(scanf("%lu ", &n) != 1)
		{
			fprintf(stderr, "Error while reading n\n");
			return 1;
		}
		std::vector<unsigned int> tab(n);
		for(size_t i = 0; i < n; ++i)
		{
			if(scanf("%u", &tab[i]) != 1)
			{
				fprintf(stderr, "Error while reading vector elements\n");
				return 1;
			}
			getchar();
		}
		std::vector<unsigned int> beginning(n);
		std::vector<unsigned int> ending(n);
		
		ending[0] = 1;

		unsigned int j = n-2;
		beginning[n-1] = 1;
		for(unsigned int i = 1; i < n; ++i)
		{

			if(tab[i] > tab[i-1])
				ending[i] = ending[i-1] + 1;
			else
				ending[i] = 1;

			if(tab[j] < tab[j+1])
				beginning[j] = beginning[j+1] + 1;
			else
				beginning[j] = 1;
			--j;
		}
		std::vector< std::pair<unsigned int, unsigned int> > incSeq;
		incSeq.push_back({tab[0], ending[0]});
		unsigned int maxVal = ending[0];

		for(unsigned int i = 1; i < n; ++i)
		{
			int left = 0;
			int right = incSeq.size()-1;

			while(left < right)
			{
				auto half = (left + right)/2;
				if(tab[i] < incSeq[half].first)
					right = half - 1;
				else
					left = half;
				if(left == right - 1)
				{
					if(tab[i] <= incSeq[left].first)
					{
						--left;
					}
					else if (tab[i] > incSeq[right].first)
					{
						left = right;
					}
					break;
				}
			}
			if(left != -1 && incSeq[left].first >= tab[i])
			{
				--left;
			}

			if(left == -1)
			{
				maxVal = std::max(maxVal, beginning[i]);
			}
			else
			{

				const auto& currSeq = incSeq[left];
				maxVal = std::max(maxVal, incSeq[left].second + beginning[i]);
				
				if(currSeq.second >= ending[i])
					continue;
			}
			int idx = left+1;
			while(incSeq[idx].second <= ending[i] && idx < (int)incSeq.size()  )
				++idx;
			if(idx == left + 1)
				incSeq.insert(incSeq.begin() + idx, {tab[i], ending[i]});
			else
			{
				incSeq[left+1] = {tab[i], ending[i]};
				if(left+2 != idx)
					incSeq.erase(incSeq.begin()+left+2, incSeq.begin() + idx);
			}
		}
		printf("%u\n", maxVal);
	}

	return 0;
}
