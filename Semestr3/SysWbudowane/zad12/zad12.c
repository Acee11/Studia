#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <memory.h>
#define METHOD_B

void strspace1(char *str, size_t n)
{
	size_t last_space = 0;
	while(str[last_space] == ' ' && last_space < n)
		++last_space;
	if(str[last_space] == ' ')
		return;
	--last_space;
	for(size_t i = 0; i < n; ++i)
	{
		if(str[i] == ' ')
		{
			char ch = ' ';
			for(size_t j = last_space; j <= i; ++j)
			{
				char tmp = str[j];
				str[j] = ch;
				ch = tmp;
			}
			++last_space;
		}
	}
}

void strspace2(char *str, size_t n)
{
	int counter = n-1;
	for(int i = n-1; i >= 0; --i)
		if(str[i] != ' ')
			str[counter--] = str[i];
	while(counter >= 0)
		str[counter--] = ' ';
}

int main()
{
	FILE *f = fopen("str","r");
	unsigned long fsize;
	fseek (f , 0 , SEEK_END);
	fsize = ftell(f);
	rewind (f);
	char* buffer = (char*) malloc(fsize+1);
	fread(buffer, 1, fsize, f);
	fclose(f);
	buffer[fsize] = '\0';

	char* res = malloc(fsize+1);
	res[fsize] = '\0';

	clock_t t;
	//sr[sizeof(s)-1] = '\0';
	//strspace2(s,sr,sizeof(s) - 1);
	#ifdef METHOD_A
	t = clock();
	strspace1(buffer, fsize);
	t = clock() - t;
	printf("MethodA   |   %f\n", ((float)t)/CLOCKS_PER_SEC);
	#else
	t = clock();
	strspace2(buffer, fsize);
	t = clock() - t;
	printf("MethodB   |   %f\n", ((float)t)/CLOCKS_PER_SEC);
	//printf("%s\n",buffer);
	#endif
	return 0;
}