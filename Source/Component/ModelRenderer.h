#pragma once
#include "AComponent.h"
class ModelRenderer : public AComponent
{
public:
	ModelRenderer(const char* modelPath);
	virtual ~ModelRenderer();

protected:
	virtual void update(float deltaTime);
};

