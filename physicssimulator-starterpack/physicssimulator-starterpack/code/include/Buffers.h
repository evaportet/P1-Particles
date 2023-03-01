#pragma once

namespace graphics {
	class VertexBuffer {
	private:
		unsigned int m_RendererId;
	public:
		VertexBuffer(const void* data, unsigned int size, bool dynamic);
		~VertexBuffer();

		void Bind() const;
		void Unbind() const;

		float* MapWriteOnly() const;
		void Unmap() const;
	};

	template <class T>
	class IndexBuffer {
	private:
		unsigned int m_RendererId;
		unsigned int m_Count;
	public:
		IndexBuffer(const T* data, unsigned int count, bool dynamic);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

		inline unsigned int GetCount() const { return m_Count; }
	};
}