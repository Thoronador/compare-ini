/*
 -------------------------------------------------------------------------------
    This file is part of the compare-ini tool.
    Copyright (C) 2014  Thoronador

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 -------------------------------------------------------------------------------
*/

#include "IniSection.hpp"
#include "EntryNotFoundException.hpp"

IniSection::IniSection()
: m_Values(std::map<std::string, std::string>())
{
}

void IniSection::addValue(const std::string& name, const std::string& value)
{
  m_Values[name] = value;
}

bool IniSection::hasValue(const std::string& name) const
{
  return (m_Values.find(name) != m_Values.end());
}

const std::string& IniSection::getValue(const std::string& name) const
{
  const std::map<std::string, std::string>::const_iterator iter =
          m_Values.find(name);
  if (iter!=m_Values.end())
    return iter->second;
  throw EntryNotFoundException(name);
}

std::vector<std::string> IniSection::getValueNames() const
{
  std::vector<std::string> result;
  std::map<std::string, std::string>::const_iterator iter =
          m_Values.begin();
  while (iter!=m_Values.end())
  {
    result.push_back(iter->first);
    ++iter;
  } //while
  return result;
}

void IniSection::clear()
{
  m_Values.clear();
}

bool IniSection::hasSameValues(const IniSection& other) const
{
  std::vector<std::string> otherNames = other.getValueNames();
  if (otherNames.size()!=m_Values.size())
    return false;
  std::map<std::string, std::string>::const_iterator iter =
          m_Values.begin();
  while (iter!=m_Values.end())
  {
    if (!other.hasValue(iter->first))
      return false;
    if (other.getValue(iter->first) != iter->second)
        return false;
    ++iter;
  } //while
  return true;
}

bool IniSection::hasSameKeys(const IniSection& other) const
{
  return (getValueNames()==other.getValueNames());
}
