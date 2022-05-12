
#include <random>
#include <algorithm>

#include "set.h"
#include "timetable.h"
#include "timer.h"


std::vector< std::string > randomvector( size_t k ) 
{
   std::vector< std::string > res; 
   for( size_t i = 0; i != k; ++ i )
   {
      std::ostringstream out;
      out << "string_" << std::abs( rand( )); 
      res. push_back( out. str( ));
   } 
   return res;
}

int main( int argc, char* argv[ ] )
{
/* 
   std::cout << log_base2(1) << "\n"; // must print 0.
   std::cout << log_base2(2) << "\n"; // must print 1.
   std::cout << log_base2(15) << "\n"; // must print 3.
   std::cout << log_base2(16) << "\n"; // must print 4.
   std::cout << log_base2(0) << "\n"; // must print 0.
*/   
   set small;    // A small test tree.

   std::cout << small. height( ) << "\n";
   small. insert( "if" ); 
   std::cout << small. height( ) << "\n"; 
   small. insert( "the" ); 
   std::cout << small. height( ) << "\n";
   small. insert( "value" );
   small. insert( "value" );
   small. insert( "value" );
   std::cout << small << "\n";
   std::cout << small. height( ) << "\n";
   small. clear( );
   std::cout << "this is the tree: " << small << "\n";
   set small3 = small; 
   std::cout << small3 << "\n";

   std::cout << small. contains( "xx" ) << "\n";
   std::cout << small. contains( "yy" ) << "\n";
      // Or not to be, that's the question. 

#if 1
   // Some more tests:

   small. insert( "oskemen" );
   std::cout << small. contains( "kostanay" ) << "\n";

   small. insert( "atyrau" );
   small. insert( "nursultan" );
   small. insert( "almaty" );
   small. insert( "shymkent" ); 
   small. insert( "pavlodar" );

   small. checksorted( );
   std::cout << small << "\n"; 
   std::cout << small. size( ) << "\n";
   std::cout << "Height is " << small. height( );
   std::cout << " should be approximately " << 
     log_base2( small. size( )) << "\n";
      // If the numbers differ much, the tree is badly balanced. 

   auto small2 = small; // Copy constructor. 
   std::cout << small2 << "\n";
   std::cout << "size = " << small2. size( ) << "\n";
   std::cout << "height = " << small2. height( ) << "\n";
   small2 = small;      // Assignment.
   small = small;       // Self assignment.

#endif 

   timetable tab( std::string( "set" ));

   for( size_t s = 1000; s < 4096 * 1000; s = 2 * s ) //before s < 4096 * 1000
   {
      // Create random test set of size s:

      std::vector< std::string > randvect = randomvector(s);

#if 0
      std::cout << "test vector: ";
      for( const auto& s : randvect )
         std::cout << s << " ";
      std::cout << "\n";
#endif

//    std::sort( randvect. begin( ), randvect. end( ));

      set someset1;

      timer tt; 
      size_t nr_insertions = 0;
      for( const auto& s : randvect ) 
      {
         nr_insertions += someset1. insert( s );
         nr_insertions += someset1. insert( std::string( "X" ) + s );
      }

      auto someset2 = someset1;

      if( nr_insertions != someset2. size( )) 
      {
         std::cout << "nr = " << nr_insertions << "\n";
         std::cout << "size( ) = " << someset2. size( ) << "\n"; 
         throw std::runtime_error( 
                       "something went wrong with counting insertions" );
      }

      // Don't use size( )! It is O(n), and will mess up your performance. 

      tab. insert( s, tt. time( )); 
      std::cout << "finished test for " << s << "\n";
   } 

   std::cout << tab << "\n"; 
   std::cout << "totaltime " << tab. totaltime( ) << "\n";

}

/*
The first part of task 2, where s < 4096 * 1000
 
finished test for 1000
finished test for 2000
finished test for 4000
finished test for 8000
finished test for 16000
finished test for 32000
finished test for 64000
finished test for 128000
finished test for 256000
finished test for 512000
finished test for 1024000
finished test for 2048000

Performance table of set (inputsize/runtime in seconds):
     1000/8.1105e-04     2000/1.6481e-03     4000/3.5789e-03     8000/8.5617e-03     16000/1.3509e-02     32000/3.0605e-02     64000/7.0285e-02     128000/1.6597e-01     256000/3.7486e-01     512000/8.8543e-01     1024000/1.9911e+00     2048000/4.6109e+00

totaltime 8.1573e+00

The last part of task 2, where  s < 100000: unbalanced tree

finished test for 64000
Performance table of set (inputsize/runtime in seconds):
     1000/7.4703e-03     2000/2.6641e-02     4000/9.6115e-02     8000/2.8580e-01     16000/1.1025e+00     32000/4.5497e+00     64000/3.3914e+01

totaltime 3.9982e+01

*/

