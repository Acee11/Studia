#include <iostream>
#include <cstdio>
#include <stdint.h>
#include <algorithm>
#include <vector>
#include <queue>
#include <array>

#define DEFAULT_NUM_OF_BUCKETS 84223
#define SEC_NUM_OF_BUCKETS 20287


class barrelVect : public std::array<short, 7>
{
private:
public:
	static size_t n;

	bool operator == (const barrelVect& b) const
	{
		for(size_t i = 0; i < n; ++i)
			if((*this)[i] != b[i])
				return false;
		return true;
	}
};
size_t barrelVect::n = 3;

template<typename T, typename hash_function>
class hashset
{
private:
	static hash_function hash_f;
	std::vector< std::vector<T> > bucket;
	size_t numOfBuckets;
	size_t elemInSet;
public:
	hashset() :
	numOfBuckets(DEFAULT_NUM_OF_BUCKETS),
	elemInSet(0)
	{
		bucket = std::vector< std::vector<T> >(DEFAULT_NUM_OF_BUCKETS); 
	}

	hashset(size_t numOfBuckets) :
	numOfBuckets(numOfBuckets),
	elemInSet(0)
	{
		bucket = std::vector< std::vector<T> >(DEFAULT_NUM_OF_BUCKETS); 
	}

	void clear()
	{
		for(size_t i = 0; i < numOfBuckets; ++i)
		{
			std::vector<T>().swap(bucket[i]);
		}
		elemInSet = 0;
	}

	void setNumOfBuckets(size_t num)
	{
		numOfBuckets = num;
	}

	bool insert(const T& x)
	{
		std::vector<T>& xvect = bucket[hash_f(x) % numOfBuckets];
		auto it = std::find(xvect.begin(), xvect.end(), x);
		if(it != xvect.end())
			return true;

		++elemInSet;
		xvect.push_back(x);
		return false;
	}

	const size_t& size() const
	{
		return elemInSet;
	}
};

struct barrelVectHash : public std::unary_function<barrelVect, size_t>
{
	size_t operator () (const barrelVect& v) const 
	{
		size_t result = 0;
		for(size_t i = 0; i < barrelVect::n; ++i)
			result ^= (size_t)v[i] + 0x9E3779B97F4A7C15ULL + (result << 6) + (result >> 2);
 		return result;
	}
};


void print_vect(const barrelVect& v)
{
	for(size_t i = 0; i < barrelVect::n; ++i)
		std::cout << v[i] << ' ';
	std::cout << '\n';
}
 
std::vector<barrelVect> generateConfigurations(
	const barrelVect& bVect, 
	const barrelVect& maxValues
)
{
	std::vector<barrelVect> res;

	barrelVect curr_vect = bVect;
	for(size_t i = 0; i < barrelVect::n; ++i)
	{
		const auto& el = bVect[i];
		if(el == 0)
			continue;
		

		curr_vect[i] = 0;
		res.push_back(curr_vect);
		curr_vect[i] = el;

		for(size_t j = 0; j < barrelVect::n; ++j)
		{
			const auto& elPrime = bVect[j];
			if(j == i || elPrime == maxValues[j])
				continue;
			auto s = std::min((short)(maxValues[j] - elPrime), (short)el);
			if(s == 0)
				continue;
			curr_vect[i] -= s;
			curr_vect[j] += s;
			res.push_back(curr_vect);
			curr_vect[i] += s;
			curr_vect[j] -= s;

		}
	}

	return res;
}


int main()
{
	int tests;
	if(scanf("%d\n", &tests) != 1)
	{
		fprintf(stderr, "Error while reading tests number\n");
		return 1;
	}
	size_t numOfBuckets = DEFAULT_NUM_OF_BUCKETS;
	hashset<barrelVect, barrelVectHash> h(numOfBuckets);
	for(int t = 0; t < tests; ++t)
	{
		size_t localN;
		if(scanf("%lu ", &localN) != 1)
		{
			fprintf(stderr, "Error while reading n\n");
			return 1;
		}
		if(barrelVect::n <= 2)
			h.setNumOfBuckets(SEC_NUM_OF_BUCKETS);
		else
			h.setNumOfBuckets(DEFAULT_NUM_OF_BUCKETS);
		barrelVect::n = localN;
		barrelVect maxValues;
		for(size_t i = 0; i < barrelVect::n; ++i)
		{
			if(scanf("%hd", &maxValues[i]) != 1)
			{
				fprintf(stderr, "Error while reading vector elements\n");
				return 1;
			}
			getchar();
		}


		
		
		std::queue<barrelVect> barrelQueue;
		barrelQueue.push(maxValues);
		h.insert(maxValues);
		int maxDistance = -1;
		int currLevelItems = 1;
		int nextLevelItems;

		while(!barrelQueue.empty())
		{
			++maxDistance;
			nextLevelItems = 0;
			for(int i = 0; i < currLevelItems; ++i)
			{
				barrelVect curr_vect = std::move(barrelQueue.front());
				barrelQueue.pop();
				for(size_t i = 0; i < barrelVect::n; ++i)
				{
					auto el = curr_vect[i];
					if(el == 0)
						continue;
					

					curr_vect[i] = 0;
					if(!h.insert(curr_vect))
					{
						barrelQueue.push(curr_vect);
						++nextLevelItems;
					}
					curr_vect[i] = el;

					for(size_t j = 0; j < barrelVect::n; ++j)
					{
						auto elPrime = curr_vect[j];
						if(j == i || elPrime == maxValues[j])
							continue;
						auto s = std::min((short)(maxValues[j] - elPrime), (short)el);
						if(s == 0)
							continue;
						curr_vect[i] -= s;
						curr_vect[j] += s;
						if(!h.insert(curr_vect))
						{
							barrelQueue.push(curr_vect);
							++nextLevelItems;
						}
						curr_vect[i] += s;
						curr_vect[j] -= s;

					}
				}
			}
			currLevelItems = nextLevelItems;
		}
		printf("%lu %d\n", h.size(), maxDistance);
		h.clear();
	}

	return 0;
}
