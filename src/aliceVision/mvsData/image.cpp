// This file is part of the AliceVision project.
// Copyright (c) 2017 AliceVision contributors.
// This Source Code Form is subject to the terms of the Mozilla Public License,
// v. 2.0. If a copy of the MPL was not distributed with this file,
// You can obtain one at https://mozilla.org/MPL/2.0/.

#include "image.hpp"

#include  <boost/algorithm/string/case_conv.hpp>

#include <iostream>
#include <algorithm>
#include <stdexcept>

#include <array>


namespace aliceVision {

std::string EImageFileType_informations()
{
  return "Image file type :\n"
         "* jpg \n"
         "* png \n"
         "* tif \n"
         "* exr (half)";
}

EImageFileType EImageFileType_stringToEnum(const std::string& imageFileType)
{
  std::string type = imageFileType;
  std::transform(type.begin(), type.end(), type.begin(), ::tolower); //tolower

  if(type == "jpg" || type == "jpeg") return EImageFileType::JPEG;
  if(type == "png")                   return EImageFileType::PNG;
  if(type == "tif" || type == "tiff") return EImageFileType::TIFF;
  if(type == "exr")                   return EImageFileType::EXR;

  throw std::out_of_range("Invalid image file type : " + imageFileType);
}

std::string EImageFileType_enumToString(const EImageFileType imageFileType)
{
  switch(imageFileType)
  {
    case EImageFileType::JPEG:  return "jpg";
    case EImageFileType::PNG:   return "png";
    case EImageFileType::TIFF:  return "tif";
    case EImageFileType::EXR:   return "exr";
  }
  throw std::out_of_range("Invalid EImageType enum");
}

std::ostream& operator<<(std::ostream& os, EImageFileType imageFileType)
{
  return os << EImageFileType_enumToString(imageFileType);
}

std::istream& operator>>(std::istream& in, EImageFileType& imageFileType)
{
  std::string token;
  in >> token;
  imageFileType = EImageFileType_stringToEnum(token);
  return in;
}

bool isSupportedUndistortFormat(const std::string &ext)
{
  static const std::array<std::string, 6> supportedExtensions = {".jpg", ".jpeg", ".png",  ".tif", ".tiff", ".exr"};
  const auto start = supportedExtensions.begin();
  const auto end = supportedExtensions.end();
  return(std::find(start, end, boost::to_lower_copy(ext)) != end);
}

} // namespace aliceVision
