
#include "tree.h"


int main( int argc, char* argv [ ] )
{
   tree t1( std::string( "a" ));
   tree t2( std::string( "b" ), {t1, t1}); 
   //tree t11 = t1;
   //std::cout << t1;
   //t1 = t2;
   //std::cout << t2;
   
   tree t3 = tree( std::string( "f" ), { t1, t2 } ); 
   std::cout << t1 << '\n';

   std::cout << subst(t3, "a" , t2) << '\n';

   std::cout << t1 << '\n';

   //std::cout << t1 << '\n';


   
   std::vector< tree > arguments = { t1, t2, t3 };

   //std::cout << tree( "F", std::move( arguments )) << "\n";
   //std::cout << t3;
   t3.replaceSubtree(0,tree(std::string("c")));
   //std::cout << subst(t3, "a", t1);

   //std::cout << t3;
   //std::cout << t3;
   t2 = t3;
   t2 = std::move(t3);

}






