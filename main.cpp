
#include <random>
#include <algorithm>
#include <sstream>

#include "set.h"


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
   set small;    // A small test tree.

   small. insert( "if" );
   small. insert( "the" );
   small. insert( "value" );
   std::cout << "Contains 1: "  << small. contains( "value" ) << "\n"; 
   std::cout << "Contains 0: "  << small. contains( "xx" ) << "\n\n";
   small. insert( "VaLuE" );
   std::cout << small << "\n";
   std::cout << "Empty0: "  << small. empty() << std::endl;

   small. clear( );
   std::cout << "Empty1: "  << small. empty() << "\n\n";
   std::cout << "this is the hash set: \n" << small << "\n";
   set small3 = small;
   std::cout << "set small 3: \n" << small3 << "\n";

   std::cout << small. contains( "xx" ) << "\n";
   std::cout << small. contains( "yy" ) << "\n";
      // Or not to be, that's the question.

#if 1 
   // Some more tests:

   small. insert( "oskemen" );
   std::cout << small. contains( "kostanay" ) << "\n";
   std::cout << small << "\n";

   small. insert( "atyrau" );
   small. insert( "nursultan" );
   small. insert( "almaty" );
   small. insert( "shymkent" );
   small. insert( "pavlodar" );

   std::cout << "Contains1: "<< small. contains("ShyMkent")<<std::endl;
   std::cout << "Contains0: "<< small. contains("ShyMkeeent")<<std::endl;
   std::cout << "Contains0: "<< small. contains("nurSULtanTan")<<std::endl;
   
   

   std::cout << small << "\n";
   std::cout << "Set size: " << small. size( ) << "\n";

   auto small2 = small; // Copy constructor.

   small2 .remove("almaty");

   std::cout << small2 << "\n";
   std::cout << "size = " << small2. size( ) << "\n";

   small2 = small;      // Assignment.
   small = small;       // Self assignment.
 
   set test = {"uno", "dos", "tako"};
 
   std::cout << test << std::endl;

   std::cout << "size =  " << test. size() << std::endl;
   test .remove("dos");
   test .remove("dot");
   std::cout << test << std::endl;
   std::cout << "size =  " << test. size() << std::endl;

   bool b = case_insensitive::equal( "aBc", "abc" );
   std::cout << b << std::endl;

   size_t h = case_insensitive::hash( "aaa" );
   std::cout << h << std::endl;

   size_t index = h % 8;
   std::cout << index << std::endl;

   test .insert("aaa");
   std::cout << test << std::endl;

   std::cout << "Contains1: "<< test. contains("UNO")<<std::endl;
   std::cout << "Contains0: "<< test. contains("UN O")<<std::endl;   
   std::cout << "Contains0: "<< test. contains("UN\nNO")<<std::endl;



#endif

   for( size_t s = 1000; s < 4096 * 1000 ; s = 2 * s ) // 4096*1000
   {
      std::cout << "----------------------------------------\n";

      // Create random test set of size s:

      std::vector< std::string > randvect = randomvector(s);

#if 0 
      std::cout << "test vector: ";
      for( const auto& s : randvect )
         std::cout << s << " ";
      std::cout << "\n";
#endif

      std::sort( randvect. begin( ), randvect. end( ));

      set someset1(25);

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

      std::cout << "number of insertions " << someset2. size( ) << "\n";

      std::cout << "finished test for " << s << "\n";
      someset2. printstatistics( std::cout );
   }

}
