#include "drawframeworks.h"


namespace DrawFrame
{

	DrawFrameWork::DrawFrameWork()
	{
	}

	// to use a basic framework to assign the VBOs instead of the object doing it.
		void DrawFrameWork::setVBOs(float fvData[], float fnData[], float ftData[],
		float size, unsigned int handle[], int indicies[], unsigned int IndiciesSize)
	{

		gl::GenVertexArrays(1, &vaoHandle);
		gl::BindVertexArray(vaoHandle);

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fvData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(0);  // Vertex position

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fnData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);  // Vertex normal

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, size, ftData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(2);  // texture coords

		gl::BindBuffer(gl::ELEMENT_ARRAY_BUFFER, handle[3]);
		gl::BufferData(gl::ELEMENT_ARRAY_BUFFER, IndiciesSize, indicies, gl::STATIC_DRAW);

	}
	// without indicies
		void DrawFrameWork::setVBOs(float fvData[], float fnData[], float ftData[],
		float size, unsigned int handle[])
	{

		gl::GenVertexArrays(1, &vaoHandle);
		gl::BindVertexArray(vaoHandle);

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[0]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fvData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)0, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(0);  // Vertex position

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[1]);
		gl::BufferData(gl::ARRAY_BUFFER, size, fnData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)1, 3, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(1);  // Vertex normal

		gl::BindBuffer(gl::ARRAY_BUFFER, handle[2]);
		gl::BufferData(gl::ARRAY_BUFFER, size, ftData, gl::STATIC_DRAW);
		gl::VertexAttribPointer((GLuint)2, 2, gl::FLOAT, FALSE, 0, ((GLubyte *)NULL + (0)));
		gl::EnableVertexAttribArray(2);  // texture coords


	}


		void DrawFrameWork::render(unsigned int VAO, unsigned int DrawCount, bool indicies)
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

		
	 void DrawFrameWork::CompileAndLinkShader()
	{

		try {
			prog.compileShader("Shaders/diffuse.vert");
			prog.compileShader("Shaders/diffuse.frag");
			prog.link();
			prog.validate();
			prog.use();
		}
		catch (GLSLProgramException & e) {
			std::cerr << e.what() << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	 void DrawFrameWork::setLightParams(vec3 CamPos, vec3 WorldLight)
	 {


		 vec3 worldLight = WorldLight;

		 prog.setUniform("Ld", 1.0f, 1.0f, 1.0f); // diffuse light intentsity
		 prog.setUniform("La", 0.5f, 0.5f, 0.5f); // ambient light intentsity
		 prog.setUniform("n", 30.f); // specular exponent
		 prog.setUniform("Al", 0.0001f); // light attenuation		
		 prog.setUniform("LightPosition", worldLight);
		 prog.setUniform(("CameraPos"), CamPos);

	 }

	 void DrawFrameWork::clearBits()
	 {
		 gl::Clear(gl::COLOR_BUFFER_BIT | gl::DEPTH_BUFFER_BIT);
	 }
}