#include "TableauPile.h"

TableauPile::TableauPile()
{

}

bool TableauPile::accepts(const Card& card)
{
  if(isEmpty()) {
    return card.getRank() == Card::KING;
  }

  return getTop().isFlipped() && (getTop().isBlack() != card.isBlack()) &&
      (static_cast<int>(getTop().getRank()) - 1 == static_cast<int>(card.getRank()));
}
