#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "mgraphicscene.h"

mGraphicScene::mGraphicScene(QObject *parent) :
    QGraphicsScene(parent)
{
}

void mGraphicScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    //emit sigMouseClick(mouseEvent->pos(), mouseEvent->button() == Qt::LeftButton);
    QPointF screenPos = mouseEvent->scenePos();

    if(mouseEvent->button() == Qt::LeftButton)
    {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item)
        {
//            if(item->data(0).toString() == "block")
//            {
//                mnu_block *pblock = (mnu_block *)item;
//                QVector<T_BLOCK_SETTING> sets = diag->getBlockSettingNames(pblock->getInfo());
//                tempSettings = pblock->getLocalSettings();
//                //QDialog *p = createSettingsDialog(sets, pblock->getLocalSettings());
//                T_BLOCK_RAW tempRaw = diag->getBlockRawByInfo(pblock->getInfo());
//                QDialog *p = createSettingsDialog(sets, QString::fromStdString(pblock->getInfo().help), QString::fromStdString(pblock->getInfo().desc));
//                curEditedItem = pblock;
//                int result = p->exec();
//                if(result)
//                    pblock->setLocalSettings(tempSettings);
//                curEditedItem = NULL;
//            }
            emit sigMouseClick(static_cast<RadioItem *>(item)->getParams());
        }
        else
        {
            T_RADIO_PARAM foo;
            emit sigMouseClick(foo);
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);    // Вызываем метод предка, а то не будет двигаться
}

void mGraphicScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

    QPointF screenPos = mouseEvent->scenePos();
    if(mouseEvent->button() == Qt::LeftButton)
    {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item)
        {
            emit sigMouseRelease(static_cast<RadioItem *>(item)->getParams().id());
        }
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);

}
