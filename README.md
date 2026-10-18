# Lag Modifier

A small Windows macro, written in C++, that drives a separate latency-control program, such as a network lag
simulator with a delay field in milliseconds. It types into that program's latency field over and over, so the
latency keeps changing while you test without anyone changing it by hand.

## How it works

The macro does not touch the network itself. It sends keyboard input to whichever window has focus (`SendInput`),
the same as a person typing into the latency control software's delay box:

1. **Waiting:** on start it prints `Waiting` and does nothing until you press **Esc**. Use that time to click into the
   latency field of the program you want to control.
2. **Running:** one second after Esc, every 500 ms it:
   - presses **Backspace** three times to clear the current value;
   - types a new three-digit value on the numpad: the first digit 1 or 2 and the other two 1 to 9, so the latency
     jumps around randomly between 111 and 299 ms.
3. **Stop:** press **Esc** again to end the macro.

Timing uses `timeGetTime` (Winmm), the keys are read with `GetAsyncKeyState` and the random digits come from
`std::mt19937`.

## Build

Open `LagModifier.sln` in Visual Studio (toolset v143) and build the `LagModifier` console application (Win32 or
x64). The target program must accept numpad digits in its latency field, and it has to have focus while the macro
runs: the keys go to whichever window is active.
