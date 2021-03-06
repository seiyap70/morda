#pragma once

#include <functional>

#include "../core/Widget.hpp"



namespace morda{



/**
 * @brief Basic button widget class.
 * Button has two states: normal and pressed.
 */
class Button : public virtual Widget{
	bool isPressed_v = false;
	
protected:
	Button() :
			Widget(nullptr)
	{}
	
	/**
	 * @brief Called when button pressed state changes.
	 * Default implementation emits the 'pressedChanged' signal.
	 */
	virtual void onPressedChanged(){
		if(this->pressedChanged){
			this->pressedChanged(*this);
		}
	}
	
	bool onMouseButton(bool isDown, const morda::Vec2r& pos, MouseButton_e button, unsigned pointerId) override;
	
	void onHoverChanged(unsigned pointerID) override;
public:	
	
	/**
	 * @brief Check if button is currently pressed.
	 * @return true if button is pressed.
	 * @return false otherwise.
	 */
	bool isPressed()const noexcept{
		return this->isPressed_v;
	}
	
	/**
	 * @brief Pressed changed signal.
	 * Emitted when button pressed satte changes.
	 */
	std::function<void(Button&)> pressedChanged;
};


/**
 * @brief Basic class of a push button.
 * Push button is a button which can be clicked.
 * Clicked means that the button was pressed and then released.
 */
class PushButton : public Button{
	bool currentlyPressed = false;

protected:
	void onPressedChanged()override;
	
	/**
	 * @brief Invoked when the button is clicked.
	 * Default implementation emits 'clicked' signal.
	 */
	virtual void onClicked(){
		if(this->clicked){
			this->clicked(*this);
		}
	}
	
	PushButton() :
			Widget(nullptr)
	{}
	
public:
	/**
	 * @brief Clicked signal.
	 * Emitted when the button is clicked.
	 */
	std::function<void(PushButton&)> clicked;
};


/**
 * @brief Basic class of a toggle button.
 * Toggle button is a button which can be checked and unchecked.
 * In GUI script it has the 'checked{true/false}' attribute which can set initial
 * checked state of the widget.
 */
class ToggleButton : public PushButton{
	bool isChecked_v;
	
	void onClicked()override{
		this->toggle();
	}
protected:
	ToggleButton(const stob::Node* chain);
	
	/**
	 * @brief Invoked when button checked state changes.
	 * Default implementation emits 'checkedChanged' signal.
	 */
	virtual void onCheckedChanged(){
		if(this->checkedChanged){
			this->checkedChanged(*this, this->isChecked());
		}
	}
public:

	/**
	 * @brief Set checked state.
	 * If checked state changes as a result of this function call it will also
	 * invoke onCheckedChanged().
	 * @param checked - whether the new state should be set to checked (true) or unchecked (false).
	 */
	void setChecked(bool checked){
		if(this->isChecked_v == checked){
			return;
		}
		
		this->isChecked_v = checked;
		this->onCheckedChanged();
	}
	
	/**
	 * @brief Change checked state to opposite.
	 */
	void toggle(){
		this->setChecked(!this->isChecked());
	}
	
	/**
	 * @brief Tell if the button is checked or not.
	 * @return true if the button is checked.
	 * @return false otherwise.
	 */
	bool isChecked()const noexcept{
		return this->isChecked_v;
	}
	
	/**
	 * @brief Checked changed signal.
	 * Emitted when checked state changes.
	 */
	std::function<void(ToggleButton&, bool)> checkedChanged;
};



}
