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
    void    setColour(Colour colour);

    // lighting coefficients
    void    setAmbientReflectionCoeff(double coeff);
    double  getAmbientReflectionCoeff();

    void    setDiffuseReflectionCoeff(double coeff);
    double  getDiffuseReflectionCoeff();

    void    setSpecularReflectionCoeff(double coeff);
    double  getSpecularReflectionCoeff();

    // phong-blinn
    void    setPhongCoeff(double coeff);
    double  getPhongCoeff();

private:
    // material colour
    // TODO: diffuse colour, ambient colour, and specular colour
    Colour  m_colour;

    // lighting coefficients
    double  m_ambientReflectionCoeff;
    double  m_diffuseReflectionCoeff;
    double  m_specularReflectionCoeff;

    // phong blinn
    double  m_phongCoeff;

};

#endif
