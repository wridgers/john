#include "material.h"

Material::Material()
{
    m_ambientReflectionCoeff = 0.6;
    m_diffuseReflectionCoeff = 0.3;
    m_specularReflectionCoeff = 0.2;
}

Material::~Material()
{

}

Colour Material::getColour()
{
    return m_colour;
}

void Material::setColour(Colour colour)
{
    m_colour = colour;
}

void Material::setAmbientReflectionCoeff(double coeff)
{
    m_ambientReflectionCoeff = coeff;
}

double Material::getAmbientReflectionCoeff()
{
    return m_ambientReflectionCoeff;
}

void Material::setDiffuseReflectionCoeff(double coeff)
{
    m_diffuseReflectionCoeff = coeff;
}

double Material::getDiffuseReflectionCoeff()
{
    return m_diffuseReflectionCoeff;
}

void Material::setSpecularReflectionCoeff(double coeff)
{
    m_specularReflectionCoeff = coeff;
}

double Material::getSpecularReflectionCoeff()
{
    return m_specularReflectionCoeff;
}