#ifndef INCLUDE_UUID_HPP_BF42FEE6_EEAB_4CDB_9F00_D546FB494450_
#define INCLUDE_UUID_HPP_BF42FEE6_EEAB_4CDB_9F00_D546FB494450_

#include <string>
#include <utility> // std::rel_ops

namespace utilities
{
  class uuid {
  public:
    uuid();
    ~uuid();

  public:
    std::string to_lower_str() const;
    std::string to_upper_str() const;

  public:
    friend bool operator == (uuid const& lhs, uuid const& rhs);
    friend bool operator != (uuid const& lhs, uuid const& rhs);

    friend bool operator <  (uuid const& lhs, uuid const& rhs);
    friend bool operator >  (uuid const& lhs, uuid const& rhs);
    friend bool operator <= (uuid const& lhs, uuid const& rhs);
    friend bool operator >= (uuid const& lhs, uuid const& rhs);
    
  private:
    unsigned char buf[16];
  };
}

#endif/*INCLUDE_UUID_HPP_BF42FEE6_EEAB_4CDB_9F00_D546FB494450_*/
