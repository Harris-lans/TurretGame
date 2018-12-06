#include "COGTextRenderer.h"

COGTextRenderer::COGTextRenderer(exEngineInterface* pEngine, GameObject* pGameObject, float fFontSize, exColor& fontColor)
	:COGShape(pEngine, pGameObject, fontColor)
{
	mText = "";
	mFontID = mFontID = mEngine->LoadFont("randomFont.ttf", fFontSize);
}

COGTextRenderer::~COGTextRenderer()
{
	Destroy();
	Console::LogString("Deleted Text Renderer Component! \n");
}

ComponentType COGTextRenderer::GetType() const
{
	return ComponentType::TextRenderer;
}

std::string& COGTextRenderer::GetText()
{
	return mText;
}

void COGTextRenderer::SetText(std::string text)
{
	mText = text;
}

void COGTextRenderer::Render()
{
	if (mTransform != nullptr)
	{
		exVector2 position = mTransform->GetPosition();
		const char* textChar = mText.c_str();

		// Drawing the text
		mEngine->DrawText(mFontID, position, textChar, mColor, 3);
	}
}