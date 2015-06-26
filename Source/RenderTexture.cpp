#include "RenderTexture.h"
#include "loadgen/gl_core_4_4.h"
#include <iostream>

RenderTexture::RenderTexture() : fboID(0), fboDepth(0) 
{
}

RenderTexture::RenderTexture(int height, int width) : fboID(0), fboDepth(0)
{
	this->width = width;
	this->height = height;

	glGenFramebuffers(1, &fboID);
	glBindBuffer(GL_FRAMEBUFFER, fboID);

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, width, height);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureID, 0);

	glGenRenderbuffers(1, &fboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, fboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fboDepth);

	GLenum drawBuffers[] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, drawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer" << std::endl;

	glBindBuffer(GL_FRAMEBUFFER, 0);
}

RenderTexture::~RenderTexture()
{

}
