#include <header.h>
//#include "execute.c"

//READ
#define RL_BUFSIZE 1024
char *my_read_line(void)
{
  int bufsize=RL_BUFSIZE;
  int position=0;
  char *buffer=malloc(sizeof(char)*bufsize);
  int c;

  //unable to allocate buffer
  if(!buffer)
  {
    fprintf(stderr, "allocation error\n");
    exit(1);
  }

  //read character by character
  while(1)
  {
    //we exceeded the buffer, reallocate it
    if(position >= bufsize)
    {
      bufsize += RL_BUFSIZE;
      buffer = realloc(buffer,bufsize);
      if(!buffer)
      {
        fprintf(stderr, "my: allocation error\n");
        exit(1);
      }
    }

    c=getchar();
    //end of list of arguments, make last character=null
    if(c=='\n')
    {
      buffer[position]='\0';
      return buffer;
    }
    else if(c==EOF)
    {
        ctrlD();
      }
    //keep reading
    else
      buffer[position]=c;

    position++;


  }
}
//END READONG


//SPLITTING INTO COMMANDS
#define TOK_BUFSIZE1 64

#define TOK_CDELIM ";\n"
int my_split_command(char* line)
{
  int bufsize = TOK_BUFSIZE1, position = 0;
  char *token;
  char **args,*saveptr;
 //printf("%s\n",line);
  token = strtok_r(line, TOK_CDELIM,&saveptr);
  while (token != NULL) {
//    printf("c:%s\n",token);
    args=my_split_line(token);
    my_execute(args);

    token = strtok_r(NULL, TOK_CDELIM,&saveptr);
  }
  return 1;
}
//END SPLITTING INTO COMMANDS
