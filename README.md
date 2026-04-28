# Krage - Internal Cheat for Counter-Strike 1.6

**Krage** is a lightweight internal cheat for Counter-Strike 1.6, providing **distance-based aimbot** and **anti-flash** functionality. It is designed for minimalism and efficiency, hooking directly into the GoldSrc engine via `hw.dll`. 

---

## **Features**

- **Aimbot**: Automatically calculates distance and aligns your view angles to the closest valid enemy.
- **Anti-Flash**: Intercepts the engine's screen fade data, preventing screen blinding effects caused by flashbang grenades.
- **Debug Console**: Automatically allocates a background console window to monitor the injection and toggle status of the cheat.
- **Safe Unload (Panic Key)**: Instantly detaches the cheat and frees the library from the game process with a single keypress.

---

## **Hotkeys**

- **`Right Shift`** : Toggle Hacks (Turns Aimbot and Anti-Flash ON / OFF).
- **`Escape`** : Panic Key (Terminates the hack thread and safely unloads the DLL).

---

## **Disclaimer**

This project is for educational purposes only. Using cheats in games may result in penalties, bans (such as VAC), or legal consequences. Please ensure compliance with the game's terms of service and community guidelines.

---

## **How to Use**

1. **Build the Project:**
   - Open the solution file (`Krage.sln`) in Visual Studio.
   - Build the solution in **Release mode** (x86/32-bit architecture is required for CS 1.6).

2. **Inject the DLL:**
   - Launch Counter-Strike 1.6.
   - Use a DLL injector to inject the built `.dll` file into the `hl.exe` (or `cstrike.exe`) game process.
   - You will see a "WELCOME TO KRAGE HACKS!" message box confirming successful injection, alongside a debug console.

3. **Activate Features:**
   - Press **Right Shift** to toggle the aimbot and anti-flash features while in-game. 
   - Check the allocated console window for a `[+] HACKS TOGGLED` confirmation message.

---

## **Requirements**

- **Operating System:** Windows 10/11.
- **Development Tools:** Visual Studio 2022 or later.
- **Game Version:** Counter-Strike 1.6 (GoldSrc Engine). *Note: The cheat relies on specific `hw.dll` and `client.dll` memory offsets.*

---

## **Legal Notice**

This project is intended solely for learning, reverse engineering, and research purposes. The author does not endorse or encourage the use of cheats in multiplayer games or any other forms of software misuse. Use responsibly and entirely at your own risk.
