#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "types/colour.h"

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

    // reflection
    void    setReflectionalCoeff(double coeff);
    double  getReflectionalCoeff();

    // phong light model
    void    setPhongAttenuation(double coeff);
    double  getPhongAttenuation();

    void    setPhongSpecularity(double coeff);
    double  getPhongSpecularity();

private:
    // material colour
    Colour  m_colour;

    // lighting coefficients
    double  m_ambientReflectionCoeff;
    double  m_diffuseReflectionCoeff;
    double  m_specularReflectionCoeff;

    // reflection
    double  m_reflectionCoeff;

    // phong variables
    double  m_phongAttenuation;
    double  m_phongSpecularity;

};

#endif
