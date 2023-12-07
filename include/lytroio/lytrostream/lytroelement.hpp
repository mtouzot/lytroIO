// Copyright (c) 2023-present, Martin TOUZOT & LytroIO contributors.
// Distributed under the GPL-3.0 Licence
// (https://opensource.org/license/gpl-3-0/)
/** \file include/lytrioio/lytrostream/lytroelement.hpp
 *
 *  \brief Implementation of a component of a Lytro files (.LPF or .LFR
 * formats)
 *
 * Once opened, Lytro files let appear different elements. This class describes
 * each of them as they follow the same structure with a version number, the
 * data lenght, a sha-1 and the data.
 *
 */
#pragma once

//
// Lytro file element

#ifndef LYTROELEMENT_H
#define LYTROELEMENT_H

#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace lytroio
{
class LytroElement
{
public:
  enum LytroElementType : int8_t
  {
    NUL = -1,
    LFM = 3,
    LFC = 5,
    LFP = 6
  };

  /**
   * @brief Construct a new LytroElement object
   *
   */
  LytroElement () = default;

  /**
   * @brief Construct a new LytroElement object of a certain type
   *
   * @param type type of the LytroElement object
   */
  LytroElement (enum LytroElement::LytroElementType type);

  /**
   * @brief Destroy the LytroElement object
   *
   */
  ~LytroElement ();

  /**
   * @brief Getter of the current LytroElement object type
   *
   * @return const char *
   */
  const char *type () const;

  /**
   * @brief Getter of the current LytroElement object version
   *
   * @return const int
   */
  const int version () const;

  /**
   * @brief Getter of the current LytroElement object length
   *
   * @return const int
   */
  const int length () const;

  /**
   * @brief Getter of the current LytroElement object sha
   *
   * @return const std::string
   */
  const std::string sha () const;

  /**
   * @brief Getter of the current LytroElement object data
   *
   * @return const std::string
   */
  const std::string data () const;

  /**
   * @brief Getter of the current LytroElement object filepath
   *
   * @return const std::filesystem::path
   */
  const std::filesystem::path filepath () const;

  /**
   * @brief Getter of the current LytroElement object parent filepath
   *
   * @return const std::filesystem::path
   */
  const std::filesystem::path parent_filepath () const;

  /**
   * @brief Set the type of the current LytroElement object
   *
   * @param type type of the LytroElement object
   */
  void set_type (enum LytroElement::LytroElementType type);

  /**
   * @brief Set the version of the current LytroElement object
   *
   * @param version a version number
   */
  void set_version (int &version);

  /**
   * @brief Set the length of the current LytroElement object
   *
   * @param length a lenght
   */
  void set_length (int &length);

  /**
   * @brief Set the sha of the current LytroElement object
   *
   * @param sha a sha
   */
  void set_sha (std::string sha);

  /**
   * @brief Set the data of the current LytroElement object
   *
   * @param data a data
   */
  void set_data (std::string data);

  /**
   * @brief Set the filepath of the current LytroElement object
   *
   * @param filepath a filepath
   */
  void set_filepath (std::filesystem::path filepath);

  /**
   * @brief Set the parent filepath of the current LytroElement object
   *
   * @param parent_filepath a parent_filepath
   */
  void set_parent_filepath (std::filesystem::path parent_filepath);

  /**
   * @brief Check if current LytroElement is empty ie. length == 0
   *
   * @return true Current LytroElement contains no data
   * @return false Current LytroElement contains data
   */
  bool empty ();

  /**
   * @brief Save current LytroElement data to LytroElement filepath
   */
  void save ();

  /**
   * @brief Override operator << to format LytroElement display
   *
   * @param os output stream
   * @param element LytroElement to display
   */
  friend std::ostream &operator<< (std::ostream &os,
                                   const LytroElement &element);

private:
  LytroElementType type_ = NUL;
  int version_ = -1;
  int length_ = -1;
  std::string sha_ = "";
  std::string data_ = "";
  std::filesystem::path filepath_ = "";
  std::filesystem::path parent_filepath_ = "";
};

} // namespace lytroio

#endif // LYTROELEMENT_H