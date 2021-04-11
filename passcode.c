#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int random_num()
{
		//srand(time(NULL));
		return rand()%10;
}

char* passcodes()
{
		static  char pass[12];
		srand(time(NULL));
		for(int ind=0; ind<12; ind++)
		{
				int num = random_num();
				pass[ind] = num + '0';
		}
		return pass;
}

int main()
{
		char* passcode = passcodes();
		printf("%s\n", passcode);

}

