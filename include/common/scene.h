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
        void clear(){
            meshes.clear();
        }
        void add(Object3D *obj){
            std::cout << "add object to scene" << std::endl;
            meshes.push_back(shared_ptr<Object3D>( obj,  [](Object3D*){}) );
        }
        const std::vector<shared_ptr<Object3D>> &getObjects(){
            return meshes;
        }

};
