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
  cout << "\tTrx:{" << endl;
  cout << "\t\tamount: " << trx->amount << "," << endl;
  cout << "\t\tdateTime: " << trx->dateTime << "," << endl;
  cout << "\t\tdescription: " << trx->description << "," << endl;
  cout << "\t\tisExpense: " << trx->isExpense << "," << endl;
  cout << "\t}";
}

struct Era{
	Trx* currentTrx;
 Era* nextEra;
};

struct Era* newEra(Trx* trx){
  Era* era = new Era;
	 era->currentTrx = trx;
  era->nextEra = NULL;
 
  return era;
}

struct TrxEras{
	 Era *rootEra;
};

struct TrxEras* newTrxEras(Era *rootEra){
  TrxEras* eras = new TrxEras;
  eras->rootEra = rootEra;
  
  return eras;
}

void totalExp(TrxEras* eras){
  double exp = .0, earn = .0;
  Era* root = eras->rootEra;
  if(root == NULL){
    cout << "none expense or earning inserted" << endl;
    return;
  }
  
  while(root->nextEra != NULL){
    Trx* trx = root->currentTrx;
    if(trx->isExpense){
      exp += trx->amount;
    }else{
      earn += trx->amount;
    }
    root = root->nextEra;
  }

  Trx* trx = root->currentTrx;
  if(trx->isExpense){
    exp += trx->amount;
  }else{
    earn += trx->amount;
  }

  cout << "Expenses: " << exp << endl;
  cout << "Earnings: " << earn << endl;
  cout << "Balance: " << earn - exp << endl;
}

void insertEra(TrxEras* eras, Era* newEra){
  Era* root = eras->rootEra;
		while(root->nextEra != NULL){
    root = root->nextEra;
  }
  root->nextEra = newEra;
}

void printEras(TrxEras* eras){
  Era* root = eras->rootEra;
  if(root == NULL){
    cout << "empty list" << endl;
    return;
  }
  cout << "Eras{" << endl;
  while(root->nextEra != NULL){
    stampTrx(root->currentTrx);
    cout << "," << endl;
    root = root->nextEra;
  }
  stampTrx(root->currentTrx);
  cout << endl << "}" << endl;
}

TrxEras* insertTrx(TrxEras *eras);

int main(int argc, char *argv[]) {

  char *username;
  TrxEras *eras = NULL;

  if (argc >= 2) {
    allocString(username, argv[1]);
  } else {
    cout << "Benvenuto come ti chiami?\t";
    username = getInput(username);
  }
 
  char action;
  do{
    cout << "i->newTrx, s->printEra, q->quit: ";
    cin >> action;
    switch(action){
      case 'i':
        cout << "insert a new transaction" << endl;
        eras = insertTrx(eras);
        break;
      case 's':
        cout << "printing all the ears until now" << endl;
        printEras(eras);
        break;
      case 'c':
        cout << "total earning and expense" << endl;
        totalExp(eras);
        break;
      case 'q':
        cout << "GoodBye " << username << endl;
        printEras(eras);
        break;
      default:
        cout << "command not codified retry" << endl;
    }
  }while(action != 'q');

  if(username){
    delete username;
    username = nullptr;
  }
  if(eras){
    delete eras;
    eras = nullptr;
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

TrxEras* insertTrx(TrxEras *eras){
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

  bool isExpense = true;
  char c;
  cout << "is it an expense(n: no, otherwise: yes): ";
  cin >> c;
  getchar();
  if(c == 'n'){
    isExpense = false;
  }
  
  Trx *trx = newTrx(amount,dateTime,description,isExpense);

  if(eras == NULL){
    eras = newTrxEras(newEra(trx));
  }else{
    insertEra(eras,newEra(trx));
  }
 
  if(dateTime){
    delete dateTime;
    dateTime = nullptr;
  }
  if(description){
    delete description;
    description = nullptr;
  }

  return eras;
}
