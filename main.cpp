//COMSC 210 | Midterm 1| Toma Dimov

#include <iostream>     //importing iostream library and using the std namespace for ease of use.
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;    //cont integers

class DoublyLinkedList {    //A Class called Doubly LinkedList is being defined.
private:
    struct Node {   //a node struct is defined within the class. each DoublyLinkedList class will have access to these, and using multiple instances of Node, it will construct a doubly linked list.
        int data;       //the data member, an int
        Node* prev;     //a Node Pointer type member. This one will point to the previous Node in our list
        Node* next;     //a Node Pointer type member. This one will point to the next Node in our list
        Node(int val, Node* p = nullptr, Node* n = nullptr) {       //Node Parameter Constructor. Node* p & Node* n arguments default to nullpointer unless overwritten when called.
            data = val;     //assigns the arguments to our class members, ala setters.
            prev = p;
            next = n;
        }
    };

    Node* head;         //the head of the DoublyLinkedList
    Node* tail;         //The Tail of the DoublyLinkedList

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }      //DoublyLinkedList default Constructor. It assigns head and tail to nullpointer.

    void insert_after(int value, int position) {            // a method which inserts a Node containing the passed value into the passed position on the doubly linked list.
        if (position < 0) {                                 // user error check, doesn't make sense to have a position that is 0 or less.
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);                    //a new node is instantiated with the Value passed as its data. We remember from earlier that its prev and next pointers are set to nullptr.
        if (!head) {                                        //if our doubly linked list has no head, it is empty:
            head = tail = newNode;                          //our new Node will be inserted as both the head and the tail.
            return;                                         // we're done, lets get out of here.
        }

        Node* temp = head;                                  //otherwise, there is head. We will set our temporary pointer to the head...
        for (int i = 0; i < position && temp; ++i)          //and begin moving our temp node along the linked list until we reach our target position.
            temp = temp->next;

        if (!temp) {                                        //we've reached the end of the linked list because temp is pointing to a nullptr:
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;                                 //delete our dynamically allocated Node,
            return;                                         //lets get out of here. The Node was not inserted.
        }
//                                                          //otherwise, we have a valid target at the proper position.
        newNode->next = temp->next;                         //Our newNode's next pointer is set to match our target position's next node. This is because we will later replace target->next with a pointer to ourselves.
        newNode->prev = temp;                               //newNode's prev pointer is equal to our target. We are placing ourselves in the list after the target.
        if (temp->next)                                     //Checks to see if we are not at the end of the list yet. If its the end of list: temp->next = nullptr, thus false, we skip to else statement.
            temp->next->prev = newNode;                     //the Node after target has its prev pointer set to ourself.
        else                                                //We are at the end of the list.
            tail = newNode;                                 //set tail to point to us.
        temp->next = newNode;                               //and finally, set the target's next pointer to point to us.
    }

    void delete_val(int value) {                            //delete a node containing a passed value.
        if (!head) return;                                  //check if our list is empty. if it is, we leave.

        Node* temp = head;                                  //set a temporary pointer to head
        
        while (temp && temp->data != value)                 //iterate through the whole list, each iteration checking if temp is pointing to a valid node AND if temp data is not equal to our target value.
            temp = temp->next;                               
//                                                          //the iteration ends here meaning 1 of 2 things happened: We reached the end or we found the target and temp is currently pointing to it
        if (!temp) return;                                  //Target was not found because we are pointing to null. lets get out of here.

        if (temp->prev)                                     //if we are not the first value
            temp->prev->next = temp->next;                  //set the node previous to our target to point its next pointer to the value after our target.
        else                                                //we are the first value
            head = temp->next;                              //head is set to the node after our target. our target will soon be deleted

        if (temp->next)                                     //if we are not the last value
            temp->next->prev = temp->prev;                  //set the node after us to point its prev pointer to the value before our target.
        else                                                //we are the last value in the list 
            tail = temp->prev;                              //the tail is set to the node before our target. our target will soon be deleted

        delete temp;                                        //our target is deleted
    }

    void delete_pos(int pos) {                              //a position on the list is passed and that node is to be deleted
        if (!head) {                                        //are we an empty list?
            cout << "List is empty." << endl;
            return;                                         //yes, lets get out of here.
        }
    
        if (pos == 1) {                                     //is our target the first position?
            pop_front();                                    //call our pop_front() method
            return;                                         //then get out of here
        }
    
        Node* temp = head;                                  //set our temp node to point to the head.
    
        for (int i = 1; i < pos; i++){                      //iterate through the list until we reach our position, then exit
            if (!temp) {                                    //we've hit out of bounds.
                cout << "Position doesn't exist." << endl;
                return;                                     //lets get out of here. Node not deleted.
            }
            else                                            //we have not yet hit out of bounds
                temp = temp->next;                          //continue iterating for as long as the for statement is valid.
        }
        if (!temp) {                                        //is our target position out of bounds?
            cout << "Position doesn't exist." << endl;      //yes it is, lets get out of here. Node not deleted.
            return;
        }
    
        if (!temp->next) {                                  //are we at the end?
            pop_back();                                     //call our pop_back() method
            return;                                         //and lets get out of here, job's done.
        }
    
        Node* tempPrev = temp->prev;                        //a temporary node that points to the target's prev node
        tempPrev->next = temp->next;                        //tempPrev's node's next is set to match target's next
        temp->next->prev = tempPrev;                        //the node after target's prev pointer is set to point to our tempPrev node.
        delete temp;                                        //delete our target from the linked list
    }

    void push_back(int v) {                                 //pass an integer as a data value. program will place it at the back of the list
        Node* newNode = new Node(v);                        //newNode pointer, dynamically allocated with V passed as data parameter in constructor.
        if (!tail)                                          //there is no tail, empty list
            head = tail = newNode;                          // this node becomes the first and last value of the linked list
        else {                                              
            tail->next = newNode;                           //last node's next points to our newNode
            newNode->prev = tail;                           //newNode's prev will point to our tail
            tail = newNode;                                 //newNode becomes the tail henceforth.
        }
    }
    
    void push_front(int v) {                                //pass an integer data value. program will place it at the start of the list
        Node* newNode = new Node(v);                        //newNode pointer, dynamically allocated with V passed as data parameter in constructor.
        if (!head)                                          //there is no head. empty list
            head = tail = newNode;                          //our newNode is the beginning and end.
        else {
            newNode->next = head;                           //newNode's next points to the current head node
            head->prev = newNode;                           //head's prev node points to newNode
            head = newNode;                                 //newNode is the head now
        }
    }
    
    void pop_front() {                                      //deletes the first node in the linked list

        if (!head) {                                        //empty list?
            cout << "List is empty." << endl;
            return;                                         //nothing happens and we leave
        }

        Node * temp = head;                                 //temp pointer to head

        if (head->next) {                                   //if there is a node after the head...
            head = head->next;                              //the head is now set to the node immediately after itself
            head->prev = nullptr;                           //that new head pointer has its prev value nulled
        }
        else                                                //there is no node after the head...
            head = tail = nullptr;                          //the head and tail are nulled, the list will be empty now
        delete temp;                                        //delete the target.
    }

    void pop_back() {                                       //delete's the last value in a linked list
        if (!tail) {                                        //if there is no tail
            cout << "List is empty." << endl;
            return;                                         //list empty, we cout an error and leave the function
        }
        Node * temp = tail;                                 //set our temp node pointer to the end of the list

        if (tail->prev) {                                   //is there a node right before us?
            tail = tail->prev;                              //yes: tail is set to that node.
            tail->next = nullptr;                           //new tail's next node is nulled
        }
        else                                                //nothing before us.
            head = tail = nullptr;                          //head and tail nulled
        delete temp;                                        //target deleted
    }

    ~DoublyLinkedList() {                                   //destructor
        while (head) {                                      //while the head exists
            Node* temp = head;                              //make a temp pointer to head
            head = head->next;                              // set head to next node
            delete temp;                                    //delete the node that temp is pointing to 
        }
    }
    void print() {
        Node* current = head;                               //node set to head
        if (!current) {                                     //empty list?
            cout << "List is empty." << endl;               // error message, return out of the function
            return;
        }
        while (current) {                                   //iterate through as long as our current pointer isn't pointing to nullptr
            cout << current->data << " ";                   //output the data and add a " "
            current = current->next;                        //move the current pointer down the list
        }
        cout << endl;
    }

    void print_reverse() {                                  //as above but reverse
        Node* current = tail;                               //set our current pointer to tail
        if (!current) {                                     //empty list?
            cout << "List is empty." << endl;
            return;                                         //complain then exit out of the function
        }
        while (current) {                                   //iterate through as long as our current pointer isn't pointing to nullptr
            cout << current->data << " ";                   // output data
            current = current->prev;                        //move the current pointer up the list
        }
        cout << endl;
    }
};

int main() {
    cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS;  // dummy statement to avoid compiler warning

    
    return 0;
}