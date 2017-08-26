
#include "uuid.hpp"

#include <string>

#include <uuid/uuid.h>

namespace utilities
{
  uuid::uuid()
  {
    uuid_generate(this->buf);
  }
  uuid::~uuid()
  {
  }

  std::string uuid::to_lower_str() const {
    char str[64] = { };
    uuid_unparse_lower(this->buf, str);
    return str;
  }

  std::string uuid::to_upper_str() const {
    char str[64] = { };
    uuid_unparse_upper(this->buf, str);
    return str;
  }

  bool operator == (uuid const& lhs, uuid const& rhs) {
    return uuid_compare(lhs.buf, rhs.buf) == 0;
  }
  bool operator != (uuid const& lhs, uuid const& rhs) {
    return std::rel_ops::operator != (lhs, rhs);
  }

  bool operator <  (uuid const& lhs, uuid const& rhs) {
    return uuid_compare(lhs.buf, rhs.buf) < 0;
  }
  bool operator >  (uuid const& lhs, uuid const& rhs) {
    return std::rel_ops::operator > (lhs, rhs);
  }
  bool operator <= (uuid const& lhs, uuid const& rhs) {
    return std::rel_ops::operator <= (lhs, rhs);
  }
  bool operator >= (uuid const& lhs, uuid const& rhs) {
    return std::rel_ops::operator >= (lhs, rhs);
  }
}
