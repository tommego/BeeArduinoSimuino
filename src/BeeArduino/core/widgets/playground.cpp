#include "playground.h"
#include <QVBoxLayout>
#include <QScrollBar>
#include "../entities/unoboardentity.h"
#include <QStyleOptionGraphicsItem>

#include "../systems/connectorsystem.h"
#include "../entities/whiteledentity.h"
#include "../entities/groundentity.h"

Playground::Playground(QWidget *parent) : QFrame(parent),
    mRenderView(QSharedPointer<RenderView>(new RenderView(this))),
    mScene(QSharedPointer<QGraphicsScene>(new QGraphicsScene(this))),
    mEntityManager(QSharedPointer<EntityManager>(new EntityManager)),
    mSystemManager(QSharedPointer<SystemManager>(new SystemManager)),
    mSceneUpdateTimer(QSharedPointer<QTimer>(new QTimer(this))),
    mMinZoomFactor(5),
    mMaxZoomFactor(1000),
    mZoomFactor(25),
    mZoomBase(25)
{
    mSceneUpdateTimer->setInterval(20);
    initUI();
    initConnections();
    initSystems();
    mSceneUpdateTimer->start();
}

void Playground::initUI()
{
    setFrameStyle(Sunken | StyledPanel);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(mRenderView.data());
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);

    mRenderView->setScene(mScene.data());

    // test
    UnoBoardEntity* unoBoard = new UnoBoardEntity();
    mEntityManager->addEntity(unoBoard);
    mScene->addItem(unoBoard);

    WhiteLedEntity* whiteLed = new WhiteLedEntity;
    mEntityManager->addEntity(whiteLed);
    mScene->addItem(whiteLed);

    GroundEntity* ground = new GroundEntity;
    mEntityManager->addEntity(ground);
    mScene->addItem(ground);

    setStyleSheet("background-color: #232936; border-color: #444444;");
}

void Playground::initConnections()
{
    connect(mRenderView.data(), &RenderView::reqeustZoomIn, [=]{
        mZoomFactor += 1;
        if(mZoomFactor > mMaxZoomFactor)
            mZoomFactor = mMaxZoomFactor;
        setupMatrix();
    });
    connect(mRenderView.data(), &RenderView::requestZoomOut, [=]{
        mZoomFactor -= 1;
        if(mZoomFactor < mMinZoomFactor)
            mZoomFactor = mMinZoomFactor;
        setupMatrix();
    });

    connect(mSceneUpdateTimer.data(), &QTimer::timeout, [=]{
        mScene->update(mRenderView->sceneRect());
    });
}

void Playground::initSystems()
{
    ConnectorSystem* connectorSys = new ConnectorSystem(nullptr, mScene.data());
    mSystemManager->addSystem(connectorSys);
}

void Playground::setupMatrix()
{
    QMatrix matrix;
    qreal scale = qPow(2, (mZoomFactor - mZoomBase) / qreal(10));
    matrix.scale(scale, scale);
    mRenderView->setMatrix(matrix);
}

RenderView::RenderView(QWidget *parent): QGraphicsView(parent)
{
    setRenderHint(QPainter::Antialiasing, true);
    setDragMode(QGraphicsView::RubberBandDrag);
    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
//    setRubberBandSelectionMode(Qt::IntersectsItemShape);
}

void RenderView::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers() & Qt::ControlModifier){
        if(event->angleDelta().y() > 0) {
            emit reqeustZoomIn();
        }
        if(event->angleDelta().y() < 0) {
            emit requestZoomOut();
        }
    }
    QGraphicsView::wheelEvent(event);
}

//void RenderView::mouseMoveEvent(QMouseEvent *e)
//{
//    QGraphicsView::mouseMoveEvent(e);
//}

//void RenderView::mousePressEvent(QMouseEvent *e)
//{
//    if(e->modifiers() & Qt::ControlModifier){
//        setDragMode(QGraphicsView::ScrollHandDrag);
//    } else {
//        setDragMode(QGraphicsView::RubberBandDrag);
//    }
//    QGraphicsView::mousePressEvent(e);
//}

//void RenderView::mouseReleaseEvent(QMouseEvent *e)
//{
//    setDragMode(QGraphicsView::RubberBandDrag);
//    QGraphicsView::mouseReleaseEvent(e);
//}
