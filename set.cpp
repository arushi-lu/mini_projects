
#include "set.h"

const treenode* find( const treenode* n, const std::string& s )
{ 
    while ( n != nullptr )
    { 
      if (s < n->value)
        n = n->left;
     
      else if (s > n->value)
        n = n->right;
     
      else 
        return n;
    }

    return nullptr;
}

treenode** find( treenode** n, const std::string& s )
{
   treenode **search = n;
 
   while( *search != nullptr )
   {
     if (s < (*search)->value)
        search =&((*search) -> left);
    
     else if (s > (*search) -> value)
        search = &((*search) -> right);
    
     else if (s == (*search) ->value)
        return n;
   }
 
  return search;
}

size_t size( const treenode* n )
{
  if (n == nullptr)
    return 0;
  else
    return(size(n->left) + 1 + size(n->right));
    
}

size_t height( const treenode* n )
{ 
  if (n == nullptr) 
     return 0;
  
  if(height(n->left) > height(n->right))
     return 1 + height(n->left);
  
  else
     return 1 + height(n->right);
  
}

void deallocate( treenode* n )
{ 
  if(n == nullptr) 
     return;
 
  deallocate(n -> left);
  deallocate(n -> right);
 
  delete n;
}

treenode* makecopy( const treenode* n ) 
{
  if(n == nullptr)
     return nullptr;
 
  treenode *copy = new treenode(n->value);
 
  copy->value = n->value; 
  
  copy->left = makecopy(n->left);
  copy->right = makecopy(n->right);
 
  return copy;
}


void print( std::ostream& out, const treenode* n, unsigned int indent )
{
   for( unsigned int i = 0; i != indent; ++ i )
      out << "|  "; 
   if(n)
   {
      out << ( n -> value ) << "\n";
      print( out, n -> left, indent + 1 );
      print( out, n -> right, indent + 1 ); 
   }
   else
      out << "#\n"; 
}


// Both the upperbound and the lowerbound are strict,
// we use pointers, so that they can be absent. 

void checkbetween( const treenode* n, 
                   const std::string* lowerbound, 
                   const std::string* upperbound ) 
{
   while(n) 
   {
      if( lowerbound && *lowerbound >= n -> value )
      {
         std::cout << "value " << ( n -> value );
         std::cout << " is not above lower bound " << *lowerbound << "\n";
         throw std::runtime_error( "tree not correct" ); 
      }

      if( upperbound && n -> value >= *upperbound )
      {
         std::cout << "value " << ( n -> value );
         std::cout << "is not below upperbound " << *upperbound << "\n";
         throw std::runtime_error( "tree not correct" );  
      }

      checkbetween( n -> left, lowerbound, &( n -> value ));
      lowerbound = & ( n -> value );
      n = n -> right;
   }
} 


unsigned int log_base2( size_t s )
{ 
  if (s > 1)
    return 1 + log_base2(s/2);
  else
    return 0;
}

bool set::contains( const std::string& s ) const
{ 
  return ::find(tr, s);
}

 
bool set::insert( const std::string& s )
{ 

   treenode** f = ::find(&tr, s);
 
   if(*f != nullptr)
   {
      return false;
   }
   else
   {
     treenode *newNode = new treenode(s);
     *f = newNode;
     return true;
   }
}

size_t set::size( ) const
{ 
   return ::size(tr);
}

size_t set::height( ) const
{
   return ::height(tr); 
}

bool set::empty( ) const
{
   if (tr == nullptr) 
     return true;
   else
     return false;
}

set:: ~set( )
{ 
  ::deallocate(tr);
  tr = nullptr;
}

void set::clear( )
{
 ::size(nullptr); 
 ::deallocate(tr);
 tr = nullptr;
}

set::set( const set& other ): tr(::makecopy(other.tr))
{ }


set& set::operator = ( const set& other )
{ 
  
  if (&other == this)
     return *this;
  
  ::deallocate(tr);
  tr = ::makecopy(other.tr);
   
 
  return *this;
}



void set::checksorted( ) const
{
   ::checkbetween( tr, nullptr, nullptr );
}


void set::print( std::ostream& out, unsigned int indent ) const
{
   ::print( out, tr, indent );
}

