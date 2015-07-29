struct Textures
{
    int hasKd;
    int hasKs;
    int hasNs;
    int hasNormal;
    int hasAlpha;

    sampler2D kd;
    sampler2D ks;
    sampler2D ns;
    sampler2D normal;
    sampler2D alpha;
};

struct Material
{
    vec4 kd;
    vec4 ks;

    float ns;

    Textures tex;
};

struct Attenuation
{
    float constant;
    float linear;
    float quadratic;
};

struct DirectionalLight
{
    vec3 direction;
};

struct PointLight
{
    vec3 position;
    Attenuation attenuation;
};

struct SpotLight
{
    vec3 position;
    vec3 direction;

    Attenuation attenuation;

    float innerAngle;
    float outerAngle;
};

struct Light
{
    int type;
    vec4 color;

    DirectionalLight directional;
    PointLight point;
    SpotLight spot;
};

uniform Material material;
uniform Light light;

out vec4 fragColor;

in vec3 vPosition;
in vec3 vNormal;
in vec3 vTexcoord;
in vec3 vEye;

vec3 getKd()
{
    if (material.tex.hasKd == 1)
    {
        return vec3(texture(material.tex.kd, vTexcoord.xy));
    }
    else
    {
        return material.kd.xyz;
    }
}

vec3 getKs()
{
    if (material.tex.hasKs == 1)
    {
        return vec3(texture(material.tex.ks, vTexcoord.xy));
    }
    else
    {
        return material.ks.xyz;
    }
}

float getNs()
{
	if (material.tex.hasNs == 1)
	{
		return texture(material.tex.ns, vTexcoord.xy).r;
	}

	return material.ns;
}

vec3 getNormal()
{
    float dir = gl_FrontFacing ? 1.0 : -1.0;
    if (material.tex.hasNormal == 1)
    {
        vec3 n = normalize(vec3(texture(material.tex.normal, vTexcoord.xy)));
        n = n * 2 - 1;
        return dir * n;
    }
    else
    {
        return vec3(dir * normalize(vNormal));
    }
}

vec3 blinnPhongInternal(vec3 d, vec3 n)
{
    vec3 direction = normalize(d);
    vec3 normal = normalize(n);
    float diffFactor = dot(normal, -direction);

    vec3 diff = vec3(0);
    vec3 spec = vec3(0);

    if (diffFactor > 0.0)
    {
        diff = diffFactor * light.color.xyz * getKd();

        vec3 vertToEye = normalize(vEye - vPosition);
        vec3 lightReflect = normalize(reflect(-direction, normal));
        float specFactor = dot(vertToEye, lightReflect);

        if (specFactor > 0.0)
        {
            specFactor = pow(specFactor, getNs());
            spec = specFactor * light.color.xyz * getKs();
        }
    }

    return diff + spec;
}

vec3 blinnPhongSpot()
{
    vec3 dir = light.spot.direction;
    vec3 color;

    float d = length(dir);
    float attenuation = light.spot.attenuation.constant +
                        light.spot.attenuation.linear * d +
                        light.spot.attenuation.quadratic * d * d;
    attenuation = 1.0 / attenuation;

    vec3 lightToPixel = normalize(vPosition - light.spot.position);

    float cosRealAngle = dot(lightToPixel, -normalize(dir));
    float cosSpotOuter = cos(light.spot.innerAngle / 2.0);

    float radialAttenuation = pow(clamp((cosRealAngle - cosSpotOuter) /
                                        (1.0 - cosSpotOuter), 0.0, 1.0), 1.6);

    color = blinnPhongInternal(-dir, getNormal());
    return color * attenuation * radialAttenuation;
}

vec3 blinnPhongPoint()
{
    vec3 dir = vPosition - light.point.position;
    vec3 color = blinnPhongInternal(normalize(dir), getNormal());

    float d = length(dir);
    float attenuation = light.point.attenuation.constant +
                        light.point.attenuation.linear * d +
                        light.point.attenuation.quadratic * d * d;

    return color / attenuation;
}

vec3 blinnPhongDirectional()
{
    return blinnPhongInternal(light.directional.direction, getNormal());
}

void main()
{

    vec3 color;
    switch (light.type)
    {
        case 0:
        {
            color = blinnPhongDirectional();
        } break;

        case 1:
        {
            color = blinnPhongPoint();
        } break;

        case 2:
        {
            color = blinnPhongSpot();
        } break;

        default:
        {
            color = vec3(0, 0, 0);
        } break;
    }

	if (material.tex.hasAlpha == 1)
	{
		float alpha = texture(material.tex.alpha, vTexcoord.xy).r; 
		if (alpha < 0.1)
		{
			discard;
		}
		//color = vec3(1, 1, 0);
	}

    fragColor = vec4(color, 1.0);
}
