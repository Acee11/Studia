#include <future>
#include <iostream>
#include "obiad.hpp"

Herbata                zrob_herbate(Woda, TorebkaHerbaty);
PokrojonySurowyKurczak pokroj_kurczaka(SurowyKurczak);
GotowyKurczak          usmaz_kurczaka(PokrojonySurowyKurczak);
UgotowaneZiemniaki     ugotuj_ziemniaki(Woda, SuroweZiemniaki);
Obiad                  zrob_obiad(UgotowaneZiemniaki, GotowyKurczak, Herbata);


Obiad ugotuj()
{
  // To dostajecie
  Woda            woda;
  SuroweZiemniaki suroweZiemniaki;
  SurowyKurczak   surowyKurczak;
  TorebkaHerbaty  torebkaHerbaty;

  // return zrob_obiad(
  //                    ugotuj_ziemniaki( Woda(), SuroweZiemniaki() ),
  //                    usmaz_kurczaka( pokroj_kurczaka( SurowyKurczak() ) ),
  //                    zrob_herbate( Woda(), TorebkaHerbaty() )
  //                  );

  // TODO: tutaj
  auto pokrojonySurowyKurczak = std::async(std::launch::async, pokroj_kurczaka, surowyKurczak);
  auto herbata = std::async(std::launch::async, zrob_herbate, woda, torebkaHerbaty);
  auto ugotowaneZiemniaki = std::async(std::launch::async, ugotuj_ziemniaki, woda, suroweZiemniaki);
  auto usmazonyKurczak = std::async(std::launch::async, usmaz_kurczaka, pokrojonySurowyKurczak.get());
  auto obiad = zrob_obiad(ugotowaneZiemniaki.get(), usmazonyKurczak.get(), herbata.get());
  return obiad;
  // HINT: std::async(std::launch::async, ...)
}



int main()
{
  auto  start  = Clock::now();
  Obiad obiad1 = synchroniczneGotowanie();
  auto  stop   = Clock::now();
  std::cout << "Synchronicznie: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << "[ms]" << std::endl;

  start        = Clock::now();
  Obiad obiad2 = ugotuj();
  stop         = Clock::now();
  std::cout << "Twoja implementacja: "
            << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
            << "[ms]" << std::endl;
}
