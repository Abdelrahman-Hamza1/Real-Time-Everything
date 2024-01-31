/*
 * The fork() function
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
  int i, status;
  pid_t pid;
  void signal_catcher(int);
  
  printf("My process ID is %d\n", getpid());

  pid = fork();
  
  if ( pid == 0 ) {
    printf("I am the child  => PID = %d\n", getpid());
    if ( sigset(SIGINT, signal_catcher) == SIG_ERR ) {
      perror("Sigset can not set SIGINT");
      exit(SIGINT);
    }
    //pause();
    while ( 1 );
  }
  else {
    printf("I am the parent => PID = %d, child ID = %d\n", getpid(), pid);
    printf("In 5 seconds, I will send a SIGINT to my child\n");
    sleep(90);
    kill(pid, SIGINT);
  }
  if (waitpid(pid, &status, 0) == pid) {
     printf("Processe ID %d has terminated (status = %d)\n", pid, WEXITSTATUS(status));
  }
  
  return(0);
}

void signal_catcher(int the_sig)
{
  printf("\nThe child has received SIGINT from parent.\n");
  //sleep(2);
  //exit(1);
  
}
