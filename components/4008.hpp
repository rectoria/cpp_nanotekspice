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

class Component_4008 : public nts::IComponent {
	public:
		Component_4008();
		~Component_4008() = default;

		nts::Tristate compute(std::size_t = 1) final;
		void setLink(std::size_t, nts::IComponent &, std::size_t) final;
		nts::Tristate &getPin(std::size_t) final;
		void dump() const final {};
	protected:
	private:
		std::vector<std::tuple<nts::Tristate *, IComponent *>> _inPins;
		std::vector<nts::Tristate> _outPins;
		std::vector<int> _prohibedPins;
		std::vector<int> _computablePins;
		std::map<int, std::vector<int>> _pair;
		std::vector<nts::IComponent *> dependencies;
};