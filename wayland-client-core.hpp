#ifndef INCLUDE_WAYLAND_CLIENT_CORE_HPP_12C976D2_782D_47F9_B2F9_F8E8FFC3104E_
#define INCLUDE_WAYLAND_CLIENT_CORE_HPP_12C976D2_782D_47F9_B2F9_F8E8FFC3104E_

#include <functional>
#include <algorithm>

namespace wayland_client_core
{
  class proxy {
  public:
    virtual ~proxy() { }
  };

  namespace details
  {
    struct fixed { int32_t value; };
    struct chunk { uint32_t size; uint32_t data[1]; };

    class proxy {
    public:
      virtual ~proxy() { }
    };

    template <typename WL_C_STRUCT, size_t VERSION>
    class interface_core : public proxy
    {
      interface_core(interface_core const&) = delete;
      interface_core& operator = (interface_core const&) = delete;

    public:
      using c_struct_type = WL_C_STRUCT;

    public:
      interface_core(WL_C_STRUCT* pointer = nullptr)
	: pointer(pointer)
      {
      }
      interface_core(interface_core&& other)
	: pointer(nullptr)
      {
	std::swap(this->pointer, other.pointer);
      }
      ~interface_core() override {
      }
      interface_core& assign(c_struct_type* pointer) {
	this->operator = (interface_core(pointer));
	return *this;
      }

      interface_core& operator = (interface_core&& other) {
	if (this != &other) {
	  std::swap(this->pointer, other.pointer);
	}
	return *this;
      }

      operator c_struct_type*() const { return this->pointer; }

    protected:
      c_struct_type* pointer;
    };
  }
}

#endif/*INCLUDE_WAYLAND_CLIENT_CORE_HPP_12C976D2_782D_47F9_B2F9_F8E8FFC3104E_*/
