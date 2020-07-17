#include <Ongine.h>
#include <Ongine\GLErr.h>

class Sandbox : public ON::Application {
public:
	ON::OpenGLShader shader;
	ON::OpenGLIndexBuffer EBO;
	ON::OpenGLVertexBuffer VBO;
	ON::OpenGLVertexArray VAO;
	ON::OpenGLRenderer renderer;

	float vertices[12] = {
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};
	unsigned int indices[6] = {
		0, 1, 3,
		1, 2, 3
	};
	virtual void OnRun() override {
		shader.Create({ "res/sysshaders/vs.shader", "res/sysshaders/fs.shader" });

		std::vector<ON::Attributte> dest;
		dest.push_back({ 0, 3, 0, 3 });

		ON::BufferLayout layout = { dest };

		VAO.Create();
		VBO.Create({vertices, sizeof(vertices)}, layout);
		EBO.Create({ indices, sizeof(indices) });

		VAO.Bind();

		EBO.LinkAttributes();

		VBO.LinkAttributes();

		VBO.Unbind();
		VAO.Unbind();
	}
	virtual void OnUpdate(ON::Input& input) override {

	}
	virtual void OnRender() override {
		renderer.DrawIndexed( { (sizeof(indices) / sizeof(indices[0])), EBO, VAO, shader });
	}
};

ON::Application* ON::CreateApplication() {
	return new Sandbox();
}