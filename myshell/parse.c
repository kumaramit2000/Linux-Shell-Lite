#include <header.h>
//PARSING
#define TOK_BUFSIZE 64
#define TOK_DELIM " \t\n\r"

char ** my_split_line(char *line)
{
  /*int bufsize=TOK_BUFSIZE, position=0;
  char *token;
  char **tokens=malloc(bufsize*sizeof(char *));

  //can't allocate buffer
  if(!tokens)
  {
    fprintf(stderr, "allocation\n");
    exit(1);
  }

  //save arguments in a 2-d array tokens
  token=strtok(line, TOK_DELIM);
  while(token!=NULL)
  {
    tokens[position]=token;
    //printf("%s:",token);
    position++;

    //if buffer full, reallocate buffer
    if(position>=bufsize)
    {
      bufsize += TOK_BUFSIZE;
      tokens=realloc(tokens, bufsize*sizeof(char*));
      if(!tokens)
      {
        fprintf(stderr, "my: allocation error\n");
        exit(1);
      }
    }

    //read next argument
    token=strtok(NULL, TOK_DELIM);
  }
  tokens[position]=NULL;
  //my_execute(tokens);
  return tokens;
  */
  int bufsize=TOK_BUFSIZE, position=0;
  char **tokens=malloc(bufsize*sizeof(char *));
  char *token;

  //can't allocate buffer
  if(!tokens)
  {
    fprintf(stderr, "my: allocation\n");
    exit(1);
  }

  //save arguments in a 2-d array tokens
  token=strtok(line, TOK_DELIM);
  while(token!=NULL)
  {
    tokens[position]=token;
    //printf("%s:",token);
    position++;

    //if buffer full, reallocate buffer
    if(position>=bufsize)
    {
      bufsize += TOK_BUFSIZE;
      tokens=realloc(tokens, bufsize*sizeof(char*));
      if(!tokens)
      {
        fprintf(stderr, "my: allocation error\n");
        exit(1);
      }
    }

    //read next argument
    token=strtok(NULL, TOK_DELIM);
  }
  tokens[position]=NULL;
  return tokens;

}
//END READING ONE COMMAND
