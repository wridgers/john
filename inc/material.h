#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "colour.h"

class Material
{
public:
    Material();
    ~Material();

    // material colour settings
    Colour  getColour();
    void    setColour(Colour col);

    // lighting coefficients
    void    setAmbientReflectionCoeff(double coeff);
    double  getAmbientReflectionCoeff();

    void    setDiffuseReflectionCoeff(double coeff);
    double  getDiffuseReflectionCoeff();

    void    setSpecularReflectionCoeff(double coeff);
    double  getSpecularReflectionCoeff();

private:
    // material colour
    // TODO: diffuse colour, ambient colour, and specular colour
    Colour  colour;

    // lighting coefficients
    double  ambientReflectionCoeff;
    double  diffuseReflectionCoeff;
    double  specularReflectionCoeff;

};

#endif
