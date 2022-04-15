# Solar System

## What's included?
	
  * [CommonOpenGL](https://www.opengl.org/) - A library for interacting with and setting up the GPU and the shaders that render the provided data
  
  * [SOIL](http://lonesock.net/soil.html) - A library for rendering images
	
  * [glew32.dll](http://glew.sourceforge.net/) - An extension wrangler to add support for different hardwares
	
  * [freeglut.dll](http://freeglut.sourceforge.net/) - An OpenGL utility toolkit API

  * Solar System - A rendering of an interpretation of our solar system
	
## Intro and showing off

This project is a continuation of a school project to prototype different techniques
  for rendering using Modern OpenGL and C++. Shaders, GPU allocations, modeling, and
  designs are coded by me with a handful of modifications to libraries that are included. 

## Controls:
	
* x/X - increase/decrease rotation on the x axis

* y/Y - increase/decrease rotation on the y axis
	
* z/Z - increase/decrease rotation on the z axis
	
* w/s - increase/decrease position in the eye_view direction
	
* a/d - increase/decrease position perpendiculart to the eye_view direction
	
* +/- - zoom in/out
	
* 1/! - increase/decrease time of rotation
	
* r - reset orientation

* q - quit/close program
	
## Images without particle system

![Initial view is from the side, from left to right: Sun, Mercury is obscured behind the Sun, Milennium Falcon, Earth with the Moon revolving around it, Mars, Saturn with its rings, and Titan and Enceladus revolving around Saturn in opposing orbits](https://i.postimg.cc/4NVBwYD2/Screenshot-45.png)

![A View from above, Saturn secluded to the right with its moons and rings](https://i.postimg.cc/dQz582xT/Screenshot-46.png)

![A bad isometric view with the planets clustering nearest the camera](https://i.postimg.cc/zDLdbt0r/Screenshot-47.png)


## Process
	
The following process was derived through a course taught by, now retired, 
  [Richard Simpson](http://web.archive.org/web/20190722191417/http://cs.mwsu.edu/~simpson/wordpress/?page_id=1741)
  during his last semester teaching. The assignments built from the ground up
  using contemporary libraries and the result is a rather cumbersome process to
  get started for those unfamiliar. To lower the barrier to entry for anyone who
  sees this, below is the process to set up a new project and/or configure a 
  project to work with the rendering libraries and classes. If the process changes,
  no longer works, or is incomplete, I will make adjustments to the process to
  accommodate these changes and/or issues.

### Setup project
	
Using Visual Studio Community Edition, go to File<sup>1</sup>->New<sup>2</sup>->Project<sup>3</sup>.

![1.1.png](https://i.postimg.cc/1XcVV1dB/1-1.png)

Go to Visual C++ Templates<sup>1</sup>, select Windows application project<sup>2</sup>, and browse to desired project location<sup>3</sup>

Once configured, press OK.

![1.2.png](https://i.postimg.cc/KvxMS4KH/1-2.png)

Remove<sup>3</sup> the provided cpp file<sup>2</sup> from the solution explorer<sup>1</sup>.

![1.3.png](https://i.postimg.cc/Dwz40DPQ/1-3.png)

### Import files

Import desired files into the desired project location (chosen when creating project).

Download or clone this repository.

Copy the following files and folders or download from the above links and place
  into the [ProjectName]/[ProjectName] folder of your visual studio project:

    * CommonOpenGL
    * freeglut.dll
    * glew32.dll
    * SOIL
  
Include the following to set up a standard vertex shader and fragment shader, model class and model loader:

    * fshader_a4.glsl
    * InitShader.cpp
    * Model.cpp
    * Model.h
    * plyloader.cpp
    * plyloader.h
    * vshader_a6.glsl
	
The following files are necessary to run the included program:

    * Earth.ply
    * Enceladus.ply
    * Falcon.ply
    * Mars.ply
    * Mercury.ply
    * Moon.ply
    * Saturn.ply
    * SaturnsRings.ply
    * SolarSystem.cpp
    * Sun.ply
    * Titan.ply

### Add files to project solution

To add files to a project solution, in the Solution Explorer<sup>1</sup>->right click on a folder<sup>2</sup>->Add<sup>3</sup>->Existing Item...<sup>4</sup>

![3.1.png](https://i.postimg.cc/fWx9rYbd/3-1.png)

Add in the imported files using the solution explorer:

    * fshader_a4.glsl
    * vshader_a6.glsl
    * InitShader.cpp
    * Model.cpp
    * Model.h
    * plyloader.h
    * plyloader.cpp
	
Also add the following files inside of the SOIL folder to to project:

    * image_DXT.c
    * image_DXT.h
    * image_helper.c
    * image_helper.h
    * SOIL.c
    * SOIL.h
    * stb_image_aug.c
    * stb_image_aug.h
    * stbi_DDS_aug.h
    * stbi_DDS_aug_c.h
		
### Configure enironment settings

Firstly, we need to configure the environment to allow access to the included libraries and prevent some errors. Go to Project<sup>1</sup>->Properties<sup>2</sup>
	
![4.1.png](https://i.postimg.cc/3w4yCv6d/4-1.png)

Ensure your configuration<sup>2</sup> looks like this inside your configuration manager<sup>1</sup>:

![4.2.png](https://i.postimg.cc/sX5vbR3z/4-2.png)

Close the configuration manager and go to C/C++<sup>1</sup> and change SDL checks<sup>2</sup> to "No (/sdl-)"<sup>3</sup> using the drop down and press Apply<sup>4</sup>

![4.3.png](https://i.postimg.cc/g0CxM0F4/4-3.png)

Go to Linker<sup>1</sup>->System<sup>2</sup>->Use the drop down on the SubSystem row<sup>3</sup> to change "Windows (/SUBSYSTEM:WINDOWS)" to "Console (/SUBSYSTEM:CONSOLE)"<sup>4</sup>

![4.4.png](https://i.postimg.cc/qvZh3L1P/4-4.png)

### Add libraries to environment

To Recognize CommonOpenGL, Angelfiles, and SOIL, go to VC++ Directories<sup>1</sup> and add the following<sup>2</sup> to your Include Directories<sup>3</sup>:	

C:\GraphicsResources\lib\CommonOpenGL\include;C:\GraphicsResources\lib\CommonOpenGL\Angelfiles;$(VC_IncludePath);$(WindowsSDK_IncludePath);<sup>2</sup>*

Add the following<sup>4</sup> to your Library Directories<sup>5</sup>:

C:\GraphicsResources\lib\CommonOpenGL\Simple OpenGL Image Library\src;C:\GraphicsResources\lib\CommonOpenGL\Simple OpenGL Image Library\lib;C:\GraphicsResources\lib\CommonOpenGL\lib;$(LibraryPath)<sup>4</sup>

Once configured, press Apply<sup>6</sup>

*: This is an example path refer to Notes section for more details

![5.1.png](https://i.postimg.cc/L5Rnp0s1/5-1.png)

  Your Visual Studio Community Edition environment should be ready to use.
	
### Notes

*: You should move CommonOpenGL to a easily accessable location, for instance, create
  a folder at the root of your drive for graphics resources and another inside 
  there for libraries. Place CommonOpenGL inside the libraries folder, so that,
  in this scenario, the path to the OpenGL libraries reads as follows:

C:\GraphicsResources\lib\CommonOpenGL\
