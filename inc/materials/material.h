#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "types/colour.h"

class Material
{
public:
    Material();
    ~Material();

    // ambient
    void    setAmbientIntensity(double intensity);
    double  getAmbientIntensity();

    // diffuse
    void    setDiffuseColour(Colour colour);
    Colour  getDiffuseColour();
    void    setDiffuseIntensity(double intensity);
    double  getDiffuseIntensity();

    // specular
    void    setSpecularIntensity(double intensity);
    double  getSpecularIntensity();

    void    setPhongAttenuation(double attenuation);
    double  getPhongAttenuation();

    void    setPhongSpecularity(double specularity);
    double  getPhongSpecularity();

    // reflection
    void    setReflectivity(double reflectivity);
    double  getReflectivity();

	// transmission
	void    setOpacity(double opacity);
	double  getOpacity();

    // refractive index
    void    setRefractiveIndex(double index);
    double  getRefractiveIndex();

private:
    // ambient
    double  m_ambientIntensity;

    // diffuse
    Colour  m_diffuseColour;
    double  m_diffuseIntensity;
    
    // specular
    double  m_specularIntensity;
    double  m_phongAttenuation;
    double  m_phongSpecularity;

    // reflection
    double  m_reflectivity;

	// transmission
	double m_opacity;
    double m_refractiveIndex;
};

#endif
