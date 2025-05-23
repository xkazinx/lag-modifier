#include <iostream>
#include <Windows.h>
#include <random>
#include <vector>

#pragma comment(lib, "Winmm.lib")

int GenRandom(int from, int to)
{
    static std::random_device rd;  // Obtain a random seed from the system
    static std::mt19937 gen(rd()); // Initialize the Mersenne Twister generator

    std::uniform_int_distribution<int> dist(from, to); // Define a range [1, 100]

    int random_number = dist(gen); // Generate a random number
    return random_number;
}

std::vector<DWORD> vks =
{
   VK_NUMPAD0,
   VK_NUMPAD1,
   VK_NUMPAD2,
   VK_NUMPAD3,
   VK_NUMPAD4,
   VK_NUMPAD5,
   VK_NUMPAD6,
   VK_NUMPAD7,
   VK_NUMPAD8,
   VK_NUMPAD9,
};

bool IsKeyPressed(DWORD vk)
{
   return GetAsyncKeyState(vk) & 0x8000;
}

void pressKey(DWORD vk) {
    INPUT input = {0};
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = vk; // Backspace key

       // Press Backspace
        SendInput(1, &input, sizeof(INPUT));

        // Release Backspace
        input.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &input, sizeof(INPUT));

        // Reset flag for next iteration
        input.ki.dwFlags = 0;
    
}


int main()
{
   DWORD change_tm = timeGetTime();

   while(true)
   {
      if (IsKeyPressed(VK_ESCAPE))
         break;

      std::cout << "Waiting" << std::endl;
      Sleep(100);
   }

   Sleep(1000);

    while (true) {
       if (IsKeyPressed(VK_ESCAPE))
          break;
       
          //std::cout << vks[GenRandom(1, 9)] << std::endl;
       if (timeGetTime() > change_tm + 500)
       {
          pressKey(VK_BACK);
          pressKey(VK_BACK);
          pressKey(VK_BACK);
          std::cout << vks[GenRandom(1, 9)] << std::endl;
          pressKey(vks[GenRandom(1, 2)]);
          pressKey(vks[GenRandom(1, 9)]);
          pressKey(vks[GenRandom(1, 9)]);

          change_tm = timeGetTime();
       }

       Sleep(100);
    }
}
