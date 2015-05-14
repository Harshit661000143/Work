#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
int main(int c, char **v)
{
int status;
pid_t child = fork();
if (child == -1) return 1; //Failed
if (child > 0) { /* I am the parent - wait for the child to finish */
  pid_t pid = waitpid(child, &status, 0);
  if (pid != -1 && WIFEXITED(status)) {
     int low8bits = WEXITSTATUS(status);
     printf("Process %d returned %d" , pid, low8bits);
  }
} else { /* I am the child */
 // do something interesting
  printf("%d", getppid());
//  execl("/bin/ls", "/bin/ls", ".", (char *) NULL); // "ls ."
}
        return 0;
}
