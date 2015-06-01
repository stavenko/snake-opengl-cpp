#pragma once
#include <vector>
#include <memory>
#include <common/object3d.h>

using std::shared_ptr;
class Scene{
    private:
        std::vector<shared_ptr<Object3D>> meshes;
    public:
        Scene(){
            meshes = std::vector<shared_ptr<Object3D>> ();
        }
        void add(Object3D *obj){
            meshes.push_back(shared_ptr<Object3D>( obj ) );
        }
        const std::vector<shared_ptr<Object3D>> &getObjects(){
            return meshes;
        }

};
