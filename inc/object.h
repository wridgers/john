#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "material.h"

using namespace std;

class Object
{
public:
    Object();
    ~Object();

    Material*   getMaterial();
    void        setMaterial(Material* mat);

private:

    Material*   material;

};

#endif