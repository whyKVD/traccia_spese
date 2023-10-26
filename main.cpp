#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

char* getInput(char *str);
char* allocString(char *str, char *buffer);

struct Trx{
  double amount;
  char dateTime[17];
  char description[256];
  bool isExpense;
};

struct Trx* newTrx(double amount,
                   char *dateTime,
                   char *description,
                   bool isExpense = true){
  Trx* trx = new Trx;
  trx->amount = amount;
  strcpy(trx->dateTime,dateTime);
  strcpy(trx->description,description);
  trx->isExpense = isExpense;

  return trx;
}

void stampTrx(Trx* trx){
  cout << "Trx:{" << endl;
  cout << "\tamount: " << trx->amount << "," << endl;
  cout << "\tdateTime: " << trx->dateTime << "," << endl;
  cout << "\tdescription: " << trx->description << "," << endl;
  cout << "\tisExpense: " << trx->isExpense << "," << endl;
  cout << "}" << endl;
}

void insertTrx(Trx *trx);

int main(int argc, char *argv[]) {

  char *username;
  char buffer[256];
  Trx *trx;

  if (argc >= 2) {
    allocString(username, argv[1]);
  } else {
    cout << "Benvenuto come ti chiami?\t";
    username = getInput(username);
  }

  cout << username; 

  insertTrx(trx);

  if(username){
    delete username;
    username = nullptr;
  }
  if(trx){
    delete trx;
    trx = nullptr;
  }
  return 0;
}

char *getInput(char *str){
  char buffer[256] = {};
  char c;
  do{
    c = getchar();
    buffer[strlen(buffer)] = c;
  }while(c != '\n' && strlen(buffer) < sizeof(buffer));
  buffer[strlen(buffer)-1] = '\0';
  str = (char*) malloc(strlen(buffer));
  strcpy(str,buffer);
  return str;
}

char* allocString(char *str, char *buffer){
  str = (char*) malloc(strlen(buffer));
  strcpy(str,buffer);
  return str;
}

void insertTrx(Trx*trx){
  double amount;
  cout << "amount:\t";
  cin >> amount;
  getchar();
 
  cout << "dateTime:\t";
  char *dateTime;
  dateTime = getInput(dateTime);

  cout << "description:\t";
  char *description;
  description = getInput(description);
  
  trx = newTrx(amount,dateTime,description);
 
  stampTrx(trx);
  if(dateTime){
    delete dateTime;
    dateTime = nullptr;
  }
  if(description){
    delete description;
    description = nullptr;
  }
}
