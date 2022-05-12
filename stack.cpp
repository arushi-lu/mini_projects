
#include "stack.h"

void stack::ensure_capacity( size_t c )
{
   // Keep current_capacity always in powers of two.

   if (c <= current_capacity)
       return;
     
   unsigned int p = 1;
   int exp = 0;

   while (c!=1){
     c = c/2;
     exp++;
   } 
   
   for (int i = 0; i <= exp; i ++)
   {
     p = p * 2;
   }
   
   double* newData = new double[p];

   std::copy(data, data + current_size, newData );

   delete[] data;
 
   data = newData;
   current_capacity = p; 
}

   // Constructs empty stack.
 
stack::stack( ):
       current_size(0),
       current_capacity(4),
       data(new double[4])
{}
  

stack::stack( const stack& s ):
       
       current_size(s.current_size),
       current_capacity(s.current_capacity),
       data(new double[s.current_capacity])
{
   std::copy(s.data, s.data + s.size(), data);      
}


const stack& stack::operator = ( const stack& s )
{
   
    ensure_capacity(s.size());
   
    std::copy(s.data, s.data + s.size(), data);
 
    current_size = s.size();
    return *this;
}
 

stack::~stack( )
{
  delete[] data;
 
}

void stack::push( double d )
{
   if(current_size == current_capacity) 
      ensure_capacity(current_size+1);

   data[current_size] = d;
   ++current_size;
} 
 
stack::stack( std::initializer_list< double > init ):
            stack()
{
   for(double d : init)
   {
      push(d);
   } 

}  
void stack::pop( )
{
   if(current_size == 0)
      throw std::runtime_error( "pop: stack is empty" );

   current_size--;
}

void stack::clear( )
{
  current_size = 0;
}
 

void stack::reset( size_t s )
{
   if(s <=current_size)
     current_size = s;
}

double stack::peek( ) const
{
   if(current_size == 0)
     throw std::runtime_error( "pop: stack is empty" );
 
 return data[current_size-1];
}

size_t stack::size( ) const
{ 
  return current_size; 
}

bool stack::empty( ) const
{
  return (current_size == 0);
}

void stack::print( std::ostream& out ) const{

 out << "stack: ";
      
 for (size_t i = 0; i < current_size; i++)
 {
   if(i>0)
      out << ", ";
         
   out << data[i];
 }
}
