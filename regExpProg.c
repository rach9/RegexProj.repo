#include <stdio.h>
#include <regex.h>
#include <string.h>
#define LARAALNUM   "^[a-z0-9A-Z_ ]*$"

int main (int argc, char* argv[])
{

  char input[100 + 1], regExpStr[100 + 1];
  input[0] = '\0';
  regExpStr[0] = '\0';
  int ind = 0,retVal = 0, regExpFlag = 0, inputFlag = 0;
  regex_t re;
  while (ind < argc)
  {
    if (strcmp(argv[ind], "-t")==0)
    {
      if (ind < argc+1 && argv[ind+1])
      {
	strcpy(input, argv[ind+1]);
        input[strlen(argv[ind+1])] = '\0';
        inputFlag = 1;
      }
    }
    if (strcmp(argv[ind], "-r")==0)
    {
      if (ind < argc+1 && argv[ind+1])
      {
	strcpy(regExpStr, argv[ind+1]);
        regExpStr[strlen(argv[ind+1])] = '\0';
        regExpFlag = 1;
     }
    }

    ind++;
  }
  printf("Input: %s, len: = %d\n", (inputFlag==1)?input:"Empty Input",strlen(input));
  
  if (inputFlag)
  {
     if (regcomp(&re, regExpFlag?regExpStr:LARAALNUM, REG_EXTENDED) != 0)
     {
        printf("Failed to compile regular exp %s\n", regExpFlag?regExpStr:LARAALNUM);
        return 0;
     }
  
     retVal = regexec(&re, input, 0, NULL, 0);
     if (retVal == 0)
     {
        printf("Input \"%s\" Confirms to \"%s\" regex\n",input, regExpFlag?regExpStr:LARAALNUM);
     }
     else
     {
        char errorBuf[100];
        printf("!!! Input \"%s\" doesnt confirm to \"%s\" regex !!!\n", input, regExpFlag?regExpStr:LARAALNUM);
        regerror(retVal, &re, errorBuf, 100);
        printf("Error Information:  %s\n", errorBuf);
     }
     regfree(&re);
  }
  return 1;
}
