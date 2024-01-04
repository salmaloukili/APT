
#ifndef NODE_H
#define NODE_H

#include "publicenums.h"
#include <world.h>
#include <QMap>
#include <QVariant>

struct Node : public Tile {
    float f = 0.0f, g = 0.0f, h = 0.0f;
    bool visited = false;
    Node *prev = nullptr;
    Node(int x, int y, float val)
        : Tile(x, y, val) { }
    Node(const Tile &t)
        : Tile(t) {};
    Node(const Node &n)
        : Tile(n.getXPos(), n.getYPos(), n.getValue())
        , f(n.f)
        , g(n.g)
        , h(n.h)
        , visited(n.visited)
        , prev(n.prev) { }

    Node()
        : Tile(0, 0, 0) { }

    Node(const QMap<DataRole, QVariant> &obj)
        : Tile(obj[DataRole::Position].toPoint().x(),
               obj[DataRole::Position].toPoint().y(),
               obj.contains(DataRole::Energy) ? obj[DataRole::Energy].toFloat() : 0) {
    }

    virtual ~Node() { }

    Node &operator=(const Node &n) {
        if(this != &n) {
            Tile::operator=(n);
            f = n.f;
            g = n.g;
            h = n.h;
            visited = n.visited;
            prev = n.prev;
        }
        return *this;
    }
};

#endif // NODE_H
