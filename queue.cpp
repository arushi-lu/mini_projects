
#include "queue.h"

queue::queue( )
    : queue_size(0),
      front(nullptr),
      back(nullptr) {}

queue::queue( const queue& q )
    : queue_size(q.size()),
      front(nullptr),
      back(nullptr)
{
     std::string val;
     node *temp;
     temp = q.front;
     
     while(temp != nullptr)
     {
        val = temp->value;
        push(val);
        temp = temp->next;
     }
}


const queue& queue::operator = ( const queue& q )
{
    if(this == &q)
      return *this;

    clear();
   
    std::string val;
    node *temp = q.front;
     
    while(temp != nullptr)
    {
       val = temp->value;
       push(val);
       temp = temp->next;
    }
 
    return *this;
}

queue::~queue( )
{
  clear();
}

queue::queue( std::initializer_list< std::string > init )
      :queue()
{
   for(std::string v: init)
        push(v); 
}

void queue::push( const std::string& s )
{
   node *new_back = new node(s);

   if ( back  == nullptr)
   {
       front = back = new_back;
       ++queue_size;
       return;
   }
    
   back->next = new_back; 
   back = new_back;

   ++queue_size;
}

void queue::pop( )
{
   if (front == nullptr) 
       return;
   
   node *remove = front; 
   front = front->next;
   
   if( front == nullptr)
      back = nullptr;
    
   delete remove;

   queue_size--;
}

void queue::clear( )
{
  if (front == nullptr)
     return;
 
  while(front != nullptr)
     pop();

  front = back = nullptr;
  queue_size = 0;
}

void queue::reset( size_t s )
{
   if(s > queue_size )
     return; 

   while(queue_size != s)
      pop();
}

const std::string& queue::peek( ) const
{
   if(front != nullptr)
      return front->value;
   else
      exit(1);
}

size_t queue::size( ) const
{
  return queue_size;
}

bool queue::empty( ) const
{
   return(front == nullptr);
}

void queue::print( std::ostream& out ) const
{
   node*cur;
 
   if(front == nullptr)
   {
     out<< "Empty queue";
     return;
   }

   cur = front;
   
   while(cur!=nullptr)
   {
      out << cur->value;
         if (cur != back)
          out << ", ";

      cur = cur->next;
   }
}

