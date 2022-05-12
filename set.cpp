
#include "set.h"

size_t case_insensitive::hash( const std::string& s )
{

   char a;
   std::string cp = s;
 
   for (size_t i = 0; i < cp.size(); i++)
   {
      a = tolower(cp[i]);
      cp[i] = a;  
   }
    
   size_t hashInd = 0;
   size_t n = s.size();
   size_t tempPow = 1;
 
   for (size_t i = 0; i < n ; i++)
   {
      hashInd += cp[n-i-1] * tempPow;
      tempPow *= 33;
   }
  
  return hashInd;
}

bool case_insensitive::equal( const std::string& s1, const std::string& s2 )
{
   std::string cp1 = s1;
   std::string cp2 = s2;
   char a;  

   for(size_t i = 0; i < cp1.size(); i++)
   {
      a = tolower(cp1[i]);
      cp1[i] = a;
   }
  
   for(size_t i = 0; i < cp2.size(); i++)
   {
      a = tolower(cp2[i]);
      cp2[i] = a;
   }
  
   if( cp1 == cp2 )
      return true;
   else
      return false;
}

bool set::insert_norehash( const std::string& s )
{ 
  size_t index = (case_insensitive::hash(s)) % buckets.size();
  
  for( auto it = buckets[index]. begin( ); it != buckets[index]. end( ); ++ it )
  {
    if (case_insensitive::equal(*it, s) ){
      return false;
    }
  }    
   
  buckets[index].push_back(s);
  return true;
}

void set::consider_rehash( )
{

  if( static_cast<size_t>(loadfactor()) > max_load_factor )
  {
  
    size_t newSize = 8; 
 
    while ( (set_size / newSize) > max_load_factor)
    {    
       newSize *= 2; 
    } 
   
    std::vector<buckettype> newTable(newSize);
 
    for (const buckettype& bucket: buckets)
    {
       for (const std::string& s: bucket)
       {  
          size_t index = (case_insensitive::hash(s)) % newSize;
          newTable[ index ].push_back(s);
       }
    }

   buckets = newTable;
  } 
} 

set::set( std::initializer_list< std::string > init,
          double max_load_factor )
   : max_load_factor( max_load_factor ),
     buckets( std::vector< buckettype > (8)),
     set_size(0)
{
   for ( auto i: init )
      insert(i);
}

bool set::contains( const std::string& s ) const
{ 
   size_t index = case_insensitive::hash(s) % buckets.size();
   bool contain = false;
 
   for ( auto it = buckets[index].begin(); it != buckets[index].end(); ++it)
   {
     if ( case_insensitive::equal(*it, s))
       contain = true;
   }
  
   return contain;
}

bool set::insert( const std::string& s )
{

  bool inserted = insert_norehash(s);

  if ( inserted )
  {
     consider_rehash();
     set_size++;
  }
   
  return inserted;
}

bool set::remove( const std::string& s ) 
{ 
   size_t index = case_insensitive::hash(s) % buckets.size();
   auto& lst = buckets[index];

   for ( auto it = lst.begin(); it != lst.end(); ++it)
   {
     if (case_insensitive::equal( *it, s ) == true)
     {
       lst.erase(it);
       set_size--;
       return true;
     }
   }

   return false;
}

size_t set::size( ) const
{ 
  return set_size; 
}

bool set::empty( ) const
{ 
  return (set_size == 0);
}

void set::clear( ) 
{
   for ( size_t i = 0; i < buckets.size(); i++)
   {
     auto &lst = buckets[i];
     lst.clear();
   }
   set_size = 0;
}

void set::print( std::ostream& out ) const
{ 
   for (size_t i = 0; i < buckets.size(); i++)
   {
     std::list<std::string> bucket = buckets[i];

     out << "bucket[" << i << "] = {";
 
         bool first = true;
 
         for ( std::string val : bucket) 
         {
            if(first)
            {
              out << val;
              first = false;
            } else {
              out << ", " << val;
            }
         }
      out << "}" << std::endl;  
   } 
}


