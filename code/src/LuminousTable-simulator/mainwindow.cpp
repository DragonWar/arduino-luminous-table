#include "mainwindow.h"

#include <QDebug>
#include <QColor>

#include "TableBehaviorDarkSky.h"
#include "TableBehaviorRandomDot.h"
#include "TableBehaviorSnake.h"
#include "TableBehaviorUnicolor.h"
#include "TableBehaviorPixelart.h"
#include "TableBehaviorVUmeter.h"
#include "TableBehaviorVUmeterB.h"
#include "TableBehaviorRandomDotSound.h"

//---------------------------------------------------------------------------------
// SIMULATOR INITIALIZATION
//---------------------------------------------------------------------------------

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mIndexBehavior = -1;
    beahavior = 0;
    createNextBehavior();

    // Main
    mMainWidget = new QWidget();
    mMainLayout = new QBoxLayout(QBoxLayout::LeftToRight);

    // Matrix
    mMatrixLayout = new QVBoxLayout();
    mMatrixLayout->addWidget(beahavior->getDotMatrix());

    // Inputs
    mButtonA = new QPushButton("Switch");
    mButtonB = new QPushButton("Action");
    connect(mButtonA, SIGNAL(clicked()), this, SLOT(onClickButtonA()));
    connect(mButtonB, SIGNAL(clicked()), this, SLOT(onClickButtonB()));

    mPotentiometer = new QDial();
    mPotentiometer->setMinimum(0);
    mPotentiometer->setMaximum(255);
    mPotentiometer->setValue(192);
    beahavior->setBrightness(mPotentiometer->value());
    connect(mPotentiometer, SIGNAL(valueChanged(int)), this, SLOT(onPotentionmeterChanged(int)));

    mSoundLevel = new QSlider(Qt::Horizontal);
    mSoundLevel->setMinimum(0);
    mSoundLevel->setMaximum(20);
    mSoundLevel->setValue(0);
    connect(mSoundLevel, SIGNAL(valueChanged(int)), this, SLOT(onSoundLevelChanged(int)));

    mInputsLayout = new QVBoxLayout();
    mInputsLayout->addWidget(mButtonA);
    mInputsLayout->addWidget(mButtonB);
    mInputsLayout->addWidget(mSoundLevel);
    mInputsLayout->addWidget(mPotentiometer);

    // Central widget
    mMainLayout->addLayout(mMatrixLayout);
    mMainLayout->addLayout(mInputsLayout);
    mMainWidget->setLayout(mMainLayout);
    this->setCentralWidget(mMainWidget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onClickButtonA()
{
    mMatrixLayout->removeWidget(beahavior->getDotMatrix());
    delete beahavior;

    createNextBehavior();

    beahavior->getDotMatrix()->setIntensity(mPotentiometer->value());
    mMatrixLayout->addWidget(beahavior->getDotMatrix());
}

void MainWindow::createNextBehavior()
{
    mIndexBehavior++;

    if (mIndexBehavior > 4){
        mIndexBehavior = 0;
    }

    switch (mIndexBehavior) {
    case 0:
        beahavior = new TableBehaviorRandomDotSound();
        break;
    case 1:
        beahavior = new TableBehaviorVUmeter();
        break;
    case 2:
        beahavior = new TableBehaviorVUmeterB();
        break;
    case 3:
        beahavior = new TableBehaviorRandomDot();
        break;
    case 4:
        beahavior = new TableBehaviorSnake();
        break;
    default:
        break;
    }


    beahavior->startLoop();
}

void MainWindow::onClickButtonB()
{
    beahavior->onClickButtonB();
}

void MainWindow::onPotentionmeterChanged(int value)
{
    beahavior->getDotMatrix()->setIntensity(value);
}

void MainWindow::onSoundLevelChanged(int value)
{
    beahavior->setSoundLevel(value);
}
