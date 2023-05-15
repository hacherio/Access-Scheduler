#include "login.h"
#include <iostream>
// for setting directory permissions
#include <unistd.h> 
// for color coding text taken from ansi code
#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define blue    "\x1b[34m"
#define reset   "\x1b[0m" // to set to default

using namespace std;

int main(int argc, char *argv[]){
  string suffix = "@elnux";
  if(argc != 2){
    cerr << red << "Usage: username@elnux" << reset << endl;
    exit(-1);
  }
  if(string(argv[1]).find(suffix) == string::npos){
    cerr << red << "Error: User needs '@elnux' at the end." << reset << endl;
    exit(-1);
  }

  // retrieve new username 
  string user = argv[1];
  string userElnux = user.substr(0, user.size() - suffix.size());
  // retieve password
  string pwd = "";
  int attempts = 0;
  int auth = -1;
  int numOption = 0;
  pqueue_arrival credentials = read_workload("loginStorage.txt");
  // for login authentication check
  while((auth == -1) && attempts < 3){
    cout << blue << "Password: " << reset;
    cin >> pwd;

    // picking a scheduler option
    cout << "\n";
    cout << blue << "List of scheduler options: " << reset << "\n";
    cout << blue << "[1] mlfq " << reset << "\n";
    cout << blue << "[2] mystery " << reset << "\n";
    cout << blue << "Type a number: " << reset;
    cin >> numOption;
    if(numOption == 1)
      auth = authenticateUser(userElnux, pwd, mlfq(credentials, 2));
    else if (numOption == 2)
      auth = authenticateUser(userElnux, pwd, mystery(credentials));
    else
      cerr << red << "Invalid option.\n" << reset;

    // check if authenticated
    if(auth == -1){
      cerr << red << "Invalid password or username.\n" << reset;
      attempts++;
    }
  }

  // traverse directories with different access levels 
  if(auth > -1){
    cout << "\n";
    cout << green << "Successfully logged in!" << reset << "\n";

    // prints out work from scheduler 
    show_workload(credentials);
    if(numOption == 1)
      show_metrics(mlfq(credentials, 2));
    if(numOption == 2)
      show_metrics(mystery(credentials));

    //  traverse for access levels by decrement
    for(int level = 2; level > -1; level--) {
      string dirName = "level-" + to_string(level);
      // in which the user change directory
      if(chdir(dirName.c_str()) == -1) {
        cerr << red << "Cannot switch to this specific directory" << "\n" << reset;
        exit(-1);
      }

      // those who can access -> create file
      if (auth <= level) {
        // txt file created to show which directory has been access
        FILE *inFile = fopen("accessed.txt", "w");
        if (inFile == NULL){
          cerr << red << "Cannot create file" << reset << endl;
          exit(-1);
        }
        fputs("This file has been accessed", inFile);
        fclose(inFile);
        // cannot swtich current directories to parent
        if(chdir("..") == -1) {
          cerr << red << "Cannot change directory" << reset << endl;
          exit(-1);
        }
      }
    }
  } 
  else{
    cerr << "User doesn't have authorization " << endl;
    exit(-1);
  }
}