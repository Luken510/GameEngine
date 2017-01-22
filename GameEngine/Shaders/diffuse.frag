#version 430
//Subroutine to change between shaders at runtime
subroutine vec4 shaderModelType();
subroutine uniform shaderModelType shaderModel;

in vec3 vertPos;
in vec3 N;
in vec3 lightPos;
in vec2 TexCoords; // texture co-ords
in vec3 TargetDir; // target direction


struct Material
{
        sampler2D texture_diffuse1;
        sampler2D texture_specular1;
};


uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity
uniform vec3 Ka;            // abient reflectivity
uniform vec3 La;			// abient light intensity
uniform vec3 Ks;			// Specular reflection
uniform float n;			// specular reflection exponent
uniform float Al;			// light attenuation
uniform Material mats; // material

// for spotlight
uniform float CutOff; // cutoff of light hitting
uniform vec3 TargetDirection; // spotlight direction
uniform vec3 LightPosition; // Light position 
uniform float OuterCutOff; // outer cut off to simulate loss of light

uniform sampler2D texture_diffuse1; // for the textures



layout( location = 0 ) out vec4 FragColour;

void main() {

	FragColour = shaderModel();

	}		

subroutine (shaderModelType)
vec4 Robot()
{
 //Calculate the light vector
   vec3 L = normalize(LightPosition - vertPos); 
// make theta to check if the obj is inside the spotline cone

   float theta = dot(L, normalize(-TargetDirection));

 //calculate ambient
	vec4 Ia = vec4((La * Ka),1.0);

   if(theta > OuterCutOff)
	{
   //Calculate V and R
   vec3 V = normalize(-vertPos);
   vec3 R = normalize(-reflect(L,N));

   //calculate Diffuse Light Intensity making sure it is not negative 
   //and is clamped 0 to 1  
   vec4 Id = vec4(Ld,1.0) * max(dot(N,L), 0.0) * (vec4(Kd,1.0));
   Id = clamp(Id, 0.0, 1.0);   
    
  
   // calculate specular light intensity, making sure it doesnt reflect on the other side
   vec4 Is =  vec4(Ld,1.0) * (pow ( max (dot(R, V), 0.0), n)) * (vec4(Ks, 1.0));
   Is = clamp(Is, 0.0, 1.0);
  

	 float epsilon = (CutOff - OuterCutOff);
	 float Fatt = clamp((theta - OuterCutOff) / epsilon, 0.0,1.0);


   //attenuation
    float distanceToLight = length(LightPosition - vertPos);
    float attenuation = 1.0 / 1.0 + Al * ( pow(distanceToLight, 2));

   //Multiply the Reflectivity by the Diffuse intensity and add ambient
  return FragColour = Ia + attenuation * ( Fatt * ( Id + Is));
		}

	 else 
	 return FragColour = Ia;

		}




// For textured objects
subroutine (shaderModelType)
vec4 Objects()
{

vec4 lightsource1;
 //Calculate the light vector
   vec3 L = normalize(LightPosition - vertPos); 
// make theta to check if the obj is inside the spotline cone

   float theta = dot(L, normalize(-TargetDirection));

 //calculate ambient
	vec4 Ia = vec4((La * Ka),1.0);

   if(theta > OuterCutOff)
{
   //Calculate V and R
   vec3 V = normalize(-vertPos);
   vec3 R = normalize(-reflect(L,N));

   //calculate Diffuse Light Intensity making sure it is not negative 
   //and is clamped 0 to 1  
   vec4 Id =  vec4(Ld,1.0) * max(dot(N,L), 0.0) * (vec4(Kd,1.0));
   Id = clamp(Id, 0.0, 1.0);   
    
  
   // calculate specular light intensity, making sure it doesnt reflect on the other side
   vec4 Is = vec4(Ld,1.0) * (pow ( max (dot(R, V), 0.0), n)) * (vec4(Ks, 1.0));
   Is = clamp(Is, 0.0, 1.0);
  

	float epsilon = (CutOff - OuterCutOff);
	float Fatt = clamp((theta - OuterCutOff) / epsilon, 0.0,1.0);


   //attenuation
    float distanceToLight = length(LightPosition - vertPos);
    float attenuation = 1.0 / 1.0 + Al * ( pow(distanceToLight, 2));

   //Multiply the Reflectivity by the Diffuse intensity and add ambient
     lightsource1 = Ia + attenuation * ( Fatt * ( Id + Is));


	}

   else

     lightsource1 = Ia;


return FragColour = vec4 (texture((texture_diffuse1), TexCoords));

}
