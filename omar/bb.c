#include "hero.h"
#include "entite_secondaire.h"
#include "bb.h"
int colision_bb(Hero *h,entite *e)
{

if ((h.position.x + h.position.w< e.posEntite. x) || (h.position.x> e.posEntite. x + e.posEntite. w) || (h.position.y + h.position.h< e.posEntite. y) || (h.position.y> e.posEntite. y + e.posEntite. h ) )
 {
   return 0;
 }
else
 {
  return 1;
 }

}
