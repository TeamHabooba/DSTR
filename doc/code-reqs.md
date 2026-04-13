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
- 

### Array
`dstr::array` must be a single memory layout containing values of the same data type.
Internal implementation must be the same (or at least close to) as `std::vector`.
An additional class `dstr::basic_array` must be implemeted as basic array.

### List


## Non-functional
