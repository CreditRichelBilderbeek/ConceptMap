//---------------------------------------------------------------------------
/*
ConceptMap, concept map classes
Copyright (C) 2013-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppConceptMap.htm
//---------------------------------------------------------------------------
#include "conceptmapcompetencies.h"

#include <cassert>
#include <stdexcept>


ribi::cmap::Competencies::Competencies()
  : m_map_dutch{}, //Lazy initialization
    m_map_english{} //Lazy initialization
{

}

boost::bimap<ribi::cmap::Competency,std::string>
ribi::cmap::CreateMapEnglish() noexcept
{

  boost::bimap<Competency,std::string> m;
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::uninitialized,"uninitialized"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::profession,"profession"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::organisations,"organisations"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::social_surroundings,"social_surroundings"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::target_audience,"target_audience"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::ti_knowledge,"ti_knowledge"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::prof_growth,"prof_growth"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::misc,"misc"));
  assert(m.left.size() == static_cast<int>(Competency::n_competencies));
  return m;
}

boost::bimap<ribi::cmap::Competency,std::string>
ribi::cmap::CreateMapDutch() noexcept
{
  boost::bimap<Competency,std::string> m;
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::uninitialized,"[Ongeinitialiseerd]"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::profession,"Kennis van het beroepsdomein"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::organisations,"Kennis van de organisatie"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::social_surroundings,"Kennis van de sociale omgeving"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::target_audience,"Kennis van de doelgroep"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::ti_knowledge,"Technisch instrumentele kennis"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::prof_growth,"Kennis van de eigen persoon"));
  m.insert(boost::bimap<Competency,std::string>::value_type(
    Competency::misc,"Overige"));
  assert(m.left.size() == static_cast<int>(Competency::n_competencies));
  return m;
}

std::vector<ribi::cmap::Competency> ribi::cmap::Competencies::GetAllCompetencies() const noexcept
{
  const std::vector<Competency> v {
    ribi::cmap::Competency::uninitialized,
    ribi::cmap::Competency::profession,
    ribi::cmap::Competency::organisations,
    ribi::cmap::Competency::social_surroundings,
    ribi::cmap::Competency::target_audience,
    ribi::cmap::Competency::ti_knowledge,
    ribi::cmap::Competency::prof_growth,
    ribi::cmap::Competency::misc
  };
  assert(static_cast<int>(v.size()) == static_cast<int>(Competency::n_competencies));
  return v;
}



int ribi::cmap::Competencies::ToIndex(const Competency competency) const noexcept
{
  return static_cast<int>(competency);
}

std::string ribi::cmap::Competencies::ToStr(const Competency type) const noexcept
{
  if (m_map_english.left.empty()) m_map_english = CreateMapEnglish();
  assert(!m_map_english.left.empty());
  assert(m_map_english.left.count(type) == 1);
  const std::string s = m_map_english.left.find(type)->second;
  return s;
}

std::string ribi::cmap::Competencies::ToStrDutch(const Competency type) const noexcept
{
  if (m_map_dutch.left.empty()) m_map_dutch = CreateMapDutch();
  assert(!m_map_dutch.left.empty());
  assert(m_map_dutch.left.count(type) == 1);
  const std::string s = m_map_dutch.left.find(type)->second;
  return s;
}

ribi::cmap::Competency ribi::cmap::Competencies::ToType(const std::string& s) const
{
  if (m_map_english.right.empty()) m_map_english = CreateMapEnglish();
  assert(!m_map_english.right.empty());
  if (m_map_english.right.count(s) == 0)
  {
    std::stringstream msg;
    msg << __func__
      << ": cannot find competency '"
      << s << "' in English dictionary"
    ;
    throw std::logic_error(msg.str());
  }
  assert(m_map_english.right.count(s) == 1);
  return m_map_english.right.find(s)->second;
}

ribi::cmap::Competency ribi::cmap::Competencies::ToTypeFromDutch(const std::string& s) const
{
  if (m_map_dutch.right.empty()) m_map_dutch = CreateMapDutch();
  assert(!m_map_dutch.right.empty());
  if (m_map_dutch.right.count(s) == 0)
  {
    std::stringstream msg;
    msg << __func__
      << ": cannot find competency '"
      << s << "' in Dutch dictionary"
    ;
    throw std::logic_error(msg.str());
  }
  assert(m_map_dutch.right.count(s) == 1);
  return m_map_dutch.right.find(s)->second;
}
