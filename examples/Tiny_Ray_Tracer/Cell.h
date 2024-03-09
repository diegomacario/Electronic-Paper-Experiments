#ifndef CELL_H
#define CELL_H

#include <string>

class Cell
{
public:

   Cell(int32_t xPos, int32_t yPos, std::string text, int32_t textXPos, int32_t testYPos);
   ~Cell() = default;

   int32_t mXPos;
   int32_t mYPos;
   std::string mText;
   int32_t mTextXPos;
   int32_t mTextYPos;
};

#endif
