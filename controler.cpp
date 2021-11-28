#include"ezgine.h"

void Ezgine::PutObject(MassPoint& entity){
    objectpool.AddObject(entity);
}
void Ezgine::DeleteObjectById(int id){
    int f = objectpool.GetFieldAttachedToObject(id);
    if(f == -1){}
    else{
        objectpool.DeleteFieldByid(f);
    }
    objectpool.DeleteObjectById(id);
}


//ObjectPool
void ObjectPool::AddObject(MassPoint& entity){
    pointpool.push_back(entity);
}
void ObjectPool::AddField(ForceField& field){
    fieldpool.push_back(field);
}
MassPoint& ObjectPool::GetObjectsById(int id1){
    auto be = pointpool.begin();
    auto en = pointpool.end();
    int sign = 0;
    while(be!=en){
        if(((*be).GetId())==id1){
            sign = 1;
            break;
        }
        be++;
    }
    if(sign == 0){
        return CMASSPOINT;
    }else{
        return (*be);
    }
}
ForceField& ObjectPool::GetFieldsById(int id1){
    auto be = fieldpool.begin();
    auto en = fieldpool.end();
    int sign = 0;
    while(be!=en){
        if(((*be).GetId())==id1){
            sign = 1;
            break;
        }
        be++;
    }
    if(sign == 0){
        return CFORCEFIELD;
    }else{
        return (*be);
    }
}
void ObjectPool::DeleteObjectById(int id1){
    auto be = pointpool.begin();
    auto en = pointpool.end();
    int sign = 0;
    while(be!=en){
        if(((*be).GetId())==id1){
            be = pointpool.erase(be);
            en = pointpool.end();
        }else{
            be++;
        }
    }
}
void ObjectPool::DeleteFieldByid(int id1){
    auto be = fieldpool.begin();
    auto en = fieldpool.end();
    int sign = 0;
    while(be!=en){
        if(((*be).GetId())==id1){
            be = fieldpool.erase(be);
            en = fieldpool.end();
        }else{
            be++;
        }
    }
}

//CollapseControler

//MoveControler
void MoveControler::Move(ObjectPool&){

}