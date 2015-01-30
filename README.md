# HunnyBop CSGO
CSGO bunnyhop script.  
There are zero anti-cheat bypass methods in this so have fun getting VAC banned.   
I am not responsible for what you do with this.

**How to use:**  
1. compile and run
2. start csgo, wait a few seconds  
3. hold space and pretend to be phoon 
4. ???

**Current Offsets:**  
```C
// Version: 507262
#define OFFSET_LOCALPLAYER 0x00A70A44
#define OFFSET_FLAGS 0x100
#define OFFSET_LIFESTATE 0x25B
#define OFFSET_TEAMID 0xF0

// unused but might be used later, who knows
#define OFFSET_JUMP 0x04AA1F7C
#define OFFSET_ENGINEPOINTER 0x0055A094
#define OFFSET_ENTITYLIST 0x04A133C4
#define OFFSET_HEALTH 0xFC
```

**Note:**  
To get this running you need to get working offsets for the current version of the game. Without them this script is useless. Google is your friend, I wont be updating the offsets regularly at all.
