#ifndef EZGINE_H
#define EZGINE_H

#include<list>

using namespace std;

class Ezgine{
public:
    Ezgine():objectpool(ObjectPool()){}
    int PutObjectGetId(Entity&);
    void Step();
    void DeleteObjectById(int);
    list<pair<Entity, Entity> > RoughCollapseJudge(ObjectPool&);
    list<pair<Entity, Entity> > ExactCollaspeJudge(list<pair<Entity, Entity> >);
    void Collapse(list<pair<Entity, Entity> >);
    void Move(ObjectPool&);
protected:
private:
    Ezgine(const Ezgine&):objectpool(ObjectPool()){}
    ObjectPool& objectpool;
};

class ObjectPool{
public:
    ObjectPool(){}
    int AddObjectGetId(Entity&);
    list<Entity> GetObjects(){return this->objectpool;}
    Entity& GetObjectsById(int);
    list<ForceField> GetFields();
    void DeleteObjectById(int); 
protected:
    list<Entity> objectpool;
private:
};

//below entities
class Entity{
public:
    Entity();
    virtual ~Entity(){}
    void Move();
    int GetMass(){return masspoint.GetMass();}
    int AddForceField(ForceField& FF){forcefields.push_back(FF);ffid_alloc++;return (ffid_alloc-1);}
    double GetX(){return masspoint.GetX();}
    double GetY(){return masspoint.GetY();}
    double GetVX(){return masspoint.GetVY();}
    double GetVY(){return masspoint.GetVX();}
    double GetFX(){return masspoint.GetFX();}
    double GetFY(){return masspoint.GetFY();}
    const list<ForceField>& GetForceFields(){return forcefields;}
    const CollisionBox& GetCollisionBox(){return collisionbox;}
    void DeleteForceFieldById(int id);
    void AddFX(double FX){masspoint.AddFX(FX);}
    void AddFY(double FY){masspoint.AddFY(FY);}
    void EditVX(double VX){masspoint.EditVX(VX);}
    void EditVY(double VY){masspoint.EditVY(VY);}
    void SetMPType(int type){masspoint.SetType(type);}
    void SetCBType(int type){collisionbox.SetType(type);}
    void SetMPType(int type){masspoint.SetType(type);}
    virtual void ReceiveBroadcast(){};
protected:

    int AllocFFid(){ffid_alloc++; return(ffid_alloc-1);}
    Entity(const Entity&){};
    static int id_alloc;
    int id;
    int ffid_alloc = 0;
    MassPoint masspoint;
    CollisionBox collisionbox;
    list<ForceField> forcefields;
private:
};
class MassPoint{
    friend Entity;
public:
protected:
    MassPoint(int m, int x, int y):mass(m),coordinate_x(x),coordinate_y(y),
        velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0),father(Entity()){}
    MassPoint(const MassPoint&):father(Entity()){}
    MassPoint():mass(65535),coordinate_x(0),coordinate_y(0),
    velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0),father(Entity()){}
    virtual ~MassPoint(){}
    int GetMass(){return mass;}
    int GetType(){return type;}
    double GetX(){return coordinate_x;}
    double GetY(){return coordinate_y;}
    double GetVX(){return velocity_x;}
    double GetVY(){return velocity_y;}
    double GetFX(){return tem_force_x;}
    double GetFY(){return tem_force_y;}
    void AddFX(double FX){tem_force_x+=FX;}
    void AddFY(double FY){tem_force_y+=FY;}
    void EditVX(double VX){velocity_x = VX;}
    void EditVY(double VY){velocity_y = VY;}
    void SetType(int type){this->type = type;}

    Entity& father;
    int mass;
    int type;
    double coordinate_x;
    double coordinate_y;
    double velocity_x;
    double velocity_y;
    double tem_force_x;
    double tem_force_y;
private:
};
class CollisionBox{
    friend Entity;
public:
protected:
    CollisionBox():father(Entity()){};
    CollisionBox(const CollisionBox&):father(Entity()){}
    CollisionBox(Entity& entity):father(entity){}
    virtual ~CollisionBox(){};
    virtual int GetShape(){return 0;}
    int GetType(){return type;}
    void SetType(int type){this->type = type;}

    Entity& father;
    int shape;
    int type;
    double center_x;
    double center_y;
    double bounce_rate;
private:
};
class CollisionBox_Round : public CollisionBox{
public:
    int GetRadious(){return radious;}
    virtual int GetShape(){return 1;}
protected:
    int radious;
private:
};
class CollisionBox_Rectangle : public CollisionBox{
public:
    int GetWidth(){return width;}
    int GetHeight(){return height;}
    virtual int GetShape(){return 2;}
protected:
    int width;
    int height;
private:
};
class ForceField{
    friend Entity;
public:
protected:
    virtual int CreateFF(Entity& entity){ForceField FF(entity);return entity.AddForceField(FF);}
    virtual pair<double, double> force(const Entity&){};
    Entity& father;
    int id;
private:
    ForceField():father(Entity()){}
    ForceField(Entity& entity):father(entity){}
    ForceField(const ForceField&):father(Entity()){}
};
#endif