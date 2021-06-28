#include <cerberus/cerberus.h>

namespace cerb{

	class __attribute__((trivial_abi)) VirtualAddr{
		cerb::byte *_address;

	public:
		always_inline void *address() const noexcept {
            return reinterpret_cast<void*>(_address);
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

    public:
        always_inline auto operator<=>(const VirtualAddr&) const = default;

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

} /* cerb */
