        #include "header.h"
        //#include "builtin.c"
        //#include "syscomm.c"

        //extern int (**builtin_func)(char **);
        /*extern int my_cd(char **);
        extern int my_pwd(char **);
        extern int my_echo(char **);
        */
        int my_execute(char **args)
        {
          int done=0;
          //empty command
          if(args[0]==NULL)
            return 1;

        //check input rdirect, output redirct
          int i;
          for ( i=0; args[i]!=NULL;  i++)
          {
            //output redirct
            if(strcmp(args[i],">")==0)
            {
              done=1;
             int fd;
            // open the file to replace stdout
            fd = open(args[i+1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if(fd == -1){
        	     perror("Failed to open file");
               exit(1);
            }
            close(1); // not required, but a good practice

            // use dup2() to duplicate the fd
            if(dup2(fd, 1) != 1){  // 1 refers to stdout
        	   perror("dup2 fail");
             exit(1);
           }
            args[i]=NULL;
            commandRun(args);
            // close the original fd
            close(fd);
            freopen("/dev/tty","w",stdout);
            }
            //output append redirct
            else if(strcmp(args[i],">>")==0)
            {
              done=1;
              int fd;
            // open the file to replace stdout
            fd = open(args[i+1], O_WRONLY | O_APPEND | O_CREAT  , 0644);
            if(fd == -1){
          perror("Failed to open file");
            }
            close(1); // not required, but a good practice

            // use dup2() to duplicate the fd
            if(dup2(fd, 1) != 1)  // 1 refers to stdout
             perror("dup2 fail");
            args[i]=NULL;
              commandRun(args);
            // close the original fd
            close(fd);
            freopen("/dev/tty","w",stdout);
          }

            //output redirct
            else if(strcmp(args[i],"<")==0)
            {
              done=1;
              int fd;
            // open the file to replace stdout
            fd = open(args[i+1], O_RDONLY, 0644);
            if(fd == -1){
        	     perror("Failed to open file");
               exit(1);
            }
            close(0); // not required, but a good practice

            // use dup2() to duplicate the fd
            if(dup2(fd, 0) == -1){  // 1 refers to stdout
        	   perror("dup2 fail");
             exit(1);
           }
            args[i]=NULL;
            commandRun(args);
            // close the original fd
            close(fd);
            freopen("/dev/tty","r",stdin);
            }

          //iterate in list of buitin commands to match the input command
          //int n=my_num_builtins();
         /* for(i=0;i<n;i++)
          {
            if(strcmp(args[0], builtin_str[i])==0)
            {
              //call the corresponding builin command function
              (*builtin_func[i])(args);
              return 1;
            }
          }*/

          }
          if (done!=1) {
            commandRun(args);
          }
        }


        int commandRun(char **args)
        {
          //check which buitin function this command is
          if(strcmp(args[0],"pwd")==0)
            return my_pwd(args);
          else if(strcmp(args[0],"echo")==0)
            return my_echo(args);
          else if(strcmp(args[0],"cd")==0)
            return my_cd(args);
            else if(strcmp(args[0],"pinfo")==0)
            return my_pinfo(args);
          else if (strcmp(args[0],"jobs")==0)
            return my_jobs();
          else if (strcmp(args[0],"fg")==0)
            return my_fg(args);
          else if (strcmp(args[0],"killallbg")==0)
          return my_killallbg();
          else if(strcmp(args[0],"quit")==0)
          return my_quit();
          else if(strcmp(args[0],"kjob")==0)
          return my_kjob(args);

          //not a buitin command
          //run as a system command
          my_launch(args);
          return 1;
        }
