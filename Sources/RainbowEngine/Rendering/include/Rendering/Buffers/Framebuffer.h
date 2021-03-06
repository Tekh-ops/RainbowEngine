

#pragma once

#include <vector>

#include "Rendering/Context/Driver.h"

namespace Rendering::Buffers
{
	/**
	* Wraps OpenGL FBO
	* 封装OpenGL的帧缓冲对象
	*/
	class API_RENDERING Framebuffer
	{
	public:

		/**
		* Create the framebuffer
		* 创建一个帧缓存
		* @param p_width
		* @param p_height
		*/
		Framebuffer(uint16_t p_width = 0, uint16_t p_height = 0);

		/**
		* Destructor
		*/
		~Framebuffer();

		/**
		* Bind the framebuffer
		* 绑定帧缓存
		*/
		void Bind();

		/**
		* Unbind the framebuffer
		* 解绑帧缓存
		*/
		void Unbind();

		/**
		* Defines a new size for the framebuffer
		* @param p_width
		* @param p_height
		*/
		void Resize(uint16_t p_width, uint16_t p_height);

		/**
		* Returns the ID of the OpenGL framebuffer
		*/
		uint32_t GetID();

		/**
		* Returns the ID of the OpenGL render texture
		*/
		uint32_t GetTextureID();

		/**
		* Returns the ID of the OpenGL render buffer
		*/
		uint32_t GetRenderBufferID();

	private:

		uint32_t m_bufferID = 0;
		uint32_t m_renderTexture = 0;
		uint32_t m_depthStencilBuffer = 0;
	};
}