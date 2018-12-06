#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QFrame>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>
#include <QMouseEvent>
#include "../global/defines.h"
#include <QSlider>
#include "../ecs/entitymanager.h"
#include "../ecs/systemmanager.h"

class RenderView: public QGraphicsView{
    Q_OBJECT
public:
    explicit RenderView(QWidget* parent = nullptr);
signals:
    void reqeustZoomIn();
    void requestZoomOut();

protected:
    void wheelEvent(QWheelEvent* event) override;
//    void mouseMoveEvent(QMouseEvent* e) override;
//    void mousePressEvent(QMouseEvent* e) override;
//    void mouseReleaseEvent(QMouseEvent* e) override;
private:
};

class Playground : public QFrame
{
    Q_OBJECT
public:
    explicit Playground(QWidget *parent = nullptr);
    void initUI();
    void initConnections();
    void initSystems();

signals:

public slots:
    void setupMatrix();

private:
    QSharedPointer<RenderView> mRenderView;
    QSharedPointer<QGraphicsScene> mScene;
    QSharedPointer<EntityManager> mEntityManager;
    QSharedPointer<SystemManager> mSystemManager;
    QSharedPointer<QTimer> mSceneUpdateTimer;
    int mMinZoomFactor;
    int mMaxZoomFactor;
    int mZoomFactor;
    int mZoomBase;
};

#endif // PLAYGROUND_H
