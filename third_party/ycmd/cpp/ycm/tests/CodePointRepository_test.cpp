// Copyright (C) 2018 ycmd contributors
//
// This file is part of ycmd.
//
// ycmd is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// ycmd is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with ycmd.  If not, see <http://www.gnu.org/licenses/>.

#include "CodePoint.h"
#include "Repository.h"
#include "TestUtils.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::Pointee;
using ::testing::UnorderedElementsAre;

namespace YouCompleteMe {

class CodePointRepositoryTest : public ::testing::Test {
protected:
  CodePointRepositoryTest()
    : repo_( Repository< CodePoint >::Instance() ) {
  }

  virtual void SetUp() {
    repo_.ClearElements();
  }

  Repository< CodePoint > &repo_;
};


TEST_F( CodePointRepositoryTest, GetCodePoints ) {
  CodePointSequence code_point_objects = repo_.GetElements( { "α", "ω" } );

  EXPECT_THAT( repo_.NumStoredElements(), 2 );
  EXPECT_THAT( code_point_objects, UnorderedElementsAre(
    Pointee( IsCodePointWithProperties< CodePointTuple >(
      { "α", "α", "Α", true, false, false, GraphemeBreakProperty::OTHER } ) ),
    Pointee( IsCodePointWithProperties< CodePointTuple >(
      { "ω", "ω", "Ω", true, false, false, GraphemeBreakProperty::OTHER } ) )
  ) );
}

} // namespace YouCompleteMe
