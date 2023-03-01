#include "Buffers.h"
#include <GL/glew.h>

namespace graphics {
	VertexBuffer::VertexBuffer(const void* data, unsigned int size, bool dynamic) {
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ARRAY_BUFFER, size, data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer() {
		glDeleteBuffers(1, &m_RendererId);
	}

	void VertexBuffer::Bind() const {
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}

	void VertexBuffer::Unbind() const {
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	float* VertexBuffer::MapWriteOnly() const {
		this->Bind();
		return (float*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}

	void VertexBuffer::Unmap() const {
		glUnmapBuffer(GL_ARRAY_BUFFER);
	}

	template <class T>
	IndexBuffer<T>::IndexBuffer(const T* data, unsigned int count, bool dynamic) : m_Count(count) {
		glGenBuffers(1, &m_RendererId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(T), data, dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	}

	template <class T>
	IndexBuffer<T>::~IndexBuffer() {
		glDeleteBuffers(1, &m_RendererId);
	}

	template <class T>
	void IndexBuffer<T>::Bind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererId);
	}

	template <class T>
	void IndexBuffer<T>::Unbind() const {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	// Explicitly define specializations
	template class IndexBuffer<GLubyte>;
}