#include "DeckItem.h"

#include "CardItem.h"
#include "MainWindow.h"

#include <QBrush>
#include <QGraphicsScene>

DeckItem::DeckItem(MainWindow* window, Deck& deck)
  : GameItem{window}, m_deck{deck}
{

}

QRectF DeckItem::boundingRect() const
{
  return QRectF{0, 0, CardItem::WIDTH, CardItem::HEIGHT};
}

void DeckItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*)
{
  auto rect = boundingRect();

  if(m_deck.isEmpty()) {
    QPen pen{Qt::black};
    painter->setPen(pen);
    painter->drawRect(rect);
  } else {
    painter->fillRect(rect, QBrush(Qt::blue));
  }
}

void DeckItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent*)
{
  if(m_deck.isEmpty()) {
    window()->resetDeck();
    update();
    return;
  }

  auto card = m_deck.draw();

  if(!card.isFlipped()) {
    card.flip();
  }

  CardItem* item = new CardItem{window(), card};
  item->moveBy(0, boundingRect().height() + 10);
  scene()->addItem(item);

  update();
}
