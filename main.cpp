#include<stdio.h>
#include<bits/stdc++.h>
#include<stdlib.h>
#include<fstream>
#include<iostream>

using namespace std;

 ofstream out("BillDocx.txt"); //writing into bill
 char myBill;
 ifstream in("BillDocx.txt"); //reading from the bill 

class Record {
    private:
    static string storeName;
    int recordID;
    string title;
    string artist;
    double price;

    public:
    Record(string title = "", string artist = "", double price = 0.0,
    int recordID = 1){ //default constructor
    this->title = title;
    this->artist = artist;
    this->price = price;
    this->recordID = recordID;
    }

    void display(){ //inspector function
    cout << "#"<< recordID <<" Title: " << title << " | Artist: "
    << artist << " | Price: INR" << price << endl;
    }
    friend class RecordStore; //friend class

      virtual void billDisplay(){ //virtual function
          out<<endl<<"See you soon";
  }
   virtual ~Record(){                      //virtual destructor
    cout<<"Base destructor called";
  }
};


class RecordStore{
      protected:
      Record* records; 
      int numRecords;
      double cashBalance;
      int noofEmployees;
      public:
      RecordStore(){
      this->records = nullptr;
      this->numRecords = 0;
      this->cashBalance = 0.0;
      } //default constructor
      ~RecordStore() { //destructor
      delete[] records;
      }

      void addRecord(const string& title, const string& artist, double
      price, int recordID) { //pass by reference
      Record* newRecords = new Record[numRecords + 1]; //dynamic memory allocation

      for (int j=0;j< numRecords;j++) {
        newRecords[j] = records[j];
      }
      newRecords[numRecords] = Record(title, artist, price,
      recordID);
      delete[] records; //deletes array
      records = newRecords;
      ++numRecords;
      }
      
      void listRecords() const{
      cout << "Records in the store:" << endl;
      for (int i = 0; i < numRecords; ++i) {
      records[i].display();
      }
      if(numRecords == 0){
      cout<<"No records available.\n";
      }
      }
      
      void buyRecord(const string& title) { //mutator function

      for (int i = 0; i < numRecords; ++i) {

      if (records[i].title == title) {
      double price = records[i].price;
      cashBalance += price;
     
      cout << "You bought '" << records[i].title << "' for INR" << price
      << endl;
      out<<title<<"|-----------------------------------------------------"<<price<<"INR"<<endl;

       deleteRecord(i);
      return;
      }
      }
      cout << "Record not found in the store." << endl;
      }


      void buyRecord(const int& recordID) { //function overloading
      for (int i = 0; i < numRecords; ++i) {
      if (records[i].recordID == recordID) {
      double price = records[i].price;
      cashBalance += price;
     
      cout << "You bought " << records[i].title << " for INR" << price << endl;
       out<<records[i].title<<"|-----------------------------------------------------"<<price<<"INR"<<endl;

        deleteRecord(i);
      return;
      }
      }
      cout << "Record not found in the store." << endl;
      }
      void deleteRecord(int index) {
      if (index < 0 || index >= numRecords) {
      return;
      }
      for (int i = index; i < numRecords - 1; ++i) {
      records[i] = records[i + 1];
      }
      --numRecords;
      cout << "Record " << index+1 << " deleted from the store." <<
      endl;
      }
      void displayCashBalance(){
      out << "Final Amount--------------------------------------------: INR" << cashBalance << endl;
      }

      void countEmployees(){
        cout<<"Enter the number of employees at the store";
        cin>>noofEmployees;
      }
};

class Employee: public RecordStore{ //inheritance
  private:
  string  employeeName;
  int employeeID;

  public:
  Employee(string employeeName, int employeeID ){
    this->employeeName=employeeName;
    this->employeeID=employeeID;
  }

  void EmployeeDetails(){
    cout<<"Name: "<<employeeName<<endl;
    cout<<"Id: "<<employeeID<<endl;
  }


  
};

class Message: public Record{ //multiple inheritance
    int num;
    public:
    Message(){
      cout<<"Derived Constructor";
    }
   void billDisplay(){ 
          out<<endl<<"thank you for your purchase!";
  }
  ~Message(){
    cout<<"Derived Destructor"; 
  }


};


int main() {
  string cname;
  int cid;
  string aname,aauthor;
  float aprice;
  int aid;
  int purchaseId;
  string purchaseName;
  int purchaseChoice;

        
  
  cout<<"____________________"<<endl;
  cout<<"---------------------Cashier's Details:--------------------"<<endl;
  cout<<"Enter Name:";cin>>cname;
  cout<<"Enter ID:";cin>>cid;
  cout<<"____________________"<<endl;
  Employee* cashier=new Employee(cname,cid); //pointer to class record
  Record* r;
  Message recordbill;
  r=&recordbill; //virtual function override
  out<<"____________BILL_____________"<<endl;
  out<<"Your Cashier: "<<cname<<endl;
  out<<"ITEMS----------------------------------------PRICE"<<endl;
system("cls");// clear screen
int c=0;

do{
      cout<<"\n________<<MENU>>___________"<<endl;
      cout<<"Enter your choice:"<<endl;
      cout<<"1.Enter Records"<<endl;
      cout<<"2.Display Records"<<endl;
      cout<<"3.Buy Record"<<endl;
      cout<<"4.Read Bill"<<endl;
      cout<<"5.Exit"<<endl;

      cin>>c;
      switch(c){
        case 1:
          cout<<"----Enter Record----"<<endl;
          
          cout<<"Enter Name, Artist, Price and Id:";
          cin>>aname>>aauthor>>aprice>>aid;
          cashier->addRecord(aname,aauthor,aprice,aid);  //pass by value
          break;

        case 2:
          cout<<"----Display Records----"<<endl;
          cashier->listRecords();
          break;

        case 3:
          cout<<"(1)Record Id or (2)Record Name:"<<endl;
          cin>>purchaseChoice;
          if(purchaseChoice==1){
            cout<<"Enter Id:";
            cin>>purchaseId;

            cashier->buyRecord(purchaseId);
          }
          else{
            cout<<"Enter Name:";
            cin>>purchaseName;
            cashier->buyRecord(purchaseName);
          }
         
       
          break;

        case 4:
          if(in.is_open()){
            while(in){
              myBill=in.get();
              cout<<myBill;
            }
          }
          break;

        case 5:
           r->billDisplay();  
           cashier->displayCashBalance();
          cout<<"Now Exiting";
            break;
          
        default:cout<<"Invalid choice!";
      }

  }
while(c!=5);

 delete r;
// cashier->addRecord("Album 1", "Artist 1", 10.99, 1);  //pass by value
// cashier->addRecord("Album 2", "Artist 2", 12.49, 2);
// cashier->addRecord("Album 3", "Artist 3", 9.99, 3);

// cashier->displayCashBalance();
// cashier->listRecords();
// cashier->displayCashBalance();
// cashier->deleteRecord(0);
// cashier->listRecords();
// cashier->displayCashBalance();
// cashier->buyRecord(3);
// cashier->listRecords();
// cashier->displayCashBalance();
// cashier->buyRecord("Album 2");
return 0;
}