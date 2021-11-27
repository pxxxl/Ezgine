#include<vector>

using namespace std;

class Ezgine{
public:
    Ezgine():objectpool(){}
protected:
private:
    Ezgine(const Ezgine&){}
    ObjectPool& objectpool;
    CollapseControler& collapsecontroler;
};

class ObjectPool{
public:
    ObjectPool(){}
    void AddObject(MassPoint&);
    vector<MassPoint> GetObjects();
    MassPoint& GetObjectsById(int);
protected:
    vector<MassPoint> pool;
private:
};

class CollapseControler{
public:
protected:
private:
};



class MassPoint{
public:
    MassPoint(int m, int x, int y):mass(m),coordinate_x(x),coordinate_y(y),
        velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0), id(id_number)
        {id_number++;}
    MassPoint(const MassPoint&){}
    virtual ~MassPoint(){}
protected:
    static int id_number;
    int id;
    int mass;
    int coordinate_x;
    int coordinate_y;
    double velocity_x;
    double velocity_y;
    double tem_force_x;
    double tem_force_y;
    CollisionBox* Collisionbox;
private:
};

class CollisionBox{
public:
    CollisionBox(){};
    CollisionBox(const CollisionBox&){}
    virtual ~CollisionBox(){};
    virtual void OnCollisionExtraReaction();
protected:
    int type;
    int center_x;
    int center_y;
    double bounce_rate;
private:

};
class CollisionBox_Round : public CollisionBox{
public:
protected:
    int radious;
private:
};
class CollisionBox_Rectangle : public CollisionBox{
public:
protected:
    int width;
    int height;
private:
};


