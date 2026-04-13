# Project Requirements
This file contains a proper explanation on what should be implemented.

## Functional
### General
- Raw pointers usage prohibited. You *will* forget to `delete`.
You have `sptr`, `wptr` and `uptr`, which are aliases for
`std::shared_ptr`, `std::weak_ptr` and `std::unique_ptr` respectively.
- Write all your code within the `dstr` namespace.
- `using namespace std;` and any other `using namespace ...` are prohibited.
If you want to omit `std::` prefix, writing `using std::...` allowed in `.cpp` files.
Only in `.cpp` files!

### Array
`dstr::array` must be a single memory layout containing values of the same data type.
Internal implementation must be the same (or at least close to) as `std::vector`.
An additional class `dstr::basic_array` must be implemeted as basic array.

### List


## Non-functional
