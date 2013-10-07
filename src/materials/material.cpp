#include "materials/material.h"

Material::Material()
{
    // sane defaults
    m_ambientIntensity = 0.6;
    m_diffuseIntensity = 0.3;
    m_specularIntensity = 0.2;

    m_reflectivity = 0.0;

    m_phongAttenuation = 0.5;
    m_phongSpecularity = 5;

    m_opacity = 0.0;
    m_refractiveIndex = 1.0;
}

Material::~Material()
{

}

void Material::setAmbientIntensity(double intensity)
{
    m_ambientIntensity = intensity;
}

double Material::getAmbientIntensity()
{
    return m_ambientIntensity;
}

Colour Material::getDiffuseColour()
{
    return m_diffuseColour;
}

void Material::setDiffuseColour(Colour colour)
{
    m_diffuseColour = colour;
}

void Material::setDiffuseIntensity(double intensity)
{
    m_diffuseIntensity = intensity;
}

double Material::getDiffuseIntensity()
{
    return m_diffuseIntensity;
}

void Material::setSpecularIntensity(double intensity)
{
    m_specularIntensity = intensity;
}

double Material::getSpecularIntensity()
{
    return m_specularIntensity;
}

void Material::setPhongAttenuation(double attenuation)
{
    m_phongAttenuation = attenuation;
}

double Material::getPhongAttenuation()
{
    return m_phongAttenuation;
}

void Material::setPhongSpecularity(double specularity)
{
    m_phongSpecularity = specularity;
}

double Material::getPhongSpecularity()
{
    return m_phongSpecularity;
}

void Material::setReflectivity(double reflectivity)
{
    m_reflectivity = reflectivity;
}

double Material::getReflectivity()
{
    return m_reflectivity;
}

void Material::setOpacity(double transparency)
{
	m_opacity = transparency;
}

double Material::getOpacity()
{
	return m_opacity;
}
