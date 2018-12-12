#ifndef RADIOITEMLINKER_H
#define RADIOITEMLINKER_H

#include <unordered_map>
#include <memory>
#include "radioitem.h"

class RadioItemLinker
{
public:
    explicit RadioItemLinker(std::shared_ptr<RadioItem> radioItem);
    void addNeighbor(std::shared_ptr<RadioItemLinker> neighbor);
    bool removeNeighbor(std::shared_ptr<RadioItemLinker> neighbor);
    void updateFor(const uint32_t & radioItemId);
    const Point2D & getCentrePoint() const;
    uint32_t getId() const;

private:
    std::shared_ptr<RadioItem> m_radioItem;
    std::unordered_map<uint32_t, std::pair<std::shared_ptr<RadioItemLinker>, uint32_t>> m_neighbors;
};

#endif // RADIOITEMLINKER_H
