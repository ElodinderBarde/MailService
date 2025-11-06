#pragma once
namespace Messerli
{
class Functions
{
  public:
    int passingCounter = 0;
    static void WaitABit();
    static void WaitABitLonger();
    static void InitializeApp();
    static void SetCursorPosition(int x, int y);
};
}
