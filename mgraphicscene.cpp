#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>
#include "mgraphicscene.h"

mGraphicScene::mGraphicScene(QObject *parent) :
    QGraphicsScene(parent)
{
    connect(this, SIGNAL(changed(QList<QRectF>)), this, SLOT(slotChanged(QList<QRectF>)));
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
            emit sigMouseRelease(static_cast<RadioItem *>(item));
        }
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);

}

#ifdef DEBUG_MESSAGE_SEND
void mGraphicScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *mouseEvent) {

    QPointF screenPos = mouseEvent->scenePos();
    if(mouseEvent->button() == Qt::LeftButton)
    {
        QGraphicsItem * item = itemAt(screenPos, QTransform());
        if(item)
        {
            static_cast<RadioItem *>(item)->testSendMessage();
        }
    }
    QGraphicsScene::mouseDoubleClickEvent(mouseEvent);
}
#endif

void mGraphicScene::slotChanged(const QList<QRectF> & region)
{
    Q_UNUSED(region);
    int size = this->items().length();
    for(int i=0; i<size; i++)
    {
        RadioItem *i_item = (RadioItem*)items()[i];
        i_item->getParams().nb().clear();
        for(int k=0; k<size; k++)
        {
            if(i != k)
            {

                RadioItem *k_item = (RadioItem*)items()[k];
                uint32_t dist = i_item->distanceTo(k_item);

                if(dist < ((RadioItem::RADIO_DISTANCE + RadioItem::RADIO_SIZE)/2))
                {
                    //i_item->params.nb.append(k_item->params.id);
                    i_item->getParams().nb().append(k_item);
                }

                //emit sigStatus(QString("dist = %1").arg(dist));
//                emit sigStatus(QString("[%1, %2], [%3, %4] LEN = %5").arg(x1).arg(y1).arg(x2).arg(y2).arg(temp));
//                if((i_item->pos() - k_item->pos()).manhattanLength() < (RADIO_DISTANCE + RADIO_SIZE/2))
//                {
//                    i_item->params.nb.append(k_item->params.id);
//                    emit sigStatus
//                }
            }
        }
    }
//    if(listNb != listNbStore)
//    {
//        listNbStore = listNb;
//        //emit nbChanged(listNbStore);
//    }

//    asm("   nop");
}
