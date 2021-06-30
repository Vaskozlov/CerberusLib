#include <compare>
#include <cerberus/cerberus.h>

namespace cerb{

	class __attribute__((trivial_abi)) VirtualAddr{
		cerb::byte *_address;

	public:
		always_inline void *address() const noexcept {
            return reinterpret_cast<void*>(_address);
        }

        always_inline u64 value() const noexcept {
            return reinterpret_cast<u64>(_address);
        }

    public:
        always_inline VirtualAddr &operator++() noexcept {
            this->_address++;
            return *this;
        }

        always_inline VirtualAddr &operator--() noexcept {
            this->_address--;
            return *this;
        }

        always_inline VirtualAddr operator++(int) noexcept {
            this->_address++;
            return *this;
        }

        always_inline VirtualAddr operator--(int) noexcept {
            this->_address--;
            return *this;
        }

        always_inline VirtualAddr &operator-=(void *change) noexcept {
            this->_address -= reinterpret_cast<size_t>(change);
            return *this;
        }

        always_inline VirtualAddr &operator+=(void *change) noexcept {
            this->_address += reinterpret_cast<size_t>(change);
            return *this;
        }

        always_inline VirtualAddr &operator-=(size_t change) noexcept {
            this->_address -= change;
            return *this;
        }

        always_inline VirtualAddr &operator+=(size_t change) noexcept {
            this->_address += change;
            return *this;
        }

        always_inline VirtualAddr &operator-=(VirtualAddr &change) noexcept {
            this->_address -= change.value();
            return *this;
        }

        always_inline VirtualAddr &operator+=(VirtualAddr &change) noexcept {
            this->_address += change.value();
            return *this;
        }

        always_inline friend VirtualAddr operator+(VirtualAddr lhs, const VirtualAddr& rhs){
            lhs += rhs.value();
            return lhs;
        }

        always_inline friend VirtualAddr operator-(VirtualAddr lhs, const VirtualAddr& rhs){
            lhs -= rhs.value();
            return lhs;
        }

    public:
        friend bool operator==(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
            return _lhs._address == _rhs._address;
        }

        inline friend bool operator!=(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
            return _lhs._address != _rhs._address;
        }

        friend bool operator>(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
            return _lhs._address > _rhs._address;
        }

        friend bool operator<(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
            return _lhs._address < _rhs._address;
        }

        inline friend bool operator>=(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
             return _lhs._address >= _rhs._address;
        }

        inline friend bool operator<=(const VirtualAddr &_lhs, const VirtualAddr &_rhs){
             return _lhs._address <= _rhs._address;
        }

    public:
        VirtualAddr &operator=(VirtualAddr &&other) = default;
        VirtualAddr &operator=(const VirtualAddr &other) = default;

    public:
        VirtualAddr(VirtualAddr &other) = default;
        VirtualAddr(VirtualAddr &&other) = default;

    public:
        VirtualAddr() = default;
        ~VirtualAddr() = default;
        always_inline VirtualAddr(void *addr) : _address(reinterpret_cast<cerb::byte*>(addr)) {}
        always_inline VirtualAddr(u64 addr) : _address(reinterpret_cast<cerb::byte*>(addr)) {}
	};

} // namespace cerb
