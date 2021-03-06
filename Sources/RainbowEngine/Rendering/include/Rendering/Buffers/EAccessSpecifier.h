#pragma once

namespace Rendering::Buffers
{
	/**
	* Defines some access hints that buffers can use
	* ���ݴ洢��Ԥ��ʹ��ģʽ
	* STATIC �����ݲ���򼸺�����ı䡣
	* DYNAMIC�����ݻᱻ�ı�ܶࡣ
	* STREAM������ÿ�λ���ʱ����ı䡣
	* #define GL_STREAM_DRAW 0x88E0
	* #define GL_STREAM_READ 0x88E1
	* #define GL_STREAM_COPY 0x88E2
	* #define GL_STATIC_DRAW 0x88E4
	* #define GL_STATIC_READ 0x88E5
	* #define GL_STATIC_COPY 0x88E6
	* #define GL_DYNAMIC_DRAW 0x88E8
	* #define GL_DYNAMIC_READ 0x88E9
	* #define GL_DYNAMIC_COPY 0x88EA
	*/
	enum class EAccessSpecifier
	{
		STREAM_DRAW		= 0x88E0,
		STREAM_READ		= 0x88E1,
		STREAM_COPY		= 0x88E2,
		DYNAMIC_DRAW	= 0x88E8,
		DYNAMIC_READ	= 0x88E9,
		DYNAMIC_COPY	= 0x88EA,
		STATIC_DRAW		= 0x88E4,
		STATIC_READ		= 0x88E5,
		STATIC_COPY		= 0x88E6
	};
}