#include "materials/material.h"

Material::Material()
{
    // sane defaults
    m_ambientReflectionCoeff = 0.6;
    m_diffuseReflectionCoeff = 0.3;
    m_specularReflectionCoeff = 0.2;

    m_phongAttenuation = 0.5;
    m_phongSpecularity = 5;
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

void Material::setPhongAttenuation(double coeff)
{
    m_phongAttenuation = coeff;
}

double Material::getPhongAttenuation()
{
    return m_phongAttenuation;
}

void Material::setPhongSpecularity(double coeff)
{
    m_phongSpecularity = coeff;
}

double Material::getPhongSpecularity()
{
    return m_phongSpecularity;
}