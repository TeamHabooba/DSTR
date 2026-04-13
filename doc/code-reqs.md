# Project Requirements
This file contains a proper explanation on what should be implemented and what are the coding rules.
Unlike the [code-style.md](./code-style.md) file, that says *how* to format code, this file
describes *what* should be in the source code.

## Functional
### General
- Split your source code in `.h` (or `.hpp`, `.hxx`, `.h++`) and `.cpp` (or `.cxx`, `.c++`) files.
First must be used for declarations only, second - for implementation.
- Raw pointers usage prohibited. You *will* forget to `delete`.
You have `sp`, `wp` and `up`, which are aliases for
`std::shared_ptr`, `std::weak_ptr` and `std::unique_ptr` respectively.
- Write all your code within the `dstr` namespace.
- `using namespace std;` and any other `using namespace ...` are prohibited.
If you want to omit `std::` prefix, writing `using std::...` (e.g.: `using std::cout; using std::cin`) allowed.
But please check the [`common/aliases.h`](../src/common/aliases.h) first.
It is strongly recommended not to override what's written there.
- Don't use C-style conversions (e.g. `(int)(variable)`) or `std::reinterpret_cast`. Only explicit `std::static_cast` allowed.
- Define all constant variables as `constexpr`. Don't use `#define` for this.
- If you need to create an alias, prefer `using t = type` instead of `typedef`. Never use `#define` on this purpose.
- Omit using `#define` include-guards. Use `pragma once` only.
- Change only your code. Never rewrite, delete or create files outside of your directory.
If any error occured in those files, please contact responsible team member(s) ASAP.
- Don't create your own `main()` functions. If you want to use one for testing, remove it before opening a pull request.
- Any collection types (`dstr::array`, `dstr::list`, etc.) must be templates.

### Array
Basic data type: `dstr::array`  
`dstr::array` must be implemeted as a single
memory layout containing values of the same data type
with dynamic memory allocation (smart pointers and RAII).  

Experimental data type: `dstr::dynamic_array`  
An additional class `dstr::dynamic_array` must have
internal implementation must be the same as (or at least close to)
`std::vector`.

Refer to
[this](https://medium.com/@simonyihunie/arrays-vs-vectors-in-modern-c-a-detailed-comparison-with-examples-b797fefff7f7) 
or [this](https://stackoverflow.com/questions/6462985/c-stdvector-vs-array-in-the-real-world)
webpage to learn the difference between basic array, `std::array` and `std::vector`).

### List
Basic data type: `dstr::list`  
`dstr::list` must be a singly-linked list. As mentioned above,
use smart pointers and RAII instead of raw pointers.

Experimental data type: `dstr::double_list`  
Implement `dstr::double_list` class based on double linked list
structure. No raw pointers.

Refer to [this](https://www.geeksforgeeks.org/dsa/types-of-linked-list/)
webpage to learn about the different types of linked lists)

## Non-functional
- All coding style rules explained [here](./code-style.md).
- Join all the meetings. Only very important meetings will be offline.
- Complete all the tasks in time.
- If 2 rules above are not followed by a team member, they will be kicked from the group.
- If you have a reason for absence/deadline failure, mention it in WhatsApp group chat.
