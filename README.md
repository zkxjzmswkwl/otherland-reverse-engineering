## Points of interest

>Note: 
>
>I'm writing (and pushing) this as I go, as I'd like to have frequent back-ups of this `README` in particular. 
>
Because I'm lazy, addresses noted are not going to be found at `module_base + 0xAddress`. If you wish to tinker with these addresses, you must do something like `GetModuleHandleA("module.exe") - 1x<address_listed>;`

### Symbols

#### Winsock

##### send(SOCKET s, char const* buffer, int32_t len, int32_t flags)
* `0x1284230` `__fastcall, (void* arg1)`

* `0x1284490` `__thiscall (void* arg1, int32_t arg2)`

* `0xEF0300` `typedef void(__fastcall* _SendPacket)(void* thisptr, void* a1, char* a2, int32_t a3, int32_t* a4)`

>Note there are two to three other virtual functions which call `send`, however, slapping breakpoints on them yielded no results. I'm unsure what they're used for as of now.

##### Functionality (naive)
The first address takes in what Binary Ninja *thinks* is a `void*`. This is likely a pointer to a constructed (and assumingly encrypted) packet object. 

With the structure of the function being `__fastcall (void* packetPointer)`, we'll make some assumptions on where interesting data may be located.

At `0x128427A`, a "`void`" is declared and passed to a function at `0x1283D00`, along with `*(packetPointer + 0x30)`, as well as the same cast again, but with `packetPointer + 0x34`. For now, we'll refer to that `void*` simply as `var_2c`. `var_2c` is used as an `out` argument for that function call. With this, we'll assume, for now, that `packetPointer + 0x30` is the opcode, and `packetPointer + 0x34` is the packet buffer.