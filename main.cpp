#include<stdio.h>
#include<bits/stdc++.h>

using namespace std;

class Record {
    protected:
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
};


class RecordStore {
      private:
      Record* records; //pointer to class record
      int numRecords;
      double cashBalance;
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
      deleteRecord(i);
      cout << "You bought '" << title << "' for INR" << price
      << endl;
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
      deleteRecord(i);
      cout << "You bought " << records[i].title << " for $" << price << endl;
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
      cout << "Cash Balance: INR" << cashBalance << endl;
      }
};




int main() {
RecordStore* store=new RecordStore;
store->addRecord("Album 1", "Artist 1", 10.99, 1);  //pass by value
store->addRecord("Album 2", "Artist 2", 12.49, 2);
store->addRecord("Album 3", "Artist 3", 9.99, 3);
store->listRecords();
store->displayCashBalance();
store->buyRecord("Album 2");
store->listRecords();
store->displayCashBalance();
store->deleteRecord(0);
store->listRecords();
store->displayCashBalance();
store->buyRecord(3);
store->listRecords();
store->displayCashBalance();
store->buyRecord("Album 2");
return 0;
}