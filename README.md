# Points of interest

>Note: 
>
>I'm writing (and pushing) this as I go, as I'd like to have frequent back-ups of this `README` in particular. 
>
>Addresses noted here are located at `module_base + 0xAddress`.

## Symbols - Winsock

### send(SOCKET s, char const* buffer, int32_t len, int32_t flags)
* `0xE84230` `__fastcall, (void* arg1)`

* `0xE84490` `__thiscall (void* arg1, int32_t arg2)`

* `0xAF0300` `typedef void(__fastcall* _SendPacket)(void* thisptr, void* a1, char* a2, int32_t a3, int32_t* a4)`

>Note there are two to three other virtual functions which call `send`, however, slapping breakpoints on them yielded no results. I'm unsure what they're used for as of now.

##### Functionality (naive)
The first address takes in what Binary Ninja *thinks* is a `void*`. This is likely a pointer to a constructed (and assumingly encrypted) packet object. 

With the structure of the function being `__fastcall (void* packetPointer)`, we'll make some assumptions on where interesting data may be located.

At `0xE84490`, a "`void`" is declared and passed to a function at `0xE83D00`, along with `*(packetPointer + 0x30)`, as well as the same cast again, but with `packetPointer + 0x34`. For now, we'll refer to that `void*` simply as `var_2c`. `var_2c` is used as an `out` argument for that function call. With this, we'll assume, for now, that `packetPointer + 0x30` is the opcode, and `packetPointer + 0x34` is the packet buffer.

Unfortunately, none of these functions are called on game start or upon login request. I'm assuming this is due to a check (likely http req) to a server checking the status of the servers. Since they're offline, these are never hit. Will update when I tinker more.