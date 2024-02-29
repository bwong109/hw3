#ifndef HEAP_H
#define HEAP_H
#include <functional>
#include <stdexcept>
#include <vector>

template <typename T, typename PComparator = std::less<T> >
class Heap
{
public:
  /**
   * @brief Construct a new Heap object
   * 
   * @param m ary-ness of heap tree (default to 2)
   * @param c binary predicate function/functor that takes two items
   *          as an argument and returns a bool if the first argument has
   *          priority over the second.
   */
  Heap(int m=2, PComparator c = PComparator());

  /**
  * @brief Destroy the Heap object
  * 
  */
  ~Heap();

  /**
   * @brief Push an item to the heap
   * 
   * @param item item to heap
   */
  void push(const T& item);

  /**
   * @brief Returns the top (priority) item
   * 
   * @return T const& top priority item
   * @throw std::underflow_error if the heap is empty
   */
  T const & top() const;

  /**
   * @brief Remove the top priority item
   * 
   * @throw std::underflow_error if the heap is empty
   */
  void pop();

  /// returns true if the heap is empty

  /**
   * @brief Returns true if the heap is empty
   * 
   */
  bool empty() const;

    /**
   * @brief Returns size of the heap
   * 
   */
  size_t size() const;

private:
  /// Add whatever helper functions and data members you need below
  std::vector<T> data;
  size_t m_ary;
  PComparator comp;

};

// Add implementation of member functions here

template <typename T, typename PComparator>
Heap<T, PComparator>::Heap(int m, PComparator c) : m_ary(m), comp(c){}

template <typename T, typename PComparator>
Heap<T, PComparator>::~Heap(){}

template <typename T, typename PComparator>
bool Heap<T, PComparator>::empty() const{
  return data.empty();
}

template <typename T, typename PComparator>
size_t Heap<T, PComparator>::size() const{
  return data.size();
}

template <typename T, typename PComparator>
void Heap<T, PComparator>::push(const T& item){
  
  // Add new item to end of vector, and index it
  data.push_back(item);
  size_t index = data.size() - 1;

  // Bubble up while not root and does not violate heap property
  while (index > 0 && comp(data[index], data[(index - 1) / m_ary])) {

    // Calculate parent node and swap current item with parent
    size_t parentIndex = (index - 1) / m_ary;
    std::swap(data[index], data[parentIndex]);

    // Update index to continue bubbling
    index = parentIndex;
  }

}

// We will start top() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
T const & Heap<T,PComparator>::top() const
{
  // Here we use exceptions to handle the case of trying
  // to access the top element of an empty heap
  if(empty()){
    throw std::underflow_error("No top, is empty");
  }

  // If we get here we know the heap has at least 1 item
  // Add code to return the top element

  return data[0];

}


// We will start pop() for you to handle the case of 
// calling top on an empty heap
template <typename T, typename PComparator>
void Heap<T,PComparator>::pop()
{
  // Use exceptions to handle case of empty heap
  if(empty()){
    throw std::underflow_error("Cannot pop, is empty");
  }

  // Replace root of heap with last element
  data[0] = data.back();
  data.pop_back();

  // Intialize parent and priority indices
  size_t parent = 0;
  size_t priority = 0;

  // Continue until heap property is satisfied or loop broken
  while (true){
    
    // Calculate index of parent's first child
    size_t index = (parent * m_ary) + 1;
    priority = index;

    // Find child with highest priority, check if it is within bounds, then update
    for (size_t child = 1; child < m_ary; child++){
      size_t childIndex = index + child;
      if (childIndex < data.size() && !comp(data[priority], data[index + child])){{
          priority = index + child;
        }
      }
    }

    // If neccessary, swap parent with highest priority
    if (priority < data.size() && !comp(data[parent], data[priority])){
      std::swap(data[parent], data[priority]);
      parent = priority; 
    }
    else{
      break;
    }

  }

}

#endif

