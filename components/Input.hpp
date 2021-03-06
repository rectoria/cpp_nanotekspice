/*
** EPITECH PROJECT, 2018
** TekSpice
** File description:
** oui
*/

#pragma once

#include <vector>
#include <map>
#include "../IComponent.hpp"
#include "../Logic.hpp"

class Component_Input : public nts::IComponent {
	public:
		Component_Input();
		~Component_Input() = default;

		nts::Tristate compute(std::size_t = 1) final;
		void setLink(std::size_t, nts::IComponent &, std::size_t) final;
		nts::Tristate &getPin(std::size_t) final;
		void dump() const final;
		nts::C_TYPE getType() { return nts::C_INPUT; }
	protected:
	private:
		std::vector<nts::Tristate *> _inPins;
		std::vector<nts::Tristate> _outPins;
};
