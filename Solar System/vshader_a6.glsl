#version 150 

in  vec4 vPosition;
in  vec3 vNormal;
in  vec4 vColor;
in  vec2 vUV;
out vec4 color;
out vec2 vst;
uniform vec4 AmbientProduct, DiffuseProduct, SpecularProduct;
uniform mat4 ModelView;
uniform mat4 Projection;
uniform vec4 LightPosition;
uniform float Shininess;

void main()
{
    // Transform vertex  position into eye coordinates
    vec3 pos = (ModelView * vPosition).xyz;
	
    vec3 L = normalize( LightPosition.xyz - pos );
    vec3 E = normalize( -pos );
    vec3 H = normalize( L + E );

    // Transform vertex normal into eye coordinates
    vec3 N = normalize( ModelView*vec4(vNormal, 0.0) ).xyz;

    // Compute terms in the illumination equation
    //vec4 ambient = AmbientProduct*vColor;
	vec4 ambient=.5*vColor;// lightambient part set to .5
    float Kd = max( dot(L, N), 0.0 );
    vec4  diffuse = Kd*DiffuseProduct;

    float Ks = pow( max(dot(N, H), 0.0), Shininess );
    vec4  specular = Ks * SpecularProduct;
    
    if( dot(L, N) < 0.0 ) {
	specular = vec4(0.0, 0.0, 0.0, 1.0);
    } 

    gl_Position = Projection * ModelView * vPosition;
    color = ambient + diffuse + specular;
  // color=vec4(0.0,1.0,0.0,1.0);
	vst = vec2(max(vUV.x, 0), max(vUV.y, 0));
}
