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
    }
    if(sign == 0){
        return 0;
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
    }
    if(sign == 0){
        return 0;
    }else{
        return (*be);
    }
}
int ObjectPool::GetFieldAttachedToObject(int){

}
void ObjectPool::DeleteObjectById(int id1){

}
void ObjectPool::DeleteFieldByid(int){

}
