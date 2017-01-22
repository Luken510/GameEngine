#include "stdafx.h"


using namespace DrawFrame;


	DrawFrameWork::DrawFrameWork()
	{
	}

	// to use a basic framework to assign the VBOs instead of the object doing it.
		void DrawFrameWork::setVBOs(GLfloat fvData[],
		GLuint size, GLuint handle[], GLfloat indicies[], GLuint IndiciesSize, GLuint vaoHandle)
	{

		gl::GenVertexArrays(1, &vaoHandle);
		gl::BindVertexArray(vaoHandle);

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fvData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(0);  // Vertex position

		/*gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fnData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));  if needed surface normals
		gl::EnableVertexAttribArray(1);  // Vertex normal

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, size, ftData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0))); // if needed texture co-ords
		gl::EnableVertexAttribArray(2);  // texture coords*/

		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, handle[3]);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, IndiciesSize, indicies, gl::STATIC_DRAW);

	}
	// without indicies
		void DrawFrameWork::setVBOs(GLfloat fvData[], GLfloat fnData[], GLuint size, GLuint vboHandle[], GLuint vaoHandle)
	{

		

		gl::GenVertexArrays(1, &vaoHandle);
		gl::BindVertexArray(vaoHandle);

		gl::GenBuffers(2, vboHandle);

		gl::BindBuffer(gl::ARRAY_BUFFER, vboHandle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fvData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(0);  // Vertex position

		gl::BindBuffer(gl::ARRAY_BUFFER, vboHandle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fnData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);  // Vertex normal

	/*	gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, size, ftData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(2);  // texture coords*/


	}


		void DrawFrameWork::render(GLuint DrawCount, bool indicies, GLuint vaoHandle)
	{

			gl::Clear(gl::COLOR_BUFFER_BIT);

		gl::BindVertexArray(vaoHandle);
		if (indicies == 1) 
			gl::DrawElements(gl::TRIANGLES, DrawCount, gl::UNSIGNED_INT, ((void*)0));
		else 
			gl::DrawArrays(gl::TRIANGLES, 0, DrawCount);
	}

	 void DrawFrameWork::EnableDepth()
	{
		gl::Enable(gl::DEPTH_TEST);
	}

	 void DrawFrameWork::setLightParams(vec3 CamPos, vec3 WorldLight,
		 float AmbIntensity, float DiffIntensity, float SpecularIntensity)
	 {

		 prog.setUniform("Ld", DiffIntensity, DiffIntensity, DiffIntensity); // diffuse light intentsity
		 prog.setUniform("La", AmbIntensity, AmbIntensity, AmbIntensity); // ambient light intentsity
		 prog.setUniform("n", SpecularIntensity); // specular exponent
		 prog.setUniform("Al", 0.0001f); // light attenuation		
		 prog.setUniform("LightPosition", WorldLight);
		 prog.setUniform(("CameraPos"), CamPos);

	 }

	 void DrawFrameWork::clearBits()
	 {
		 gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	 }

	 void DrawFrameWork::setReflectivity(vec3 ambientReflect, vec3 diffuseReflect, vec3 specularReflect)
	 {
		 prog.setUniform("Kd", diffuseReflect); // diffuse light
		 prog.setUniform("Ka", ambientReflect); // ambient light
		 prog.setUniform("Ks", specularReflect); // specular light

	 }

	 void DrawFrameWork::setMatricies(glm::mat3 NormalMatrix, glm::mat4 model, glm::mat4 view, glm::mat4 proj)
	 {
		
		 prog.setUniform("NormalMatrix", NormalMatrix);
		 prog.setUniform("M", model);
		 prog.setUniform("V", view);
		 prog.setUniform("P", proj);

	 }

	 void DrawFrameWork::setViewPort(GLint x, GLint y, GLint width, GLint height)
	 {
		 gl::Viewport(x, y, width, height);
	 }

	 DrawFrameWork::~DrawFrameWork()
	 {
		 // TO DO : Implement this to destroy all Vbos and Vaos
	 }