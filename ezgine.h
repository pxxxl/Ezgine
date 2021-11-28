#ifndef EZGINE_H
#define EZGINE_H

#include<list>

using namespace std;

class Ezgine{
public:
    Ezgine():objectpool(ObjectPool()),collapsecontroler(CollapseControler())
    ,movecontroler(MoveControler()){}
    int PutObjectGetId(Entity&);
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
    int AddObjectGetId(Entity&);
    list<Entity> GetObjects(){return this->objectpool;}
    Entity& GetObjectsById(int);
    list<ForceField> GetFields();
    void DeleteObjectById(int); 
protected:
    list<Entity> objectpool;
private:
};

class CollapseControler{
public:
    CollapseControler(){}
    list<pair<Entity, Entity> > RoughCollapseJudge(ObjectPool&);
    list<pair<Entity, Entity> > ExactCollaspeJudge(list<pair<Entity, Entity> >);
    void Collapse(list<pair<Entity, Entity> >);
protected:
private:
};

class MoveControler{
public:
    MoveControler(){}
    void Move(ObjectPool&);
protected:
private:
};

class ForceFieldControler{
    friend Ezgine;
public:
protected:

private:
};

//below entities
class Entity{
public:
    Entity(){};
    virtual ~Entity(){}
    Entity(const Entity&){};
    void Move();
    int GetMass(){return masspoint.GetMass();}
    double GetX(){return masspoint.GetX();}
    double GetY(){return masspoint.GetY();}
    double GetVX(){return masspoint.GetVY();}
    double GetVY(){return masspoint.GetVX();}
    double GetFX(){return masspoint.GetFX();}
    double GetFY(){return masspoint.GetFY();}
    const list<ForceField>& GetForceFields(){return forcefields;}
    const CollisionBox& GetCollisionBox(){return collisionbox;}
    void AddFoeceField(ForceField ff){forcefields.push_back(ff);}
    void DeleteForceFieldById(int id);
    void AddFX(double FX){masspoint.AddFX(FX);}
    void AddFY(double FY){masspoint.AddFY(FY);}
    void EditVX(double VX){masspoint.EditVX(VX);}
    void EditVY(double VY){masspoint.EditVY(VY);}
protected:
private:
    MassPoint masspoint;
    CollisionBox collisionbox;
    list<ForceField> forcefields;
};
class MassPoint{
    friend Entity;
public:
protected:
    MassPoint(int m, int x, int y):mass(m),coordinate_x(x),coordinate_y(y),
        velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0){}
    MassPoint(const MassPoint&){}
    MassPoint():mass(65535),coordinate_x(0),coordinate_y(0),
    velocity_x(0), velocity_y(0), tem_force_x(0), tem_force_y(0){}
    virtual ~MassPoint(){}
    int GetMass(){return mass;}
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
    int mass;
    double coordinate_x;
    double coordinate_y;
    double velocity_x;
    double velocity_y;
    double tem_force_x;
    double tem_force_y;
private:
};
class CollisionBox{
public:
    CollisionBox(){};
    CollisionBox(const CollisionBox&){}
    virtual ~CollisionBox(){};
    virtual void OnCollisionExtraReaction();
    virtual int GetType(){return 0;}
protected:
    int type;
    double center_x;
    double center_y;
    double bounce_rate;
private:
};
class CollisionBox_Round : public CollisionBox{
public:
    int GetRadious(){return radious;}
    virtual int GetType(){return 1;}
protected:
    int radious;
private:
};
class CollisionBox_Rectangle : public CollisionBox{
public:
    int GetWidth(){return width;}
    int GetHeight(){return height;}
    virtual int GetType(){return 2;}
protected:
    int width;
    int height;
private:
};

class ForceField{
public:
    virtual pair<double, double> force(const Entity&){};
    int GetId(){return id;}
    int GetAttach_id(){return attach_id;}
    void AttachEntity(int id);
protected:
    static int id_num;
    int id;
    int attach_id;
private:
};
//comp
#endif