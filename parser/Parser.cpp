/*
** EPITECH PROJECT, 2021
** cpp_nanotekspice
** File description:
** Created by rectoria
*/

#include <fstream>
#include <iostream>
#include "../TekSpice.hpp"
#include "Parser.hpp"

Parser::Parser() = default;

Parser::~Parser() = default;

std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &Parser::get_links(
	std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &components,
	std::ifstream &file
)
{
	std::string line;
	std::string component1;
	std::string component2;
	size_t pin1;
	size_t pin2;
	unsigned i = 0;

	getline(file, line);

	if ((line.empty() && !file.eof()) || line[0] == '#')
		return get_links(components, file);
	else if (line.empty() && file.eof())
		return components;
	i = (unsigned)line.find_first_not_of(" \t", i);
	for (unsigned long iter = line.find(':', i); iter > i; i++)
		component1 += line[i];
	i += 1;
	pin1 = static_cast<size_t>(std::stoi(
		line.substr(i, line.find_first_of(" \t\n", i) - i)));
	i = (unsigned)line.find_first_of(" \t", i);
	i = (unsigned)line.find_first_not_of(" \t", i);
	for (unsigned long iter = line.find(':', i); iter > i; i++)
		component2 += line[i];
	i += 1;
	pin2 = static_cast<size_t>(std::stoi(
		line.substr(i, line.find_first_of(" \t\n", i) - i)));
	if (components.count(component1) && components.count(component2))
		components[component2]->setLink(pin2, *components[component1], pin1);
	if (file.eof())
		return components;
	return get_links(components, file);
}

std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &Parser::get_chipset(
	std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> &components,
	std::ifstream &file
)
{
	std::string line;
	std::string name;
	std::string type;
	TekSpice t;
	unsigned i = 0;

	getline(file, line);

	if (line == ".links:")
		return get_links(components, file);
	else if (line[0] == '#' || line.empty())
		return get_chipset(components, file);
	i = (unsigned)line.find_first_not_of(" \t", i);
	for (unsigned j = i; j < line.length() && line[j] != ' ' &&
		line[j] != '\t'; j++, i++)
		type += line[j];
	i = (unsigned)line.find_first_not_of(" \t", i);
	for (; i < line.length() && line[i] != ' ' && line[i] != '\t'; i++)
		name += line[i];
	components[name] = t.createComponent(type, name);
	return (get_chipset(components, file));
}

std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> Parser::parse_file(
	std::string const &filename
)
{
	std::unordered_map<std::string, std::shared_ptr<nts::IComponent>> components;
	std::ifstream file(filename);
	std::string line;

	if (!file.is_open())
		throw std::runtime_error("Can't open '" + filename + "'\n");
	for (; getline(file, line) && line != ".chipsets:";);
	components = get_chipset(components, file);
	return components;
}
