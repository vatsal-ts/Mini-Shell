#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <linux/limits.h>
#include <limits>
#include <fcntl.h>
#include <time.h>
#include <algorithm>
// unistd, linux based
#define clear() printf("\033[H\033[J")

#define micros 1313131

void reset() {}

using namespace std;

void add_hist(string s)
{
  fstream outfile;

  outfile.open("/tmp/history.txt", std::ios_base::app); // append instead of overwrite
  outfile << s << "\n";
}

string replaceif(string s)
{
  if (s[0] == '$')
  {
    string prime(s.begin() + 1, s.end());
    auto env_val = getenv(prime.c_str());

    if (env_val != NULL)
    {
      //cout<<"I should replace "<<s<<" with "<<env_val;
      return env_val;
    }
  }
  return s;
}

int isSubstring(string s1, string s2)
{
  int M = s1.length();
  int N = s2.length();

  /* A loop to slide pat[] one by one */
  for (int i = 0; i <= N - M; i++)
  {
    int j;

    /* For current index i, check for
 pattern match */
    for (j = 0; j < M; j++)
      if (s2[i + j] != s1[j])
        break;

    if (j == M)
      return i;
  }

  return -1;
}

bool isBlankLine(char const *line)
{
  for (char const *cp = line; *cp; ++cp)
  {
    if (!isspace(*cp))
      return false;
  }
  return true;
}

bool isBlankLine(std::string const &line)
{
  return isBlankLine(line.c_str());
}

vector<string> tokenize(string s, char param)
{
  vector<string> tokens;
  stringstream check1(s);

  string intermediate;

  while (getline(check1, intermediate, param))
  {
    intermediate.erase(std::remove(intermediate.begin(), intermediate.end(), '"'), intermediate.end());
    intermediate.erase(std::remove(intermediate.begin(), intermediate.end(), '\''), intermediate.end());
    intermediate = replaceif(intermediate);
    tokens.push_back(intermediate);
  }

  return tokens;
}

int executeArgs(vector<string> seperated, int &i, string filename, int type)
{

  char *args[seperated.size() + 1];
  for (int i = 0; i < seperated.size(); i++)
  {
    char *cstr = new char[seperated[i].length() + 1];
    strcpy(cstr, seperated[i].c_str());
    args[i] = cstr;
  }
  args[seperated.size()] = NULL;

  // Forking a child
  pid_t pid = fork();

  if (pid == -1)
  {
    printf("\nFailed forking child..");
    i = -2011;
  }
  else if (pid == 0)
  {
    int fd;
    if (type == 0)
    {
      //append mode
      fd = open(filename.c_str(), O_CREAT | O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
      dup2(fd, 1);
    }
    else
    {
      //write mode
      fd = open(filename.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
      dup2(fd, 1);
    }
    if (execvp(seperated[0].c_str(), args) < 0)
    {
      i = 2020;
    }
    else
    {
      i = -4747; //yipeee
    }
    perror("execvp failed");
    exit(0);
    close(fd);
  }
  else
  {
    // waiting for child to terminate
    wait(NULL);
    i = -1000;
  }
  kill(pid, 1);
  return 0;
}

int executeArgs(vector<string> seperated, int &i)
{
  // cout<<"HERE PAKKA";

  // for(auto K:seperated){
  //   cout<<"in loop seperated"<<K<<"  ";
  // }

  //   vector<char*> args;
  //   //args.reserve(seperated.size());
  //   int ct=0;
  //   for (string sp : seperated)
  //   {
  //     cout<<"im sp "<<sp<<"\n";
  //     args.push_back(const_cast<char *>(sp.c_str()));
  //     cout<<" am i not doing anything  "<<args[ct++]<<"\n";
  //   }
  //  args.push_back(nullptr);

  //   for(size_t i=0;i<args.size();){
  //     cout<<"  in loop args  "<<args[i++]<<"\n";
  //   }

  char *args[seperated.size() + 1];
  for (int i = 0; i < seperated.size(); i++)
  {
    char *cstr = new char[seperated[i].length() + 1];
    strcpy(cstr, seperated[i].c_str());
    args[i] = cstr;
  }
  args[seperated.size()] = NULL;

  // for(size_t i=0;i<seperated.size();){
  //   cout<<"  in loop args  "<<args[i++]<<"\n";
  // }

  // Forking a child
  pid_t pid = fork();

  if (pid == -1)
  {
    printf("\nFailed forking child..");
    i = -2011;
  }
  else if (pid == 0)
  {
    if (execvp(seperated[0].c_str(), args) < 0)
    {
      i = 2020;
    }
    else
    {
      i = 4747; //yipeee
    }
    perror("Invalid Command or Dependencies Installed incorrectly ");
    exit(0);
  }
  else
  {
    // waiting for child to terminate
    wait(NULL);
    i = -1000;
  }
  kill(pid, 1);
  return 0;
}

void piping(vector<string> seperated, vector<string> seperated2, int &i)
{

  char *args[seperated.size() + 1];
  for (int i = 0; i < seperated.size(); i++)
  {
    char *cstr = new char[seperated[i].length() + 1];
    strcpy(cstr, seperated[i].c_str());
    args[i] = cstr;
  }
  args[seperated.size()] = NULL;

  int des_p[2];
  if (pipe(des_p) == -1)
  {
    perror("Pipe failed");
    exit(1);
  }
  pid_t p1, p2;
  p1 = fork();
  if (p1 == 0) //first fork
  {
    close(STDOUT_FILENO); //closing stdout
    dup(des_p[1]);        //replacing stdout with pipe write
    close(des_p[0]);      //closing pipe read
    close(des_p[1]);

    execvp(seperated[0].c_str(), args);
    perror("execvp of first part failed");
    exit(1);
  }

  char *args2[seperated2.size() + 1];
  for (int i = 0; i < seperated2.size(); i++)
  {
    char *cstr = new char[seperated2[i].length() + 1];
    strcpy(cstr, seperated2[i].c_str());
    args2[i] = cstr;
  }
  args2[seperated2.size()] = NULL;

  p2 = fork();
  if (p2 == 0) //creating 2nd child
  {
    close(STDIN_FILENO); //closing stdin
    dup(des_p[0]);       //replacing stdin with pipe read
    close(des_p[1]);     //closing pipe write
    close(des_p[0]);

    execvp(seperated2[0].c_str(), args2);
    perror("execvp of second part failed");
    exit(1);
  }

  close(des_p[0]);
  close(des_p[1]);
  wait(0);
  wait(0);
  i = 1;
  kill(p1, SIGTERM);
  kill(p2, SIGTERM);
  return;
}

void executeArgsinput(vector<string> seperated, int &status, string filename)
{

  char *args[seperated.size() + 1];
  for (int i = 0; i < seperated.size(); i++)
  {
    char *cstr = new char[seperated[i].length() + 1];
    strcpy(cstr, seperated[i].c_str());
    args[i] = cstr;
  }
  args[seperated.size()] = NULL;
  pid_t readHere = fork();
  if (readHere == 0)
  {
    int readMode;
    readMode = open(filename.c_str(), O_RDONLY | O_CREAT, 0666);
    dup2(readMode, 0);
    execvp(seperated[0].c_str(), args);
    perror("execvp failed");
    close(readMode);
    exit(0);
  }
  wait(NULL);
  kill(readHere, SIGTERM);
  // free(input_str);
  // continue;
}

int main(/*int argc, char **argv*/)
{

  auto env_thisuser = getenv("USER");
  string one(env_thisuser);
  string final = "./home/" + one;

  cout << "\n\n\n\n\n\n*********WELCOME TO SHELL********** \n\nCreated by Vatsal Gupta, RNO:200101105\n\n\n\n\n";
  usleep(1.3 * micros);
  clear();
  std::streambuf *cinbuf = std::cin.rdbuf();
  std::streambuf *coutbuf = std::cout.rdbuf();
  // necessary for controlling input output
  // ios_base::sync_with_stdio(false);
  // std::cin.tie(0);

  // Run command loop.

  /* #region   */
  string mainline;
  string *arguesplit;
  FILE *redirected = NULL;

  //string has a beautiful advantage no need to do anything, mystring goes out of scope and everything is cleaned up automatically
  //so freeing up memory explicitly isnt necessary
  char *cwd;
  char buff[2024];

  while (1)
  {
    std::cin.rdbuf(cinbuf);   //reset to standard input again
    std::cout.rdbuf(coutbuf); //reset to standard output again
    //printing working directory
    cwd = getcwd(buff, 2025);
    printf("%s $ ", cwd);

    //taking input
    std::getline(std::cin, mainline);

    //checking for empty input, if not add to history.
    if (!(isBlankLine(mainline)))
    {
      add_hist(mainline);
    }
    else
    {
      //reset();
      //reset();
      continue;
    }

    /*
string s = mainline;
      if (s.find('|') != std::string::npos)
        ; // found piping
      else if(s.find('>') != std::string::npos){
        vector<string> mainvec;
        mainvec=tokenize(s,'>');
        fstream secondly;
        secondly.open((mainvec[1]).c_str());
      }

        ;//found >
      else if(s.find('<') != std::string::npos){}
      ; //found <
      else if(s.find(">>") != std::string::npos){}
      ;//found >>
*/

    string s = mainline;
    if (s.find('|') != std::string::npos)
    {
      //cout << "\n\n\nPIPE\n\n\n";
      vector<string> temp = tokenize(mainline, '|');
      auto mainline1 = tokenize(temp[0], ' ');
      auto mainline2 = tokenize(temp[1], ' ');
      int status = 0;
      if (mainline2[0].empty())
      {
        vector<string> mainline2prime(mainline2.begin() + 1, mainline2.end());
        mainline2 = mainline2prime;
      }

      piping(mainline1, mainline2, status);
      continue;
    }
    // found piping

    //found >
    else if (s.find('<') != std::string::npos)
    {
      //cout << "\n\n\n<\n\n\n";
      int temp;
      temp = s.find('<');
      mainline = s.substr(0, temp);

      auto filename = s.substr(temp + 1, s.length());
      // ifstream out(filename.c_str(), ios::in);
      // cin.rdbuf(out.rdbuf());
      /* #region   */
      //parse or tokenize input
      vector<string> seperated = tokenize(mainline, ' ');

      //check for environment variables
      auto env_val = getenv(mainline.c_str());

      if (env_val != NULL)
      {
        cout << env_val << "\n";
        //reset();
        //reset();
        continue;
      }

      //search in path

      //parameter to check if system execution was succesful
      else
      {
        int status;

        executeArgsinput(seperated, status, filename);
        //cout<<"\n\n\n"<<param<<"\n\n\n";

        //exiting child process after entering main
        if (status < 0)

        {
          continue;
        }
      }

      /* #endregion */

    } //found <

    else if (s.find(">>") != std::string::npos)
    {
      //cout << "\n\n\n>>\n\n\n";
      int temp;
      temp = s.find(">>");
      auto filename = s.substr(temp + 2, s.length());
      ofstream out(filename.c_str(), ios::app);
      cout.rdbuf(out.rdbuf());
      mainline = s.substr(0, temp);

      /* #region   */
      //parse or tokenize input
      vector<string> seperated = tokenize(mainline, ' ');

      //check for environment variables
      auto env_val = getenv(mainline.c_str());

      if (env_val != NULL)
      {
        cout << env_val << "\n";
        //reset();
        //reset();
        continue;
      }

      //checking for cd

      else if (seperated[0] == "cd")
      {
        if (seperated.size() == 1)
        {
          chdir("/");
          chdir(final.c_str());
        }
        else
        {
          chdir(seperated[1].c_str());
        }
        //reset();
        //reset();
        continue;
      }

      //history criterion
      else if (mainline == "history")
      {
        fstream abouttogo;

        abouttogo.open("/tmp/history.txt");
        string s;
        while (getline(abouttogo, s))
        {
          cout << s << "\n";
        }
        //reset();
        //reset();
        continue;
      }
      //

      //checking exit criterion
      else if (mainline == "exit" || mainline == "quit" || mainline == "x")
      {
        remove("/tmp/history.txt");
        cout << "Exiting Shell, Goodbye!\n";
        break;
      }

      //search in path

      //parameter to check if system execution was succesful
      else
      {
        int status;

        executeArgs(seperated, status, filename, 0);
        //cout<<"\n\n\n"<<param<<"\n\n\n";

        //exiting child process after entering main
        if (status < 0)

        {
          continue;
        }
      }

      /* #endregion */
    }
    else if (s.find('>') != std::string::npos)
    {
      //cout << "\n\n\n>\n\n\n";
      int temp;
      temp = s.find('>');
      auto filename = s.substr(temp + 1, s.length());
      ofstream out(filename.c_str(), ios::out);
      cout.rdbuf(out.rdbuf());

      mainline = s.substr(0, temp);

      /* #region   */
      //parse or tokenize input
      vector<string> seperated = tokenize(mainline, ' ');

      //check for environment variables
      auto env_val = getenv(mainline.c_str());

      if (env_val != NULL)
      {
        cout << env_val << "\n";
        //reset();
        //reset();
        continue;
      }

      //checking for cd

      else if (seperated[0] == "cd")
      {
        if (seperated.size() == 1)
        {
          chdir("/");
          chdir(final.c_str());
        }
        else
        {
          chdir(seperated[1].c_str());
        }
        //reset();
        //reset();
        continue;
      }

      //history criterion
      else if (mainline == "history")
      {
        fstream abouttogo;

        abouttogo.open("/tmp/history.txt");
        string s;
        while (getline(abouttogo, s))
        {
          cout << s << "\n";
        }
        //reset();
        //reset();
        continue;
      }
      //

      //checking exit criterion
      else if (mainline == "exit" || mainline == "quit" || mainline == "x")
      {
        remove("/tmp/history.txt");
        cout << "Exiting Shell, Goodbye!\n";
        break;
      }

      //search in path

      //parameter to check if system execution was succesful
      else
      {
        int status;

        executeArgs(seperated, status, filename, 1);
        //cout<<"\n\n\n"<<param<<"\n\n\n";

        //exiting child process after entering main
        if (status < 0)

        {
          continue;
        }
      }

      /* #endregion */
    }
    else
    {
      // cout << "\n\nLOVE GENERIC\n\n";
      /* #region   */
      //parse or tokenize input
      vector<string> seperated = tokenize(mainline, ' ');

      //check for environment variables

      if (seperated[0] == "setenv")
      {
        //cout<<"CAME HERE";
        auto term = seperated[1];
        if (setenv(term.c_str(), seperated[3].c_str(), 1))
        {
          cout << "UNABLE TO CHANGE VALUE\n";
        }
        else
        {
          cout << "VALUE CHANGED\n";
        }
        continue;
      }

      if (mainline == "help")
      {
        cout << "Internal Commands are as follows:\n\n";
        cout << "help\nSYNTAX: help\nUsage: Displays this text providing help.\n\n";
        cout << "cd\nSYNTAX: cd dir\nUsage: Change the shell working directory.\nChange the current directory to dir.  \nThe default DIR is the value of the\nHOME shell variable, so if no path is given\nwriting just cd changes shell's working directory to HOME.\n\n";
        cout << "history\nSYNTAX: history\nUsage: displays set of previous entered commands\naccessed from history.txt file stored in tmp folder as per flowchart\n\n";
        cout << "exit<or>quit<or>x\nSYNTAX: exit or x or quit\nUsage:Exits the shell with a \"Exiting Shell,Goodbye\" message\n\n";
        cout<<"clear\nSYNTAX: clear\nUsage:Clears Up shell to make it neater\n\n";
        cout << "Information On Environment Variables are as follows:\n\nprintenv\nSYNTAX: printenv\nprints all environment varaibles\n\nsetenv\nSYNTAX: setenv variable_name = variable_value\n\nUsage:Changes Environment Variables as required\n\nThese values may be checked by employing echo $VAR \nor just writing VAR in the terminal\nan example for this is given in the README.\n\n";
        cout<<"External Commands are as follows:\n\n";
        cout<<"A reasonable subset of the following has been implemented\nman, which, chsh, whereis, passwd, date, cal, clear, \nsleep, alias, unalias, history, apropos, exit, logout,\nshutdown, ls, cat, more, less, touch, cp, mv, rm,\nscript, find, mkdir, cd, pwd, rmdir, chmod, grep\n\n";
        cout<<"information on any particular command can be obtained by writing man <command name> in the shell\nFor example man ls\n\n";
        cout<<"\n\n\nKindly read README for more details.\n\n";
        continue;
      }

      auto env_val = getenv(mainline.c_str());

      if (env_val != NULL)
      {
        cout << env_val << "\n";
        //reset();
        // reset();
        continue;
      }

      //checking for cd

      else if (seperated[0] == "cd")
      {
        if (seperated.size() == 1)
        {
          chdir("/");
          chdir(final.c_str());
        }
        else
        {
          chdir(seperated[1].c_str());
        }
        //reset();
        //reset();
        continue;
      }

      //history criterion
      else if (mainline == "history")
      {
        fstream abouttogo;

        abouttogo.open("/tmp/history.txt");
        string s;
        while (getline(abouttogo, s))
        {
          cout << s << "\n";
        }
        //reset();
        //reset();
        continue;
      }
      //

      //checking exit criterion
      else if (mainline == "exit" || mainline == "quit" || mainline == "x")
      {
        remove("/tmp/history.txt");
        cout << "Exiting Shell, Goodbye!\n";
        break;
      }

      //search in path

      //parameter to check if system execution was succesful
      else
      {
        int status;

        executeArgs(seperated, status);
        //cout<<"\n\n\n"<<param<<"\n\n\n";

        //exiting child process after entering main
        if (status < 0)

        {
          continue;
        }
      }

      /* #endregion */
    }
  }
  return 0;
}