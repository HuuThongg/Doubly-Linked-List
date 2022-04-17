#include <iostream>
#include <stdexcept>
using namespace std;

template <class T>
class Node {
public:
    T value;
    Node* prev, * next;
    Node(const T& v, Node* p = nullptr, Node* n = nullptr) {
        prev = p; next = n; value = v;
    }
};

// A doubly linked list in which the values are arranged in ascending order.

template <class T>

class OrderedLinkedList {

    friend ostream& operator<<(ostream& out, const  OrderedLinkedList<T>& l) {

        out << "{ ";

        // FILL IN MISSING CODE
        if (!l.isEmpty()){
           Node<T>* current = l.headPtr;
           while (current->next != nullptr) {
               out << current->value << ",";
               current = current->next;
           }
           out << current->value;
        }

        cout << "}";

        return out;

    }

private:

    Node<T> *headPtr, // a pointer to first node or null if list is empty.

            *tailPtr; // a pointer to last  node or null if list is empty.

    int length; // the list length




    // Return a pointer to first node containing v

    // or return nullptr if v is not found.

    Node<T>* findNodeWithValue(const T& v) const {

        // FILL IN MISSING CODE
        Node<T>* temp = headPtr;
        while( temp->next!= nullptr ){
            if(temp->value == v)
                return temp;
            temp = temp->next;
        }
         if(temp->value == v)
            return temp;
        return nullptr;
    }

public:




    // Set headPtr and tailPtr to null and set length to zero.

    OrderedLinkedList() {

        // FILL IN MISSING CODE
        headPtr = nullptr;
        tailPtr = nullptr;
        length = 0;
        

    }




    // Copy constructor.

    OrderedLinkedList(const OrderedLinkedList& otherList) {

        // FILL IN MISSING CODE
        
       headPtr = tailPtr = nullptr;
        length = 0;
        if (otherList.isEmpty())
            return;
        headPtr = new Node<T>(otherList.headPtr->value);
        Node<T>* otherCurrent = otherList.headPtr->next;
        Node<T>* thisPre = headPtr;
        while (otherCurrent != nullptr) {
            thisPre->next = new Node<T> (otherCurrent->value,thisPre);
            otherCurrent = otherCurrent->next;
            thisPre = thisPre->next;
        }
        tailPtr = thisPre;
        length = otherList.length; 
    }
    
    OrderedLinkedList & operator=(const OrderedLinkedList<T>& other){
     if(&other != this){
      while(!isEmpty()){
       Node<T>* toRemove = headPtr;
       headPtr = headPtr->next;
       headPtr->prev = nullptr;
       delete toRemove;
       length--;
      }
      headPtr = new Node<T>(other.headPtr->value);
        Node<T>* otherCurrent = other.headPtr->next;
        Node<T>* thisPre = headPtr;
        while (otherCurrent != nullptr) {
            thisPre->next = new Node<T> (otherCurrent->value,thisPre);
            otherCurrent = otherCurrent->next;
            thisPre = thisPre->next;
        }
        tailPtr = thisPre;
        length = other.length; 
      
     }
     return *this;
    }
    
    OrderedLinkedList & operator+=(const OrderedLinkedList<T>& add){
     tailPtr->next = add.headPtr;
     add.headPtr->prev = tailPtr;
     Node<T>* ptr = add.headPtr;
     while(ptr->next != nullptr)
      ptr = ptr->next;
     tailPtr = ptr;
     return *this;
    }
    
    // Return value in node at given index

    // or throw logic_error if index < 0 or > length-1

    // Message should be "Index out of bounds"

    T& operator[](int index) {

        if (index < 0 || index > length - 1)

            throw logic_error("Index out of bounds");

        // FILL IN MISSING CODE    //  2 5 1 5
        Node<T> *current = headPtr;
        for(int i = 0; i < index;i++)
            current = current->next;
        return current->value;
    }
  

    // Destructor

    ~OrderedLinkedList() {

        // FILL IN MISSING CODE
    clear();


    }

    // Remove all values from the list.

    void clear() {

        // FILL IN MISSING CODE
        while (headPtr != nullptr){
            Node<T>* temp = headPtr;
            headPtr = headPtr->next;
            delete temp; // must delete temp to avoid a memory leak
            length--;
        }
    }
    void insertFirst(const T& v){
     Node<T>*temp = new Node<T>(v,nullptr,headPtr);
     headPtr->prev = temp;
     headPtr = temp;
     length++;
    }
    
    void insert(const T&v , int index){
     if(index < 0 || index > length)
      return;
     if(index == 0)
      insertFirst();
     else{
      Node<T>*pre = headPtr;    //1 2 4 index =2 ; v=3
      for(int i = 0; i < index -1; i++)
       pre = pre->next;
      Node<T>* toInsert = new Node<T>(v,pre, pre->next);
      pre->next = toInsert;
      length++;
     }
    }
    
    void insertAfter(Node<T>* pre, int d){
     Node<T>* toInsert = new Node<T>(d,pre, pre->next);
     pre->next = toInsert;
     length++;
    }
    
    void insertAtEnd(int d){
     Node<T>* toInsert =new Node<T>(d, tailPtr);
     tailPtr->next = toInsert;
     tailPtr = toInsert;
     length++;
    }
    
    void insertAfterHead(int d){
     if(isEmpty())
      return;
     Node<T>*  toInsert = new Node<T>(d,headPtr,headPtr->next);
      headPtr->next = toInsert;
      (toInsert->next)->prev= toInsert;
      length++;
    }


    // Return the number of occurrences of v in the list

    // or return 0 if v is not found.

    // Your code should call findNodeWithValue.

    int count(const T& v) {

        Node<T>* p = findNodeWithValue(v);
        // FILL IN MISSING CODE
        int count  = 0;
        Node<T> * ptr = headPtr;
        while( ptr != nullptr){
            if( v == ptr->value)
                count++;
            ptr = ptr->next;
        }
        return count;
    }

    // Print the list values in reverse order,

    // enclosed in angle brackets, e.g. < 4 3 2 1 >

  
   void printBackwards() const{
    Node<T> *temp = tailPtr;
    while(temp!=nullptr){
     cout << temp->value << " ";
     temp = temp->prev;
    }
   }
   void printForwards() const{
    Node<T> *temp = headPtr;
    while(temp!=nullptr){
     cout << temp->value << " ";
     temp = temp->next;
    }
   }







    // Insert v in the correct position

    // in the list and update length

    // Update headPtr or tailPtr if necessary.

    // Avoid needless looping

    // when v is the new biggest or the new smallest value.


    // Return the list length

    int getLength() const {

        // FILL IN MISSING CODE
        return length;

    }




    // Return true if the list is empty

    bool isEmpty() const {

        // FILL IN MISSING CODE
        return headPtr == nullptr;
    }




    // Set b to the biggest value or do nothing if the list is empty. // 1 2 3 4 5 6 7 8 

    void getBiggest(T & b) const {

        // FILL IN MISSING CODE
        if(isEmpty())
            return;
        Node<T>* ptr = headPtr;
        while(ptr->next != nullptr)
            ptr = ptr->next;
        b = ptr->value;
    }




    // Set s to the smallest value or do nothing if the list is empty.

    void getSmallest(T& s) const {

        // FILL IN MISSING CODE
        if(headPtr == nullptr)
            return;
        s = headPtr->value;
    }




    // Remove the first occurence of v or do nothing if v isn't found.

    // Your code should call findNodeWithValue.

    void removeNode(const T& v) {
        // FILL IN MISSING CODE      / 2 5 7 8      7
         Node<T> *ptr = findNodeWithValue(v);
         if(ptr == nullptr)
          return;
         if(ptr == tailPtr){
          Node<T> *temp = ptr->prev;
          temp->next = nullptr;
          tailPtr = temp;
          delete ptr;
          length--;
          return;
         }

         if(ptr == headPtr){
          Node<T> *temp = ptr->next;
          temp->prev = nullptr;
          headPtr = temp;
          delete ptr;
          length--;
          return;
         }
         cout << " hello ";
         Node<T> *temp = ptr->prev;
         temp->next = ptr->next;
         (ptr->next)->prev = temp;
         delete ptr;
         length--;
         
    }
    void removeFirst(){
     if(headPtr == nullptr)
      return;
     Node<T> *temp = headPtr;
          (temp->next)->prev = nullptr;
          headPtr = headPtr->next;
           delete temp;
          length--;
     
    }
    
    void removeEnd(){
     if(tailPtr == nullptr)
      return;
     Node<T> *temp = tailPtr->prev;
     temp->next = nullptr;
     delete tailPtr;
     tailPtr = temp;
     length--;
    }
    
    void removeAfter(Node<T> *pre){
     Node<T>*temp = pre->next;
     pre->next = temp->next;
     (temp->next)->prev = pre;
     delete temp;
     length--;
    }
    void removeAtIndex(int index){
     if(index < 0 || index >= length)
      return;
     if(index == 0)
      removeFirst();
     if( index == length - 1)
      removeEnd();
     Node<T> *pre = headPtr;
     Node<T> *current = pre->next;   // 1 2  3 4 index =2  value =3
     for(int i = 0 ; i < index - 1;i++){
      pre = pre->next;
      current = current->next;
     }
     pre->next = current->next;
     (current->next)->prev = pre;
     delete current;
      
    }
    
    void insertArray(T array[], int numValues, int location){
     if(location < 0 || location > length || numValues ==0)
      return;
     Node<T>* first = new Node<T>(array[0]), *last = first;
     for(int i=1; i< numValues; i++){
     last->next = new Node<T>(array[i],last);
      last = last->next;
     }
     
     if(location == 0){
      last->next = headPtr;
      headPtr->prev = last;
      headPtr = first;
     }
     else{
      Node<T> * pre = headPtr;
      for(int i = 0; i < location - 1; i++)
       pre = pre->next;
       
      last->next = pre->next;
      (last->next)->prev = last;
      pre->next = first;
      first->prev = pre;
     }
     length += numValues;
    }
    
    void insert(const T& v) {

        // FILL IN MISSING CODE // 11 3 5       11  ////////// 3 4 11    50
        
        if(headPtr == nullptr){
            Node<T> *toInsert = new Node<T>(v, nullptr , nullptr);
            headPtr = toInsert;
            tailPtr = toInsert;
            length++;
            return;
        }
        if(v < headPtr->value){        //   3 v=1; 1 3 
         Node<T> *toInsert = new Node<T>(v, nullptr , headPtr);
         headPtr->prev = toInsert;
         headPtr = toInsert;
         length++;
         return;
        }
        
        if(v > tailPtr->value){     // 1 3 5   v=7
         Node<T> *toInsert = new Node<T>(v, tailPtr , nullptr);
         tailPtr->next = toInsert;
         tailPtr = toInsert;
         length++;
         return;
        }
        // 1  3   5  7 v=4
        Node<T> *toInsert = new Node<T>(v);
        Node<T> *temp = headPtr->next;
        while(temp->value < v){
         temp =temp->next;
        }
        (temp->prev)->next = toInsert;
        toInsert->prev = temp->prev;
        temp->prev = toInsert;
        toInsert->next = temp;
       
        length++;
    }
    
};

template <class T>

void testList(OrderedLinkedList<T> list) {

    cout << endl << "BEGIN TESTLIST xx" << endl;

    cout << "Length = " << list.getLength() << endl;

    cout << "Forwards: " << list << endl;

    cout << "Backwards: ";

    list.printBackwards();

    if (list.isEmpty()) cout << "The list is empty." << endl;

    else {

        T v;

        cout << "getSmallest returns ";

        list.getSmallest(v);

        cout << v << "." << endl;

        cout << "getBiggest returns ";

        list.getBiggest(v);

        cout << v << "." << endl;

    }

    try {

        cout << list[list.getLength()] << endl;

    }

    catch (logic_error e) {

        cout << e.what() << endl;

    }

    try {

        cout << list[-1] << endl;

    }

    catch (logic_error e) {

        cout << e.what() << endl;

    }

    for (int i = 0; i < list.getLength() / 2; i++)

        swap(list[i], list[list.getLength() - i - 1]);

    cout << "After reversing values " << list << endl;

    list.clear();

    cout << "After clear: " << list << endl;

    cout << "END TESTLIST" << endl << endl;

}




int main()

{

    OrderedLinkedList<int> list;

    cout << "Initial list = " << list << endl;
    
    cout << "Initial list length = " << list.getLength() <<   endl;
    list.insert(11);

    list.insert(4);
    list.insert(5);
    list.insert(9);
    // list.printBackwards() ;
    // cout << endl;
    //  OrderedLinkedList<int> list1;
    //  list1 = list;
    //  list1.printBackwards() ;
    //  int a=list[1];
    //  cout <<"\n"<< a << endl;
    //  list.insertFirst(2);
    //  cout << endl;
    //  list.printBackwards();
    //  list.insertAfterHead(3);
    //  cout << endl;
    //  list.printBackwards();
    //  list.insertAtEnd(12);
    //  cout << endl;
    //  list.printBackwards();
    //  list.insert(8);
    //  cout << endl;
    //  list.printBackwards();
    //  cout << "Length = " << list.getLength() << endl;
     
    //   int array[2]={0,1};
    //   list.insertArray(array, 2 ,1);
    //     list.printForwards();
    //   cout << endl;
    //   list.printBackwards();
    // list.removeFirst();
    //  cout << endl;
    //  list.printBackwards();
    //  list.removeEnd();
    //  cout << endl;
    //  list.printBackwards();
    //  list.removeAtIndex(1);
    //  cout << endl;
    //  list.printBackwards();
    //  list.removeNode(9);
    //  cout << endl;
    //  list.printBackwards();
    
    list.insert(5);

    list.insert(7);

    list.insert(6);

    list.insert(4);

    list.insert(2);

    list.insert(8);

    list.insert(5);

    list.insert(1);

    list.insert(0);

    list.insert(12);

    list.insert(10);

    list.insert(5);

    list.insert(13);

    list.insert(0);

    list.insert(8);

    list.insert(4);

    cout << "After insertions, list = " << list << endl;

    testList(list);

    cout << "After testList, list = " << list << endl;

    char response = 'n';

    int v = -1;

    do {

        cout << "Enter a value to remove or -1 to quit: ";

        cin >> v;

        if (v != -1) {

            cout << "old count: " << list.count(v) <<  endl;
            
            list.removeNode(v);

            cout << "new count: " << list.count(v) << endl;
            cout << " ==========================" << endl;

            testList(list);

            cout << list << endl;

        }

    } while (v != -1);

    do {

        cout << "Enter a value to insert or -1 to quit: ";

        cin >> v;

        if (v != -1) {

            cout << "old count: " << list.count(v) << endl;

            list.insert(v);

            cout << "new count: " << list.count(v) << endl;
            

            testList(list);

            cout << list << endl;

        }

    } while (v != -1);

    cout << "Bye" << endl;
    

    return 0;

}







