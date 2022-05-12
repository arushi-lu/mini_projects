
#include "state.h"
#include <string>

state::state( std::initializer_list< unsigned int > init )
{
 sticks = init;  
}

state::state( unsigned int i1, unsigned int i2 )
{
   int rows = i2 ;
   for(int  i = 0 ; i < rows;  i ++) 
   {
     sticks.push_back(i+i1);
   }
}

unsigned int state::sum( ) const
{ 
 int stickNum = 0;
 for (int i = 0; i < sticks.size(); i++)
 {
   stickNum = stickNum + sticks[i];
 }
 
 return stickNum;
}

optional_move state::randommove( ) const 
{
  if(sum () == 0 )
  {
    return optional_move();
  } 
    
   int randomRow = rand() % sticks.size() ;
  
    while (sticks[randomRow] == 0 )
    { 
       randomRow = rand() % sticks.size();
    }
  
    int remainSticks = rand() % sticks[randomRow];
    
  return move(randomRow, remainSticks) ;
}  


void state::make( move m )
{
 if (m.row <= sticks.size() || m.remaining < m.row )
    sticks[m.row] = m.remaining;
 else
  std::abort();
}

void state::print( std::ostream& out ) const
{
 int k = 0;
  for (int i = 0; i < sticks.size() ; i++, k++)
  {
    out << i + 1 << "  :   " ;
    for (int j = 0; j < sticks[k]; j++ )
    {
     out << "1 ";
    }
    out << "\n";
  } 
}


optional_move state::usermove( std::ostream& out, std::istream& in ) const
{

   if( sum( ))
   {
      while( true )
      {
         std::string inp;
         try
         {
            out << "row? "; out. flush( );
            in >> inp; 

            unsigned int row = std::stoul( inp ); inp. clear( );

            if( row > 0 && row <= sticks. size( )) 
            {
               unsigned int row1 = row - 1;  // This is a type conversion! 
               if( sticks[ row1 ] )
               {
                  out << "how many remaining? "; out. flush( );
                  in >> inp; 
                  unsigned int remain = std::stoul( inp ); inp. clear( ); 

                  if( remain < sticks[ row1 ] )
                     return move( row1, remain );
                  else
                  {
                     out << "having " << remain 
                         << " remaining is not possible, "
                         << "you have to remove at least one stick\n";
                  }
               }
               else 
               {
                  out << "row " << row << " is already empty\n";
               }
            }
            else
            {
               out << "row " << row << " is not a valid row, ";
               out << "rows are between 1 and " << sticks. size( ) << "\n";
            }
            
         }
         catch( std::invalid_argument& inv )
         {
            out << inp << " is not a number\n";
         }
         catch( std::out_of_range& r )
         {
            out << inp << " is too big\n";
         }
      }
   }
   else
      return optional_move( ); 
}

optional_move state:: removelastmorethantwo( ) const
{
  int countMoreTwo = 0;
    for( int i = 0; i  < sticks.size(); i++)
    {
      if (sticks[i] >=2)
        countMoreTwo ++;
    }
  
  if(countMoreTwo != 1)
     return optional_move(); 
  
  int remainSt;
  int row;
  int countOne = 0;
        
    for (int i = 0; i < sticks.size(); i++)
    {
      if (sticks[i] == 1)
        countOne ++;
      if (sticks[i] >1)
        row = i;
    }
         
  if((countOne + 1) % 2 == 1)
     return move(row, 1);
  else 
     return move(row, 0);
      
   
}

unsigned int state:: nimber( ) const
{
  int resXOR = 0; 
  
  for (int i = 0; i < sticks.size(); i++)
  {
   resXOR = resXOR^sticks[i];
  } 

return resXOR;
} 

optional_move state:: makenimberzero( ) const
{

 int resXor = nimber();

 if (resXor == 0)
 {
  return optional_move();
 }

 int row;
 for (int i = 0; i < sticks.size(); i++)
    {
      if (sticks[i] ^ resXor <= sticks[i])
       row = i;
    }
 int remain = (sticks[row] ^ resXor);
 return move(row, remain ); 
}
