#ifndef _MATERIAL_H_
#define	_MATERIAL_H_

#include <assert.h>

#include "vec.h"
#include "constant.h"
#include "Sampling.h"

typedef Vec Color;

class Material
{
public:
	Material(const Color& reflectance, const Color& emission)
		: m_reflectance(reflectance)
		, m_emission(emission)
	{
	}
	virtual ~Material(){}

public:
	virtual Color BRDF(const Vec& in, const Vec& normal, const Vec& out) const = 0;
	virtual Vec Sample(Random& random, const Vec& in, const Vec& normal, double* pdf, Color* brdf_value) const = 0;

public:
	const Color& GetReflecrance() const { return m_reflectance; }
	const Color& GetEmission() const { return m_emission; }

private:
	Material(){}
	Material(const Material& obj){}

protected:
	Color m_reflectance;	//!< 反射率
	Color m_emission;		//!< 発光
};

#if 1
// LambertianBRDF
class LambertianMaterial : public Material
{
public:
	LambertianMaterial(const Color& reflectance) : Material(reflectance, Color(0, 0, 0)){}
	~LambertianMaterial(){}

public:
	Color BRDF(const Vec& in, const Vec& normal, const Vec& out) const override
	{
		return m_reflectance / PI;
	}

	Vec Sample(Random& random, const Vec& in, const Vec& normal, double* pdf, Color* brdf_value) const override
	{
		Vec binormal, tangent, now_normal = normal;

		createOrthoNormalBasis(now_normal, &tangent, &binormal);
		const Vec dir = Sampling::UniformHemisphereSurface(random, now_normal, tangent, binormal);

		// pdf: 1/(2 * pi)
		if (pdf != NULL) {
			*pdf = 1.0 / (2.0 * PI);
		}
		if (brdf_value != NULL) {
			*brdf_value = BRDF(in, normal, dir);
		}
		return dir;
	}

private:

};

#else

// LambertianBRDF
class LambertianMaterial : public Material
{
public:
	LambertianMaterial(const Color& reflectance) : Material(reflectance, Color(0, 0, 0)) {}
	~LambertianMaterial() {}

public:
	Color BRDF(const Vec& in, const Vec& normal, const Vec& out) const override
	{
		return m_reflectance / PI;
	}

	// pdfとしてcosΘ/piを使用してインポータンスサンプリングする。
	Vec Sample(Random& random, const Vec& in, const Vec& normal, double* pdf, Color* brdf_value) const override
	{
		Vec binormal, tangent, now_normal = normal;

		createOrthoNormalBasis(now_normal, &tangent, &binormal);
		const Vec dir = Sampling::cosineWeightedHemisphereSurface(random, now_normal, tangent, binormal);

		// pdf: cosΘ/pi
		if (pdf != NULL) {
			*pdf = dot(normal, dir) / PI;
		}
		if (brdf_value != NULL) {
			*brdf_value = BRDF(in, normal, dir);
		}
		return dir;
	}

private:

};
#endif

// ライト
class LightSource : public Material
{
public:
	LightSource(const Color& emission) : Material(Color(0, 0, 0), emission) {}
	~LightSource(){}

public:
	Color BRDF(const Vec& in, const Vec& normal, const Vec& out) const override
	{
		assert(false);
		return Color();
	}

	Vec Sample(Random& random, const Vec& in, const Vec& normal, double* pdf, Color* brdf_value) const override
	{
		assert(false);
		return Color();
	}

private:
};


#endif // !_MATERIAL_H_
