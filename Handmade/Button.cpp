#include "Button.h"
#include "Input.h"

Button::Button(const SDL_Point& position,
	const SDL_Point& dimension,
	const SDL_Rect& textureDimension,
	const std::string& filename,
	bool hasClickState,
	int rowIndex) : m_rowIndex(rowIndex), m_hasClickState(hasClickState)
{
	m_texture.Load(filename, filename);
	m_texture.SetDimension(dimension.x, dimension.y);
	m_texture.SetSourceDimension(textureDimension.x,
		textureDimension.y,
		textureDimension.w,
		textureDimension.h);
	m_texture.SetTexture(filename);

	m_position = position;
	m_dimension = dimension;
	m_collider = { position.x, position.y, dimension.x, dimension.y };
}

void Button::Update(int deltaTime)
{
	auto mousePosition = Input::Instance()->GetMousePosition();
	auto isMouseClicked = Input::Instance()->IsMouseClicked(HM_MOUSE_LEFT);

	if (SDL_PointInRect(&mousePosition, &m_collider))
	{
		if (isMouseClicked && m_hasClickState)
		{
			m_state = State::Clicked;
		}

		else
		{
			m_state = State::Hover;
		}
	}

	else
	{
		m_state = State::Default;
	}
}

bool Button::Render()
{
	m_texture.SetCel(static_cast<int>(m_state), m_rowIndex);
	m_texture.Render(m_position.x, m_position.y);
	return true;
}