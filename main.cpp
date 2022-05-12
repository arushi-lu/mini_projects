
#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>

#include "stack.h"


int main( int argc, char* argv [ ] )
{

   stack s1 = { 4, 2, 1 };
   stack s2 = { 8, 7, 4, 3, 0 };

   for( size_t i = 0; i < 1000; ++ i )
   {
      s1. push( i*i ); 
      s2 = s1;
 
   }

   double sum = 0;
   while( s2. size( ))
   {
      stack s3 = s2;
      sum += s3. peek( );
      s2. pop( );
   }
   std::cout << "the sum is " << sum << "\n";
   std::cout << "   should be 3.32834e+08\n"; 
   std::cout << "\n";
// Tests on constructors and functions of stack
   stack st = { 1,2,3,4 };
   
   std::cout << "Stack size before :  "  << st.current_size << "\n";
   std::cout << "Stack capacity before :  "  << st.current_capacity << "\n\n";
 
   st. push(5);
   st.pop();
   st.pop();
   
   std::cout << "I see a " << st.peek() << " on stack"<< "\n"; 
   std::cout << st << "\n";
   std::cout << "Stack size after :  "  << st.current_size << "\n";
   std::cout << "Stack capacity after :  "  << st.current_capacity << "\n\n";



   stack stk1 = {11,22,33,44};
   stack stk2;
   
   stk2.push(99);
   stk2.push(88);
   stk2.push(77);
   
   int val = stk2.peek();
   std::cout<<"I saw : " <<val <<std::endl;
  
   stack stk3(stk2);
   stk2.pop();
 
   std::cout << stk1 << "\n";
   std::cout << stk2 << "\n";
   std::cout << stk3 << "\n";

  return 0; 
}

