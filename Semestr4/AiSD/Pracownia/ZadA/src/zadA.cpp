#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <iostream>



void dfs(int i, int j, bool** visited, char** tab, int n, int m)
{
	std::vector< std::pair<short,short> > stack;
	std::pair<short,short> curr_v;
	stack.push_back({i,j});
	visited[i][j] = true;
	while(!stack.empty())
	{
		curr_v = stack.back();
		stack.pop_back();
		
		switch(tab[curr_v.first][curr_v.second])
		{
			case 'A':
				break;
			case 'B':
				i = curr_v.first;
				j = curr_v.second - 1;
				if(j >= 0 && !visited[i][j] && tab[i][j] >= 'D' && tab[i][j] <= 'F')
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i += 1;
				j += 1;
				if(i < n && !visited[i][j] && (tab[i][j] == 'C' || tab[i][j] == 'D' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				break;
			case 'C':
				i = curr_v.first;
				j = curr_v.second - 1;
				if(j >= 0 && !visited[i][j] && tab[i][j] >= 'D' && tab[i][j] <= 'F')
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i -= 1;
				j += 1;
				if(i >= 0 && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'E' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				break;
			case 'D':
				i = curr_v.first;
				j = curr_v.second + 1;
				if(j < m && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'C' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i -= 1;
				j -= 1;
				if(i >= 0 && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'E' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				break;
			case 'E':
				i = curr_v.first;
				j = curr_v.second + 1;
				if(j < m && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'C' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i += 1;
				j -= 1;
				if(i < n && !visited[i][j] && (tab[i][j] == 'C' || tab[i][j] == 'D' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				break;
			case 'F':
				i = curr_v.first;
				j = curr_v.second + 1;
				if(j < m && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'C' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i = curr_v.first;
				j = curr_v.second - 1;
				if(j >= 0 && !visited[i][j] && (tab[i][j] == 'D' || tab[i][j] == 'E' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i = curr_v.first + 1;
				j = curr_v.second;
				if(i < n && !visited[i][j] && (tab[i][j] == 'C' || tab[i][j] == 'D' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				i = curr_v.first - 1;
				j = curr_v.second;
				if(i >= 0 && !visited[i][j] && (tab[i][j] == 'B' || tab[i][j] == 'E' || tab[i][j] == 'F'))
				{
					stack.push_back({i,j});
					visited[i][j] = true;
				}
				break;
			default:
				printf("error???\n");
				break;
		}
	}
	/*
	*/
}

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	getchar();
	char **tab = new char*[n];
	char* res;
	bool **visited = new bool*[n];

	int city = 0;

	for(int i = 0; i < n; ++i)
	{
		tab[i] = new char[m+2];
		visited[i] = new bool[m];
	}
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
			visited[i][j] = false;
		res = fgets(tab[i], m+2, stdin);
		if(res == NULL)
		{
			fprintf(stderr,"error\n");
			return 1;
		}
	}

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < m; ++j)
		{
			if(visited[i][j] || tab[i][j] == 'A')
				continue;
			dfs(i, j, visited, tab, n, m);
			++city;
		}
	}

	printf("%d\n", city);

	return 0;
}