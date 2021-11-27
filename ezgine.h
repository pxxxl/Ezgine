#ifndef EZGINE_H
#define EZGINE_H

#include<list>

using namespace std;



class Ezgine{
public:
    Ezgine():objectpool(ObjectPool()),collapsecontroler(CollapseControler())
    ,movecontroler(MoveControler()){}
    void PutObject(MassPoint&);
    void Step();
    void DeleteObjectById(int);
    
protected:
private:
    Ezgine(const Ezgine&):objectpool(ObjectPool()),collapsecontroler(CollapseControler())
    ,movecontroler(MoveControler()){}
    ObjectPool& objectpool;
    CollapseControler& collapsecontroler;
    MoveControler& movecontroler;
};

class ObjectPool{
public:
    ObjectPool(){}
    void AddObject(MassPoint&);
    void AddField(ForceField&);
    list<MassPoint> GetObjects();
    MassPoint& GetObjectsById(int);
    list<ForceField> GetFields();
    ForceField& GetFieldsById(int);
    int GetFieldAttachedToObject(int);
    void DeleteObjectById(int);
    void DeleteFieldByid(int); 
protected:
    list<MassPoint> pointpool;
    list<ForceField> fieldpool;
private:
};

class CollapseControler{
public:
    CollapseControler(){}
    
protected:
private:
};

class MoveControler{
public:
    MoveControler(){}
    
protected:
private:
};



//below entities
class MassPoint{
public:
    MassPoint(int m, int x, int y):mass(m),coordinate_x(x),coordinate_y(y),
        velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0), id(id_number)
        ,collisionbox(nullptr){id_number++;}
    MassPoint(const MassPoint&){}
    virtual ~MassPoint(){}
    int GetId(){return id;}
protected:
    static int id_number;
    int id;
    int mass;
    double coordinate_x;
    double coordinate_y;
    double velocity_x;
    double velocity_y;
    double tem_force_x;
    double tem_force_y;
    CollisionBox* collisionbox;
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
    double center_x;
    double center_y;
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

class ForceField{
public:
    virtual pair<double, double> force(int,int){}
    int GetId(){return id;}
protected:
    int type;
    int id;
private:
};

#endif