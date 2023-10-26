#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

void getInput(char *buffer);
char* allocString(char *str, char *buffer);

struct Trx{
  int amount;
  char dateTime[17];
  char description[256];
  bool isExpense;
};

struct Trx* newTrx(int amount,
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
  cout << "\t" << trx->amount << "," << endl;
  cout << "\t" << trx->dateTime << "," << endl;
  cout << "\t" << trx->description << "," << endl;
  cout << "\t" << trx->isExpense << "," << endl;
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
    getInput(buffer);
    username = allocString(username, buffer);
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

void getInput(char *buffer){
  char c;
  while(cin >> c){
    buffer[strlen(buffer)] = c;
    cout << c << endl;
  }
}

char* allocString(char *str, char *buffer){
  str = (char*) malloc(strlen(buffer));
  strcpy(str,buffer);
  return str;
}

void insertTrx(Trx*trx){
  char buffer[256];
  int amount;
  cout << "amount:\t";
  cin >> amount;
  
  cout << "dateTime:\t";
  getInput(buffer);
  char *dateTime;
  dateTime = allocString(dateTime,buffer);

  cout << "description:\t";
  getInput(buffer);
  char *description;
  description = allocString(description,buffer);
  
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
