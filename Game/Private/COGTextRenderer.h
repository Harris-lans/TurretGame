#pragma once
#include "COGShape.h"
#include <string>

class COGTextRenderer : public COGShape
{
public:
	COGTextRenderer(exEngineInterface* pEngine, GameObject* pGameObject, float fFontSize, exColor& fontColor);
	~COGTextRenderer();

	virtual void Render() override;
	virtual ComponentType GetType() const override;
	std::string& GetText();
	void SetText(std::string);

private:
	std::string				mText;
	int						mFontID;
};