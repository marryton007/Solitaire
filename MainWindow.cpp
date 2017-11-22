#include "MainWindow.h"
#include "CardItem.h"
#include "DeckItem.h"
#include "TableauItem.h"
#include "CardPileItem.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  m_scene = new QGraphicsScene;
  m_view = new QGraphicsView{m_scene};

  m_scene->setSceneRect(0, 0, 800, 600);
  m_view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  m_view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  setFixedSize(800, 600);
  setCentralWidget(m_view);

  initializeGame();
  addComponents();
}

MainWindow::~MainWindow()
{
  delete m_scene;
}

void MainWindow::initializeGame()
{
  m_deck.shuffle();

  for(size_t i = 0; i < Tableau::PILE_COUNT; i++) {
    TableauPile& pile = m_tableau.getPile(i);

    for(size_t j = 0; j <= i; j++) {
      pile.add(m_deck.draw(), false);
    }

    pile.top().flip();
  }
}

void MainWindow::addComponents()
{
  auto deck = new DeckItem{this, m_deck};

  for(size_t i = 0; i < Tableau::PILE_COUNT; i++) {
    auto pile = new CardPileItem{this, m_tableau.getPile(i)};
    pile->moveBy((CardItem::WIDTH + TableauItem::PADDING) * (i + 1), CardItem::HEIGHT + TableauItem::PADDING);
    m_scene->addItem(pile);
  }

  m_scene->addItem(deck);
}
