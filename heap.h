/******************************************************
  Heap.h -- Declarations for Basic Heap-of-Pair-of-Ints Class

  Stores pairs <element,priority> of ints.
  Supports O(log n) insertion, O(1) peeking at min priority and element 
  with min priority, and O(log n) extraction of element with min priority.
*******************************************************/
using namespace std;

class Heap{

public:
   // Constructors and Destructor

   // New empty Heap with default capacity.
   Heap();  

   // New empty Heap with capacity c.
   Heap(int c); 

   // New Heap with size s, consisting of pairs <Pi,Ei> where, 
   // for 0 <= i < s, Pi is Priorities[i] and Ei is value Elements[i].  
   // Capacity is s + c, where c is the "spare capacity" argument.
   // Requires: Priorities and Elements are of size at least s. 
   Heap( const int * Priorities, const int * Elements, int s, int c); 

   // New Heap with combined contents the two Heap arguments. 
   // Size of the new Heap is the sum of the sizes of argument Heaps.
   // Capacity of the new Heap is its size plus the "spare capacity" c.
   Heap( const Heap & Heap1, const Heap & Heap2, int c ); 

   // Destructor.
   ~Heap(); 

   

   // Accessors
   bool empty() const {return hSize == 0;}; // True iff Heap is empty.
   int size() const { return hSize ;} ; // Current size of Heap.
   int capacity() const { return hCapacity ;} ; // Current capacity.
   int peekMin() const { return A[0].element ;} // Peek at minimum element.
   int peekMinPriority() const { return A[0].priority ;} // Peek at priority of min element.
   int e(int i) const { return A[i].element;} //grabs the element
   int p(int i) const { return A[i].priority;} //grabs the priority

    // Modifiers
   void insert( int element, int priority ); // Insert the pair <element,priority>.
   int extractMin(); // Remove and return the highest priority element.
private:
   class Pair{
      public:
        int element ;
        int priority ;
   };

   Pair* A ; // Array containing heap contents.
   int hCapacity ; // Max number of elements (= size of A).
   int hSize ; // Current number of elements.

   // Repairs ordering invariant after adding leaf at A[i].
   void trickleUp(int i);

   // Repairs ordering invariant for sub-tree rooted at index i,
   //   when A[i] may be smaller than one of its children.
   void trickleDown(int i);

   // Establishes ordering invariant for entire array contents.
   void heapify(); //(Same as "make_heap" in lectures.)

   // Useful for implementing trickle up and down
   void swap(int i,int j);

    int parent(int i);

    int left(int i);;

    int right (int i);

};
//default constructor
Heap::Heap(){
   hCapacity = 16 ;
   A = new Pair[hCapacity];
   hSize = 0 ; 
}

Heap::Heap(int c){ // New empty Heap with capacity c.
    hCapacity = c ;
    A = new Pair[hCapacity];
    hSize = 0 ;
}

// New Heap with capacity c+s, with s elements, consisting of pairs <Pi,Vi> where 
//  Pi is Priorities[i], Ei is value Elements[i], for 0 <= i < s.
Heap::Heap( const int * Priorities, const int * Elements, int s, int c){ 
    hCapacity = c+s ;
    A = new Pair[hCapacity];
    hSize = 0 ;
    for(int i = 0; i<s; i++){
        insert(Elements[i],Priorities[i]);
    }
}

// New Heap with combined contents the two Heap arguments.
// Size of the new Heap is the sum of the sizes of argument Heaps.
// Capacity of the new Heap is its size plus the "spare capacity" c.
Heap::Heap( const Heap & Heap1, const Heap & Heap2, int c ){
   hCapacity = (Heap1.hSize + Heap2.hSize) + c ;
    A = new Pair[hCapacity];
    hSize = 0;
    for(int i =0; i<Heap1.hSize; i++){
        insert(Heap1.e(i),Heap1.p(i));
    }
    for(int k =0; k<Heap2.hSize; k++){
        insert(Heap2.e(k),Heap2.p(k));
    }
}

// Destructor
Heap::~Heap(){
   delete[] A;
}
// Modifiers

//swaps two elements
void Heap::swap(int i, int j){
    Pair temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

void Heap::insert(int element, int priority){
   A[hSize].element = element;
   A[hSize].priority = priority;
   trickleUp(hSize);
   hSize ++;
}

// Repairs the heap ordering invariant after adding a new element.
// Initial call should be trickleUp(hSize-1).
void Heap::trickleUp(int i){
        if (A[parent(i)].priority > A[i].priority) {
            swap(i,parent(i));
            trickleUp(parent(i));
    } else {
        return;
    }
}
// Removes and returns the element with highest priority.
// (That is, the element associated with the minimum priority value.)
int Heap::extractMin(){
    int i;
    Pair tmp = A[0];
    A[0]=A[hSize-1];
    hSize--;
    trickleDown(0);
    return tmp.element;
}

// Repairs the heap ordering invariant after replacing the root.
// Initial call by insert() is trickleDown(0).
// (trickleDown(i) performs the repair on the subtree rooted a A[i].)
// (heapify() calls trickleDown(i) for i from (hSize/2)-1 down to 0.)

//starts at current node
void Heap::trickleDown(int i){
    int tmp = left(i);
    if (left(i) < hSize){
        if (right(i) < hSize && A[right(i)].priority < A[left(i)].priority){
            tmp=right(i);
        }
        if (A[i].priority > A[tmp].priority){
            swap(i,tmp);
            trickleDown(tmp);
        }
    }
    }

// Turns A[0] .. A[size-1] into a heap.
void Heap::heapify(){
   for( int i = (hSize/2)-1; i>=0 ; i-- ) trickleDown(i);
}

int Heap::parent(int i){
    return (i-1)/2;
}

int Heap::left(int i){
    return (2*i)+1;
}

int Heap::right (int i){
    return (2*i)+2;
}
