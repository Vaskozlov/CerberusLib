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
     
        always_inline VirtualAddr &operator-=(const VirtualAddr _rhs) noexcept {
            this->_address -= _rhs.value();
            return *this;
        }

        always_inline VirtualAddr &operator+=(const VirtualAddr _rhs) noexcept {
            this->_address += _rhs.value();
            return *this;
        }

        always_inline VirtualAddr &operator/=(const VirtualAddr _rhs) noexcept {
            this->_address = reinterpret_cast<cerb::byte*>(value() / _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator*=(const VirtualAddr _rhs) noexcept {
            this->_address = reinterpret_cast<cerb::byte*>(value() * _rhs.value());
            return *this;
        }
        
        always_inline VirtualAddr &operator&=(const VirtualAddr _rhs) noexcept {
            this->_address = reinterpret_cast<cerb::byte*>(value() & _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator|=(const VirtualAddr _rhs) noexcept {
            this->_address = reinterpret_cast<cerb::byte*>(value() | _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator^=(const VirtualAddr _rhs) noexcept {
           this->_address = reinterpret_cast<cerb::byte*>(value() ^ _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator%=(const VirtualAddr _rhs){
            this->_address = reinterpret_cast<cerb::byte*>(value() % _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator<<=(const VirtualAddr _rhs){
            this->_address = reinterpret_cast<cerb::byte*>(value() << _rhs.value());
            return *this;
        }

        always_inline VirtualAddr &operator>>=(const VirtualAddr _rhs){
            this->_address = reinterpret_cast<cerb::byte*>(value() >> _rhs.value());
            return *this;
        }

    public:
        always_inline size_t GetAmountOfKB() const noexcept {
            return (value() >> 10UL);
        }

        always_inline size_t GetAmountOfMB() const noexcept {
            return (value() >> 20UL);
        }

        always_inline size_t GetAmountOfGB() const noexcept {
            return (value() >> 30UL);
        }

    public:
        always_inline size_t Get4KBIndex() const noexcept {
            return (value() >> 12UL) % 512;
        }

        always_inline size_t Get2MBIndex() const noexcept {
            return (value() >> 21UL) % 512;
        }

        always_inline size_t Get1GBIndex() const noexcept {
            return (value() >> 30UL);
        }

    public:
        friend bool operator==(const VirtualAddr _lhs, const VirtualAddr &_rhs){
            return _lhs._address == _rhs._address;
        }

        inline friend bool operator!=(const VirtualAddr _lhs, const VirtualAddr &_rhs){
            return _lhs._address != _rhs._address;
        }

        friend bool operator>(const VirtualAddr _lhs, const VirtualAddr &_rhs){
            return _lhs._address > _rhs._address;
        }

        friend bool operator<(const VirtualAddr _lhs, const VirtualAddr &_rhs){
            return _lhs._address < _rhs._address;
        }

        inline friend bool operator>=(const VirtualAddr _lhs, const VirtualAddr &_rhs){
             return _lhs._address >= _rhs._address;
        }

        inline friend bool operator<=(const VirtualAddr _lhs, const VirtualAddr &_rhs){
             return _lhs._address <= _rhs._address;
        }

    public:
        always_inline friend VirtualAddr operator+(VirtualAddr lhs, const VirtualAddr _rhs){
            lhs._address += _rhs.value();
            return lhs;
        }

        always_inline friend VirtualAddr operator-(VirtualAddr lhs, const VirtualAddr _rhs){
            lhs._address -= _rhs.value();
            return lhs;
        }

        always_inline friend VirtualAddr operator%(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() % _rhs.value();
        }

        always_inline friend VirtualAddr operator/(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() / _rhs.value();
        }

        always_inline friend VirtualAddr operator*(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() * _rhs.value();
        }

        always_inline friend VirtualAddr operator&(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() & _rhs.value();
        }

        always_inline friend VirtualAddr operator|(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() | _rhs.value();
        }

        always_inline friend VirtualAddr operator^(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() ^ _rhs.value();
        }

        always_inline friend VirtualAddr operator>>(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() >> _rhs.value();
        }

        always_inline friend VirtualAddr operator<<(const VirtualAddr _lhs, const VirtualAddr _rhs){
            return _lhs.value() << _rhs.value();
        }

    public:
        template<typename _Tp>
        always_inline operator _Tp*() const { return static_cast<_Tp*>(address()); }

    public:
        VirtualAddr &operator=(VirtualAddr &&other) = default;
        VirtualAddr &operator=(const VirtualAddr &other) = default;

    public:
        VirtualAddr(VirtualAddr &other) = default;
        VirtualAddr(VirtualAddr &&other) = default;

    public:
        VirtualAddr() = default;
        ~VirtualAddr() = default;
        always_inline VirtualAddr(u64 addr) : _address(reinterpret_cast<cerb::byte*>(addr)) {}
        always_inline VirtualAddr(void *addr) : _address(reinterpret_cast<cerb::byte*>(addr)) {}
        
        always_inline VirtualAddr(size_t index1GB, size_t index2MB, size_t index4KB) : _address(
            reinterpret_cast<cerb::byte*>(
                    (index1GB<<30) + (index2MB << 21) + (index4KB << 12)
            )
        ) {}
	};

} // namespace cerb
