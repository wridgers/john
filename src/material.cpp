#include "material.h"

Material::Material()
{
    Material::ambientReflectionCoeff = 0.6;
    Material::diffuseReflectionCoeff = 0.3;
    Material::specularReflectionCoeff = 0.2;
}

Material::~Material()
{

}

Colour Material::getColour()
{
    return Material::colour;
}

void Material::setColour(Colour col)
{
    Material::colour = col;
}

void Material::setAmbientReflectionCoeff(double coeff)
{
    Material::ambientReflectionCoeff = coeff;
}

double Material::getAmbientReflectionCoeff()
{
    return Material::ambientReflectionCoeff;
}

void Material::setDiffuseReflectionCoeff(double coeff)
{
    Material::diffuseReflectionCoeff = coeff;
}

double Material::getDiffuseReflectionCoeff()
{
    return Material::diffuseReflectionCoeff;
}

void Material::setSpecularReflectionCoeff(double coeff)
{
    Material::specularReflectionCoeff = coeff;
}

double Material::getSpecularReflectionCoeff()
{
    return Material::specularReflectionCoeff;
}