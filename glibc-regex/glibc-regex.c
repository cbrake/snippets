// gcc -Wall -o glibc-regex glibc-regex.c && ./glibc-regex


#include <stdio.h>
#include <string.h>
#include <regex.h>



int main ()
{
	char * source = "this is a test hw_version=10 asdf werwer";
	char * regexString = "hw_version=([0-9]+)";
	size_t maxGroups = 2;

	regex_t regexCompiled;
	regmatch_t groupArray[maxGroups];

	if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
	{
		printf("Could not compile regular expression.\n");
		return 1;
	};

	if (regexec(&regexCompiled, source, maxGroups, groupArray, 0)) {
		printf("regexec error\n");
	}

	unsigned int g = 0;
	for (g = 0; g < maxGroups; g++)
	{
		if (groupArray[g].rm_so == (size_t)-1)
			break;  // No more groups

		char copy[strlen(source) + 1];
		strcpy(copy, source);
		copy[groupArray[g].rm_eo] = 0;
		printf("Group %u: [%2u-%2u]: %s\n",
			g, groupArray[g].rm_so, groupArray[g].rm_eo,
				copy + groupArray[g].rm_so);
	}

	regfree(&regexCompiled);

	return 0;
}
